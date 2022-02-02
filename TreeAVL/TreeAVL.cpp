#include <iostream>
#include <stack>
#include <vector>
#include<string>  
#include <fstream>
#include "Tree.h"

// Please check README

int main()
{
	Tree abc;
	abc.addData(10);
	abc.addData(9);
	abc.addData(50);
	abc.addData(0);
	std::cout << abc.display("output") << std::endl;
	abc.addData(3);
	abc.addData(-29);
	std::cout << abc.display("output") << std::endl;
	abc.addData(60);
	abc.addData(13);
	abc.addData(19);

	abc.addData(19);
	abc.addData(7);
	abc.addData(89);
	abc.addData(49);
	abc.addData(39);
	abc.addData(29);
	abc.addData(-19);
	abc.addData(2);
	abc.addData(6);
	abc.addData(12);
	abc.addData(16);
	abc.addData(22);
	abc.addData(31);
	std::cout << abc.display("output") << std::endl;
	abc.substractData(2);
	std::cout << abc.display("output") << std::endl;
	abc.substractData(2);
	abc.substractData(13);
	abc.substractData(11);
	abc.substractData(10);

	std::cout << abc.display("output") << std::endl;

	return 0;
}
