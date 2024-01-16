//  Created by Omar Basheer on 11/27/22.

#include <vector>
#include <sstream>
#include <fstream>
#include <cstring>
#include <iostream>
#include <algorithm>
#include "read_write.h"
#include "../Routes/routes.h"
#include "../Airports/airports.h"
#include "../Haversine/haversine.h"

std::string ReadWrite::StartCity;/* The start city of a given flight*/
std::string ReadWrite::StartCountry;/* The start country of a given flight*/
std::string ReadWrite::Destination_City;/* The destination city of a given flight*/
std::string ReadWrite::Destination_Country;/* The destination country of a given flight*/

/**
 * @brief Retrieves the start city for the navigation.
 *
 * @return The start city as a string.
 */
std::string ReadWrite::getStartCity()
{
    return StartCity;
}

/**
 * @brief Retrieves the start country.
 *
 * @return The start country as a string.
 */
std::string ReadWrite::getStartCountry()
{
    return StartCountry;
}

/**
 * @brief Retrieves the destination city.
 *
 * @return The destination city as a string.
 */
std::string ReadWrite::getDestination_City()
{
    return Destination_City;
}

/**
 * @brief Get the destination country.
 * 
 * @return std::string The destination country.
 */
std::string ReadWrite::getDestination_Country()
{
    return Destination_Country;
}

/**
 * @brief Sets the starting city for the navigation.
 * 
 * @param city The name of the starting city.
 */
void ReadWrite::setStartCity(const std::string city)
{
    StartCity = city;
}

/**
 * @brief Sets the starting country for the ReadWrite object.
 * 
 * @param country The name of the starting country.
 */
void ReadWrite::setStartCountry(const std::string country)
{
    StartCountry = country;
}

/**
 * @brief Sets the destination city for the ReadWrite object.
 * 
 * @param city The name of the destination city.
 */
void ReadWrite::setDestinationCity(const std::string city)
{
    Destination_City = city;
}

/**
 * @brief Sets the destination country for the ReadWrite object.
 * 
 * @param country The name of the destination country.
 */
void ReadWrite::setDestinationCountry(const std::string country)
{
    Destination_Country = country;
}

/**
 * @brief Read user input file containing start city and country, and destination city and country
 * @param input_filename  the file name of the users input file
 */
void ReadWrite::inputFileReader(const std::string &input_filename)
{

    std::fstream inputStream;
    inputStream.open(input_filename);
    // check if file exists
    if (inputStream)
    {
        std::cout << std::endl;
        std::cout << "> Reading input file..." << std::endl;

        // split input file lines by ", " to get city and country values and store them in a vector
        std::vector<std::string> splitline;
        std::string delimiter = ", ";
        std::string substring;
        size_t pos = 0;
        std::string streamline, streamword, temp;

        while (getline(inputStream, streamline))
        {
            std::stringstream line_of(streamline);

            while ((pos = streamline.find(delimiter)) != std::string::npos)
            {
                substring = streamline.substr(0, pos);
                splitline.emplace_back(substring);
                streamline.erase(0, pos + delimiter.length());
            }
            splitline.emplace_back(streamline);
        }
        inputStream.close();
        std::cout << "> File read!" << std::endl;

        // set vector elements to respective variables
        setStartCity(splitline[0]);
        setStartCountry(splitline[1]);
        setDestinationCity(splitline[2]);
        setDestinationCountry(splitline[3]);
    }
    else
    {
        std::cout << "error opening/reading your file: check that input file is in right directory and the given file name matches" << std::endl;
    }

    std::string start_iata;
    std::string goal_iata;
    std::vector<std::string> all_starts;
    std::vector<std::string> all_goals;
    Airport tempair1;
    Airport tempair2;

    // get airport iata code from AirportMap associated with given city and country pair from user's input file
    for (auto const &pair : Airport::AirportMap)
    {
        if (pair.first[1] == getStartCity() && pair.first[2] == getStartCountry())
        {
            start_iata = pair.first[0];
            all_starts.emplace_back(start_iata);
        }
        if (pair.first[1] == Destination_City && pair.first[2] == Destination_Country)
        {
            goal_iata = pair.first[0];
            all_goals.emplace_back(goal_iata);
        }
    }
    std::cout << std::endl;
    std::cout << "> Starting search..." << std::endl;

    haversineHelper(all_starts, all_goals);
}

/**
 *@brief Calculates haversine distance between airports in a solution path and accumulates the values to obtain the total distance between the start and goal airports given a particular solution path. Passes solution path with lowest distance to outputFileWriter for file writing
 *@param all_starts a string vector of the iata codes of all airports in the given start city
 *@param all_goals a string vector of the iata codes of all airports in the given goal city
 */
void ReadWrite::haversineHelper(const std::vector<std::string> all_starts, const std::vector<std::string> all_goals)
{

    Airport tempair1;
    Airport tempair2;
    std::string flight_path;
    std::vector<std::string> flight_vec;
    std::map<double, std::string> all_paths;

    // find route for every airport within the start city]
    for (int i = 0; i < all_starts.size(); i++)
    {
        std::cout << "  >> start number: " << all_starts.size() << std::endl;
        std::cout << "  >> goal number: " << all_goals.size() << std::endl;
        std::cout << "  * path " << i + 1 << " *" << std::endl;
        flight_path = Route::findRoute(all_starts[i], all_goals[all_goals.size() - 1]);
        flight_vec = Route::stringToVec(flight_path);

        // haversine
        double haversine_distance = 0;

        for (int i = 1; i < flight_vec.size() - 1; i++)
        {
            for (auto const &pair : Airport::AirportMap)
            {
                if (pair.first[0] == flight_vec[i])
                {
                    std::vector<std::string> temp1{pair.first[0], pair.first[1], pair.first[2]};
                    tempair1 = Airport::AirportMap[temp1];
                }
                if (pair.first[0] == flight_vec[i + 1])
                {
                    std::vector<std::string> temp2{pair.first[0], pair.first[1], pair.first[2]};
                    tempair2 = Airport::AirportMap[temp2];
                }
            }
            double latitude1 = stod(tempair1.getLatitude());
            double latitude2 = stod(tempair2.getLatitude());
            double longitude1 = stod(tempair1.getLongitude());
            double longitude2 = stod(tempair2.getLongitude());

            double distance = haversine(latitude1, longitude1, latitude2, longitude2);
            haversine_distance = haversine_distance + distance;
        }
        all_paths.insert(std::pair<double, std::string>(haversine_distance, flight_path));
        std::cout << "      >>>> haversine distance: " << haversine_distance << " km" << std::endl;
        std::cout << std::endl;
    }

    outputFileWriter(all_paths.begin()->second);
}

/**
 * @brief Writes the flight path to an output file.
 * @param flight_path The flight path to be written.
 */
void ReadWrite::outputFileWriter(const std::string flight_path)
{

    std::string file = "//Users/admin/Library/CloudStorage/OneDrive-AshesiUniversity/Ashesi University/ashesi year 2/sem2/intermediate computer programming/AeroNav/flight_plan.txt";
    std::ofstream outputStream(file);
    std::cout << std::endl;
    std::cout << "> Writing to output file..." << std::endl;

    std::vector<std::string> output;
    output = Route::stringToVec(flight_path);

    // print to file
    outputStream << " >> Flight Plan <<" << std::endl
                 << std::endl;
    for (int i = 1; i < output.size() - 1; i++)
    {
        for (auto &pair : Route::AirlineRoutesMap)
        {
            if (pair.first[1] == output[i])
            {
                std::string airline = pair.first[0];
                std::string stops = pair.first[2];
                outputStream << "     " << i << ". flight " << airline << " from " << output[i] << " to " << output[i + 1] << " " << stops << " stops" << std::endl;
                break;
            }
        }
    }
    outputStream << "Total Flights: " << output.size() - 2 << std::endl;
    outputStream << "Total Additional Stops: "
                 << "1" << std::endl;
    std::cout << "> Written to file!" << std::endl;
}

// int main()
// {

//     //    cout << "start city and country: " << ReadWrite::getStartCity() << ", " << ReadWrite::getStartCountry() << endl;
//     //
//     //    cout << "destination city and country: " << ReadWrite::getDestination_City() << ", " << ReadWrite::getDestination_Country() << endl;
//     //
//     //    cout << "starting search ..." << endl;

//     std::string airport_filename = "//Users/admin/Library/CloudStorage/OneDrive-AshesiUniversity/Ashesi University/ashesi year 2/sem2/intermediate computer programming/AeroNav/Airports/airports.csv";

//     std::string airRoute_filename = "//Users/admin/Library/CloudStorage/OneDrive-AshesiUniversity/Ashesi University/ashesi year 2/sem2/intermediate computer programming/AeroNav/Routes/routes.csv";

//     std::map<std::vector<std::string>, Airport> myAirportMap;
//     myAirportMap = Airport::AirportFileReader(airport_filename);
//     //    Airport::printMap(myAirportMap);

//     std::map<std::string, std::vector<std::string>> myAirRoutesMap;
//     myAirRoutesMap = Route::AirportRouteReader(airRoute_filename);
//     //    Route::printMap(myAirRoutesMap);

//     std::map<std::vector<std::string>, std::vector<std::string>> myAirlineForRouteMap;
//     myAirlineForRouteMap = Route::AirlineRouteReader(airRoute_filename);
//     //    Route::printMap(myAirlineForRouteMap);

//     //    vector<string> test;
//     //    test.emplace_back("AER");
//     //    test.emplace_back("EGO");
//     //    test.emplace_back("NBC");
//     //
//     //    for(int i=0; i<=test.size(); i++){
//     //        for(auto &pair : myAirlineForRouteMap){
//     //            if(pair.first[1] == test[i]){
//     //                cout << pair.first[0] << endl;
//     //            }
//     //        }
//     //    }
//     ReadWrite::inputFileReader("/Users/admin/Library/CloudStorage/OneDrive-AshesiUniversity/Ashesi University/ashesi year 2/sem2/intermediate computer programming/AeroNav/ReadWrite/myfile");
// }
