#include "reverse.h"
#include <string>
#include <iterator>  // std::back_inserter
#include <iostream>



void nop::test_adjacent_swap_copy() {
	std::string outstr;
	
	std::string instr1 {"ababab"};
	nop::adjacent_swap_copy(instr1.begin(),instr1.end(),std::back_inserter(outstr));
	std::cout << instr1 << " => " << outstr << std::endl;
	std::cout << std::endl;

	outstr.clear();
	std::string instr2 {"abababa"};
	nop::adjacent_swap_copy(instr2.begin(),instr2.end(),std::back_inserter(outstr));
	std::cout << instr2 << " => " << outstr << std::endl;
	std::cout << std::endl;

	outstr.clear();
	std::string instr3 {""};
	nop::adjacent_swap_copy(instr3.begin(),instr3.end(),std::back_inserter(outstr));
	std::cout << instr3 << " => " << outstr << std::endl;
	std::cout << std::endl;

}








