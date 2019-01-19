#ifndef _SCORE_H_
#define _SCORE_H_
#include <fstream>
class Score
{
	int value = 0;
public:
	std::ofstream tofile;
	Score();	
	~Score();
	void addtoscore();
	void resetscore();
	void streamscore();
};
#endif
