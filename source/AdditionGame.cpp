#include "AdditionGame.h"
#include "Iw2D.h"

AdditionGame::AdditionGame() {
	spriteManager = new SpriteManager();
}

AdditionGame::~AdditionGame() {
	delete spriteManager;
}

/*
Modes:
1 = addition
2 = subtraction
3 = multiplication
4 = division
*/

void AdditionGame::Update(float deltaTime, float alphaMul) {
	if (!m_IsActive)
		return;

	Scene::Update(deltaTime, alphaMul);

	//Check to see if the game mode or difficulty has changed and reset if it has
	if (prevDiff != g_pSceneManager->GetCurrent()->GetSceneDifficulty()
		|| prevMode != g_pSceneManager->GetCurrent()->GetSceneMode()) {
		prevDiff = g_pSceneManager->GetCurrent()->GetSceneDifficulty();
		prevMode = g_pSceneManager->GetCurrent()->GetSceneMode();
		reset = true;
	}
	else if (answerDisplayTimer > 0.f) {
		answerDisplayTimer -= deltaTime;
		displayWrongAndCorrect();
	}
	//Game over functions
	else if (gameOver && !g_pGlobalProperties->PracticeMode) {
		g_pUIHelper->gameOverInit();
		gameOver = g_pUIHelper->GameOverMenuUpdate(score, reset);
		return;
	}
	//Reset the game screen
	else if (reset) {
		Reset();
	}
	//Escape menu functions
	else if (escapeMenu) {
		g_pUIHelper->EscapeMenuUpdate(escapeMenu, reset);
	}
	//Input functions
	else if (m_IsInputActive && m_Manager->GetCurrent() == this && !g_pInput->touched && g_pInput->prevTouched) {

		g_pInput->Reset();

		if (answerButton1->HitTest(g_pInput->m_X, g_pInput->m_Y)) {
			handleAnswerInput(0);
		}
		else if (answerButton2->HitTest(g_pInput->m_X, g_pInput->m_Y)) {
			handleAnswerInput(1);
		}
		else if (answerButton3->HitTest(g_pInput->m_X, g_pInput->m_Y)) {
			handleAnswerInput(2);
		}
		else if (answerButton4->HitTest(g_pInput->m_X, g_pInput->m_Y)) {
			handleAnswerInput(3);
		}
		else if (XButton->HitTest(g_pInput->m_X, g_pInput->m_Y)) {
			escapeMenu = true;
			g_pUIHelper->EscapeMenuInit();
		}
	}
	else if(!g_pGlobalProperties->PracticeMode){
		if (timeKnockback && timeKnockback < 1) {
			timer += timeKnockback;
			timeKnockback = 0;
		}
		else {
			timer += timeKnockback / 20;
			timeKnockback *= .95f;
		}
		if (timer > maxTimer) {
			timer = maxTimer;
			timeKnockback = 0;
		}
		timer -= deltaTime;
		timerBackground->scale = (maxTimer - timer) / maxTimer;
		if (timer <= 0) {
			timer = maxTimer;
			handleTimeout();
		}
	}
}

void AdditionGame::Render() {
	if (!m_IsActive)
		return;

	if (!g_pGlobalProperties->PracticeMode)
		timerBackground->isVisible = true;
	else
		timerBackground->isVisible = false;
	
	Scene::Render();

	char string[128];
	sprintf(string, "Score: %d", score);
	scoreText->SetText(string);
	
	if (!g_pGlobalProperties->PracticeMode)
		scoreText->isVisible = true;
	else 
		scoreText->isVisible = false;

	if (g_pSceneManager->GetCurrent()->GetSceneMode() == 1) {
		sprintf(string, "%d + %d", (int)prob[0], (int)prob[1]);
		problemText->SetText(string);
	}
	else if (g_pSceneManager->GetCurrent()->GetSceneMode() == 2) {
		sprintf(string, "%d - %d", (int)prob[0], (int)prob[1]);
		problemText->SetText(string);
	}
	else if (g_pSceneManager->GetCurrent()->GetSceneMode() == 3) {
		sprintf(string, "%d x %d", (int)prob[0], (int)prob[1]);
		problemText->SetText(string);
	}
	else if (g_pSceneManager->GetCurrent()->GetSceneMode() == 4) {
		Iw2DSetFont(g_pResources->getLargeGameFont());
		sprintf(string, "%d\n%d", (int)prob[0], (int)prob[1]);
		problemText->SetText(string);
	}

	sprintf(string, "%d", (int)ans[0]);
	ab1Text->SetText(string);

	sprintf(string, "%d", (int)ans[1]);
	ab2Text->SetText(string);

	sprintf(string, "%d", (int)ans[2]);
	ab3Text->SetText(string);

	sprintf(string, "%d", (int)ans[3]);
	ab4Text->SetText(string);

	spriteManager->Render();

	if (g_pSceneManager->GetCurrent()->GetSceneMode() == 4) {
		float i = 0;
		float x = prob[0];
		while (x > 1.f) {
			i++;
			x /= 10.f;
		}
		Iw2DFillRect(CIwFVec2(IwGxGetScreenWidth() / 2 - 30.f * i * scale , problemText->m_Y - 5.f * scale), 
			CIwFVec2(60.f * i * scale, 10.f * scale));
	}

	if (gameOver)
		g_pUIHelper->GameOverDisplay();
	else if (escapeMenu)
		g_pUIHelper->EscapeMenuDisplay();

	

}

void AdditionGame::Init() {
	Scene::Init();

	AdditionGame* menu = (AdditionGame*)g_pSceneManager->Find("additionGame");

	m_ProblemCreator->createMathProblem(prob, 1, 1);
	m_ProblemCreator->CreateAnswers(prob, ans, 1, 1);

	background = new Sprite();

	background->m_X = (float)IwGxGetScreenWidth() / 2;
	background->m_Y = (float)IwGxGetScreenHeight() / 2;
	background->SetImage(g_pResources->getBackground());
	scale = MAX((float)IwGxGetScreenHeight() / (float)background->GetImage()->GetHeight(), (float)IwGxGetScreenWidth() / (float)background->GetImage()->GetWidth());
	background->m_W = background->GetImage()->GetWidth() * scale;
	background->m_H = background->GetImage()->GetHeight() * scale;
	background->m_AnchorX = 0.5f;
	background->m_AnchorY = 0.5f;

	spriteManager->AddSprite(background);

	timerBackground = new Sprite();

	timerBackground->m_X = (float)IwGxGetScreenWidth() / 2;
	timerBackground->m_Y = (float)IwGxGetScreenHeight() / 2;
	timerBackground->SetImage(g_pResources->getTimerBackground());
	timerBackground->m_W = timerBackground->GetImage()->GetWidth() * scale;
	timerBackground->m_H = timerBackground->GetImage()->GetHeight() * scale;
	timerBackground->m_AnchorX = 0.5f;
	timerBackground->m_AnchorY = 0.5f;
	timerBackground->timer = true;
	timerBackground->scale = 0.f;

	spriteManager->AddSprite(timerBackground);
	

	shift = shift * scale;
	answerButton1 = new Sprite();

	answerButton1->SetImage(g_pResources->getAnswerButton());
	answerButton1->m_W = answerButton1->GetImage()->GetWidth() * scale;
	answerButton1->m_H = answerButton1->GetImage()->GetHeight() * scale;
	answerButton1->m_X = (float)IwGxGetScreenWidth() / 2 - (answerButton1->m_W / 2 + 5);
	answerButton1->m_Y = (float)IwGxGetScreenHeight() / 2 - (answerButton1->m_H / 2 + 5) + shift;
	answerButton1->m_AnchorX = 0.5f;
	answerButton1->m_AnchorY = 0.5f;

	spriteManager->AddSprite(answerButton1);

	answerButton2 = new Sprite();

	answerButton2->SetImage(g_pResources->getAnswerButton());
	answerButton2->m_W = answerButton2->GetImage()->GetWidth() * scale;
	answerButton2->m_H = answerButton2->GetImage()->GetHeight() * scale;
	answerButton2->m_X = (float)IwGxGetScreenWidth() / 2 + (answerButton2->m_W / 2 + 5);
	answerButton2->m_Y = (float)IwGxGetScreenHeight() / 2 - (answerButton2->m_H / 2 + 5) + shift;
	answerButton2->m_AnchorX = 0.5f;
	answerButton2->m_AnchorY = 0.5f;

	spriteManager->AddSprite(answerButton2);

	answerButton3 = new Sprite();

	answerButton3->SetImage(g_pResources->getAnswerButton());
	answerButton3->m_W = answerButton3->GetImage()->GetWidth() * scale;
	answerButton3->m_H = answerButton3->GetImage()->GetHeight() * scale;
	answerButton3->m_X = (float)IwGxGetScreenWidth() / 2 - (answerButton3->m_W / 2 + 5);
	answerButton3->m_Y = (float)IwGxGetScreenHeight() / 2 + (answerButton3->m_H / 2 + 5) + shift;
	answerButton3->m_AnchorX = 0.5f;
	answerButton3->m_AnchorY = 0.5f;

	spriteManager->AddSprite(answerButton3);

	answerButton4 = new Sprite();

	answerButton4->SetImage(g_pResources->getAnswerButton());
	answerButton4->m_W = answerButton4->GetImage()->GetWidth() * scale;
	answerButton4->m_H = answerButton4->GetImage()->GetHeight() * scale;
	answerButton4->m_X = (float)IwGxGetScreenWidth() / 2 + (answerButton4->m_W / 2 + 5);
	answerButton4->m_Y = (float)IwGxGetScreenHeight() / 2 + (answerButton4->m_H / 2 + 5) + shift;
	answerButton4->m_AnchorX = 0.5f;
	answerButton4->m_AnchorY = 0.5f;

	spriteManager->AddSprite(answerButton4);

	answerButtonCorrect = new Sprite();
	answerButtonCorrect->SetImage(g_pResources->getAnswerButtonCorrect());
	answerButtonCorrect->m_W = answerButtonCorrect->GetImage()->GetWidth() * scale;
	answerButtonCorrect->m_H = answerButtonCorrect->GetImage()->GetHeight() * scale;
	answerButtonCorrect->m_AnchorX = 0.5f;
	answerButtonCorrect->m_AnchorY = 0.5f;
	answerButtonCorrect->isVisible = false;

	spriteManager->AddSprite(answerButtonCorrect);

	answerButtonWrong = new Sprite();
	answerButtonWrong->SetImage(g_pResources->getAnswerButtonWrong());
	answerButtonWrong->m_W = answerButtonWrong->GetImage()->GetWidth() * scale;
	answerButtonWrong->m_H = answerButtonWrong->GetImage()->GetHeight() * scale;
	answerButtonWrong->m_AnchorX = 0.5f;
	answerButtonWrong->m_AnchorY = 0.5f;
	answerButtonWrong->isVisible = false;

	spriteManager->AddSprite(answerButtonWrong);

	XButton = new Sprite();
	XButton->SetImage(g_pResources->getXButton());
	XButton->m_W = XButton->GetImage()->GetWidth() * scale;
	XButton->m_H = XButton->GetImage()->GetHeight() * scale;
	XButton->m_X = (float)IwGxGetScreenWidth() - XButton->m_W / 2 - 5;
	XButton->m_Y = XButton->m_H / 2 + 5;
	XButton->m_AnchorX = 0.5f;
	XButton->m_AnchorY = 0.5f;
	spriteManager->AddSprite(XButton);
	

	CIwFVec2 center(IwGxGetScreenWidth() / 2, IwGxGetScreenHeight() / 4);
	CIwFVec2 region(570, 600);
	float fontScale = IwGxGetScreenHeight() / (float)region.y;
	CIwFVec2 size(IwGxGetScreenWidth(), 0);
	CIwFVec2 topLeft(center.x - size.x / 2,
		center.y - size.y / 2);

	scoreText = new Label();
	scoreText->m_X = 5;
	scoreText->m_Y = 5;
	scoreText->m_W = IwGxGetScreenWidth() / 2;
	scoreText->m_H = 100.f * scale;
	scoreText->scale = fontScale;
	scoreText->horizontalAlignment = IW_2D_FONT_ALIGN_LEFT;
	scoreText->verticalAlignment = IW_2D_FONT_ALIGN_TOP;
	scoreText->font = g_pResources->getTextFont();
	spriteManager->AddLabel(scoreText);

	problemText = new Label();
	problemText->m_X = topLeft.x;
	problemText->m_Y = topLeft.y;
	problemText->m_W = size.x;
	problemText->m_H = size.y;
	problemText->scale = fontScale;
	problemText->font = g_pResources->getLargeGameFont();
	spriteManager->AddLabel(problemText);

	ab1Text = new Label();
	ab1Text->m_X = answerButton1->m_X - answerButton1->m_W / 2;
	ab1Text->m_Y = answerButton1->m_Y - answerButton1->m_H / 2;
	ab1Text->m_W = answerButton1->m_W;
	ab1Text->m_H = answerButton1->m_H;
	ab1Text->scale = fontScale;
	ab1Text->font = g_pResources->getGameFont();
	spriteManager->AddLabel(ab1Text);

	ab2Text = new Label();
	ab2Text->m_X = answerButton2->m_X - answerButton2->m_W / 2;
	ab2Text->m_Y = answerButton2->m_Y - answerButton2->m_H / 2;
	ab2Text->m_W = answerButton2->m_W;
	ab2Text->m_H = answerButton2->m_H;
	ab2Text->scale = fontScale;
	ab2Text->font = g_pResources->getGameFont();
	spriteManager->AddLabel(ab2Text);

	ab3Text = new Label();
	ab3Text->m_X = answerButton3->m_X - answerButton3->m_W / 2;
	ab3Text->m_Y = answerButton3->m_Y - answerButton3->m_H / 2;
	ab3Text->m_W = answerButton3->m_W;
	ab3Text->m_H = answerButton3->m_H;
	ab3Text->scale = fontScale;
	ab3Text->font = g_pResources->getGameFont();
	spriteManager->AddLabel(ab3Text);

	ab4Text = new Label();
	ab4Text->m_X = answerButton4->m_X - answerButton4->m_W / 2;
	ab4Text->m_Y = answerButton4->m_Y - answerButton4->m_H / 2;
	ab4Text->m_W = answerButton4->m_W;
	ab4Text->m_H = answerButton4->m_H;
	ab4Text->scale = fontScale;
	ab4Text->font = g_pResources->getGameFont();
	spriteManager->AddLabel(ab4Text);
}

void AdditionGame::handleAnswerInput(int buttonNum) {
	if (ans[buttonNum] == prob[2]) {
		handleCorrect();
	}
	else {
		handleIncorrect();
		initButtonWrong(buttonNum);
		
		int i = 0;
		while (i < 4) {
			if (ans[i] == prob[2]) {
				initButtonCorrect(i);
				break;
			}
			i++;
		}
		
	}
	if (!g_pGlobalProperties->PracticeMode)
		updateHighScore();

	
}

void AdditionGame::handleCorrect() {
	timer += timeKnockback;
	timeKnockback = maxTimeKnockback / MAX(1, log(problemNumber));
	problemNumber++;
	score++;
	m_ProblemCreator->createMathProblem(prob, g_pSceneManager->GetCurrent()->GetSceneDifficulty(), g_pSceneManager->GetCurrent()->GetSceneMode());
	m_ProblemCreator->CreateAnswers(prob, ans, g_pSceneManager->GetCurrent()->GetSceneDifficulty(), g_pSceneManager->GetCurrent()->GetSceneMode());
}

void AdditionGame::handleIncorrect() {
	answerDisplayTimer = answerDisplay;
	if (!g_pGlobalProperties->PracticeMode)
		gameOver = 1;
	reset = true;
	s3eVibraVibrate(150, 200);
}

void AdditionGame::handleTimeout() {
	handleIncorrect();
	initButtonWrong(-1);

	int i = 0;
	while (i < 4) {
		if (ans[i] == prob[2]) {
			initButtonCorrect(i);
			break;
		}
		i++;
	}
	
}

void AdditionGame::Reset() {
	reset = false;
	score = 0;
	timer = maxTimer;
	problemNumber = 1;
	timeKnockback = maxTimeKnockback;
	m_ProblemCreator->createMathProblem(prob, g_pSceneManager->GetCurrent()->GetSceneDifficulty(), g_pSceneManager->GetCurrent()->GetSceneMode());
	m_ProblemCreator->CreateAnswers(prob, ans, g_pSceneManager->GetCurrent()->GetSceneDifficulty(), g_pSceneManager->GetCurrent()->GetSceneMode());
}

void AdditionGame::updateHighScore() {
	switch (g_pSceneManager->GetCurrent()->GetSceneMode()) {
	case 1: //addition
		switch (g_pSceneManager->GetCurrent()->GetSceneDifficulty()) {
		case 1:
			if(g_pGlobalProperties->AdditionEasyHighScore < score)
				g_pGlobalProperties->AdditionEasyHighScore = score;
			break;

		case 2:
			if(g_pGlobalProperties->AdditionMediumHighScore < score)
				g_pGlobalProperties->AdditionMediumHighScore = score;
			break;

		case 3:
			if(g_pGlobalProperties->AdditionHardHighScore < score)
				g_pGlobalProperties->AdditionHardHighScore = score;
			break;
		}
		break;

	case 2://subtraction
		switch (g_pSceneManager->GetCurrent()->GetSceneDifficulty()) {
		case 1:
			if(g_pGlobalProperties->SubtractionEasyHighScore < score)
				g_pGlobalProperties->SubtractionEasyHighScore = score;
			break;

		case 2:
			if(g_pGlobalProperties->SubtractionMediumHighScore < score)
				g_pGlobalProperties->SubtractionMediumHighScore = score;
			break;

		case 3:
			if(g_pGlobalProperties->SubtractionHardHighScore < score)
				g_pGlobalProperties->SubtractionHardHighScore = score;
			break;
		}
		break;

	case 3://multiplication
		switch (g_pSceneManager->GetCurrent()->GetSceneDifficulty()) {
		case 1:
			if(g_pGlobalProperties->MultiplicationEasyHighScore < score)
				g_pGlobalProperties->MultiplicationEasyHighScore = score;
			break;

		case 2:
			if(g_pGlobalProperties->MultiplicationMediumHighScore < score)
				g_pGlobalProperties->MultiplicationMediumHighScore = score;
			break;

		case 3:
			if(g_pGlobalProperties->MultiplicationHardHighScore < score)
				g_pGlobalProperties->MultiplicationHardHighScore = score;
			break;
		}
		break;

	case 4://division
		switch (g_pSceneManager->GetCurrent()->GetSceneDifficulty()) {
		case 1:
			if(g_pGlobalProperties->DivisionEasyHighScore < score)
				g_pGlobalProperties->DivisionEasyHighScore = score;
			break;

		case 2:
			if(g_pGlobalProperties->DivisionMediumHighScore < score)
				g_pGlobalProperties->DivisionMediumHighScore = score;
			break;

		case 3:
			if(g_pGlobalProperties->DivisionHardHighScore < score)
				g_pGlobalProperties->DivisionHardHighScore = score;
			break;
		}
		break;
	}
}

void AdditionGame::displayWrongAndCorrect() {
	if (answerDisplayTimer <= 0.f) {
		answerDisplayTimer = 0.f;
		answerButtonCorrect->isVisible = false;
		answerButtonWrong->isVisible = false;
		if (!g_pGlobalProperties->PracticeMode)
			g_pUIHelper->gameOverInit();
	}
	else {
		answerButtonCorrect->isVisible = true;
		answerButtonWrong->isVisible = true;
	}
}

void AdditionGame::initButtonCorrect(int num) {
	switch (num) {
	case 0:
		answerButtonCorrect->m_X = answerButton1->m_X;
		answerButtonCorrect->m_Y = answerButton1->m_Y;
		break;
	case 1:
		answerButtonCorrect->m_X = answerButton2->m_X;
		answerButtonCorrect->m_Y = answerButton2->m_Y;
		break;
	case 2:
		answerButtonCorrect->m_X = answerButton3->m_X;
		answerButtonCorrect->m_Y = answerButton3->m_Y;
		break;
	case 3:
		answerButtonCorrect->m_X = answerButton4->m_X;
		answerButtonCorrect->m_Y = answerButton4->m_Y;
		break;
	}
	
	
	answerButtonCorrect->isVisible = true;
}

void AdditionGame::initButtonWrong(int num) {
	switch (num) {
	case 0:
		answerButtonWrong->m_X = answerButton1->m_X;
		answerButtonWrong->m_Y = answerButton1->m_Y;
		break;
	case 1:
		answerButtonWrong->m_X = answerButton2->m_X;
		answerButtonWrong->m_Y = answerButton2->m_Y;
		break;
	case 2:
		answerButtonWrong->m_X = answerButton3->m_X;
		answerButtonWrong->m_Y = answerButton3->m_Y;
		break;
	case 3:
		answerButtonWrong->m_X = answerButton4->m_X;
		answerButtonWrong->m_Y = answerButton4->m_Y;
		break;
	case -1:
		answerButtonWrong->m_X = -10000;
		answerButtonWrong->m_Y = -10000;
	}

	answerButtonWrong->isVisible = true;
}