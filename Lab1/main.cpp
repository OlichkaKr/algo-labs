#include <iostream>
#include <conio.h>
#include "Movie.h"
#include <fstream>
#include <cstdlib>
#include <chrono>

int main() {
	std::fstream file;
	file.open("movies.txt", std::fstream::in);
	if (!file.is_open()) {
		std::cout << "Could not open the file 'movies.txt'" << std::endl;
		std::cout << "Program terminating." << std::endl;
		exit(EXIT_FAILURE);
	}

	int size;
	file >> size;
	file.get();
	
	Movie* movie = new Movie[size];
	movie->input_movies_array(file, movie, size);
	file.close();

	int* comp_swap = new int[2]{ 0, 0 };

	std::string algorithm = "Insertion";
	auto start_time = std::chrono::high_resolution_clock::now();
	movie->reversed_insertion(movie, size, comp_swap);
	auto end_time = std::chrono::high_resolution_clock::now();
	auto search_time = std::chrono::duration_cast<std::chrono::microseconds> (end_time - start_time);
	movie->output_result(movie, size, algorithm, search_time.count(), comp_swap[0], comp_swap[1]);

	algorithm = "Merge";
	comp_swap[0] = 0;
	comp_swap[1] = 0;
	start_time = std::chrono::high_resolution_clock::now();
	movie->merge(movie, 0, size - 1, comp_swap);
	end_time = std::chrono::high_resolution_clock::now();
	search_time = std::chrono::duration_cast<std::chrono::microseconds> (end_time - start_time);
	movie->output_result(movie, size, algorithm, search_time.count(), comp_swap[0], comp_swap[1]);
	//_getch();
	
	delete[] comp_swap;
	delete[] movie;
	return 0;
}