#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <windows.h>
#include "Pipe.h"
#include "Station.h"
#include "abstractions.h"
using namespace std;

int findPipeIndex(const vector<Pipe>& pipes, int id) {
    for (int i = 0; i < pipes.size(); i++) {
        if (pipes[i].getId() == id) return i;
    }
    return -1;
}

int findStationIndex(const vector<Station>& stations, int id) {
    for (int i = 0; i < stations.size(); i++) {
        if (stations[i].getId() == id) return i;
    }
    return -1;
}

void showAll(const vector<Pipe>& pipes, const vector<Station>& stations) {
    for (int i = 0; i < pipes.size(); i++) pipes[i].print();
    for (int i = 0; i < stations.size(); i++) stations[i].print();
}

void editPipe(vector<Pipe>& pipes) {
    if (pipes.empty()) { cout << "Нет труб\n"; return; }
    cout << "ID трубы: ";
    int index = findPipeIndex(pipes, GetCorrectNumber<int>(1, 10000));
    if (index != -1) {
        pipes[index].setRepair(!pipes[index].isRepair());
        cout << "Статус изменен\n";
    }
    else cout << "Не найдено\n";
}

void editStation(vector<Station>& stations) {
    if (stations.empty()) { cout << "Нет КС\n"; return; }
    cout << "ID КС: ";
    int index = findStationIndex(stations, GetCorrectNumber<int>(1, 10000));
    if (index == -1) { cout << "Не найдено\n"; return; }

    cout << "1-запустить, 2-остановить: ";
    int c = GetCorrectNumber<int>(1, 2);
    int work = stations[index].getWorking();
    int total = stations[index].getTotal();

    if (c == 1 && work < total) stations[index].setWorking(work + 1);
    if (c == 2 && work > 0) stations[index].setWorking(work - 1);
}

void deletePipe(vector<Pipe>& pipes) {
    if (pipes.empty()) { cout << "Нет труб\n"; return; }
    cout << "ID для удаления: ";
    int index = findPipeIndex(pipes, GetCorrectNumber<int>(1, 10000));
    if (index != -1) {
        pipes.erase(pipes.begin() + index);
        cout << "Удалено\n";
    }
    else cout << "Не найдено\n";
}

void deleteStation(vector<Station>& stations) {
    if (stations.empty()) { cout << "Нет КС\n"; return; }
    cout << "ID для удаления: ";
    int index = findStationIndex(stations, GetCorrectNumber<int>(1, 10000));
    if (index != -1) {
        stations.erase(stations.begin() + index);
        cout << "Удалено\n";
    }
    else cout << "Не найдено\n";
}

void searchPipes(const vector<Pipe>& pipes) {
    cout << "1-по названию, 2-в ремонте: ";
    if (GetCorrectNumber<int>(1, 2) == 1) {
        string name;
        cout << "Название: ";
        INPUT_LINE(cin, name);
        for (int i = 0; i < pipes.size(); i++)
            if (pipes[i].getName() == name) pipes[i].print();
    }
    else {
        for (int i = 0; i < pipes.size(); i++)
            if (pipes[i].isRepair()) pipes[i].print();
    }
}

void searchStations(const vector<Station>& stations) {
    cout << "Загрузка меньше (%): ";
    double maxLoad = GetCorrectNumber<double>(0, 100);
    for (int i = 0; i < stations.size(); i++)
        if (stations[i].getLoad() < maxLoad) stations[i].print();
}

void batchEditPipes(vector<Pipe>& pipes) {
    cout << "1-все, 2-по ID: ";
    if (GetCorrectNumber<int>(1, 2) == 1) {
        for (int i = 0; i < pipes.size(); i++) pipes[i].setRepair(!pipes[i].isRepair());
        cout << "Все изменены\n";
        return;
    }

    while (true) {
        cout << "ID (0-выход): ";
        int id = GetCorrectNumber<int>(0, 10000);
        if (id == 0) return;
        int index = findPipeIndex(pipes, id);
        if (index != -1) {
            pipes[index].setRepair(!pipes[index].isRepair());
            cout << "Изменено\n";
        }
    }
}

void saveToFile(const vector<Pipe>& pipes, const vector<Station>& stations) {
    string filename;
    cout << "Имя файла: ";
    INPUT_LINE(cin, filename);
    ofstream file(filename);
    if (!file.is_open()) { cout << "Ошибка\n"; return; }

    file << pipes.size() << "\n";
    for (int i = 0; i < pipes.size(); i++) file << pipes[i];
    file << stations.size() << "\n";
    for (int i = 0; i < stations.size(); i++) file << stations[i];
    cout << "Сохранено\n";
}

void loadFromFile(vector<Pipe>& pipes, vector<Station>& stations) {
    string filename;
    cout << "Имя файла: ";
    INPUT_LINE(cin, filename);
    ifstream file(filename);
    if (!file.is_open()) { cout << "Файл не найден\n"; return; }

    pipes.clear();
    stations.clear();
    int count;

    file >> count;
    for (int i = 0; i < count; i++) {
        Pipe p; file >> p; pipes.push_back(p);
    }
    file >> count;
    for (int i = 0; i < count; i++) {
        Station s; file >> s; stations.push_back(s);
    }
    cout << "Загружено\n";
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    redirect_output_wrapper cerr_wrapper(cerr);
    ofstream logfile("log.txt");
    if (logfile) cerr_wrapper.redirect(logfile);

    vector<Pipe> pipes;
    vector<Station> stations;
    int choice = -1;

    while (choice != 0) {
        cout << "\n1-добавить трубу\n2-добавить КС\n3-показать всё\n";
        cout << "4-редактировать трубу\n5-редактировать КС\n";
        cout << "6-удалить трубу\n7-удалить КС\n";
        cout << "8-поиск труб\n9-поиск КС\n10-пакетное редактирование\n";
        cout << "11-сохранить\n12-загрузить\n0-выход\nВыбор: ";
        choice = GetCorrectNumber<int>(0, 12);

        switch (choice) {
        case 1: { Pipe p; p.read(); pipes.push_back(p); break; }
        case 2: { Station s; s.read(); stations.push_back(s); break; }
        case 3: showAll(pipes, stations); break;
        case 4: editPipe(pipes); break;
        case 5: editStation(stations); break;
        case 6: deletePipe(pipes); break;
        case 7: deleteStation(stations); break;
        case 8: searchPipes(pipes); break;
        case 9: searchStations(stations); break;
        case 10: batchEditPipes(pipes); break;
        case 11: saveToFile(pipes, stations); break;
        case 12: loadFromFile(pipes, stations); break;
        case 0: cout << "Выход\n"; break;
        }
    }
    return 0;
}