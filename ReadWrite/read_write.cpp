//  ReadWrite
//  Created by Omar Basheer on 11/27/22.

#include <vector>
#include <sstream>
#include <fstream>
#include <cstring>
#include <iostream>
#include <algorithm>
#include "airports.h"


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
    static const std::string getStartCity()
    {
        return StartCity;
    }

    static const std::string getStartCountry()
    {
        return StartCountry;
    }

    static const std::string getDestination_City()
    {
        return Destination_City;
    }

    static const std::string getDestination_Country()
    {
        return Destination_Country;
    }

    static void setStartCity(std::string city)
    {
        StartCity = city;
    }

    static void setStartCountry(std::string country)
    {
        StartCountry = country;
    }

    static void setDestinationCity(std::string city)
    {
        Destination_City = city;
    }

    static void setDestinationCountry(std::string country)
    {
        Destination_Country = country;
    }

    /**
     * Read user input file containing start city and country, and destination city and country
     * @param input_filename  the file name of the users input file
     */
    static void inputFileReader(const std::string &input_filename)
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
        cout << endl;
        cout << "> Starting search..." << endl;

        haversineHelper(all_starts, all_goals);
    }

    /**
     * Calculates haversine distance between airports in a solution path and accumulates the values to obtain the total distance between the start and goal airports given a particular solution path. Passes solution path with lowest distance to outputFileWriter for file writing
     *@param all_starts a string vector of the iata codes of all airports in the given start city
     *@param all_goals a string vector of the iata codes of all airports in the given goal city
     */
    static void haversineHelper(vector<string> all_starts, vector<string> all_goals)
    {

        Airport tempair1;
        Airport tempair2;
        string flight_path;
        vector<string> flight_vec;
        map<double, string> all_paths;

        // find route for every airport within the start city]
        for (int i = 0; i < all_starts.size(); i++)
        {
            cout << "  >> start number: " << all_starts.size() << endl;
            cout << "  >> goal number: " << all_goals.size() << endl;
            cout << "  * path " << i + 1 << " *" << endl;
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
                        vector<string> temp1{pair.first[0], pair.first[1], pair.first[2]};
                        tempair1 = Airport::AirportMap[temp1];
                    }
                    if (pair.first[0] == flight_vec[i + 1])
                    {
                        vector<string> temp2{pair.first[0], pair.first[1], pair.first[2]};
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
            all_paths.insert(pair<double, string>(haversine_distance, flight_path));
            cout << "      >>>> haversine distance: " << haversine_distance << " km" << endl;
            cout << endl;
        }

        outputFileWriter(all_paths.begin()->second);
    }

    static void outputFileWriter(string flight_path)
    {

        string file = "/Users/admin/Desktop/xCode/Airliner/AirlinerC++/AirlinerC++/flight plan";
        //        string file = "flight plan";
        ofstream outputStream(file);
        cout << endl;
        cout << "> Writing to output file..." << endl;

        vector<string> output;
        output = Route::stringToVec(flight_path);

        // print to file
        outputStream << " >> Flight Plan <<" << endl
                     << endl;
        for (int i = 1; i < output.size() - 1; i++)
        {
            for (auto &pair : Route::AirlineRoutesMap)
            {
                //                cout<<"test2"<<endl;
                if (pair.first[1] == output[i])
                {
                    //                    cout<<pair.first[0] << " ";
                    string airline = pair.first[0];
                    string stops = pair.first[2];
                    outputStream << "     " << i << ". flight " << airline << " from " << output[i] << " to " << output[i + 1] << " " << stops << " stops" << endl;
                    break;
                }
            }
        }
        outputStream << "Total Flights: " << output.size() - 2 << endl;
        outputStream << "Total Additional Stops: "
                     << "1" << endl;
        cout << "> Written to file!" << endl;
    }
};

string ReadWrite::StartCity;
string ReadWrite::StartCountry;
string ReadWrite::Destination_City;
string ReadWrite::Destination_Country;

int main()
{

    //    cout << "start city and country: " << ReadWrite::getStartCity() << ", " << ReadWrite::getStartCountry() << endl;
    //
    //    cout << "destination city and country: " << ReadWrite::getDestination_City() << ", " << ReadWrite::getDestination_Country() << endl;
    //
    //    cout << "starting search ..." << endl;

    string airport_filename = "//Users/admin/Desktop/xCode/Airliner/AirlinerC++/AirlinerC++/Airports/airports.csv";

    string airRoute_filename = "/Users/admin/Library/CloudStorage/OneDrive-AshesiUniversity/Ashesi University/ashesi year 2/sem2/intermediate computer programming/Airliner/routes.csv";

    map<vector<string>, Airport> myAirportMap;
    myAirportMap = Airport::AirportFileReader(airport_filename);
    //    Airport::printMap(myAirportMap);

    map<string, vector<string>> myAirRoutesMap;
    myAirRoutesMap = Route::AirportRouteReader(airRoute_filename);
    //    Route::printMap(myAirRoutesMap);

    map<vector<string>, vector<string>> myAirlineForRouteMap;
    myAirlineForRouteMap = Route::AirlineRouteReader(airRoute_filename);
    //    Route::printMap(myAirlineForRouteMap);

    //    vector<string> test;
    //    test.emplace_back("AER");
    //    test.emplace_back("EGO");
    //    test.emplace_back("NBC");
    //
    //    for(int i=0; i<=test.size(); i++){
    //        for(auto &pair : myAirlineForRouteMap){
    //            if(pair.first[1] == test[i]){
    //                cout << pair.first[0] << endl;
    //            }
    //        }
    //    }
    ReadWrite::inputFileReader("/Users/admin/Desktop/xCode/Airliner/AirlinerC++/AirlinerC++/ReadWrite/myfile");
}
