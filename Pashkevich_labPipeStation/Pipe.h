#pragma once
#include <string>
#include <iostream>
#include <unordered_map>

class Pipe {
private:
    static int nextId;
    int id;
    std::string name;
    int diameter;
    double length;
    bool repair;

public:
    Pipe();

    int getId() const { return id; }
    std::string getName() const { return name; }
    bool isRepair() const { return repair; }

    void setRepair(bool r) { repair = r; }

    void read();
    void print() const;

    friend std::ostream& operator<<(std::ostream& os, const Pipe& p);
    friend std::istream& operator>>(std::istream& is, Pipe& p);
};

void addPipe(std::unordered_map<int, Pipe>& pipes);
void editPipe(std::unordered_map<int, Pipe>& pipes);
void deletePipe(std::unordered_map<int, Pipe>& pipes);
void searchPipes(const std::unordered_map<int, Pipe>& pipes);
bool filterPipeName(const Pipe& p, std::string name);
bool filterPipeRepair(const Pipe& p, bool inRepair);
void batchEditPipes(std::unordered_map<int, Pipe>& pipes);