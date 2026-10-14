// Pashkevich_labPipeStation.cpp : Этот файл содержит функцию "main".
//

#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include "Pipe.h"
#include "Station.h"
#include "Input.h"
using namespace std;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Pipe myPipe;
    Station myStation;
    bool flagPipe = false;
    bool flagStation = false;

    int choice = -1;
    while (choice != 0) {
        cout << "\n1-добавить трубу\n";
        cout << "2-добавить КС\n";
        cout << "3-показать всё\n";
        cout << "4-редактировать трубу\n";
        cout << "5-редактировать КС\n";
        cout << "6-сохранить всё\n";
        cout << "7-загрузить всё\n";
        cout << "0-выход\n";
        cout << "Выбор: ";
        choice = getInt();

        while (choice < 0 || choice > 7) {
            cout << "Ошибка! Только 0, 1, 2, 3, 4, 5, 6, 7: ";
            choice = getInt();
        }

        switch (choice) {
        case 1:
            NewPipe(myPipe);
            flagPipe = true;
            cout << "Труба добавлена!\n";
            break;
        case 2:
            NewStation(myStation);
            flagStation = true;
            cout << "КС добавлена!\n";
            break;
        case 3:
            if (flagPipe) PrintPipe(myPipe);
            if (flagStation) PrintStation(myStation);
            if (!flagPipe && !flagStation) cout << "Пока ничего нет\n";
            break;
        case 4:
            if (flagPipe) EditPipe(myPipe);
            else cout << "Сначала добавьте трубу\n";
            break;
        case 5:
            if (flagStation) EditStation(myStation);
            else cout << "Сначала добавьте КС\n";
            break;
        case 6: {
            string filename;
            cout << "Введите имя файла для сохранения: ";
            getline(cin >> ws, filename);

            ofstream file(filename);
            if (!file.is_open()) {
                cout << "Ошибка: не могу создать файл " << filename << "\n";
                break;
            }

            if (flagPipe) SavePipe(file, myPipe);
            if (flagStation) SaveStation(file, myStation);

            file.close();
            cout << "Данные сохранены в " << filename << "\n";
            break;
        }
        case 7: {
            string filename;
            cout << "Введите имя файла для загрузки: ";
            getline(cin >> ws, filename);

            ifstream file(filename);
            if (!file.is_open()) {
                cout << "Ошибка: файл " << filename << " не найден\n";
                break;
            }

            if (flagPipe) LoadPipe(file, myPipe);
            if (flagStation) LoadStation(file, myStation);

            file.close();
            cout << "Данные загружены из " << filename << "\n";
            break;
        }
        case 0:
            cout << "Пока пока!\n";
            break;
        default:
            cout << "Неверный выбор\n";
            break;
        }
    }
    return 0;
}