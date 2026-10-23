#include "Station.h"
#include "abstractions.h"
using namespace std;

int Station::nextId = 1;

Station::Station() {
    id = nextId++;
    total = 0;
    working = 0;
    classNum = 0;
}

void Station::read() {
    cout << "Название: ";
    INPUT_LINE(cin, name);
    cout << "Всего цехов: ";
    total = GetCorrectNumber<int>(1, 100);
    cout << "Работают: ";
    working = GetCorrectNumber<int>(0, total);
    cout << "Класс: ";
    classNum = GetCorrectNumber<int>(1, 10);

    cerr << "Создана КС #" << id << "\n";
}

void Station::print() const {
    cout << "[" << id << "] " << name
        << " | цехов " << total
        << " | работают " << working
        << " | класс " << classNum
        << " | незадействовано " << getLoad() << "%\n";
}

ostream& operator<<(ostream& os, const Station& s) {
    os << s.id << "\n" << s.name << "\n" << s.total << "\n"
        << s.working << "\n" << s.classNum << "\n";
    return os;
}

istream& operator>>(istream& is, Station& s) {
    is >> s.id;
    is.ignore();
    getline(is, s.name);
    is >> s.total >> s.working >> s.classNum;
    if (s.id >= Station::nextId) Station::nextId = s.id + 1;
    return is;
}