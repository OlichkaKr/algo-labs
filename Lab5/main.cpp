#include <fstream>
#include <vector>
#include <iostream>
#include <cmath>
#include <chrono>

const bool MIN = false;
const bool MAX = true;

int read_from_file(std::vector<int>& heights);
void write_to_file(double max_distance);
double calculate_distance(int x, int y1, int y2);
void from_min_or_max(std::vector<int>& heights, std::vector<std::vector<bool>>& min_and_max, std::vector<double>& temporary_distance, 
					int distance, unsigned iterator);

int main() {
	auto start_time = std::chrono::high_resolution_clock::now();
	std::vector<int> heights;
	std::vector<double> temporary_distance;
	std::vector<std::vector<bool>> min_and_max;;
	std::vector<int> next_heights;
	double max_distance = 0;
	int distance = read_from_file(heights);
	if (heights.size() == 2) {
		double max_min = calculate_distance(distance, heights[0], 1);
		double min_max = calculate_distance(distance, 1, heights[1]);
		if (max_min > min_max) {
			write_to_file(max_min);
			return 0;
		}
		else {
			write_to_file(min_max);
			return 0;
		}
	}
	if (heights.size() == 3) {
		from_min_or_max(heights, min_and_max, temporary_distance, distance, 0);
		write_to_file(temporary_distance[0]);
		return 0;
	}
	for (unsigned i = 0; i < heights.size() - 2; i++) {
		from_min_or_max(heights, min_and_max, temporary_distance, distance, i);
		if (i != 0) {
			if (min_and_max[i - 1][1] == min_and_max[i][0] && min_and_max[i - 1][2] == min_and_max[i][1]) {
			}
			else {
				if (min_and_max[i][1]) {
					double min_max_max = calculate_distance(distance, 1, heights[i]);
					double max_max_min = calculate_distance(distance, heights[i], heights[i + 1]);
					min_max_max += max_max_min;
					max_max_min += calculate_distance(distance, heights[i + 1], 1);
					min_and_max[i - 1][2] = MAX;
					min_and_max[i][0] = MAX;
					temporary_distance[i - 1] = min_max_max;
					temporary_distance[i] = max_max_min;
				}
				else {
					double min_min_max = calculate_distance(distance, 1, 1);
					double max_min_min = calculate_distance(distance, heights[i - 1], 1);
					max_min_min += min_min_max;
					min_min_max += calculate_distance(distance, 1, heights[i + 2]);
					min_and_max[i - 1][2] = MIN;
					min_and_max[i][0] = MIN;
					temporary_distance[i - 1] = max_min_min;
					temporary_distance[i] = min_min_max;
				}
				
			}
			if (i % 2 == 0 && i != 1) {
				max_distance += temporary_distance[i - 2];
			}
		}
	}
	if (heights.size() % 2 == 0) {
		if (min_and_max[min_and_max.size() - 1][2]) {
			max_distance += calculate_distance(distance, 1, heights[heights.size() - 1]);
		}
		else {
			max_distance += calculate_distance(distance, heights[heights.size() - 2], 1);
		}
	}
	else {
		max_distance += temporary_distance[temporary_distance.size() - 1];
	}
	write_to_file(max_distance);
	auto end_time = std::chrono::high_resolution_clock::now();
	auto search_time = std::chrono::duration_cast<std::chrono::microseconds> (end_time - start_time);
	std::cout << search_time.count() << std::endl;
	system("pause");
	return 0;
}

int read_from_file(std::vector<int>& heights) {
	int height;
	int distance;
	std::fstream f;
	f.open("electr.in", std::fstream::in);
	f >> distance;
	f.get();
	while (f >> height) {
		heights.push_back(height);
	}
	f.close();
	return distance;
}

void write_to_file(double max_distance) {
	std::fstream f;
	f.open("electr.out", std::fstream::out);
	max_distance = floorf(max_distance * 100) / 100;
	f << max_distance;
	f.close();
}

double calculate_distance(int x, int y1, int y2) {
	return sqrt(pow(x, 2) + pow(fabs(y1 - y2), 2));
}

void from_min_or_max(std::vector<int>& heights, std::vector<std::vector<bool>>& min_and_max, std::vector<double>& temporary_distance, 
					int distance, unsigned iterator) {
	double max_min_max = calculate_distance(distance, heights[iterator], 1);
	max_min_max += calculate_distance(distance, 1, heights[iterator + 2]);
	double min_max_min = calculate_distance(distance, 1, heights[iterator + 1]);
	min_max_min += calculate_distance(distance, heights[iterator + 1], 1);
	min_and_max.push_back(std::vector<bool>());
	if (min_max_min > max_min_max) {
		min_and_max[iterator].push_back(MIN);
		min_and_max[iterator].push_back(MAX);
		min_and_max[iterator].push_back(MIN);
		temporary_distance.push_back(min_max_min);
	}
	else {
		min_and_max[iterator].push_back(MAX);
		min_and_max[iterator].push_back(MIN);
		min_and_max[iterator].push_back(MAX);
		temporary_distance.push_back(max_min_max);
	}
}
