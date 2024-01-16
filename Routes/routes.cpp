//  Created by Omar Basheer on 11/20/22.

#include <map>
#include <set>
#include <deque>
#include <queue>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include "routes.h"
#include "../Airports/airports.h"

/**
 * @brief Default constructor for the Route class.
 * Initializes the Source_AirportCode and AirlineCode to empty strings.
 */
Route::Route()
{
    this->Source_AirportCode = "";
    this->AirlineCode = "";
}

/**
 * @brief Constructs a Route object with the given destination airport code and airline code.
 *
 * @param Destination_AirportCode The destination airport code.
 * @param airlineCode The airline code.
 */
Route::Route(std::string Destination_AirportCode, std::string airlineCode)
{
    this->Destination_AirportCode = Destination_AirportCode;
    this->AirlineCode = airlineCode;
}

/**
 * @brief Gets the source airport code.
 *
 * @return The source airport code as a string.
 */
const std::string Route::getSA_Code() const
{
    return Source_AirportCode;
}

/**
 * @brief Get the Destination Airport Code.
 *
 * @return The destination airport code as a string.
 */
const std::string Route::getDA_Code() const
{
    return Destination_AirportCode;
}

/**
 * @brief Gets the airline code.
 *
 * @return The airline code as a string.
 */
const std::string Route::getAirline_Code() const
{
    return AirlineCode;
}

/**
 * @brief Returns the stops of the route.
 *
 * @return The stops of the route as a string.
 */
const std::string Route::getStops() const
{
    return Stops;
}

/**
 * @brief Converts the Route object to a string representation.
 *
 * @return The string representation of the Route object.
 */
const std::string Route::toString() const
{
    return "[ " + getDA_Code() + ", " + getAirline_Code() + " ]";
}

/**
 * @brief A map that stores airport routes.
 *
 * This map associates a string key representing an airport with a vector of strings representing the routes from that airport.
 */
std::map<std::string, std::vector<std::string>> Route::AirportRoutesMap;

/**
 * @brief A map that stores airline routes.
 *
 * This map associates a vector of strings representing the departure and arrival airports
 * with a vector of strings representing the airlines that operate the route.
 */
std::map<std::vector<std::string>, std::vector<std::string>> Route::AirlineRoutesMap;

/**
 * @brief Split a string by a delimiter and store values into a vector
 * @param vector_string  a single string vlaue
 * @return vector of strings
 */
std::vector<std::string> Route::stringToVec(std::string vector_string)
{
    std::vector<std::string> output;
    std::string delimiter = ", ";
    std::string substring;
    size_t pos = 0;

    while ((pos = vector_string.find(delimiter)) != std::string::npos)
    {
        substring = vector_string.substr(0, pos);
        output.emplace_back(substring);
        vector_string.erase(0, pos + delimiter.length());
    }
    output.emplace_back(vector_string);
    return output;
}

/**
 * @brief Convert values in a vector into a single string
 * @param string_vector  a vector of strings
 * @return a single concatenated string of the vector values
 */
std::string const Route::vecToString(std::vector<std::string> string_vector)
{
    std::stringstream stream;
    stream << "[";
    for (auto it = string_vector.begin(); it != string_vector.end(); it++)
    {
        if (it != string_vector.begin())
        {
            stream << ", ";
        }
        stream << *it;
    }

    return stream.str();
}

/**
 * @brief Reads an airport route file and creates a map of routes.
 *
 * This function reads a file containing airport routes and creates a map
 * where the keys are route keys and the values are vectors of destinations.
 *
 * @param filename The name of the file to read.
 * @return A map of routes, where the keys are route keys and the values are vectors of destinations.
 */
std::map<std::string, std::vector<std::string>> Route::AirportRouteReader(std::string const &filename)
{
    std::fstream inputStream;
    inputStream.open(filename);

    if (inputStream)
    {
        // cout << "> file opened"<<endl;
        std::vector<std::string> splitline;
        std::string streamline, streamword, temp;

        while (getline(inputStream, streamline))
        {
            splitline.clear();
            std::stringstream line_of(streamline);

            while (getline(line_of, streamword, ','))
            {
                splitline.push_back(streamword);
            }

            // read into AirRoutesMap first
            std::string routekey = splitline[2];

            if (AirportRoutesMap.count(routekey) > 0)
            {
                // key found
                std::vector<std::string> routelist = AirportRoutesMap[splitline[2]];
                routelist.emplace_back(splitline[4]);
                AirportRoutesMap.erase(splitline[2]);
                AirportRoutesMap.insert(std::pair<std::string, std::vector<std::string>>(routekey, routelist));
            }
            else
            {
                // key not found
                std::vector<std::string> routelist;
                routelist.emplace_back(splitline[4]);
                AirportRoutesMap.insert(std::pair<std::string, std::vector<std::string>>(routekey, routelist));
            }
        }
        inputStream.close();
        std::cout << "> Airport-Route map created..." << std::endl;
    }
    else
    {
        std::cout << "error opening/reading data file: check that the input file is in right directory and the given file name matches" << std::endl;
    }

    return AirportRoutesMap;
}

/**
 * @brief Reads airline routes from a file and creates a map of routes.
 *
 * This function reads airline routes from a file specified by the filename parameter.
 * It creates a map where the keys are vectors of strings representing the airline code, source airport, and number of stops,
 * and the values are vectors of strings representing the destinations.
 *
 * @param filename The name of the file to read the airline routes from.
 * @return A map of airline routes, where the keys are vectors of strings and the values are vectors of strings.
 */
std::map<std::vector<std::string>, std::vector<std::string>> Route::AirlineRouteReader(std::string const &filename)
{

    std::fstream inputStream;
    inputStream.open(filename);
    // check if file exists
    if (inputStream)
    {
        std::vector<std::string> splitline;
        std::string streamline, streamword, temp;

        while (getline(inputStream, streamline))
        {
            splitline.clear();
            std::stringstream line_of(streamline);

            while (getline(line_of, streamword, ','))
            {
                splitline.push_back(streamword);
            }
            // read into RouteAirlineMap
            std::vector<std::string> routekey2;
            routekey2.emplace_back(splitline[0]); // airline code
            routekey2.emplace_back(splitline[2]); // source airport
            routekey2.emplace_back(splitline[7]); // stops

            if (AirlineRoutesMap.find(routekey2) != AirlineRoutesMap.end())
            {
                // key found
                std::vector<std::string> routelist = AirlineRoutesMap[routekey2];
                routelist.emplace_back(splitline[4]);
                AirlineRoutesMap.erase(routekey2);
                AirlineRoutesMap.insert(std::pair<std::vector<std::string>, std::vector<std::string>>(routekey2, routelist));
            }
            else
            {
                // key not found
                std::vector<std::string> routelist = AirlineRoutesMap[routekey2];
                routelist.emplace_back(splitline[4]);
                AirlineRoutesMap.insert(std::pair<std::vector<std::string>, std::vector<std::string>>(routekey2, routelist));
            }
        }
        inputStream.close();
        std::cout << "> Airline-Route map created..." << std::endl;
    }
    else
    {
        std::cout << "error opening/reading data file: check that the input file is in right directory and the given file name matches" << std::endl;
    }

    return AirlineRoutesMap;
}

/**
 * @brief Prints the contents of a map, where the keys are strings and the values are vectors of strings.
 *
 * @param thisMap The map to be printed.
 */
void Route::printMap(std::map<std::string, std::vector<std::string>> thisMap)
{
    for (auto &pair : thisMap)
    {
        std::cout << "[" << pair.first << "]"
                  << " >> " << vecToString(pair.second) << std::endl;
        std::cout << std::endl;
    }
}

/**
 * @brief Prints the contents of a map, where the keys and values are vectors of strings.
 *
 * @param thisMap The map to be printed.
 */
void Route::printMap(std::map<std::vector<std::string>, std::vector<std::string>> thisMap)
{
    for (auto &pair : thisMap)
    {
        std::cout << vecToString(pair.first) << "] >> " << vecToString(pair.second) << "]" << std::endl;
    }
}

/**
 * @brief Check if a given string deque conatins a given string
 * @param deq a deque of strings
 * @param value a string
 * @return true if deque contains element and false if otherwise
 */
bool Route::contains(std::deque<std::string> deq, std::string value)
{
    std::deque<std::string>::iterator itr;
    itr = find(deq.begin(), deq.end(), value);
    if (itr != deq.end())
    {
        return true;
    }
    else
        return false;
}

/**
 * @brief Check if a given string vector conatins a given string
 * @param vec a vector of strings
 * @param value a string
 * @return true if vector contains element and false if otherwise
 */
bool Route::contains(std::vector<std::string> vec, std::string value)
{
    if (std::find(vec.begin(), vec.end(), value) != vec.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * @brief Find a given goal airport from a start airport using airport iata codes
 * @param start_airport the iata code of a start airport
 * @param goal_airport the iata code of a goal airport
 * @return string of iata codes of found solution path containing all connected airports between start airport and goal airport
 */
std::string Route::findRoute(std::string start_airport, std::string goal_airport)
{

    std::map<std::string, std::string> child_parent;
    std::cout << "  >> start airport: " << start_airport << std::endl;
    std::cout << "  >> goal airport: " << goal_airport << std::endl;
    std::cout << "     >>> searching..." << std::endl;

    std::deque<std::string> frontier;
    frontier.emplace_back(start_airport);
    std::vector<std::string> explored_set;
    std::vector<std::string> key;

    while (!frontier.empty())
    {
        std::string parent = frontier.front();
        frontier.pop_front();
        child_parent.insert(std::pair<std::string, std::string>(parent, ""));
        explored_set.emplace_back(parent);
        std::vector<std::string> successors = AirportRoutesMap[parent];

        if (!successors.empty())
        {
            for (int i = 0; i < successors.size(); i++)
            {
                std::string child = successors[i];
                child_parent.insert(std::pair<std::string, std::string>(child, parent));
                if (!contains(explored_set, child) && (!contains(frontier, child)))
                {
                    if (child.compare(goal_airport) == 0)
                    {
                        std::string solution = solution_path(child_parent, child);
                        return solution;
                    }
                }
                frontier.emplace_back(child);
            }
        }
        else
        {
            std::cout << "no route from this airport: " << std::endl;
            break;
        }
    }
    return NULL;
}

/**
 * @brief Find solution path by connecting each airport iata code to its given parent
 * @param solution_map  a map of parent-child relationships between all airports explored during the search. keys are iata codes of child states and values are iata codes of parent states.
 * @param child  the goal airport iata code, the last child discovered during the search
 * @return concatenated string of all connected nodes from start aiport to goal airport
 */
std::string Route::solution_path(std::map<std::string, std::string> solution_map, std::string child)
{
    std::vector<std::string> solution_path;
    solution_path.emplace_back(child);
    std::string parent = solution_map[child];
    solution_path.emplace_back(parent);

    while (parent != "")
    {
        child = parent;
        parent = solution_map[child];
        solution_path.emplace_back(parent);
    }
    reverse(solution_path.begin(), solution_path.end());
    std::cout << "      >>>> solution path: " << vecToString(solution_path) << " ]" << std::endl;

    return vecToString(solution_path);
}

// std::map<std::string, std::vector<std::string>> Route::AirportRoutesMap;
// std::map<std::vector<std::string>, std::vector<std::string>> Route::AirlineRoutesMap;

// int main()
// {

//     std::map<std::string, std::vector<std::string>> airport_routemap;
//     std::map<std::vector<std::string>, std::vector<std::string>> airline_routemap;

//     std::string filename = "/Users/admin/Library/CloudStorage/OneDrive-AshesiUniversity/Ashesi University/ashesi year 2/sem2/intermediate computer programming/AeroNav/Routes/routes.csv";

//     airport_routemap = Route::AirportRouteReader(filename);
//     airline_routemap = Route::AirlineRouteReader(filename);
//     //    Route::printMap(myAirRoutesMap);
//     Route::printMap(airline_routemap);

//     std::vector<std::string> test;
//     test.emplace_back("AER");
//     test.emplace_back("EGO");
//     test.emplace_back("NBC");

//     for (int i = 0; i <= test.size(); i++)
//     {
//         for (auto &pair : airline_routemap)
//         {
//             if (pair.first[1] == test[i])
//             {
//                 std::cout << pair.first[0] << std::endl;
//             }
//         }
//     }

//     //    Route::findRoute("ACC", "CTU");
//     //    vector<string> test;
//     //    test.emplace_back("2B");
//     //    test.emplace_back("DME");
//     //    cout << Route::vecToString(myRoutesAirlineMap[test]) << endl;

//     return 0;
// }
