#include "Movie.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

Movie::Movie(){}

Movie::Movie(std::string name, int during_min, int feedback_iMDb) {
	this->name = name;
	this->during_min = during_min;
	this->feedback_iMDb = feedback_iMDb;
}

Movie::~Movie()
{
}

void Movie::reversed_insertion(Movie* arr, int size, int* comp_swap) {
	int temp, j;
	for (int i = 1; i < size; i++) {
		temp = arr[i].feedback_iMDb;
		j = i - 1;
		comp_swap[0]++;
		while ((j >= 0) && (temp > arr[j].feedback_iMDb)) {
			comp_swap[1]++;
			std::swap(arr[j + 1].name, arr[j].name);
			std::swap(arr[j + 1].during_min, arr[j].during_min);
			std::swap(arr[j + 1].feedback_iMDb, arr[j].feedback_iMDb);
			j--;
		}
	}
}

void Movie::merge_algorithm(Movie* arr, int start, int mid, int end, int* comp_swap) {
	int size_left = mid - start + 1;
	int size_right = end - mid;
	Movie* left = new Movie[size_left];
	Movie* right = new Movie[size_right];
	for (int i = 0; i < size_left; i++) {
		left[i].name = arr[start + i].name;
		left[i].during_min = arr[start + i].during_min;
		left[i].feedback_iMDb = arr[start + i].feedback_iMDb;
	}
	for (int i = 0; i < size_right; i++) {
		right[i].name = arr[mid + i + 1].name;
		right[i].during_min = arr[mid + i + 1].during_min;
		right[i].feedback_iMDb = arr[mid + i + 1].feedback_iMDb;
	}

	int i = 0;
	int j = 0;
	int k = start;
	
	while (((i < size_left) && (++comp_swap[0])) && ((j < size_right) && (++comp_swap[0]))) {
		comp_swap[0]++;
		comp_swap[1]++;
		if (left[i].during_min <= right[j].during_min) {
			arr[k].name = left[i].name;
			arr[k].during_min = left[i].during_min;
			arr[k].feedback_iMDb = left[i].feedback_iMDb;
			i++;
		}
		else {
			arr[k].name = right[j].name;
			arr[k].during_min = right[j].during_min;
			arr[k].feedback_iMDb = right[j].feedback_iMDb;
			j++;
		}
		k++;
	}

	while ((i < size_left) && (++comp_swap[0])) {
		comp_swap[1]++;
		arr[k].name = left[i].name;
		arr[k].during_min = left[i].during_min;
		arr[k].feedback_iMDb = left[i].feedback_iMDb;
		i++;
		k++;
	}
	while ((j < size_right) && (++comp_swap[0])) {
		comp_swap[1]++;
		arr[k].name = right[j].name;
		arr[k].during_min = right[j].during_min;
		arr[k].feedback_iMDb = right[j].feedback_iMDb;
		j++;
		k++;
	}
	
	delete[] left;
	delete[] right;
}

void Movie::merge(Movie* arr, int start, int end, int* comp_swap) {
	if (start < end) {
		int mid = start + (end - start) / 2;
		merge(arr, start, mid, comp_swap);
		merge(arr, mid + 1, end, comp_swap);
		merge_algorithm(arr, start, mid, end, comp_swap);
	}

}

void Movie::input_movies_array(std::fstream &file, Movie* movie, int size) {
	std::string movie_info;
	int k;
	std::string splited_string[3];
	for (int i = 0; i < size; i++) {
		getline(file, movie_info);
		
		k = 0;
		splited_string[0] = "";
		splited_string[1] = "";
		splited_string[2] = "";
		for (unsigned int j = 0; j < movie_info.length(); j++) {
			if (movie_info[j] != ',') {
				splited_string[k] += movie_info[j];
			}
			else {
				k++;
			}
		}
		movie[i].name = splited_string[0];
		movie[i].during_min = std::stoi(splited_string[1]);
		movie[i].feedback_iMDb = std::stoi(splited_string[2]);
	}
}

void Movie::output_result(Movie* movies, int size, std::string algo, int runtime, int comp, int swap) {
	std::fstream file;
	file.open("result.txt", std::fstream::out | std::fstream::app);
	file << "--------------- " << algo << " ---------------" << std::endl;
	file << "Execution time is " << runtime << " ms" << std::endl;
	file << "Comparisons: " << comp << ", swaps: " << swap << std::endl;
	file << std::left << std::setw(25) << "NAME" << std::setw(10) << "DURATION" << std::setw(10) << "FEEDBACKS" << std::endl;
	for (int i = 0; i < size; i++) {
		file << std::left << std::setw(25) << movies[i].name << std::setw(10) << movies[i].during_min 
			<< std::setw(10) << movies[i].feedback_iMDb << std::endl;
	}
	file << std::endl;
	file.close();
}
