#pragma once
#include <iostream>
#include <string>
using namespace std;

class redirect_output_wrapper {
	ostream& stream;
	streambuf* const old_buf;
public:
	redirect_output_wrapper(ostream& src)
		: old_buf(src.rdbuf()), stream(src) {}
	~redirect_output_wrapper() {
		stream.rdbuf(old_buf);
	}

	void redirect(ostream& dest) {
		stream.rdbuf(dest.rdbuf());
	}
};

template <typename T>
T GetCorrectNumber(T min, T max)
{
	T x;
	while ((cin >> x).fail()
		|| cin.peek() != '\n'
		|| x < min || x > max)
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Ошибка! Введите число от " << min << " до " << max << ": ";
	}
	cin.ignore(10000, '\n');
	return x;
}