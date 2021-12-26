#include <iostream>
#include "my_proj/cal.h"

int main(int argc, char* argv[])
{
	Calendar cal(1, 2021);
	std::string input = "";
	input = input + argv[1] + " " + argv[2];
	cal.getmmyyyy(input);
	cal.printmonth();
	return 0;
}
