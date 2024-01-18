# AeroNav
C++ application designed to assist users in planning and visualizing air travel routes. This project leverages airport and route data to help users determine the optimal flight paths between cities

It enables users to input their departure and destination cities, providing detailed flight plans, including distance calculations.

### Key Features:
* Flight Planning: Plan efficient routes based on airport and route data.
* Haversine Distance Calculation: Compute accurate distances between airports using the Haversine formula.

### Installation
1. Clone the Repository:
```bash
git clone https://github.com/your-username/AeroNav.git
cd AeroNav
```

2. Compile the Code:
```bash
g++ -std=c++14 -o AeroNav read_write.cpp -I.
```
Note: Replace [other source files] with the actual names of your project's source files.

3. Run the Executable:
```bash
./AeroNav
```

### Usage
1. Input File:
Prepare an input file containing start city, start country, destination city, and destination country. Each value should be separated by a comma and space (, ).
Example input file (e.g., input.txt):
```sql
New York, USA
London, UK
```
2. Run AeroNav:
Execute the compiled AeroNav executable with the input file as a parameter.
```bash
./AeroNav input.txt
```

3. View Output:
AeroNav will read the input file, find the optimal flight path, calculate Haversine distances, and generate an output file (flight_plan.txt) with detailed flight information.

5. Explore Flight Plan:
Open flight_plan.txt to view the generated flight plan, including airline information and total distance.
