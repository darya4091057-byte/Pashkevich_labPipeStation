#pragma once
#include <string>
#include <iostream>

class Station {
private:
    static int nextId;
    int id;
    std::string name;
    int total;
    int working;
    int classNum;

public:
    Station();

    int getId() const { return id; }
    std::string getName() const { return name; }
    int getTotal() const { return total; }
    int getWorking() const { return working; }

    void setWorking(int w) { working = w; }

    double getLoad() const {
        if (total == 0) return 0;
        return ((double)(total - working) / total) * 100.0;
    }

    void read();
    void print() const;

    friend std::ostream& operator<<(std::ostream& os, const Station& s);
    friend std::istream& operator>>(std::istream& is, Station& s);
};