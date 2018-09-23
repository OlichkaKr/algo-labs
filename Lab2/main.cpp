#include <iostream>
#include <fstream>
#include <cstdlib>
#include <conio.h>

//int search_max_amount(int** hamster, int total_amount, int food);
int algo(int** hamster, int total_amount, int food);

int main() {
	std::fstream file;
	file.open("hamstr.in", std::fstream::in);
	if (!file.is_open())
	{
		std::cout << "Could not open the file 'movies.txt'" << std::endl;
		std::cout << "Program terminating.\n";
		exit(EXIT_FAILURE);
	}
	int food, total_amount;
	file >> food;
	file.get();
	file >> total_amount;
	file.get();

	int** hamster = new int*[total_amount];
	for (int i = 0; i < total_amount; i++) {
		hamster[i] = new int[2];
	}
	for (int i = 0; i < total_amount; i++) {
		file >> hamster[i][0] >> hamster[i][1];
		file.get();
	}
	file.close();

	int result = algo(hamster, total_amount, food);
	file.open("hamstr.out", std::fstream::out);
	file << result << std::endl;
	//_getch();

	for (int i = 0; i < total_amount; i++) {
		delete[] hamster[i];
	}
	delete[] hamster;
	file.close();
	
	return 0;
}

int search_worst(int** hamster, int total_amount, int max_amount) {
	int pos = 0;
	for (int i = 1; i < max_amount + 1; i++) {
		if ((hamster[pos][0] + hamster[pos][1] * max_amount) < (hamster[i][0] + hamster[i][1] * max_amount)) {
			pos = i;
		}
	}
	return pos;
}

int algo(int** hamster, int total_amount, int food) {
	int sum_food = 0;
	int sum_greed = 0;
	int max_amount = total_amount - 1;
	int worst = -1;
	for (int i = 0; i < total_amount; i++) {
		sum_food += hamster[i][0] + hamster[i][1] * (total_amount - 1);
		sum_greed += hamster[i][1];
	}
	while (sum_food > food) {
		sum_food -= sum_greed;
		worst = search_worst(hamster, total_amount, max_amount);
		sum_food -= (hamster[worst][0] + hamster[worst][1] * (max_amount - 1));
		sum_greed -= hamster[worst][1];
		std::swap(hamster[worst][0], hamster[max_amount][0]);
		std::swap(hamster[worst][1], hamster[max_amount][1]);
		max_amount--;
	}
	return max_amount + 1;
}

