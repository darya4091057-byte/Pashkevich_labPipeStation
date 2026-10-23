#include "Pipe.h"
#include "abstractions.h"
using namespace std;

int Pipe::nextId = 1;

Pipe::Pipe() {
    id = nextId++;
    diameter = 0;
    length = 0;
    thickness = 0;
    repair = false;
}

void Pipe::read() {
    cout << "Название: ";
    INPUT_LINE(cin, name);
    cout << "Диаметр (мм): ";
    diameter = GetCorrectNumber<int>(1, 10000);
    cout << "Длина (км): ";
    length = GetCorrectNumber<double>(0.1, 10000);
    cout << "Толщина (мм): ";
    thickness = GetCorrectNumber<double>(0.1, 1000);
    cout << "В ремонте? (0-нет, 1-да): ";
    repair = GetCorrectNumber<int>(0, 1);

    cerr << "Создана труба #" << id << "\n";
}

void Pipe::print() const {
    cout << "[" << id << "] " << name
        << " | D=" << diameter
        << " | L=" << length
        << " | T=" << thickness
        << " | " << (repair ? "в ремонте" : "рабочая") << "\n";
}

ostream& operator<<(ostream& os, const Pipe& p) {
    os << p.id << "\n" << p.name << "\n" << p.diameter << "\n"
        << p.length << "\n" << p.thickness << "\n" << p.repair << "\n";
    return os;
}

istream& operator>>(istream& is, Pipe& p) {
    is >> p.id;
    is.ignore();
    getline(is, p.name);
    is >> p.diameter >> p.length >> p.thickness >> p.repair;
    if (p.id >= Pipe::nextId) Pipe::nextId = p.id + 1;
    return is;
}