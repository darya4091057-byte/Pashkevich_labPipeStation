#pragma once
#include <string>
#include <iostream>

class Pipe {
private:
    static int nextId;
    int id;
    std::string name;
    int diameter;
    double length;
    double thickness;
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