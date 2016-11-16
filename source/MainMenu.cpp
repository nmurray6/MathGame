#include "MainMenu.h"

MainMenu::MainMenu() {
	spriteManager = new SpriteManager();
}

MainMenu::~MainMenu(){
	delete spriteManager;
}

void MainMenu::Update(float deltaTime, float alphaMul) {
	if (!m_IsActive)
		return;

	Scene::Update(deltaTime, alphaMul);

	if (m_IsInputActive && m_Manager->GetCurrent() == this && !g_pInput->touched && g_pInput->prevTouched) {
		g_pInput->Reset();
		if (playButton->HitTest(g_pInput->m_X, g_pInput->m_Y)) {
			//ADD IN BUTTON EFFECT
			g_pGlobalProperties->PracticeMode = 0;
			Scene* temp = g_pSceneManager->Find("additionGame");
			g_pSceneManager->SwitchTo(g_pSceneManager->Find("gameSelectionScreen"));
		}
		else if (practiceButton->HitTest(g_pInput->m_X, g_pInput->m_Y)) {
			g_pGlobalProperties->PracticeMode = 1;
			Scene* temp = g_pSceneManager->Find("additionGame");
			g_pSceneManager->SwitchTo(g_pSceneManager->Find("gameSelectionScreen"));
		}
	}
}

void MainMenu::Render() {
	if (!m_IsActive)
		return;

	Scene::Render();
	spriteManager->Render();
}

void MainMenu::Init() {
	Scene::Init();

	MainMenu* menu = (MainMenu*)g_pSceneManager->Find("mainMenu");

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

	playButton = new Sprite();

	playButton->m_X = (float)IwGxGetScreenWidth() / 2;
	playButton->m_Y = (float)IwGxGetScreenHeight() / 2;
	playButton->SetImage(g_pResources->getPlayButton());
	playButton->m_W = playButton->GetImage()->GetWidth() * scale;
	playButton->m_H = playButton->GetImage()->GetHeight() * scale;
	playButton->m_AnchorX = 0.5f;
	playButton->m_AnchorY = 0.5f;

	spriteManager->AddSprite(playButton);

	practiceButton = new Sprite();

	practiceButton->SetImage(g_pResources->getPracticeButton());
	practiceButton->m_X = playButton->m_X;
	practiceButton->m_Y = playButton->m_Y + playButton->GetImage()->GetHeight() * scale / 2 + practiceButton->GetImage()->GetHeight() * scale / 2 + 5 * scale;
	practiceButton->m_W = practiceButton->GetImage()->GetWidth() * scale;
	practiceButton->m_H = practiceButton->GetImage()->GetHeight() * scale;
	practiceButton->m_AnchorX = 0.5f;
	practiceButton->m_AnchorY = 0.5f;

	spriteManager->AddSprite(practiceButton);
}

