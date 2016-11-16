#if !defined(_ADDITION_GAME_H_)
#define _ADDITION_GAME_H_

#include "scene.h"
#include "input.h"
#include "Resources.h"
#include "IwGx.h"
#include "IwHashString.h"
#include "ProblemCreator.h"
#include "Sprite.h"
#include "SpriteManager.h"

class GameMode : public Scene {
public:
	bool isActive;

protected:
	SpriteManager* spriteManager;
	int currentRoundedScore;
	float currentActualScore;

	CLabel* scoreLabel;
	CLabel* equation;
	Sprite* background;

private:
	void initUI();

public:
	GameMode(){}
	~GameMode();

	void Init();
	void Update(float, float);
	void Render();
	
	void addToRoundScore(int score);
	void gameOver();
};

#endif