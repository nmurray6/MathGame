#include "Resources.h"
#include "Iw2D.h"

Resources::Resources() {
	futura24 = Iw2DCreateFont("fonts/futura24.gxfont");
	futura36 = Iw2DCreateFont("fonts/futura36.gxfont");
	futura48 = Iw2DCreateFont("fonts/futura48.gxfont");
	gotham16 = Iw2DCreateFont("fonts/gotham16.gxfont");

	Background = Iw2DCreateImage("textures/background.png");
	playButton = Iw2DCreateImage("textures/PlayButton.png");
	practiceButton = Iw2DCreateImage("textures/PracticeButton.png");
	answerButton = Iw2DCreateImage("textures/AnswerButton.png");
	gameOverBackground = Iw2DCreateImage("textures/GameOverBackground.png");
	gameOverBackgroundBlank = Iw2DCreateImage("textures/GameOverBackgroundBlank.png");
	mainMenuButton = Iw2DCreateImage("textures/MainMenuButton.png");
	restartButton = Iw2DCreateImage("textures/RestartButton.png");
	difficultyButton1 = Iw2DCreateImage("textures/basic.png");
	difficultyButton2 = Iw2DCreateImage("textures/advanced.png");
	difficultyButton3 = Iw2DCreateImage("textures/master.png");
	difficultyButton1Down = Iw2DCreateImage("textures/basic_down.png");
	difficultyButton2Down = Iw2DCreateImage("textures/advanced_down.png");
	difficultyButton3Down = Iw2DCreateImage("textures/master_down.png");
	additionGameButton = Iw2DCreateImage("textures/AdditionGameButton.png");
	subtractionGameButton = Iw2DCreateImage("textures/SubtractiongameButton.png");
	multiplicationGameButton = Iw2DCreateImage("textures/MultiplicationGameButton.png");
	divisionGameButton = Iw2DCreateImage("textures/DivisionGameButton.png");
	XButton = Iw2DCreateImage("textures/XButton.png");
	cancelButton = Iw2DCreateImage("textures/CancelButton.png");
	modesButton = Iw2DCreateImage("textures/ModesButton.png");
	timerBackground = Iw2DCreateImage("textures/TimerBackground.png");
	answerButtonCorrect = Iw2DCreateImage("textures/AnswerButtonCorrect.png");
	answerButtonWrong = Iw2DCreateImage("textures/AnswerButtonWrong.png");
}

Resources::~Resources() {
	delete futura24;
	delete futura36;
	delete futura48;
	delete gotham16;
	delete Background;
	delete playButton;
	delete practiceButton;
	delete answerButton;
	delete gameOverBackground;
	delete gameOverBackgroundBlank;
	delete mainMenuButton;
	delete restartButton;
	delete difficultyButton1;
	delete difficultyButton2;
	delete difficultyButton3;
	delete difficultyButton1Down;
	delete difficultyButton2Down;
	delete difficultyButton3Down;
	delete additionGameButton;
	delete subtractionGameButton;
	delete multiplicationGameButton;
	delete divisionGameButton;
	delete XButton;
	delete cancelButton;
	delete modesButton;
	delete timerBackground;
	delete answerButtonCorrect;
	delete answerButtonWrong;
}

Resources* g_pResources = 0;