#include <chrono>
#include <iostream>
#include "plotting/matplotlibcpp.h"

namespace plt = matplotlibcpp;


int main()
{
	plt::xlim(-10, 100);
	plt::ylim(-10, 100);

	std::vector<int> x(100);
	std::iota(x.begin(), x.end(), 0);
	plt::plot(x, [](int x){
		return sin(x)*sin(x)*100;
	}, "r");

	plt::show();
}