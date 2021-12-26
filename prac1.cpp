#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>
#include "my_proj/prac.h"


int main()
{
	BigNumber BG(5234);
	BigNumber GG(4456);

	BG.multiply(BG, GG);
	BG.print_results();
	BG.print_ur_results();

	std::cout << GG.number() << std::endl;

	BG.MakeLongMultString();


return 0;
}
