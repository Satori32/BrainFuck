#include <iostream>
#include "BrainFuck.h"


int main() {
	BrainFuck<char> BF;
	//BrainFuck<int> BF;

	std::string Hello = "+++++++++[>++++++++>+++++++++++>+++++<<<-]>.>++.+++++++..+++. > -.------------.<++++++++.--------.++ + .------.--------.>+.";
	std::string S1 = "++++[>++++[>++++<-]<-]>>.";
	std::string S2 = "++[>+<-]>.";

	//BF.Initialize(256, S1);
	BF.Initialize(16, Hello);
	BF.Interpret([](auto& a) {}, [](auto& a) {std::cout << a; });
	return 0;
}