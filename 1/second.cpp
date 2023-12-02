#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <iostream>
#include <algorithm>

int main()
{
	std::ifstream file{"input.txt"};
	std::vector<std::string> lines{};

	std::copy(std::istream_iterator<std::string>(file), std::istream_iterator<std::string>(), std::back_inserter(lines));
	file.close();

	int sum{};
	std::vector<std::pair<std::string, std::string>> valid_digits{{"1", "one"},
																									 							{"2", "two"},
																									 							{"3", "three"},
																									 							{"4", "four"},
																									 							{"5", "five"},
																																{"6", "six"},
																																{"7", "seven"},
																									 							{"8", "eight"},
																									 							{"9", "nine"}};
	
	std::for_each(lines.begin(), lines.end(), [&sum, valid_digits](std::string& line) {

		std::pair<int, int> first_digit{line.size(), -1};
		std::pair<int, int> last_digit{-1, -1};

		for (int i{}; i < int(valid_digits.size()); i++)
		{
			int first_pos = std::min(line.size(), std::min(line.find(valid_digits[i].first), line.find(valid_digits[i].second)));
			int last_pos = std::max(int(line.rfind(valid_digits[i].first)), int(line.rfind(valid_digits[i].second)));
			first_digit = std::min(first_digit, {first_pos, i+1});
			last_digit = std::max(last_digit, {last_pos, i+1});
		}

		if (first_digit.first != int(line.size()))
			sum += first_digit.second * 10 + last_digit.second;
	});

	std::cout << "Sum: " << sum << std::endl;

	return 0;
}