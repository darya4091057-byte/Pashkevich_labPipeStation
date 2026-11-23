#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <windows.h>
#include "Pipe.h"
#include "Station.h"
#include "abstractions.h"
#include <filesystem>
#include "GTS.h"
using namespace std;

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

    filesystem::create_directories("log");
    redirect_output_wrapper cerr_out(cerr);
    string time = format("{:%d_%M_%Y %H_%M_%OS}", chrono::system_clock::now());
    ofstream logfile("log/log_" + time + ".txt");
    if (logfile)
        cerr_out.redirect(logfile);

    unordered_map<int, Pipe> pipes;
    unordered_map<int, Station> stations;

    GTS network;
    int choice = -1;

    while (choice != 0) {
        cout << "\n1-добавить трубу\n2-добавить КС\n3-показать всё\n";
        cout << "4-редактировать трубу\n5-редактировать КС\n";
        cout << "6-удалить трубу\n7-удалить КС\n";
        cout << "8-поиск труб\n9-поиск КС\n10-пакетное редактирование труб\n";
        cout << "11-сохранить в файл\n";
        cout << "12-загрузить из файла\n";
        cout << "13-соединить КС\n";
        cout << "14-Показать соединения\n";
        cout << "15-отключить трубу\n";
        cout << "16-Показать матрицу смежности\n";
        cout << "0-выход\n";
        cout << "Выбор: ";
        choice = GetCorrectNumber<int>(0, 16);

        switch (choice) {
        case 1: 
            network.addPipe();
            break;
        case 2: 
            network.addStation();
            break;
        case 3: 
            network.showAll();
            break;
        case 4: 
            network.editPipe();
            break;
        case 5: 
            network.editStation();
            break;
        case 6: 
            network.deletePipe();
            break;
        case 7: 
            network.deleteStation();
            break;
        case 8: 
            network.searchPipes();
            break;
        case 9: 
            network.searchStations();
            break;
        case 10: 
            network.batchEditPipes();
            break;
        case 11: 
            network.saveToFile();
            break;
        case 12: 
            network.loadFromFile();
            break;
        case 13:
            network.connectStations();
            break;
        case 14:
            network.ShowConnections();
            break;
        case 15:
            network.disconnectPipe();
            break;
        case 16:
            network.showAdjacencyMatrix();
            break;
        case 0: 
            cout << "Выход\n";
            break;
        }
    }
    return 0;
}