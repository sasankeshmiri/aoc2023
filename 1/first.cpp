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
	
	std::for_each(lines.begin(), lines.end(), [&sum](std::string& line) {
		std::string calibration_value{};
		auto first_digit{line.find_first_of("123456789")};
		auto last_digit{line.find_last_of("123456789")};
		if (first_digit != line.npos)
		{
			calibration_value += line.at(first_digit);
			calibration_value += line.at(last_digit);
		}
		sum += std::stoi(calibration_value);
	});

	std::cout << "Sum: " << sum << std::endl;

	return 0;
}