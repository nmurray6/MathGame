#if !defined(_RESOURCES_H_)
#define _RESOURCES_H_

#include "Iw2D.h"
#include "Iw2DSceneGraph.h"
#include "IwGx.h"

using namespace Iw2DSceneGraph;

class Resources {
protected:
	CIw2DFont* futura24;
	CIw2DFont* futura36;
	CIw2DFont* futura48;
	CIw2DFont* gotham16;
	CIw2DImage* Background;
	CIw2DImage* playButton;
	CIw2DImage* practiceButton;
	CIw2DImage* answerButton;
	CIw2DImage* gameOverBackground;
	CIw2DImage* gameOverBackgroundBlank;
	CIw2DImage* mainMenuButton;
	CIw2DImage* restartButton;
	CIw2DImage* difficultyButton1;
	CIw2DImage* difficultyButton2;
	CIw2DImage* difficultyButton3;
	CIw2DImage* difficultyButton1Down;
	CIw2DImage* difficultyButton2Down;
	CIw2DImage* difficultyButton3Down;
	CIw2DImage* additionGameButton;
	CIw2DImage* subtractionGameButton;
	CIw2DImage* multiplicationGameButton;
	CIw2DImage* divisionGameButton;
	CIw2DImage* XButton;
	CIw2DImage* cancelButton;
	CIw2DImage* modesButton;
	CIw2DImage* timerBackground;
	CIw2DImage* answerButtonCorrect;
	CIw2DImage* answerButtonWrong;

public:
	CIw2DFont* getGameFont() { return futura24;	}//return (IwGxGetScreenHeight() >= 800) ? ((IwGxGetScreenHeight() >= 1400) ? futura48 : futura36) : futura24; }
	CIw2DFont* getTextFont() { return gotham16; }
	CIw2DFont* getLargeGameFont() { return futura36; }//(IwGxGetScreenHeight() >= 500) ? ((IwGxGetScreenHeight() >= 800) ? futura48 : futura36) : futura24; }
	CIw2DImage* getBackground() { return Background; }
	CIw2DImage* getPlayButton() { return playButton; }
	CIw2DImage* getPracticeButton() { return practiceButton; }
	CIw2DImage* getAnswerButton() { return answerButton; }
	CIw2DImage* getGameOverBackground() { return gameOverBackground; }
	CIw2DImage* getGameOverBackgroundBlank() { return gameOverBackgroundBlank; }
	CIw2DImage* getMainMenuButton() { return mainMenuButton; }
	CIw2DImage* getRestartButton() { return restartButton; }
	CIw2DImage* getDifficultyButton1() { return difficultyButton1; }
	CIw2DImage* getDifficultyButton2() { return difficultyButton2; }
	CIw2DImage* getDifficultyButton3() { return difficultyButton3; }
	CIw2DImage* getDifficultyButton1Down() { return difficultyButton1Down; }
	CIw2DImage* getDifficultyButton2Down() { return difficultyButton2Down; }
	CIw2DImage* getDifficultyButton3Down() { return difficultyButton3Down; }
	CIw2DImage* getAdditionGameButton() { return additionGameButton; }
	CIw2DImage* getSubtractionGameButton() { return subtractionGameButton; }
	CIw2DImage* getMultiplicationGameButton() { return multiplicationGameButton; }
	CIw2DImage* getDivisionGameButton() { return divisionGameButton; }
	CIw2DImage* getXButton() { return XButton; }
	CIw2DImage* getModesButton() { return modesButton; }
	CIw2DImage* getCancelButton() { return cancelButton; }
	CIw2DImage* getTimerBackground() { return timerBackground; }
	CIw2DImage* getAnswerButtonCorrect() { return answerButtonCorrect; }
	CIw2DImage* getAnswerButtonWrong() { return answerButtonWrong; }

public:
	Resources();
	~Resources();
};

extern Resources* g_pResources;

#endif