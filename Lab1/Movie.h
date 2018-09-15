#ifndef __MOVIE_H_INCLUDED__
#define __MOVIE_H_INCLUDED__

#include <string>
#include <fstream>

class Movie
{
private:
	void merge_algorithm(Movie* arr, int start, int mid, int end, int* comp_swap);
public:
	std::string name;
	int during_min;
	int feedback_iMDb;

	Movie();
	Movie(std::string name, int during_min, int feedback_iMDb);
	~Movie();

	void reversed_insertion(Movie* arr, int size, int* comp_swap);
	void merge(Movie* arr, int start, int end, int* comp_swap);
	void input_movies_array(std::fstream &file, Movie* movie, int size);
	void output_result(Movie* movies, int size, std::string algo, int runtime, int comp, int swap);
};

#endif