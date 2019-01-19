#include "Score.h"

Score::Score()
{
	try
	{
		tofile.open("Yourscore.txt");
	}
	catch (std::ofstream::failure &readErr)
	{

	}
	
}

Score::~Score()
{
}

void Score::addtoscore()
{
	value += 100;
}
void Score::resetscore()
{
	value = 0;
}

void Score::streamscore()
{
	tofile <<"Your score is "<<value;
}