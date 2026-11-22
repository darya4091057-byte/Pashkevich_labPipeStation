#include "GTS.h"

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