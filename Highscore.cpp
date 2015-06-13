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
	m_pClear_button->Load(&g_pTextures->t_menuButtonDeleteHighscore, g_pFramework->GetWindow()->getSize().x - 400, 5* (g_pFramework->GetWindow()->getSize().y / 6), 3);

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
	ifstream Input("Data/Saves/Highscore.hsc", ios::binary);
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

	RectangleShape rect;
	rect.setFillColor(Color(0, 0, 0, 150));

	//if no highscore exists
	if (m_highscore.m_level == -1)
	{
		Stream << "Kein Highscore vorhanden!" << endl;
		text.setString(Stream.str());
		text.setPosition(g_pFramework->GetWindow()->getSize().x / 2 - text.getGlobalBounds().width / 2, g_pFramework->GetWindow()->getSize().y / 2 - text.getGlobalBounds().height / 2);

		rect.setPosition(text.getPosition().x -10, text.getPosition().y -10);
		rect.setSize(Vector2f(text.getGlobalBounds().width+20, text.getGlobalBounds().height+20));

		g_pFramework->GetRenderWindow()->draw(rect);
		g_pFramework->GetRenderWindow()->draw(text);
	}
	else
	{
		//draw the name
		Stream << m_highscore.m_name << endl;

		text.setColor(Color(23, 213, 32));
		text.setCharacterSize(40);
		text.setString(Stream.str());
		text.setPosition(g_pFramework->GetWindow()->getSize().x / 2 - text.getGlobalBounds().width / 2, 100);


		rect.setPosition(text.getPosition().x - 10, text.getPosition().y - 10);
		rect.setSize(Vector2f(text.getGlobalBounds().width + 20, text.getGlobalBounds().height + 20));

		g_pFramework->GetRenderWindow()->draw(rect);
		g_pFramework->GetRenderWindow()->draw(text);

		//draw class and level
		Stream.str("");

		Stream << "Erreichtes Level: " << m_highscore.m_level << endl;

		switch (m_highscore.m_class)
		{
		case(MINER) :
			Stream << "Startklasse: Minenarbeiter" << endl;
			break;
		case(BUILDER) :
			Stream << "Startklasse: Bauarbeiter" << endl;
			break;
		case(WARRIOR) :
			Stream << "Startklasse: Krieger" << endl;
			break;
		case(MAGE) :
			Stream << "Startklasse: Magier" << endl;
			break;
		default:
			Stream << "Startklasse: Cheater" << endl << endl;
			break;
		}

		text.setColor(Color(200, 200, 0));
		text.setPosition(g_pFramework->GetWindow()->getSize().x / 2 - text.getGlobalBounds().width / 2, text.getGlobalBounds().top + text.getGlobalBounds().height);
		text.setCharacterSize(35);
		text.setString(Stream.str());
		text.setPosition(g_pFramework->GetWindow()->getSize().x / 2 - text.getGlobalBounds().width / 2, text.getGlobalBounds().top);
		rect.setPosition(text.getPosition().x - 10, text.getPosition().y - 10);
		rect.setSize(Vector2f(text.getGlobalBounds().width + 20, text.getGlobalBounds().height + 20));

		g_pFramework->GetRenderWindow()->draw(rect);
		g_pFramework->GetRenderWindow()->draw(text);

		//draw attributes
		Stream.str("");
		Stream << "Leben:                          " << m_highscore.m_attributes.maxHealth << endl;
		Stream << "Lebensregeneration:      " << m_highscore.m_attributes.healthRegeneration << endl;
		Stream << "Mana:                             " << m_highscore.m_attributes.maxMana << endl;
		Stream << "Manaregeneration:         " << m_highscore.m_attributes.manaRegeneration << endl;
		Stream << "Rüstung:                         " << m_highscore.m_attributes.armour << endl;
		Stream << "Stärke:                            " << m_highscore.m_attributes.strength << endl;
		Stream << "Kritische Chance:          " << m_highscore.m_attributes.criticalChance << endl;
		Stream << "Kritischer Schaden:       " << m_highscore.m_attributes.criticalDamage << endl;
		Stream << "Glück:                             " << m_highscore.m_attributes.luck << endl;
		Stream << "Abbaugeschwindigkeit: " << m_highscore.m_attributes.breakingSpeed << endl;
		Stream << "Geschwindigkeit:          " << m_highscore.m_attributes.speed << endl;

		text.setPosition(g_pFramework->GetWindow()->getSize().x / 2 - text.getGlobalBounds().width / 2, text.getGlobalBounds().top + text.getGlobalBounds().height);
		text.setFont(g_pTextures->f_cents18);
		text.setCharacterSize(40);
		text.setString(Stream.str());
		text.setPosition(g_pFramework->GetWindow()->getSize().x / 2 - text.getGlobalBounds().width / 2, text.getGlobalBounds().top);
		rect.setPosition(text.getPosition().x - 10, text.getPosition().y - 10);
		rect.setSize(Vector2f(text.getGlobalBounds().width + 20, text.getGlobalBounds().height + 20));

		g_pFramework->GetRenderWindow()->draw(rect);
		g_pFramework->GetRenderWindow()->draw(text);

	}

}






void CHighscore::clearHighscore()
{
	m_highscore.m_class = -1;
	m_highscore.m_level = -1;
	m_highscore.m_name = "";

	ofstream Output1("Data/Saves/Highscore.hsc", ios::binary);
	Output1.write((char *)&m_highscore, sizeof(m_highscore));
	Output1.close();
}