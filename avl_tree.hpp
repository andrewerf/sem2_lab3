#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

template <typename T>
T max(T&& a, T&& b){
	return a > b ? a : b;
}


struct Node {
public:
	Node(int k):
		key(k),
		height(1),
		left(nullptr),
		right(nullptr)
	{}
//	Node(int k, Node *l, Node *r):
//		key(k),
//		height(max(l->height, r->height) + 1),
//		left(l),
//		right(r)
//	{}

//	int factor(){
//		return left->height - right->height;
//	}

	int key;
	unsigned int height;
	int val;
	Node *left, *right;
};

int height(Node *p){
	return p ? p->height : 0;
}

void fixheight(Node *p){
	p->height = max(height(p->left), height(p->right)) + 1;
}

int factor(Node *p){
	return height(p->right) - height(p->left);
}


Node *rotate_right(Node *p)
{
	Node *q = p->left;
	p->left = q->right;
	q->right = p;

	fixheight(p);
	fixheight(q);

	return q;
}

Node *rotate_left(Node *q)
{
	Node *p = q->right;
	q->right = p->left;
	p->left = q;

	fixheight(q);
	fixheight(p);

	return p;
}


Node *balance(Node *p)
{
	fixheight(p);

	if(factor(p) == 2)
	{
		if(factor(p->right) < 0)
			p->right = rotate_right(p->right);

		p = rotate_left(p);
	}
	else if(factor(p) == -2)
	{
		if(factor(p->left) > 0)
			p->left = rotate_left(p->left);

		p = rotate_right(p);
	}

	return p;
}


Node *insert(Node *p, int k)
{
	if(p == nullptr){
		return new Node(k);
	}
	if(k < p->key)
		p->left = insert(p->left, k);
	else
		p->right = insert(p->right, k);

	fixheight(p);
	return balance(p);
}


#endif

