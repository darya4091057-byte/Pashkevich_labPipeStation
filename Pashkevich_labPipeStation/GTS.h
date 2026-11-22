#pragma once
#include <unordered_map>
#include "Pipe.h"
#include "Station.h"

struct Link {
	int fromStationId;
	int toStationId;
};

class GTS {
private:
	std::unordered_map<int, Pipe> pipes;
	std::unordered_map<int, Station> stations;
	std::unordered_map<int, Link> links;

public:
	void addPipe();
	void addStation();
	void showAll() const;
	void editPipe();
	void editStation();
	void searchPipes() const;
	void searchStations() const;
	void batchEditPipes();
	void deletePipe();
	void deleteStation();
	void saveToFile() const;
	void loadFromFile();
};