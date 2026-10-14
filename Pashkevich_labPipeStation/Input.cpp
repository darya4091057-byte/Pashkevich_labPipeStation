#include "Input.h"
#include <iostream>
using namespace std;

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