#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

void read_data(std::vector<std::vector<int>> &graph, std::vector<std::map<int, int>> &sorted_edges);
void print_result(int* max, int* min);
void algo(std::vector<std::map<int, int>> &sorted_edges, std::vector<std::string> &result, int* min_value, int* max);

int main() {
	std::vector<std::vector<int>> graph;
	std::vector<std::map<int, int>> sorted_edges;

	read_data(graph, sorted_edges);

	std::vector<std::string> result;
	int *min_value = new int;
	int *max = new int;

	algo(sorted_edges, result, min_value, max);
	print_result(max, min_value);

	delete min_value;
	delete max;
	return 0;
}

void read_data(std::vector<std::vector<int>> &graph, std::vector<std::map<int, int>> &sorted_edges) {
	std::fstream f;
	std::vector<std::string> splited_string;
	std::string vert;
	std::string values;
	f.open("prof.in", std::fstream::in);
	std::getline(f, values);
	std::istringstream row(values);
	while (row >> vert) {
		splited_string.push_back(vert);
	}
	for (int i = 0; i < splited_string.size(); i++) {
		graph.push_back(std::vector<int>());
		sorted_edges.push_back(std::map<int, int>());
		vert = "";
		for (unsigned int j = 0; j < splited_string[i].length(); j++) {
			if (splited_string[i][j] != ',' && j != splited_string[i].length() - 1) {
				vert += splited_string[i][j];
			}
			else {
				if (vert == "0" || splited_string[i][j] == '0') {
					graph[i].push_back(0);
				}
				else if (j == splited_string[i].length() - 1 && splited_string[i][j] != ',') {
					graph[i].push_back((int)splited_string[i][j]);
					sorted_edges[i][(int)splited_string[i][j]] = int(graph[i].size() - 1);
				}
				else {
					graph[i].push_back(std::stoi(vert));
					sorted_edges[i][std::stoi(vert)] = int(graph[i].size() - 1);
				}
				vert = "";
			}
		}
	}
	f.close();
}

void print_result(int* max, int* min) {
	std::fstream f;
	f.open("prof.out", std::fstream::out);
	f << *max - *min;
	f.close();
}

void algo(std::vector<std::map<int, int>> &sorted_edges, std::vector<std::string> &result, int* min_value, int* max) {
	int prev = 0;
	int curent = 0;
	int local_min = 1000;
	*max = 1000;
	*min_value = sorted_edges[0].begin()->first;
	curent = sorted_edges[0].begin()->second;
	result.push_back(std::to_string(prev) + "->" + std::to_string(curent));
	int end = sorted_edges.size() - 1;
	auto iter = sorted_edges[prev].begin();
	iter++;
	while (end > 0) {
		for (auto i = sorted_edges[curent].begin(); i != sorted_edges[curent].end(); i++) {
			if (i->second != prev && ((i->first - *min_value) < (local_min - *min_value))) {
				local_min = i->first;
				break;
			}
		}
		if ((local_min - *min_value) > (iter->first - *min_value)) {
			result.push_back(std::to_string(curent) + "->" + std::to_string(prev));
			curent = iter->second;
			result.push_back(std::to_string(prev) + "->" + std::to_string(curent));
			if (*max < iter->first || *max == 1000) {
				*max = iter->first;
			}
			iter++;
			end--;
		}
		else {
			prev = curent;
			curent = sorted_edges[curent][local_min];
			result.push_back(std::to_string(prev) + "->" + std::to_string(curent));
			if (*max < local_min || *max == 1000) {
				*max = local_min;
			}
		}
		end--;
	}
}