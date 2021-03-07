#include <string>
#include <vector>
#include <random>
#include <iostream>
#include <chrono>
#include <thread>

class Arithmetic final
{
	const int array_number_size = 100;
	const int number_of_examples_until_result_ = 10;
	std::string types;
	std::vector<int> container_of_left_numbers;
	std::vector<int> container_of_right_numbers;

	time_t stvec_ = 0;
	time_t etvec_ = 0;
	time_t dtvec_ = 0;

	size_t rights = 0;
	size_t wrongs = 0;
	int range_ = 11;
	int turn_ = 0;
	int dif_operations_numb_ = 0;

	std::random_device rand_device;
	std::mt19937 rand_engine = std::mt19937(rand_device());

	void game();
	void check_answer(int ans, int i, int j);
	void score();

	size_t random_in_range(size_t range);
	size_t skrand(size_t range);
public:
	Arithmetic();

	void start(int argc = 0, char** argv = nullptr);
};