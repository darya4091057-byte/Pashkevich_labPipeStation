#pragma once
#include <iostream>
#include <unordered_map>
#include <unordered_set>

class redirect_output_wrapper {
	std::ostream& stream;
	std::streambuf* const old_buf;
public:
	redirect_output_wrapper(std::ostream& src)
		: old_buf(src.rdbuf()), stream(src) {
	}
	~redirect_output_wrapper() {
		stream.rdbuf(old_buf);
	}

	void redirect(std::ostream& dest) {
		stream.rdbuf(dest.rdbuf());
	}
};

template<typename Obj, typename T>
using Filter = bool(*)(const Obj& obj, T param);

template<typename Obj, typename T>
std::unordered_set<int> FindByFilter(
	const std::unordered_map<int, Obj>& objects,
	Filter<Obj, T> f, T param)
{
	std::unordered_set<int> result;
	for (const auto& [id, obj] : objects) {
		if (f(obj, param)) {
			result.insert(id);
		}
	}
	return result;
}

template <typename T>
T GetCorrectNumber(T min, T max)
{
	T x;
	while ((std::cin >> x).fail()
		|| std::cin.peek() != '\n'
		|| x < min || x > max)
	{
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		std::cout << "Ошибка! Введите число от " << min << " до " << max << ": ";
	}
	std::cin.ignore(10000, '\n');
	return x;
}
#define INPUT_LINE(in, str) getline(in>>std::ws, str); std::cerr << str << std::endl