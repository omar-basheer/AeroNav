//  ReadWrite
//  read_write_h.h
//  Created by omar on 11/27/22.

#ifndef READWRITE_H
#define READWRITE_H

#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>



/**
 * @class ReadWrite
 * @brief A class that handles reading and writing operations for flight information.
 *
 * This class provides static methods to read user input file containing start city and country,
 * and destination city and country. It also calculates the haversine distance between airports
 * in a solution path and writes the flight plan to an output file.
 */
class ReadWrite
{
private:
    static std::string StartCity;
    static std::string StartCountry;
    static std::string Destination_City;
    static std::string Destination_Country;

public:
    static std::string getStartCity();
    static std::string getStartCountry();
    static std::string getDestination_City();
    static std::string getDestination_Country();
    static void setStartCity(const std::string city);
    static void setStartCountry(const std::string country);
    static void setDestinationCity(const std::string city);
    static void setDestinationCountry(const std::string country);

    /**
     * Read user input file containing start city and country, and destination city and country
     * @param input_filename  the file name of the users input file
     */
    static void inputFileReader(const std::string &input_filename);

    /**
     * Calculates haversine distance between airports in a solution path and accumulates the values
     * to obtain the total distance between the start and goal airports given a particular solution path.
     * Passes solution path with lowest distance to outputFileWriter for file writing
     * @param all_starts a string vector of the iata codes of all airports in the given start city
     * @param all_goals a string vector of the iata codes of all airports in the given goal city
     */
    static void haversineHelper(const std::vector<std::string> all_starts, const std::vector<std::string> all_goals);

    /**
     * Writes the flight plan to an output file
     * @param flight_path the flight path to be written to the output file
     */
    static void outputFileWriter(const std::string flight_path);
};

#endif // READWRITE_H
