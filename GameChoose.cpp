#include "GameChoose.hpp"




CGameChoose::CGameChoose()
{
	m_pBackground = NULL;
	m_pNewGameButton = NULL;
	m_pLoadGameButton = NULL;
	m_pMultiplayerButton = NULL;
}





void CGameChoose::Init()
{
	m_returnNumber = 0;
	is_running = true;

	m_newWorldAttributes.GameName = ' ';
	m_newWorldAttributes.PlayerClass = MINER;
	m_newWorldAttributes.WorldSize = SMALL;

	m_pBackground = new CSprite;
	m_pBackground->Load(&g_pTextures->t_menuBackground);

    m_pNewGameButton = new CButton;
	m_pNewGameButton->Load(&g_pTextures->t_menuButtonNewGame, g_pFramework->GetRenderWindow()->getSize().x/2 - 100, g_pFramework->GetRenderWindow()->getSize().y/6, CButton::BUTTONTYPE_MOTION_UP); 

	m_pLoadGameButton = new CButton;
	m_pLoadGameButton->Load(&g_pTextures->t_menuButtonLoadGame, g_pFramework->GetRenderWindow()->getSize().x/2 - 100, 100 + 2*(g_pFramework->GetRenderWindow()->getSize().y/6), CButton::BUTTONTYPE_MOTION_UP); 

	m_pMultiplayerButton = new CButton;
	m_pMultiplayerButton->Load(&g_pTextures->t_menuButtonMultiplayer, g_pFramework->GetRenderWindow()->getSize().x/2 - 100, 200 + 3*(g_pFramework->GetRenderWindow()->getSize().y/6), CButton::BUTTONTYPE_MOTION_UP); 
}





SNewWorldAttributes CGameChoose::Quit()
{
	SAFE_DELETE(m_pBackground);
	SAFE_DELETE(m_pNewGameButton);
	SAFE_DELETE(m_pLoadGameButton);
	SAFE_DELETE(m_pMultiplayerButton);

	return m_newWorldAttributes;
}





int CGameChoose::Run()
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





void CGameChoose::RenderButtons()
{
	if(m_pNewGameButton->Render(m_ButtonEventtype) == true)
	{
		CNewGame newGame;
		newGame.Init();
		m_returnNumber = newGame.Run();
		m_newWorldAttributes = newGame.Quit();

		if(m_returnNumber == 2)
		{
			is_running = false;
			return;
		}
		else
			m_returnNumber = 0;
	}

	if(m_pLoadGameButton->Render(m_ButtonEventtype) == true)
	{
		CLoadGame loadGame;
		loadGame.Init();
		m_returnNumber = loadGame.Run();
		m_newWorldAttributes.GameName = loadGame.Quit();

		if(m_returnNumber == 10)
			is_running = false;
		else
			m_returnNumber = 0;
	}

	if(m_pMultiplayerButton->Render(m_ButtonEventtype) == true)
	{
		m_returnNumber = 4;
		is_running = false;
	}
}