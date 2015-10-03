#include "Game.hpp"




CGame::CGame()
{
	m_pWorld = NULL;
	m_pPlayer = NULL;
	m_pBackground = NULL;
	m_pNightSky = NULL;
	m_pPauseMenu = NULL;
	m_pContinueButton = NULL;
	m_pSaveButton = NULL;
	m_pQuitButton = NULL;
}




void CGame::Init(SNewWorldAttributes _attributes, bool _loaded)
{
	//sets the view to it's normal size 
	m_View.reset(FloatRect(0,0, (float)g_pFramework->GetRenderWindow()->getSize().x, (float)g_pFramework->GetRenderWindow()->getSize().y));

	//applies the view to the window
	g_pFramework->GetRenderWindow()->setView(m_View);

	//Inits the profiler
	g_pProfiler->Init();

	//Loads the background
	m_pBackground = new CSprite;
	m_pBackground->Load(&g_pTextures->t_gameBackground);

	//Loads the nightsky
	m_pNightSky = new CSprite;
	m_pNightSky->Load(&g_pTextures->t_gameNightSky);
	m_pNightSky->SetColor(255, 255, 255, 0);

	//Init the world with the right size
	m_pWorld = new CWorld;
	m_pPlayer = new CPlayer;

	char* var = getenv("APPDATA");
	boost::filesystem::path Path;
	Path = var;
	Path.append("/Dig Deeper/Settings.stt");

	if (boost::filesystem::exists(Path))
	{
		ifstream Input(Path.string());
		Input.read((char *)&m_Settings, sizeof(m_Settings));
		Input.close();
	}
	else
	{
		m_Settings.m_beam_numbers = false;
		m_Settings.m_inventory_numbers = false;
		m_Settings.m_fast_light = true;
	}

	//Inits the npc machine
	m_NpcMachine.Init(m_pWorld, m_pPlayer, &m_View);
	m_NpcMachine.AddObserver(&m_SoundEngine);

	if(_attributes.WorldSize == SMALL)
		m_pWorld->Init(100, 54, &m_View, &m_NpcMachine, m_Settings.m_fast_light, _loaded);
	else if(_attributes.WorldSize == MEDIUM)
		m_pWorld->Init(200, 100, &m_View, &m_NpcMachine, m_Settings.m_fast_light, _loaded);
	else
		m_pWorld->Init(300, 200, &m_View, &m_NpcMachine, m_Settings.m_fast_light, _loaded);

	//Inits the player
	m_pPlayer->Init(700, 300, m_pWorld, &m_View, _attributes.PlayerClass, m_Settings.m_inventory_numbers, m_Settings.m_beam_numbers);

	/*if(!_loaded)
	{
		m_NpcMachine.AddNpc(GOBLIN, 1500, 100, false);
	}*/

	g_pProjectiles->Init(m_pWorld, m_pPlayer, &m_NpcMachine);
	g_pEffects->Init(m_pWorld, m_pPlayer, &m_NpcMachine);

	m_pPauseMenu = new CSprite;
	m_pPauseMenu->Load(&g_pTextures->t_pauseMenu);
	m_pPauseMenu->SetPos((int)(g_pFramework->GetRenderWindow()->getSize().x/2 - m_pPauseMenu->GetRect().width/2), (int)(g_pFramework->GetRenderWindow()->getSize().y/2 - m_pPauseMenu->GetRect().height/2));

	m_pContinueButton = new CButton;
	m_pContinueButton->Load(&g_pTextures->t_pauseMenuContinueButton, m_pPauseMenu->GetRect().left + 50, m_pPauseMenu->GetRect().top + 25, 3);

	m_pSaveButton = new CButton;
	m_pSaveButton->Load(&g_pTextures->t_pauseMenuSaveButton, m_pPauseMenu->GetRect().left + 50, m_pPauseMenu->GetRect().top + 100, 3);

	m_pQuitButton = new CButton;
	m_pQuitButton->Load(&g_pTextures->t_pauseMenuQuitButton, m_pPauseMenu->GetRect().left + 50, m_pPauseMenu->GetRect().top + 175, 3);

	//sets the fps counter and the fps timer to zero
	m_frame = 0;
	m_currentFPS = 0;
	m_seconds = 0;

	m_TimeRunning = 0;

	//select the first music
	m_music = rand()%10;

	for (int i = 0; i < 10; i++)
	{
		song_played[i] = false;
	}

	song_played[m_music] = true;

	m_Name = _attributes.GameName;

	//the zoom is normal
	m_zoom = 1;

	m_rotatingDown = true;

	//the game is now running
	is_running = true;

	g_pFramework->WriteToLog(INFO, "Initialized Game...");
}




void CGame::Quit()
{
	SAFE_DELETE(m_pBackground);
	SAFE_DELETE(m_pNightSky);
	SAFE_DELETE(m_pWorld);
	SAFE_DELETE(m_pPlayer);
	SAFE_DELETE(m_pPauseMenu);
	SAFE_DELETE(m_pContinueButton);
	SAFE_DELETE(m_pSaveButton);
	SAFE_DELETE(m_pQuitButton);

	m_NpcMachine.RemoveObserver(&m_SoundEngine);
	m_NpcMachine.Quit();

	g_pSound->m_musicGame[m_music].stop();

	g_pProfiler->Quit();

	g_pProjectiles->Quit();
	g_pEffects->Quit();

	//Sets the default view
	g_pFramework->GetRenderWindow()->setView(g_pFramework->GetRenderWindow()->getDefaultView());
}




void CGame::Run()
{
	g_pSound->m_musicGame[m_music].play();

	g_pFramework->Update();
	while(is_running)
	{
		g_pFramework->Update();
		g_pFramework->Clear();

		m_TimeRunning += g_pTimer->GetElapsedTime().asSeconds();

		//clear the profiler
		g_pProfiler->ClearProfiler();


		g_pFramework->GetRenderWindow()->setView(m_View);

		g_pFramework->ProcessEvents();

		Zoom();
		
		//check for the pause menu
		if(g_pFramework->keyStates.escapeDown)
		{
			PauseGame();

			g_pFramework->Update();
			g_pFramework->Update();
			g_pFramework->Clear();
			g_pFramework->GetRenderWindow()->setView(m_View);

			g_pFramework->ProcessEvents();
		}
		
		//check for the help page
		if (g_pFramework->keyStates.f1)
		{
			g_pFramework->GetRenderWindow()->setView(g_pFramework->GetRenderWindow()->getDefaultView());

			CHelpPage help;
			help.Init();
			help.Run();
			help.Quit();

			g_pFramework->Update();
			g_pFramework->Update();
			g_pFramework->Clear();
			g_pFramework->GetRenderWindow()->setView(m_View);

			g_pFramework->ProcessEvents();
		}

		//check for fast saving
		if (g_pFramework->keyStates.f6)
		{
			SaveGame();
			g_pFramework->Update();
		}

		CheckMusic();
		m_SoundEngine.CheckAllSounds();


		if (m_zoom == 1)
		{
			if (m_pWorld->CheckPlaceables(m_pPlayer->GetRect(), m_pPlayer))
			{
				g_pFramework->GetRenderWindow()->setView(g_pFramework->GetRenderWindow()->getDefaultView());

				Sprite sprite;
				sprite.setTexture(g_pTextures->t_BackgroundWon);
				sprite.setScale((float)g_pFramework->GetRenderWindow()->getSize().x / (float)sprite.getLocalBounds().width, (float)g_pFramework->GetRenderWindow()->getSize().y / (float)sprite.getLocalBounds().height);

				g_pFramework->GetRenderWindow()->draw(sprite);
				g_pFramework->Flip();

				sleep(seconds(5));

				SaveHighscore();

				is_running = false;
			}
		}

		//Checks all npcs
		m_NpcMachine.CheckAllNpcs();


		g_pProjectiles->CheckProjectiles();
		g_pEffects->CheckEffects();


		RenderBackground();
		m_pWorld->Render();

		CheckView();

		//renders the player
		m_pPlayer->Render();

		//renders the npcs
		m_NpcMachine.RenderAllNpcs();

		g_pProjectiles->Render();
		g_pEffects->Render();

		//renders darkness and light
		m_pWorld->RenderLight();


		//Renders the damage indicator
		m_NpcMachine.RenderDamageIndicator();


		//Sets the default view for rendering the panels
		g_pFramework->GetRenderWindow()->setView(g_pFramework->GetRenderWindow()->getDefaultView());

		m_pPlayer->RenderInventory();

		//sets the fps value
		g_pProfiler->SetProfilingValue(FPS, m_currentFPS);
		g_pProfiler->SetProfilingValue(XPOS, m_pPlayer->GetRect().left);
		g_pProfiler->SetProfilingValue(YPOS, m_pPlayer->GetRect().top);
		g_pProfiler->SetProfilingValue(MUSICNUMBER, m_music);

		//show the profiler
		g_pProfiler->ShowProfiler();

		if (m_pPlayer->GetHealth() <= 0)
		{
			Sprite sprite;
			sprite.setTexture(g_pTextures->t_BackgroundDead);
			sprite.setScale((float)g_pFramework->GetRenderWindow()->getSize().x / (float)sprite.getLocalBounds().width, (float)g_pFramework->GetRenderWindow()->getSize().y / (float)sprite.getLocalBounds().height);

			g_pFramework->GetRenderWindow()->draw(sprite);
			g_pFramework->Flip();

			g_pSound->m_sound.setBuffer(g_pSound->m_laughSound);
			g_pSound->m_sound.play();

			sleep(seconds(5));

			is_running = false;
		}

		g_pFramework->Flip();

	    CheckFps();

	}

	g_pFramework->ApplyShader(NO_SHADER);
}



//Moves the view and the player
void CGame::CheckView()
{
	if (m_pPlayer->GetDrunkness() > 5.0f)
		g_pFramework->ApplyShader(DRUNK);
	else
		g_pFramework->ApplyShader(NO_SHADER);


	//Moves the player
	Vector2f dwarfCenter = m_pPlayer->CheckMovement();

	//if the view is outside the world reset it
	if(dwarfCenter.x < m_View.getSize().x/2)
		dwarfCenter.x = m_View.getSize().x/2;
	if(dwarfCenter.x > m_pWorld->GetDimensions().x *100 - m_View.getSize().x/2)
		dwarfCenter.x = m_pWorld->GetDimensions().x *100 - m_View.getSize().x/2;
	if(dwarfCenter.y < m_View.getSize().y/2)
		dwarfCenter.y = m_View.getSize().y/2;
	if(dwarfCenter.y > m_pWorld->GetDimensions().y *100 - m_View.getSize().y/2)
		dwarfCenter.y = m_pWorld->GetDimensions().y *100 - m_View.getSize().y/2;

	//sets the view
	m_View.setCenter(dwarfCenter);

	//applies the view to the window
    g_pFramework->GetRenderWindow()->setView(m_View);
}




void CGame::CheckMusic()
{
	//is the music playing?
	if(g_pSound->m_musicGame[m_music].getStatus() == Music::Stopped)
	{
		//play random new music
		int newMusic = rand()%10;
		if(song_played[newMusic] == false)
		{
			m_music = newMusic;

			//if all songs were played already: reset the music
			bool song_left = false;
			BOOST_FOREACH(bool b, song_played)
			{
				if(b == false)
					song_left = true;
			}

			if(song_left == false)
			{
				BOOST_FOREACH(bool b, song_played)
					b = false;
			}

			song_played[newMusic] = true;

			g_pSound->m_musicGame[m_music].play();

			cout << "Now playing music number: " << m_music << endl;
		}
	}
}


void CGame::CheckFps()
{
	//add one frame
	m_frame++;

	//add the elapsed time to the frame timer
	m_seconds += g_pTimer->GetElapsedTime().asSeconds();

	//if one second has passed
	if(m_seconds >= 1.0f)
	{
		//write the frames per second and set the frame counter and the frame timer to zero
		m_currentFPS = m_frame;
		m_frame = 0;
		m_seconds = 0;
	}
}


//Renders the background
void CGame::RenderBackground()
{
	int x1, x2, x3, x4, y1, y2, y3, y4;
	int xView, yView;
	int background_width, background_height;
	IntRect offsets1, offsets2, offsets3, offsets4, offsets5, offsets6;


	//get the coordinates from the upper left corner of the view
	xView = (int)(m_View.getCenter().x - m_View.getSize().x/2);
	yView = (int)(m_View.getCenter().y - m_View.getSize().y/2);

	//get the widht and height of the background
	background_width = m_pBackground->GetRect().width;
	background_height = m_pBackground->GetRect().height - 400;

	//set the coordinates of the backgrounds
	x1 = xView - (xView % background_width);
	y1 = yView - (yView % background_height);

	x2 = x1 + background_width;
	y2 = y1;

	x3 = x1;
	y3 = y1 + background_height;

	x4 = x2;
	y4 = y3;


	//sets the texture rects of the background for rendering
	offsets1.left = xView - x1;
	offsets1.width = background_width - offsets1.left;

	//check for sky
	if (yView <= background_height - m_View.getSize().y)
		offsets1.top = yView - y1;
	else
		offsets1.top = yView - y1 + 400;

	offsets1.height = background_height - (yView - y1);


	//changes the position
	x1 = xView;
	y1 = yView;

	offsets2.left = 0;
	offsets2.top = offsets1.top;
	offsets2.width = (int)(m_View.getSize().x - offsets1.width);
	offsets2.height = offsets1.height;

	y2 = y1;

	offsets3.left = offsets1.left;
	offsets3.top = 400;
	offsets3.width = offsets1.width;
	offsets3.height = (int)(m_View.getSize().y - offsets1.height);

	x3 = x1;

	offsets4.left = 400;
	offsets4.top = offsets3.top;
	offsets4.width = offsets2.width;
	offsets4.height = offsets3.height;


	//if the sky can be seen
	if(yView <= 400)
	{
		//sets the texture rects of the night sky for rendering
		offsets5 = offsets1;
		offsets5.height = m_pNightSky->GetRect().height - yView;

		offsets6 = offsets2;
		offsets6.height = offsets5.height;
	}


	//Render the backgrounds
	m_pBackground->setTextureRect(offsets1);
	m_pBackground->SetPos(x1, y1);
	m_pBackground->Render(g_pFramework->GetRenderWindow());

	m_pBackground->setTextureRect(offsets2);
	m_pBackground->SetPos(x2, y2);
	m_pBackground->Render(g_pFramework->GetRenderWindow());
	
	m_pBackground->setTextureRect(offsets3);
	m_pBackground->SetPos(x3, y3);
	m_pBackground->Render(g_pFramework->GetRenderWindow());

	m_pBackground->setTextureRect(offsets4);
	m_pBackground->SetPos(x4, y4);
	m_pBackground->Render(g_pFramework->GetRenderWindow());

	if(yView <= 400)
	{
		m_pNightSky->setTextureRect(offsets5);
		m_pNightSky->SetPos(x1, y1);
		m_pNightSky->SetColor(255, 255, 255, m_pWorld->GetNightAlpha());
		m_pNightSky->Render(g_pFramework->GetRenderWindow());

		m_pNightSky->setTextureRect(offsets6);
		m_pNightSky->SetPos(x2, y2);
		m_pNightSky->SetColor(255, 255, 255, m_pWorld->GetNightAlpha());
		m_pNightSky->Render(g_pFramework->GetRenderWindow());
	}

	//sets the default texture rect
	m_pBackground->setTextureRectToDefault();
	m_pNightSky->setTextureRectToDefault();
}





void CGame::PauseGame()
{
	bool is_open = true;
	int buttonEventtype = 0;

	g_pFramework->GetRenderWindow()->setView(g_pFramework->GetRenderWindow()->getDefaultView());

	while(is_open)
	{
		buttonEventtype = 0;
		g_pFramework->Update();
		g_pFramework->Clear();

		g_pFramework->ProcessEvents();

		if(g_pFramework->keyStates.leftMouseUp)
			buttonEventtype = 1;

		m_pPauseMenu->Render(g_pFramework->GetRenderWindow());

		if(m_pContinueButton->Render(buttonEventtype))
			is_open = false;

		if(m_pSaveButton->Render(buttonEventtype))
		{
			SaveGame();
			is_open = false;
		}

		if(m_pQuitButton->Render(buttonEventtype))
		{
			is_running = false;
			is_open = false;
		}

		g_pFramework->Flip();
	}
}




//checks if the player wants to zoom out or in
void CGame::Zoom()
{
	//does the player want to zoom in?
	if(g_pFramework->keyStates.add)
	{
		if(m_zoom > 1)
		{	
			m_zoom *= 0.8f;
			m_View.zoom(0.8f);
		}
	}
	//or out?
	else if(g_pFramework->keyStates.subtract)
	{
		if(m_zoom <= 1.953125)
		{
			m_zoom *= 1.25f;
			m_View.zoom(1.25f);
		}
	}
}




void CGame::SaveGame()
{
	//creates a new directory if needed
	//get the path of the directory

	char* var = getenv("APPDATA");
	string pathString = var;
	pathString.append("/Dig Deeper/Saves/");
	pathString.append(m_Name.c_str());

	boost::filesystem::path savegame(pathString);

	//create the directory
	if(!exists(savegame))
		create_directory(savegame);

	//saves the player
	ofstream outputFile(pathString + "/Player.pla", ios::binary);
	outputFile.clear();
	binary_oarchive playerArchive(outputFile);
	playerArchive << m_pPlayer;
	outputFile.close();

	//saves the world
	outputFile.open(pathString + "/World.wld", ios::binary);
	outputFile.clear();
	binary_oarchive worldArchive(outputFile);
	worldArchive << m_pWorld;
	outputFile.close();

	//saves the npcs
	outputFile.open(pathString + "/Npcs.npc", ios::binary);
	outputFile.clear();
	binary_oarchive npcArchive(outputFile);
	npcArchive << m_NpcMachine;
	outputFile.close();

	//save the game data
	outputFile.open(pathString + "/Gamedata.gmd", ios::binary);
	outputFile.clear();
	binary_oarchive gameArchive(outputFile);
	gameArchive << m_TimeRunning;
	outputFile.close();
}




void CGame::Load(string _path)
{
	SNewWorldAttributes attributes;
	attributes.GameName = _path;
	attributes.PlayerClass = MINER;
	attributes.WorldSize = SMALL;

	Init(attributes, true);
	SAFE_DELETE(m_pPlayer);

	char* var = getenv("APPDATA");
	string pathString = var;
	pathString.append("/Dig Deeper/Saves/" + _path);

	boost::filesystem::path savegame(pathString);

	cout <<"Load player..." << endl;

	//loads the player
	ifstream inputFile(pathString + "/Player.pla", ios::binary);
	binary_iarchive playerArchive(inputFile);
	playerArchive >> m_pPlayer;
	inputFile.close();

	cout <<"Loaded player..." << endl;

	cout <<"Load world..." << endl;

	SAFE_DELETE(m_pWorld);
	//loads the world
	inputFile.open(pathString + "/World.wld", ios::binary);
	binary_iarchive worldArchive(inputFile);
	worldArchive >> m_pWorld;
	inputFile.close();

	cout <<"World loaded" << endl;

	//load the npcs
	inputFile.open(pathString + "/Npcs.npc", ios::binary);
	binary_iarchive npcArchive(inputFile);
	npcArchive >> m_NpcMachine;
	inputFile.close();

	//load the game data
	savegame.append("/Gamedata.gmd");

	if (exists(savegame))
	{
		inputFile.open(pathString + "/Gamedata.gmd", ios::binary);
		binary_iarchive gameArchive(inputFile);
		gameArchive >> m_TimeRunning;
		inputFile.close();
	}
	else
		m_TimeRunning = 0;

	m_pPlayer->InitLoaded(500, 300, m_pWorld, &m_View, m_Settings.m_inventory_numbers, m_Settings.m_beam_numbers);
	m_pWorld->Init(0, 0, &m_View, &m_NpcMachine, m_Settings.m_fast_light, true);
	m_NpcMachine.Init(m_pWorld, m_pPlayer, &m_View, true);
	g_pProjectiles->Init(m_pWorld, m_pPlayer, &m_NpcMachine);
}




void CGame::SaveHighscore()
{
	SHighscore highscore[10];

	//get the path
	char* var = getenv("APPDATA");
	string Path = var;
	Path.append("/Dig Deeper/Highscore_02.hsc");

	if (!boost::filesystem::exists(boost::filesystem::path(Path)))
		ClearHighscore();

	//open the file
	ifstream Input(Path, ios::binary);
	Input.read((char *)&highscore, sizeof(highscore));
	Input.close();


	if (highscore[9].m_timeNeeded > m_TimeRunning)
	{
		CStringInput stringInput;
		stringInput.Init(g_pTextures->f_coolsville, 35, g_pFramework->GetWindow()->getSize().x / 2, g_pFramework->GetWindow()->getSize().y / 2, Color(200, 200, 0));

		CButton *button = new CButton;
		button->Load(&g_pTextures->t_menuButtonSaveHighscore, g_pFramework->GetWindow()->getSize().x / 2 - 100, g_pFramework->GetWindow()->getSize().y - 100, 3);

		//init the text
		Text text;
		text.setFont(g_pTextures->f_coolsville);
		text.setCharacterSize(35);
		text.setColor(Color(200, 0, 0));
		text.setString("Gib deinen Namen ein:");
		text.setPosition(g_pFramework->GetWindow()->getSize().x / 2 - text.getGlobalBounds().width / 2, 100);

		bool quit = false;

		while (quit == false)
		{
			g_pFramework->Update();
			g_pFramework->Clear();

			g_pFramework->ProcessEvents();

			g_pFramework->GetRenderWindow()->draw(text);

			stringInput.HandleInput();

			if (button->Render(g_pFramework->keyStates.leftMouseUp))
			{
				quit = true;
			}

			stringInput.Show(g_pFramework->GetRenderWindow());

			g_pFramework->Flip();
		}

		//save the highscore
		for (int i = 0; i < 10; i++)
		{
			if (highscore[i].m_timeNeeded > m_TimeRunning)
			{
				for (int a = 9; a > i; a--)
				{
					highscore[a].m_name = highscore[a - 1].m_name;
					highscore[a].m_level = highscore[a - 1].m_level;
					highscore[a].m_attributes = highscore[a - 1].m_attributes;
					highscore[a].m_class = highscore[a - 1].m_class;
					highscore[a].m_timeNeeded = highscore[a - 1].m_timeNeeded;
				}
				highscore[i].m_name = stringInput.GetString().c_str();
				highscore[i].m_level = m_pPlayer->GetLevel();
				highscore[i].m_attributes = m_pPlayer->GetPlayerBasicAttributes();
				highscore[i].m_class = m_pPlayer->GetClass();
				highscore[i].m_timeNeeded = m_TimeRunning;

				i = 10;
			}
		}


		SAFE_DELETE(button);

	}


	ofstream Output(Path, ios::binary);
	Output.write((char *)&highscore, sizeof(highscore));
	Output.close();
}







void CGame::ClearHighscore()
{
	char* var = getenv("APPDATA");
	string Path = var;
	Path.append("/Dig Deeper/Highscore_02.hsc");

	SHighscore highscore[10];

	for (int i = 0; i < 10; i++)
	{
		highscore[i].m_class = -1;
		highscore[i].m_timeNeeded = 10000;
		highscore[i].m_level = 0;
		highscore[i].m_name = "Niemand";

		highscore[i].m_attributes.armour = 0;
		highscore[i].m_attributes.breakingSpeed = 0;
		highscore[i].m_attributes.criticalChance = 0;
		highscore[i].m_attributes.criticalDamage = 0;
		highscore[i].m_attributes.currentExp = 0;
		highscore[i].m_attributes.currentMana = 0;
		highscore[i].m_attributes.currentHealth = 0;
		highscore[i].m_attributes.healthRegeneration = 0;
		highscore[i].m_attributes.luck = 0;
		highscore[i].m_attributes.manaRegeneration = 0;
		highscore[i].m_attributes.maxExp = 0;
		highscore[i].m_attributes.maxHealth = 0;
		highscore[i].m_attributes.maxMana = 0;
		highscore[i].m_attributes.strength = 0;
		highscore[i].m_attributes.speed = 0;
	}

	ofstream Output1(Path, ios::binary);
	Output1.write((char *)&highscore, sizeof(highscore));
	Output1.close();
}