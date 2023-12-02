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

	int sum_games{};

	for (std::string line : game_strings)
	{
		line.erase(line.size()-1);

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

		int red_min{};
		int green_min{};
		int blue_min{};

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

				if (color == "red" && amount > red_min)
					red_min = amount;
				else if (color == "green" && amount > green_min)
					green_min = amount;
				else if (color == "blue" && amount > blue_min)
					blue_min = amount;
			}
		}

		int power{red_min * green_min * blue_min};
		sum_games += power;
	}

	std::cout << "Sum: " << sum_games << std::endl;

	return 0;
}