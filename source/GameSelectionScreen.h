#if !defined(_GAMESELECTIONSCREEN_H_)
#define _GAMESELECTIONSCREEN_H_

#include "scene.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "input.h"
#include "Resources.h"
#include "IwGx.h"
#include "s3eAudio.h"
#include "Iw2D.h"
#include "ProblemCreator.h"
#include "AdditionGame.h"

class GameSelectionScreen : public Scene {

protected:
	SpriteManager* spriteManager;
	Sprite* background;
	Sprite* difficultyButton1;
	Sprite* difficultyButton2;
	Sprite* difficultyButton3;
	Sprite* difficultyButton1Down;
	Sprite* difficultyButton2Down;
	Sprite* difficultyButton3Down;

	Sprite* additionGameButton;
	Sprite* subtractionGameButton;
	Sprite* multiplicationGameButton;
	Sprite* divisionGameButton;

	Label* difficultyLabel;
	Label* gameModesLabel;

public:
	GameSelectionScreen();
	~GameSelectionScreen();

	void Init();

	void Update(float deltaTime = 0.0f, float alphaMul = 1.0f);

	void Render();
};

#endif