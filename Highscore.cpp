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

	for (int i = 0; i < 10; i++)
	{
		m_highscoreText[i].setFont(g_pTextures->f_coolsville);
		m_highscoreText[i].setCharacterSize(30);
		m_highscoreText[i].setColor(Color(200, 200, 0));
	}

	is_running = true;
	m_mode = -1;
}



void CHighscore::Quit()
{
	SAFE_DELETE(m_pClear_button);
	SAFE_DELETE(m_pReturn_button);
}




void CHighscore::Run()
{
	char* var = getenv("APPDATA");

	//delete the old highscore file if existis
	string oldPath = var;
	oldPath.append("/Dig Deeper/Highscore.hsc");

	if (boost::filesystem::exists(path(oldPath)))
		boost::filesystem::remove(path(oldPath));


	string Path = var;
	Path.append("/Dig Deeper/Highscore_02.hsc");

	//if there is no highscore file: make new one and clear it
	if (!boost::filesystem::exists(path(Path)))
		clearHighscore();
	
	//open the highscore file
	ifstream Input(Path, ios::binary);
	Input.read((char *)&m_highscore, sizeof(m_highscore));
	//close the highscore file
	Input.close();

	stringstream stream;
	stream.str("");

	for (int i = 0; i < 10; i++)
	{

		stream << roundf(m_highscore[i].m_timeNeeded / 60) << " Minuten" << "     " << m_highscore[i].m_name;

		m_highscoreText[i].setString(stream.str());
		stream.str("");
	}


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
			if (m_mode == -1)
				is_running = false;
			else
				m_mode = -1;
		}


		if (m_mode == -1)
		{
			if (m_pClear_button->Render(g_pFramework->keyStates.leftMouseUp))
			{
				clearHighscore();
			}
		}


		g_pFramework->Flip();
	}
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

	if (m_mode == -1)
	{
		int y = 100;

		//draw the highscore list
		for (int i = 0; i < 10; i++)
		{
			m_highscoreText[i].setPosition(g_pFramework->GetWindow()->getSize().x / 2 - m_highscoreText[i].getGlobalBounds().width / 2, y);

			rect.setPosition(m_highscoreText[i].getGlobalBounds().left -10, m_highscoreText[i].getGlobalBounds().top-10);
			rect.setSize(Vector2f(m_highscoreText[i].getGlobalBounds().width +20, m_highscoreText[i].getGlobalBounds().height+20));

			g_pFramework->GetRenderWindow()->draw(rect);
			g_pFramework->GetRenderWindow()->draw(m_highscoreText[i]);

			if (m_highscoreText[i].getGlobalBounds().contains(Vector2f(Mouse::getPosition())) && g_pFramework->keyStates.leftMouseUp)
			{
				m_mode = i;
			}

			y += g_pFramework->GetWindow()->getSize().y/12;
			Stream.str("");
		}
	}
	else
	{


		//if no highscore exists
		if (m_highscore[m_mode].m_level == 0)
		{
			Stream << "Kein Highscore vorhanden!" << endl;
			text.setString(Stream.str());
			text.setPosition(g_pFramework->GetWindow()->getSize().x / 2 - text.getGlobalBounds().width / 2, g_pFramework->GetWindow()->getSize().y / 2 - text.getGlobalBounds().height / 2);

			rect.setPosition(text.getPosition().x - 10, text.getPosition().y - 10);
			rect.setSize(Vector2f(text.getGlobalBounds().width + 20, text.getGlobalBounds().height + 20));

			g_pFramework->GetRenderWindow()->draw(rect);
			g_pFramework->GetRenderWindow()->draw(text);
		}
		else
		{
			//draw the name
			Stream << m_highscore[m_mode].m_name << endl;

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

			Stream << "Erreichtes Level: " << m_highscore[m_mode].m_level << endl;

			switch (m_highscore[m_mode].m_class)
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
			Stream << "Leben:                          " << m_highscore[m_mode].m_attributes.maxHealth << endl;
			Stream << "Lebensregeneration:      " << m_highscore[m_mode].m_attributes.healthRegeneration << endl;
			Stream << "Mana:                             " << m_highscore[m_mode].m_attributes.maxMana << endl;
			Stream << "Manaregeneration:         " << m_highscore[m_mode].m_attributes.manaRegeneration << endl;
			Stream << "Rüstung:                         " << m_highscore[m_mode].m_attributes.armour << endl;
			Stream << "Stärke:                            " << m_highscore[m_mode].m_attributes.strength << endl;
			Stream << "Kritische Chance:          " << m_highscore[m_mode].m_attributes.criticalChance << endl;
			Stream << "Kritischer Schaden:       " << m_highscore[m_mode].m_attributes.criticalDamage << endl;
			Stream << "Glück:                             " << m_highscore[m_mode].m_attributes.luck << endl;
			Stream << "Abbaugeschwindigkeit: " << m_highscore[m_mode].m_attributes.breakingSpeed << endl;
			Stream << "Geschwindigkeit:          " << m_highscore[m_mode].m_attributes.speed << endl;

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
}






void CHighscore::clearHighscore()
{
	char* var = getenv("APPDATA");
	string Path = var;
	Path.append("/Dig Deeper/Highscore_02.hsc");

	for (int i = 0; i < 10; i++)
	{
		m_highscore[i].m_class = -1;
		m_highscore[i].m_level = 0;
		m_highscore[i].m_name = "Niemand";
		m_highscore[i].m_timeNeeded = 1000000;

		m_highscore[i].m_attributes.armour = 0;
		m_highscore[i].m_attributes.breakingSpeed = 0;
		m_highscore[i].m_attributes.criticalChance = 0;
		m_highscore[i].m_attributes.criticalDamage = 0;
		m_highscore[i].m_attributes.currentExp = 0;
		m_highscore[i].m_attributes.currentMana = 0;
		m_highscore[i].m_attributes.currentHealth = 0;
		m_highscore[i].m_attributes.healthRegeneration = 0;
		m_highscore[i].m_attributes.luck = 0;
		m_highscore[i].m_attributes.manaRegeneration = 0;
		m_highscore[i].m_attributes.maxExp = 0;
		m_highscore[i].m_attributes.maxHealth = 0;
		m_highscore[i].m_attributes.maxMana = 0;
		m_highscore[i].m_attributes.strength = 0;
		m_highscore[i].m_attributes.speed = 0;
	}

	ofstream Output1(Path, ios::binary);
	Output1.write((char *)&m_highscore, sizeof(m_highscore));
	Output1.close();


	//open the highscore file
	ifstream Input(Path, ios::binary);
	Input.read((char *)&m_highscore, sizeof(m_highscore));
	Input.close();

	stringstream stream;
	stream.str("");

	for (int i = 0; i < 10; i++)
	{
		stream << m_highscore[i].m_timeNeeded << " Minuten" << "     " << m_highscore[i].m_name;
		m_highscoreText[i].setString(stream.str());
		stream.str("");
	}
}