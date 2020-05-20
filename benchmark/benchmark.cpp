#include <chrono>
#include <random>
#include <vector>
#include "3rdparty/plotting/matplotlibcpp.h"

#include "avl_tree.hpp"

namespace plt = matplotlibcpp;


template <typename Func, typename ...Args>
long long measure_time(Func f, Args&& ...args)
{
	auto start = std::chrono::high_resolution_clock::now();
	f(std::forward<Args>(args)...);
	auto stop = std::chrono::high_resolution_clock::now();

	return std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
}

template <typename Func, typename ...Args>
std::pair<std::vector<long long>,std::vector<double>> benchmark(long long from, long long to, long long step, Func f, Args&&... args)
{
	std::vector<long long> x;
	std::vector<double> y;
	x.reserve((to - from) / step);
	y.reserve((to - from) / step);

	for(long long n = from; n < to; n += step){
		x.push_back(n);
		double t = (double)measure_time(f, step, std::forward<Args>(args)...) / (double)step;
		y.push_back(t);
	}

	return {x,y};
}


void benchmark_insert(long long step, AVL_Tree<long long,long long> &tree)
{
	auto s = tree.size();
	for(long long i = s; i < s + step; ++i){
		tree[i] = i;
	}
}


int main()
{
	long long from = 1000, to = 1e8;

	plt::xlim((long long)from, (long long)to);
	plt::ylim(-5, 50);

	AVL_Tree<long long, long long> tree;
	benchmark_insert(from, tree);
	auto result = benchmark(from, to, 1000, benchmark_insert, tree);
	tree.clear();

	for (double &y : result.second)
		y *= 15;
	plt::plot(result.first, result.second);


	plt::show();
}