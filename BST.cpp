#include <iostream>
#include <fstream>
#include <algorithm>
#include "BST.h"
#include <string>

using namespace std;


BST::BST() {
	root = NULL;
	count = 0;
}


bool BST::empty() {
	if (count == 0) return true;
	return false;
}


int BST::size() {
	return count;
}


void BST::preOrderPrint() {
	if (root == NULL) return;// handle special case
	else preOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::preOrderPrint2(BTNode *cur) {

	if (cur == NULL) return;
	cur->item.print(cout);
	preOrderPrint2(cur->left);
	preOrderPrint2(cur->right);
}


void BST::inOrderPrint() {
	if (root == NULL) return;// handle special case
	else inOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::inOrderPrint2(BTNode *cur) {

	if (cur == NULL) return;

	inOrderPrint2(cur->left);
	cur->item.print(cout);
	inOrderPrint2(cur->right);
}


void BST::postOrderPrint() {
	if (root == NULL) return;// handle special case
	else postOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::postOrderPrint2(BTNode *cur) {
	if (cur == NULL) return;
	postOrderPrint2(cur->left);
	postOrderPrint2(cur->right);
	cur->item.print(cout);
}



int BST::countNode() {
	int	counter = 0;
	if (root == NULL) return 0;
	countNode2(root, counter);
	return counter;
}


void BST::countNode2(BTNode *cur, int &count) {
	if (cur == NULL) return;
	countNode2(cur->left, count);
	countNode2(cur->right, count);
	count++;
}


bool BST::findGrandsons(type grandFather) {
	if (root == NULL) return false;
	return (fGS2(grandFather, root));
}


bool BST::fGS2(type grandFather, BTNode *cur) {
	if (cur == NULL) return false;
	//if (cur->item == grandFather) {
	if (cur->item.compare2(grandFather)){

		fGS3(cur, 0);// do another TT to find grandsons
		return true;
	}
	if (fGS2(grandFather, cur->left)) return true;
	return fGS2(grandFather, cur->right);
}


void BST::fGS3(BTNode *cur, int level) {
	if (cur == NULL) return;
	if (level == 2) {
		cur->item.print(cout);
		return;  // No need to search downward
	}
	fGS3(cur->left, level + 1);
	fGS3(cur->right, level + 1);
}



void BST::topDownLevelTraversal() {
	BTNode			*cur;
	Queue		    q;


	if (empty()) return; 	// special case
	q.enqueue(root);	// Step 1: enqueue the first node
	while (!q.empty()) { 	// Step 2: do 2 operations inside
		q.dequeue(cur);
		if (cur != NULL) {
			cur->item.print(cout);

			if (cur->left != NULL)
				q.enqueue(cur->left);

			if (cur->right != NULL)
				q.enqueue(cur->right);
		}
	}
}

//insert for BST
bool BST::insert(type newItem) {
	BTNode	*cur = new BTNode(newItem);
	if (!cur) return false;		// special case 1
	if (root == NULL) {
		root = cur;
		count++;
		return true; 			// special case 2
	}
	insert2(root, cur);			// normal
	count++;
	return true;
}


void BST::insert2(BTNode *cur, BTNode *newNode) {
	//if (cur->item > newNode->item) {
	if (cur->item.compare1(newNode->item)){
		if (cur->left == NULL)
			cur->left = newNode;
		else
			insert2(cur->left, newNode);
	}
	else {
		if (cur->right == NULL)
			cur->right = newNode;
		else
			insert2(cur->right, newNode);
	}
}



bool BST::remove(type item) {
	if (root == NULL) return false; 		// special case 1: tree is empty
	return remove2(root, root, item); 		// normal case
}

bool BST::remove2(BTNode *pre, BTNode *cur, type item) {

	// Turn back when the search reaches the end of an external path
	if (cur == NULL) return false;

	// normal case: manage to find the item to be removed
	//if (cur->item == item) {
	if (cur->item.compare2(item)){
		if (cur->left == NULL || cur->right == NULL)
			case2(pre, cur);	// case 2 and case 1: cur has less than 2 sons
		else
			case3(cur);		// case 3, cur has 2 sons
		count--;				// update the counter
		return true;
	}

	// Current node does NOT store the current item -> ask left sub-tree to check
	//if (cur->item > item)
	if (cur->item.compare1(item))
		return remove2(cur, cur->left, item);

	// Item is not in the left subtree, try the right sub-tree instead
	return remove2(cur, cur->right, item);
}


void BST::case2(BTNode *pre, BTNode *cur) {

	// special case: delete root node
	if (pre == cur) {
		if (cur->left != NULL)	// has left son?
			root = cur->left;
		else
			root = cur->right;

		free(cur);
		return;
	}

	if (pre->right == cur) {		// father is right son of grandfather? 
		if (cur->left == NULL)			// father has no left son?
			pre->right = cur->right;			// connect gfather/gson
		else
			pre->right = cur->left;
	}
	else {						// father is left son of grandfather?
		if (cur->left == NULL)			// father has no left son? 
			pre->left = cur->right;				// connect gfather/gson
		else
			pre->left = cur->left;
	}

	free(cur);					// remove item
}


void BST::case3(BTNode *cur) {
	BTNode		*is, *isFather;

	// get the IS and IS_parent of current node
	is = isFather = cur->right;
	while (is->left != NULL) {
		isFather = is;
		is = is->left;
	}

	// copy IS node into current node
	cur->item = is->item;

	// Point IS_Father (grandfather) to IS_Child (grandson)
	if (is == isFather)
		cur->right = is->right;		// case 1: There is no IS_Father    
	else
		isFather->left = is->right;	// case 2: There is IS_Father

	// remove IS Node
	free(is);
}
//Task(b)
int BST::treeHeight(BTNode* root) //check the height of tree
{
	if (!root) return 0;

	int leftHeight = treeHeight(root->left);
	int rightHeight = treeHeight(root->right);

	return max(leftHeight, rightHeight) + 1;
}
bool BST::deepestNodes() {
	if (empty()) {
		return false;
	}

	BTNode* cur;
	Queue q;
	int level = 1;
	q.enqueue(root);

	while (!q.empty()) {
		int queuesize = q.size();
		for (int i = 0; i < queuesize; ++i) {
			q.dequeue(cur);
			if (level == treeHeight(root)) {   //when the level of nodes meet bottom
				cout << cur->item.id << " ";
			}
			if (cur->left != NULL) {
				q.enqueue(cur->left);
			}
			if (cur->right != NULL) {
				q.enqueue(cur->right);
			}
		}
		level++;
	}
	return true;
}

//Task(c)
//order = 1 for ascending and order = 2 for descending : To print in ascending visit left son and then right son. 
//As to print in descending visit right son and then left son.
//source = 1 to print to screen and source = 2 to print to a file name “student-info.txt”. 
bool BST::display(int order, int source) {
	if (root == nullptr) {
		return false;
	}
	if (source == 1) {
		if (order == 1)
			inOrderPrint(); // Display in-order on screen
		else if (order == 2)
			inOrderPrintInverse(); // Display post-order on screen
	}
	else if (source == 2) {
		ofstream outfile("student-info.txt"); // Open a file for writing

		if (empty())
			return false;
		else if (outfile.fail()) {
			cout << "\nError opening the file.\n" << endl;
			return false;
		}

		if (order == 1) {
			inOrderPrintToFile(outfile); // Write in-order to file
		}
		else if (order == 2) {
			inOrderPrintToFileInverse(outfile); // Write post-order to file
		}

		cout << "File is created and the data is displayed successfully.\n";
		outfile.close(); // Close the file
	}
	return true;
}
void BST::inOrderPrintInverse() {
	if (root == NULL) return;// handle special case
	else inOrderPrintInverse2(root);// do normal process
	cout << endl;
}
void BST::inOrderPrintInverse2(BTNode* cur) {

	if (cur == NULL) return;
	inOrderPrintInverse2(cur->right);
	cur->item.print(cout);
	inOrderPrintInverse2(cur->left);
}
void BST::inOrderPrintToFile(ofstream& outfile) {
	if (root == NULL) return;// handle special case
	else inOrderPrintToFile2(root, outfile);// do normal process
	cout << endl;
}
void BST::inOrderPrintToFile2(BTNode* cur, ofstream& outfile) {

	if (cur == NULL) return;
	inOrderPrintToFile2(cur->left, outfile);
	cur->item.print(outfile);
	inOrderPrintToFile2(cur->right, outfile);
}
void BST::inOrderPrintToFileInverse(ofstream& outfile) {
	if (root == NULL) return;// handle special case
	else inOrderPrintToFileInverse2(root, outfile);// do normal process
	cout << endl;
}
void BST::inOrderPrintToFileInverse2(BTNode* cur, ofstream& outfile) {

	if (cur == NULL) return;
	inOrderPrintToFileInverse2(cur->right, outfile);
	cur->item.print(outfile);
	inOrderPrintToFileInverse2(cur->left, outfile);
}

//Task(d)
bool BST::CloneSubtree(BST t1, type item)
{
	if (t1.empty())
		return false;
	
	if (!checkItem(t1.root, item))
		return false;
	
	return true;
}
bool BST::checkItem(BTNode* cur, type item) 
{
	if (cur == NULL)
		return false;

	if (cur->item.compare2(item)) {
		root = new BTNode{ cur->item };
		insertToSubtree(root, cur);
		if (root->left == NULL && root->right == NULL)
		{
			return false;
		}
		return true;
	}
	
	if (checkItem(cur->left, item) || checkItem(cur->right, item))
	{
		return true;
	}
	return checkItem(cur->right, item);
}
void BST::insertToSubtree(BTNode* sub, BTNode* cur)
{
	if (cur->left != NULL) {
		sub->left = new BTNode{ cur->left->item };
		insertToSubtree(sub->left, cur->left);
	}
	if (cur->right != NULL) {
		sub->right = new BTNode{ cur->right->item };
		insertToSubtree(sub->right, cur->right);
	}
}

//Task(e)
bool BST::printLevelNodes() 
{
	if (empty())
		return false;

	BTNode* cur;
	Queue q;
	int level = 1;
	q.enqueue(root);

	while (!q.empty()) 
	{
		int count = q.size();
		cout << "Level " << level << " nodes: ";
		while (count > 0) 
		{
			q.dequeue(cur);
			cout << cur->item.id << " ";
			if (cur->left != NULL) 
			{
				q.enqueue(cur->left);
			}
			if (cur->right != NULL) 
			{
				q.enqueue(cur->right);
			}
			count--;
		}
		cout << endl;
		level++;
	}
	
	return true;
}

//Task(f)
bool BST::printPath()
{
	if (root == NULL)
		return false;
	cout << "Below are all the external paths for the tree: " << endl;
	cout << endl;
	printExternalPath(root, "");
	return true;
}
void BST::printExternalPath(BTNode* node, string id)
{
	if (node == NULL)
		return;

	if (node->left == NULL && node->right == NULL)
	{
		cout << id << node->item.id << endl;
	}

	if (node->left != NULL) 
	{
		printExternalPath(node->left, id + to_string(node->item.id) + " -> ");
	}

	if (node->right != NULL) 
	{
		printExternalPath(node->right, id + to_string(node->item.id) + " -> ");
	}
}

//DuplicateCheck
bool BST::hasDuplicates(BST* t1, int id) {
	if (t1->root == NULL) {
		return false; // No duplicates in an empty tree
	}
	return hasDuplicates2(t1->root, id); // Call recursive helper function
}
bool BST::hasDuplicates2(BTNode* cur, int id) {
	if (cur == NULL) {
		return false; // Base case: no duplicates found
	}
	if (cur->item.compare3(id))
		return true;
	if (id < cur->item.id)
		// Recursively check the left and right subtrees
		return hasDuplicates2(cur->left, id);
	else
		return hasDuplicates2(cur->right, id);
}