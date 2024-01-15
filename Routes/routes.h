//  Routes.h
//  Created by Omar Basheer on 11/20/22.
#ifndef ROUTES_H
#define ROUTES_H

#include <map>
#include <vector>
#include <deque>
#include <fstream>
#include <sstream>
#include <iostream>

class Route {

private:
    std::string Source_AirportCode;
    std::string Destination_AirportCode;
    std::string AirlineCode;
    std::string Stops;

public:
    Route();
    Route(std::string Destination_AirportCode, std::string airlineCode);

    const std::string getSA_Code() const;
    const std::string getDA_Code() const;
    const std::string getAirline_Code() const;
    const std::string getStops() const;
    const std::string toString() const;

    static std::map<std::string, std::vector<std::string>> AirportRoutesMap;
    static std::map<std::vector<std::string>, std::vector<std::string>> AirlineRoutesMap;

    static std::vector<std::string> stringToVec(std::string vector_string);
    static std::string const vecToString(std::vector<std::string> string_vector);

    static std::map<std::string, std::vector<std::string>> AirportRouteReader(const std::string &filename);
    static std::map<std::vector<std::string>, std::vector<std::string>> AirlineRouteReader(const std::string &filename);

    static void printMap(std::map<std::string, std::vector<std::string>> thisMap);
    static void printMap(std::map<std::vector<std::string>, std::vector<std::string>> thisMap);

    static bool contains(std::deque<std::string> deq, std::string value);
    static bool contains(std::vector<std::string> vec, std::string value);

    static std::string findRoute(std::string start_airport, std::string goal_airport);
    static std::string solution_path(std::map<std::string, std::string> solution_map, std::string child);
};

#endif // ROUTES_H
