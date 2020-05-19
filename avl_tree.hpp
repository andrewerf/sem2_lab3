#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include <utility>
#include <stdexcept>


template <typename T, typename V>
class AVL_Tree {
public:
	AVL_Tree() :
		_root(nullptr),
		_size(0)
	{}

	template<typename ...Args>
	AVL_Tree(Args&& ...args);


	template<typename TT, typename VV>
	void insert(TT&& key, VV&& val);

	template<typename TT>
	void erase(TT&& key) {_root = _remove(_root, std::forward<TT>(key));}

	template<typename TT>
	V& get(TT&& key) {return _get(_root, std::forward<TT>(key))->val;}

	template<typename TT>
	const V& get(TT&& key) const {return _get(_root, std::forward<TT>(key))->val;}

	template<typename TT>
	bool find(TT&& key) const {return _find(_root, std::forward<TT>(key)) != nullptr;}

	template<typename TT>
	V& operator[] (TT&& key);

	template<typename TT>
	const V& operator[] (TT&& key) const {return get(std::forward<TT>(key));}


	size_t size() const {return _size;}
	int height() const {return _root->height;}

private:
	struct Node {
	public:
		template<typename TT, typename VV>
		Node(TT&& k, VV&& v):
			key(std::forward<TT>(k)),
			val(std::forward<VV>(v)),
			height(1),
			left(nullptr),
			right(nullptr)
		{}


		T key;
		V val;
		unsigned int height;
		Node *left, *right;
	};


	int _height(Node *p) const;

	void _fixheight(Node *p);

	int _factor(Node *p) const;

	Node *_rotate_right(Node *p);

	Node *_rotate_left(Node *q);

	Node *_balance(Node *p);

	template<typename TT>
	Node *_find(Node *p, TT&& key) const;

	Node *_find_min(Node *p) const;

	Node *_remove_min(Node *p);

	template<typename TT>
	Node *_remove(Node *p, TT&& k);

	template<typename TT, typename VV>
	Node *_insert(Node *p, TT&& k, VV&& val);

	template<typename TT>
	Node *_get(Node *p, TT&& k) const;

private:
	template<typename FV, typename ...Args>
	void _list_initializer(FV&& p, Args&& ...args);
	void _list_initializer(){}

	Node *_root;
	size_t _size;
};



template <typename T, typename V>
template <typename ...Args>
AVL_Tree<T, V>::AVL_Tree(Args&& ...args):
	AVL_Tree()
{
	_list_initializer(std::forward<Args>(args)...);
}


template <typename T, typename V>
template<typename TT, typename VV>
void AVL_Tree<T,V>::insert(TT&& key, VV&& val)
{
	if(_root == nullptr){
		_root = new Node(std::forward<TT>(key), std::forward<VV>(val));
	}
	else{
		_root = _insert(_root, std::forward<TT>(key), std::forward<VV>(val));
	}

	++_size;
}

template <typename T, typename V>
template<typename TT>
V& AVL_Tree<T,V>::operator[](TT&& key)
{
	if(!find(key)){
		insert(std::forward<TT>(key), V());
	}

	return get(std::forward<TT>(key));
}

template <typename T, typename V>
template <typename FV, typename ...Args>
void AVL_Tree<T, V>::_list_initializer(FV&& p, Args&& ...args)
{
	insert(std::forward<typename FV::first_type>(p.first),
		   std::forward<typename FV::second_type>(p.second));

	_list_initializer(std::forward<Args>(args)...);
}




template <typename T, typename V>
int AVL_Tree<T,V>::_height(Node *p) const{
	return p ? p->height : 0;
}

template <typename T, typename V>
void AVL_Tree<T,V>::_fixheight(Node *p){
	p->height = std::max(_height(p->left), _height(p->right)) + 1;
}

template <typename T, typename V>
int AVL_Tree<T,V>::_factor(Node *p) const {
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
template<typename TT>
typename AVL_Tree<T,V>::Node *AVL_Tree<T,V>::_find(Node *p, TT&& key) const
{
	if(p == nullptr)
		return nullptr;
	if(key == p->key)
		return p;
	if(key < p->key)
		return _find(p->left, std::forward<TT>(key));
	if(key > p->key)
		return _find(p->right, std::forward<TT>(key));
}

template<typename T, typename V>
typename AVL_Tree<T,V>::Node *AVL_Tree<T,V>::_find_min(Node *p) const
{
	return p->left ? _find_min(p->left) : p;
}

template<typename T, typename V>
typename AVL_Tree<T,V>::Node *AVL_Tree<T,V>::_remove_min(Node *p)
{
	if(p->left == nullptr)
		return p->right;
	p->left = _remove_min(p->left);
	return _balance(p);
}

template<typename T, typename V>
template<typename TT>
typename AVL_Tree<T,V>::Node *AVL_Tree<T,V>::_remove(Node *p, TT&& k)
{
	if(p == nullptr)
		throw std::out_of_range("AVL_Tree out of range!");
	if(k < p->key)
		p->left = _remove(p->left, std::forward<TT>(k));
	else if(k > p->key)
		p->right = _remove(p->right, std::forward<TT>(k));
	else
	{
		Node *q = p->left;
		Node *r = p->right;
		delete p;

		if(r == nullptr)
			return q;

		Node *m = _find_min(r);
		m->right = _remove_min(r);
		m->left = q;
		return _balance(m);
	}
}


template <typename T, typename V>
template <typename TT, typename VV>
typename AVL_Tree<T,V>::Node *AVL_Tree<T,V>::_insert(Node *p, TT&& k, VV&& val)
{
	if(p == nullptr)
		return new Node(std::forward<TT>(k), std::forward<VV>(val));
	if(p->key == k)
		p->val = val;
	if(k < p->key)
		p->left = _insert(p->left, std::forward<TT>(k), std::forward<VV>(val));
	else
		p->right = _insert(p->right, std::forward<TT>(k), std::forward<VV>(val));

	_fixheight(p);
	return _balance(p);
}

template <typename T, typename V>
template <typename TT>
typename AVL_Tree<T,V>::Node *AVL_Tree<T,V>::_get(Node *p, TT&& k) const
{
	if(p == nullptr)
		throw std::out_of_range("AVL_Tree out of range!");
	if(k == p->key)
		return p;
	if(k < p->key)
		return _get(p->left, k);
	else
		return _get(p->right, k);
}




#endif
