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
	if(_attributes.WorldSize == SMALL)
		m_pWorld->Init(100, 54, &m_View, &m_NpcMachine, _loaded);
	else if(_attributes.WorldSize == MEDIUM)
		m_pWorld->Init(500, 100, &m_View, &m_NpcMachine, _loaded);
	else
		m_pWorld->Init(1000, 500, &m_View, &m_NpcMachine, _loaded);

	//Inits the player
	m_pPlayer = new CPlayer;
	m_pPlayer->Init(7000, 300, m_pWorld, &m_View, _attributes.PlayerClass);

	//Inits the npc machine
	m_NpcMachine.Init(m_pWorld, m_pPlayer, &m_View);
	//if(!_loaded)
	//{
	//	m_NpcMachine.AddNpc(BEE, 700, 300);
	//	m_NpcMachine.AddNpc(BEE, 800, 200);
	//	m_NpcMachine.AddNpc(BEE, 600, 300);
	//	m_NpcMachine.AddNpc(GOBLIN, 900, 270);
	//}

	g_pProjectiles->Init(m_pWorld, m_pPlayer, &m_NpcMachine);

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

	m_NpcMachine.Quit();

	g_pSound->m_musicGame[m_music].stop();

	g_pProfiler->Quit();

	g_pProjectiles->Quit();

	//Sets the default view
	g_pFramework->GetRenderWindow()->setView(g_pFramework->GetRenderWindow()->getDefaultView());
}




void CGame::Run()
{
	g_pSound->m_musicGame[m_music].play();

	g_pFramework->Update();
	while(is_running)
	{
		cout << "New frame" << endl;
		g_pFramework->Update();
		g_pFramework->Clear();

		//clear the profiler
		g_pProfiler->ClearProfiler();

	//if(Keyboard::isKeyPressed(Keyboard::Add))
	//{
	//	m_View.zoom(0.8f);
	//}
	//else if(Keyboard::isKeyPressed(Keyboard::Subtract))
	//{
	//	m_View.zoom(1.2f);
	//}
	

		g_pFramework->GetRenderWindow()->setView(m_View);

		g_pFramework->ProcessEvents();

		Zoom();
		
		if(g_pFramework->keyStates.escapeDown)
		{
			PauseGame();

			g_pFramework->Update();
			g_pFramework->Update();
			g_pFramework->Clear();
			g_pFramework->GetRenderWindow()->setView(m_View);

			g_pFramework->ProcessEvents();
		}
		cout << "Check music" << endl;

		CheckMusic();


		cout << "Check placeables" << endl;
		if(m_zoom == 1)
			m_pWorld->CheckPlaceables(m_pPlayer->GetRect(), m_pPlayer);


		cout << "check npcs" << endl;
		//Checks all npcs
		m_NpcMachine.CheckAllNpcs();


		cout << "check projectiles" << endl;
		g_pProjectiles->CheckProjectiles();


		cout << "render world" << endl;
		RenderBackground();
		m_pWorld->Render();


		CheckView();

		cout << "render player" << endl;
		//renders the player
		m_pPlayer->Render();


		cout << "render npcs" << endl;
		//renders the npcs
		m_NpcMachine.RenderAllNpcs();


		cout << "render projectiles" << endl;
		g_pProjectiles->Render();


		cout << "render light" << endl;
		//renders darkness and light
		m_pWorld->RenderLight();


		//Renders the damage indicator
		m_NpcMachine.RenderDamageIndicator();


		//Sets the default view for rendering the panels
		g_pFramework->GetRenderWindow()->setView(g_pFramework->GetRenderWindow()->getDefaultView());

		cout << "render inventory" << endl;
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


	cout << "XView :" << m_View.getCenter().x - m_View.getSize().x / 2 << endl;

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
		cout << "Fps: " << m_frame << endl;
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
	background_height = m_pBackground->GetRect().height;

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
	offsets1.top = yView - y1;
	offsets1.width = background_width - offsets1.left;
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
	offsets3.top = 0;
	offsets3.width = offsets1.width;
	offsets3.height = (int)(m_View.getSize().y - offsets1.height);

	x3 = x1;

	offsets4.left = 0;
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
	string pathString("Data/Saves/");
	pathString.append(m_Name.c_str());

	path savegame(pathString);

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
}




void CGame::Load(string _path)
{
	SNewWorldAttributes attributes;
	attributes.GameName = _path;
	attributes.PlayerClass = MINER;
	attributes.WorldSize = SMALL;

	Init(attributes, true);
	SAFE_DELETE(m_pPlayer);
	
	string pathString("Data/Saves/" + _path);

	path savegame(pathString);

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

	m_pPlayer->InitLoaded(500, 300, m_pWorld, &m_View);
	m_pWorld->Init(0,0, &m_View, &m_NpcMachine, true);
	m_NpcMachine.Init(m_pWorld, m_pPlayer, &m_View, true);
	g_pProjectiles->Init(m_pWorld, m_pPlayer, &m_NpcMachine);
}