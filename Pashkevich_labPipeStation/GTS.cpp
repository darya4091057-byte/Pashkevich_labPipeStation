#include "GTS.h"

void GTS::addPipe() {
	::addPipe(pipes);
}

void GTS::showAll() const {
	for (const auto [id, p] : pipes) {
		p.print();
	}

	for (const auto [id, s] : stations) {
		s.print();
	}
}