//  Airports
//  Created by Omar Basheer on 11/19/22.

#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include "airports.h"

/**
 * Default constructor for the Airport class.
 * Initializes all member variables to empty strings.
 */
Airport::Airport()
{
    this->AirportName = "";
    this->AirportCity = "";
    this->Country = "";
    this->IATA_Code = "";
    this->Latitude = "";
    this->Longitude = "";
}

/**
 * @brief Constructor for the Airport class.
 * 
 * @param airportName The name of the airport.
 * @param airportCity The city where the airport is located.
 * @param country The country where the airport is located.
 * @param iataCode The IATA code of the airport.
 * @param latitude The latitude coordinate of the airport.
 * @param longitude The longitude coordinate of the airport.
 */
Airport::Airport(std::string airportName, std::string airportCity, std::string country, std::string iataCode, std::string latitude, std::string longitude)
{
    this->AirportName = airportName;
    this->AirportCity = airportCity;
    this->Country = country;
    this->IATA_Code = iataCode;
    this->Latitude = latitude;
    this->Longitude = longitude;
}


/**
 * @brief Returns the name of the airport.
 * 
 * @return std::string The name of the airport.
 */
const std::string Airport::getAirportName() const
{
    return AirportName;
}

/**
 * @brief Returns the airport city.
 * 
 * @return The airport city as a std::string.
 */
const std::string Airport::getAirportCity() const
{
    return AirportCity;
}

/**
 * @brief Get the country of the airport.
 *
 * @return The country of the airport as a string.
 */
const std::string Airport::getCountry() const
{
    return Country;
}

/**
 * @brief Get the IATA code of the airport.
 *
 * @return The IATA code as a string.
 */
const std::string Airport::getIataCode() const
{
    return IATA_Code;
}

/**
 * @brief Gets the latitude of the airport.
 *
 * @return The latitude of the airport as a string.
 */
const std::string Airport::getLatitude() const
{
    return Latitude;
}

/**
 * @brief Get the longitude of the airport.
 *
 * @return The longitude of the airport as a string.
 */
const std::string Airport::getLongitude() const
{
    return Longitude;
}

/**
 * @brief Converts the airport information to a string representation.
 *
 * @return A string representation of the airport information.
 */
const std::string Airport::toString() const
{
    return "Airport - [" + getAirportName() + ", " + getAirportCity() + ", " + getCountry() + ", " + getIataCode() + ", " + getLatitude() + ", " + getLongitude() + "]";
}

/**
 * Converts a vector of strings to a string representation.
 *
 * @param string_vector The vector of strings to be converted.
 * @return The string representation of the vector.
 */
std::string Airport::vecToString(const std::vector<std::string> string_vector)
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
    stream << "]";
    return stream.str();
}

/**
 * @brief A map that associates a vector of strings with an Airport object.
 * 
 * The keys of the map are vectors of strings, and the values are Airport objects.
 * This map allows efficient lookup of an Airport based on a vector of strings.
 */
std::map<std::vector<std::string>, Airport> Airport::AirportMap;

/**
 * Reads airport data from a file and creates a map of airports.
 * The file should be in CSV format with the following columns:
 * 1. Airport ID
 * 2. Name
 * 3. City
 * 4. Country
 * 5. IATA code
 * 6. Latitude
 * 7. Longitude
 *
 * @param filename The name of the file to read the airport data from.
 * @return A map of airports, where the key is a vector of strings containing the IATA code, city, and country,
 *         and the value is an Airport object containing the airport details.
 */
std::map<std::vector<std::string>, Airport> Airport::AirportFileReader(const std::string &filename)
{
    std::fstream inputStream;
    inputStream.open(filename);

    if (inputStream)
    {
        // cout << "> file opened" << endl;
        std::vector<std::string> splitline;
        std::string streamline, streamword, temp;

        while (getline(inputStream, streamline))
        {

            splitline.clear();
            std::stringstream line_of(streamline);
            // cout << "  >> got streamline" << endl;
            // cout << "   >> streamline: " << streamline << endl;

            while (getline(line_of, streamword, ','))
            {
                splitline.push_back(streamword);
                // cout << "   >> got streamword: " << streamword << endl;
            }

            if (!(splitline[4] == "\\N"))
            {
                std::vector<std::string> airportKey;
                airportKey.emplace_back(splitline[4]);
                airportKey.emplace_back(splitline[2]);
                airportKey.emplace_back(splitline[3]);
                // std::cout << vecToString(airportKey);

                Airport airport = Airport(splitline[1], splitline[2], splitline[3], splitline[4],
                                          splitline[6], splitline[7]);
                // std::cout << airport.toString() << std::endl;
                // std::cout << std::endl;
                AirportMap.insert(std::pair<std::vector<std::string>, Airport>(airportKey, airport));
            }
        }
        inputStream.close();
        std::cout << "> Airports map created..." << std::endl;
    }

    else
    {
        std::cout << "error opening/reading data file: check that the input file is in right directory and the given file name matches" << std::endl;
    }

    return AirportMap;
}

/**
 * Prints the contents of a map of airports.
 *
 * @param thisMap The map of airports to be printed.
 */
void Airport::printMap(const std::map<std::vector<std::string>, Airport> thisMap)
{
    for (auto const &pair : thisMap)
    {
        std::cout << vecToString(pair.first) << " >> " << pair.second.toString() << std::endl;
    }
}


// int main()
// {
//     std::map<std::vector<std::string>, Airport> myAirportMap;

//     std::string filename = "//Users/admin/Library/CloudStorage/OneDrive-AshesiUniversity/Ashesi University/ashesi year 2/sem2/intermediate computer programming/Airliner_/Airports/airports.csv";
//     myAirportMap = Airport::AirportFileReader(filename);
//     Airport::printMap(myAirportMap);
// }
