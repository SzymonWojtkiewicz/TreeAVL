#include "Tree.h"




std::string Tree::intToString(int x) {
	std::string str = std::to_string(x);
	if (x > -1 && x < 10) {
		str = "00" + str;
	}
	else if (x > 9 && x < 100)
	{
		str = "0" + str;
	}
	else if (x > -10 && x < 0)
	{
		str = std::to_string(abs(x));
		str = "-0" + str;
	}
	return str;
}
//best works for numbers from -99 to 999
int Tree::display(std::string failNameWithoutTxt) {
	if (this->root == nullptr)
		return -1;
	int key = this->root->key;
	int treeHight = 0;
	node* currentNode = this->root;
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
	currentNode = this->root;

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
						vect[i + currentHight].push_back(this->root->key);
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
						vect[i + currentHight].push_back(this->root->key);
					}
				}
				for (int i = 1; i + currentHight < treeHight + 1; i++) {
					int j = pow(2, i - 1);
					for (int k = 0; k < j; k++) {
						vect[i + currentHight].push_back(this->root->key);
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
					else if (st.top() == 0 && currentNode->right == nullptr)
					{
						for (int i = 1; i + currentHight < treeHight + 1; i++) {
							int j = pow(2, i - 1);
							for (int k = 0; k < j; k++) {
								vect[i + currentHight].push_back(this->root->key);
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
				space2 = space2 + space;
			}
			j = j * 2 + 2;

			image[2 * i] = space2;

			for (int k = 0; k < vect[i].size(); k++) {
				std::string nextNumb;
				if (vect[i][k] != this->root->key || i == 0)
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
int Tree::checkBalance(node* sNode) {
	int ltree = 0;
	int rtree = 0;
	int treeHight = 0;
	node* currentNode = sNode->left;

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
					if (currentNode->parent == nullptr || currentNode->parent == sNode) {
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
	currentNode = sNode->right;

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
					if (currentNode->parent == nullptr || currentNode->parent == sNode) {
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
void Tree::leftRotation(node* nodePointer) {
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
void Tree::rightRotation(node* nodePointer) {
	node* cNodePointer = nodePointer;
	node* nodeLeft = nodePointer->left;
	node* nodeParent = nodePointer->parent;
	node* nodeLeftRight = nodePointer->left->right;


	if (nodeParent != nullptr)
		if (nodeParent->left == cNodePointer)
			cNodePointer->parent->left = nodeLeft;
		else if (nodeParent->right == cNodePointer)
			cNodePointer->parent->right = nodeLeft;
	cNodePointer->left = nodeLeftRight;
	cNodePointer->parent = nodeLeft;
	nodeLeft->parent = nodeParent;
	nodeLeft->right = cNodePointer;
	if (nodeLeftRight != nullptr)
		nodeLeftRight->parent = cNodePointer;

	cNodePointer->balance = checkBalance(cNodePointer);
	nodeLeft->balance = checkBalance(nodeLeft);
}
void Tree::leftRightRotation(node* nodePointer) {
	leftRotation(nodePointer->left);
	rightRotation(nodePointer);
}
void Tree::rightLeftRotation(node* nodePointer) {
	rightRotation(nodePointer->right);
	leftRotation(nodePointer);
}
void Tree::rebalance(node* curentNode) {
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
bool Tree::addData(int key) {
	if (this->root == nullptr) {
		this->root = new node();
		this->root->key = key;
		return true;
	}

	node* curentNode = this->root;
	node* newNode = new node();
	newNode->key = key;
	{
		bool requaiersRebalance = false;
		std::stack<bool> st;
		while (true) {
			if (curentNode->key == key)			//this value already exists
				return false;
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
				std::cout << std::endl << "Unexpected Exeption" << std::endl;
				return false;
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
			else if (curentNode->balance == -1 || curentNode->balance == 1) {
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
				if (this->root->parent != nullptr)
					this->root = this->root->parent;
				break;
			}
		}
	}
	
	return true;
}
Tree::node* Tree::search(int key) {
	node* currentNode = this->root;
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
bool Tree::substractData(int key) {
	node* nodeToDel = search(key);
	if (nodeToDel == nullptr)
		return false;
	node* nodeBalanceStart; // from this node start rebalance
	node* cNode = nodeToDel;
	if (nodeToDel == this->root) {
		//*********
		if (nodeToDel->left == nullptr && nodeToDel->right == nullptr) { // No children
			nodeToDel->left = nullptr;
			nodeToDel->right = nullptr;
			nodeToDel->parent = nullptr;
			delete nodeToDel;
			return false;
		}
		else if (nodeToDel->left == nullptr || nodeToDel->right == nullptr) {//One child
			if (nodeToDel->left == nullptr) {
				cNode = nodeToDel->right->parent;
				nodeToDel->right->parent = nullptr;
				/*nodeToDel->left = nullptr;
				nodeToDel->right = nullptr;
				nodeToDel->parent = nullptr;*/
				delete nodeToDel;
				return true;
			}
			else
			{
				cNode = nodeToDel->left->parent;
				nodeToDel->left->parent = nullptr;
				/*nodeToDel->left = nullptr;
				nodeToDel->right = nullptr;
				nodeToDel->parent = nullptr;*/
				delete nodeToDel;
				return true;
			}
		}
		else if (nodeToDel->left != nullptr && nodeToDel->right != nullptr) {//Has two children
			if (nodeToDel->balance > 0) {
				cNode = nodeToDel->right;
				while (true) {
					if (cNode->left == nullptr) {
						if (cNode->right != nullptr)
							cNode->right->parent = cNode->parent;

						nodeBalanceStart = cNode->parent;
						if (cNode->parent->left != nodeToDel->left)
							cNode->parent->left = cNode->right;
						if (nodeToDel->right != cNode)
							cNode->right = nodeToDel->right;
						if (nodeToDel->left != cNode)
							cNode->left = nodeToDel->left;
						//cNode->right = nodeToDel->right;
						//cNode->left = nodeToDel->left;
						cNode->parent = nodeToDel->parent;

						if(nodeToDel->left != cNode)///
							nodeToDel->left->parent = cNode;

						if(nodeToDel->right != cNode)///
							nodeToDel->right->parent = cNode;


						break;
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

						nodeBalanceStart = cNode->parent;
						if (cNode->parent->right != nodeToDel->right)
							cNode->parent->right = cNode->left;

						if (nodeToDel->right != cNode)
							cNode->right = nodeToDel->right;
						if (nodeToDel->left != cNode)
							cNode->left = nodeToDel->left;
						//cNode->right = nodeToDel->right;
						//cNode->left = nodeToDel->left;
						cNode->parent = nodeToDel->parent;

						if(nodeToDel->left != cNode)///
							nodeToDel->left->parent = cNode;

						if(nodeToDel->right != cNode)///
							nodeToDel->right->parent = cNode;


						break;
					}
					else
					{
						cNode = cNode->right;
					}
				}
			}
		}

	}
	else if (nodeToDel->left == nullptr && nodeToDel->right == nullptr) { // No children
		if (nodeToDel->parent->left == nodeToDel) {//Is left child 
			nodeToDel->parent->left = nullptr;
			cNode = nodeToDel->parent;

		}
		else if (nodeToDel->parent->right == nodeToDel) {//Is right child
			nodeToDel->parent->right = nullptr;
			cNode = nodeToDel->parent;
		}
	}
	else if (nodeToDel->left == nullptr || nodeToDel->right == nullptr) { //One child
		if (nodeToDel->left == nullptr) {//Has right child
			if (nodeToDel->parent->left == nodeToDel) {//Is left child
				nodeToDel->parent->left = nodeToDel->right;
				nodeToDel->right->parent = nodeToDel->parent;
				cNode = nodeToDel->parent;

			}
			else if (nodeToDel->parent->right == nodeToDel) {//Is right child
				nodeToDel->parent->right = nodeToDel->right;
				nodeToDel->right->parent = nodeToDel->parent;
				cNode = nodeToDel->parent;

			}
		}
		else if (nodeToDel->right == nullptr) {//Has left child
			if (nodeToDel->parent->left == nodeToDel) {//Is left child
				nodeToDel->parent->left = nodeToDel->left;
				nodeToDel->left->parent = nodeToDel->parent;
				cNode = nodeToDel->parent;

			}
			else if (nodeToDel->parent->right == nodeToDel) {//Is right child
				nodeToDel->parent->right = nodeToDel->left;
				nodeToDel->left->parent = nodeToDel->parent;
				cNode = nodeToDel->parent;

			}
		}
	}
	else if (nodeToDel->left != nullptr && nodeToDel->right != nullptr) {//Has two children
		if (nodeToDel->balance > 0) {
			cNode = nodeToDel->right;
			while (true) {
				if (cNode->left == nullptr) {
					if (cNode->right != nullptr)
						cNode->right->parent = cNode->parent;

					nodeBalanceStart = cNode->parent;

					if (cNode->parent->left != nodeToDel->left)
						cNode->parent->left = cNode->right;

					if (nodeToDel->right != cNode)
						cNode->right = nodeToDel->right;
					if (nodeToDel->left != cNode)
						cNode->left = nodeToDel->left;
				//	cNode->right = nodeToDel->right;
				//	cNode->left = nodeToDel->left;
					cNode->parent = nodeToDel->parent;

					if(nodeToDel->left != cNode)
						nodeToDel->left->parent = cNode;//

					if(nodeToDel->right != cNode)
						nodeToDel->right->parent = cNode;//

					if (nodeToDel->parent->left == nodeToDel) {
						nodeToDel->parent->left = cNode;
					}
					else if (nodeToDel->parent->right == nodeToDel) {
						nodeToDel->parent->right = cNode;
					}
					else {
						std::cout << std::endl << "unexpected 1" << std::endl;
					}
					break;
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

					nodeBalanceStart = cNode->parent;

					if(cNode->parent->right != nodeToDel->right)
						cNode->parent->right = cNode->left;
					if(nodeToDel->right != cNode)
						cNode->right = nodeToDel->right;
					if (nodeToDel->left != cNode)
						cNode->left = nodeToDel->left;
					cNode->parent = nodeToDel->parent;

					if(nodeToDel->left != cNode)//
						nodeToDel->left->parent = cNode;//

					//if(nodeToDel->right == nullptr)
						//!!!!!!!!!!!!!!!!!!!!!!!!!
					if(nodeToDel->right != cNode)//
						nodeToDel->right->parent = cNode;//
					//cNode->parent = nodeToDel->parent;
					if (nodeToDel->parent->left == nodeToDel) {
						nodeToDel->parent->left = cNode;
					}
					else if (nodeToDel->parent->right == nodeToDel) {
						nodeToDel->parent->right = cNode;
					}
					else {
						std::cout << std::endl << "unexpected 1" << std::endl;
					}
					break;
				}
				else
				{
					cNode = cNode->right;
				}
			}
		}
	}
	//!!!!!!!!!!!!! remember reseting root!!!!!!!!!

	do {
		cNode->balance = checkBalance(cNode);
		if (cNode->balance < -1 || cNode->balance > 1)
			rebalance(cNode);
		if (cNode->parent != nullptr)
			cNode = cNode->parent;
	} while (cNode->parent != nullptr);
	// check to root balance
	this->root = cNode;
	delete nodeToDel;
	return true;
}