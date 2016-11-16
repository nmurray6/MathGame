#include "UIHelper.h"

UIHelper* g_pUIHelper = 0;

UIHelper::UIHelper() {
	spriteManager = new SpriteManager();
	inmobi_set_loglevel(1);
	inmobi_initialize("7278f55929434cea95be9050e659ab06");
}

UIHelper::~UIHelper() {
	delete spriteManager;
}

void UIHelper::Init() {
	background = new Sprite();
	background->SetImage(g_pResources->getGameOverBackground());
	background->m_W = background->GetImage()->GetWidth();
	background->m_H = background->GetImage()->GetHeight();
	background->m_AnchorX = 0.5f;
	background->m_AnchorY = 0.5f;
	background->isVisible = false;
	spriteManager->AddSprite(background);

	mainMenuButton = new Sprite();
	mainMenuButton->SetImage(g_pResources->getMainMenuButton());
	mainMenuButton->m_W = mainMenuButton->GetImage()->GetWidth();
	mainMenuButton->m_H = mainMenuButton->GetImage()->GetHeight();
	mainMenuButton->m_AnchorX = 0.5f;
	mainMenuButton->m_AnchorY = 0.5f;
	mainMenuButton->isVisible = false;
	spriteManager->AddSprite(mainMenuButton);
	
	restartButton = new Sprite();
	restartButton->SetImage(g_pResources->getRestartButton());
	restartButton->m_W = restartButton->GetImage()->GetWidth();
	restartButton->m_H = restartButton->GetImage()->GetHeight();
	restartButton->m_AnchorX = 0.5f;
	restartButton->m_AnchorY = 0.5f;
	restartButton->isVisible = false;
	spriteManager->AddSprite(restartButton);

	gameModeButton = new Sprite();
	gameModeButton->SetImage(g_pResources->getModesButton());
	gameModeButton->m_W = gameModeButton->GetImage()->GetWidth();
	gameModeButton->m_H = gameModeButton->GetImage()->GetHeight();
	gameModeButton->m_AnchorX = 0.5f;
	gameModeButton->m_AnchorY = 0.5f;
	gameModeButton->isVisible = false;
	spriteManager->AddSprite(gameModeButton);

	cancelButton = new Sprite();
	cancelButton->SetImage(g_pResources->getCancelButton());
	cancelButton->m_W = cancelButton->GetImage()->GetWidth();
	cancelButton->m_H = cancelButton->GetImage()->GetHeight();
	cancelButton->m_AnchorX = 0.5f;
	cancelButton->m_AnchorY = 0.5f;
	cancelButton->isVisible = false;
	spriteManager->AddSprite(cancelButton);

	CIwFVec2 region(570, 600);
	float fontScale = IwGxGetScreenHeight() / (float)region.y;

	scoreText = new Label();
	scoreText->scale = fontScale;
	scoreText->font = g_pResources->getTextFont();
	scoreText->isVisible = false;
	spriteManager->AddLabel(scoreText);
}

void UIHelper::gameOverInit() {
	background->m_X = (float)IwGxGetScreenWidth() / 2;
	background->m_Y = (float)IwGxGetScreenHeight() / 2;
	float scale = MAX((float)IwGxGetScreenHeight() / (float)g_pResources->getBackground()->GetHeight(), (float)IwGxGetScreenWidth() / (float)g_pResources->getBackground()->GetWidth());
	background->m_H = background->GetImage()->GetHeight() * scale;
	background->m_W = background->GetImage()->GetWidth() * scale;
	background->isVisible = true;

	mainMenuButton->m_H = mainMenuButton->GetImage()->GetHeight() * scale;
	mainMenuButton->m_W = mainMenuButton->GetImage()->GetWidth() * scale;
	mainMenuButton->m_X = background->m_X;
	mainMenuButton->m_Y = background->m_Y - 100.f * scale;
	mainMenuButton->isVisible = true;

	gameModeButton->m_X = background->m_X;
	gameModeButton->m_Y = mainMenuButton->m_Y + mainMenuButton->m_H + 5 * scale;
	gameModeButton->m_H = gameModeButton->GetImage()->GetHeight() * scale;
	gameModeButton->m_W = gameModeButton->GetImage()->GetWidth() * scale;
	gameModeButton->isVisible = true;

	restartButton->m_X = background->m_X;
	restartButton->m_Y = gameModeButton->m_Y + gameModeButton->m_H + 5 * scale;
	restartButton->m_H = restartButton->GetImage()->GetHeight() * scale;
	restartButton->m_W = restartButton->GetImage()->GetWidth() * scale;
	restartButton->isVisible = true;

	scoreText->m_X = background->m_X - background->m_W / 2;
	scoreText->m_Y = background->m_Y - background->m_H / 3;
	scoreText->m_W = background->m_W;
	scoreText->m_H = 100.f * scale;
	scoreText->isVisible = true;
}

void UIHelper::GameOverDisplay() {
	spriteManager->Render();

	
	char string[120];
	switch (g_pSceneManager->GetCurrent()->GetSceneMode()) {
	case 1: //addition
		switch (g_pSceneManager->GetCurrent()->GetSceneDifficulty()) {
		case 1:
			sprintf(string, "Score: %d   High Score: %d", gameScore, g_pGlobalProperties->AdditionEasyHighScore);
			break;

		case 2:
			sprintf(string, "Score: %d   High Score: %d", gameScore, g_pGlobalProperties->AdditionMediumHighScore);
			break;

		case 3:
			sprintf(string, "Score: %d   High Score: %d", gameScore, g_pGlobalProperties->AdditionMediumHighScore);
			break;
		}
		break;

	case 2://subtraction
		switch (g_pSceneManager->GetCurrent()->GetSceneDifficulty()) {
		case 1:
			sprintf(string, "Score: %d   High Score: %d", gameScore, g_pGlobalProperties->SubtractionEasyHighScore);
			break;

		case 2:
			sprintf(string, "Score: %d   High Score: %d", gameScore, g_pGlobalProperties->SubtractionMediumHighScore);
			break;

		case 3:
			sprintf(string, "Score: %d   High Score: %d", gameScore, g_pGlobalProperties->SubtractionMediumHighScore);
			break;
		}
		break;

	case 3://multiplication
		switch (g_pSceneManager->GetCurrent()->GetSceneDifficulty()) {
		case 1:
			sprintf(string, "Score: %d   High Score: %d", gameScore, g_pGlobalProperties->MultiplicationEasyHighScore);
			break;

		case 2:
			sprintf(string, "Score: %d   High Score: %d", gameScore, g_pGlobalProperties->MultiplicationMediumHighScore);
			break;

		case 3:
			sprintf(string, "Score: %d   High Score: %d", gameScore, g_pGlobalProperties->MultiplicationMediumHighScore);
			break;
		}
		break;

	case 4://division
		switch (g_pSceneManager->GetCurrent()->GetSceneDifficulty()) {
		case 1:
			sprintf(string, "Score: %d   High Score: %d", gameScore, g_pGlobalProperties->DivisionEasyHighScore);
			break;

		case 2:
			sprintf(string, "Score: %d   High Score: %d", gameScore, g_pGlobalProperties->DivisionMediumHighScore);
			break;

		case 3:
			sprintf(string, "Score: %d   High Score: %d", gameScore, g_pGlobalProperties->DivisionMediumHighScore);
			break;
		}
		break;
	}

	scoreText->SetText(string);

	DisplayBannerAd();
}

int UIHelper::GameOverMenuUpdate(int& score, bool& reset) {
	gameScore = score;
	if (!g_pInput->touched && g_pInput->prevTouched) {
		g_pInput->Reset();

		if (mainMenuButton->HitTest(g_pInput->m_X, g_pInput->m_Y)) {
			g_pSceneManager->SwitchTo(g_pSceneManager->Find("mainMenu"));
			score = 0;
			reset = true;
			background->isVisible = false;
			mainMenuButton->isVisible = false;
			gameModeButton->isVisible = false;
			restartButton->isVisible = false;
			scoreText->isVisible = false;
			return 0;
		}
		else if (gameModeButton->HitTest(g_pInput->m_X, g_pInput->m_Y)) {
			g_pSceneManager->SwitchTo(g_pSceneManager->Find("gameSelectionScreen"));
			reset = true;
			background->isVisible = false;
			mainMenuButton->isVisible = false;
			gameModeButton->isVisible = false;
			restartButton->isVisible = false;
			scoreText->isVisible = false;
			return 0;
		}
		else if (restartButton->HitTest(g_pInput->m_X, g_pInput->m_Y)) {
			score = 0;
			reset = true;
			background->isVisible = false;
			mainMenuButton->isVisible = false;
			gameModeButton->isVisible = false;
			restartButton->isVisible = false;
			scoreText->isVisible = false;
			return 0;
		}
	}
	return 1;
}

void UIHelper::EscapeMenuInit() {
	background->m_X = (float)IwGxGetScreenWidth() / 2;
	background->m_Y = (float)IwGxGetScreenHeight() / 2;
	float scale = MAX((float)IwGxGetScreenHeight() / (float)g_pResources->getBackground()->GetHeight(), (float)IwGxGetScreenWidth() / (float)g_pResources->getBackground()->GetWidth());
	background->m_H = background->GetImage()->GetHeight() * scale;
	background->m_W = background->GetImage()->GetWidth() * scale;
	background->isVisible = true;

	mainMenuButton->m_X = background->m_X;
	mainMenuButton->m_Y = background->m_Y - 50 * scale;
	mainMenuButton->m_H = mainMenuButton->GetImage()->GetHeight() * scale;
	mainMenuButton->m_W = mainMenuButton->GetImage()->GetWidth() * scale;
	mainMenuButton->isVisible = true;

	gameModeButton->m_X = background->m_X;
	gameModeButton->m_Y = mainMenuButton->m_Y + mainMenuButton->m_H + 5;
	gameModeButton->m_H = gameModeButton->GetImage()->GetHeight() * scale;
	gameModeButton->m_W = gameModeButton->GetImage()->GetWidth() * scale;
	gameModeButton->isVisible = true;

	cancelButton->m_X = background->m_X;
	cancelButton->m_Y = gameModeButton->m_Y + gameModeButton->m_H + 5;
	cancelButton->m_H = cancelButton->GetImage()->GetHeight() * scale;
	cancelButton->m_W = cancelButton->GetImage()->GetWidth() * scale;
	cancelButton->isVisible = true;

	
}

void UIHelper::EscapeMenuDisplay() {
	spriteManager->Render();
	DisplayBannerAd();
}

void UIHelper::EscapeMenuUpdate(bool& active, bool& reset) {
	if (!g_pInput->touched && g_pInput->prevTouched) {
		g_pInput->Reset();

		if (mainMenuButton->HitTest(g_pInput->m_X, g_pInput->m_Y)) {
			g_pSceneManager->SwitchTo(g_pSceneManager->Find("mainMenu"));
			reset = true;
			background->isVisible = false;
			mainMenuButton->isVisible = false;
			cancelButton->isVisible = false;
			gameModeButton->isVisible = false;
			active = false;
		}
		else if (gameModeButton->HitTest(g_pInput->m_X, g_pInput->m_Y)) {
			g_pSceneManager->SwitchTo(g_pSceneManager->Find("gameSelectionScreen"));
			reset = true;
			background->isVisible = false;
			mainMenuButton->isVisible = false;
			cancelButton->isVisible = false;
			gameModeButton->isVisible = false;
			active = false;
		}
		else if (cancelButton->HitTest(g_pInput->m_X, g_pInput->m_Y)) {
			background->isVisible = false;
			mainMenuButton->isVisible = false;
			cancelButton->isVisible = false;
			gameModeButton->isVisible = false;
			active = false;
		}
		else if (!background->HitTest(g_pInput->m_X, g_pInput->m_Y)) {
			background->isVisible = false;
			mainMenuButton->isVisible = false;
			cancelButton->isVisible = false;
			gameModeButton->isVisible = false;
			active = false;
		}
	}
}

void UIHelper::DisplayBannerAd() {
	if (s3eInMobiAdsAvailable() == S3E_TRUE) {
		InMobiAd* ad = inmobi_banner_init("1470686986410", INMOBIADS_BANNER_SIZE_320x50, 0, 0);
		inmobi_banner_load(ad, "age:25,education:EDUCATION_HIGHSCHOOLORLESS");
	}
}