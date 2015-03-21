#include "World.hpp"



CWorld::CWorld()
{
	m_pBlocks.resize(100);
	for(int i = 0; i < 100; i++)
		m_pBlocks[i].resize(54);

	m_pWalls.resize(100);
	for(int i = 0; i < 100; i++)
		m_pWalls[i].resize(54);

	for(int y = 0; y < 54; y++)
	{
		for(int x = 0; x < 100; x++)
		{
			m_pBlocks[x][y] = NULL;
		}
	}


	for(int y = 0; y < 54; y++)
	{
		for(int x = 0; x < 100; x++)
		{
			m_pWalls[x][y] = NULL;
		}
	}

	m_BlocksX = 100;
	m_BlocksY = 54;
}



CWorld::~CWorld()
{
	for(int y = 0; y < m_BlocksY; y++)
	{
		for(int x = 0; x < m_BlocksX; x++)
		{
			SAFE_DELETE(m_pBlocks[x][y]);
		}
	}


	for(int y = 0; y < m_BlocksY; y++)
	{
		for(int x = 0; x < m_BlocksX; x++)
		{
			SAFE_DELETE(m_pWalls[x][y]);
		}
	}


	
	list<CLittleItem>::iterator i;

	for(i = m_LittleItemList.begin(); i != m_LittleItemList.end(); i++)
	{
		(i)->Quit(true);
	}
		m_LittleItemList.clear();

	list<CPanel*>::iterator p;
	for(p = m_PanelList.begin(); p != m_PanelList.end(); p++)
	{
		(*p)->Quit();
		SAFE_DELETE(*p);
	}
	m_PanelList.clear();


	m_lightMachine.Quit();

}




void CWorld::Init(int _width, int _height, View* _view, bool _loaded)
{
	if(!_loaded)
	{
		m_BlocksX = _width;
		m_BlocksY = _height;

		m_NightAlpha = 0;
		m_fNightTimer = 500.0f;
		m_fSecondTimer = 0.0f;

		//set the world's size
		m_pBlocks.resize(_width);
		for(int i = 0; i < _width; i++)
			m_pBlocks[i].resize(_height);

		m_pWalls.resize(_width);
		for(int i = 0; i < _width; i++)
			m_pWalls[i].resize(_height);

		for(int y = 0; y < _height; y++)
		{
			for(int x = 0; x < _width; x++)
			{
				m_pBlocks[x][y] = NULL;
			}
		}

		for(int y = 0; y < _height; y++)
		{
			for(int x = 0; x < _width; x++)
			{
				m_pWalls[x][y] = NULL;
			}
		}


		GenerateWorld();
	}

	//m_lightMachine.Init(m_BlocksX*100, m_BlocksY*100);
	m_lightMachine.Init(_view);

	m_WorldHeight = m_BlocksY *100;
	m_WorldWidth = m_BlocksX *100;
}



//generates a random world
void CWorld::GenerateWorld()
{
	int possibility[8];


	int randomNumber;
	int possibilitySum = 0;
	srand((int)time(0));

	//generates the blocks
	for(int y = 4; y < m_BlocksY; y++)
	{
		for(int x = 0; x < m_BlocksX; x++)
		{	
			if(m_pBlocks[x][y] == NULL)
			{
				//set the start possibilities
				possibility[0] = 84;            //dirt
				possibility[1] = 10;            //stone

				if(y > 7)
					possibility[2] = 3;            //coal
				else
					possibility[2] = 0;

				if(y > 10)
					possibility[3] = 2;            //iron
				else
					possibility[3] = 0;

				if(y > 15)
					possibility[4] = 1;            //gold
				else
					possibility[4] = 0;

				if(y > 20)
					possibility[5] = 1;              //arcanus
				else
					possibility[5] = 0;

				if(y > 4)
					possibility[6] = 5;             //marble
				else
					possibility[6] = 0;

				if(y > 7)
					possibility[7] = 1;             //room
				else
					possibility[7] = 0;

				//if a near placeable is a specific type: greater chance, that this placeable will be the same type
				if(y > 4 && x > 0)
				{
					if(m_pBlocks[x-1][y] != NULL)
						if(m_pBlocks[x-1][y]->getID() != WOOD)
							possibility[m_pBlocks[x-1][y]->getID()-1] += 50;
					if(m_pBlocks[x][y-1] != NULL)
						if(m_pBlocks[x][y-1]->getID() != WOOD)
							possibility[m_pBlocks[x][y-1]->getID()-1] += 50;
				}



					//Create new Placeable
					m_pBlocks[x][y] = new CPlaceable;

					//the first layer is a dirt layer
					if(y != 4)
					{
						//calculate the sum
						possibilitySum = 0;
						for(int i = 0; i < 8; i++)
							possibilitySum += possibility[i];

						//generate a random number between 1 and 100
						randomNumber = rand()%possibilitySum +1;					

						//decide which placeable is going to be set
						if(randomNumber <= possibility[0])
							m_pBlocks[x][y]->Init(DIRT);
						else if(randomNumber <= possibility[1] + possibility[0])
							m_pBlocks[x][y]->Init(STONE);
						else if(randomNumber <= possibility[0] + possibility[1] + possibility[2])
							m_pBlocks[x][y]->Init(COALBLOCK);
						else if(randomNumber <= possibility[0] + possibility[1] + possibility[2] + possibility[3])
							m_pBlocks[x][y]->Init(IRONBLOCK);
						else if(randomNumber <= possibility[0] + possibility[1] + possibility[2] + possibility[3] + possibility[4])
							m_pBlocks[x][y]->Init(GOLDBLOCK);
						else if(randomNumber <= possibility[0] + possibility[1] + possibility[2] + possibility[3] + possibility[4] + possibility[5])
							m_pBlocks[x][y]->Init(ARCANUSBLOCK);
						else if(randomNumber <= possibility[0] + possibility[1] + possibility[2] + possibility[3] + possibility[4] + possibility[5] + possibility[6])
							m_pBlocks[x][y]->Init(MARBLE);
						else
						{
							SAFE_DELETE(m_pBlocks[x][y]);
							GenerateRoom(x, y);						
							x--;
							continue;
						}

					}
					else
						m_pBlocks[x][y]->Init(DIRT);

					//set position
					m_pBlocks[x][y]->SetPos(static_cast<float>(x*100), static_cast<float> (y * 100));
			}
			else
			{
				if(m_pBlocks[x][y]->getID() == ROOMFILL)
					SAFE_DELETE(m_pBlocks[x][y]);
			}
		}
	}
}
						



//Generates a random room
void CWorld::GenerateRoom(int _x, int _y)
{
	cout << "Build room..." << endl;

	//generate the size of the room
	int xSize = rand()%9 +3;
	int ySize = rand()%3 +3;

	if(_x + xSize <= m_BlocksX && _y + ySize <= m_BlocksY)
	{
		//build the room
		for(int y=_y; y < _y + ySize; y++)
		{
			for(int x=_x; x < _x + xSize; x++)
			{
			
				m_pBlocks[x][y] = new CPlaceable;

				//check if this block is one of the outer blocks
				if(y == _y || y == _y + ySize -1 || x == _x || x == _x + xSize -1)
				{
					m_pBlocks[x][y]->Init(WOOD);
					m_pBlocks[x][y]->SetPos(static_cast<float>(x*100), static_cast<float> (y * 100));	
				}
				else if(y == _y + ySize -2)
				{
					int type = rand()%10;

					//init the things in the room
					if(type == 5)
					{
						m_pBlocks[x][y]->Init(CUPBOARD);
						m_pBlocks[x][y]->SetPos(static_cast<float>(x*100), static_cast<float> (y * 100));
					}
					else if(type == 6)
					{
						m_pBlocks[x][y]->Init(CHEST);
						m_pBlocks[x][y]->SetPos(static_cast<float>(x*100), static_cast<float> (y * 100));
						m_pBlocks[x][y]->SetSpecialID(AddPanel(CHEST, x*100, y*100));
						FillChestRandomly(m_pBlocks[x][y]->GetSpecialID());
					}
					else if(type == 7)
					{
						m_pBlocks[x][y]->Init(FURNANCE);
						m_pBlocks[x][y]->SetPos(static_cast<float>(x*100), static_cast<float> (y * 100));
						m_pBlocks[x][y]->SetSpecialID(AddPanel(FURNANCE, x*100, y*100));
					}
					else if(type == 8)
					{
						m_pBlocks[x][y]->Init(TABLE);
						m_pBlocks[x][y]->SetPos(static_cast<float>(x*100), static_cast<float> (y * 100));
					}
					else
					{
						m_pBlocks[x][y]->Init(ROOMFILL);
					}


					m_pWalls[x][y] = new CPlaceable;
					m_pWalls[x][y]->Init(WOODWALL);
					m_pWalls[x][y]->SetPos(static_cast<float>(x*100), static_cast<float> (y * 100));
				
				}
				else
				{
					m_pBlocks[x][y]->Init(ROOMFILL);

					m_pWalls[x][y] = new CPlaceable;
					m_pWalls[x][y]->Init(WOODWALL);
					m_pWalls[x][y]->SetPos(static_cast<float>(x*100), static_cast<float> (y * 100));
				}

				}
			}
		}

	
}



void CWorld::Render(Vector2f _viewSize, Vector2f _viewCenter)
{
	//add time to the night timers
	m_fNightTimer += g_pTimer->GetElapsedTime().asSeconds();
	m_fSecondTimer += g_pTimer->GetElapsedTime().asSeconds();

	//if one cycle is finished: reset the timer
	if(m_fNightTimer >= 1020.0f)
		m_fNightTimer = 0.0f;

	//if it is dusk: make it darker
	if(m_fNightTimer >= 480.0f && m_fNightTimer <= 600.0f)
	{
		if(m_fSecondTimer >= 0.5f)
		{
			m_NightAlpha ++;
		}
	}
	//if it is night
	else if(m_fNightTimer > 600.0f && m_fNightTimer < 900.0f)
	{
		if(m_NightAlpha < 240)
		{
			if(m_fSecondTimer >= 0.5f)
				m_NightAlpha++;
		}
		else
			m_NightAlpha = 240;
	}
	//if it is dawn: make it brighter
	else if(m_fNightTimer >= 900)
	{
		if(m_fSecondTimer >= 0.5f)
		{
			m_NightAlpha --;
		}
	}
	//if it is day
	else
		m_NightAlpha = 0;
	
	//reset the second timer
	if(m_fSecondTimer >= 0.5f)
		m_fSecondTimer = 0.0f;

	int viewX = _viewCenter.x - _viewSize.x/2;
	int viewY = _viewCenter.y - _viewSize.y/2;

	//clear the light machine
	m_lightMachine.Clear(Color(0, 0, 0, m_NightAlpha));



	//get all the blocks, which are within the view
	int xStart = (int)((viewX)/100)-3;
	if(xStart < 0)
		xStart = 0;

	int yStart = (int)((viewY)/100)-3;
	if(yStart < 0)
		yStart = 0;

	int xEnd = (int)(xStart + _viewSize.x/100) +6;
	if(xEnd > m_BlocksX)
		xEnd = m_BlocksX;

	int yEnd = (int)(yStart + _viewSize.y/100)+6;
	if(yEnd > m_BlocksY)
	yEnd = m_BlocksY;


	//render the second layer walls
	for(int y = yStart; y < yEnd; y++)
	{
		for(int x = xStart; x < xEnd; x++)
		{	
			if(m_pWalls[x][y] != NULL)
				m_pWalls[x][y]->Render();			
		}
	}

	//render the placeables
	for(int y = yStart; y < yEnd; y++)
	{
		for(int x = xStart; x < xEnd; x++)
		{	
			if(m_pBlocks[x][y] != NULL)
			{
				m_pBlocks[x][y]->Render();		

				if(m_pBlocks[x][y]->getID() == FURNANCE)
					m_lightMachine.AddLightCircle(m_pBlocks[x][y]->GetRect().left + m_pBlocks[x][y]->GetRect().width/2 - 100, m_pBlocks[x][y]->GetRect().top - 15, 100, Color(230, 0,0));
				else if(m_pBlocks[x][y]->getID() == LANTERNP)
					m_lightMachine.AddLightCircle(m_pBlocks[x][y]->GetRect().left -100 , m_pBlocks[x][y]->GetRect().top - 60, 150, Color::Yellow);
				
			}
		}
	}


	//checks the panels on their special rendering
	list<CPanel*>::iterator p;

	for(p = m_PanelList.begin(); p != m_PanelList.end(); p++)
	{
		(*p)->CheckThings();
	}
	


	//Renders the little items
	list<CLittleItem>::iterator i;

	for(i = m_LittleItemList.begin(); i != m_LittleItemList.end(); i++)
	{
		if(i->GetRect().left >= xStart*100 &&  i->GetRect().left <= xEnd*100 && i->GetRect().top >= yStart*100 && i->GetRect().top <= yEnd*100)
		{
			i->Render();
		}
	}
}




void CWorld::RenderLight()
{
	m_lightMachine.Render();
	g_pProfiler->SetProfilingValue(NIGHTLEVEL, m_fNightTimer);
}


//returns true if the player would collide with a Placeable
bool CWorld::CheckLivingCollision(FloatRect _player)
{
	int xStart = (int)(_player.left/100) -2;
	if(xStart < 0)
		xStart = 0;

	int yStart = (int)(_player.top/100) -2;
	if(yStart < 0)
		yStart = 0;

	int xEnd = xStart +4;
	if(xEnd > m_BlocksX)
		xEnd = m_BlocksX;

	int yEnd = yStart +4;
	if(yEnd > m_BlocksY)
		yEnd = m_BlocksY;

	for(int y = yStart; y <= yEnd; y++)
	{
		for(int x = xStart; x <= xEnd; x++)
		{
			if(m_pBlocks[x][y] != NULL)
			{
				if(m_pBlocks[x][y]->IsPassable() == false)
				{
					if(_player.intersects((FloatRect)m_pBlocks[x][y]->GetRect()))
					return true;
				}
			}
		}
	}

	return false;
}


//returns ID of the thing the player collided with returns -1 if collided with nothing
int CWorld::CheckCollisionWithPassable(FloatRect _player)
{
	int xStart = (int)(_player.left/100) -2;
	if(xStart < 0)
		xStart = 0;

	int yStart = (int)(_player.top/100) -2;
	if(yStart < 0)
		yStart = 0;

	int xEnd = xStart +4;
	if(xEnd > m_BlocksX)
		xEnd = m_BlocksX;

	int yEnd = yStart +4;
	if(yEnd > m_BlocksY)
		yEnd = m_BlocksY;


	for(int y = yStart; y <= yEnd; y++)
	{
		for(int x = xStart; x <= xEnd; x++)
		{
			if(m_pBlocks[x][y] != NULL)
			{
				if(m_pBlocks[x][y]->IsPassable() == true)
				{
					if(_player.intersects((FloatRect)m_pBlocks[x][y]->GetRect()))
					{
						return m_pBlocks[x][y]->getID();
					}
				}
			}
		}
	}

	return -1;
}




//Checks wether placeables are broken by the player and deletes them and checks the little items
void CWorld::CheckPlaceables(IntRect _playerRect, CPlayer *_player, float _xView, float _yView)
{

	IntRect rectP;
	list<CPanel*>::iterator p;
	

	CheckLittle();

	int xStart = (int)(_playerRect.left/100) -1;
	if(xStart < 0)
		xStart = 0;

	int yStart = (int)(_playerRect.top/100) -1;
	if(yStart < 0)
		yStart = 0;

	int xEnd = (_playerRect.left/100) +1;
	if(xEnd > m_BlocksX)
		xEnd = m_BlocksX;

	int yEnd = (_playerRect.top/100) +1;
	if(yEnd > m_BlocksY)
		yEnd = m_BlocksY;



	for(int y = yStart; y <= yEnd; y++)
	{
		for(int x = xStart; x <= xEnd; x++)
		{
			//Checking for the placeables
			if(m_pBlocks[x][y] != NULL)
			{
				rectP = m_pBlocks[x][y]->GetRect();
				rectP.left = (m_pBlocks[x][y]->GetRect().left - (int)_xView);
				rectP.top = (m_pBlocks[x][y]->GetRect().top - (int)_yView);
		

				if(rectP.contains(Mouse::getPosition()) && Mouse::isButtonPressed(Mouse::Left))
				{
					if(m_pBlocks[x][y]->IsBroken(_player->m_modifications.breaking_speed))
					{
						//set the sound
						if(m_pBlocks[x][y]->getID() == GOLDBLOCK)
						{
							int soundNumber = rand()%3;

							m_sound.setBuffer(g_pTextures->m_goldSound[soundNumber]);
							m_sound.play();
						}

						bool lucky = false;

						if(m_pBlocks[x][y]->getID() >=3 && m_pBlocks[x][y]->getID() <= 6)
							lucky = true;
					
						do
						{
							AddLittleItem(m_pBlocks[x][y]->GetLittleID(), m_pBlocks[x][y]->GetRect().left + 23, m_pBlocks[x][y]->GetRect().top + 20);

							//check for luck
							int randomNumber = rand()%100 +1;
							if(randomNumber > _player->m_modifications.luck)
								lucky = false;

						}while(lucky);

						//if a furnance was destroyed: delete the panel
						if(m_pBlocks[x][y]->getID() == FURNANCE || m_pBlocks[x][y]->getID() == CHEST)
						{
							vector<SItem> droppedItems;

							//seek for the panel
							for(p = m_PanelList.begin(); p != m_PanelList.end(); p++)
							{
								//if found: delete it
								if(m_pBlocks[x][y]->GetSpecialID() == (*p)->GetNumber())
								{
									droppedItems = (*p)->GetContent();
									SAFE_DELETE(*p);
									m_PanelList.erase(p);
									break;
								}
							}

							//add the content as little items
							BOOST_FOREACH(SItem s, droppedItems)
							{
								for(int amount = 0; amount < s.amount; amount++)
								{
							
									if(amount > 0)
									{
										AddLittleItem(s.thing->getID(), m_pBlocks[x][y]->GetRect().left + 23, m_pBlocks[x][y]->GetRect().top - 20);
									}
									else
									{
										CLittleItem item;
										item.Init(s.thing, m_pBlocks[x][y]->GetRect().left + 23 + (rand()%50 -25), m_pBlocks[x][y]->GetRect().top - 20 + (rand()%50 -25));
										item.SetVel(Vector2f(0, -150.0f));
										m_LittleItemList.push_back(item);
									}
								}
							}
						}

						//for debugging:::
						if(m_pBlocks[x][y]->getID() == GOLDBLOCK || m_pBlocks[x][y]->getID() == IRONBLOCK || m_pBlocks[x][y]->getID() == ARCANUSBLOCK)
							_player->AddExp(5);

						SAFE_DELETE(m_pBlocks[x][y]);
					}
				}
				else
					m_pBlocks[x][y]->SetBreakingFalse();	


				//if the right mouse button was pressed
				if(rectP.contains(Mouse::getPosition()) && g_pFramework->keyStates.rightMouseDown)
				{
					if(m_pBlocks[x][y]->getID() == DOOR)
						m_pBlocks[x][y]->SetSpecialID(1);
				}
			}

			//checking for the second layer walls
			if(m_pWalls[x][y] != NULL)
			{
				rectP = m_pWalls[x][y]->GetRect();
				rectP.left = m_pWalls[x][y]->GetRect().left - (int)_xView;
				rectP.top = m_pWalls[x][y]->GetRect().top - (int)_yView;
		

				if(rectP.contains(Mouse::getPosition()) && Mouse::isButtonPressed(Mouse::Left))
				{
					if(m_pWalls[x][y]->IsBroken(_player->m_modifications.breaking_speed))
					{
						//if the placeable is broken: a little item is placed
						CLittleItem item;
						item.Init(m_pWalls[x][y], m_pWalls[x][y]->GetRect().left + 23 + (rand()%50 -25), m_pWalls[x][y]->GetRect().top - 20 + (rand()%50 -25));
						item.SetVel(Vector2f(0, -350.0f));
						m_LittleItemList.push_back(item);

						m_pWalls[x][y] = NULL;
					}
				}
				else
					m_pWalls[x][y]->SetBreakingFalse();
			}
		}
	}



	//check, wether the player has collided with a little item
	 list<CLittleItem>::iterator i;

	for(i = m_LittleItemList.begin(); i != m_LittleItemList.end(); i++)
	{

		if(_playerRect.intersects(i->GetRect()))
		{
			_player->Take(i->GetThing(),1);			
			i->Quit();
			m_LittleItemList.erase(i);
			return;
		}

	}


}




void CWorld::AddLittleItem(int _ID, int _x, int _y, int _amount)
{
	for(int i = 0; i < _amount; i++)
	{
		CLittleItem item;

		//if thing is a placeable
			if(_ID < PIBREAK)
			{
				CPlaceable *thing = new CPlaceable;
				thing->Init(_ID);
				item.Init(thing, _x + (rand()%50 -25), _y + (rand()%20));
			}
			//if thing is an item
			else if(_ID > PIBREAK && _ID < ITBREAK)
			{
				CItem *thing = new CItem;
				thing->Init(_ID);
				item.Init(thing, _x + (rand()%50 -25), _y + (rand()%20));	
			}
			//if thing is a tool
			else if(_ID > ITBREAK && _ID < TEBREAK)
			{
				CTool *thing = new CTool;
				thing->InitTool(_ID);
				item.Init(thing, _x + (rand()%50 -25), _y + (rand()%20));
			}
			//if thing is equipment
			else
			{
				CEquipment *thing = new CEquipment;
				thing->InitEquipment(_ID);
				item.Init(thing, _x + (rand()%50 -25), _y + (rand()%20));
			}

		item.SetVel(Vector2f(0, -350.0f));
		m_LittleItemList.push_back(item);
	}
}


//checks the little thing's movement
void CWorld::CheckLittle()
{
	IntRect rect;

	list<CLittleItem>::iterator i;

	for(i = m_LittleItemList.begin(); i != m_LittleItemList.end(); i++)
	{
			
		int xStart = static_cast<int>(i->GetRect().left/100) -2;
		if(xStart < 0)
			xStart = 0;

		int yStart =  static_cast<int>(i->GetRect().top/100) -2;
		if(yStart < 0)
			yStart = 0;

		int xEnd = static_cast<int>(i->GetRect().left/100) +2;
		if(xEnd > 100)
				xEnd = 100;

		int yEnd = static_cast<int>(i->GetRect().top/100) +2;
		if(yEnd > 54)
			yEnd = 54;
	
		//Check the velocity

		//if not the maximum velocity: add a value to the velocity
		if(i->GetVel().y < 250)
		{
			i->SetVel(Vector2f(0, i->GetVel().y + (int)(525 * g_pTimer->GetElapsedTime().asSeconds())));

			//if the velocity is to high: set it to 100
			if(i->GetVel().y > 250)
				i->SetVel(Vector2f(0, 250));
		}
		//if the velocity is to low: set it to -150
		if(i->GetVel().y < -350)
			i->SetVel(Vector2f(0, -350));
		//if it has reached it's highest point: set velocity to 100 (falling)
		if((int)i->GetVel().y == 0)
			i->SetVel(Vector2f(0, 250));

		//check for collisions with placeables
		for(int y = yStart; y < yEnd; y++)
		{
			for(int x = xStart; x < xEnd; x++)
			{
				if(m_pBlocks[x][y] != NULL)
				{
					if(m_pBlocks[x][y]->IsPassable() == false)
					{
						//define rect of the little thing in the next frame
						rect = i->GetRect();
						rect.top += (int(i->GetVel().y * g_pTimer->GetElapsedTime().asSeconds()));
						rect.height += 5;

						if(rect.intersects(m_pBlocks[x][y]->GetRect()))
						{
							//if the little thing has hit the placeable from the bottom side
							if(rect.top > m_pBlocks[x][y]->GetRect().top)
							{
								i->SetVel(Vector2f(0, 250));
								continue;
							}

							i->SetVel(Vector2f(0, i->GetVel().y/2));
							rect.top -= (int)(i->GetVel().y * g_pTimer->GetElapsedTime().asSeconds());

							if(rect.intersects(m_pBlocks[x][y]->GetRect()))
							{
								i->SetVel(Vector2f(0, i->GetVel().y/2));
								rect.top -= (int)(i->GetVel().y * g_pTimer->GetElapsedTime().asSeconds());

								if(rect.intersects(m_pBlocks[x][y]->GetRect()))
								{
									i->SetVel(Vector2f(0, 0));
								}
							}
						}
					}
				}
			}
		}
		//move the little thing according to it's velocity
		i->Move();
	}
		
}




//place a new thing at position x, y into the world
bool CWorld::PlaceNewThing(int x, int y, int ID, IntRect &_playerRect)
{
	x = x - x%100; 
	y = y -y%100;

	//if it was a wall and could be placed: return true
	if(CanPlaceWall(x, y, ID) == true)
		return true;
	
	//if the wall couldn't be placed: return false
	if(ID > PWBREAK && ID < PIBREAK)
		return false;

	//Check if there is enough space to place a thing
	if(m_pBlocks[x/100][y/100] == NULL 	&& _playerRect.intersects(IntRect(x,y, 100, 100)) == false)
	{
			if(y != 0 && x != 0)
			{
				if(m_pBlocks[x/100 -1][y/100] != NULL || m_pBlocks[x/100 +1][y/100] != NULL || m_pBlocks[x/100][y/100 -1] != NULL || m_pBlocks[x/100][y/100 +1] != NULL)
				{
					//some things must be placed on top of another
					if(ID == FURNANCE || ID == CHEST || ID == CUPBOARD || ID == LANTERN)
					{
						if(m_pBlocks[x/100][y/100+1] != NULL)
						{
							m_pBlocks[x/100][y/100] = new CPlaceable;
							if(ID == LANTERN)
								m_pBlocks[x/100][y/100]->Init(LANTERNP);
							else
								m_pBlocks[x/100][y/100]->Init(ID);
							m_pBlocks[x/100][y/100]->SetPos(x, y);
						}
						else
							return false;
					}
					//others not
					else
					{
						m_pBlocks[x/100][y/100] = new CPlaceable;
						m_pBlocks[x/100][y/100]->Init(ID);
						m_pBlocks[x/100][y/100]->SetPos(x, y);
					}

					if(ID == FURNANCE || ID == CHEST)
					{
						m_pBlocks[x/100][y/100]->SetSpecialID(AddPanel(ID, x, y));
					}

					return true;
				}
				else
					return false;
			}
			else if(y == 0 && x!= 0)
			{
				if(m_pBlocks[x/100 -1][y/100] != NULL || m_pBlocks[x/100 +1][y/100] != NULL || m_pBlocks[x/100][y/100 +1] != NULL)
				{
					//some things must be placed on top of another
					if(ID == FURNANCE || ID == CHEST || ID == CUPBOARD || ID == LANTERN)
					{
						if(m_pBlocks[x/100][y/100+1] != NULL)
						{
							m_pBlocks[x/100][y/100] = new CPlaceable;
							if(ID == LANTERN)
								m_pBlocks[x/100][y/100]->Init(LANTERNP);
							else
								m_pBlocks[x/100][y/100]->Init(ID);
							m_pBlocks[x/100][y/100]->SetPos(x, y);
						}
						else
							return false;
					}
					//others not
					else
					{
						m_pBlocks[x/100][y/100] = new CPlaceable;
						m_pBlocks[x/100][y/100]->Init(ID);
						m_pBlocks[x/100][y/100]->SetPos(x, y);
					}

					if(ID == FURNANCE || ID == CHEST)
					{
						m_pBlocks[x/100][y/100]->SetSpecialID(AddPanel(ID, x, y));
					}

					return true;
				}
				else
					return false;
			}
			else if(y != 0 && x == 0)
			{
				if(m_pBlocks[x/100 +1][y/100] != NULL || m_pBlocks[x/100][y/100 -1] != NULL || m_pBlocks[x/100][y/100 +1] != NULL)
				{
					//some things must be placed on top of another
					if(ID == FURNANCE || ID == CHEST || ID == CUPBOARD || ID == LANTERN)
					{
						if(m_pBlocks[x/100][y/100+1] != NULL)
						{
							m_pBlocks[x/100][y/100] = new CPlaceable;
							if(ID == LANTERN)
								m_pBlocks[x/100][y/100]->Init(LANTERNP);
							else
								m_pBlocks[x/100][y/100]->Init(ID);
							m_pBlocks[x/100][y/100]->SetPos(x, y);
						}
						else
							return false;
					}
					//others not
					else
					{
						m_pBlocks[x/100][y/100] = new CPlaceable;
						m_pBlocks[x/100][y/100]->Init(ID);
						m_pBlocks[x/100][y/100]->SetPos(x, y);
					}


					if(ID == FURNANCE || ID == CHEST)
					{
						m_pBlocks[x/100][y/100]->SetSpecialID(AddPanel(ID, x, y));
					}

					return true;
				}
				else
					return false;
			}
			else
			{
				if(m_pBlocks[x/100 +1][y/100] != NULL || m_pBlocks[x/100][y/100 +1] != NULL)
				{
					//some things must be placed on top of another
					if(ID == FURNANCE || ID == CHEST || ID == CUPBOARD || ID == LANTERN)
					{
						if(m_pBlocks[x/100][y/100+1] != NULL)
						{
							m_pBlocks[x/100][y/100] = new CPlaceable;
							if(ID == LANTERN)
								m_pBlocks[x/100][y/100]->Init(LANTERNP);
							else
								m_pBlocks[x/100][y/100]->Init(ID);
							m_pBlocks[x/100][y/100]->SetPos(x, y);
						}
						else
							return false;
					}
					//others not
					else
					{
						m_pBlocks[x/100][y/100] = new CPlaceable;
						m_pBlocks[x/100][y/100]->Init(ID);
						m_pBlocks[x/100][y/100]->SetPos(x, y);
					}


					if(ID == FURNANCE || ID == CHEST)
					{
						m_pBlocks[x/100][y/100]->SetSpecialID(AddPanel(ID, x, y));
					}

					return true;
				}
				else
					return false;
			}
		
	}
	
	return false;
}





bool CWorld::CanPlaceWall(int _x, int _y, int _ID)
{
	//Check if there is enough space to place a thing
	if(_ID > PWBREAK && _ID < PIBREAK && m_pWalls[_x/100][_y/100] == NULL)
	{
			if(_y != 0 && _x != 0)
			{
				if(m_pBlocks[_x/100 -1][_y/100] != NULL || m_pBlocks[_x/100 +1][_y/100] != NULL || m_pBlocks[_x/100][_y/100 -1] != NULL || m_pBlocks[_x/100][_y/100 +1] != NULL || m_pWalls[_x/100 -1][_y/100] != NULL || m_pWalls[_x/100 +1][_y/100] != NULL || m_pWalls[_x/100][_y/100 -1] != NULL || m_pWalls[_x/100][_y/100 +1] != NULL)
				{
					m_pWalls[_x/100][_y/100] = new CPlaceable;
					m_pWalls[_x/100][_y/100]->Init(_ID);
					m_pWalls[_x/100][_y/100]->SetPos(_x, _y);

					return true;
				}
				else
					return false;
			}
			else if(_y == 0 && _x!= 0)
			{
				if(m_pBlocks[_x/100 -1][_y/100] != NULL || m_pBlocks[_x/100 +1][_y/100] != NULL || m_pBlocks[_x/100][_y/100 +1] != NULL || m_pWalls[_x/100 -1][_y/100] != NULL || m_pWalls[_x/100 +1][_y/100] != NULL || m_pWalls[_x/100][_y/100 +1] != NULL )
				{
					m_pWalls[_x/100][_y/100] = new CPlaceable;
					m_pWalls[_x/100][_y/100]->Init(_ID);
					m_pWalls[_x/100][_y/100]->SetPos(_x, _y);

					return true;
				}
				else
					return false;
			}
			else if(_y != 0 && _x == 0)
			{
				if(m_pBlocks[_x/100 +1][_y/100] != NULL || m_pBlocks[_x/100][_y/100 -1] != NULL || m_pBlocks[_x/100][_y/100 +1] != NULL || m_pWalls[_x/100 +1][_y/100] != NULL || m_pWalls[_x/100][_y/100 -1] != NULL || m_pWalls[_x/100][_y/100 +1] != NULL)
				{	
					m_pWalls[_x/100][_y/100] = new CPlaceable;
					m_pWalls[_x/100][_y/100]->Init(_ID);
					m_pWalls[_x/100][_y/100]->SetPos(_x, _y);

					return true;
				}
				else
					return false;
			}
			else
			{
				if(m_pBlocks[_x/100 +1][_y/100] != NULL || m_pBlocks[_x/100][_y/100 +1] != NULL || m_pWalls[_x/100 +1][_y/100] != NULL || m_pWalls[_x/100][_y/100 +1] != NULL)
				{
					m_pWalls[_x/100][_y/100] = new CPlaceable;
					m_pWalls[_x/100][_y/100]->Init(_ID);
					m_pWalls[_x/100][_y/100]->SetPos(_x, _y);

					return true;
				}
				else
					return false;
			}
		
	}
	
	return false;
}





int CWorld::AddPanel(int _ID, int _x, int _y)
{
	CPanel *newPanel;

	int counter = 1;
	list<CPanel*>::iterator p;

	//searches the list for a free number
	for(p = m_PanelList.begin(); p != m_PanelList.end(); p++)
	{
		//if a free number was found: continue 
		if(counter != (*p)->GetNumber())
			break;

		counter ++;
	}


	//if the panel is a furnance panel: Add it
	if(_ID == FURNANCE)
	{
		newPanel = new CFurnance(_x, _y);
		newPanel->Init(counter);

		m_PanelList.insert(p, newPanel);
	}
	else if(_ID == CHEST)
	{
		newPanel = new CChest();
		newPanel->Init(counter);

		m_PanelList.insert(p, newPanel);
	}


	return counter;
}



//returns the panel on which was clicked
CPanel* CWorld::GetPanel(View *_view)
{
	int x, y, number = -1;
	list<CPanel*>::iterator p;

	//calculate the chosen block's x and y
	x = Mouse::getPosition().x + (int)(_view->getCenter().x - _view->getSize().x/2);
	y = Mouse::getPosition().y + (int)(_view->getCenter().y - _view->getSize().y/2);
	x = (x - x%100)/100; 
	y = (y -y%100)/100;

	if(m_pBlocks[x][y] != NULL)
	{
		//if the thing is a furnance or a chest and the player clicked on it: get it's number
		if(m_pBlocks[x][y]->getID() == FURNANCE || m_pBlocks[x][y]->getID() == CHEST)
		{
			if(Mouse::isButtonPressed(Mouse::Right))
				number = m_pBlocks[x][y]->GetSpecialID();
		}
	}

	//get the panel of the thing
	for(p = m_PanelList.begin(); p != m_PanelList.end(); p++)
	{
		if(number == (*p)->GetNumber())
			return (*p);
	}
 
	//if the player didn't clicked on a thing: return NULL
	return NULL;
}





void CWorld::FillChestRandomly(int _chestID)
{
	list<CPanel*>::iterator p;
	bool is_filled = false;
	int counter = 0;
	int failCounter = 0;
	int randomNumber = 0;

	//get the panel of the chest
	for(p = m_PanelList.begin(); p != m_PanelList.end(); p++)
	{
		if(_chestID == (*p)->GetNumber())
		{
			//fill the chest
			while(is_filled == false)
			{
				//get a random ID
				randomNumber = rand()%85 + 54;

				//very rare ring has currently the id 200
				if(randomNumber == 138)
					randomNumber = 200;

				CThing *thing = NULL;

				//if thing is an item
				if(randomNumber > PIBREAK && randomNumber < 65)
				{
					thing = new CItem;
					((CItem*)thing)->Init(randomNumber);	
				}
				//if thing is a tool
				else if(randomNumber > ITBREAK && randomNumber < 103)
				{
					thing = new CTool;
					((CTool*)thing)->InitToolRandomly(randomNumber);
				}
				//if thing is equipment
				else if(randomNumber > TEBREAK)
				{
					thing = new CEquipment;
					((CEquipment*)thing)->InitEquipmentRandomly(randomNumber);
				}

				//if the id was valid: create the thing
				if(thing != NULL)
				{
					//insert new item
					SItem newItem;
					newItem.thing = thing;

					//all tools and equipment have the amount 1
					if(randomNumber > ITBREAK || randomNumber == RECIPE)
						newItem.amount = 1;
					else
						newItem.amount = rand()%5 +1;

					newItem.position = -1;

					((CChest*)(*p))->TakeThing(newItem);

					counter ++;
				}
				else
					failCounter++;
				
				//if there are 5 things in the chest: end filling it
				if(counter >= 5)
					is_filled = true;

				//if there were 3 fails while filling the chest: end filling
				if(failCounter >= 7)
					is_filled = true;			
			}
		}		
	}
}





vector<Vector2i> CWorld::GetSpawnPlaces(IntRect _view)
{
	vector<Vector2i> spawnPlaces;
	spawnPlaces.clear();

	int xStart = (int)(_view.left/100) - 5;
	if(xStart < 0)
		xStart = 0;

	int yStart = (int)(_view.top/100)- 5;
	if(yStart < 0)
		yStart = 0;

	int xEnd = (_view.left/100) + _view.width/100 + 5;
	if(xEnd > m_BlocksX)
		xEnd = m_BlocksX;

	int yEnd = (_view.top/100) + _view.height/100 + 5;
	if(yEnd > m_BlocksY)
		yEnd = m_BlocksY;



	for(int y = yStart; y <= yEnd; y++)
	{
		for(int x = xStart; x <= xEnd; x++)
		{
			//if there is no block
			if(m_pBlocks[x][y] == NULL)
			{
				//outside the view?
				if(!IntRect(x*100, y*100, 100, 100).intersects(_view))
				{
					spawnPlaces.push_back(Vector2i(x*100, y*100));
				}
			}
			//if there is a block
			else
			{
				//if the block is passable and is outside the view
				if(m_pBlocks[x][y]->IsPassable() && !IntRect(x*100, y*100, 100, 100).intersects(_view))
				{
					spawnPlaces.push_back(Vector2i(x*100, y*100));
				}
			}
		}
	}

	return spawnPlaces;
}