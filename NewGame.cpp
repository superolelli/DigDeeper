#include "NewGame.hpp"




CNewGame::CNewGame()
{
	m_pBackground = NULL;
	m_pClassLeft = NULL;
	m_pClassRight = NULL;
	m_pWorldLeft = NULL;
	m_pWorldRight = NULL;
	m_pStartGameButton = NULL;
	m_pReturnButton = NULL;

	BOOST_FOREACH(CSprite* c, m_pClass)
	{
		c = NULL;
	}

	BOOST_FOREACH(CSprite* c, m_pWorldSize)
	{
		c = NULL;
	}
}



void CNewGame::Init()
{
	m_pBackground = new CSprite;
	m_pBackground->Load(&g_pTextures->t_newGameBackground);

	m_pStartGameButton = new CButton;
	m_pStartGameButton->Load(&g_pTextures->t_menuButtonNewGame, g_pFramework->GetWindow()->getSize().x/2 +200, g_pFramework->GetWindow()->getSize().y - 200, 3);

	m_pReturnButton = new CButton;
	m_pReturnButton->Load(&g_pTextures->t_menuButtonReturn, g_pFramework->GetWindow()->getSize().x/2 - 350, g_pFramework->GetWindow()->getSize().y - 200, 3);

	m_pClass[0] = new CSprite;
	m_pClass[0]->Load(&g_pTextures->t_newGameMiner);
	
	m_pClass[1] = new CSprite;
	m_pClass[1]->Load(&g_pTextures->t_newGameBuilder);

	m_pClass[2] = new CSprite;
	m_pClass[2]->Load(&g_pTextures->t_newGameWarrior);
	
	m_pClass[3] = new CSprite;
	m_pClass[3]->Load(&g_pTextures->t_newGameMage);

	BOOST_FOREACH(CSprite* c, m_pClass)
		c->SetPos((float)g_pFramework->GetWindow()->getSize().x/5, (float)g_pFramework->GetWindow()->getSize().y/4);

	m_pWorldSize[0] = new CSprite;
	m_pWorldSize[0]->Load(&g_pTextures->t_newGameSmallWorld);

	m_pWorldSize[1] = new CSprite;
	m_pWorldSize[1]->Load(&g_pTextures->t_newGameMediumWorld);

	m_pWorldSize[2] = new CSprite;
	m_pWorldSize[2]->Load(&g_pTextures->t_newGameBigWorld);

	BOOST_FOREACH(CSprite* c, m_pWorldSize)
		c->SetPos((float)g_pFramework->GetWindow()->getSize().x/1.5, (float)g_pFramework->GetWindow()->getSize().y/2);

	m_pClassLeft = new CButton;
	m_pClassLeft->Load(&g_pTextures->t_newGameButtonLeft, m_pClass[0]->GetRect().left - 120, m_pClass[0]->GetRect().top + m_pClass[0]->GetRect().height/2 - 37, 1);

	m_pClassRight = new CButton;
	m_pClassRight->Load(&g_pTextures->t_newGameButtonRight, m_pClass[0]->GetRect().left + m_pClass[0]->GetRect().width + 10, m_pClass[0]->GetRect().top + m_pClass[0]->GetRect().height/2 - 37, 1);

	m_pWorldLeft = new CButton;
	m_pWorldLeft->Load(&g_pTextures->t_newGameButtonLeft, m_pWorldSize[0]->GetRect().left - 120, m_pWorldSize[0]->GetRect().top + m_pWorldSize[0]->GetRect().height/2 - 37, 1);

	m_pWorldRight = new CButton;
	m_pWorldRight->Load(&g_pTextures->t_newGameButtonRight, m_pWorldSize[0]->GetRect().left + m_pWorldSize[0]->GetRect().width + 10, m_pWorldSize[0]->GetRect().top + m_pWorldSize[0]->GetRect().height/2 - 37, 1);

	m_font.loadFromFile("Data/Fonts/ltromatic.ttf");
	m_GameName.Init(m_font, 30, g_pFramework->GetWindow()->getSize().x/2, g_pFramework->GetWindow()->getSize().y/8, Color(230, 220, 0));
	m_GameName.SetString("Neue Welt");

	m_class = 0;
	m_worldSize = 0;

	is_running = true;
	m_returnNumber = 0;
}




SNewWorldAttributes CNewGame::Quit()
{
	SNewWorldAttributes attributes;
	attributes.GameName = m_GameName.GetString();
	attributes.PlayerClass = m_class +1;
	attributes.WorldSize = m_worldSize +1;


	SAFE_DELETE(m_pBackground);
	SAFE_DELETE(m_pClassLeft);
	SAFE_DELETE(m_pClassRight);
	SAFE_DELETE(m_pWorldLeft);
	SAFE_DELETE(m_pWorldRight);
	SAFE_DELETE(m_pStartGameButton);
	SAFE_DELETE(m_pReturnButton);

	
	BOOST_FOREACH(CSprite* c, m_pClass)
	{
		SAFE_DELETE(c);
	}

	BOOST_FOREACH(CSprite* c, m_pWorldSize)
	{
		SAFE_DELETE(c);
	}

	return attributes;
}




int CNewGame::Run()
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
		else if (g_pFramework->keyStates.f3)
		{
			m_class = TEST - 1;

			is_running = false;
			return 2;
		}

		
		m_GameName.HandleInput();

		//Render the background
		m_pBackground->Render(g_pFramework->GetWindow());

		m_GameName.Show(g_pFramework->GetWindow());

		m_pClass[m_class]->Render(g_pFramework->GetWindow());
		m_pWorldSize[m_worldSize]->Render(g_pFramework->GetWindow());

		//Render the buttons
		RenderButtons();
       

		g_pFramework->Flip();
	}

	return m_returnNumber;
}




void CNewGame::RenderButtons()
{
	if(m_pClassLeft->Render(m_ButtonEventtype) == true)
	{
		m_class --;
		if(m_class < 0)
			m_class = 3;
	}

	if(m_pClassRight->Render(m_ButtonEventtype) == true)
	{
		m_class++;
		if(m_class > 3)
			m_class = 0;
	}

	if(m_pWorldLeft->Render(m_ButtonEventtype) == true)
	{
		m_worldSize--;
		if(m_worldSize < 0)
			m_worldSize = 2;
	}

	if(m_pWorldRight->Render(m_ButtonEventtype) == true)
	{
		m_worldSize++;
		if(m_worldSize > 2)
			m_worldSize = 0;
	}

	if(m_pStartGameButton->Render(m_ButtonEventtype) == true)
	{
		m_returnNumber = 2;
		is_running = false;
	}

	if(m_pReturnButton->Render(m_ButtonEventtype) == true)
	{
		m_returnNumber = 4;
		is_running = false;
	}
}