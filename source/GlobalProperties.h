#if !defined(_GLOBAL_H_)
#define _GLOBAL_H_

#include <fstream>
#include <iostream>
#include <stdio.h>
#include "s3eFile.h"
#include <math.h>

using namespace std;

class GlobalProperties {
public:
	int AdditionEasyHighScore = 0;
	int AdditionMediumHighScore = 0;
	int AdditionHardHighScore = 0;

	int SubtractionEasyHighScore = 0;
	int SubtractionMediumHighScore = 0;
	int SubtractionHardHighScore = 0;

	int MultiplicationEasyHighScore = 0;
	int MultiplicationMediumHighScore = 0;
	int MultiplicationHardHighScore = 0;

	int DivisionEasyHighScore = 0;
	int DivisionMediumHighScore = 0;
	int DivisionHardHighScore = 0;

	int difficulty = 1;
	int PracticeMode = 0;

	GlobalProperties();
	~GlobalProperties();
	
	void Save();

private:
	int parseInt(char * str);
	void DeterminePlace(char * tag, int val);
	
};

extern GlobalProperties* g_pGlobalProperties;

#endif