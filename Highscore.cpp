#include "Highscore.hpp"



CHighscore::CHighscore()
{
	m_pClear_button = NULL;
	m_pReturn_button = NULL;
}



void CHighscore::Init()
{

	m_background.Load(&g_pTextures->t_menuBackground);

	m_pClear_button = new CButton;
	m_pClear_button->Load(&g_pTextures->t_menuButtonLoad, g_pFramework->GetWindow()->getSize().x - 200, 5* (g_pFramework->GetWindow()->getSize().y / 6), 3);

	m_pReturn_button = new CButton;
	m_pReturn_button->Load(&g_pTextures->t_menuButtonReturn, 200, 5*(g_pFramework->GetWindow()->getSize().y / 6), 3);

	is_running = true;
}



void CHighscore::Quit()
{
	SAFE_DELETE(m_pClear_button);
	SAFE_DELETE(m_pReturn_button);
}




void CHighscore::Run()
{
	//open the highscore file
	ifstream Input("Data/Highscore.hsc", ios::binary);
	Input.read((char *)&m_highscore, sizeof(m_highscore));


	while (is_running == true)
	{
		g_pFramework->Update();
		g_pFramework->Clear();

		g_pFramework->ProcessEvents();

		//render the background
		m_background.Render(g_pFramework->GetRenderWindow());

		//render the highscore 
		RenderHighscore();

		//render the buttons
		if (m_pReturn_button->Render(g_pFramework->keyStates.leftMouseUp))
		{
			is_running = false;
		}


		if (m_pClear_button->Render(g_pFramework->keyStates.leftMouseUp))
		{
			clearHighscore();
		}


		g_pFramework->Flip();
	}

	//close the highscore file
	Input.close();
}



void CHighscore::RenderHighscore()
{
//init the text
	Text text;
	text.setFont(g_pTextures->f_coolsville);
	text.setCharacterSize(35);
	text.setColor(Color(200, 200, 0));

	std::stringstream Stream;
	Stream.str("");

	int y = 100;


	for (int i = 0; i < 10; i++)
	{
		//show the name
		Stream << m_highscore.points[i];
		text.setString(Stream.str());
		text.setPosition((g_pFramework->GetWindow()->getSize().x/2 - text.getGlobalBounds().width/2) - 200, y);
		g_pFramework->GetRenderWindow()->draw(text);

		//show the points
		text.setString(m_highscore.name[i].c_str());
		text.setPosition((g_pFramework->GetWindow()->getSize().x / 2 - text.getGlobalBounds().width / 2) + 200, y);
		g_pFramework->GetRenderWindow()->draw(text);

		y += g_pFramework->GetWindow()->getSize().y/12;
		Stream.str("");
	}
}






void CHighscore::clearHighscore()
{
	for (int i = 0; i < 10; i++)
	{
		m_highscore.name[i] = "Niemand";
		m_highscore.points[i] = 0;
	}


	ofstream Output1("Data/Highscore.hsc", ios::binary);
	Output1.write((char *)&m_highscore, sizeof(m_highscore));
	Output1.close();
}