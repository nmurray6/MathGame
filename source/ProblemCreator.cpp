#include "ProblemCreator.h"

/*
Modes:
1 = addition
2 = subtraction
3 = multiplication
4 = division
*/
ProblemCreator* m_ProblemCreator = 0;

ProblemCreator::ProblemCreator() {
	srand(time(NULL));
	int i = 0;
	int j = 0;
	while (i < MAX_USED) {
		j = 0;
		while (j < MAX_NUMBERS_IN_EQUATION) {
			used[i][j] = 0.f;
			j++;
		}
		i++;
	}
}

ProblemCreator::~ProblemCreator() {
}

void ProblemCreator::createMathProblem(float prob[3], int diff, int mode) {
	if (mode == 1)
		createAdditionProblem(prob, diff);
	else if (mode == 2)
		createSubtractionProblem(prob, diff);
	else if (mode == 3)
		createMultiplicationProblem(prob, diff);
	else if (mode == 4)
		createDivisionProblem(prob, diff);
}

void ProblemCreator::createAdditionProblem(float prob[3], int diff) {
	prob[0] = 0.f;
	prob[1] = 0.f;
	prob[2] = 0.f;
	while (CheckIfUsed(prob)) {
		prob[0] = (float) (rand() % (int) pow(10, diff) + 1);
		prob[1] = (float) (rand() % (int) pow(10, diff) + 1);
		prob[2] = prob[0] + prob[1];
	}
	AddToUsed(prob);
}

void ProblemCreator::createSubtractionProblem(float prob[3], int diff) {
	prob[0] = 0.f;
	prob[1] = 0.f;
	prob[2] = 0.f;
	int count = 0;
	while (CheckIfUsed(prob)) {
		float a = (float)(rand() % ((int)pow(10, diff) + 10) + 1);
		float b = (float)(rand() % ((int)pow(10, diff) + 10) + 1);
		if (a > b) {
			prob[0] = a;
			prob[1] = b;
		}
		else {
			prob[0] = b;
			prob[1] = a;
		}
		prob[2] = prob[0] - prob[1];
		count++;
		if (count > 10)
			break;
	}
	
	AddToUsed(prob);
}

void ProblemCreator::createMultiplicationProblem(float prob[3], int diff) {
	prob[0] = 0.f;
	prob[1] = 0.f;
	prob[2] = 0.f;
	bool valid = false;
	while (CheckIfUsed(prob) || !valid) {
		if (diff == 1) {
			prob[0] = (float)(rand() % (int)pow(10, diff) + 1);
			prob[1] = (float)(rand() % (int)pow(10, diff) + 1);
			prob[2] = prob[0] * prob[1];
		}
		else if (diff == 2) {
			prob[0] = (float)(rand() % 25 + 1);
			prob[1] = (float)(rand() % 25 + 1);
			prob[2] = prob[0] * prob[1];
		}
		else if (diff == 3) {
			prob[0] = (float)(rand() % 50 + 1);
			prob[1] = (float)(rand() % 50 + 1);
			prob[2] = prob[0] * prob[1];
		}
		
		valid = false;
		if (diff == 1
			|| (diff == 2 && prob[2] < 200)
			|| (diff == 3 && prob[2] < 2000)) {
			valid = true;
			
		}
	}
	
	AddToUsed(prob);
}

void ProblemCreator::createDivisionProblem(float prob[3], int diff) {
	prob[0] = 0.f;
	prob[1] = 0.f;
	prob[2] = 0.f;
	bool valid = false;
	while (CheckIfUsed(prob) || !valid) {
		if (diff == 1) {
			prob[2] = (float)(rand() % (int)pow(10, diff) + 1);
			prob[1] = (float)(rand() % (int)pow(10, diff) + 1);
			prob[0] = prob[2] * prob[1];
		}
		else if (diff == 2) {
			prob[2] = (float)(rand() % 25 + 1);
			prob[1] = (float)(rand() % 25 + 1);
			prob[0] = prob[2] * prob[1];
		}
		else if (diff == 3) {
			prob[2] = (float)(rand() % 50 + 1);
			prob[1] = (float)(rand() % 50 + 1);
			prob[0] = prob[2] * prob[1];
		}
		valid = false;
		if (diff == 1
			|| (diff == 2 && prob[0] < 200)
			|| (diff == 3 && prob[0] < 2000)) {
			valid = true;

		}
	}
	AddToUsed(prob);
}

bool ProblemCreator::CheckIfUsed(float* prob) {
	int i = 0;
	//Safe check to make sure none of them are 0
	while (i < MAX_NUMBERS_IN_EQUATION - 1) {
		if (prob[i] == 0)
			return true;
		i++;
	}

	int conflict = 0;
	
	i = 0;
	int j = 0;
	int x = 0;

	for (i = 0; i < MAX_USED; i++) {
		conflict = 0;
		if (used[i][0] == prob[0]
			&& used[i][1] == prob[1]
			&& used[i][2] == prob[2])
			return true;
	}

/*	while (i < MAX_USED) {
		j = 0;
		conflict = 0;
		while (j < MAX_NUMBERS_IN_EQUATION - 1) {
			x = 0;
			while (x < MAX_NUMBERS_IN_EQUATION - 1) {
				if (used[i][x] == prob[j])
					conflict++;
				x++;
			}
			j++;
		}
		if (conflict >= MAX_NUMBERS_IN_EQUATION - 1)
			return true;
		i++;
	}*/
	return false;
}

void ProblemCreator::AddToUsed(float* num) {
	used[usedPlace][0] = num[0];
	used[usedPlace][1] = num[1];
	used[usedPlace][2] = num[2];
	usedPlace++;
	if (usedPlace >= MAX_USED)
		usedPlace = 0;


/*
	int x = 0;
	int y = 0;
	printf("USED PRINT START:\n");
	while (x < MAX_USED) {
		y = 0;
		while (y < MAX_NUMBERS_IN_EQUATION) {
			printf("%f, ", used[x][y]);
			y++;
		}
		printf("\n");
		x++;
	}
	printf("END USED PRINT\n ");*/
}

void ProblemCreator::CreateAnswers(float* prob, float* ans, int diff, int mode) {
	if (mode == 1)
		CreateAdditionAnswers(prob, ans, diff, mode);
	else if (mode == 2)
		CreateSubtractionAnswers(prob, ans, diff, mode);
	else if (mode == 3)
		CreateMultiplicationAnswers(prob, ans, diff, mode);
	else if (mode == 4)
		CreateDivisionAnswers(prob, ans, diff, mode);
	
}

void ProblemCreator::CreateAdditionAnswers(float* prob, float* ans, int diff, int mode) {
	ans[0] = prob[2];
	int y;
	bool comp = false;
	float num;
	int z = rand() % 2;
	if (ans[0] > 200) {
		if (z && ans[0] - 100.f > prob[0] && ans[0] - 100.f > prob[1]) {
			ans[1] = ans[0] - 100.f;
			}
		else {
			ans[1] = ans[0] + 100.f;
		}
			while (!comp) {
			z = rand() % 2;
			if (z) {
				num = ans[0] + rand() % ((diff * 10) / (diff + 1));
			}
			else {
				num = ans[0] - rand() % ((diff * 10) / (diff + 1));
			}
			if (CheckIfValid(ans, num, mode, prob)) {
				comp = true;
				ans[2] = num;
			}
		}
		comp = false;
		while (!comp) {
			z = rand() % 2;
			if (z) {
				num = ans[1] + rand() % ((diff * 10) / (diff + 1));
			}
			else {
				num = ans[1] - rand() % ((diff * 10) / (diff + 1));
			}
			if (CheckIfValid(ans, num, mode, prob)) {
				comp = true;
				ans[3] = num;
			}
		}
	}
	else if (prob[2] > 20) {
		if (z && ans[0] - 10.f > prob[0] && ans[0] - 10.f > prob[1]) {
			ans[1] = ans[0] - 10.f;
		}
		else {
			ans[1] = ans[0] + 10.f;
		}

		while (!comp) {
			z = rand() % 2;
			if (z) {
				num = ans[0] + rand() % ((diff * 10) / (diff + 1));
			}
			else {
				num = ans[0] - rand() % ((diff * 10) / (diff + 1));
			}
			if (CheckIfValid(ans, num, mode, prob)) {
				comp = true;
				ans[2] = num;
			}
		}
		comp = false;
		while (!comp) {
			z = rand() % 2;
			if (z) {
				num = ans[1] + rand() % ((diff * 10) / (diff + 1));
			}
			else {
				num = ans[1] - rand() % ((diff * 10) / (diff + 1));
			}
			if (CheckIfValid(ans, num, mode, prob)) {
				comp = true;
				ans[3] = num;
			}
		}
	}
	else {
		for (y = 1; y < 4; y++) {
			while (!comp) {
				z = rand() % 2;
				if (z) {
					num = prob[2] + rand() % ((diff * 10) / (diff + 1));
				}
				else {
					num = prob[2] - rand() % ((diff * 10) / (diff + 1));
				}
				if (CheckIfValid(ans, num, mode, prob)) {
					comp = true;
					ans[y] = num;
				}
			}
			comp = false;
		}
	}
	sort(ans);
}

void ProblemCreator::CreateSubtractionAnswers(float* prob, float* ans, int diff, int mode) {
	ans[0] = prob[2];
	int y;
	bool comp = false;
	float num;
	int z = rand() % 2;
	if (prob[0] > 201 || prob[1] > 201) {
		if (z && ans[0] - 100.f > 0) {
			ans[1] = ans[0] - 100.f;
		}
		else {
			ans[1] = ans[0] + 100.f;
		}
		while (!comp) {
			z = rand() % 2;
			if (z) {
				num = ans[0] + rand() % ((diff * 10) / (diff + 1));
			}
			else {
				num = ans[0] - rand() % ((diff * 10) / (diff + 1));
			}
			if (CheckIfValid(ans, num, mode, prob)) {
				comp = true;
				ans[2] = num;
			}
		}
		comp = false;
		while (!comp) {
			z = rand() % 2;
			if (z) {
				num = ans[1] + rand() % ((diff * 10) / (diff + 1));
			}
			else {
				num = ans[1] - rand() % ((diff * 10) / (diff + 1));
			}
			if (CheckIfValid(ans, num, mode, prob)) {
				comp = true;
				ans[3] = num;
			}
		}
	}
	else if (prob[0] > 21 || prob[1] > 21) {
		if (z && ans[0] - 10.f > 0) {
			ans[1] = ans[0] - 10.f;
		}
		else {
			ans[1] = ans[0] + 10.f;
		}

		while (!comp) {
			z = rand() % 2;
			if (z) {
				num = ans[0] + rand() % ((diff * 10) / (diff + 1));
			}
			else {
				num = ans[0] - rand() % ((diff * 10) / (diff + 1));
			}
			if (CheckIfValid(ans, num, mode, prob)) {
				comp = true;
				ans[2] = num;
			}
		}
		comp = false;
		while (!comp) {
			z = rand() % 2;
			if (z) {
				num = ans[1] + rand() % ((diff * 10) / (diff + 1));
			}
			else {
				num = ans[1] - rand() % ((diff * 10) / (diff + 1));
			}
			if (CheckIfValid(ans, num, mode, prob)) {
				comp = true;
				ans[3] = num;
			}
		}
	}
	else {
		for (y = 1; y < 4; y++) {
			while (!comp) {
				z = rand() % 2;
				if (z) {
					num = prob[2] + rand() % ((diff * 10) / (diff + 1));
				}
				else {
					num = prob[2] - rand() % ((diff * 10) / (diff + 1));
				}
				if (CheckIfValid(ans, num, mode, prob)) {
					comp = true;
					ans[y] = num;
				}
			}
			comp = false;
		}
	}
	sort(ans);
}

void ProblemCreator::CreateMultiplicationAnswers(float* prob, float* ans, int diff, int mode) {
	ans[0] = prob[2];
	int y;
	bool comp = false;
	float num;
	int z = rand() % 2;
	for (y = 1; y < 4; y++) {
		while (!comp) {
			z = rand() % 2;
			if (z) {
				num = prob[0] * (prob[1] + rand() % ((diff * 10) / (diff + 1)));
			}
			else {
				num = prob[0] * (prob[1] - rand() % ((diff * 10) / (diff + 1)));
			}
			if (CheckIfValid(ans, num, mode, prob)) {
				comp = true;
				ans[y] = num;
			}
		}
		comp = false;
	}
	sort(ans);
}

void ProblemCreator::CreateDivisionAnswers(float* prob, float* ans, int diff, int mode) {
	ans[0] = prob[2];
	int x;
	float posOffset = ans[0] + 1;
	float negOffset = ans[0] - 1;
	bool found = false;
	for (x = 1; x < 4; x++) {
		float rem;
		while (!found) {
			int z = rand() % 2;
			if (!z && negOffset > 1) {
				if ((int)prob[0] % (int)negOffset == 0) {
					ans[x] = negOffset;
					found = true;
				}
				negOffset--;
			}
			else {
				
				if ((int)prob[0] % (int)posOffset == 0) {
					ans[x] = posOffset;
					found = true;
				}
				else if (posOffset > prob[0]) {
					float num;
					while (!found) {
						z = rand() % 2;
						if (z) {
							num = prob[2] + rand() % ((diff * 10) / (diff + 1));
						}
						else {
							num = prob[2] - rand() % ((diff * 10) / (diff + 1));
						}
						if (CheckIfValid(ans, num, mode, prob)) {
							found = true;
							ans[x] = num;
						}
					}
				}
				posOffset++;
			}
		}
		found = false;
	}
	sort(ans);
}

int ProblemCreator::CheckIfValid(float* ans, float num, int mode, float* prob) {
	int valid = 1;
	int x;
	for (x = 0; x < 4; x++) {
		if (ans[x] == num) {
			valid = 0;
			break;
		}
	}
	if (mode == 1 && !CheckIfValidForAddition(prob, num)
		|| mode == 2 && !CheckIfValidForSubtraction(prob, num, prob)
		|| mode == 3 && !CheckIfValidForMultiplication(prob, num)
		|| mode == 4 && !CheckIfValidForDivision(prob, num))
		valid = 0;
	return valid;
}

int ProblemCreator::CheckIfValidForAddition(float* ans, float num) {
	if (num <= ans[0] 
		|| num <= ans[1] 
		|| num < 2)
		return 0;
	return 1;
}

int ProblemCreator::CheckIfValidForSubtraction(float* ans, float num, float* prob) {
	if (num >= 0 && num <= 4 && prob[0] <= 4)
		return 1;
	if ((ans[0] > ans[1] && num > ans[0])
		|| (ans[1] > ans[0] && num > ans[1])
		|| num < 0)
		return 0;
	return 1;
}

int ProblemCreator::CheckIfValidForMultiplication(float* ans, float num) {
	if (num < 1)
		return 0;
	return 1;
}

int ProblemCreator::CheckIfValidForDivision(float* ans, float num) {
	if (num < 1)
		return 0;
	return 1;
}

void ProblemCreator::sort(float* arr) {
	int i = 0;
	int j = 1;
	while (i < 3) {
		j = i + 1;
		while (j < 4) {
			if (arr[j] < arr[i]) {
				float temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
			j++;
		}
		i++;
	}
}