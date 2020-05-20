#include <random>

#include "sem2_lab2/tests.h"
#include <algorithm> //for std::sort
#include "avl_tree.hpp"
#include "priority_queue.hpp"


int randint(int a, int b)
{
	static std::random_device rand_dev;
	static std::mt19937 generator(rand_dev());
	std::uniform_int_distribution<int>  distr(a, b);

	return distr(generator);
}


void test_avl_tree_basics()
{
	//test list-or-pairs constructor
	AVL_Tree<int, int> tree = {
		std::make_pair(-1, 1),
		std::make_pair(-2, 2)
	};

	//test copy-constructor
	AVL_Tree<int, int> tree2 = tree;
	tree.get(-1) = -1;

	assert_equal(tree2.get(-1), 1);
	assert_equal(tree2.get(-2), 2);
	assert_equal(tree.get(-1), -1);

	//test move-constructor
	tree2 = std::move(tree);
	assert_equal(tree.size(), 0);
	assert_equal(tree2.get(-1), -1);
	assert_equal(tree2.get(-2), 2);
}

void test_avl_tree_sort()
{
	AVL_Tree<int, int> tree;

	size_t n = randint(10, 100);
	for(size_t i = 0; i < n; ++i) {
		auto t = randint(0, 2*n);
		tree[t] = t;
	}

	//traversal is used to get a sorted sequence from tree
	int last = -1;
	tree.traversal(tree.LRtR, [&last](auto k, auto v){
		assert_equal(v > last, true);
		last = v;
	});

	//different types of traversal for ascending and descending order
	++last;
	tree.traversal(tree.RRtL, [&last](auto k, auto v){
		assert_equal(v < last, true);
		last = v;
	});
}

void test_avl_tree_map()
{
	size_t n = randint(10, 100);
	AVL_Tree<int, int> tree;
	int *array = new int[n];
	bool *used = new bool[2*n];
	for(size_t i = 0; i < 2*n; ++i)
		used[i] = false;

	for(size_t i = 0; i < n; ++i) {
		auto t = randint(0, 2*n);
		if(used[t]) {
			i--;
			continue;
		}
		used[t] = true;
		tree[t] = t;
		array[i] = t;
	}

	std::sort(&array[0], &array[0] + n);
	for(size_t i = 0; i < n; ++i)
		array[i] *= array[i];

	size_t i = 0;
	tree = map(tree, [](auto v){
		return v*v;
	});

	tree.traversal(tree.LRtR, [&array, &i](auto k, auto v){
		assert_equal(array[i++], v);
	});
}

void test_avl_tree_where()
{
	size_t n = randint(10, 100);
	if(n % 2 == 1)
		++n;

	AVL_Tree<int, int> tree;
	int *array = new int[n / 2];

	for(size_t i = 0; i < n; ++i) {
		tree[i] = i;
		if(i >= n / 2)
			array[i - n/2] = i;
	}

	tree = where(tree, [n](const auto v){
		return v >= n / 2;
	});

	size_t i = 0;
	tree.traversal(tree.LRtR, [&array, &i](auto k, auto v){
		assert_equal(array[i++], v);
	});
}


void test_priority_queue()
{
	PriorityQueue<int> queue;

	queue.push(0, 0);
	queue.push(1, 1);
	queue.push(2, 2);
	queue.push(3, 3);

	int i = 0;
	while(!queue.empty())
		assert_equal(3 - (i++), queue.pop());

	assert_equal(i, 4);
}


int main()
{
	TestFunction<void> functions[] = {
		{"avl_tree_basics", test_avl_tree_basics},
		{"avl_tree_sort", test_avl_tree_sort},
		{"avl_tree_map", test_avl_tree_map},
		{"avl_tree_where", test_avl_tree_where},

		{"priority_queue", test_priority_queue}
	};

	run_tests(functions, sizeof(functions) / sizeof (TestFunction<void>));
}