#if !defined(_UIHELPER_H_)
#define _UIHELPER_H_

#include "scene.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "input.h"
#include "Resources.h"
#include "IwGx.h"
#include "s3eAudio.h"
#include "Iw2D.h"
#include "ProblemCreator.h"
#include "GlobalProperties.h"
#include "s3eInMobiAds.h"

class UIHelper {
protected:
	SpriteManager* spriteManager;

	Sprite* background;
	Sprite* mainMenuButton;
	Sprite* restartButton;
	Sprite* gameModeButton;
	Sprite* cancelButton;
	Label* scoreText;

	int gameScore;

	float gameOverScale = 1.f;
	float escapeMenuScale = 1.f;

public:
	UIHelper();
	~UIHelper();

	void Init();

	void gameOverInit();

	void GameOverDisplay();

	int GameOverMenuUpdate(int&, bool&);

	void EscapeMenuInit();
	
	void EscapeMenuDisplay();

	void EscapeMenuUpdate(bool&, bool&);

	void DisplayBannerAd();
};

extern UIHelper* g_pUIHelper;

#endif