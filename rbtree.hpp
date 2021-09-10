#ifndef RBTREE_HPP
#define RBTREE_HPP

namespace ft
{
template <class T>
struct node {
	struct node* 	left;
	struct node* 	right;
	struct node*	parent;
	bool			black;
};

class rbtree
{
private:
	node*	_root;
public:
	rbtree(/* args */);
	~rbtree();
};
} // namespace ft

#endif /* RBTREE_HPP */
