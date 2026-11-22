#include "Pipe.h"
#include "abstractions.h"
#include <unordered_map>
using namespace std;

int Pipe::nextId = 1;

Pipe::Pipe() {
    id = nextId++;
    diameter = 0;
    length = 0;
    repair = false;
}

istream& operator>>(istream& is, Pipe& p) {
    cout << "Название: ";
    INPUT_LINE(is, p.name);
    cout << "Диаметр (мм): ";
    p.diameter = GetCorrectNumber<int>(1, 10000);
    cout << "Длина (км): ";
    p.length = GetCorrectNumber<double>(0.1, 10000);
    cout << "В ремонте? (0-нет, 1-да): ";
    p.repair = GetCorrectNumber<int>(0, 1);
    cerr << "Создана труба с id" << p.id << "\n";

    return is;
}

void Pipe::print() const {
    cout << "[" << id << "] " << name
        << " d=" << diameter
        << " l=" << length
        << " " << (repair ? "в ремонте" : "рабочая") << "\n";
}

ofstream& operator<<(ofstream& os, const Pipe& p) {
    os << p.id << "\n" << p.name << "\n" << p.diameter << "\n"
        << p.length << "\n" << p.repair << "\n";
    return os;
}

ifstream& operator>>(ifstream& is, Pipe& p) {
    is >> p.id;
    is >> ws;
    getline(is, p.name);
    is >> p.diameter >> p.length >> p.repair;
    if (p.id >= Pipe::nextId) 
        Pipe::nextId = p.id + 1;
    return is;
}

void addPipe(unordered_map<int, Pipe>& pipes) {
    Pipe p;
    cin >> p;
    pipes.emplace(p.getId(), p);

}

void editPipe(unordered_map<int, Pipe>& pipes) {
    if (pipes.empty()) { cout << "Нет труб\n"; return; }
    cout << "ID трубы: ";
    int id = GetCorrectNumber<int>(1, 10000);
    if (pipes.count(id)) {
        pipes[id].setRepair(!pipes[id].isRepair());
        cout << "Статус изменен\n";
    }
    else cout << "Не найдено\n";
}

void deletePipe(unordered_map<int, Pipe>& pipes) {
    if (pipes.empty()) { cout << "Нет труб\n"; return; }
    cout << "ID для удаления: ";
    int id = GetCorrectNumber<int>(1, 10000);
    if (pipes.erase(id)) cout << "Удалено\n";
    else cout << "Не найдено\n";
}

bool filterPipeName(const Pipe& p, string name) {
    return p.getName() == name;
}

bool filterPipeRepair(const Pipe& p, bool inRepair) {
    return p.isRepair() == inRepair;
}

void searchPipes(const unordered_map<int, Pipe>& pipes) {
    if (pipes.empty()) { cout << "Нет труб\n"; return; }
    cout << "1-по названию, 2-в ремонте: ";
    if (GetCorrectNumber<int>(1, 2) == 1) {
        string name;
        cout << "Название: ";
        INPUT_LINE(cin, name);

        auto result = FindByFilter(pipes, filterPipeName, name);
        for (int id : result) pipes.at(id).print();
    }
    else {
        cout << "1-в ремонте, 0-рабочие: ";
        bool rep = GetCorrectNumber<int>(0, 1);
        auto result = FindByFilter(pipes, filterPipeRepair, rep);
        for (int id : result) pipes.at(id).print();
    }
}

void batchEditPipes(unordered_map<int, Pipe>& pipes) {
    if (pipes.empty()) { cout << "Нет труб\n"; return; }

    cout << "1-все, 2-по ID: ";
    if (GetCorrectNumber<int>(1, 2) == 1) {
        for (auto& [id, p] : pipes) {
            p.setRepair(!p.isRepair());
        }
        cout << "Все изменены\n";
        return;
    }
    while (true) {
        cout << "ID (0-выход): ";
        int id = GetCorrectNumber<int>(0, 10000);
        if (id == 0) return;
        if (pipes.count(id)) {
            pipes[id].setRepair(!pipes[id].isRepair());
            cout << "Изменено\n";
        }
        else {
            cout << "Не найдено\n";
        }
    }
}