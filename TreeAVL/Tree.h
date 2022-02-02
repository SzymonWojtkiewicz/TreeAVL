#pragma once

#include <iostream>
#include <stack>
#include <vector>
#include<string>  
#include <fstream>

class Tree
{
public:
	struct node {
		node* parent = nullptr;
		node* left = nullptr;
		node* right = nullptr;
		int key = 0;
		int balance = 0;
	};

	Tree::node* root = nullptr;

private:
	std::string intToString(int x);
	//best works for numbers from -99 to 999
public:
	int display(std::string failNameWithoutTxt);
private:
	int checkBalance(node* root);
	void leftRotation(node* nodePointer);
	void rightRotation(node* nodePointer);
	void leftRightRotation(node* nodePointer);
	void rightLeftRotation(node* nodePointer);
	void rebalance(node* curentNode);
public:
	bool addData(int key);
	node* search(int key);
	bool substractData(int key);

};

