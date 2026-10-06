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



int getInt() {
    int x;
    while (true) {
        cin >> x;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ошибка! Введите число: ";
            continue;
        }

        if (cin.peek() != '\n' && cin.peek() != EOF) {
            cin.ignore(10000, '\n');
            cout << "Ошибка! Введите только число, без букв: ";
            continue;
        }

        else {
            cin.ignore(10000, '\n');
            return x;
        }
    }

}

double getDouble() {
    double x;
    while (true) {
        cin >> x;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ошибка! Введите число: ";
            continue;
        }

        if (cin.peek() != '\n' && cin.peek() != EOF) {
            cin.ignore(10000, '\n');
            cout << "Ошибка! Введите только число, без букв: ";
            continue;
        }

        else {
            cin.ignore(10000, '\n');
            return x;
        }
    }

}

void NewPipe(Pipe& p)
{
    cout << "Название: ";
    getline(cin >> ws, p.name);//
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

void NewStation(Station& s)
{
    cout << "Название: ";
    getline(cin >> ws, s.name);//
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
            getline(cin >> ws, filename);//!!

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
