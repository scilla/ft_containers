#ifndef RBTREE_HPP
#define RBTREE_HPP

class rbtree
{
private:
	typename struct node {
		struct node* 	left;
		struct node* 	right;
		struct node*	parent;
		bool			black;
	}
public:
	rbtree(/* args */);
	~rbtree();
};

rbtree::rbtree(/* args */)
{
}

rbtree::~rbtree()
{
}


#endif /* RBTREE_HPP */
