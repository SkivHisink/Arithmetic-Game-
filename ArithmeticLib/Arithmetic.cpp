#include "Arithmetic.hpp"
namespace {
	template<class arg, class result>
	struct Unary_function
	{
		typedef arg argument_type;
		typedef result result_type;
	};
	struct Increment : Unary_function<int&, void>
	{
		int value;

		Increment() : value(0) {}

		void operator()(int& val) { val = value++; }
	};
}

Arithmetic::Arithmetic()
{
	container_of_left_numbers.assign(array_number_size, 0);
	std::for_each(container_of_left_numbers.begin(), container_of_left_numbers.end(), Increment());
	container_of_right_numbers = container_of_left_numbers;
}

void Arithmetic::start(int argc, char** argv)
{
	while (argc > 1)
	{
		if (argv != nullptr) {
			switch (*argv[1])
			{
			case '+':
			case '-':
			case 'x':
			case '/':
				while (true) {
					types.push_back(argv[1][dif_operations_numb_]);
					++dif_operations_numb_;
					if (!argv[1][dif_operations_numb_]) { break; }
				}
				break;

			default:
				range_ = std::stoi(argv[1]) + 1;
			}
			argv++;
			argc--;
		}
	}
	if (range_ > array_number_size) { 
		std::cout << "Range is too large." << std::endl;
		exit(0);
	}

	if (dif_operations_numb_ == 0) {
		types.push_back('+');
		types.push_back('-');
		dif_operations_numb_ = 2;
	}
	time(&stvec_);
	turn_ = 0;
	game();
}

void Arithmetic::game()
{
	size_t numb_of_oper_ = 0;

	if (dif_operations_numb_ > 1) { numb_of_oper_ = random_in_range(dif_operations_numb_); }
	
	size_t temp;
	size_t i = skrand(range_);
	size_t j = skrand(range_);
	int ans;

	switch (types[numb_of_oper_]) {
	case '+':
	default:
		ans = container_of_left_numbers[i] + container_of_right_numbers[j];
		std::cout << container_of_left_numbers[i] << " + " << container_of_right_numbers[j] << " =   ";
		break;

	case '-':
		temp = container_of_left_numbers[i] + container_of_right_numbers[j];
		ans = container_of_left_numbers[i];
		printf("%d - %d =   ", temp, container_of_right_numbers[j]);
		break;

	case 'x':
		ans = container_of_left_numbers[i] * container_of_right_numbers[j];
		std::cout << container_of_left_numbers[i] << " x " << container_of_right_numbers[j] << "%d =   ";
		break;

	case '/':
		while (container_of_left_numbers[j] == 0) { j = random_in_range(range_); }
		temp = container_of_left_numbers[i] * container_of_right_numbers[j] + random_in_range(container_of_right_numbers[j]);
		ans = container_of_left_numbers[i];
		std::cout << temp << " / " << container_of_right_numbers[j] << " =   ";
		break;
	}
	check_answer(ans, i, j);
}

void Arithmetic::check_answer(int ans, int i, int j)
{
	std::string line_;
	std::cin >> line_;
	dtvec_ += etvec_ - stvec_;
	if (line_[0] == '\n') check_answer(ans, i, j);
	int pans;
	pans = std::stoi(line_);
	if (pans == ans) {
		std::cout << "Right!" << std::endl;
		++rights;
		(++turn_ % number_of_examples_until_result_ == 0) ? score() : game();
		game();
	}
	else {
		std::cout << "What?" << std::endl;
		++wrongs;
		if (range_ >= array_number_size) check_answer(ans, i, j);
		container_of_left_numbers[range_] = container_of_left_numbers[i];
		container_of_left_numbers[++range_] = container_of_right_numbers[j];
		check_answer(ans, i, j);
	}
}

void Arithmetic::score()
{
	time(&etvec_);

	std::cout << std::endl << std::endl << "rights " << rights << "; Wrongs " << wrongs << "; Score " << static_cast<double>(rights) * 100 / (static_cast<double>(wrongs) + rights) << "%" << std::endl;
	const double spp = (rights == 0) ? 0 : static_cast<double>(etvec_ - stvec_) / rights;
	std::cout << "Total time " << etvec_ - stvec_ << " seconds; " << spp << " seconds per problem";
	for (int m = 0; m < 3; ++m) { std::cout << std::endl; }
	std::chrono::milliseconds timespan(3000);
	std::this_thread::sleep_for(timespan);

	time(&dtvec_);
	stvec_ += dtvec_ - etvec_;
}

size_t Arithmetic::random_in_range(size_t range)
{
	return static_cast<size_t>(rand_engine()) % range;
}

size_t Arithmetic::skrand(size_t range)
{
	const size_t temp = random_in_range(range) + random_in_range(range);
	return temp > range - 1 ? 2 * range - 1 - temp : temp;
}