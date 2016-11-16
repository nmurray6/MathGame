/*
 * (C) 2001-2012 Marmalade. All Rights Reserved.
 *
 * This document is protected by copyright, and contains information
 * proprietary to Marmalade.
 *
 * This file consists of source code released by Marmalade under
 * the terms of the accompanying End User License Agreement (EULA).
 * Please do not use this program/source code before you have read the
 * EULA and have agreed to be bound by its terms.
 */


#include "ProblemCreator.h"
#include "scene.h"
#include "input.h"
#include "Resources.h"
#include "MainMenu.h"
#include "AdditionGame.h"
#include "GameSelectionScreen.h"
#include "GlobalProperties.h"

#include "IwGx.h"
#include "s3e.h"
#include "IwDebug.h"
#include "Iw2DSceneGraph.h"
#include "IwGx.h"


using namespace Iw2DSceneGraphCore;
using namespace Iw2DSceneGraph;

// Scene root node
CNode* g_SceneRoot = NULL;


// Main entry point for the application
int main()
{
    //Initialise graphics system(s)
    Iw2DInit();
	
	g_pResources = new Resources();
	g_pInput = new Input();
	m_ProblemCreator = new ProblemCreator();
	g_pGlobalProperties = new GlobalProperties();
	g_pSceneManager = new SceneManager();

	g_pUIHelper = new UIHelper();
	g_pUIHelper->Init();

	Iw2DSetFont(g_pResources->getGameFont());

	MainMenu* mainMenu = new MainMenu();
	mainMenu->SetName("mainmenu");
	mainMenu->Init();
	g_pSceneManager->Add(mainMenu);

	AdditionGame* additionGame = new AdditionGame();
	additionGame->SetName("additionGame");
	additionGame->Init();
	g_pSceneManager->Add(additionGame);

	GameSelectionScreen* gameSelect = new GameSelectionScreen();
	gameSelect->SetName("gameSelectionScreen");
	gameSelect->Init();
	g_pSceneManager->Add(gameSelect);


	g_pSceneManager->SwitchTo(mainMenu);
    
	float deltaTime = 0.f;
	float timer = 0.f;

    // Loop forever, until the user or the OS performs some action to quit the app
	while (!s3eDeviceCheckQuitRequest())
    {
        //Update the input systems
        s3eKeyboardUpdate();
        s3ePointerUpdate();

		g_pInput->Update();

		deltaTime = s3eTimerGetMs() - timer;
		timer = s3eTimerGetMs();
		g_pSceneManager->Update(deltaTime);

        Iw2DSurfaceClear(0xff00ffff);

        //g_SceneRoot->Render();
		g_pSceneManager->Render();

        //Draws Surface to screen
        Iw2DSurfaceShow();
		
        // Sleep for 0ms to allow the OS to process events etc.
        s3eDeviceYield(0);
    }

    //Terminate modules being used
    delete g_pSceneManager;
	delete g_pResources;
	delete g_pInput;
	delete m_ProblemCreator;
	delete g_pUIHelper;
	delete g_pGlobalProperties;

    Iw2DTerminate();
    
    // Return
    return 0;
}
