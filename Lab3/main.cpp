#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

const int INF = 1000000001;

void read_from_file(std::vector<std::vector<std::pair<int, int>>>& edges, int vertexes, std::vector<int>& clients, std::vector<int>& routers);
void delete_extra_routers(std::vector<std::vector<std::pair<int, int>>>& edges, int vertexes, std::vector<int>& clients, std::vector<int>& routers);
void dijkstras_algorithm(std::vector<std::vector<std::pair<int, int>>>& edges, int vertexes, std::vector<int>& distance, std::vector<int>& p);
long build_path(std::vector<std::vector<std::pair<int, int>>>& edges, int vertexes, int router, int client, std::vector<int>& path, std::vector<int>& p);
void output_to_file(std::pair<int, int>& best_server);

int main() {
	std::fstream f;
	int count_edges, vertexes;
	f.open("gamesrv.in", std::fstream::in);
	f >> vertexes >> count_edges;
	f.get();
	f.close();
	
	std::vector<std::vector<std::pair<int, int>>>edges(vertexes);
	std::vector<int> clients;
	std::vector<int> routers;
	

	read_from_file(edges, vertexes, clients, routers);

	if (routers.size() != 1) {
		delete_extra_routers(edges, vertexes, clients, routers);
	}

	long max_for_point;
	std::vector<long> max(vertexes);
	std::pair<int, int> best_server;
	best_server.first = 0;
	best_server.second = INF;
	for (int router : routers) {
		std::vector<int> distance(vertexes, INF), p(vertexes);
		distance[router] = 0;
		//std::vector<bool> u(vertexes);
		std::vector<int> path;

		dijkstras_algorithm(edges, vertexes, distance, p);
		
		for (int client : clients) {
			max_for_point = build_path(edges, vertexes, router, client, path, p);
			
			if (max[router] < max_for_point) {
				max[router] = max_for_point;
			}
			path.clear();
		}
		if (best_server.second > max[router]) {
			best_server.first = router + 1;
			best_server.second = max[router];
		}
	}
	//std::cout << "Best server position: " << best_server.first << std::endl;
	//std::cout << "The largest latency: " << best_server.second << std::endl;
	output_to_file(best_server);

	return 0;
}

void read_from_file(std::vector<std::vector<std::pair<int, int>>>& edges, int vertexes, std::vector<int>& clients, std::vector<int>& routers) {
	std::fstream f;
	int vert, first, second, third;
	std::string client;
	f.open("gamesrv.in", std::fstream::in);
	std::getline(f, client);
	std::getline(f, client);
	std::istringstream row(client);
	for (int i = 0; i < vertexes; i++) {
		routers.push_back(i);
	}
	while (row >> vert) {
		clients.push_back(vert - 1);
		routers.erase(std::remove(routers.begin(), routers.end(), vert - 1), routers.end());
	}
	int counter = 0;
	std::pair<int, int> pairs_to;
	std::pair<int, int> pairs_reverse;
	while (!f.eof()) {
		f >> first >> second >> third;
		pairs_to.first = second - 1;
		pairs_reverse.first = first - 1;
		pairs_to.second = third;
		pairs_reverse.second = third;
		edges[first - 1].push_back(pairs_to);
		edges[second - 1].push_back(pairs_reverse);
		f.get();
	}
	f.close();
}

void delete_extra_routers(std::vector<std::vector<std::pair<int, int>>>& edges, int vertexes, std::vector<int>& clients, std::vector<int>& routers) {
	bool for_delete;
	for (int i = 0; i < vertexes; i++) {
		for_delete = true;
		for (std::pair<int, int> j : edges[i]) {
			if (std::find_if(clients.begin(), clients.end(), [&j](const int& element) { return element == j.first; }) == clients.end()) {
				for_delete = false;
				break;
			}
		}
		if (for_delete) {
			for (std::pair<int, int> j : edges[i]) {
				edges[j.first].erase(std::remove_if(edges[j.first].begin(), edges[j.first].end(), [&i](const std::pair<int, int> element) { return element.first == i; }), edges[j.first].end());
			}
			edges[i].clear();
			routers.erase(std::remove(routers.begin(), routers.end(), i), routers.end());
		}
	}
}

void dijkstras_algorithm(std::vector<std::vector<std::pair<int, int>>>& edges, int vertexes, std::vector<int>& distance, std::vector<int>& p) {
	std::vector<bool> visited(vertexes);
	for (int i = 0; i < vertexes; i++) {
		int v = -1;
		for (int j = 0; j < vertexes; ++j) {
			if (!visited[j] && (v == -1 || distance[j] < distance[v]))
				v = j;
		}
		visited[v] = true;
		int j = 0;
		for (int j = 0; j < edges[v].size(); j++) {
			int to = edges[v][j].first,
				len = edges[v][j].second;
			if (distance[v] + len < distance[to]) {
				distance[to] = distance[v] + len;
				p[to] = v;
			}
		}
	}
}

long build_path(std::vector<std::vector<std::pair<int, int>>>& edges, int vertexes, int router, int client, std::vector<int>& path, std::vector<int>& p) {
	long max_for_point = 0;
	for (int v = client; v != router; v = p[v]) {
		path.push_back(v + 1);
	}
	path.push_back(router + 1);
	reverse(path.begin(), path.end());
	for (int i = 0; i < path.size(); i++) {
		if (path[path.size() - 1] != path[i]) {
			auto it = std::find_if(edges[path[i] - 1].begin(), edges[path[i] - 1].end(), [&path, &i](const std::pair<int, int> element) { return element.first == (path[i + 1] - 1); });
			max_for_point += (*it).second;
			//std::cout << max_for_point << std::endl;
		}
		//std::cout << path[i] << " ";
	}
	//std::cout << std::endl << max_for_point << std::endl;
	return max_for_point;
}

void output_to_file(std::pair<int, int>& best_server) {
	std::fstream f;
	f.open("gamesrv.out", std::fstream::out);
	f << best_server.second;
	f.close();
}
