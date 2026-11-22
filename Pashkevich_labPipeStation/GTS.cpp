#include "GTS.h"
#include "abstractions.h"
#include <fstream>
using namespace std;

void GTS::addPipe() {
	::addPipe(pipes);
}

void GTS::addStation() {
	::addStation(stations);
}

void GTS::showAll() const {
	for (const auto [id, p] : pipes) {
		p.print();
	}

	for (const auto [id, s] : stations) {
		s.print();
	}
}

void GTS::editPipe() {
	::editPipe(pipes);
}

void GTS::editStation() {
	::editStation(stations);
}
void GTS::searchPipes() const {
	::searchPipes(pipes);
}

void GTS::searchStations() const {
	::searchStations(stations);
}

void GTS::batchEditPipes() {
	::batchEditPipes(pipes);
}

void GTS::deletePipe() {
	if (pipes.empty()) {
		cout << "Нет труб\n";
		return;
	}

	cout << "ID трубы для удаления: ";
	int id = GetCorrectNumber<int>(1, 10000);

	if (pipes.erase(id)) {
		links.erase(id);
		cout << "Удалено\n";
	}
	else {
		cout << "Не найдено\n";
	}
}

void GTS::deleteStation() {
	if (stations.empty()) {
		cout << "Нет КС\n";
		return;
	}
	cout << "ID КС для удаления: ";
	int id = GetCorrectNumber<int>(1, 10000);

	if (stations.count(id) == 0) {
		cout << "Не найдено\n";
		return;
	}

	for (auto it = links.begin(); it != links.end(); ) {
		if (it->second.fromStationId == id ||
			it->second.toStationId == id) {
			it = links.erase(it);
		}
		else {
			++it;
		}
	}

	stations.erase(id);
	cout << "Удалено\n";
}

void GTS::saveToFile() const {
	string filename;
	cout << "Имя файла: ";
	INPUT_LINE(cin, filename);
	ofstream file(filename);
	if (!file.is_open()) { cout << "Ошибка\n"; return; }

	file << pipes.size() << "\n";
	for (const auto& [id, p] : pipes) file << p;
	file << stations.size() << "\n";
	for (const auto& [id, s] : stations) file << s;
	cout << "Сохранено\n";
}

void GTS::loadFromFile() {
	string filename;
	cout << "Имя файла: ";
	INPUT_LINE(cin, filename);
	ifstream file(filename);
	if (!file.is_open()) { cout << "Файл не найден\n"; return; }

	pipes.clear(); stations.clear(); links.clear();
	int count;
	file >> count;
	for (int i = 0; i < count; i++) {
		Pipe p; file >> p; pipes[p.getId()] = p;
	}
	file >> count;
	for (int i = 0; i < count; i++) {
		Station s;
		if (!(file >> s)) {
			cout << "Ошибка чтения КС из файла\n";
			return;
		}
		stations.emplace(s.getId(), s);
	}
	cout << "Загружено\n";
}