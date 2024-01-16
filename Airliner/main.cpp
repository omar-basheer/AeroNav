//  Created by omar on 11/19/22.

#include <map>
#include <vector>
#include <iostream>
#include "../Routes/routes.h"
#include "../Airports/airports.h"
#include "../ReadWrite/read_write.h"


/**
 * @brief The entry point of the program.
 * @return int The exit status of the program.
 */
int main(){
    
    std::string airport_filename = "//Users/admin/Library/CloudStorage/OneDrive-AshesiUniversity/Ashesi University/ashesi year 2/sem2/intermediate computer programming/AeroNav/Airports/airports.csv";
    
    std::string airRoute_filename = "//Users/admin/Library/CloudStorage/OneDrive-AshesiUniversity/Ashesi University/ashesi year 2/sem2/intermediate computer programming/AeroNav/Routes/routes.csv";
    
    std::map<std::vector<std::string>, Airport> airport_map;
    airport_map = Airport::AirportFileReader(airport_filename);
    // Airport::printMap(airport_map);
    
    std::map<std::string, std::vector<std::string>> airport_routemap;
    airport_routemap = Route::AirportRouteReader(airRoute_filename);
    // Route::printMap(airport_map);
    
    std::map<std::vector<std::string>, std::vector<std::string>> airline_routemap;
    airline_routemap = Route::AirlineRouteReader(airRoute_filename);
    // Route::printMap(airport_map);
    
    ReadWrite::inputFileReader("//Users/admin/Library/CloudStorage/OneDrive-AshesiUniversity/Ashesi University/ashesi year 2/sem2/intermediate computer programming/AeroNav/ReadWrite/myfile.txt");
    
}
