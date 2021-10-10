#include "../common.hpp"
#include <iostream>
int main()
{
	clock_t t;
	clock_t ft_time;
	clock_t std_time;

	{
		ft::vector<std::string>	vec1;
		t = clock();
		for (int i = 0; i < 10; ++i)
			vec1.insert(vec1.begin(), 100, "string");
		ft_time = clock() - t;
		std::vector<std::string>	vec2;
		t = clock();
		for (int i = 0; i < 10; ++i)
			vec2.insert(vec2.begin(), 100, "string");
		std_time = clock() - t;
		efficiency_output(ft_time, std_time);
	}
	return 0;
}
