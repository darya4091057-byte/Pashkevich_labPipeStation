#include "GTS.h"
#include "abstractions.h"

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
		std::cout << "Нет труб\n";
		return;
	}

	std::cout << "ID трубы для удаления: ";
	int id = GetCorrectNumber<int>(1, 10000);

	if (pipes.erase(id)) {
		links.erase(id);
		std::cout << "Удалено\n";
	}
	else {
		std::cout << "Не найдено\n";
	}
}

void GTS::deleteStation() {
	if (stations.empty()) {
		std::cout << "Нет КС\n";
		return;
	}
	std::cout << "ID КС для удаления: ";
	int id = GetCorrectNumber<int>(1, 10000);

	if (stations.count(id) == 0) {
		std::cout << "Не найдено\n";
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
	std::cout << "Удалено\n";
}