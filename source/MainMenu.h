#if !defined(_MAINMENU_H_)
#define _MAINMENU_H_

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

class MainMenu : public Scene {

protected:
	SpriteManager* spriteManager;
	Sprite* background;
	Sprite* playButton;
	Sprite* practiceButton;

	int difficulty = 1;

public:
	MainMenu();
	~MainMenu();

	void Init();

	void Update(float deltaTime = 0.0f, float alphaMul = 1.0f);

	void Render();
};

#endif