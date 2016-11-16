#if !defined(PROBLEM_CREATOR)
#define PROBLEM_CREATOR

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define MAX_USED 5
#define MAX_NUMBERS_IN_EQUATION 3

class ProblemCreator {
private:
	float used[MAX_USED][MAX_NUMBERS_IN_EQUATION];
	int usedPlace = 0;

public:
	ProblemCreator();
	~ProblemCreator();

	void createMathProblem(float[3], int, int);

	void createAdditionProblem(float [3], int);

	void createSubtractionProblem(float[3], int);

	void createMultiplicationProblem(float[3], int);

	void createDivisionProblem(float[3], int);

	bool CheckIfUsed(float*);

	void AddToUsed(float*);

	void CreateAnswers(float*, float*, int, int);

	void CreateAdditionAnswers(float*, float*, int, int);

	void CreateSubtractionAnswers(float*, float*, int, int);

	void CreateMultiplicationAnswers(float*, float*, int, int);

	void CreateDivisionAnswers(float*, float*, int, int);

	int CheckIfValid(float*, float, int, float*);

	int CheckIfValidForAddition(float* ans, float num);

	int CheckIfValidForSubtraction(float* ans, float num, float* prob);

	int CheckIfValidForMultiplication(float* ans, float num);

	int CheckIfValidForDivision(float* ans, float num);

	void sort(float* arr);

};

extern ProblemCreator* m_ProblemCreator;

#endif