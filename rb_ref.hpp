 typedef struct s_node
 {
	struct s_node* left;
	struct s_node* right;
	struct s_node* parent;
 } node;
 
 enum Color {
	BLACK,
	RED
 };
 
 node* grandparent(node* n) {
	return n->parent->parent;
 }

 node* uncle(node* n) {
	if (n->parent == grandparent(n)->left)
		return grandparent(n)->right;
	else
		return grandparent(n)->left;
}

void insert_case1(node n) {
	if (n->parent == NULL)
		n->color = BLACK;
	else
		insert_case2(n);
}

	void insert_case2(node n) {
		 if (n->parent->color == BLACK)
				 return; /* Tree is still valid */
		 else
				 insert_case3(n);
 }

 void insert_case3(node n) {
		 if (uncle(n) != NULL && uncle(n)->color == RED) {
				 n->parent->color = BLACK;
				 uncle(n)->color = BLACK;
				 grandparent(n)->color = RED;
				 insert_case1(grandparent(n));
		 }
		 else
				 insert_case4(n);
 }

 void insert_case4(node n) {
		 if (n == n->parent->right && n->parent == grandparent(n)->left) {
				 rotate_left(n->parent);
				 n = n->left;
		 } else if (n == n->parent->left && n->parent == grandparent(n)->right) {
				 rotate_right(n->parent);
				 n = n->right;
		 }
				 insert_case5(n);
 }

	void insert_case5(node n) {
		 n->parent->color = BLACK;
		 grandparent(n)->color = RED;
		 if (n == n->parent->left && n->parent == grandparent(n)->left) {
				 rotate_right(grandparent(n));
		 } else {
				 /* Here, n == n->parent->right && n->parent == grandparent(n)->right */
				 rotate_left(grandparent(n));
		 }
 }