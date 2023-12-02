#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <fstream>

int main()
{
	std::ifstream file{"input.txt"};
	std::vector<std::string> game_strings{};

	std::string game{};
	while(std::getline(file, game))
	{
		game_strings.push_back(game);
	}
	file.close();

	const int red_max{12};
	const int green_max{13};
	const int blue_max{14};

	int sum_games{};

	for (std::string line : game_strings)
	{
		line.erase(line.size()-1);

		int id = std::stoi(line.substr(5, line.find(":")));

		line = line.substr(line.find(":") + 2);

		std::vector<std::string> sets{};
		std::string set{};

		auto delim{line.find(";")};
		while (delim != line.npos)
		{
			set = line.substr(0, delim);
			line = line.substr(delim + 2);

			sets.push_back(set);

			delim = line.find(";");
		}
		set = line;
		sets.push_back(set);

		bool game_valid{true};
		for (std::string set : sets)
		{
			std::vector<std::string> dices{};
			std::string dice{};
			delim = set.find(",");
			while(delim != set.npos)
			{
				dice = set.substr(0, delim);
				dices.push_back(dice);
				set = set.substr(delim + 2);
				delim = set.find(",");
			}
			dice = set;
			dices.push_back(dice);

			for (std::string dice : dices)
			{
				int amount{std::stoi(dice.substr(0, dice.find(" ")))};
				std::string color{dice.substr(dice.find(" ") + 1)};

				if (color == "red" && amount > red_max)
					game_valid = false;
				else if (color == "green" && amount > green_max)
					game_valid = false;
				else if (color == "blue" && amount > blue_max)
					game_valid = false;
			}
		}

		if (game_valid)
			sum_games += id;
	}

	std::cout << "Sum: " << sum_games << std::endl;

	return 0;
}