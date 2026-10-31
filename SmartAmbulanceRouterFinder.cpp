#include <iostream>
#include <string>
#include <climits>
#include <limits>
using namespace std;

const int MAX_LOCATIONS = 20;
const int INF = INT_MAX / 4;

class AmbulanceRouteFinder {
private:
    string locations[MAX_LOCATIONS];
    int road[MAX_LOCATIONS][MAX_LOCATIONS];
    bool hospital[MAX_LOCATIONS];
    int locationCount;

    // Linear search to find a location by name
    int findLocation(string name) {
        for (int i = 0; i < locationCount; i++) {
            if (locations[i] == name) {
                return i;
            }
        }
        return -1;
    }

    // Dijkstra's algorithm for shortest distances
    void dijkstra(int source, int dist[], int parent[]) {
        bool visited[MAX_LOCATIONS];

        for (int i = 0; i < locationCount; i++) {
            dist[i] = INF;
            parent[i] = -1;
            visited[i] = false;
        }

        dist[source] = 0;

        for (int count = 0; count < locationCount; count++) {
            int u = -1;
            int minimum = INF;

            // Select the unvisited location with minimum distance
            for (int i = 0; i < locationCount; i++) {
                if (!visited[i] && dist[i] < minimum) {
                    minimum = dist[i];
                    u = i;
                }
            }

            if (u == -1) {
                break;
            }

            visited[u] = true;

            // Update distances of neighbouring locations
            for (int v = 0; v < locationCount; v++) {
                if (road[u][v] > 0 && !visited[v]) {
                    if (dist[u] + road[u][v] < dist[v]) {
                        dist[v] = dist[u] + road[u][v];
                        parent[v] = u;
                    }
                }
            }
        }
    }

    // Display the route using the parent array
    void displayRoute(int source, int destination, int parent[]) {
        int path[MAX_LOCATIONS];
        int length = 0;
        int current = destination;

        while (current != -1 && length < MAX_LOCATIONS) {
            path[length++] = current;

            if (current == source) {
                break;
            }

            current = parent[current];
        }

        if (length == 0 || path[length - 1] != source) {
            cout << "No route is available.\n";
            return;
        }

        cout << "Route: ";

        for (int i = length - 1; i >= 0; i--) {
            cout << locations[path[i]];

            if (i > 0) {
                cout << " -> ";
            }
        }

        cout << endl;
    }

    // Read a location name and search for it
    int askForLocation(string message) {
        string name;
        cout << message;
        getline(cin, name);

        int index = findLocation(name);

        if (index == -1) {
            cout << "Location not found. Use the exact name shown in the list.\n";
        }

        return index;
    }

    // Display locations in alphabetical order using bubble sort
    void sortLocations() {
        string sorted[MAX_LOCATIONS];

        for (int i = 0; i < locationCount; i++) {
            sorted[i] = locations[i];
        }

        // Bubble sort on a copy; the graph's original order stays unchanged
        for (int i = 0; i < locationCount - 1; i++) {
            for (int j = 0; j < locationCount - i - 1; j++) {
                if (sorted[j] > sorted[j + 1]) {
                    string temp = sorted[j];
                    sorted[j] = sorted[j + 1];
                    sorted[j + 1] = temp;
                }
            }
        }

        cout << "\nLocations in alphabetical order:\n";

        for (int i = 0; i < locationCount; i++) {
            cout << i + 1 << ". " << sorted[i] << endl;
        }
    }

    // Add a sample road between two locations
    void connect(int a, int b, int distance) {
        road[a][b] = distance;
        road[b][a] = distance;
    }

    // Create sample locations and roads
    void initializeData() {
        locationCount = 7;

        locations[0] = "Sangamner";
        locations[1] = "Akole";
        locations[2] = "Nashik";
        locations[3] = "Shirdi";
        locations[4] = "Rahata";
        locations[5] = "Civil Hospital";
        locations[6] = "Rural Hospital";

        for (int i = 0; i < MAX_LOCATIONS; i++) {
            hospital[i] = false;

            for (int j = 0; j < MAX_LOCATIONS; j++) {
                road[i][j] = 0;
            }
        }

        hospital[5] = true;
        hospital[6] = true;

        // Sample road distances in kilometres
        connect(0, 1, 25);
        connect(0, 2, 65);
        connect(0, 3, 45);
        connect(0, 4, 35);
        connect(1, 2, 90);
        connect(3, 4, 15);
        connect(2, 5, 5);
        connect(4, 6, 10);
        connect(3, 6, 25);
    }

public:
    // Constructor
    AmbulanceRouteFinder() {
        locationCount = 0;

        for (int i = 0; i < MAX_LOCATIONS; i++) {
            hospital[i] = false;

            for (int j = 0; j < MAX_LOCATIONS; j++) {
                road[i][j] = 0;
            }
        }

        initializeData();
    }

    // Display all locations
    void displayLocations() {
        cout << "\nAvailable Locations:\n";

        for (int i = 0; i < locationCount; i++) {
            cout << i + 1 << ". " << locations[i];

            if (hospital[i]) {
                cout << " (Hospital)";
            }

            cout << endl;
        }
    }

    // Search for a location using linear search
    void searchLocation() {
        string name;

        cout << "Enter location name: ";
        getline(cin, name);

        int index = findLocation(name);

        if (index == -1) {
            cout << "Location not found.\n";
        } else {
            cout << "Location found: " << locations[index] << endl;

            if (hospital[index]) {
                cout << "This location is a hospital.\n";
            } else {
                cout << "This location is not marked as a hospital.\n";
            }
        }
    }

    // Display the road network
    void displayRoadNetwork() {
        cout << "\nRoad Network (distance in km):\n";

        for (int i = 0; i < locationCount; i++) {
            for (int j = i + 1; j < locationCount; j++) {
                if (road[i][j] > 0) {
                    cout << locations[i] << " <-> "
                         << locations[j] << " : "
                         << road[i][j] << " km\n";
                }
            }
        }
    }

    // Add a new road between existing locations
    void addRoad() {
        if (locationCount < 2) {
            cout << "Not enough locations to create a road.\n";
            return;
        }

        cout << "\nEnter the first location name:\n";
        int a = askForLocation("First location: ");

        if (a == -1) {
            return;
        }

        cout << "Enter the second location name:\n";
        int b = askForLocation("Second location: ");

        if (b == -1) {
            return;
        }

        if (a == b) {
            cout << "A road must connect two different locations.\n";
            return;
        }

        int distance;
        cout << "Enter road distance in kilometres: ";

        if (!(cin >> distance)) {
            cout << "Invalid distance input.\n";
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            return;
        }

        cin.ignore(INT_MAX, '\n');

        if (distance <= 0) {
            cout << "Distance must be greater than zero.\n";
            return;
        }

        if (road[a][b] > 0) {
    cout << "Road already exists between "
         << locations[a] << " and " << locations[b] << ".\n";
    cout << "Existing distance: " << road[a][b] << " km\n";
    cout << "No changes made.\n";
    return;
}

connect(a, b, distance);

cout << "Road added successfully.\n";
    }

    // Find and display the shortest route between two locations
    void findShortestRoute() {
        cout << "\nFind Shortest Route\n";

        int source = askForLocation("Starting location: ");
        if (source == -1) {
            return;
        }

        int destination = askForLocation("Destination: ");
        if (destination == -1) {
            return;
        }

        int dist[MAX_LOCATIONS];
        int parent[MAX_LOCATIONS];

        dijkstra(source, dist, parent);

        if (dist[destination] == INF) {
            cout << "No route exists between these locations.\n";
            return;
        }

        displayRoute(source, destination, parent);
        cout << "Shortest distance: "
             << dist[destination] << " km\n";
    }

    // Find the nearest reachable hospital
    void findNearestHospital() {
        cout << "\nFind Nearest Hospital\n";

        int source = askForLocation("Starting location: ");
        if (source == -1) {
            return;
        }

        int dist[MAX_LOCATIONS];
        int parent[MAX_LOCATIONS];

        dijkstra(source, dist, parent);

        int nearest = -1;
        int minimumDistance = INF;

        for (int i = 0; i < locationCount; i++) {
            if (hospital[i] && dist[i] < minimumDistance) {
                minimumDistance = dist[i];
                nearest = i;
            }
        }

        if (nearest == -1) {
            cout << "No reachable hospital was found.\n";
            return;
        }

        cout << "Nearest hospital: " << locations[nearest] << endl;
        displayRoute(source, nearest, parent);
        cout << "Distance to hospital: "
             << minimumDistance << " km\n";
    }

    // Main menu
    void run() {
        int choice;

        do {
            cout << "\n====================================\n";
            cout << "     SMART AMBULANCE ROUTE FINDER\n";
            cout << "====================================\n";
            cout << "1. Display all locations\n";
            cout << "2. Search for a location\n";
            cout << "3. Display road network\n";
            cout << "4. Add a road\n";
            cout << "5. Find shortest route\n";
            cout << "6. Find nearest hospital\n";
            cout << "7. Sort locations alphabetically\n";
            cout << "8. Exit\n";
            cout << "Enter your choice: ";

            if (!(cin >> choice)) {
                cout << "Please enter a valid menu number.\n";
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                continue;
            }

            cin.ignore(INT_MAX, '\n');

            switch (choice) {
                case 1:
                    displayLocations();
                    break;

                case 2:
                    searchLocation();
                    break;

                case 3:
                    displayRoadNetwork();
                    break;

                case 4:
                    addRoad();
                    break;

                case 5:
                    findShortestRoute();
                    break;

                case 6:
                    findNearestHospital();
                    break;

                case 7:
                    sortLocations();
                    break;

                case 8:
                    cout << "Thank you for using Smart Ambulance Route Finder.\n";
                    break;

                default:
                    cout << "Invalid choice. Please select 1 to 8.\n";
            }

        } while (choice != 8);
    }
};

int main() {
    AmbulanceRouteFinder app;
    app.run();

    return 0;

}

//OUTPUT PS C:\Users\LENOVO> cd "D:\DSA CCE3"
PS D:\DSA CCE3> g++ "SmartAmbulanceRouterFinder.cpp" -o ambulance.exe
C:/msys64/ucrt64/bin/../lib/gcc/x86_64-w64-mingw32/16.2.0/../../../../x86_64-w64-mingw32/bin/ld.exe: cannot open output file ambulance.exe: Permission denied
collect2.exe: error: ld returned 1 exit status
PS D:\DSA CCE3> .\ambulance.exe

====================================
     SMART AMBULANCE ROUTE FINDER
====================================
1. Display all locations
2. Search for a location
3. Display road network
4. Add a road
5. Find shortest route
6. Find nearest hospital
7. Sort locations alphabetically
8. Exit
Enter your choice: 1

Available Locations:
1. Sangamner
2. Akole
3. Nashik
4. Shirdi
5. Rahata
6. Civil Hospital (Hospital)
7. Rural Hospital (Hospital)

====================================
     SMART AMBULANCE ROUTE FINDER
====================================
1. Display all locations
2. Search for a location
3. Display road network
4. Add a road
5. Find shortest route
6. Find nearest hospital
7. Sort locations alphabetically
8. Exit
Enter your choice: 2
Enter location name: Nashik
Location found: Nashik
This location is not marked as a hospital.

====================================
     SMART AMBULANCE ROUTE FINDER
====================================
1. Display all locations
2. Search for a location
3. Display road network
4. Add a road
5. Find shortest route
6. Find nearest hospital
7. Sort locations alphabetically
8. Exit
Enter your choice: 3

Road Network (distance in km):
Sangamner <-> Akole : 25 km
Sangamner <-> Nashik : 65 km
Sangamner <-> Shirdi : 45 km
Sangamner <-> Rahata : 35 km
Akole <-> Nashik : 90 km
Nashik <-> Civil Hospital : 5 km
Shirdi <-> Rahata : 15 km
Shirdi <-> Rural Hospital : 25 km
Rahata <-> Rural Hospital : 10 km

====================================
     SMART AMBULANCE ROUTE FINDER
====================================
1. Display all locations
2. Search for a location
3. Display road network
4. Add a road
5. Find shortest route
6. Find nearest hospital
7. Sort locations alphabetically
8. Exit
Enter your choice: 4

Enter the first location name:
First location: Akole
Enter the second location name:
Second location: Shirdi
Enter road distance in kilometres: 30
Road added successfully.

====================================
     SMART AMBULANCE ROUTE FINDER
====================================
1. Display all locations
2. Search for a location
3. Display road network
4. Add a road
5. Find shortest route
6. Find nearest hospital
7. Sort locations alphabetically
8. Exit
Enter your choice: 5

Find Shortest Route
Starting location: Sangamner
Destination: Civil Hospital
Route: Sangamner -> Nashik -> Civil Hospital
Shortest distance: 70 km

====================================
     SMART AMBULANCE ROUTE FINDER
====================================
1. Display all locations
2. Search for a location
3. Display road network
4. Add a road
5. Find shortest route
6. Find nearest hospital
7. Sort locations alphabetically
8. Exit
Enter your choice: 6

Find Nearest Hospital
Starting location: Sangamner
Nearest hospital: Rural Hospital
Route: Sangamner -> Rahata -> Rural Hospital
Distance to hospital: 45 km

====================================
     SMART AMBULANCE ROUTE FINDER
====================================
1. Display all locations
2. Search for a location
3. Display road network
4. Add a road
5. Find shortest route
6. Find nearest hospital
7. Sort locations alphabetically
8. Exit
Enter your choice: 7

Locations in alphabetical order:
1. Akole
2. Civil Hospital
3. Nashik
4. Rahata
5. Rural Hospital
6. Sangamner
7. Shirdi

====================================
     SMART AMBULANCE ROUTE FINDER
====================================
1. Display all locations
2. Search for a location
3. Display road network
4. Add a road
5. Find shortest route
6. Find nearest hospital
7. Sort locations alphabetically
8. Exit
Enter your choice: 4

Enter the first location name:
First location: Nashik
Enter the second location name:
Second location: Civil Hospital
Enter road distance in kilometres: 20
Road already exists between Nashik and Civil Hospital.
Existing distance: 5 km
No changes made.

====================================
     SMART AMBULANCE ROUTE FINDER
====================================
1. Display all locations
2. Search for a location
3. Display road network
4. Add a road
5. Find shortest route
6. Find nearest hospital
7. Sort locations alphabetically
8. Exit
Enter your choice: 4

Enter the first location name:
First location: Akole
Enter the second location name:
Second location: Shirdi
Enter road distance in kilometres: 0
Distance must be greater than zero.

====================================
     SMART AMBULANCE ROUTE FINDER
====================================
1. Display all locations
2. Search for a location
3. Display road network
4. Add a road
5. Find shortest route
6. Find nearest hospital
7. Sort locations alphabetically
8. Exit
Enter your choice: 4

Enter the first location name:
First location: Akole
Enter the second location name:
Second location: Shirdi
Enter road distance in kilometres: -10
Distance must be greater than zero.

====================================
     SMART AMBULANCE ROUTE FINDER
====================================
1. Display all locations
2. Search for a location
3. Display road network
4. Add a road
5. Find shortest route
6. Find nearest hospital
7. Sort locations alphabetically
8. Exit
Enter your choice: 2
Enter location name: Mumbai
Location not found.

====================================
     SMART AMBULANCE ROUTE FINDER
====================================
1. Display all locations
2. Search for a location
3. Display road network
4. Add a road
5. Find shortest route
6. Find nearest hospital
7. Sort locations alphabetically
8. Exit
Enter your choice: 4

Enter the first location name:
First location: Akole
Enter the second location name:
Second location: Akole
A road must connect two different locations.

====================================
     SMART AMBULANCE ROUTE FINDER
====================================
1. Display all locations
2. Search for a location
3. Display road network
4. Add a road
5. Find shortest route
6. Find nearest hospital
7. Sort locations alphabetically
8. Exit
Enter your choice: 9
Invalid choice. Please select 1 to 8.

====================================
     SMART AMBULANCE ROUTE FINDER
====================================
1. Display all locations
2. Search for a location
3. Display road network
4. Add a road
5. Find shortest route
6. Find nearest hospital
7. Sort locations alphabetically
8. Exit
Enter your choice: 8
Thank you for using Smart Ambulance Route Finder.
PS D:\DSA CCE3> 
