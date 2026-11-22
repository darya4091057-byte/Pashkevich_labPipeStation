#include "Station.h"
#include "abstractions.h"
#include <unordered_map>
using namespace std;

int Station::nextId = 1;

Station::Station() {
    id = nextId++;
    total = 0;
    working = 0;
    classNum = 0;
}

istream& operator>>(istream& is, Station& s) {
    cout << "Название: ";
    INPUT_LINE(is, s.name);
    cout << "Всего цехов: ";
    s.total = GetCorrectNumber<int>(1, 100);
    cout << "Работают: ";
    s.working = GetCorrectNumber<int>(0, s.total);
    cout << "Класс: ";
    s.classNum = GetCorrectNumber<int>(1, 10);
    cerr << "Создана КС с id" << s.id << "\n";
    return is;
}

void Station::print() const {
    cout << "[" << id << "] " << name
        << " цехов " << total
        << " работают " << working
        << " класс " << classNum
        << " незадействовано " << getLoad() << "%\n";
}

ofstream& operator<<(ofstream& os, const Station& s) 
{
    os << s.id << "\n" << s.name << "\n" << s.total << "\n"
        << s.working << "\n" << s.classNum << "\n";
    return os;
}

ifstream& operator>>(ifstream& is, Station& s) {
    is >> s.id;
    is >> ws;
    is >> s.total >> s.working >> s.classNum;
    if (s.id >= Station::nextId) Station::nextId = s.id + 1;
    return is;
}

void addStation(unordered_map<int, Station>& stations) {
    Station s;
    cin >> s;
    stations.emplace(s.getId(), s);
}

void editStation(unordered_map<int, Station>& stations) {
    if (stations.empty()) { cout << "Нет КС\n"; return; }
    cout << "ID КС: ";
    int id = GetCorrectNumber<int>(1, 10000);
    if (stations.count(id)) {
        cout << "1-запустить, 2-остановить: ";
        int c = GetCorrectNumber<int>(1, 2);
        if (c == 1) {
            stations[id].setWorking(stations[id].getWorking() + 1);
        }
        if (c == 2) {
            stations[id].setWorking(stations[id].getWorking() - 1);
        }
        cout << "Готово. В работе: " << stations[id].getWorking() << "\n";
    }
    else cout << "Не найдено\n";
}

void deleteStation(unordered_map<int, Station>& stations) {
    if (stations.empty()) { cout << "Нет КС\n"; return; }
    cout << "ID для удаления: ";
    int id = GetCorrectNumber<int>(1, 10000);
    if (stations.erase(id)) 
        cout << "Удалено\n";
    else cout << "Не найдено\n";
}

bool filterCSName(const Station& s, string name) {
    return s.getName() == name;
}

bool filterCSPercent(const Station& s, double maxLoad) {
    return s.getLoad() < maxLoad;
}

void searchStations(const unordered_map<int, Station>& stations) {
    if (stations.empty()) { cout << "Нет КС\n"; return; }
    cout << "1-по названию, 2-по проценту загрузки: ";
    if (GetCorrectNumber<int>(1, 2) == 1) {
        string name;
        cout << "Название: ";
        INPUT_LINE(cin, name);

        auto result = FindByFilter(stations, filterCSName, name);
        for (int id : result) 
            stations.at(id).print();
    }
    else {
        cout << "Загрузка меньше (%): ";
        double maxLoad = GetCorrectNumber<double>(0, 100);
        auto result = FindByFilter(stations, filterCSPercent, maxLoad);
        for (int id : result) stations.at(id).print();
    }
}