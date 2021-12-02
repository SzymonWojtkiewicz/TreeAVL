#include <iostream>

class AVL {
	AVL(std::string data);
	struct node;
public:
	void addData(std::string key) {
	
	};
	bool substractData(std::string key);
	bool substractData(node* nodePointer);
	bool search(std::string key);

private:
	void leftRotation(node* nodePointer);
	void rightRotation(node* nodePointer);
	void leftRightRotation(node* nodePointer);
	void rightLeftRotation(node* nodePointer);

};