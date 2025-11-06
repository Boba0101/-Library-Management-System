#ifndef BT_type
#define BT_type

#include	"BTNode.h"
#include	"Queue.h"


struct BST {

		int		count;
		BTNode	*root;

		// print operation for BST (same as BT)					
		void preOrderPrint2(BTNode *);	// recursive function for preOrderPrint()
		void inOrderPrint2(BTNode *);	// recursive function for inOrderPrint()
		void postOrderPrint2(BTNode *);	// recursive function for postOrderPrint()

		// sample operation (extra functions) - same as BT
		void countNode2(BTNode *, int &);		// recursive function for countNode()
		bool fGS2(type, BTNode *);					// recursive function for findGrandsons(): to find the grandfather
		void fGS3(BTNode *, int);				// recursive function for findGrandsons(): to find the grandsons after the grandfather has been found
		
		// basic functions for BST
		void insert2(BTNode *, BTNode *);		// recursive function for insert() of BST
		void case3(BTNode *);					// recursive function for remove()
		void case2(BTNode *, BTNode *);		// recursive function for remove()
		bool remove2(BTNode *, BTNode *, type);	// recursive function for remove()



		// basic functions for BST
		BST();
		bool empty();
		int size();
		bool insert (type);		// insert an item into a BST
		bool remove(type);			// remove an item from a BST
		
		// print operation for BST (same as BT)
		void preOrderPrint();			// print BST node in pre-order manner
		void inOrderPrint();			// print BST node in in-order manner
		void postOrderPrint();			// print BST node in post-order manner
		void topDownLevelTraversal();	// print BST level-by-level

		// sample operation (extra functions) - same as BT
		int countNode();		// count number of tree nodes
		bool findGrandsons(type);	// find the grandsons of an input father item

		//Task(b)
		int treeHeight(BTNode*);
		bool deepestNodes();
		//Task(c)
		bool display(int, int);
		void inOrderPrintInverse();
		void inOrderPrintInverse2(BTNode*);
		void inOrderPrintToFile(ofstream&);
		void inOrderPrintToFile2(BTNode*, ofstream&);
		void inOrderPrintToFileInverse(ofstream&);
		void inOrderPrintToFileInverse2(BTNode*, ofstream&);
		//Task(d)
		bool CloneSubtree(BST, type);
		bool checkItem(BTNode*, type);
		void insertToSubtree(BTNode*, BTNode*);
		//Task(e)
		bool printLevelNodes();
		//Task(f)
		bool printPath();
		void printExternalPath(BTNode* node, string id);
		//DuplicateCheck
		bool hasDuplicates(BST*, int);
		bool hasDuplicates2(BTNode*, int);
};




#endif