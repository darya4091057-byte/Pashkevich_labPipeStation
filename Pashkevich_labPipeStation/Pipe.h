#pragma once
#include <string>
#include <fstream>
using namespace std;

class Pipe {
    string name;
    int diameter;
    double lenght;
    double thickness;
    bool repair;
};

void NewPipe(Pipe& p);
void PrintPipe(const Pipe& p);
void EditPipe(Pipe& p);
void SavePipe(ofstream& file, const Pipe& p);
void LoadPipe(ifstream& file, Pipe& p);