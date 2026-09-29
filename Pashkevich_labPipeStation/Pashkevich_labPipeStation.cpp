// Pashkevich_labPipeStation.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
using namespace std;

struct Pipe
{
    string name;
    int diameter;
    double lenght;
    double thickness;
    bool repair;
};

struct Station
{
    string name;
    int total;
    int working;
    int classNum;
};

Pipe myPipe;
Station myStation;
bool flagPipe = false;
bool flagStation = false;

int getInt()
{
    int x;
    while (true) {
        cin >> x;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ошибка! Введите число: ";
        }
        else {
            cin.ignore(10000, '\n');
            return x;
        }
    }

}

int getDouble()
{
    int x;
    while (true) {
        cin >> x;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ошибка! Введите число: ";
        }
        else {
            cin.ignore(10000, '\n');
            return x;
        }
    }

}

string getString()
{
    string s;
    getline(cin, s);
    return s;
}

void NewPipe(Pipe& p)
{
    cout << "Название: ";
    cin >> p.name;
    cout << "Диаметр: ";
    p.diameter = getInt();
    cout << "Длина: ";
    p.lenght = getDouble();
    cout << "Толщина: ";
    p.thickness = getDouble();
    cout << "Труба в ремонте? (0 - нет, 1 - да):";
    p.repair = getInt();
}

void PrintPipe(const Pipe& p)
{
    cout << "Труба: " << p.name << ", " << p.diameter << " мм, " << p.lenght << " км, " << p.thickness << " мм " << (p.repair ? "в ремонте" : "не в ремонте") << "\n";
}

void EditPipe(Pipe& p)
{
    p.repair = !p.repair;
    cout << "Труба теперь: " << (p.repair ? "в ремонте" : "не в ремонте") << "\n";
}

void SavePipe(const Pipe& p) {
    ofstream file("pipe.txt");
    if (!file.is_open()) {
        cout << "Ошибка: не могу открыть файл\n";
        return;
    }
    file << p.name << "\n";
    file << p.diameter << "\n";
    file << p.lenght << "\n";
    file << p.thickness << "\n";
    if (p.repair) file << "в ремонте\n";
    else file << "не в ремонте\n";
    file.close();
    cout << "Созданная труба сохранена в pipe.txt\n";
}

void LoadPipe(Pipe& p) {
    ifstream file("pipe.txt");
    if (!file.is_open()) {
        cout << "Ошибка, файл pipe.txt не найден\n";
        return;
    }
    getline(file, p.name);
    file >> p.diameter;
    file >> p.lenght;
    file >> p.thickness;
    file.ignore();
    string status;
    getline(file, status);
    if (status == "в ремонте") p.repair = true;
    else p.repair = false;
    file.close();
    cout << "Труба загружена из pipe.txt\n";
}

void NewStation(Station& s)
{
    cout << "Название: ";
    cin >> s.name;
    cout << "Всего цехов: ";
    s.total = getInt();
    cout << "Цехов в работе: ";
    s.working = getInt();
    cout << "Класс станции: ";
    s.classNum = getInt();
}

void PrintStation(const Station& s)
{
    cout << "КС: " << s.name << ", цехов " << s.total << ", работают " << s.working << ", класс " << s.classNum << "\n";

}

void EditStation(Station& s)
{
    cout << "1-запустить цех: " << "2-остановить цех: ";
    int c = getInt();
    if (c == 1 && s.working < s.total) s.working++;
    if (c == 2 && s.working > 0) s.working--;
    cout << "В работе: " << s.working << " из " << s.total << "\n";
}

void SaveStation(const Station& s) {
    ofstream file("station.txt");
    if (!file.is_open()) {
        cout << "Ошибка: не могу открыть файл\n";
        return;
    }
    file << s.name << "\n";
    file << s.total << "\n";
    file << s.working << "\n";
    file << s.classNum << "\n";
    file.close();
    cout << "КС сохранена в файл station.txt\n";
}

void LoadStation(Station& s) {
    ifstream file("station.txt");
    if (!file.is_open()) {
        cout << "Ошибка: файл station.txt не найден\n";
        return;
    }
    getline(file, s.name);
    file >> s.total;
    file >> s.working;
    file >> s.classNum;
    file.close();
    hasStation = true;
    cout << "КС загружена из station.txt";
}
