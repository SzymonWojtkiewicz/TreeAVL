#include <iostream>

#pragma once
class AVL {
public :
	AVL(std::string data);
	struct node {
		node* parent = nullptr;
		node* left = nullptr;
		node* right = nullptr;
		std::string key;
		int balance = 0;
	};
	void addData(std::string key);
	bool substractData(std::string key);
	bool substractData(node* nodePointer);
	bool search(std::string key);

private :
	void leftRotation(node* nodePointer);
	void rightRotation(node* nodePointer);
	void leftRightRotation(node* nodePointer);
	void rightLeftRotation(node* nodePointer);

};