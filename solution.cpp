/*
*Loudcloud - Technical Exam
*Parking Lot Problem 
*Code by: Amanda Lim
*/

#include <bits/stdc++.h>
using namespace std;
#define endl "\n" // just a small optimization

int main()
{
    string input_str;
    int parking_size;
    
    while (input_str != "create_parking_lot")
        cin >> input_str;

    cin >> parking_size;
    cout << "Created a parking lot with " << parking_size << " slots" << endl;

    priority_queue <int, vector <int>, greater <int>> curr_open_slots;
    for (int i = 1; i <= parking_size; i++)
        curr_open_slots.push(i);

    vector <pair <string, string>> parking_lot (parking_size);
    map <string, int> where_they_parked;
    map <string, vector <pair <int, string>>> where_color_is_parked; // Note: could have used a linked list, but I'm not sure whether the output should be ordered; I didn't ask anymore since I think having an ordered output looks better and implementing a linked list is a bit complicated

    string license_plate, color;
    int parking_slot;

    while (cin >> input_str) { // Note: assumes correct input for all the commands and assumes no cars with same license plate
        if (input_str == "park") {
            cin >> license_plate >> color;

            if (curr_open_slots.size() >= 1) {
                parking_slot = curr_open_slots.top();
                curr_open_slots.pop();

                parking_lot[parking_slot - 1] = {license_plate, color};
                where_they_parked[license_plate] = parking_slot;
                where_color_is_parked[color].push_back({parking_slot, license_plate});

                cout << "Allocated slot number: " << parking_slot << endl;
                
            } else
                cout << "Sorry, parking lot is full" << endl;

        } else if (input_str == "leave") {
            cin >> parking_slot;
            license_plate = parking_lot[parking_slot - 1].first;

            curr_open_slots.push(parking_slot);
            where_they_parked.erase(license_plate);
            parking_lot[parking_slot - 1] = {"", ""};
            // did not delete from "where_color_is_parked" due to the unnecessary O(N) time complexity; this will be handled in the other part of the code anyway
            // problem: space complexity

            cout << "Slot number " << parking_slot << " is free" << endl;

        } else if (input_str == "status") {
            cout << endl;

            cout << "Slot No. | Plate No | Colour" << endl;

            for (int i = 0; i < parking_size; i++)
                if ((parking_lot[i].first != "") || (parking_lot[i].second != ""))
                    cout << i + 1 << " | " << parking_lot[i].first << " | " << parking_lot[i].second << endl;

            cout << endl;
            
        } else if (input_str == "plate_numbers_for_cars_with_colour") {
            cin >> color;

            bool first = true;
            set <int> printed;
            for (auto car : where_color_is_parked[color]) {
                if (printed.find(car.first) != printed.end())
                    continue;

                if ((parking_lot[car.first - 1].first == car.second) && (parking_lot[car.first - 1].second == color)) {
                    if (first) {
                        cout << car.second;
                        first = false;
                    } else
                        cout << ", " << car.second;
                    
                    printed.insert(car.first);
                }
            }

            if (first) {
                cout << "No cars with that color"; // Note: No instructions as to what to output, I just assumed the same output as the license plate output
            }

            cout << endl;

        } else if (input_str == "slot_numbers_for_cars_with_colour") {
            cin >> color;

            bool first = true;
            set <int> printed;
            for (auto car : where_color_is_parked[color]) {
                if (printed.find(car.first) != printed.end())
                    continue;
                
                if ((parking_lot[car.first - 1].first == car.second) && (parking_lot[car.first - 1].second == color)) {
                    if (first) {
                        cout << car.first;
                        first = false;
                    } else
                        cout << ", " << car.first;

                    printed.insert(car.first);
                }
            }

            if (first) {
                cout << "Not found"; // Note: Again, no instructions as to what to output, I just assumed the same output as the license plate output
            }

            cout << endl;

        } else if (input_str == "slot_number_for_registration_number") {
            cin >> license_plate;

            if (where_they_parked.find(license_plate) != where_they_parked.end())
                cout << where_they_parked[license_plate] << endl;
            else
                cout << "Not found" << endl;
            
        } else {
            cout << "Unrecognized command" << endl;
        }
    }
    
    return 0;
}