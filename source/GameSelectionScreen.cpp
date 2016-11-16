#include "GameSelectionScreen.h"

GameSelectionScreen::GameSelectionScreen() {
	spriteManager = new SpriteManager();
}

GameSelectionScreen::~GameSelectionScreen() {
	delete spriteManager;
}

void GameSelectionScreen::Update(float deltaTime, float alphaMul) {
	if (!m_IsActive)
		return;

	Scene::Update(deltaTime, alphaMul);

	if (m_IsInputActive && m_Manager->GetCurrent() == this && !g_pInput->touched && g_pInput->prevTouched) {
		g_pInput->Reset();
		if (difficultyButton1->HitTest(g_pInput->m_X, g_pInput->m_Y)) {
			difficultyButton1->isVisible = false;
			difficultyButton2->isVisible = true;
			difficultyButton3->isVisible = true;
			difficultyButton1Down->isVisible = true;
			difficultyButton2Down->isVisible = false;
			difficultyButton3Down->isVisible = false;

			g_pGlobalProperties->difficulty = 1;
		}
		else if (difficultyButton2->HitTest(g_pInput->m_X, g_pInput->m_Y)) {
			difficultyButton1->isVisible = true;
			difficultyButton2->isVisible = false;
			difficultyButton3->isVisible = true;
			difficultyButton1Down->isVisible = false;
			difficultyButton2Down->isVisible = true;
			difficultyButton3Down->isVisible = false;

			g_pGlobalProperties->difficulty = 2;
		}
		else if (difficultyButton3->HitTest(g_pInput->m_X, g_pInput->m_Y)) {
			difficultyButton1->isVisible = true;
			difficultyButton2->isVisible = true;
			difficultyButton3->isVisible = false;
			difficultyButton1Down->isVisible = false;
			difficultyButton2Down->isVisible = false;
			difficultyButton3Down->isVisible = true;
			
			g_pGlobalProperties->difficulty = 3;
		}
		else if (additionGameButton->HitTest(g_pInput->m_X, g_pInput->m_Y)) {
			Scene* temp = g_pSceneManager->Find("additionGame");
			temp->SetSceneDifficulty(g_pGlobalProperties->difficulty);
			temp->SetSceneMode(1);
			g_pSceneManager->SwitchTo(temp);
		}
		else if (subtractionGameButton->HitTest(g_pInput->m_X, g_pInput->m_Y)) {
			Scene* temp = g_pSceneManager->Find("additionGame");
			temp->SetSceneDifficulty(g_pGlobalProperties->difficulty);
			temp->SetSceneMode(2);
			g_pSceneManager->SwitchTo(temp);
		}
		else if (multiplicationGameButton->HitTest(g_pInput->m_X, g_pInput->m_Y)) {
			Scene* temp = g_pSceneManager->Find("additionGame");
			temp->SetSceneDifficulty(g_pGlobalProperties->difficulty);
			temp->SetSceneMode(3);
			g_pSceneManager->SwitchTo(temp);
		}
		else if (divisionGameButton->HitTest(g_pInput->m_X, g_pInput->m_Y)) {
			Scene* temp = g_pSceneManager->Find("additionGame");
			temp->SetSceneDifficulty(g_pGlobalProperties->difficulty);
			temp->SetSceneMode(4);
			g_pSceneManager->SwitchTo(temp);
		}
	}
}

void GameSelectionScreen::Render() {
	if (!m_IsActive)
		return;

	Scene::Render();



	spriteManager->Render();
}

void GameSelectionScreen::Init() {
	Scene::Init();

	GameSelectionScreen* menu = (GameSelectionScreen*)g_pSceneManager->Find("gameSelectionScreen");

	background = new Sprite();

	background->m_X = (float)IwGxGetScreenWidth() / 2;
	background->m_Y = (float)IwGxGetScreenHeight() / 2;
	background->SetImage(g_pResources->getBackground());
	float scale = MAX((float)IwGxGetScreenHeight() / (float)background->GetImage()->GetHeight(), (float)IwGxGetScreenWidth() / (float)background->GetImage()->GetWidth());
	background->m_W = background->GetImage()->GetWidth() * scale;
	background->m_H = background->GetImage()->GetHeight() * scale;
	background->m_AnchorX = 0.5f;
	background->m_AnchorY = 0.5f;

	spriteManager->AddSprite(background);

	//add in 3 difficulty buttons
	difficultyButton2 = new Sprite();
	difficultyButton2->m_X = (float)IwGxGetScreenWidth() / 2;
	difficultyButton2->m_Y = 180.f * scale;
	difficultyButton2->SetImage(g_pResources->getDifficultyButton2());
	difficultyButton2->m_W = difficultyButton2->GetImage()->GetWidth() * scale;
	difficultyButton2->m_H = difficultyButton2->GetImage()->GetHeight() * scale;
	difficultyButton2->m_AnchorX = 0.5f;
	difficultyButton2->m_AnchorY = 0.f;
	if (g_pGlobalProperties->difficulty == 2)
		difficultyButton2->isVisible = false;
	spriteManager->AddSprite(difficultyButton2);

	difficultyButton1 = new Sprite();
	difficultyButton1->m_X = difficultyButton2->m_X - (difficultyButton2->GetImage()->GetWidth() * scale / 2) - (g_pResources->getDifficultyButton1()->GetWidth() * scale / 2) + 1;
	difficultyButton1->m_Y = 180.f * scale;
	difficultyButton1->SetImage(g_pResources->getDifficultyButton1());
	difficultyButton1->m_W = difficultyButton1->GetImage()->GetWidth() * scale;
	difficultyButton1->m_H = difficultyButton1->GetImage()->GetHeight() * scale;
	difficultyButton1->m_AnchorX = 0.5f;
	difficultyButton1->m_AnchorY = 0.f;
	if (g_pGlobalProperties->difficulty == 1)
		difficultyButton1->isVisible = false;
	spriteManager->AddSprite(difficultyButton1);



	difficultyButton3 = new Sprite();
	difficultyButton3->m_X = difficultyButton2->m_X + (difficultyButton2->GetImage()->GetWidth() * scale / 2) + (g_pResources->getDifficultyButton3()->GetWidth() * scale / 2);
	difficultyButton3->m_Y = 180.f * scale;
	difficultyButton3->SetImage(g_pResources->getDifficultyButton3());
	difficultyButton3->m_W = difficultyButton3->GetImage()->GetWidth() * scale;
	difficultyButton3->m_H = difficultyButton3->GetImage()->GetHeight() * scale;
	difficultyButton3->m_AnchorX = 0.5f;
	difficultyButton3->m_AnchorY = 0.f;
	if (g_pGlobalProperties->difficulty == 3)
		difficultyButton3->isVisible = false;
	spriteManager->AddSprite(difficultyButton3);

	difficultyButton2Down = new Sprite();
	difficultyButton2Down->m_X = difficultyButton2->m_X;
	difficultyButton2Down->m_Y = difficultyButton2->m_Y;
	difficultyButton2Down->SetImage(g_pResources->getDifficultyButton2Down());
	difficultyButton2Down->m_W = difficultyButton2Down->GetImage()->GetWidth() * scale;
	difficultyButton2Down->m_H = difficultyButton2Down->GetImage()->GetHeight() * scale;
	difficultyButton2Down->m_AnchorX = 0.5f;
	difficultyButton2Down->m_AnchorY = 0.f;
	if (g_pGlobalProperties->difficulty == 2)
		difficultyButton2Down->isVisible = true;
	else
		difficultyButton2Down->isVisible = false;
	spriteManager->AddSprite(difficultyButton2Down);

	difficultyButton1Down = new Sprite();
	difficultyButton1Down->m_X = difficultyButton1->m_X;
	difficultyButton1Down->m_Y = difficultyButton1->m_Y;
	difficultyButton1Down->SetImage(g_pResources->getDifficultyButton1Down());
	difficultyButton1Down->m_W = difficultyButton1Down->GetImage()->GetWidth() * scale;
	difficultyButton1Down->m_H = difficultyButton1Down->GetImage()->GetHeight() * scale;
	difficultyButton1Down->m_AnchorX = 0.5f;
	difficultyButton1Down->m_AnchorY = 0.f;
	if(g_pGlobalProperties->difficulty == 1)
		difficultyButton1Down->isVisible = true;
	else
		difficultyButton1Down->isVisible = false;
	spriteManager->AddSprite(difficultyButton1Down);



	difficultyButton3Down = new Sprite();
	difficultyButton3Down->m_X = difficultyButton3->m_X;
	difficultyButton3Down->m_Y = difficultyButton3->m_Y;
	difficultyButton3Down->SetImage(g_pResources->getDifficultyButton3Down());
	difficultyButton3Down->m_W = difficultyButton3Down->GetImage()->GetWidth() * scale;
	difficultyButton3Down->m_H = difficultyButton3Down->GetImage()->GetHeight() * scale;
	difficultyButton3Down->m_AnchorX = 0.5f;
	difficultyButton3Down->m_AnchorY = 0.f;
	if (g_pGlobalProperties->difficulty == 3)
		difficultyButton3Down->isVisible = true;
	else
		difficultyButton3Down->isVisible = false;
	spriteManager->AddSprite(difficultyButton3Down);


	float shift = 700.f;

	additionGameButton = new Sprite();
	additionGameButton->m_X = (float)IwGxGetScreenWidth() / 2;
	additionGameButton->m_Y = shift * scale;
	additionGameButton->SetImage(g_pResources->getAdditionGameButton());
	additionGameButton->m_W = additionGameButton->GetImage()->GetWidth() * scale;
	additionGameButton->m_H = additionGameButton->GetImage()->GetHeight() * scale;
	additionGameButton->m_AnchorX = 0.5f;
	additionGameButton->m_AnchorY = 0.5f;
	spriteManager->AddSprite(additionGameButton);

	subtractionGameButton = new Sprite();
	subtractionGameButton->m_X = (float)IwGxGetScreenWidth() / 2;
	subtractionGameButton->m_Y = additionGameButton->m_Y + additionGameButton->m_H + 20.f * scale;
	subtractionGameButton->SetImage(g_pResources->getSubtractionGameButton());
	subtractionGameButton->m_W = subtractionGameButton->GetImage()->GetWidth() * scale;
	subtractionGameButton->m_H = subtractionGameButton->GetImage()->GetHeight() * scale;
	subtractionGameButton->m_AnchorX = 0.5f;
	subtractionGameButton->m_AnchorY = 0.5f;
	spriteManager->AddSprite(subtractionGameButton);

	multiplicationGameButton = new Sprite();
	multiplicationGameButton->m_X = (float)IwGxGetScreenWidth() / 2;
	multiplicationGameButton->m_Y = subtractionGameButton->m_Y + subtractionGameButton->m_H + 20.f * scale;
	multiplicationGameButton->SetImage(g_pResources->getMultiplicationGameButton());
	multiplicationGameButton->m_W = multiplicationGameButton->GetImage()->GetWidth() * scale;
	multiplicationGameButton->m_H = multiplicationGameButton->GetImage()->GetHeight() * scale;
	multiplicationGameButton->m_AnchorX = 0.5f;
	multiplicationGameButton->m_AnchorY = 0.5f;
	spriteManager->AddSprite(multiplicationGameButton);

	divisionGameButton = new Sprite();
	divisionGameButton->m_X = (float)IwGxGetScreenWidth() / 2;
	divisionGameButton->m_Y = multiplicationGameButton->m_Y + multiplicationGameButton->m_H + 20.f * scale;
	divisionGameButton->SetImage(g_pResources->getDivisionGameButton());
	divisionGameButton->m_W = divisionGameButton->GetImage()->GetWidth() * scale;
	divisionGameButton->m_H = divisionGameButton->GetImage()->GetHeight() * scale;
	divisionGameButton->m_AnchorX = 0.5f;
	divisionGameButton->m_AnchorY = 0.5f;
	spriteManager->AddSprite(divisionGameButton);

	float fontScale = IwGxGetScreenHeight() / 600.f;

	difficultyLabel = new Label();
	difficultyLabel->m_X = 0;
	difficultyLabel->m_Y = 100.f * scale;
	difficultyLabel->m_W = IwGxGetScreenWidth();
	difficultyLabel->m_H = 0;
	difficultyLabel->scale = fontScale;
	difficultyLabel->font = g_pResources->getLargeGameFont();
	difficultyLabel->SetText("Difficulty");
	spriteManager->AddLabel(difficultyLabel);

	gameModesLabel = new Label();
	gameModesLabel->m_X = 0;
	gameModesLabel->m_Y = additionGameButton->m_Y - 180.f * scale;
	gameModesLabel->m_W = IwGxGetScreenWidth();
	gameModesLabel->m_H = 0;
	gameModesLabel->scale = fontScale;
	gameModesLabel->font = g_pResources->getLargeGameFont();
	gameModesLabel->SetText("Game Type");
	spriteManager->AddLabel(gameModesLabel);
}