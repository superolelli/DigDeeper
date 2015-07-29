#include "LoadGame.hpp"



CLoadGame::CLoadGame()
{
	m_pBackground = NULL;
	m_pLoadGameButton = NULL;
	m_pDeleteGameButton = NULL;
	m_pReturnButton = NULL;

	m_GamePath = "";

	m_pButtonList.clear();
	m_GameNameList.clear();
}




void CLoadGame::Init()
{
	m_pBackground = new CSprite;
	m_pBackground->Load(&g_pTextures->t_menuBackground);

	m_pLoadGameButton = new CButton;
	m_pLoadGameButton->Load(&g_pTextures->t_menuButtonLoadThisGame, g_pFramework->GetRenderWindow()->getSize().x/2 - 350, g_pFramework->GetRenderWindow()->getSize().y - g_pFramework->GetRenderWindow()->getSize().y/4, 3);

	m_pDeleteGameButton = new CButton;
	m_pDeleteGameButton->Load(&g_pTextures->t_menuButtonDeleteThisGame, g_pFramework->GetRenderWindow()->getSize().x/2 + 150, g_pFramework->GetRenderWindow()->getSize().y - g_pFramework->GetRenderWindow()->getSize().y/4, 3);

	m_pReturnButton = new CButton;
	m_pReturnButton->Load(&g_pTextures->t_menuButtonReturn, g_pFramework->GetRenderWindow()->getSize().x/2 - 100, g_pFramework->GetRenderWindow()->getSize().y - 150, 3);

	m_pButtonUp = new CButton;
	m_pButtonUp->Load(&g_pTextures->t_menuButtonUp, g_pFramework->GetRenderWindow()->getSize().x - 100, 200, 1);
	m_pButtonDown = new CButton;
	m_pButtonDown->Load(&g_pTextures->t_menuButtonDown, g_pFramework->GetRenderWindow()->getSize().x - 100 , g_pFramework->GetRenderWindow()->getSize().y - 200, 1);

	m_font.loadFromFile("Data/Fonts/ltromatic.ttf");
	m_text.setFont(m_font);
	m_text.setCharacterSize(32);
	m_text.setColor(Color(0, 0, 0));

	is_running = true;
	m_returnNumber = 0;
	m_scrollPosition = 0;
	

	char* var = getenv("APPDATA");
	string pathString = var;
	pathString.append("/Dig Deeper/Saves/");


	directory_iterator end_itr;
	for(directory_iterator itr(pathString); itr != end_itr; itr++)
	{
		if(is_directory(itr->status()))
		{
			Savegame savegame;
			savegame.m_clicked = false;
			savegame.m_path = itr->path();
			m_GameNameList.push_back(savegame);
		}
	}

	int y = 30;

	for(int i = 0; i < m_GameNameList.size(); i++)
	{
		CSprite* sprite = new CSprite;
		sprite->Load(&g_pTextures->t_menuButtonBlank, 2, 500, 100);
		sprite->SetPos( g_pFramework->GetRenderWindow()->getSize().x/2 - 250, y);
		m_pButtonList.push_back(sprite);

		y += 130;
	}
}



string CLoadGame::Quit()
{
	SAFE_DELETE(m_pBackground);
	SAFE_DELETE(m_pLoadGameButton);
	SAFE_DELETE(m_pDeleteGameButton);
	SAFE_DELETE(m_pReturnButton);
	SAFE_DELETE(m_pButtonUp);
	SAFE_DELETE(m_pButtonDown);

	list<CSprite*>::iterator i;
	for(i = m_pButtonList.begin(); i != m_pButtonList.end(); i++)
	{
		SAFE_DELETE(*i);
	}

	m_pButtonList.clear();
	m_GameNameList.clear();

	return m_GamePath;
}


int CLoadGame::Run()
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






void CLoadGame::RenderButtons()
{
	list<CSprite*>::iterator ib;
	list<Savegame>::iterator is;
	list<Savegame>::iterator forIs;

	if(m_pLoadGameButton->Render(m_ButtonEventtype) == true)
	{
		if(m_GamePath.length() > 0)
		{
			m_returnNumber = 10;
			is_running = false;
		}
	}

	if(m_pDeleteGameButton->Render(m_ButtonEventtype) == true)
	{
		if(m_GamePath.length() > 0)
		{
			//get path
			char* var = getenv("APPDATA");
			string pathString = var;
			pathString.append("/Dig Deeper/Saves/");

			path Path;
			Path.append(pathString + m_GamePath);
			remove_all(Path);
		
			ib = m_pButtonList.begin();

			for(is = m_GameNameList.begin(); is != m_GameNameList.end(); is++)
			{
				if((*is).m_path.filename() == m_GamePath)
				{
					is = m_GameNameList.erase(is);
					SAFE_DELETE(*ib);
					ib = m_pButtonList.erase(ib);
					break;
				}
				ib++;
			}

			m_GamePath.clear();
		}
	}


	if(m_pButtonUp->Render(m_ButtonEventtype) == true)
	{
		m_scrollPosition--;
		if(m_scrollPosition < 0)
			m_scrollPosition = 0;
	}

	if(m_pButtonDown->Render(m_ButtonEventtype) == true)
	{
		if(m_pButtonList.size() >= 4)
		{
			m_scrollPosition++;
			if(m_scrollPosition > m_pButtonList.size() - 4)
				m_scrollPosition = m_pButtonList.size() - 4;
		}
	}


	is = m_GameNameList.begin();

	for(int i = 0; i < m_scrollPosition; i++)
	{
		ib++;
		is++;
	}

	int counter = 0;

	//Iterate through the button list
	for(ib = m_pButtonList.begin(); ib != m_pButtonList.end(); ib++)
	{
		(*ib)->SetPos( g_pFramework->GetRenderWindow()->getSize().x/2 - 250, 30 + (counter*130));
		//sets the name of the saved directory as text
		m_text.setString((*is).m_path.filename().c_str());
		m_text.setPosition((*ib)->GetRect().left + (*ib)->GetRect().width/2 - m_text.getGlobalBounds().width/2, (*ib)->GetRect().top + 30);
		
		//if a savegame was clicked: save the path
		if((*ib)->GetRect().contains(Mouse::getPosition()) && m_ButtonEventtype == MOUSE_LEFT_UP)
		{
			if((*is).m_clicked)
			{
				(*is).m_clicked = false;
				m_GamePath.clear();
			}
			else
			{
				m_GamePath = (*is).m_path.filename().string().c_str();		

				for (forIs = m_GameNameList.begin(); forIs != m_GameNameList.end(); forIs++)
					forIs->m_clicked = false;
				
				(*is).m_clicked = true;
			}
		}

		//render the button
		if((*is).m_clicked)
			(*ib)->Render(g_pFramework->GetRenderWindow(), 1.0f);
		else
			(*ib)->Render(g_pFramework->GetRenderWindow(), 0.0f);
		

		g_pFramework->GetRenderWindow()->draw(m_text);

		is++;
		counter++;

		if((counter) >= 4)
			break;
	}

	if(m_pReturnButton->Render(m_ButtonEventtype) == true)
	{
		m_returnNumber = 4;
		is_running = false;
	}
}