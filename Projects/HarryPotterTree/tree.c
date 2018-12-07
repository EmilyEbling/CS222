/*
These functions are operations for a binary search tree. They will be used as helper methos throughout the main program.
*/
void findMin(Student* rParent, Student* rChild);

void insert(Student** root, Student* node) { //adds a student to the tree in the proper location
	
	if (*root == NULL) //if the tree is empty, make the root the node
		*root = node;
	
	else if (strcmp(node->last, (*root)->last) < 0) //if the node's last name comes before the root's last name move to the left
		insert(&(*root)->left, node);

	else if (strcmp(node->last, (*root)->last) > 0) //if the nodes's last name comes after the root's last name move to the right
		insert(&(*root)->right, node);

	else { //if the two last names are equal
		if (strcmp(node->first, (*root)->first) < 0) //if the node's first name comes before the root's first name move to the left
			insert(&(*root)->left, node);

		else if (strcmp(node->first, (*root)->first) > 0) //if the node's first name comes after the root's first name move to the right
			insert(&(*root)->right, node);
	}	


}

Student* search(Student* root, char* first, char* last) { //searches for a student in the tree
	
	if (root == NULL) //returns null if the tree is empty
		return NULL;

	else if (strcmp (last, root->last) < 0) //if the last name comes before the root's last name move to the left
		return search(root->left, first, last);

	else if (strcmp (last, root->last) > 0) //if the last name comes after the root's last name move to the right
		return search(root->right, first, last);

	else { //if the last names are equal
		if (strcmp(first, root->first) < 0) //if the first name comes before the root's first name move to the left
			return search(root->left, first, last);

		else if (strcmp(first, root->first) > 0) //if the first name comes after the root's first name move to the right
			return search(root->right, first, last);

		return root; //return found student
	}

	
}

Student* delete(Student** root, char* first, char* last) {

	Student* student = *root; //keep track of current location

	if (*root == NULL) //if empty
		return *root;

	else if (strcmp(last, student->last) < 0) //if the last name comes before the root's last name move to the left of the tree
		return delete(&(*root)->left, first, last);

	else if (strcmp(last, student->last) > 0) //if the last name comes after the root's last name move to the right of the tree
		return delete(&(*root)->right, first, last);
	
	else { //if the last names are identical the first names must be checked
		
		if (strcmp(first, student->first) < 0) //if the first name comes before the root's first name move to the left of the tree
			return delete(&(*root)->left, first, last);

		else if (strcmp(first, student->first) > 0) //if the first name comes after the root's first name move to the right of the tree
			return delete(&(*root)->right, first, last);
	
		else { //if you found the student that needs to be deleted

			if ((*root)->left == NULL)  //if the root does not have a left child, change the root to be the right child
				*root = (*root)->right;
	
			else if ((*root)->right == NULL)  //if the root does not have a right child, change the root to be the left child
				*root = (*root)->left;

			else { //if there are both a left and right child
				Student* rParent = (*root); //keep track of previous student
				Student* rChild = (*root)->right; //keep track of right student
		
				findMin(rParent, rChild);

				if (rChild == rParent->left) //swap tree ordering if needed
					rParent->left = rChild->right;

				else //change root's right
					(*root)->right = rChild->right;

				rChild->left = student->left;
				rChild->right = student->right;

				*root = rChild;
	
			}	

			student->left = NULL;
			student->right = NULL;

			return(student); //return deleted student
		}
	}

	return NULL; //return null if student wasn't found

}

void findMin(Student* rParent, Student* rChild) { //find the smallest child from right node

	while (rChild->left != NULL) {
		rParent = rChild;
		rChild = rChild->left;
	}

}




 
