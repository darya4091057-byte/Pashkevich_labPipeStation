// Pashkevich_labPipeStation.cpp : Этот файл содержит функцию "main".
//
//Для контрольной: написать через тернарный оператор, типа что получится, если дано это...
// Или поиск числа в векторе - функцию написать или переписать if на switch, на while и так далее 
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <windows.h>
#include "Pipe.h"
#include "Station.h"
#include "abstractions.h"
using namespace std;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    redirect_output_wrapper cerr_wrapper(cerr);
    ofstream logfile("log.txt");
    if (logfile) cerr_wrapper.redirect(logfile);

    vector<Pipe> pipes;
    vector<Station> stations;
    int choice = -1;

    while (choice != 0) {
        cout << "\n1-добавить трубу\n";
        cout << "2-добавить КС\n";
        cout << "3-показать всё\n";
        cout << "4-редактировать трубу\n";
        cout << "5-редактировать КС\n";
        cout << "6-удалить трубу\n";
        cout << "7-удалить КС\n";
        cout << "8-поиск труб\n";
        cout << "9-поиск КС\n";
        cout << "10-пакетное редактирование труб\n";
        cout << "11-сохранить в файл\n";
        cout << "12-загрузить из файла\n";
        cout << "0-выход\n";
        cout << "Выбор: ";
        choice = GetCorrectNumber<int>(0, 12);

        switch (choice) {
        case 1: {
            Pipe p;
            p.read();
            pipes.push_back(p);
            break;
        }
        case 2: {
            Station s;
            s.read();
            stations.push_back(s);
            break;
        }
        case 3:
            for (int i = 0; i < pipes.size(); i++) pipes[i].print();
            for (int i = 0; i < stations.size(); i++) stations[i].print();
            break;

        case 4: {
            if (pipes.size() == 0) { cout << "Нет труб\n"; break; }
            cout << "ID трубы: ";
            int id = GetCorrectNumber<int>(1, 10000);
            for (int i = 0; i < pipes.size(); i++) {
                if (pipes[i].getId() == id) {
                    pipes[i].setRepair(!pipes[i].isRepair());
                    cout << "Статус ремонта изменен\n";
                    break;
                }
            }
            break;
        }

        case 5: {
            if (stations.size() == 0) { cout << "Нет КС\n"; break; }
            cout << "ID КС: ";
            int id = GetCorrectNumber<int>(1, 10000);
            for (int i = 0; i < stations.size(); i++) {
                if (stations[i].getId() == id) {
                    cout << "1-запустить, 2-остановить: ";
                    int c = GetCorrectNumber<int>(1, 2);
                    if (c == 1 && stations[i].getWorking() < stations[i].getTotal())
                        stations[i].setWorking(stations[i].getWorking() + 1);
                    if (c == 2 && stations[i].getWorking() > 0)
                        stations[i].setWorking(stations[i].getWorking() - 1);
                    break;
                }
            }
            break;
        }

        case 6: {
            if (pipes.size() == 0) { cout << "Нет труб\n"; break; }
            cout << "ID трубы для удаления: ";
            int id = GetCorrectNumber<int>(1, 10000);
            for (int i = 0; i < pipes.size(); i++) {
                if (pipes[i].getId() == id) {
                    pipes.erase(pipes.begin() + i);
                    cout << "Удалено\n";
                    break;
                }
            }
            break;
        }

        case 7: {
            if (stations.size() == 0) { cout << "Нет КС\n"; break; }
            cout << "ID КС для удаления: ";
            int id = GetCorrectNumber<int>(1, 10000);
            for (int i = 0; i < stations.size(); i++) {
                if (stations[i].getId() == id) {
                    stations.erase(stations.begin() + i);
                    cout << "Удалено\n";
                    break;
                }
            }
            break;
        }

        case 8: {
            cout << "1-по названию, 2-в ремонте: ";
            int c = GetCorrectNumber<int>(1, 2);
            if (c == 1) {
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
            break;
        }

        case 9: {
            cout << "Показать КС с загрузкой меньше (%): ";
            double maxLoad = GetCorrectNumber<double>(0, 100);
            for (int i = 0; i < stations.size(); i++)
                if (stations[i].getLoad() < maxLoad) stations[i].print();
            break;
        }

        case 10: {
            cout << "1-все трубы, 2-выбрать по ID: ";
            int c = GetCorrectNumber<int>(1, 2);
            if (c == 1) {
                for (int i = 0; i < pipes.size(); i++)
                    pipes[i].setRepair(!pipes[i].isRepair());
                cout << "Все изменены\n";
            }
            else {
                while (true) {
                    cout << "ID (0-закончить): ";
                    int id = GetCorrectNumber<int>(0, 10000);
                    if (id == 0) break;
                    for (int i = 0; i < pipes.size(); i++) {
                        if (pipes[i].getId() == id) {
                            pipes[i].setRepair(!pipes[i].isRepair());
                            cout << "Изменено\n";
                            break;
                        }
                    }
                }
            }
            break;
        }

        case 11: {
            string filename;
            cout << "Имя файла: ";
            INPUT_LINE(cin, filename);
            ofstream file(filename);
            if (!file.is_open()) { cout << "Ошибка\n"; break; }
            file << pipes.size() << "\n";
            for (int i = 0; i < pipes.size(); i++) file << pipes[i];
            file << stations.size() << "\n";
            for (int i = 0; i < stations.size(); i++) file << stations[i];
            file.close();
            break;
        }

        case 12: {
            string filename;
            cout << "Имя файла: ";
            INPUT_LINE(cin, filename);
            ifstream file(filename);
            if (!file.is_open()) { cout << "Файл не найден\n"; break; }
            pipes.clear(); stations.clear();
            int cp; file >> cp;
            for (int i = 0; i < cp; i++) {
                Pipe p; file >> p; pipes.push_back(p);
            }
            int cs; file >> cs;
            for (int i = 0; i < cs; i++) {
                Station s; file >> s; stations.push_back(s);
            }
            file.close();
            break;
        }

        case 0:
            cout << "Выход\n";
            break;
        }
    }
    return 0;
}