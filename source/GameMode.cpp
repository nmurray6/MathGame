#include "GameMode.h"

GameMode::GameMode() {
	spriteManager = new SpriteManager();
}

GameMode::~GameMode(){
	delete spriteManager;
}

void GameMode::addToRoundScore(int score) {

}

void GameMode::gameOver() {

}

void GameMode::Update(float deltaTime, float alphaMul) {
	if (!isActive)
		return;
}

void GameMode::Render() {
	if (!isActive)
		return;

	Scene::Render();
	spriteManager->Render();
}

void GameMode::initUI() {

}

void GameMode::Init() {
	Scene::Init();

	background = new Sprite();

	background->m_X = (float)IwGxGetScreenWidth() / 2;
	background->m_Y = (float)IwGxGetScreenHeight() / 2;
	background->SetImage(g_pResources->getBackground());
	background->m_W = background->GetImage()->GetWidth();
	background->m_H = background->GetImage()->GetHeight();
	background->m_AnchorX = 0.5f;
	background->m_AnchorY = 0.5f;

	spriteManager->AddSprite(background);
}