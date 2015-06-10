#include "Menu.hpp"





CMenu::CMenu()
{
	m_pBackground = NULL;
	m_pPlay = NULL;
	m_pOptions = NULL;
	m_pQuit = NULL;
	m_pHighscore = NULL;
}




void CMenu::Init()
{
	is_running = true;

	m_newWorldAttributes.GameName = ' ';
	m_newWorldAttributes.PlayerClass = MINER;
	m_newWorldAttributes.WorldSize = SMALL;

	//Load the background
	m_pBackground = new CSprite;
	m_pBackground->Load(&g_pTextures->t_menuBackground);

	//Load the three buttons
	m_pPlay = new CButton;
	m_pPlay->Load(&g_pTextures->t_menuButtonPlay, g_pFramework->GetRenderWindow()->getSize().x/2 - 100, g_pFramework->GetRenderWindow()->getSize().y/10, CButton::BUTTONTYPE_MOTION_UP); 

	m_pOptions = new CButton;
	m_pOptions->Load(&g_pTextures->t_menuButtonOptions, g_pFramework->GetRenderWindow()->getSize().x/2 - 100, 3*(g_pFramework->GetRenderWindow()->getSize().y/10), CButton::BUTTONTYPE_MOTION_UP); 

	m_pHighscore = new CButton;
	m_pHighscore->Load(&g_pTextures->t_menuButtonHighscore, g_pFramework->GetRenderWindow()->getSize().x/2 - 100, 5*(g_pFramework->GetRenderWindow()->getSize().y/10), CButton::BUTTONTYPE_MOTION_UP); 

	m_pQuit = new CButton;
	m_pQuit->Load(&g_pTextures->t_menuButtonQuit, g_pFramework->GetRenderWindow()->getSize().x / 2 - 100, 7 * (g_pFramework->GetRenderWindow()->getSize().y / 10), CButton::BUTTONTYPE_MOTION_UP);
}



SNewWorldAttributes CMenu::Quit()
{
	SAFE_DELETE(m_pBackground);
	SAFE_DELETE(m_pPlay);
	SAFE_DELETE(m_pOptions);
	SAFE_DELETE(m_pHighscore);
	SAFE_DELETE(m_pQuit);

	return m_newWorldAttributes;
}




int CMenu::Run()
{
	//the loop
	while(is_running == true)
	{
		//Update and clear the Window
		g_pFramework->Update();
		g_pFramework->Clear();

		//get the events
		g_pFramework->ProcessEvents();
		m_ButtonEventtype = 0;

		//If an event happened, important for the buttons, save it (Left mouse up)	
		if(g_pFramework->keyStates.leftMouseUp)
				m_ButtonEventtype = MOUSE_LEFT_UP;

		//Render the background
		m_pBackground->Render(g_pFramework->GetRenderWindow());

		//Render the buttons
		RenderButtons();
       

		g_pFramework->Flip();
	}

	return m_returnNumber;
}





void CMenu::RenderButtons()
{
	if(m_pQuit->Render(m_ButtonEventtype) == true)
	{
		m_returnNumber = 1;
		is_running = false;
	}

	if(m_pOptions->Render(m_ButtonEventtype) == true)
	{
		COptions Options;

		Options.Init();
		Options.Run();
		Options.Quit();
	}

	if (m_pHighscore->Render(m_ButtonEventtype) == true)
	{
		CHighscore Highscore;

		Highscore.Init();
		Highscore.Run();
		Highscore.Quit();
	}

	if(m_pPlay->Render(m_ButtonEventtype) == true)
	{
		CGameChoose GameChoose;

		GameChoose.Init();
		m_returnNumber = GameChoose.Run();
		m_newWorldAttributes = GameChoose.Quit();

		is_running = false;
	}
}