#include "Pipe.h"
#include "Input.h"
#include <iostream>
using namespace std;

void NewPipe(Pipe& p)
{
    cout << "Название: ";
    getline(cin >> ws, p.name);
    cout << "Диаметр: ";
    p.diameter = getInt();
    cout << "Длина: ";
    p.lenght = getDouble();
    cout << "Толщина: ";
    p.thickness = getDouble();
    cout << "Труба в ремонте? (0 - нет, 1 - да): ";
    p.repair = getInt();
}

void PrintPipe(const Pipe& p)
{
    cout << "Труба: " << p.name << ", " << p.diameter << " мм, "
        << p.lenght << " км, " << p.thickness << " мм "
        << (p.repair ? "в ремонте" : "не в ремонте") << "\n";
}

void EditPipe(Pipe& p)
{
    p.repair = !p.repair;
    cout << "Труба теперь: " << (p.repair ? "в ремонте" : "не в ремонте") << "\n";
}

void SavePipe(ofstream& file, const Pipe& p)
{
    file << p.name << "\n";
    file << p.diameter << "\n";
    file << p.lenght << "\n";
    file << p.thickness << "\n";
    if (p.repair) file << "в ремонте\n";
    else file << "не в ремонте\n";
}

void LoadPipe(ifstream& file, Pipe& p)
{
    getline(file, p.name);
    file >> p.diameter;
    file >> p.lenght;
    file >> p.thickness;
    file.ignore();
    string status;
    getline(file, status);
    if (status == "в ремонте") p.repair = true;
    else p.repair = false;
}