#include <iostream>
#include <stack>
#include <vector>
#include<string>  
#include <fstream>

struct node {
	node* parent = nullptr;
	node* left = nullptr;
	node* right = nullptr;
	int key = 0;
	int balance = 0;
}root;
//node5, node30, node10, node14, node17, node50, node11, node40, node20;

std::string intToString(int x) {
	std::string str = std::to_string(x);
	if (x > -1 && x < 10) {
		str = "00" + str;
	}
	else if(x > 9 && x < 100)
	{
		str = "0" + str;
	}
	else if(x > -10 && x < 0)
	{
		str = std::to_string(abs(x));
		str = "-0" + str;
	}
	return str;
}
//best works for numbers from -99 to 999
int display(node* root, std::string failNameWithoutTxt) {
	int key = root->key;
	int treeHight = 0;
	node* currentNode = root;
	{
		int currentHight = 0;
		std::stack<bool> st;
		bool breakAll = false;
		while (true) {
			if (currentNode->left != nullptr) {
				currentHight++;
				if (currentHight > treeHight)
					treeHight = currentHight;
				st.push(0);
				currentNode = currentNode->left;
			}
			else if(currentNode->right != nullptr) {
				currentHight++;
				if (currentHight > treeHight)
					treeHight = currentHight;
				st.push(1);
				currentNode = currentNode->right;
			}
			else {
				while (true)
				{
					if (currentNode->parent == nullptr) {
						breakAll = true;
						break;
					}
					currentHight--;
					currentNode = currentNode->parent;
					if (st.empty()) 
					{
						std::cout << std::endl << "Unexpected end of a stack display 1 " << currentNode->balance << std::endl; breakAll = true; break;
					}
					if (st.top() == 0 && currentNode->right != nullptr) {
						st.pop();
						st.push(1);
						currentHight++;
						currentNode = currentNode->right;
						break;
					}
					st.pop();
				}
			}
			if (breakAll)
				break;
		}
	}
	std::vector<std::vector<int>> vect;
	{
		size_t size = treeHight + 1;
		vect.resize(size);
	}
	//****************************
	//vect[0].push_back(root->key);
	currentNode = root;

	/*int currentHight = 0;
	for (int i = 1; i + currentHight < treeHight + 1; i++) {
		int j = pow(2, i - 1);
		for (int k = 0; k < j; k++) {
			vect[i + currentHight].push_back(root->key);
		}
	}*/
	{
		int currentHight = 0;
		std::stack<bool> st;
		bool breakAll = false;
		while (true) {
			vect[currentHight].push_back(currentNode->key);
			if (currentNode->left != nullptr) {
				currentHight++;
				st.push(0);
				currentNode = currentNode->left;
			}
			else if (currentNode->right != nullptr) {
				for (int i = 1; i + currentHight < treeHight + 1; i++) {
					int j = pow(2, i - 1);
					for (int k = 0; k < j; k++) {
						vect[i + currentHight].push_back(root->key);
					}
				}
				currentHight++;
				st.push(1);
				currentNode = currentNode->right;
			}
			else {
				for (int i = 1; i + currentHight < treeHight + 1; i++) {
					int j = pow(2, i - 1);
					for (int k = 0; k < j; k++) {
						vect[i + currentHight].push_back(root->key);
					}
				}
				for (int i = 1; i + currentHight < treeHight + 1; i++) {
					int j = pow(2, i - 1);
					for (int k = 0; k < j; k++) {
						vect[i + currentHight].push_back(root->key);
					}
				}
				while (true)
				{
					if (currentNode->parent == nullptr) {
						breakAll = true;
						break;
					}
					currentHight--;
					currentNode = currentNode->parent;
					if (st.empty()) 
					{
						std::cout << std::endl << "Unexpected end of a stack display 2 " << currentNode->balance << std::endl; breakAll = true; break;
					}
					if (st.top() == 0 && currentNode->right != nullptr) {
						st.pop();
						st.push(1);
						currentHight++;
						currentNode = currentNode->right;
						break;
					}
					else if(st.top() == 0 && currentNode->right == nullptr)
					{
						for (int i = 1; i + currentHight < treeHight + 1; i++) {
							int j = pow(2, i - 1);
							for (int k = 0; k < j; k++) {
								vect[i + currentHight].push_back(root->key);
							}
						}
					}
					st.pop();
				}
			}
			if (breakAll)
				break;
		}
	}
	//*************************************
	std::vector<std::string> image;
	
	size_t size = 2 * treeHight + 1;
	image.resize(size);
	{
		int j = 0;
		for (int i = treeHight; i > -1; i--) {
			std::string space = " ";
			std::string space2 = "";
			for (int z = 0; z < j; z++) {
				 space2 = space2 +space;
			}
			j = j * 2 + 2;

			image[2 * i] = space2;

			for (int k = 0; k < vect[i].size(); k++) {
				std::string nextNumb;
				if (vect[i][k] != root->key || i == 0)
					nextNumb = intToString(vect[i][k]);
				else
					nextNumb = "XXX";
				if (k + 1 < vect[i].size()) {
					image[2 * i] = image[2 * i] + nextNumb + space2 + space + space2;
				}
				else
				{
					image[2 * i] = image[2 * i] + nextNumb + space2;
				}
			}
			
				
			
		}
	}
	std::string finaleImage;
	for (int i = 0; i < image.size(); i++) {
		finaleImage = finaleImage + "\n" + image[i];
		
	}
	std::ofstream out(failNameWithoutTxt + ".txt");
	out << finaleImage;
	out.close();
	int bss = 20;
		return treeHight;
}
int checkBalance(node* root) {
	int ltree = 0;
	int rtree = 0;
	int treeHight = 0;
	node* currentNode = root->left;
	
	if(currentNode != nullptr){
		int currentHight = 0;
		std::stack<bool> st;
		bool breakAll = false;
		while (true) {
			if (currentNode->left != nullptr) {
				currentHight++;
				if (currentHight > treeHight)
					treeHight = currentHight;
				st.push(0);
				currentNode = currentNode->left;
			}
			else if (currentNode->right != nullptr) {
				currentHight++;
				if (currentHight > treeHight)
					treeHight = currentHight;
				st.push(1);
				currentNode = currentNode->right;
			}
			else {
				while (true)
				{
					if (currentNode->parent == nullptr || currentNode->parent == root) {
						breakAll = true;
						break;
					}
					currentHight--;
					currentNode = currentNode->parent;
					if (st.top() == 0 && currentNode->right != nullptr) {
						st.pop();
						st.push(1);
						currentHight++;
						currentNode = currentNode->right;
						break;
					}
					st.pop();
				}
			}
			if (breakAll)
				break;
		}
	}
	ltree = treeHight;
	currentNode = root->right;

	if (currentNode != nullptr) {
		int currentHight = 0;
		std::stack<bool> st;
		bool breakAll = false;
		while (true) {
			if (currentNode->left != nullptr) {
				currentHight++;
				if (currentHight > treeHight)
					treeHight = currentHight;
				st.push(0);
				currentNode = currentNode->left;
			}
			else if (currentNode->right != nullptr) {
				currentHight++;
				if (currentHight > treeHight)
					treeHight = currentHight;
				st.push(1);
				currentNode = currentNode->right;
			}
			else {
				while (true)
				{
					if (currentNode->parent == nullptr || currentNode->parent == root) {
						breakAll = true;
						break;
					}
					currentHight--;
					currentNode = currentNode->parent;
					if (st.top() == 0 && currentNode->right != nullptr) {
						st.pop();
						st.push(1);
						currentHight++;
						currentNode = currentNode->right;
						break;
					}
					st.pop();
				}
			}
			if (breakAll)
				break;
		}
	}
	rtree = treeHight;
	return rtree - ltree;
}
void leftRotation(node* nodePointer) {
	node* cNodePointer = nodePointer;
	node* nodeRight = nodePointer->right;
	node* nodeParent = nodePointer->parent;
	node* nodeRightLeft = nodePointer->right->left;

	
	if (nodeParent != nullptr)
		if (nodeParent->left == cNodePointer)
			cNodePointer->parent->left = nodeRight;
		else if (nodeParent->right == cNodePointer)
			cNodePointer->parent->right = nodeRight;
	cNodePointer->right = nodeRightLeft;
	cNodePointer->parent = nodeRight;
	nodeRight->parent = nodeParent;
	nodeRight->left = cNodePointer;
	if (nodeRightLeft != nullptr)
		nodeRightLeft->parent = cNodePointer;

	cNodePointer->balance = checkBalance(cNodePointer);
	nodeRight->balance = checkBalance(nodeRight);
}
void rightRotation(node* nodePointer) {
	node* cNodePointer = nodePointer;
	node* nodeLeft = nodePointer->left;
	node* nodeParent = nodePointer->parent;
	node* nodeLeftRight = nodePointer->left->right;
	
	
	if (nodeParent != nullptr)
		if (nodeParent->left == cNodePointer)
			cNodePointer->parent->left = nodeLeft;
		else if(nodeParent->right == cNodePointer)
			cNodePointer->parent->right = nodeLeft;
	cNodePointer->left = nodeLeftRight;
	cNodePointer->parent = nodeLeft;
	nodeLeft->parent = nodeParent;
	nodeLeft->right = cNodePointer;
	if(nodeLeftRight != nullptr)
		nodeLeftRight->parent = cNodePointer;

	cNodePointer->balance = checkBalance(cNodePointer);
	nodeLeft->balance = checkBalance(nodeLeft);
}			
void leftRightRotation(node* nodePointer) {
	leftRotation(nodePointer->left);
	rightRotation(nodePointer);
}
void rightLeftRotation(node* nodePointer) {
	rightRotation(nodePointer->right);
	leftRotation(nodePointer);
}
void rebalance(node* curentNode) {
	if (curentNode->balance == -2) {
		if (curentNode->left->balance == -1) {
			rightRotation(curentNode);
		}
		else if (curentNode->left->balance == 1) {
			leftRightRotation(curentNode);
		}
	}
	else if (curentNode->balance == 2) {
		if (curentNode->right->balance == -1) {
			rightLeftRotation(curentNode);
		}
		else if (curentNode->right->balance == 1) {
			leftRotation(curentNode);
		}
	}
}
node* addData(node* root , int key) {
	
	node* curentNode = root;
	node* newNode = new node();
	newNode->key = key;
	{
		bool requaiersRebalance = false;
		std::stack<bool> st;
		while (true) {
			if (curentNode->key == key)			//this value already exists
				return root;
			else if (curentNode->key > key) {	//left side -1 to balance
				if (curentNode->left == nullptr) {
					curentNode->left = newNode;
					newNode->parent = curentNode;
					st.push(0);
					break;
				}
				else {
					curentNode = curentNode->left;
					st.push(0);
				}

			}
			else if (curentNode->key < key) {	//right side +1 to balance
				if (curentNode->right == nullptr) {
					curentNode->right = newNode;
					newNode->parent = curentNode;
					st.push(1);
					break;
				}
				else {
					curentNode = curentNode->right;
					st.push(1);
				}
			}
			else {
				std::cout << std::endl << "Unexpected Exeption"<< std::endl;
				return root;
			}
		}
		while (true) {
			if (st.empty())
			{
				std::cout << std::endl << "Unexpected end of a stack " << curentNode->balance << std::endl; break;
			}
			if (st.top())
				curentNode->balance++;
			else
				curentNode->balance--;
			st.pop();

			if (curentNode->balance == 0) {
				break;
			}
			else if(curentNode->balance == -1 || curentNode->balance == 1) {
				if (curentNode->parent == nullptr)
					break;
				else
					curentNode = curentNode->parent;
				continue;
			}
			else {
				//bool replantRoot = false;
				//if (curentNode = root)
				//	replantRoot = true;
				
				rebalance(curentNode);
				//if (replantRoot)
				//	root = curentNode->parent;
				if (root->parent != nullptr)
					root = root->parent;
				break;
			}
		}
	}
	return root;
	}
node* search(node* root, int key){
	node* currentNode = root;
	while (true) {
		if (currentNode->key == key) {
			return currentNode;
		}
		else
		{
			if (currentNode->key > key) {
				if (currentNode->left != nullptr) {
					currentNode = currentNode->left;
				}
				else {
					return nullptr;
				}
			}
			else {
				if (currentNode->right != nullptr) {
					currentNode = currentNode->right;
				}
				else {
					return nullptr;
				}
			}
		}
	}
}
node* substractData(node* root, int key){
	node* nodeToDel = search(root, key);
	if (nodeToDel == root) {
		//*********

	}
	else if (nodeToDel->left == nullptr && nodeToDel->right == nullptr) {
		if (nodeToDel->parent->left == nodeToDel) {
			nodeToDel->parent->left = nullptr;
			
		}
		else if (nodeToDel->parent->right == nodeToDel) {
			nodeToDel->parent->right = nullptr;
			
		}
	}
	else if (nodeToDel->left == nullptr || nodeToDel->right == nullptr) {
		if (nodeToDel->left == nullptr) {
			if (nodeToDel->parent->left == nodeToDel) {
				nodeToDel->parent->left = nodeToDel->right;
				nodeToDel->right->parent = nodeToDel->parent;
				
			}
			else if (nodeToDel->parent->right == nodeToDel) {
				nodeToDel->parent->right = nodeToDel->right;
				nodeToDel->right->parent = nodeToDel->parent;
				
			}
		}
		else if (nodeToDel->right == nullptr) {
			if (nodeToDel->parent->left == nodeToDel) {
				nodeToDel->parent->left = nodeToDel->left;
				nodeToDel->left->parent = nodeToDel->parent;
				
			}
			else if (nodeToDel->parent->right == nodeToDel) {
				nodeToDel->parent->right = nodeToDel->left;
				nodeToDel->left->parent = nodeToDel->parent;
				
			}
		}
	}
	else if (nodeToDel->left != nullptr && nodeToDel->right != nullptr) {
		node* cNode = nodeToDel;
		if (nodeToDel->balance > 0) {
			cNode = nodeToDel->right;
			while (true) {
				if (cNode->left == nullptr) {
					if(cNode->right != nullptr)
						cNode->right->parent = cNode->parent;

					cNode->parent->left = cNode->right;

					cNode->right = nodeToDel->right;
					cNode->left = nodeToDel->left;
					cNode->parent = nodeToDel->parent;

					nodeToDel->left->parent = cNode;

					nodeToDel->right->parent = cNode;
					
					if (nodeToDel->parent->left == nodeToDel) {
						nodeToDel->parent->left = cNode;
					}
					else if (nodeToDel->parent->right == nodeToDel) {
						nodeToDel->parent->right = cNode;
					}
					else {
						std::cout << std::endl << "unexpected 1" << std::endl;
					}
				}
				else
				{
					cNode = cNode->left;
				}
			}
		}
		else {
			cNode = nodeToDel->left;
			while (true) {
				if (cNode->right == nullptr) {
					if (cNode->left != nullptr)
						cNode->left->parent = cNode->parent;

					cNode->parent->right = cNode->left;

					cNode->right = nodeToDel->right;
					cNode->left = nodeToDel->left;
					cNode->parent = nodeToDel->parent;

					nodeToDel->left->parent = cNode;

					nodeToDel->right->parent = cNode;

					if (nodeToDel->parent->left == nodeToDel) {
						nodeToDel->parent->left = cNode;
					}
					else if (nodeToDel->parent->right == nodeToDel) {
						nodeToDel->parent->right = cNode;
					}
					else {
						std::cout << std::endl << "unexpected 1" << std::endl;
					}
				}
				else
				{
					cNode = cNode->left;
				}
			}
		}
	}
	// check to root balance
	delete& nodeToDel;
	return root;
}

int main()
{
	node* rootNoode = &root;
	{
		int initialRootKey = 11;
		//std::cin >> initialRootKey;
		root.key = initialRootKey;
	}
	/*
	root.key = 18;
	root.left = &node5;
	root.right = &node30;

	node5.key = 5;
	node5.left = &node10;
	node5.right = nullptr;
	node5.parent = &root;
	
	node10.key = 10;
	node10.left = nullptr;
	node10.right = &node14;
	node10.parent = &node5;

	node14.key = 14;
	node14.parent = &node10;

	node30.key = 30;
	node30.left = &node17;
	node30.right = &node50;
	node30.parent = &root;

	node17.key = 17;
	node17.left = &node11;
	node17.right = &node40;
	node17.parent = &node30;

	node11.key = 11;
	node11.left = nullptr;
	node11.right = &node20;
	node11.parent = &node17;

	node20.key = 20;
	node20.parent = &node11;

	node40.key = 40;
	node40.parent = &node17;

	node50.key = 50;
	node50.parent = &node30;
	*/
	
	//std::cout << display((rootNoode, "output") << std::endl;
	rootNoode = addData(rootNoode, 10);
	//std::cout << display((rootNoode, "output") << std::endl;
	rootNoode = addData(rootNoode, 9);
	//std::cout << display((rootNoode, "output") << std::endl;
	rootNoode = addData(rootNoode, 50);
	//std::cout << display((rootNoode, "output") << std::endl;
	rootNoode = addData(rootNoode, 0);
	std::cout << display(rootNoode, "output") << std::endl;
	rootNoode = addData(rootNoode, 3);
	//std::cout << display((rootNoode, "output") << std::endl;
	rootNoode = addData(rootNoode, -29);
	std::cout << display(rootNoode, "output") << std::endl;
	rootNoode = addData(rootNoode, 60);
	//std::cout << display((rootNoode, "output") << std::endl;
	rootNoode = addData(rootNoode, 13);
	//std::cout << display((rootNoode, "output") << std::endl;
	rootNoode = addData(rootNoode, 19);
	/*
	rootNoode = addData(rootNoode, 19);
	rootNoode = addData(rootNoode, 7);
	rootNoode = addData(rootNoode, 89);
	rootNoode = addData(rootNoode, 49);
	rootNoode = addData(rootNoode, 39);
	rootNoode = addData(rootNoode, 29);
	rootNoode = addData(rootNoode, -19);
	rootNoode = addData(rootNoode, 2);
	rootNoode = addData(rootNoode, 6);
	rootNoode = addData(rootNoode, 12);
	rootNoode = addData(rootNoode, 16);
	rootNoode = addData(rootNoode, 22);
	rootNoode = addData(rootNoode, 31);
	*/
	std::cout << display(rootNoode, "output") << std::endl;

	//std::cout << search(rootNoode, 29)->key << std::endl;
}
