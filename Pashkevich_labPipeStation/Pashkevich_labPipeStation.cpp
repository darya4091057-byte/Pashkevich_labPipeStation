#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <windows.h>
#include "Pipe.h"
#include "Station.h"
#include "abstractions.h"
using namespace std;

void showAll(const unordered_map<int, Pipe>& pipes, const unordered_map<int, Station>& stations) {
    for (const auto& [id, p] : pipes)
        p.print();
    for (const auto& [id, s] : stations)
        s.print();
}

void saveToFile(const unordered_map<int, Pipe>& pipes, const unordered_map<int, Station>& stations) {
    string filename;
    cout << "Имя файла: ";
    INPUT_LINE(cin, filename);
    ofstream file(filename);
    if (!file.is_open()) { cout << "Ошибка\n"; return; }

    file << pipes.size() << "\n";
    for (const auto& [id, p] : pipes) file << p;
    file << stations.size() << "\n";
    for (const auto& [id, s] : stations) file << s;
    cout << "Сохранено\n";
}

void loadFromFile(unordered_map<int, Pipe>& pipes, unordered_map<int, Station>& stations) {
    string filename;
    cout << "Имя файла: ";
    INPUT_LINE(cin, filename);
    ifstream file(filename);
    if (!file.is_open()) { cout << "Файл не найден\n"; return; }

    pipes.clear(); stations.clear();
    int count;
    file >> count;
    for (int i = 0; i < count; i++) {
        Pipe p; file >> p; pipes[p.getId()] = p;
    }
    file >> count;
    for (int i = 0; i < count; i++) {
        Station s; file >> s; stations[s.getId()] = s;
    }
    cout << "Загружено\n";
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    redirect_output_wrapper cerr_wrapper(cerr);
    ofstream logfile("log.txt");
    if (logfile) 
        cerr_wrapper.redirect(logfile);

    unordered_map<int, Pipe> pipes;
    unordered_map<int, Station> stations;
    int choice = -1;

    while (choice != 0) {
        cout << "\n1-добавить трубу\n2-добавить КС\n3-показать всё\n";
        cout << "4-редактировать трубу\n5-редактировать КС\n";
        cout << "6-удалить трубу\n7-удалить КС\n";
        cout << "8-поиск труб\n9-поиск КС\n10-пакетное редактирование труб\n";
        cout << "11-сохранить в файл\n12-загрузить из файла\n0-выход\nВыбор: ";
        choice = GetCorrectNumber<int>(0, 12);

        switch (choice) {
        case 1: 
            addPipe(pipes);
            break;
        case 2: addStation(stations);
            break;
        case 3: showAll(pipes, stations);
            break;
        case 4: editPipe(pipes);
            break;
        case 5: editStation(stations);
            break;
        case 6: deletePipe(pipes);
            break;
        case 7: deleteStation(stations);
            break;
        case 8: searchPipes(pipes);
            break;
        case 9: searchStations(stations);
            break;
        case 10: batchEditPipes(pipes);
            break;
        case 11: saveToFile(pipes, stations);
            break;
        case 12: loadFromFile(pipes, stations);
            break;
        case 0: cout << "Выход\n";
            break;
        }
    }
    return 0;
}