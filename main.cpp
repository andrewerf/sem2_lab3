#include <iostream>
#include <string>
#include <vector>

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
	AVL_Tree<int, string> Tree = {
		std::make_pair(0, "lalal"),
		std::make_pair(1, "djksfjl")
	};
	Tree[3] = "lol2";
	Tree.erase(0);

//	for(int i = 0; i < 1024; ++i)
//		Tree.insert(i, std::to_string(2*i));

	cout << Tree.get(3);
//	bfs_show(root);

	return 0;
}
