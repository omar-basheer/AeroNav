//  Routes
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
// #include "airports.h"

/**
 This class contains functions that read and utilize data stored in the Routes.csv file
 */


Route::Route()
{
    this->Source_AirportCode = "";
    this->AirlineCode = "";
}


Route::Route(std::string Destination_AirportCode, std::string airlineCode)
{
    this->Destination_AirportCode = Destination_AirportCode;
    this->AirlineCode = airlineCode;
}

const std::string Route::getSA_Code() const
{
    return Source_AirportCode;
}

const std::string Route::getDA_Code() const
{
    return Destination_AirportCode;
}

const std::string Route::getAirline_Code() const
{
    return AirlineCode;
}

std::string const Route::getStops() const
{
    return Stops;
}

/**
 * To String mehtod for Route Objects
 */
const std::string Route::toString() const
{
    return "[ " + getDA_Code() + ", " + getAirline_Code() + " ]";
}

/**
 * AirportRoutesMap - map with string keys and string vector values that stores the iata codes of all airports that can be reached from a particular source airport
 */
std::map<std::string, std::vector<std::string>> Route::AirportRoutesMap;

/**
 * AirlineRoutesMap - map with string vector keys and string vector values that stores the airline codes of all the airline that goes from one source airport to all destination airports
 */
std::map<std::vector<std::string>, std::vector<std::string>> Route::AirlineRoutesMap;

/**
 * Split a string by a delimiter and store values into a vector
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
        //            cout << substring << endl;
        output.emplace_back(substring);
        vector_string.erase(0, pos + delimiter.length());
    }
    output.emplace_back(vector_string);
    return output;
}

/**
 * Convert values in a vector into a single string
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
    //        stream << "]";

    return stream.str();
}

/**
 * Read Route.csv file
 * @param filename  a csv file
 * @return a map with string keys of an airport iata code and values of the iata codes of all destination airports that can be reached from a particular key
 */
std::map<std::string, std::vector<std::string>> Route::AirportRouteReader(std::string const &filename)
{

    // map<string, vector<string>> AirRoutesMap;
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
            //                cout << "  >> got streamline" << endl;
            //                cout << "   >> streamline: " << streamline << endl;

            while (getline(line_of, streamword, ','))
            {
                splitline.push_back(streamword);
                //                    cout << "   >> got streamword: " << streamword << endl;
            }

            //                read into AirRoutesMap first
            std::string routekey = splitline[2];
            //                cout << endl;
            //                cout << " >> key - " << routekey << endl;
            if (AirportRoutesMap.count(routekey) > 0)
            {
                // key found
                std::vector<std::string> routelist = AirportRoutesMap[splitline[2]];
                //                    cout << "  current list - " << vecToString(routelist) << endl;
                routelist.emplace_back(splitline[4]);
                AirportRoutesMap.erase(splitline[2]);
                //                    cout << "  updated list - " << vecToString(routelist) << endl;
                //                    cout << endl;
                AirportRoutesMap.insert(std::pair<std::string, std::vector<std::string>>(routekey, routelist));
            }
            else
            {
                //                  key not found
                std::vector<std::string> routelist;
                routelist.emplace_back(splitline[4]);
                //                    cout << "  new current list - " << vecToString(routelist) << endl;
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
 * Read Route.csv file
 * @param filename  a csv file
 * @return a map with string vector keys of a route's airline and start aiport iata code, and values of the iata codes of all destination airports that can be reached from a particular key
 */
std::map<std::vector<std::string>, std::vector<std::string>> Route::AirlineRouteReader(std::string const &filename)
{

    std::fstream inputStream;
    inputStream.open(filename);
    //            cout << "> file opened"<<endl;
    // check if file exists
    if (inputStream)
    {
        std::vector<std::string> splitline;
        std::string streamline, streamword, temp;

        while (getline(inputStream, streamline))
        {
            splitline.clear();
            std::stringstream line_of(streamline);
            //                cout << "  >> got streamline" << endl;
            //                cout << "   >> streamline: " << streamline << endl;

            while (getline(line_of, streamword, ','))
            {
                splitline.push_back(streamword);
                //                    cout << "   >> got streamword: " << streamword << endl;
            }
            //              read into RouteAirlineMap
            std::vector<std::string> routekey2;
            routekey2.emplace_back(splitline[0]); // airline code
            routekey2.emplace_back(splitline[2]); // source airport
            routekey2.emplace_back(splitline[7]); // stops
                                                  //                cout << endl;
                                                  //                cout << " >> key - " << vecToString(routekey2) << endl;

            if (AirlineRoutesMap.find(routekey2) != AirlineRoutesMap.end())
            {
                // key found
                std::vector<std::string> routelist = AirlineRoutesMap[routekey2];
                //                    cout << "  current list - " << vecToString(routelist) << endl;
                routelist.emplace_back(splitline[4]);
                AirlineRoutesMap.erase(routekey2);
                AirlineRoutesMap.insert(std::pair<std::vector<std::string>, std::vector<std::string>>(routekey2, routelist));
            }
            else
            {
                // key not found
                std::vector<std::string> routelist = AirlineRoutesMap[routekey2];
                routelist.emplace_back(splitline[4]);
                //                    cout << "  new current list - " << vecToString(routelist) << endl;
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
 * Print out the key value pairs of a given map
 * @param thisMap  a map of string keys and string vector values
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
 * Print out the key value pairs of a given map
 * @overload
 */
void Route::printMap(std::map<std::vector<std::string>, std::vector<std::string>> thisMap)
{
    for (auto &pair : thisMap)
    {
        std::cout << vecToString(pair.first) << "] >> " << vecToString(pair.second) << "]" << std::endl;
    }
}

/**
 * Check if a given string deque conatins a given string
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
 * Check if a given string vector conatins a given string
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
 * Find a given goal airport from a start airport using airport iata codes
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
    //        cout << "added parent " << start_airport << " to frontier " << endl;
    std::vector<std::string> explored_set;
    //        cout << "explored set: " << vecToString(explored_set) << endl;
    std::vector<std::string> key;
    while (!frontier.empty())
    {
        std::string parent = frontier.front();
        frontier.pop_front();
        //            cout << "popped parent, " << parent << endl;
        child_parent.insert(std::pair<std::string, std::string>(parent, ""));
        explored_set.emplace_back(parent);
        //            cout << "added node to explored set, explored set: " << vecToString(explored_set) << endl;

        std::vector<std::string> successors = AirportRoutesMap[parent];
        if (!successors.empty())
        {
            for (int i = 0; i < successors.size(); i++)
            {
                std::string child = successors[i];
                child_parent.insert(std::pair<std::string, std::string>(child, parent));
                //                    cout << "generated successor: " << child << endl;
                if (!contains(explored_set, child) && (!contains(frontier, child)))
                {
                    if (child.compare(goal_airport) == 0)
                    {
                        //                            cout << "found goal: " << child << endl;
                        //                            cout << vecToString(solution_path(child_parent, child));
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
 * Find solution path by connecting each airport iata code to its given parent
 * @param solution_map  a map of parent-child relationships between all airports explored during the search. keys are iata codes of child states and values are iata codes of parent states.
 * @param child  the goal airport iata code, the last child discovered during the search
 * @return concatenated string of all connected nodes from start aiport to goal airport
 */
std::string Route::solution_path(std::map<std::string, std::string> solution_map, std::string child)
{
    std::vector<std::string> solution_path;
    solution_path.emplace_back(child);
    //        cout << vecToString(solution_path) << endl;
    std::string parent = solution_map[child];
    solution_path.emplace_back(parent);
    //        cout << vecToString(solution_path) << endl;
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

int main()
{

    std::map<std::string, std::vector<std::string>> airport_routemap;
    std::map<std::vector<std::string>, std::vector<std::string>> airline_routemap;

    std::string filename = "/Users/admin/Library/CloudStorage/OneDrive-AshesiUniversity/Ashesi University/ashesi year 2/sem2/intermediate computer programming/AeroNav/Routes/routes.csv";

    airport_routemap = Route::AirportRouteReader(filename);
    airline_routemap = Route::AirlineRouteReader(filename);
    //    Route::printMap(myAirRoutesMap);
    Route::printMap(airline_routemap);

    std::vector<std::string> test;
    test.emplace_back("AER");
    test.emplace_back("EGO");
    test.emplace_back("NBC");

    for (int i = 0; i <= test.size(); i++)
    {
        for (auto &pair : airline_routemap)
        {
            if (pair.first[1] == test[i])
            {
                std::cout << pair.first[0] << std::endl;
            }
        }
    }

    //    Route::findRoute("ACC", "CTU");
    //    vector<string> test;
    //    test.emplace_back("2B");
    //    test.emplace_back("DME");
    //    cout << Route::vecToString(myRoutesAirlineMap[test]) << endl;

    return 0;
}
