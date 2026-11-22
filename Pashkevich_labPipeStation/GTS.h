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
	int findFreePipe(int diameter) const;
	bool readConnectionStations(int& fromId, int& toId) const;
	int readDiameter() const;
	int createPipeForConnection(int diameter);

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
	void connectStations();
};