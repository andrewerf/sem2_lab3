#include <iostream>
#include <string>
#include <vector>
#include <tuple>

#include "avl_tree.hpp"

using namespace std;


//void bfs_show(Node *t)
//{
//	vector<Node*> wave;
//	wave.push_back(t);

//	int ll = 0;
//	for(size_t i = 0; i < wave.size(); ++i){
//		auto node = wave[i];
//		if(ll != height(node)){
//			cout << '\n';
//			ll = height(node);
//		}

//		if(node == nullptr){
//			cout << "NULL";
//		}
//		else{
//			cout << node->key;
//			wave.push_back(node->left);
//			wave.push_back(node->right);
//		}
//		cout << "	";
//	}
//}


int main()
{
	AVL_Tree<int, string> Tree, Tree2;

	for(int i = 0; i < 15; ++i)
		Tree[i] = std::to_string(i);

	Tree2 = Tree;

	Tree2 = map<int,string>(Tree2, [](string &s){
		return "-" + s;
	});

	Tree2.traversal(Tree2.RRtL, [](const int &a, string &b){
		std::cout << b << ' ';
	});
	cout << '\n';
	Tree.traversal(Tree.RRtL, [](const int &a, string &b){
		std::cout << b << ' ';
	});
	return 0;
}
