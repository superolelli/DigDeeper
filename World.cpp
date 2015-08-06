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




void CWorld::Init(int _width, int _height, View* _view, CNpcMachine* _npcs, bool _loaded)
{
	m_pView = _view;
	m_pNpcMachine = _npcs;

	if(!_loaded)
	{
		m_BlocksX = _width;
		m_BlocksY = _height;

		m_NightAlpha = 0;
		m_fNightTimer = 0.0f;
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
	m_lightMachine.Init(_view, this, false);

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
						if(m_pBlocks[x-1][y]->getID() < 8 && m_pBlocks[x-1][y]->getID() > 0)
							possibility[m_pBlocks[x-1][y]->getID()-1] += 50;
					if(m_pBlocks[x][y-1] != NULL && m_pBlocks[x][y-1]->getID() > 0)
						if (m_pBlocks[x][y - 1]->getID() < 8)
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

							if (rand() % 2 == 0)
								GenerateRoom(x, y);
							else
								GenerateCave(x, y);

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




	//set trees
	for (int x = 0; x < m_BlocksX; x++)
	{
		randomNumber = rand() % 20;

		if (randomNumber < 4)
			SetTree(x, 3);
		else if (randomNumber == 4)
		{
			m_pBlocks[x][3] = new CPlaceable;
			m_pBlocks[x][3]->Init(CLOVERP);
			m_pBlocks[x][3]->SetPos(static_cast<float>(x * 100), static_cast<float> (300));
		}
		else if (randomNumber == 5)
		{
			m_pBlocks[x][3] = new CPlaceable;
			m_pBlocks[x][3]->Init(RADISHP);
			m_pBlocks[x][3]->SetPos(static_cast<float>(x * 100), static_cast<float> (300));
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
					int type = rand()%11;

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
					else if (type == 9)
					{
						m_pBlocks[x][y]->Init(ROOMFILL);
						m_pNpcMachine->AddNpc(GOBLIN, x * 100, y * 100, CHESTGOBLIN);
						cout << "added chest goblin" << endl;
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



void CWorld::GenerateCave(int _x, int _y)
{
	//generate the size of the cave
	int xSize = rand() % 9 + 2;
	int ySize = rand() % 3 + 3;

	if (_x + xSize <= m_BlocksX && _y + ySize <= m_BlocksY)
	{
		//build the cave
		for (int y = _y; y < _y + ySize; y++)
		{
			for (int x = _x; x < _x + xSize; x++)
			{

				m_pBlocks[x][y] = new CPlaceable;

				//check if this block is one of the outer blocks
				//check for stalagits
				if (y == _y)
				{
					if (rand() % 3 == 0 && m_pBlocks[x][y-1] != NULL)
					{
						m_pBlocks[x][y]->Init(STALAGTIT);
						m_pBlocks[x][y]->SetSpecialID(rand() % 4);
						m_pBlocks[x][y]->SetPos(static_cast<float>(x * 100), static_cast<float> (y * 100));
					}
					else
						m_pBlocks[x][y]->Init(ROOMFILL);
				}
				else if (x == _x || x == _x + xSize - 1)
				{
					if (rand() % 3 == 0)
					{
						m_pBlocks[x][y]->Init(STONE);
						m_pBlocks[x][y]->SetPos(static_cast<float>(x * 100), static_cast<float> (y * 100));
					}
					else
						m_pBlocks[x][y]->Init(ROOMFILL);
				}
				else if (y == _y + ySize - 1)
				{
					int type = rand() % 6;

					//init the things in the cave
					if (type == 0)
					{
						m_pBlocks[x][y]->Init(MUSHROOMP);
						m_pBlocks[x][y]->SetPos(static_cast<float>(x * 100), static_cast<float> (y * 100));
					}
					else if (type == 1)
					{
						m_pBlocks[x][y]->Init(RUBBISH);
						m_pBlocks[x][y]->SetPos(static_cast<float>(x * 100), static_cast<float> (y * 100));
					}
					else if (type == 2)
					{
						m_pBlocks[x][y]->Init(ROOMFILL);
						m_pNpcMachine->AddNpc(GOBLIN, x*100, y*100, true);				
					}
					else if (type == 3)
					{
						m_pBlocks[x][y]->Init(ROOMFILL);
						m_pNpcMachine->AddNpc(OGRE, x * 100, (y-1) * 100, true);
					}
					else
					{
						m_pBlocks[x][y]->Init(ROOMFILL);
					}

				}
				else
				{
					m_pBlocks[x][y]->Init(ROOMFILL);
				}

			}
		}
	}

}




void CWorld::SetTree(int _x, int _y)
{
	int height = 1;
	bool beehive = false;

	if (m_pBlocks[_x][_y] == NULL)
	{
		//place the first trunk
		m_pBlocks[_x][_y] = new CPlaceable;
		m_pBlocks[_x][_y]->Init(TREETRUNK);
		m_pBlocks[_x][_y]->SetPos(_x * 100, _y * 100);

		bool grow = true;
		while (grow && rand() % 2 == 0)
		{
			//if not out of world
			if (_y - 1 > 0)
			{
				//if there's no block already
				if (m_pBlocks[_x][_y - 1] == NULL)
				{
					//place another trunk
					m_pBlocks[_x][_y - 1] = new CPlaceable;
					m_pBlocks[_x][_y - 1]->Init(TREETRUNK);
					m_pBlocks[_x][_y - 1]->SetPos(_x * 100, (_y - 1) * 100);

					//if theres no beehive at the tree: add one randomly
					if (rand() % 4 == 0 && beehive == false)
					{
						//place a hive left
						if (rand() % 2 == 0 && _x - 1 >= 0)
						{
							if (m_pBlocks[_x - 1][_y - 1] == NULL)
							{
								//place the hive
								m_pBlocks[_x - 1][_y - 1] = new CPlaceable;
								m_pBlocks[_x - 1][_y - 1]->Init(BEEHIVEP);
								m_pBlocks[_x - 1][_y - 1]->SetSpecialID(0);
								m_pBlocks[_x - 1][_y - 1]->SetPos((_x - 1) * 100, (_y - 1) * 100);

								beehive = true;
							}
						}
						//place a hive right
						else if (_x + 1 < m_BlocksX)
						{
							if (m_pBlocks[_x + 1][_y - 1] == NULL)
							{
								//place the hive
								m_pBlocks[_x + 1][_y - 1] = new CPlaceable;
								m_pBlocks[_x + 1][_y - 1]->Init(BEEHIVEP);
								m_pBlocks[_x + 1][_y - 1]->SetSpecialID(1);
								m_pBlocks[_x + 1][_y - 1]->SetPos(((_x + 1) * 100) - 17, (_y - 1) * 100);

								beehive = true;
							}
						}
					}

					height++;
					_y--;
				}
				else
					grow = false;
			}
			else
				grow = false;

			if (height == 3)
				grow = false;
		}


		if (m_pBlocks[_x][_y - 1] == NULL && m_pBlocks[_x][_y]->getID() == TREETRUNK)
		{
			//place the crown
			m_pBlocks[_x][_y - 1] = new CPlaceable;
			m_pBlocks[_x][_y - 1]->Init(TREECROWN);
			m_pBlocks[_x][_y - 1]->SetPos(_x * 100, (_y - 1) * 100);
		}
	}
}



void CWorld::Render()
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
		if(m_NightAlpha < 254)
		{
			if(m_fSecondTimer >= 0.5f)
				m_NightAlpha++;
		}
		else
			m_NightAlpha = 254;
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

	int viewX = m_pView->getCenter().x - m_pView->getSize().x/2;
	int viewY = m_pView->getCenter().y - m_pView->getSize().y/2;
	int viewFirstBlock = viewX - viewX % 100;

	//clear the light machine
	//m_lightMachine.Clear(Color(0, 0, 0, m_NightAlpha));
	m_lightMachine.Clear(Color::Black);


	if (viewY < 1000)
	{
		//add the "sun"
	/*	for (int i = viewFirstBlock - 100; i <= viewFirstBlock + m_pView->getSize().x + 100; i += 100)
		{
			m_lightMachine.AddLightBeam(i, 0, 800, 100, Color(255, 255, 255, m_NightAlpha));
		}
*/
		for (int i = viewFirstBlock - 100; i <= viewFirstBlock + m_pView->getSize().x + 100; i += 100)
		{
			m_lightMachine.AddLightCircle(i, 0, 1000, Color(255, 255, 255, m_NightAlpha));
		}
	}


	//get all the blocks, which are within the view
	int xStart = (int)((viewX)/100)-3;
	if(xStart < 0)
		xStart = 0;

	int yStart = (int)((viewY)/100)-3;
	if(yStart < 0)
		yStart = 0;

	int xEnd = (int)(xStart + m_pView->getSize().x/100) +6;
	if(xEnd > m_BlocksX)
		xEnd = m_BlocksX;

	int yEnd = (int)(yStart + m_pView->getSize().y/100)+6;
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

				int neighbourID = -1;

				//check for overlapping top
				if (y - 1 >= 0)
				{
					if (m_pBlocks[x][y-1] != NULL && m_pBlocks[x][y -1]->GetPriority() > m_pBlocks[x][y]->GetPriority() && m_pBlocks[x][y]->GetPriority() != -1)
					{
						neighbourID = m_pBlocks[x][y - 1]->getID();
						if (neighbourID == COALBLOCK || neighbourID == GOLDBLOCK || neighbourID == IRONBLOCK || neighbourID == ARCANUSBLOCK)
							neighbourID = STONE;
						
						if (neighbourID == TREETRUNK)
						{
							g_pRims->TreeRims[m_pBlocks[x][y - 1]->GetOverlappingID(0)].SetPos(x * 100, y * 100);
							g_pRims->TreeRims[m_pBlocks[x][y - 1]->GetOverlappingID(0)].Render(g_pFramework->GetRenderWindow());
						}
						else
						{
							g_pRims->TopRims[neighbourID - 1][m_pBlocks[x][y - 1]->GetOverlappingID(0)].SetPos(x * 100, y * 100);
							g_pRims->TopRims[neighbourID - 1][m_pBlocks[x][y - 1]->GetOverlappingID(0)].Render(g_pFramework->GetRenderWindow());
						}
					}

				}

				//check for overlapping bottom
				if (y + 1 < m_BlocksY)
				{
					if (m_pBlocks[x][y + 1] != NULL && m_pBlocks[x][y + 1]->GetPriority() > m_pBlocks[x][y]->GetPriority() && m_pBlocks[x][y]->GetPriority() != -1)
					{
						neighbourID = m_pBlocks[x][y + 1]->getID();
						if (neighbourID == COALBLOCK || neighbourID == GOLDBLOCK || neighbourID == IRONBLOCK || neighbourID == ARCANUSBLOCK)
							neighbourID = STONE;

						if (neighbourID != TREETRUNK)
						{
							g_pRims->BottomRims[neighbourID - 1][m_pBlocks[x][y + 1]->GetOverlappingID(1)].SetPos(x * 100, y * 100 + 100 - g_pRims->BottomRims[0][0].GetRect().height);
							g_pRims->BottomRims[neighbourID - 1][m_pBlocks[x][y + 1]->GetOverlappingID(1)].Render(g_pFramework->GetRenderWindow());
						}
					}

				}

				//check for overlapping left
				if (x - 1 >= 0)
				{
					if (m_pBlocks[x - 1][y] != NULL && m_pBlocks[x - 1][y]->GetPriority() > m_pBlocks[x][y]->GetPriority() && m_pBlocks[x][y]->GetPriority() != -1)
					{
						neighbourID = m_pBlocks[x - 1][y]->getID();
						if (neighbourID == COALBLOCK || neighbourID == GOLDBLOCK || neighbourID == IRONBLOCK || neighbourID == ARCANUSBLOCK)
							neighbourID = STONE;

						if (neighbourID != TREETRUNK)
						{
							g_pRims->LeftRims[neighbourID - 1][m_pBlocks[x - 1][y]->GetOverlappingID(2)].SetPos(x * 100, y * 100);
							g_pRims->LeftRims[neighbourID - 1][m_pBlocks[x - 1][y]->GetOverlappingID(2)].Render(g_pFramework->GetRenderWindow());
						}
					}

				}

				//check for overlapping right
				if (x + 1 < m_BlocksX)
				{
					if (m_pBlocks[x + 1][y] != NULL && m_pBlocks[x + 1][y]->GetPriority() > m_pBlocks[x][y]->GetPriority() && m_pBlocks[x][y]->GetPriority() != -1)
					{
						neighbourID = m_pBlocks[x + 1][y]->getID();
						if (neighbourID == COALBLOCK || neighbourID == GOLDBLOCK || neighbourID == IRONBLOCK || neighbourID == ARCANUSBLOCK)
							neighbourID = STONE;

						if (neighbourID != TREETRUNK)
						{
							g_pRims->RightRims[neighbourID - 1][m_pBlocks[x + 1][y]->GetOverlappingID(3)].SetPos(x * 100 + 100 - g_pRims->RightRims[0][0].GetRect().width, y * 100);
							g_pRims->RightRims[neighbourID - 1][m_pBlocks[x + 1][y]->GetOverlappingID(3)].Render(g_pFramework->GetRenderWindow());
						}
					}

				}



				//check various blocks for light or npcs etc.
				if(m_pBlocks[x][y]->getID() == FURNANCE)
					m_lightMachine.AddLightCircle(m_pBlocks[x][y]->GetRect().left + m_pBlocks[x][y]->GetRect().width/2, m_pBlocks[x][y]->GetRect().top + 50, 200, Color(230, 0,0,0));
				else if(m_pBlocks[x][y]->getID() == LANTERNP)
					m_lightMachine.AddLightCircle(m_pBlocks[x][y]->GetRect().left, m_pBlocks[x][y]->GetRect().top, 350, Color(0,0,0,0));	
				else if (m_pBlocks[x][y]->getID() == TORCH)
					m_lightMachine.AddLightCircle(m_pBlocks[x][y]->GetRect().left + m_pBlocks[x][y]->GetRect().width / 2, m_pBlocks[x][y]->GetRect().top + 50, 500, Color(0, 0, 0, 0));
				else if (m_pBlocks[x][y]->getID() == BEEHIVEP)
				{
					if (rand() % 120 == 0)
						m_pNpcMachine->AddNpc(BEE, x * 100 + 50, y * 100 + 50);
				}
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

	int yEnd = yStart +4 + (_player.height/100);
	if(yEnd > m_BlocksY)
		yEnd = m_BlocksY;

	for(int y = yStart; y < yEnd; y++)
	{
		for(int x = xStart; x < xEnd; x++)
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
	if(xEnd >= m_BlocksX)
		xEnd = m_BlocksX-1;

	int yEnd = yStart +4;
	if(yEnd >= m_BlocksY)
		yEnd = m_BlocksY-1;


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
void CWorld::CheckPlaceables(IntRect _playerRect, CPlayer *_player)
{

	IntRect rectP;
	list<CPanel*>::iterator p;

	int xView = m_pView->getCenter().x - m_pView->getSize().x / 2;
	int yView = m_pView->getCenter().y - m_pView->getSize().y / 2;
	

	CheckLittle();

	int xStart = (int)(_playerRect.left/100) -1;
	if(xStart < 0)
		xStart = 0;

	int yStart = (int)(_playerRect.top/100) -1;
	if(yStart < 0)
		yStart = 0;

	int xEnd = (_playerRect.left/100) +1;
	if(xEnd >= m_BlocksX)
		xEnd = m_BlocksX - 1;

	int yEnd = (_playerRect.top/100) +1;
	if(yEnd >= m_BlocksY)
		yEnd = m_BlocksY - 1;



	for(int y = yStart; y <= yEnd; y++)
	{
		for(int x = xStart; x <= xEnd; x++)
		{
			//Checking for the placeables
			if(m_pBlocks[x][y] != NULL)
			{
				rectP = m_pBlocks[x][y]->GetRect();
				rectP.left = (m_pBlocks[x][y]->GetRect().left - (int)xView);
				rectP.top = (m_pBlocks[x][y]->GetRect().top - (int)yView);
		

				if(rectP.contains(Mouse::getPosition()) && Mouse::isButtonPressed(Mouse::Left))
				{
					if(m_pBlocks[x][y]->IsBroken(_player->m_modifications.breaking_speed))
					{
						//set the sound
						if(m_pBlocks[x][y]->getID() == GOLDBLOCK)
						{
							int soundNumber = rand()%3;

							m_sound.setBuffer(g_pSound->m_goldSound[soundNumber]);
							m_sound.play();
						}

						//check if the broken placeable was a tree
						if (m_pBlocks[x][y]->getID() == TREETRUNK)
						{
							bool is_tree = true;
							int oldY = y;
							while (is_tree)
							{
								//check for other treeparts
								if (y - 1 >= 0)
								{
									//if another tree part is above: break it too
									if (m_pBlocks[x][y - 1] != NULL && (m_pBlocks[x][y - 1]->getID() == TREETRUNK || m_pBlocks[x][y - 1]->getID() == TREECROWN))
									{
										AddLittleItem(WOOD, m_pBlocks[x][y - 1]->GetRect().left + 23, m_pBlocks[x][y - 1]->GetRect().top + 20, 2);
										SAFE_DELETE(m_pBlocks[x][y - 1]);
										y--;
									}
									else
										is_tree = false;
								}
								else
									is_tree = false;



								//check for hives left
								if (x - 1 >= 0)
								{
									if (m_pBlocks[x - 1][y] != NULL && m_pBlocks[x - 1][y]->getID() == BEEHIVEP)
									{
										AddLittleItem(BEEHIVE, m_pBlocks[x-1][y]->GetRect().left + 23, m_pBlocks[x-1][y]->GetRect().top + 20);
										SAFE_DELETE(m_pBlocks[x-1][y]);
									}
								}

								//check for hives right
								if (x + 1 < m_BlocksX)
								{
									if (m_pBlocks[x + 1][y] != NULL && m_pBlocks[x + 1][y]->getID() == BEEHIVEP)
									{
										AddLittleItem(BEEHIVE, m_pBlocks[x + 1][y]->GetRect().left + 23, m_pBlocks[x + 1][y]->GetRect().top + 20);
										SAFE_DELETE(m_pBlocks[x + 1][y]);
									}
								}



							}
							y = oldY;
						}


						//if the placeable was rubbish show animation
						if (m_pBlocks[x][y]->getID() == RUBBISH)
						{
							SProjectile projectile;

							//add a projectile
							CSprite *sprite = new CSprite;

							sprite->Load(&g_pTextures->t_rubbishAnimation, 5, 150, 150);
							sprite->SetPos(x*100 -25, y*100 - 50);

							projectile.m_ID = RUBBISHANIMATION;
							projectile.m_Damage = 0;
							projectile.m_fFlown = 0.0f;
							projectile.m_flightLength = 0;
							projectile.m_fromPlayer = true;
							projectile.m_fYVel = 0.0f;
							projectile.m_Sprite = sprite;
							projectile.m_fAnimState = 0;
							g_pProjectiles->NewProjectile(projectile);
						}


						//check if the player could have luck
						bool lucky = false;
						int amount = 1;

						if (m_pBlocks[x][y]->getID() == TREETRUNK || m_pBlocks[x][y]->getID() == TREECROWN)
							amount = 2;

						if(m_pBlocks[x][y]->getID() >=3 && m_pBlocks[x][y]->getID() <= 6)
							lucky = true;
					
						do
						{
							AddLittleItem(m_pBlocks[x][y]->GetLittleID(), m_pBlocks[x][y]->GetRect().left + 23, m_pBlocks[x][y]->GetRect().top + 20, amount);

							//check for luck
							int randomNumber = rand()%100 +1;
							if(randomNumber > _player->m_modifications.luck)
								lucky = false;

						}while(lucky);

						//if a furnance was destroyed: delete the panel
						if(m_pBlocks[x][y]->getID() == FURNANCE || m_pBlocks[x][y]->getID() == CHEST || m_pBlocks[x][y]->getID() == CAULDRON)
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
					//if it was a door: close/open the door
					if(m_pBlocks[x][y]->getID() == DOOR)
						m_pBlocks[x][y]->SetSpecialID(1);

					//it it was a beehouse: give honey
					if (m_pBlocks[x][y]->getID() == BEEHOUSE &&  m_pBlocks[x][y]->IsPlaceableReady())
					{
						AddLittleItem(HONEY, m_pBlocks[x][y]->GetRect().left + 23, m_pBlocks[x][y]->GetRect().top - 20);
					}
				}
			}

			//checking for the second layer walls
			if(m_pWalls[x][y] != NULL)
			{
				rectP = m_pWalls[x][y]->GetRect();
				rectP.left = m_pWalls[x][y]->GetRect().left - (int)xView;
				rectP.top = m_pWalls[x][y]->GetRect().top - (int)yView;
		

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

		if(_playerRect.intersects(i->GetRect()) && !_player->IsInventoryFull())
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
	if (_ID != -1)
	{
		for (int i = 0; i < _amount; i++)
		{
			CLittleItem item;

			//if thing is a placeable
			if (_ID < PIBREAK)
			{
				CPlaceable *thing = new CPlaceable;
				thing->Init(_ID);
				item.Init(thing, _x + (rand() % 50 - 25), _y + (rand() % 20));
			}
			//if thing is an item
			else if (_ID > PIBREAK && _ID < ICBREAK)
			{
				CItem *thing = new CItem;
				thing->Init(_ID);
				item.Init(thing, _x + (rand() % 50 - 25), _y + (rand() % 20));
			}
			else if (_ID > ICBREAK && _ID < CTBREAK)
			{
				CConsumable *thing = new CConsumable;
				thing->InitConsumable(_ID);
				item.Init(thing, _x + (rand() % 50 - 25), _y + (rand() % 20));
			}
			//if thing is a tool
			else if (_ID > CTBREAK && _ID < TEBREAK)
			{
				CTool *thing = new CTool;
				thing->InitTool(_ID);
				item.Init(thing, _x + (rand() % 50 - 25), _y + (rand() % 20));
			}
			//if thing is equipment
			else
			{
				CEquipment *thing = new CEquipment;
				thing->InitEquipment(_ID);
				item.Init(thing, _x + (rand() % 50 - 25), _y + (rand() % 20));
			}

			item.SetVel(Vector2f(0, -350.0f));
			m_LittleItemList.push_back(item);
		}
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
					if (ID == FURNANCE || ID == CHEST || ID == CUPBOARD || ID == LANTERN || ID == TORCH || ID == CAULDRON)
					{
						//if there is a block below
						if(m_pBlocks[x/100][y/100+1] != NULL && m_pBlocks[x/100][y/100+1]->CanBePlacedOn())
						{
							//creates a new block
							m_pBlocks[x/100][y/100] = new CPlaceable;

							//checks for some special placeables
							if(ID == LANTERN)
								m_pBlocks[x/100][y/100]->Init(LANTERNP);
							else
								m_pBlocks[x/100][y/100]->Init(ID);

							if (ID == TORCH)
								m_pBlocks[x / 100][y / 100]->SetSpecialID(0);

							//sets the position
							m_pBlocks[x / 100][y / 100]->SetPos(x, y);
						}
						else
						{
							//torches can be placed on walls too
							if (ID == TORCH )
							{
								if (m_pBlocks[x / 100 - 1][y / 100] != NULL && m_pBlocks[x / 100-1][y / 100]->CanBePlacedOn())
								{
									m_pBlocks[x / 100][y / 100] = new CPlaceable;
									m_pBlocks[x / 100][y / 100]->Init(ID);
									m_pBlocks[x / 100][y / 100]->SetSpecialID(2);
									m_pBlocks[x / 100][y / 100]->SetPos(x, y);
								}
								else if (m_pBlocks[x / 100 + 1][y / 100] != NULL && m_pBlocks[x / 100+1][y / 100]->CanBePlacedOn())
								{
									m_pBlocks[x / 100][y / 100] = new CPlaceable;
									m_pBlocks[x / 100][y / 100]->Init(ID);
									m_pBlocks[x / 100][y / 100]->SetSpecialID(3);
									m_pBlocks[x / 100][y / 100]->SetPos(x, y);
								}
								else if (m_pWalls[x / 100][y / 100] != NULL)
								{
									m_pBlocks[x / 100][y / 100] = new CPlaceable;
									m_pBlocks[x / 100][y / 100]->Init(ID);
									m_pBlocks[x / 100][y / 100]->SetSpecialID(1);
									m_pBlocks[x / 100][y / 100]->SetPos(x, y);
								}
								else
									return false;
							}
							else
								return false;
						}
					}
					//others not
					else
					{
						m_pBlocks[x/100][y/100] = new CPlaceable;
						m_pBlocks[x/100][y/100]->Init(ID);
						m_pBlocks[x/100][y/100]->SetPos(x, y);
					}

					if(ID == FURNANCE || ID == CHEST || ID == CAULDRON)
					{
						m_pBlocks[x/100][y/100]->SetSpecialID(AddPanel(ID, x, y));
					}

					return true;
				}
				else
				{
					if (ID == TORCH && m_pWalls[x / 100][y / 100] != NULL)
					{
						m_pBlocks[x / 100][y / 100] = new CPlaceable;
						m_pBlocks[x / 100][y / 100]->Init(ID);
						m_pBlocks[x / 100][y / 100]->SetSpecialID(1);
						m_pBlocks[x / 100][y / 100]->SetPos(x, y);
					}
					else
						return false;
				}
			}
			else if(y == 0 && x!= 0)
			{
				if(m_pBlocks[x/100 -1][y/100] != NULL || m_pBlocks[x/100 +1][y/100] != NULL || m_pBlocks[x/100][y/100 +1] != NULL)
				{
					if (ID == FURNANCE || ID == CHEST || ID == CUPBOARD || ID == LANTERN || ID == TORCH || ID == CAULDRON)
					{
						//if there is a block below
						if (m_pBlocks[x / 100][y / 100 + 1] != NULL &&  m_pBlocks[x / 100][y / 100 + 1]->CanBePlacedOn())
						{
							m_pBlocks[x / 100][y / 100] = new CPlaceable;
							if (ID == LANTERN)
								m_pBlocks[x / 100][y / 100]->Init(LANTERNP);
							else
								m_pBlocks[x / 100][y / 100]->Init(ID);

							if (ID == TORCH)
								m_pBlocks[x / 100][y / 100]->SetSpecialID(0);

							m_pBlocks[x / 100][y / 100]->SetPos(x, y);
						}
						else
						{
							//torches can be placed on walls too
							if (ID == TORCH)
							{
								if (m_pBlocks[x / 100 - 1][y / 100] != NULL &&  m_pBlocks[x / 100 - 1][y / 100]->CanBePlacedOn())
								{
									m_pBlocks[x / 100][y / 100] = new CPlaceable;
									m_pBlocks[x / 100][y / 100]->Init(ID);
									m_pBlocks[x / 100][y / 100]->SetSpecialID(2);
									m_pBlocks[x / 100][y / 100]->SetPos(x, y);
								}
								else if (m_pBlocks[x / 100 + 1][y / 100] != NULL &&  m_pBlocks[x / 100 + 1][y / 100]->CanBePlacedOn())
								{
									m_pBlocks[x / 100][y / 100] = new CPlaceable;
									m_pBlocks[x / 100][y / 100]->Init(ID);
									m_pBlocks[x / 100][y / 100]->SetSpecialID(3);
									m_pBlocks[x / 100][y / 100]->SetPos(x, y);
								}
								else if (m_pWalls[x / 100][y / 100] != NULL)
								{
									m_pBlocks[x / 100][y / 100] = new CPlaceable;
									m_pBlocks[x / 100][y / 100]->Init(ID);
									m_pBlocks[x / 100][y / 100]->SetSpecialID(1);
									m_pBlocks[x / 100][y / 100]->SetPos(x, y);
								}
								else
									return false;
							}
						}
					}
					//others not
					else
					{
						m_pBlocks[x/100][y/100] = new CPlaceable;
						m_pBlocks[x/100][y/100]->Init(ID);
						m_pBlocks[x/100][y/100]->SetPos(x, y);
					}

					if (ID == FURNANCE || ID == CHEST || ID == CAULDRON)
					{
						m_pBlocks[x/100][y/100]->SetSpecialID(AddPanel(ID, x, y));
					}

					return true;
				}
				else
				{
					if (ID == TORCH && m_pWalls[x / 100][y / 100] != NULL)
					{
						m_pBlocks[x / 100][y / 100] = new CPlaceable;
						m_pBlocks[x / 100][y / 100]->Init(ID);
						m_pBlocks[x / 100][y / 100]->SetSpecialID(1);
						m_pBlocks[x / 100][y / 100]->SetPos(x, y);
					}
					else
						return false;
				}
			}
			else if(y != 0 && x == 0)
			{
				if(m_pBlocks[x/100 +1][y/100] != NULL || m_pBlocks[x/100][y/100 -1] != NULL || m_pBlocks[x/100][y/100 +1] != NULL)
				{
					//some things must be placed on top of another
					if (ID == FURNANCE || ID == CHEST || ID == CUPBOARD || ID == LANTERN || ID == TORCH || ID == CAULDRON)
					{
						//if there is a block below
						if (m_pBlocks[x / 100][y / 100 + 1] != NULL && m_pBlocks[x / 100][y / 100 + 1]->CanBePlacedOn())
						{
							m_pBlocks[x / 100][y / 100] = new CPlaceable;
							if (ID == LANTERN)
								m_pBlocks[x / 100][y / 100]->Init(LANTERNP);
							else
								m_pBlocks[x / 100][y / 100]->Init(ID);

							if (ID == TORCH)
								m_pBlocks[x / 100][y / 100]->SetSpecialID(0);

							m_pBlocks[x / 100][y / 100]->SetPos(x, y);
						}
						else
						{
							//torches can be placed on walls too
							if (ID == TORCH)
							{
								if (m_pBlocks[x / 100 + 1][y / 100] != NULL &&  m_pBlocks[x / 100 + 1][y / 100]->CanBePlacedOn())
								{
									m_pBlocks[x / 100][y / 100] = new CPlaceable;
									m_pBlocks[x / 100][y / 100]->Init(ID);
									m_pBlocks[x / 100][y / 100]->SetSpecialID(3);
									m_pBlocks[x / 100][y / 100]->SetPos(x, y);
								}
								else if (m_pWalls[x / 100][y / 100] != NULL)
								{
									m_pBlocks[x / 100][y / 100] = new CPlaceable;
									m_pBlocks[x / 100][y / 100]->Init(ID);
									m_pBlocks[x / 100][y / 100]->SetSpecialID(1);
									m_pBlocks[x / 100][y / 100]->SetPos(x, y);
								}
								else
									return false;
							}
						}
					}
					//others not
					else
					{
						m_pBlocks[x/100][y/100] = new CPlaceable;
						m_pBlocks[x/100][y/100]->Init(ID);
						m_pBlocks[x/100][y/100]->SetPos(x, y);
					}


					if (ID == FURNANCE || ID == CHEST || ID == CAULDRON)
					{
						m_pBlocks[x/100][y/100]->SetSpecialID(AddPanel(ID, x, y));
					}

					return true;
				}
				else
				{
					if (ID == TORCH && m_pWalls[x / 100][y / 100] != NULL)
					{
						m_pBlocks[x / 100][y / 100] = new CPlaceable;
						m_pBlocks[x / 100][y / 100]->Init(ID);
						m_pBlocks[x / 100][y / 100]->SetSpecialID(1);
						m_pBlocks[x / 100][y / 100]->SetPos(x, y);
					}
					else
						return false;
				}
			}
			else
			{
				if(m_pBlocks[x/100 +1][y/100] != NULL || m_pBlocks[x/100][y/100 +1] != NULL)
				{
					//some things must be placed on top of another
					if (ID == FURNANCE || ID == CHEST || ID == CUPBOARD || ID == LANTERN || ID == TORCH || ID == CAULDRON)
					{
						//if there is a block below
						if (m_pBlocks[x / 100][y / 100 + 1] != NULL &&  m_pBlocks[x / 100][y / 100 + 1]->CanBePlacedOn())
						{
							m_pBlocks[x / 100][y / 100] = new CPlaceable;
							if (ID == LANTERN)
								m_pBlocks[x / 100][y / 100]->Init(LANTERNP);
							else
								m_pBlocks[x / 100][y / 100]->Init(ID);

							if (ID == TORCH)
								m_pBlocks[x / 100][y / 100]->SetSpecialID(0);

							m_pBlocks[x / 100][y / 100]->SetPos(x, y);
						}
						else
						{
							//torches can be placed on walls too
							if (ID == TORCH)
							{
								if (m_pBlocks[x / 100 + 1][y / 100] != NULL &&  m_pBlocks[x / 100 + 1][y / 100]->CanBePlacedOn())
								{
									m_pBlocks[x / 100][y / 100] = new CPlaceable;
									m_pBlocks[x / 100][y / 100]->Init(ID);
									m_pBlocks[x / 100][y / 100]->SetSpecialID(3);
									m_pBlocks[x / 100][y / 100]->SetPos(x, y);
								}
								else if (m_pWalls[x / 100][y / 100] != NULL)
								{
									m_pBlocks[x / 100][y / 100] = new CPlaceable;
									m_pBlocks[x / 100][y / 100]->Init(ID);
									m_pBlocks[x / 100][y / 100]->SetSpecialID(1);
									m_pBlocks[x / 100][y / 100]->SetPos(x, y);
								}
								else
									return false;
							}
						}
					}
					//others not
					else
					{
						m_pBlocks[x/100][y/100] = new CPlaceable;
						m_pBlocks[x/100][y/100]->Init(ID);
						m_pBlocks[x/100][y/100]->SetPos(x, y);
					}


					if (ID == FURNANCE || ID == CHEST || ID == CAULDRON)
					{
						m_pBlocks[x/100][y/100]->SetSpecialID(AddPanel(ID, x, y));
					}

					return true;
				}
				else
				{
					if (ID == TORCH && m_pWalls[x / 100][y / 100] != NULL)
					{
						m_pBlocks[x / 100][y / 100] = new CPlaceable;
						m_pBlocks[x / 100][y / 100]->Init(ID);
						m_pBlocks[x / 100][y / 100]->SetSpecialID(1);
						m_pBlocks[x / 100][y / 100]->SetPos(x, y);
					}
					else
						return false;
				}
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
	else if (_ID == CAULDRON)
	{
		newPanel = new CCauldron();
		newPanel->Init(counter);

		m_PanelList.insert(p, newPanel);
	}
	else if (_ID == COOKINGBOOK)
	{
		newPanel = new CCookingBook();
		newPanel->Init(counter);

		m_PanelList.insert(p, newPanel);
	}


	return counter;
}



//returns the panel on which was clicked
CPanel* CWorld::GetPanel(int _number)
{
	int x, y = -1;
	list<CPanel*>::iterator p;

	//calculate the chosen block's x and y
	x = Mouse::getPosition().x + (int)(m_pView->getCenter().x - m_pView->getSize().x/2);
	y = Mouse::getPosition().y + (int)(m_pView->getCenter().y - m_pView->getSize().y/2);
	x = (x - x%100)/100; 
	y = (y -y%100)/100;

	if(m_pBlocks[x][y] != NULL && _number == -1)
	{
		//if the thing is a furnance or a chest and the player clicked on it: get it's number
		if(m_pBlocks[x][y]->getID() == FURNANCE || m_pBlocks[x][y]->getID() == CHEST || m_pBlocks[x][y]->getID() == CAULDRON)
		{
			if(Mouse::isButtonPressed(Mouse::Right))
				_number = m_pBlocks[x][y]->GetSpecialID();
		}
	}

	//get the panel of the thing
	for(p = m_PanelList.begin(); p != m_PanelList.end(); p++)
	{
		if(_number == (*p)->GetNumber())
			return (*p);
	}
 
	//if the player didn't clicked on a thing: return NULL
	return NULL;
}




void CWorld::DeletePanel(int _number)
{
	list<CPanel*>::iterator p;

	//get the panel of the chest
	for (p = m_PanelList.begin(); p != m_PanelList.end(); p++)
	{
		if (_number == (*p)->GetNumber())
		{
			(*p)->Quit();
			m_PanelList.erase(p);
			return;
		}
	}

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
				randomNumber = rand()%84 + 56;

				//very rare ring has currently the id 200
				if(randomNumber == 139)
					randomNumber = 200;

				CThing *thing = NULL;

				//if thing is an item
				if(randomNumber > PIBREAK && randomNumber < 71)
				{
					thing = new CItem;
					((CItem*)thing)->Init(randomNumber);	

					if (thing->getID() == COOKINGBOOK)
					{
						((CItem*)thing)->SetSpecialID(AddPanel(COOKINGBOOK, 0, 0));
					}
				}
				//if thing is a consumable
				else if (randomNumber >ICBREAK && randomNumber < 89)
				{
					thing = new CConsumable;
					((CConsumable*)thing)->InitConsumable(randomNumber);
				}
				//if thing is a tool
				else if(randomNumber > CTBREAK && randomNumber < 106)
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
					if(randomNumber > CTBREAK || randomNumber == RECIPE || randomNumber == COOKINGBOOK)
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





vector<Vector2i> CWorld::GetSpawnPlaces()
{
	vector<Vector2i> spawnPlaces;
	spawnPlaces.clear();

	IntRect viewRect;
	viewRect.left = m_pView->getCenter().x - m_pView->getSize().x / 2;
	viewRect.top = m_pView->getCenter().y - m_pView->getSize().y / 2;
	viewRect.width = m_pView->getSize().x;
	viewRect.height = m_pView->getSize().y;

	int xStart = (int)(viewRect.left/100) - 5;
	if(xStart < 0)
		xStart = 0;

	int yStart = (int)(viewRect.top/100)- 5;
	if(yStart < 0)
		yStart = 0;

	int xEnd = (viewRect.left/100) + viewRect.width/100 + 5;
	if(xEnd >= m_BlocksX)
		xEnd = m_BlocksX - 1;

	int yEnd = (viewRect.top/100) + viewRect.height/100 + 5;
	if(yEnd >= m_BlocksY)
		yEnd = m_BlocksY - 1;



	for(int y = yStart; y <= yEnd; y++)
	{
		for(int x = xStart; x <= xEnd; x++)
		{
			//if there is no block
			if(m_pBlocks[x][y] == NULL)
			{
				//outside the view?
				if(!IntRect(x*100, y*100, 100, 100).intersects(viewRect))
				{
					spawnPlaces.push_back(Vector2i(x*100, y*100));
				}
			}
			//if there is a block
			else
			{
				//if the block is passable and is outside the view
				if(m_pBlocks[x][y]->IsPassable() && !IntRect(x*100, y*100, 100, 100).intersects(viewRect))
				{
					spawnPlaces.push_back(Vector2i(x*100, y*100));
				}
			}
		}
	}

	return spawnPlaces;
}




vector < vector <SWorldPlace> > CWorld::GetWorldMatrix(bool _big)
{
	IntRect viewRect;
	viewRect.left = m_pView->getCenter().x - m_pView->getSize().x / 2;
	viewRect.top = m_pView->getCenter().y - m_pView->getSize().y / 2;
	viewRect.width = m_pView->getSize().x;
	viewRect.height = m_pView->getSize().y;

	vector< vector <SWorldPlace> > worldMatrix;
	int xMatrix = 0;
	int yMatrix = 0;

	//get the blocks in the view
	int xStart = (int)(viewRect.left / 100) - 2;
	if (xStart < 0)
		xStart = 0;

	int yStart = (int)(viewRect.top / 100) - 2;
	if (yStart < 0)
		yStart = 0;

	int xEnd = (viewRect.left / 100) + viewRect.width / 100 + 2;
	if (xEnd >= m_BlocksX)
		xEnd = m_BlocksX - 1;

	int yEnd = (viewRect.top / 100) + viewRect.height / 100 + 2;
	if (yEnd >= m_BlocksY)
		yEnd = m_BlocksY - 1;

	if (_big)
	{
		//resize the matrix
		worldMatrix.resize((xEnd + 1)/2);
		for (int i = 0; i < (xEnd + 1)/2; i++)
			worldMatrix[i].resize((yEnd + 1)/2);
	}
	else
	{
		//resize the matrix
		worldMatrix.resize(xEnd + 1);
		for (int i = 0; i < xEnd + 1; i++)
			worldMatrix[i].resize(yEnd + 1);
	}

	//for big npcs
	if (_big)
	{
		int x = xStart;
		int y = yStart;

		for (xMatrix = 0; xMatrix < worldMatrix.size(); xMatrix++)
		{
			for (yMatrix = 0; yMatrix < worldMatrix[0].size(); yMatrix++)
			{
				worldMatrix[xMatrix][yMatrix].xPos = x * 100;
				worldMatrix[xMatrix][yMatrix].yPos = y * 100;
				worldMatrix[xMatrix][yMatrix].matrixXPos = xMatrix;
				worldMatrix[xMatrix][yMatrix].matrixYPos = yMatrix;
				worldMatrix[xMatrix][yMatrix].parentX = 0;
				worldMatrix[xMatrix][yMatrix].parentY = 0;
				worldMatrix[xMatrix][yMatrix].pathValue = 0;
				worldMatrix[xMatrix][yMatrix].cost = 0;
				worldMatrix[xMatrix][yMatrix].passable = true;

				for (int a = 0; a < 4; a++)
				{
					//if there is no block or the block is passable: add passable worldPlace
					if (!(m_pBlocks[x][y] == NULL || m_pBlocks[x][y]->IsPassable()))
						worldMatrix[xMatrix][yMatrix].passable = false;

					if (a == 0)
						y++;
					else if (a == 1)
						x++;
					else if (a==2)
						y--;
				}

				y += 2;
				x--;
			}

			x += 2;
			y = yStart;
		}
	}
	else
	{
		for (int y = yStart; y <= yEnd; y++)
		{
			for (int x = xStart; x <= xEnd; x++)
			{
				worldMatrix[xMatrix][yMatrix].xPos = x * 100;
				worldMatrix[xMatrix][yMatrix].yPos = y * 100;
				worldMatrix[xMatrix][yMatrix].matrixXPos = xMatrix;
				worldMatrix[xMatrix][yMatrix].matrixYPos = yMatrix;
				worldMatrix[xMatrix][yMatrix].parentX = 0;
				worldMatrix[xMatrix][yMatrix].parentY = 0;
				worldMatrix[xMatrix][yMatrix].pathValue = 0;
				worldMatrix[xMatrix][yMatrix].cost = 0;

				//if there is no block or the block is passable: add passable worldPlace
				if (m_pBlocks[x][y] == NULL || m_pBlocks[x][y]->IsPassable())
					worldMatrix[xMatrix][yMatrix].passable = true;
				else
					worldMatrix[xMatrix][yMatrix].passable = false;

				xMatrix++;
			}

			xMatrix = 0;
			yMatrix++;
		}
	}

	return worldMatrix;
}





bool CWorld::CheckCanJump(IntRect _living, bool _left)
{
	int x = _living.left / 100;
	int y = _living.top / 100;

	//if the living thing wants to jump to the left side
	if (_left)
	{
		//end of world?
		if (y - 1 >= 0 && x - 1 >= 0)
		{
			//is there space to jump?
			if ((m_pBlocks[x][y - 1] == NULL || m_pBlocks[x][y - 1]->IsPassable()) && (m_pBlocks[x - 1][y - 1] == NULL || m_pBlocks[x - 1][y - 1]->IsPassable()))
			{
				cout << "Can jump: true" << endl;
				return true;
			}
		}
	}
	//if the living thing wants to jump to the right side
	else
	{
		//end of world?
		if (y - 1 >= 0 && x + 1 <= m_BlocksX)
		{
			//is there space to jump?
			if ((m_pBlocks[x][y - 1] == NULL || m_pBlocks[x][y - 1]->IsPassable()) && (m_pBlocks[x + 1][y - 1] == NULL || m_pBlocks[x + 1][y - 1]->IsPassable()))
			{
				cout << "Can jump: true" << endl;
				return true;
			}
		}
	}

	cout << "Can jump: false" << endl;
	return false;
}




//checks for barriers in x-direction
bool CWorld::CheckForBarrier(IntRect _living, bool _left)
{
	int x = _living.left / 100;
	int y = _living.top / 100;

	if (_living.height > 120)
		y++;

	if (_left)
	{
		if (x - 1 >= 0 && y < m_BlocksY)
		{
			if (m_pBlocks[x - 1][y] == NULL || m_pBlocks[x - 1][y]->IsPassable())
			{
				cout << "Is barrier: false" << endl;
				return false;
			}
		}
	}
	else
	{
		if (x + 1 < m_BlocksX && y < m_BlocksY)
		{
			if (m_pBlocks[x + 1][y] == NULL || m_pBlocks[x + 1][y]->IsPassable())
			{
				cout << "Is barrier: false" << endl;
				return false;
			}
		}
	}

	cout << "Is barrier: true" << endl;
	return true;
}





bool CWorld::isBlockPassable(int _x, int _y)
{
	if (_x >= 0 && _y >= 0 && _x < m_BlocksX && _y < m_BlocksY)
	{
		if (m_pBlocks[_x][_y] != NULL && !m_pBlocks[_x][_y]->IsPassable())
			return false;
		else
			return true;
	}

	return true;
}





void CWorld::DoAlchemy(int _level)
{
	
	int newID = 0;

	//set the block values
	int blockValues[8];
	blockValues[DIRT - 1] = 1;
	blockValues[STONE - 1] = 2;
	blockValues[COALBLOCK - 1] = 2;
	blockValues[IRONBLOCK - 1] = 3;
	blockValues[GOLDBLOCK - 1] = 3;
	blockValues[ARCANUSBLOCK - 1] = 4;
	blockValues[MARBLE - 1] = 2;
	blockValues[WOOD - 1] = 2;


	//get the mouse position
	int x = Mouse::getPosition().x + (m_pView->getCenter().x - m_pView->getSize().x/2);
	int y = Mouse::getPosition().y + (m_pView->getCenter().y - m_pView->getSize().y/2);

	//get the position in the world matrix
	x /= 100;
	y /= 100;

	if (m_pBlocks[x][y] != NULL && m_pBlocks[x][y]->getID() < 9)
	{
		int newValue = rand() % 100 + 1;

		//calculate the new block value
		if (newValue <= 100 * ((float)_level / 100.0f))
		{
			newValue = blockValues[m_pBlocks[x][y]->getID() - 1] + 1;
			if (newValue > 4)
				newValue = 4;
		}
		else if (newValue >= 95)
		{
			newValue = blockValues[m_pBlocks[x][y]->getID() - 1] - 1;
			if (newValue < 1)
				newValue = 1;
		}
		else
			newValue = blockValues[m_pBlocks[x][y]->getID() - 1];

		//get a new block id
		switch (newValue)
		{
		case(1) :
		{
			newID = DIRT;
		}break;

		case(2) :
		{
			newID = rand() % 4;

			if (newID == 0)
				newID = STONE;
			else if (newID == 1)
				newID = COALBLOCK;
			else if (newID == 2)
				newID = MARBLE;
			else if (newID == 3)
				newID = WOOD;
		}break;

		case(3) :
		{
			newID = rand() % 2;

			if (newID == 0)
				newID = IRONBLOCK;
			else
				newID = GOLDBLOCK;
		}break;

		case(4) :
		{
			newID = ARCANUSBLOCK;
		}break;
		}

		//init the new block
		SAFE_DELETE(m_pBlocks[x][y]);
		m_pBlocks[x][y] = new CPlaceable;
		m_pBlocks[x][y]->Init(newID);
		m_pBlocks[x][y]->SetPos(x * 100, y * 100);
	}

		//show alchemy animation
		SProjectile projectile;

		//add a projectile
		CSprite *sprite = new CSprite;

		sprite->Load(&g_pTextures->t_alchemy, 5, 100, 100);
		sprite->SetPos(x*100, y*100);

		projectile.m_ID = ALCHEMYANIMATION;
		projectile.m_Damage = 0;
		projectile.m_fFlown = 0.0f;
		projectile.m_flightLength = 0;
		projectile.m_fromPlayer = true;
		projectile.m_fYVel = 0.0f;
		projectile.m_Sprite = sprite;
		projectile.m_fAnimState = 0;
		g_pProjectiles->NewProjectile(projectile);
	
}




void CWorld::DeleteBlock(int _x, int _y)
{
	list<CPanel*>::iterator p;

	if (_x >= 0 && _y >= 0 && _x < m_BlocksX && _y < m_BlocksY)
	{
		if (m_pBlocks[_x][_y] != NULL)
		{
			AddLittleItem(m_pBlocks[_x][_y]->GetLittleID(), m_pBlocks[_x][_y]->GetRect().left + 23, m_pBlocks[_x][_y]->GetRect().top + 20);

			//if a furnance or else was destroyed: delete the panel
			if (m_pBlocks[_x][_y]->getID() == FURNANCE || m_pBlocks[_x][_y]->getID() == CHEST || m_pBlocks[_x][_y]->getID() == CAULDRON)
			{
				vector<SItem> droppedItems;

				//seek for the panel
				for (p = m_PanelList.begin(); p != m_PanelList.end(); p++)
				{
					//if found: delete it
					if (m_pBlocks[_x][_y]->GetSpecialID() == (*p)->GetNumber())
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
					for (int amount = 0; amount < s.amount; amount++)
					{

						if (amount > 0)
						{
							AddLittleItem(s.thing->getID(), m_pBlocks[_x][_y]->GetRect().left + 23, m_pBlocks[_x][_y]->GetRect().top - 20);
						}
						else
						{
							CLittleItem item;
							item.Init(s.thing, m_pBlocks[_x][_y]->GetRect().left + 23 + (rand() % 50 - 25), m_pBlocks[_x][_y]->GetRect().top - 20 + (rand() % 50 - 25));
							item.SetVel(Vector2f(0, -150.0f));
							m_LittleItemList.push_back(item);
						}
					}
				}
			}

			SAFE_DELETE(m_pBlocks[_x][_y]);
		}
	}
}