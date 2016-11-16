#include "GlobalProperties.h"

GlobalProperties* g_pGlobalProperties = 0;

GlobalProperties::GlobalProperties() {
	s3eFile* sFile = s3eFileOpen("save.bin", "r");

	char tag[128];

	while (!s3eFileEOF(sFile)) {
		int i = 0;
		char x = s3eFileGetChar(sFile);
		while (i < 127 && x != '=') {
			if(x != ' ')
				tag[i] = x;
			x = s3eFileGetChar(sFile);
			i++;
		}
		tag[i] = 0;

		char strVal[20];
		i = 0;
		x = s3eFileGetChar(sFile);
		while (i < 19 && x != '\n' ) {
			strVal[i] = x;
			if (s3eFileEOF(sFile))
				break;
			x = s3eFileGetChar(sFile);
			i++;
		}
		strVal[i] = 0;

		int val = parseInt(strVal);

		DeterminePlace(tag, val);
	}

	s3eFileClose(sFile);
}

GlobalProperties::~GlobalProperties() {
	Save();
}

int GlobalProperties::parseInt(char * str) {
	int i = 0;
	int val = 0;
	while (str[i+1]) {
		i++;
	}
	int j = 0;
	while (i >= 0) {
		val += (str[i] - 48) * pow(10, j);
		i--;
		j++;
	}
	return val;
}

void GlobalProperties::DeterminePlace(char * tag, int val) {
	if (!strcmp(tag, "AdditionEasyHighScore")) {
		AdditionEasyHighScore = val;
	}
	else if (!strcmp(tag, "AdditionMediumHighScore")) {
		AdditionMediumHighScore = val;
	}
	else if (!strcmp(tag, "AdditionHardHighScore")) {
		AdditionHardHighScore = val;
	}

	else if (!strcmp(tag, "SubtractionEasyHighScore")) {
		SubtractionEasyHighScore = val;
	}
	else if (!strcmp(tag, "SubtractionMediumHighScore")) {
		SubtractionMediumHighScore = val;
	}
	else if (!strcmp(tag, "SubtractionHardHighScore")) {
		SubtractionHardHighScore = val;
	}

	else if (!strcmp(tag, "MultiplicationEasyHighScore")) {
		MultiplicationEasyHighScore = val;
	}
	else if (!strcmp(tag, "MultiplicationMediumHighScore")) {
		MultiplicationMediumHighScore = val;
	}
	else if (!strcmp(tag, "MultiplicationHardHighScore")) {
		MultiplicationHardHighScore = val;
	}

	else if (!strcmp(tag, "DivisionEasyHighScore")) {
		DivisionEasyHighScore = val;
	}
	else if (!strcmp(tag, "DivisionMediumHighScore")) {
		DivisionMediumHighScore = val;
	}
	else if (!strcmp(tag, "DivisionHardHighScore")) {
		DivisionHardHighScore = val;
	}
	else if (!strcmp(tag, "Difficulty")) {
		difficulty = val;
	}
}

void GlobalProperties::Save() {
	s3eFile* sFile = s3eFileOpen("save.bin", "w");

	char tag[128];
	sprintf(tag, "AdditionEasyHighScore=%d\n", AdditionEasyHighScore);
	s3eFilePrintf(sFile, tag);
	sprintf(tag, "AdditionMediumHighScore=%d\n", AdditionMediumHighScore);
	s3eFilePrintf(sFile, tag);
	sprintf(tag, "AdditionHardHighScore=%d\n", AdditionHardHighScore);
	s3eFilePrintf(sFile, tag);

	sprintf(tag, "SubtractionEasyHighScore=%d\n", SubtractionEasyHighScore);
	s3eFilePrintf(sFile, tag);
	sprintf(tag, "SubtractionMediumHighScore=%d\n", SubtractionMediumHighScore);
	s3eFilePrintf(sFile, tag);
	sprintf(tag, "SubtractionHardHighScore=%d\n", SubtractionHardHighScore);
	s3eFilePrintf(sFile, tag);

	sprintf(tag, "MultiplicationEasyHighScore=%d\n", MultiplicationEasyHighScore);
	s3eFilePrintf(sFile, tag);
	sprintf(tag, "MultiplicationMediumHighScore=%d\n", MultiplicationMediumHighScore);
	s3eFilePrintf(sFile, tag);
	sprintf(tag, "MultiplicationHardHighScore=%d\n", MultiplicationHardHighScore);
	s3eFilePrintf(sFile, tag);

	sprintf(tag, "DivisionEasyHighScore=%d\n", DivisionEasyHighScore);
	s3eFilePrintf(sFile, tag);
	sprintf(tag, "DivisionMediumHighScore=%d\n", DivisionMediumHighScore);
	s3eFilePrintf(sFile, tag);
	sprintf(tag, "DivisionHardHighScore=%d\n", DivisionHardHighScore);
	s3eFilePrintf(sFile, tag);

	sprintf(tag, "Difficulty=%d", difficulty);
	s3eFilePrintf(sFile, tag);

	s3eFileClose(sFile);
}