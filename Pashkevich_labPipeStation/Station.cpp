#include "Station.h"
#include "Input.h"
#include <iostream>
using namespace std;

void NewStation(Station& s)
{
    cout << "Название: ";
    getline(cin >> ws, s.name);
    cout << "Всего цехов: ";
    s.total = getInt();
    cout << "Цехов в работе: ";
    s.working = getInt();
    cout << "Класс станции: ";
    s.classNum = getInt();
}

void PrintStation(const Station& s)
{
    cout << "КС: " << s.name << ", цехов " << s.total
        << ", работают " << s.working
        << ", класс " << s.classNum << "\n";
}

void EditStation(Station& s)
{
    cout << "1-запустить цех: 2-остановить цех: ";
    int c = getInt();
    if (c == 1 && s.working < s.total) s.working++;
    if (c == 2 && s.working > 0) s.working--;
    cout << "В работе: " << s.working << " из " << s.total << "\n";
}

void SaveStation(ofstream& file, const Station& s)
{
    file << s.name << "\n";
    file << s.total << "\n";
    file << s.working << "\n";
    file << s.classNum << "\n";
}

void LoadStation(ifstream& file, Station& s)
{
    getline(file, s.name);
    file >> s.total;
    file >> s.working;
    file >> s.classNum;
    file.ignore();
}