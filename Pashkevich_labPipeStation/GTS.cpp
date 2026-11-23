#include "GTS.h"
#include "abstractions.h"
#include <fstream>
#include <algorithm>
#include <iomanip>
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

	saveConnections(file);

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
		Pipe p;
		file >> p;
		pipes.emplace(p.getId(), p);
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

	if (!loadConnections(file)) {
		cout << "Ошибка чтения соединений\n";
		return;
	}
	cout << "Загружено\n";
}

int GTS::findFreePipe(int diameter) const {
	for (const auto& [id, p] : pipes) {
		if (p.getDiameter() == diameter && links.count(id) == 0) {
			return id;
		}
	}
	return 0;
}

void GTS::connectStations() {
	int fromId, toId;

	if (!readConnectionStations(fromId, toId)) {
		return;
	}

	int diameter = readDiameter();
	int pipeId = findFreePipe(diameter);
	if (pipeId == 0) {
		pipeId = createPipeForConnection(diameter);
	}

	links.emplace(pipeId, Link{ fromId, toId });

	cout << "КС" << fromId << " -> КС" << toId << ", труба ID" << pipeId << "\n";
}

bool GTS::readConnectionStations(int& fromId, int& toId) const {
	if (stations.size() < 2) {
		cout << "Нужны хотя бы две КС\n";
		return false;
	}

	cout << "ID КС, из которой выходит газ: ";
	fromId = GetCorrectNumber<int>(1, 10000);

	cout << "ID КС, в которую приходит газ: ";
	toId = GetCorrectNumber<int>(1, 10000);

	if (stations.count(fromId) == 0 || stations.count(toId) == 0 || fromId == toId) {
		cout << "КС должны существовать и различаться\n";
		return false;
	}

	return true;
}

int GTS::readDiameter() const {
	while (true) {
		cout << "Диаметр: 500, 700, 1000 или 1400 мм: ";
		int diameter = GetCorrectNumber<int>(500, 1400);

		if (diameter == 500 || diameter == 700 || diameter == 1000 || diameter == 1400) {
			return diameter;
		}
		cout << "Недопустимый диаметр\n";
	}
}

int GTS::createPipeForConnection(int diameter) {
	cout << "Создайте трубу диаметром " << diameter << " мм\n";

	while (true) {
		Pipe p;
		cin >> p;

		if (p.getDiameter() != diameter) {
			cout << "Диаметр не совпадает. Повторите ввод\n";
			continue;
		}

		int id = p.getId();
		pipes.emplace(id, p);
		return id;
	}
}

void GTS::ShowConnections() const {
	if (links.empty()) {
		cout << "Соединений нет\n";
		return;
	}

	for (const auto& [pipeId, link] : links) {
		cout << "Труба ID " << pipeId << ": КС " << link.fromStationId << " -> КС " << link.toStationId << "\n";
	}
}

void GTS::disconnectPipe() {
	cout << "ID трубы для отключения: ";
	int pipeId = GetCorrectNumber<int>(1, 10000);

	if (pipes.count(pipeId) == 0) {
		cout << "Труба не найдена\n";
		return;
	}

	if (links.erase(pipeId)) {
		cout << "Труба отключена\n";
	}
	else {
		cout << "Труба уже свободна\n";
	}
}

void GTS::saveConnections(ofstream& file) const {
	file << links.size() << "\n";

	for (const auto& [pipeId, link] : links) {
		file << pipeId << " " << link.fromStationId << " " << link.toStationId << "\n";
	}
}

bool GTS::loadConnections(ifstream& file) {
	file >> ws;
	if (file.eof()) {
		return true;
	}
	int count;
	if (!(file >> count) || count < 0) {
		return false;
	}
	unordered_map<int, Link> loadedLinks;

	for (int i = 0; i < count; i++) {
		int pipeId;
		Link link;

		if (!(file >> pipeId >> link.fromStationId >> link.toStationId)) {
			return false;
		}

		if (pipes.count(pipeId) == 0 || stations.count(link.fromStationId) == 0 || stations.count(link.toStationId) == 0 ||
			link.fromStationId == link.toStationId || loadedLinks.count(pipeId) != 0) {
			return false;
		}

		loadedLinks.emplace(pipeId, link);
	}
	links = loadedLinks;
	return true;
}

vector<int> GTS::getStationIds() const {
	vector<int> ids;

	for (const auto& [id, station] : stations) {
		ids.push_back(id);
	}
	sort(ids.begin(), ids.end());
	return ids;
}

vector<vector<int>> GTS::buildAdjacencyMatrix(
	const vector<int>& ids) const {
	int n = static_cast<int>(ids.size());
	vector<vector<int>> matrix(n, vector<int>(n, 0));

	unordered_map<int, int> index;
	for (int i = 0; i < n; i++) {
		index.emplace(ids[i], i);
	}

	for (const auto& [pipeId, link] : links) {
		int from = index.at(link.fromStationId);
		int to = index.at(link.toStationId);

		matrix[from][to] = 1;
	}
	return matrix;
}

void GTS::showAdjacencyMatrix() const {
	vector<int> ids = getStationIds();

	if (ids.empty()) {
		cout << "Нет КС\n";
		return;
	}

	auto matrix = buildAdjacencyMatrix(ids);

	cout << "Строка - откуда, столбец - куда. Подписи - ID КС.\n";

	cout << setw(7) << " ";
	for (int id : ids) {
		cout << setw(7) << id;
	}
	cout << "\n";

	for (size_t i = 0; i < ids.size(); i++) {
		cout << setw(7) << ids[i];

		for (int value : matrix[i]) {
			cout << setw(7) << value;
		}
		cout << "\n";
	}
}

vector<int> GTS::countIncoming(
	const vector<vector<int>>& matrix) const {

	int n = static_cast<int>(matrix.size());
	vector<int> incoming(n, 0);

	for (int from = 0; from < n; from++) {
		for (int to = 0; to < n; to++) {
			incoming[to] += matrix[from][to];
		}
	}
	return incoming;
}

int GTS::findReadyStation(const vector<int>& incoming) const {
	int n = static_cast<int>(incoming.size());

	for (int i = 0; i < n; i++) {
		if (incoming[i] == 0) {
			return 1;
		}
	}
	return -1;
}

vector<int> GTS::getTopologicalOrder(
	const vector<int>& ids) const {

	auto matrix = buildAdjacencyMatrix(ids);
	vector<int> incoming = countIncoming(matrix);
	vector<int> order;

	int n = static_cast<int>(ids.size());

	for (int step = 0; step < n; step++) {
		int current = findReadyStation(incoming);
		if (current == -1) {
			return {};
		}

		order.push_back(ids[current]);
		incoming[current] = -1;

		for (int to = 0; to < n; to++) {
			if (matrix[current][to] == 1) {
				incoming[to]--;
			}
		}
	}
	return order;
}

void GTS::showTopologicalOrder() const {
	vector<int> ids = getStationIds();

	if (ids.empty()) {
		cout << "Нет КС\n";
		return;
	}

	vector<int> order = getTopologicalOrder(ids);

	if (order.empty()) {
		cout << "В графе есть цикл. Сортировка невозможна\n";
		return;
	}

	cout << "Топологический порядок ID КС: ";

	for (int id : order) {
		cout << id << " ";
	}
	cout << "\n";
}