#include <iostream>
#include <stdio.h>
#include<fstream>

using namespace std;
string file_name;
short number_of_people = 0;
int *seats_available_ = new int[number_of_people];

bool filemanager(string file_name_);

short count_people(string line);

void seats_available(string line);


int main(int argc, char *argv[]) {
    FILE *cp;
    if (argv[1] != NULL) {
        file_name = argv[1];
        filemanager(file_name);
//        printf("-> File name : %s\n", file_name.c_str());
//        cp = fopen(file_name.c_str(), "r");
//        if (cp == NULL) {
//            cout << "-> File not found\n";
//            return 0;
//        } else {
//        }
    } else {
        cout << "working on default file \" cars.txt\" ";
        cp = fopen("cars.txt", "r");
        if (cp == NULL) {
            cout << "Error (#Code 2): File not found.";
            return 0;
        } else {
            filemanager("cars.txt");
//            cout << "Error (#Code 3): File not found.";
        }
    }

    return 0;
}

bool filemanager(string file_name_) {
    cout << endl;
    ifstream file(file_name_);
    if (file.is_open()) {
        string line;
        bool first_line_ = true;
        while (getline(file, line)) {
            if (first_line_) {
                number_of_people = count_people(line);
                first_line_ = false;
            } else {
                seats_available(line);
            }
        }
        file.close();
    } else {
        cout << "Error (#Code 1): File not found.";
        return false;
    }
    return true;
}

short count_people(string line) {
    int count = 0;
    for (int i = 0; i < line.length(); i++) {
        if (line[i] >= '0' && line[i] <= '9') {
            count += (line[i]) - 48;
        }
    }
//    cout << "No of people : " << count << endl;
    return count;
}

void seats_available(string line) {
    int No_Cars = 0;
    for (int i = 0; i < line.length(); i++) {
        if (line[i] >= '0' && line[i] <= '9') {
            seats_available_[No_Cars++] = (line[i]) - 48;
        }
    }
    //sort the array in descending order
    for (int i = 0; i < No_Cars; i++) {
        for (int j = i + 1; j < No_Cars; j++) {
            if (seats_available_[i] < seats_available_[j]) {
                int temp = seats_available_[i];
                seats_available_[i] = seats_available_[j];
                seats_available_[j] = temp;
            }
        }
    }

//    cout <<"->Seats available : ";
//    for (int i = 0; i < No_Cars; i++) {
//        cout << seats_available_[i] << " ";
//    }
    int seats_required = number_of_people;
    int cars_used = 0;
    for (int i = 0; i < No_Cars; i++) {
        if (seats_required > 0) {
            seats_required -= seats_available_[i];
            cars_used++;
        }
    }
    if (seats_required <= 0) {
        cout << "Cars required : " << cars_used << endl;
    } else {
        cout << "Cars required : " << cars_used + 1 << endl;
    }


}