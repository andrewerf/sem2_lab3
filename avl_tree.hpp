#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP


template <typename T>
T max(T&& a, T&& b){
	return a > b ? a : b;
}

template <typename T, typename V>
class AVL_Tree {
public:
	AVL_Tree() :
		_root(nullptr)
	{}


	void insert(T key, V val);
	V& get(T key);

private:
	struct Node {
	public:
		Node(T k, V v):
			key(k),
			val(v),
			height(1),
			left(nullptr),
			right(nullptr)
		{}


		T key;
		V val;
		unsigned int height;
		Node *left, *right;
	};

	int _height(Node *p);

	void _fixheight(Node *p);

	int _factor(Node *p);

	Node *_rotate_right(Node *p);

	Node *_rotate_left(Node *q);

	Node *_balance(Node *p);

	Node *_insert(Node *p, T k, V val);

	Node *_get(Node *p, T k);

private:
	Node *_root;
};

template <typename T, typename V>
void AVL_Tree<T,V>::insert(T key, V val)
{
	if(_root == nullptr){
		_root = new Node(key, val);
	}
	else{
		_root = _insert(_root, key, val);
	}
}

template <typename T, typename V>
V& AVL_Tree<T,V>::get(T key)
{
	return _get(_root, key)->val;
}




template <typename T, typename V>
int AVL_Tree<T,V>::_height(Node *p){
	return p ? p->height : 0;
}

template <typename T, typename V>
void AVL_Tree<T,V>::_fixheight(Node *p){
	p->height = max(_height(p->left), _height(p->right)) + 1;
}

template <typename T, typename V>
int AVL_Tree<T,V>::_factor(Node *p){
	return _height(p->right) - _height(p->left);
}

template <typename T, typename V>
typename AVL_Tree<T,V>::Node *AVL_Tree<T,V>::_rotate_right(Node *p)
{
	Node *q = p->left;
	p->left = q->right;
	q->right = p;

	_fixheight(p);
	_fixheight(q);

	return q;
}

template <typename T, typename V>
typename AVL_Tree<T,V>::Node *AVL_Tree<T,V>::_rotate_left(Node *q)
{
	Node *p = q->right;
	q->right = p->left;
	p->left = q;

	_fixheight(q);
	_fixheight(p);

	return p;
}


template <typename T, typename V>
typename AVL_Tree<T,V>::Node *AVL_Tree<T,V>::_balance(Node *p)
{
	_fixheight(p);

	if(_factor(p) == 2)
	{
		if(_factor(p->right) < 0)
			p->right = _rotate_right(p->right);

		p = _rotate_left(p);
	}
	else if(_factor(p) == -2)
	{
		if(_factor(p->left) > 0)
			p->left = _rotate_left(p->left);

		p = _rotate_right(p);
	}

	return p;
}


template <typename T, typename V>
typename AVL_Tree<T,V>::Node *AVL_Tree<T,V>::_insert(Node *p, T k, V val)
{
	if(p == nullptr){
		return new Node(k, val);
	}
	if(k < p->key)
		p->left = _insert(p->left, k, val);
	else
		p->right = _insert(p->right, k, val);

	_fixheight(p);
	return _balance(p);
}

template<typename T, typename V>
typename AVL_Tree<T,V>::Node *AVL_Tree<T,V>::_get(Node *p, T k)
{
	if(p == nullptr){
		return nullptr;
	}
	if(k == p->key)
		return p;
	if(k < p->key)
		return _get(p->left, k);
	else
		return _get(p->right, k);
}


#endif

