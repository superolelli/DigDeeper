#include "Options.hpp"




COptions::COptions()
{
	m_pBackground = NULL;
	m_pSettingsButton = NULL;
	m_pAchievementsButton = NULL;
	m_pUpgradesButton = NULL;
	m_pReturnButton = NULL;
}




//Load the button textures
void COptions::Init()
{
	is_running = true;

	m_pBackground = new CSprite;
	m_pBackground->Load(&g_pTextures->t_menuBackground);

	m_pSettingsButton = new CButton;
	m_pAchievementsButton = new CButton;
	m_pUpgradesButton = new CButton;

	m_pSettingsButton->Load(&g_pTextures->t_menuButtonSettings, g_pFramework->GetRenderWindow()->getSize().x / 2 - 100, g_pFramework->GetRenderWindow()->getSize().y / 6, CButton::BUTTONTYPE_MOTION_UP);
	m_pAchievementsButton->Load(&g_pTextures->t_menuButtonAchievements, g_pFramework->GetRenderWindow()->getSize().x / 2 - 100, 100 + 2 * (g_pFramework->GetRenderWindow()->getSize().y / 6), CButton::BUTTONTYPE_MOTION_UP);
	m_pUpgradesButton->Load(&g_pTextures->t_menuButtonUpgrades, g_pFramework->GetRenderWindow()->getSize().x / 2 - 100, 200 + 3 * (g_pFramework->GetRenderWindow()->getSize().y / 6), CButton::BUTTONTYPE_MOTION_UP);


    m_pReturnButton = new CButton;
	m_pReturnButton->Load(&g_pTextures->t_menuButtonReturn, g_pFramework->GetRenderWindow()->getSize().x/2 - 100, g_pFramework->GetRenderWindow()->getSize().y - 80, CButton::BUTTONTYPE_MOTION_UP); 
}





void COptions::Quit()
{
	SAFE_DELETE(m_pBackground);
	SAFE_DELETE(m_pSettingsButton);
	SAFE_DELETE(m_pAchievementsButton);
	SAFE_DELETE(m_pUpgradesButton);
	SAFE_DELETE(m_pReturnButton);	
}





void COptions::Run()
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
}





void COptions::RenderButtons()
{
	if (m_pReturnButton->Render(m_ButtonEventtype) == true)
		is_running = false;

	if (m_pSettingsButton->Render(m_ButtonEventtype))
	{
		CSettings Settings;
		Settings.Init();
		Settings.Run();
		Settings.Quit();
	}


	if (m_pAchievementsButton->Render(m_ButtonEventtype))
	{
		
	}


	if (m_pUpgradesButton->Render(m_ButtonEventtype))
	{
		
	}
}