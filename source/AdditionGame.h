#if !defined(_ADDITIONGAME_H_)
#define _ADDITIONGAME_H_

#include "scene.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "input.h"
#include "Resources.h"
#include "IwGx.h"
#include "s3eAudio.h"
#include "Iw2D.h"
#include "ProblemCreator.h"
#include "UIHelper.h"
#include "Label.h"
#include "GlobalProperties.h"
#include "s3eVibra.h"


class AdditionGame : public Scene {

protected:
	SpriteManager* spriteManager;
	Sprite* background;
	Sprite* timerBackground;
	Sprite* playButton;
	Sprite* answerButton1;
	Sprite* answerButton2;
	Sprite* answerButton3;
	Sprite* answerButton4;
	Sprite* answerButtonCorrect;
	Sprite* answerButtonWrong;
	Sprite* XButton;
	float prob[3] = { 0, 0, 0 };
	float ans[4] = { 0, 0, 0, 0 };
	int score = 0;
	int prevDiff = 1;
	int prevMode = 1;
	int gameOver = 0;
	bool reset = false;
	bool escapeMenu = false;
	float maxTimer = 10000.f;
	float timer = 10000.f;
	float shift = 240.f;
	float timeKnockback = 5000.f;
	float maxTimeKnockback = 5000.f;
	float problemNumber = 1;
	int mode = 1;
	float scale;
	float answerDisplayTimer = 0.f;
	float answerDisplay = 1250.f;
	bool displayAnswer = false;

	Label* scoreText;
	Label* problemText;
	Label* ab1Text;
	Label* ab2Text;
	Label* ab3Text;
	Label* ab4Text;

public:
	AdditionGame();
	~AdditionGame();

	void Init();

	void Update(float deltaTime = 0.0f, float alphaMul = 1.0f);

	void Render();

	void handleAnswerInput(int);

	void handleCorrect();

	void handleIncorrect();

	void handleTimeout();

	void Reset();

	void updateHighScore();

	void displayWrongAndCorrect();

	void initButtonCorrect(int);

	void initButtonWrong(int);
};

#endif