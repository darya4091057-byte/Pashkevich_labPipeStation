#pragma once
#include <string>
#include <fstream>
using namespace std;

struct Station {
    string name;
    int total;
    int working;
    int classNum;
};

void NewStation(Station& s);
void PrintStation(const Station& s);
void EditStation(Station& s);
void SaveStation(ofstream& file, const Station& s);
void LoadStation(ifstream& file, Station& s);