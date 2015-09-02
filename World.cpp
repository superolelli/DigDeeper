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




void CWorld::Init(int _width, int _height, View* _view, CNpcMachine* _npcs, bool _fastLight, bool _loaded)
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
	m_lightMachine.Init(_view, this, _fastLight);

	m_WorldHeight = m_BlocksY *100;
	m_WorldWidth = m_BlocksX *100;

	m_fast_sun = _fastLight;
}




//void CWorld::GenerateWorld()
//{
//	int possibility[8];
//
//	bool finalRoom = false;
//	int randomNumber;
//	int possibilitySum = 0;
//	srand((int)time(0));
//
//
//	//generates the blocks
//	for (int y = 4; y < m_BlocksY - 1; y++)
//	{
//		for (int x = 0; x < m_BlocksX; x++)
//		{
//			if (m_pBlocks[x][y] == NULL)
//			{
//				//check for final room
//				if (finalRoom == false && y >= m_BlocksY - 7)
//				{
//					if (rand() % 10 == 0 || x >= m_BlocksX - 8)
//					{
//						GenerateFinalRoom(x, y);
//						finalRoom = true;
//						x--;
//						continue;
//					}
//				}
//
//
//				//set the start possibilities
//				possibility[0] = 84;            //dirt
//				possibility[1] = 10;            //stone
//
//				if (y > 7)
//					possibility[2] = 3;            //coal
//				else
//					possibility[2] = 0;
//
//				if (y > 10)
//					possibility[3] = 2;            //iron
//				else
//					possibility[3] = 0;
//
//				if (y > 15)
//					possibility[4] = 1;            //gold
//				else
//					possibility[4] = 0;
//
//				if (y > 20)
//					possibility[5] = 1;              //arcanus
//				else
//					possibility[5] = 0;
//
//				if (y > 4)
//					possibility[6] = 5;             //marble
//				else
//					possibility[6] = 0;
//
//				if (y > 7)
//					possibility[7] = 1;             //room
//				else
//					possibility[7] = 0;
//
//
//				//if a near placeable is a specific type: greater chance, that this placeable will be the same type
//				if (y > 4 && x > 0)
//				{
//					if (m_pBlocks[x - 1][y] != NULL)
//						if (m_pBlocks[x - 1][y]->getID() < 8 && m_pBlocks[x - 1][y]->getID() > 0)
//							possibility[m_pBlocks[x - 1][y]->getID() - 1] += 50;
//					if (m_pBlocks[x][y - 1] != NULL && m_pBlocks[x][y - 1]->getID() > 0)
//						if (m_pBlocks[x][y - 1]->getID() < 8)
//							possibility[m_pBlocks[x][y - 1]->getID() - 1] += 50;
//				}
//
//
//
//				//Create new Placeable
//				m_pBlocks[x][y] = new CPlaceable;
//
//				//the first layer is a dirt layer
//				if (y != 4)
//				{
//					//calculate the sum
//					possibilitySum = 0;
//					for (int i = 0; i < 8; i++)
//						possibilitySum += possibility[i];
//
//					//generate a random number between 1 and 100
//					randomNumber = rand() % possibilitySum + 1;
//
//					//decide which placeable is going to be set
//					if (randomNumber <= possibility[0])
//						m_pBlocks[x][y]->Init(DIRT);
//					else if (randomNumber <= possibility[1] + possibility[0])
//						m_pBlocks[x][y]->Init(STONE);
//					else if (randomNumber <= possibility[0] + possibility[1] + possibility[2])
//						m_pBlocks[x][y]->Init(COALBLOCK);
//					else if (randomNumber <= possibility[0] + possibility[1] + possibility[2] + possibility[3])
//						m_pBlocks[x][y]->Init(IRONBLOCK);
//					else if (randomNumber <= possibility[0] + possibility[1] + possibility[2] + possibility[3] + possibility[4])
//						m_pBlocks[x][y]->Init(GOLDBLOCK);
//					else if (randomNumber <= possibility[0] + possibility[1] + possibility[2] + possibility[3] + possibility[4] + possibility[5])
//						m_pBlocks[x][y]->Init(ARCANUSBLOCK);
//					else if (randomNumber <= possibility[0] + possibility[1] + possibility[2] + possibility[3] + possibility[4] + possibility[5] + possibility[6])
//						m_pBlocks[x][y]->Init(MARBLE);
//					else
//					{
//						SAFE_DELETE(m_pBlocks[x][y]);
//
//						if (rand() % 2 == 0)
//							GenerateRoom(x, y);
//						else
//							GenerateCave(x, y);
//
//						x--;
//						continue;
//					}
//
//				}
//				else
//					m_pBlocks[x][y]->Init(DIRT);
//
//
//				//set position
//				m_pBlocks[x][y]->SetPos(static_cast<float>(x * 100), static_cast<float> (y * 100));
//			}
//			else
//			{
//				if (m_pBlocks[x][y]->getID() == ROOMFILL)
//					SAFE_DELETE(m_pBlocks[x][y]);
//			}
//		}
//	}
//
//
//	//set trees and bedrock
//	for (int x = 0; x < m_BlocksX; x++)
//	{
//		//set bedrock
//		m_pBlocks[x][m_BlocksY - 1] = new CPlaceable;
//		m_pBlocks[x][m_BlocksY - 1]->Init(BEDROCK);
//		m_pBlocks[x][m_BlocksY - 1]->SetPos(static_cast<float>(x * 100), static_cast<float> ((m_BlocksY - 1) * 100));
//
//		//set trees
//		randomNumber = rand() % 20;
//
//		if (randomNumber < 4)
//			SetTree(x, 3);
//		else if (randomNumber == 4)
//		{
//			m_pBlocks[x][3] = new CPlaceable;
//			m_pBlocks[x][3]->Init(CLOVERP);
//			m_pBlocks[x][3]->SetPos(static_cast<float>(x * 100), static_cast<float> (300));
//		}
//		else if (randomNumber == 5)
//		{
//			m_pBlocks[x][3] = new CPlaceable;
//			m_pBlocks[x][3]->Init(RADISHP);
//			m_pBlocks[x][3]->SetPos(static_cast<float>(x * 100), static_cast<float> (300));
//		}
//	}
//}


//generates a random world
void CWorld::GenerateWorld()
{
	GenerateTopLayer();
	GenerateBottomLayer(GenerateMidLayer());
}
					



void CWorld::GenerateTopLayer()
{
	int possibility[10];

	int randomNumber;
	int possibilitySum = 0;
	srand((int)time(0));


	//generates the blocks
	for (int y = 4; y < m_BlocksY/2; y++)
	{
		for (int x = 0; x < m_BlocksX; x++)
		{
			if (m_pBlocks[x][y] == NULL)
			{
				//set the start possibilities
				possibility[0] = 84;            //dirt
				possibility[1] = 10;            //stone

				if (y > 7)
					possibility[2] = 3;            //coal
				else
					possibility[2] = 0;

				if (y > 10)
					possibility[3] = 2;            //iron
				else
					possibility[3] = 0;

				if (y > 15)
					possibility[4] = 1;            //gold
				else
					possibility[4] = 0;

				if (y > 20)
					possibility[5] = 1;              //arcanus
				else
					possibility[5] = 0;

				if (y > 4)
					possibility[6] = 5;             //marble
				else
					possibility[6] = 0;

				if (y > 7)
					possibility[7] = 3;            //sulfur
				else
					possibility[7] = 0;

				if (y > 7)
					possibility[8] = 3;            //salpeter
				else
					possibility[8] = 0;

				if (y > 7)
					possibility[9] = 1;             //room
				else
					possibility[9] = 0;



				//if a near placeable is a specific type: greater chance, that this placeable will be the same type
				if (y > 4 && x > 0)
				{
					if (m_pBlocks[x - 1][y] != NULL)
						if (m_pBlocks[x - 1][y]->getID() < 10 && m_pBlocks[x - 1][y]->getID() > 0)
							possibility[m_pBlocks[x - 1][y]->getID() - 1] += 50;
					if (m_pBlocks[x][y - 1] != NULL && m_pBlocks[x][y - 1]->getID() > 0)
						if (m_pBlocks[x][y - 1]->getID() < 10)
							possibility[m_pBlocks[x][y - 1]->getID() - 1] += 50;
				}



				//Create new Placeable
				m_pBlocks[x][y] = new CPlaceable;

				//the first layer is a dirt layer
				if (y != 4)
				{
					//calculate the sum
					possibilitySum = 0;
					for (int i = 0; i < 10; i++)
						possibilitySum += possibility[i];

					//generate a random number between 1 and 100
					randomNumber = rand() % possibilitySum + 1;

					//decide which placeable is going to be set
					if (randomNumber <= possibility[0])
						m_pBlocks[x][y]->Init(DIRT);
					else if (randomNumber <= possibility[1] + possibility[0])
						m_pBlocks[x][y]->Init(STONE);
					else if (randomNumber <= possibility[0] + possibility[1] + possibility[2])
						m_pBlocks[x][y]->Init(COALBLOCK);
					else if (randomNumber <= possibility[0] + possibility[1] + possibility[2] + possibility[3])
						m_pBlocks[x][y]->Init(IRONBLOCK);
					else if (randomNumber <= possibility[0] + possibility[1] + possibility[2] + possibility[3] + possibility[4])
						m_pBlocks[x][y]->Init(GOLDBLOCK);
					else if (randomNumber <= possibility[0] + possibility[1] + possibility[2] + possibility[3] + possibility[4] + possibility[5])
						m_pBlocks[x][y]->Init(ARCANUSBLOCK);
					else if (randomNumber <= possibility[0] + possibility[1] + possibility[2] + possibility[3] + possibility[4] + possibility[5] + possibility[6])
						m_pBlocks[x][y]->Init(MARBLE);
					else if (randomNumber <= possibility[0] + possibility[1] + possibility[2] + possibility[3] + possibility[4] + possibility[5] + possibility[6] + possibility[7])
						m_pBlocks[x][y]->Init(SULFURBLOCK);
					else if (randomNumber <= possibility[0] + possibility[1] + possibility[2] + possibility[3] + possibility[4] + possibility[5] + possibility[6] + possibility[7] + possibility[8])
						m_pBlocks[x][y]->Init(SALPETERBLOCK);
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
				m_pBlocks[x][y]->SetPos(static_cast<float>(x * 100), static_cast<float> (y * 100));
			}
			else
			{
				if (m_pBlocks[x][y]->getID() == ROOMFILL)
					SAFE_DELETE(m_pBlocks[x][y]);
			}
		}
	}


	//set trees
	for (int x = 0; x < m_BlocksX; x++)
	{
		//set trees
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


list<SRoom> CWorld::GenerateMidLayer()
{
	list<SRoom> roomlist;
	list<SRoom>::iterator i;

	Vector2i roomSize;

	//generate outer rooms
	for (int y = m_BlocksY/2; y < m_BlocksY/2 + 6; y++)
	{
		for (int x = 0; x < m_BlocksX; x++)
		{
			if (m_pBlocks[x][y] == NULL)
			{
				if (rand() % 10 == 0 && y == m_BlocksY/2 + 5)
				{
					roomSize = GenerateOuterRoom(x, y);

					if (roomSize.x != 0 && roomSize.y != 0)
					{
						SRoom room;
						room.x = x;
						room.y = y;
						room.width = roomSize.x;
						room.height = roomSize.y;
						room.connectionDown = false;
						room.connectionLeft = false;
						room.connectionRight = false;
						room.connectionUp = false;

						roomlist.push_back(room);
					}
				}

			}
			else
			{
				if (m_pBlocks[x][y]->getID() == ROOMFILL)
					SAFE_DELETE(m_pBlocks[x][y]);
			}
		}
	}




	//generate goblin town
	bool end = false;
	int x = 0 + rand()%5;
	int y = m_BlocksY / 2 + 6 + rand()%3;
	int yAdd, xAdd;
	int lowestY = 0;
	int lastLowestY = 0;
	int distanceX, distanceY;


	while (end == false)
	{
		//generate a new room
		if (rand() % 15 == 0)
			roomSize = GenerateCave(x, y);
		else
			roomSize = GenerateGoblinRoom(x, y);

		if (roomSize.x != 0 && roomSize.y != 0)
		{
			SRoom room;
			room.x = x;
			room.y = y;
			room.width = roomSize.x;
			room.height = roomSize.y;
			room.connectionDown = false;
			room.connectionLeft = false;
			room.connectionRight = false;
			room.connectionUp = false;

			//connect rooms
			for (i = roomlist.begin(); i != roomlist.end(); i++)
			{
				distanceX = abs(room.x - i->x);
				distanceY = abs(room.y - i->y);

				//if rooms are near together
				if (distanceX < 21 && distanceY < 21 && distanceX >= distanceY)
				{
					//if other room is at the right side
					if (room.x + room.width - 1 < i->x && distanceX > distanceY)
					{
						if (!i->connectionLeft)
						{
							GenerateConnectionHorizontal(room.x + room.width - 1, room.y + room.height - 2, i->x, i->y + i->height - 2);
							room.connectionRight = true;
							i->connectionLeft = true;
						}
					}
					//if the room is at the left side
					else if (i->x + i->width - 1 < room.x && distanceX > distanceY)
					{
						if (!i->connectionRight)
						{
							GenerateConnectionHorizontal(i->x + i->width - 1, i->y + i->height - 2, room.x, room.y + room.height - 2);
							room.connectionLeft = true;
							i->connectionRight = true;
						}
					}
					//if the room is lower
					else if (room.y + room.height - 1 < i->y)
					{
						if (!i->connectionUp)
						{
							if (i->x > room.x && i->x < room.x + room.width - 1)
								GenerateConnectionVertical(i->x + 1, room.y + room.height - 1, i->x + 1, i->y);
							else if (i->x + i->width - 1 > room.x && i->x + i->width - 1 < room.x + room.width - 1)
								GenerateConnectionVertical(i->x + i->width - 2, room.y + room.height - 1, i->x + i->width - 2, i->y);
							else if (room.x > i->x)
								GenerateConnectionVertical(room.x + 1, room.y + room.height - 1, i->x + i->width - 2, i->y);
							else
								GenerateConnectionVertical(room.x + room.width - 2, room.y + room.height - 1, i->x + 1, i->y);

							//room.connectionDown = true;
							//i->connectionUp = true;
						}
					}
					else if (room.y > i->y + i->height - 1)
					{
						cout << "In last else..." << endl;
						if (!i->connectionDown)
						{
							if (room.x + 1 > i->x && room.x + 1 < i->x + i->width - 1)
								GenerateConnectionVertical(room.x + 1, i->y + i->height - 1, room.x + 1, room.y);
							else if (room.x + room.width - 2 > i->x && room.x + room.width - 2 < i->x + i->width - 1)
								GenerateConnectionVertical(room.x + room.width - 2, i->y + i->height - 1, room.x + room.width - 2, room.y);
							else if (i->x > room.x)
								GenerateConnectionVertical(i->x + 1, i->y + i->height - 1, room.x + room.width - 2, room.y);
							else
								GenerateConnectionVertical(i->x + i->width - 2, i->y + i->height - 1, room.x + 1, room.y);

							//room.connectionUp = true;
							//i->connectionDown = true;
						}
					}
				}
			}


			roomlist.push_back(room);



			//get distance for next room
			xAdd = rand() % 9 + 1;
			x = x + room.width + xAdd;

			//get y-distance
			yAdd = rand() % 4;
			if (yAdd > xAdd)
				yAdd = xAdd;

			if (rand() % 2 == 0)
				y = y + yAdd;
			else
				y = y - yAdd;

			if (y <= m_BlocksY / 2 + 6)
				y = m_BlocksY / 2 + 6 + rand() % 3;

			if (y <= lastLowestY + 4)
				y = lastLowestY + 5 + rand() % 3;


			if (y > lowestY)
				lowestY = y;

			//check for new row or end
			if (x >= m_BlocksX)
			{
				x = 0;
				y = lowestY + 6;
				lastLowestY = lowestY;

				if (y >= m_BlocksY - 18)
					end = true;
			}
		}
		else
		{
			x++;

			if (x >= m_BlocksX)
			{
				x = 0;
				y = lowestY + 6;
				lastLowestY = lowestY;

				if (y >= m_BlocksY - 18)
					end = true;
			}
		}

	}

	return roomlist;
}


void CWorld::GenerateBottomLayer(list<SRoom> _roomlist)
{
	int randomNumber;
	bool princess = false;
	int y = m_BlocksY - 12;
	Vector2i roomSize;
	list<SRoom>::iterator i;

	//build first dungeon layer
	for (int x = 0; x < m_BlocksX;)
	{
		randomNumber = rand() % 7 + 4;
		roomSize = GenerateGoblinRoom(x, y, randomNumber, 5, true);


		if (roomSize.x != 0 && roomSize.y != 0)
		{
			//connect rooms
			for (i = _roomlist.begin(); i != _roomlist.end(); i++)
			{
				//if rooms are near together
				if (abs(x - i->x) < 15 && abs(y - i->y) < 21)
				{
					if (y > i->y + i->height - 1)
					{
						if (!i->connectionDown)
						{
							if (x + 1 > i->x && x + 1 < i->x + i->width - 1)
								GenerateConnectionVertical(x + 1, i->y + i->height - 1, x + 1, y);
							else if (x + roomSize.x - 2 > i->x && x + roomSize.x - 2 < i->x + i->width - 1)
								GenerateConnectionVertical(x + roomSize.x - 2, i->y + i->height - 1, x + roomSize.x - 2, y);
							else if (i->x > x)
								GenerateConnectionVertical(i->x + 1, i->y + i->height - 1, x + roomSize.x - 2, y);
							else
								GenerateConnectionVertical(i->x + i->width - 2, i->y + i->height - 1, x + 1, y);

							i->connectionDown = true;
						}
					}
				}
			}
		}

		x += randomNumber;
	}


	y = m_BlocksY - 7;

	//build second dungeon layer
	for (int x = 0; x < m_BlocksX;)
	{
		if (!princess && (rand() % 12 == 0 || x >= m_BlocksX - 20))
		{
			randomNumber = rand() % 6 + 6;
			GenerateFinalRoom(x, y, randomNumber);
			princess = true;
		}
		else
		{
			randomNumber = rand() % 7 + 4;
			GenerateGoblinRoom(x, y, randomNumber, 6, true);
		}

		x += randomNumber;
	}


	//generate blocks between rooms
	for (int y = m_BlocksY / 2 + 6; y < m_BlocksY - 1; y++)
	{
		for (int x = 0; x < m_BlocksX; x++)
		{
			GenerateRandomBlock(x, y);
		}
	}


	y = m_BlocksY - 1;

	//build bedrock layer
	for (int x = 0; x < m_BlocksX; x++)
	{
		m_pBlocks[x][y] = new CPlaceable;
		m_pBlocks[x][y]->Init(BEDROCK);
		m_pBlocks[x][y]->SetPos(static_cast<float>(x * 100), static_cast<float> (y * 100));
	}
}


//Generates a random room
void CWorld::GenerateRoom(int _x, int _y)
{
	//generate the size of the room
	int xSize = rand()%9 +3;
	int ySize = rand()%3 +3;

	if(_x + xSize <= m_BlocksX && _y + ySize <= m_BlocksY-1)
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
						m_pNpcMachine->AddNpc(GOBLIN, x * 100, y * 100, true, CHESTGOBLIN);
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


//Generates an outer room
Vector2i CWorld::GenerateOuterRoom(int _x, int _y)
{
	bool door = false;

	//generate the size of the room
	int xSize = rand() % 7 + 4;
	int ySize = rand() % 3 + 3;

	if (_x + xSize <= m_BlocksX && _y + ySize <= m_BlocksY - 1)
	{
		//build the room
		for (int y = _y - ySize + 1; y < _y + 1; y++)
		{
			for (int x = _x; x < _x + xSize; x++)
			{
				m_pBlocks[x][y] = new CPlaceable;

				//check if this block is one of the outer blocks
				if (y == _y - ySize + 1 || x == _x || x == _x + xSize - 1)
				{
					//set door
					if ((y == _y && x == _x && rand() % 2 == 0) || (y == _y && x == _x + xSize - 1 && door == false))
					{
						m_pBlocks[x][y]->Init(DOOR);
						m_pBlocks[x][y]->SetPos(static_cast<float>(x * 100), static_cast<float> (y * 100));
						m_pBlocks[x][y]->SetSpecialID(0);

						m_pWalls[x][y] = new CPlaceable;
						m_pWalls[x][y]->Init(BRICKWALL);
						m_pWalls[x][y]->SetPos(static_cast<float>(x * 100), static_cast<float> (y * 100));

						door = true;

						continue;
					}
					else
					{
						m_pBlocks[x][y]->Init(BRICKS);
						m_pBlocks[x][y]->SetPos(static_cast<float>(x * 100), static_cast<float> (y * 100));
					}
				}
				else if (y == _y)
				{
					int type = rand() % 10;

					//init the things in the room
					if (type == 5)
					{
						m_pBlocks[x][y]->Init(CUPBOARD);
						m_pBlocks[x][y]->SetPos(static_cast<float>(x * 100), static_cast<float> (y * 100));
					}
					else if (type == 6)
					{
						m_pBlocks[x][y]->Init(CHEST);
						m_pBlocks[x][y]->SetPos(static_cast<float>(x * 100), static_cast<float> (y * 100));
						m_pBlocks[x][y]->SetSpecialID(AddPanel(CHEST, x * 100, y * 100));
						FillChestRandomly(m_pBlocks[x][y]->GetSpecialID());
					}
					else if (type == 7)
					{
						m_pBlocks[x][y]->Init(FURNANCE);
						m_pBlocks[x][y]->SetPos(static_cast<float>(x * 100), static_cast<float> (y * 100));
						m_pBlocks[x][y]->SetSpecialID(AddPanel(FURNANCE, x * 100, y * 100));
					}
					else if (type == 8)
					{
						m_pBlocks[x][y]->Init(RUBBISH);
						m_pBlocks[x][y]->SetPos(static_cast<float>(x * 100), static_cast<float> (y * 100));
					}
					else if (type == 9)
					{
						m_pBlocks[x][y]->Init(ROOMFILL);
						m_pNpcMachine->AddNpc(GOBLIN, x * 100, y * 100, true, CHESTGOBLIN);
					}
					else if (y == _y)
					{
						m_pBlocks[x][y]->Init(ROOMFILL);
					}
					else
					{
						SAFE_DELETE(m_pBlocks[x][y]);
					}


					m_pWalls[x][y] = new CPlaceable;
					m_pWalls[x][y]->Init(BRICKWALL);
					m_pWalls[x][y]->SetPos(static_cast<float>(x * 100), static_cast<float> (y * 100));

				}
				else
				{
					SAFE_DELETE(m_pBlocks[x][y]);

					m_pWalls[x][y] = new CPlaceable;
					m_pWalls[x][y]->Init(BRICKWALL);
					m_pWalls[x][y]->SetPos(static_cast<float>(x * 100), static_cast<float> (y * 100));
				}

			}
		}
	}
	else
		return Vector2i(0, 0);

	return Vector2i(xSize, ySize);
}


//Generates a goblin room
Vector2i CWorld::GenerateGoblinRoom(int _x, int _y, int _sizeX, int _sizeY, bool _dungeon)
{
	int xSize, ySize;

	//generate the size of the room
	if (_sizeX == -1)
		xSize = rand() % 7 + 4;
	else
		xSize = _sizeX;

	if (_sizeY == -1)
		ySize = rand() % 3 + 3;
	else
		ySize = _sizeY;



	if (_x + xSize <= m_BlocksX && _y + ySize <= m_BlocksY - 1)
	{
		//build the room
		for (int y = _y; y < _y + ySize; y++)
		{
			for (int x = _x; x < _x + xSize; x++)
			{
				//check if this block is one of the outer blocks
				if (y == _y || y == _y + ySize - 1 || x == _x || x == _x + xSize - 1)
				{
					if (m_pBlocks[x][y] == NULL)
					{
						m_pBlocks[x][y] = new CPlaceable;
						m_pBlocks[x][y]->Init(BRICKS);
						m_pBlocks[x][y]->SetPos(static_cast<float>(x * 100), static_cast<float> (y * 100));
					}
					else
						MakeBrickwall(x, y);
				}
				else if (y == _y + ySize - 2)
				{
					int type = rand() % 10;

					//init the things in the room
					if (type == 5 && !_dungeon)
					{
						m_pBlocks[x][y] = new CPlaceable;
						m_pBlocks[x][y]->Init(CUPBOARD);
						m_pBlocks[x][y]->SetPos(static_cast<float>(x * 100), static_cast<float> (y * 100));
					}
					else if (type == 6)
					{
						m_pBlocks[x][y] = new CPlaceable;
						m_pBlocks[x][y]->Init(CHEST);
						m_pBlocks[x][y]->SetPos(static_cast<float>(x * 100), static_cast<float> (y * 100));
						m_pBlocks[x][y]->SetSpecialID(AddPanel(CHEST, x * 100, y * 100));
						FillChestRandomly(m_pBlocks[x][y]->GetSpecialID());
					}
					else if (type == 7 && !_dungeon)
					{
						m_pBlocks[x][y] = new CPlaceable;
						m_pBlocks[x][y]->Init(FURNANCE);
						m_pBlocks[x][y]->SetPos(static_cast<float>(x * 100), static_cast<float> (y * 100));
						m_pBlocks[x][y]->SetSpecialID(AddPanel(FURNANCE, x * 100, y * 100));
					}
					else if (type == 8)
					{
						m_pBlocks[x][y] = new CPlaceable;
						m_pBlocks[x][y]->Init(RUBBISH);
						m_pBlocks[x][y]->SetPos(static_cast<float>(x * 100), static_cast<float> (y * 100));
					}
					else if (type == 9)
					{
						m_pBlocks[x][y] = new CPlaceable;
						m_pBlocks[x][y]->Init(ROOMFILL);
						m_pNpcMachine->AddNpc(GOBLIN, x * 100, y * 100, true, CHESTGOBLIN);
					}
					else
					{
						m_pBlocks[x][y] = new CPlaceable;
						m_pBlocks[x][y]->Init(ROOMFILL);
					}


					m_pWalls[x][y] = new CPlaceable;
					m_pWalls[x][y]->Init(BRICKWALL);
					m_pWalls[x][y]->SetPos(static_cast<float>(x * 100), static_cast<float> (y * 100));

				}
				else
				{
					m_pBlocks[x][y] = new CPlaceable;
					m_pBlocks[x][y]->Init(ROOMFILL);

					m_pWalls[x][y] = new CPlaceable;
					m_pWalls[x][y]->Init(BRICKWALL);
					m_pWalls[x][y]->SetPos(static_cast<float>(x * 100), static_cast<float> (y * 100));
				}

			}
		}

		//if the room is in the dungeon: make connection
		if (_dungeon)
		{
			MakeBrickwall(_x, _y + ySize - 2);
			MakeBrickwall(_x + xSize - 1, _y + ySize - 2);
		}
	}
	else
	{
		xSize = 0;
		ySize = 0;
	}

	return Vector2i(xSize, ySize);
}


//Generates a horizontal conncection between two rooms
void CWorld::GenerateConnectionHorizontal(int _xStart, int _yStart, int _xEnd, int _yEnd)
{
	if (abs(_xStart - _xEnd) > abs(_yStart - _yEnd))
	{
		int xConnection = _xStart + 1;
		int yConnection = _yStart;

		int directionRegulator = 0;

		if (_yStart > _yEnd)
			directionRegulator = 1;

		//make an entrance
		MakeBrickwall(_xStart, _yStart);


		//if there's a difference in height
		if (_yStart != _yEnd)
		{

			for (yConnection; yConnection != _yEnd;)
			{
				//generate ceiling
				if (m_pBlocks[xConnection][yConnection - 1 - directionRegulator] == NULL && m_pWalls[xConnection][yConnection - 1 - directionRegulator] == NULL)
				{
					m_pBlocks[xConnection][yConnection - 1 - directionRegulator] = new CPlaceable;
					m_pBlocks[xConnection][yConnection - 1 - directionRegulator]->Init(BRICKS);
					m_pBlocks[xConnection][yConnection - 1 - directionRegulator]->SetPos((float)xConnection * 100, (float)(yConnection - 1 - directionRegulator) * 100);
				}
				else
				{
					MakeBrickwall(xConnection, yConnection - 1 - directionRegulator);
				}


				//generate inside
				if (m_pBlocks[xConnection][yConnection - directionRegulator] == NULL && m_pWalls[xConnection][yConnection - directionRegulator] == NULL)
				{
					m_pBlocks[xConnection][yConnection - directionRegulator] = new CPlaceable;
					m_pBlocks[xConnection][yConnection - directionRegulator]->Init(ROOMFILL);

					m_pWalls[xConnection][yConnection - directionRegulator] = new CPlaceable;
					m_pWalls[xConnection][yConnection - directionRegulator]->Init(BRICKWALL);
					m_pWalls[xConnection][yConnection - directionRegulator]->SetPos((float)xConnection * 100, (float)(yConnection - directionRegulator) * 100);
				}
				else
				{
					MakeBrickwall(xConnection, yConnection - directionRegulator);
				}



				if (m_pBlocks[xConnection][yConnection + 1 - directionRegulator] == NULL && m_pWalls[xConnection][yConnection + 1 - directionRegulator] == NULL)
				{
					m_pBlocks[xConnection][yConnection + 1 - directionRegulator] = new CPlaceable;
					m_pBlocks[xConnection][yConnection + 1 - directionRegulator]->Init(ROOMFILL);

					m_pWalls[xConnection][yConnection + 1 - directionRegulator] = new CPlaceable;
					m_pWalls[xConnection][yConnection + 1 - directionRegulator]->Init(BRICKWALL);
					m_pWalls[xConnection][yConnection + 1 - directionRegulator]->SetPos((float)xConnection * 100, (float)(yConnection + 1 - directionRegulator) * 100);
				}
				else
				{
					MakeBrickwall(xConnection, yConnection + 1 - directionRegulator);
				}


				//generate floor
				if (m_pBlocks[xConnection][yConnection + 2 - directionRegulator] == NULL && m_pWalls[xConnection][yConnection + 2 - directionRegulator] == NULL)
				{
					m_pBlocks[xConnection][yConnection + 2 - directionRegulator] = new CPlaceable;
					m_pBlocks[xConnection][yConnection + 2 - directionRegulator]->Init(BRICKS);
					m_pBlocks[xConnection][yConnection + 2 - directionRegulator]->SetPos((float)xConnection * 100, (float)(yConnection + 2 - directionRegulator) * 100);
				}
				else
				{
					MakeBrickwall(xConnection, yConnection + 2 - directionRegulator);
				}



				xConnection++;

				if (xConnection != _xStart)
				{
					if (_yStart < _yEnd)
						yConnection++;
					else
						yConnection--;
				}
			}
		}




		while (_xEnd != xConnection)
		{
			//generate ceiling
			if (m_pBlocks[xConnection][yConnection - 1] == NULL && m_pWalls[xConnection][yConnection - 1] == NULL)
			{
				m_pBlocks[xConnection][yConnection - 1] = new CPlaceable;
				m_pBlocks[xConnection][yConnection - 1]->Init(BRICKS);
				m_pBlocks[xConnection][yConnection - 1]->SetPos((float)xConnection * 100, (float)(yConnection - 1) * 100);
			}
			else
			{
				MakeBrickwall(xConnection, yConnection -1);
			}
			

			//generate inside
			if (m_pBlocks[xConnection][yConnection] == NULL && m_pWalls[xConnection][yConnection] == NULL)
			{
				m_pBlocks[xConnection][yConnection] = new CPlaceable;
				m_pBlocks[xConnection][yConnection]->Init(ROOMFILL);

				m_pWalls[xConnection][yConnection] = new CPlaceable;
				m_pWalls[xConnection][yConnection]->Init(BRICKWALL);
				m_pWalls[xConnection][yConnection]->SetPos((float)xConnection * 100, (float)yConnection * 100);
			}
			else
			{
				MakeBrickwall(xConnection, yConnection);
			}

			//generate floor
			if (m_pBlocks[xConnection][yConnection + 1] == NULL && m_pWalls[xConnection][yConnection + 1] == NULL)
			{
				m_pBlocks[xConnection][yConnection + 1] = new CPlaceable;
				m_pBlocks[xConnection][yConnection + 1]->Init(BRICKS);
				m_pBlocks[xConnection][yConnection + 1]->SetPos((float)xConnection * 100, (float)(yConnection + 1) * 100);
			}
			else
			{
				MakeBrickwall(xConnection, yConnection + 1);
			}

			xConnection++;
		}

		//make an exit
		MakeBrickwall(xConnection, yConnection);

	}
}


//Generates a vertical conncection between two rooms
void CWorld::GenerateConnectionVertical(int _xStart, int _yStart, int _xEnd, int _yEnd)
{
	if (abs(_yStart - _yEnd) > abs(_xStart - _xEnd))
	{
		int xConnection = _xStart;
		int yConnection = _yStart +1;

		int directionRegulator = 0;

		if (_xStart > _xEnd)
			directionRegulator = 1;

		//delete all things above the entrance (cupboards, chests etc.)
		MakeBrickwall(_xStart, _yStart - 1);

		//make an entrance
		SAFE_DELETE(m_pBlocks[_xStart][_yStart]);
		m_pBlocks[_xStart][_yStart] = new CPlaceable;
		m_pBlocks[_xStart][_yStart]->Init(LADDER);
		m_pBlocks[_xStart][_yStart]->SetPos((float)_xStart * 100, (float)_yStart * 100);

		SAFE_DELETE(m_pWalls[_xStart][_yStart]);
		m_pWalls[_xStart][_yStart] = new CPlaceable;
		m_pWalls[_xStart][_yStart]->Init(BRICKWALL);
		m_pWalls[_xStart][_yStart]->SetPos((float)_xStart * 100, (float)_yStart * 100);


		//if there's a difference in x-direction
		if (_xStart != _xEnd)
		{

			for (xConnection; xConnection != _xEnd;)
			{
				//generate left wall
				if (m_pBlocks[xConnection - 1 - directionRegulator][yConnection] == NULL && m_pWalls[xConnection - 1 - directionRegulator][yConnection] == NULL)
				{
					m_pBlocks[xConnection - 1 - directionRegulator][yConnection] = new CPlaceable;
					m_pBlocks[xConnection - 1 - directionRegulator][yConnection]->Init(BRICKS);
					m_pBlocks[xConnection - 1 - directionRegulator][yConnection]->SetPos((float)(xConnection - 1 - directionRegulator) * 100, (float)yConnection * 100);
				}
				else
				{
					if (!(m_pBlocks[xConnection - 1 - directionRegulator][yConnection] != NULL && m_pBlocks[xConnection - 1 - directionRegulator][yConnection]->getID() == BRICKS))
						MakeBrickwall(xConnection - 1 - directionRegulator, yConnection);
				}

				//generate inside
				if (m_pBlocks[xConnection - directionRegulator][yConnection] == NULL && m_pWalls[xConnection - directionRegulator][yConnection] == NULL)
				{
					m_pBlocks[xConnection - directionRegulator][yConnection] = new CPlaceable;
					m_pBlocks[xConnection - directionRegulator][yConnection]->Init(ROOMFILL);

					m_pWalls[xConnection - directionRegulator][yConnection] = new CPlaceable;
					m_pWalls[xConnection - directionRegulator][yConnection]->Init(BRICKWALL);
					m_pWalls[xConnection - directionRegulator][yConnection]->SetPos((float)(xConnection - directionRegulator) * 100, (float)yConnection * 100);
				}
				else
				{
					MakeBrickwall(xConnection - directionRegulator, yConnection);
				}


				if (m_pBlocks[xConnection + 1 - directionRegulator][yConnection] == NULL && m_pWalls[xConnection + 1 - directionRegulator][yConnection] == NULL)
				{
					m_pBlocks[xConnection + 1 - directionRegulator][yConnection] = new CPlaceable;
					m_pBlocks[xConnection + 1 - directionRegulator][yConnection]->Init(ROOMFILL);

					m_pWalls[xConnection + 1 - directionRegulator][yConnection] = new CPlaceable;
					m_pWalls[xConnection + 1 - directionRegulator][yConnection]->Init(BRICKWALL);
					m_pWalls[xConnection + 1 - directionRegulator][yConnection]->SetPos((float)(xConnection + 1 - directionRegulator) * 100, (float)yConnection * 100);
				}
				else
				{
					MakeBrickwall(xConnection + 1 - directionRegulator, yConnection);
				}

				//generate right wall
				if (m_pBlocks[xConnection + 2 - directionRegulator][yConnection] == NULL && m_pWalls[xConnection + 2 - directionRegulator][yConnection] == NULL)
				{
					m_pBlocks[xConnection + 2 - directionRegulator][yConnection] = new CPlaceable;
					m_pBlocks[xConnection + 2 - directionRegulator][yConnection]->Init(BRICKS);
					m_pBlocks[xConnection + 2 - directionRegulator][yConnection]->SetPos((float)(xConnection + 2 - directionRegulator) * 100, (float)yConnection * 100);
				}
				else
				{
					if (!(m_pBlocks[xConnection + 2 - directionRegulator][yConnection] != NULL && m_pBlocks[xConnection + 2 - directionRegulator][yConnection]->getID() == BRICKS))
						MakeBrickwall(xConnection + 2 - directionRegulator, yConnection);
				}


				yConnection++;

				if (yConnection != _yStart)
				{
					if (_xStart < _xEnd)
						xConnection++;
					else
						xConnection--;
				}
			}


		}




		while (_yEnd != yConnection)
		{
			//generate left wall
			if (m_pBlocks[xConnection - 1][yConnection] == NULL && m_pWalls[xConnection - 1][yConnection] == NULL)
			{
				m_pBlocks[xConnection - 1][yConnection] = new CPlaceable;
				m_pBlocks[xConnection - 1][yConnection]->Init(BRICKS);
				m_pBlocks[xConnection - 1][yConnection]->SetPos((float)(xConnection-1) * 100, (float)yConnection * 100);
			}
			else
			{
				if (!(m_pBlocks[xConnection - 1 - directionRegulator][yConnection] != NULL && m_pBlocks[xConnection - 1 - directionRegulator][yConnection]->getID() == BRICKS))
					MakeBrickwall(xConnection - 1, yConnection);
			}

			//generate inside
			if (m_pBlocks[xConnection][yConnection] == NULL && m_pWalls[xConnection][yConnection] == NULL)
			{
				m_pBlocks[xConnection][yConnection] = new CPlaceable;
				m_pBlocks[xConnection][yConnection]->Init(LADDER);
				m_pBlocks[xConnection][yConnection]->SetPos((float)xConnection * 100, (float)yConnection * 100);

				m_pWalls[xConnection][yConnection] = new CPlaceable;
				m_pWalls[xConnection][yConnection]->Init(BRICKWALL);
				m_pWalls[xConnection][yConnection]->SetPos((float)xConnection * 100, (float)yConnection * 100);
			}
			else
			{
				MakeBrickwall(xConnection, yConnection);
			}

			//generate right wall
			if (m_pBlocks[xConnection + 1][yConnection] == NULL && m_pWalls[xConnection + 1][yConnection] == NULL)
			{
				m_pBlocks[xConnection + 1][yConnection] = new CPlaceable;
				m_pBlocks[xConnection + 1][yConnection]->Init(BRICKS);
				m_pBlocks[xConnection + 1][yConnection]->SetPos((float)(xConnection+1) * 100, (float)yConnection * 100);
			}
			else
			{
				if (!(m_pBlocks[xConnection + 1 - directionRegulator][yConnection] != NULL && m_pBlocks[xConnection + 1 - directionRegulator][yConnection]->getID() == BRICKS))
					MakeBrickwall(xConnection + 1, yConnection);
			}

			yConnection++;
		}

		//make an exit
		SAFE_DELETE(m_pBlocks[xConnection][yConnection]);
		m_pBlocks[xConnection][yConnection] = new CPlaceable;
		m_pBlocks[xConnection][yConnection]->Init(LADDER);
		m_pBlocks[xConnection][yConnection]->SetPos((float)xConnection * 100, (float)yConnection * 100);

		SAFE_DELETE(m_pWalls[xConnection][yConnection]);
		m_pWalls[xConnection][yConnection] = new CPlaceable;
		m_pWalls[xConnection][yConnection]->Init(BRICKWALL);
		m_pWalls[xConnection][yConnection]->SetPos((float)xConnection * 100, (float)yConnection * 100);

		yConnection++;

		//build ladders to the ground
		while (m_pBlocks[xConnection][yConnection] == NULL || m_pBlocks[xConnection][yConnection]->IsPassable())
		{
			MakeBrickwall(xConnection, yConnection);

			SAFE_DELETE(m_pBlocks[xConnection][yConnection]);
			m_pBlocks[xConnection][yConnection] = new CPlaceable;
			m_pBlocks[xConnection][yConnection]->Init(LADDER);
			m_pBlocks[xConnection][yConnection]->SetPos((float)xConnection * 100, (float)yConnection * 100);

			yConnection++;
		}

	}
}


//converts block in brickwall
void CWorld::MakeBrickwall(int _x, int _y)
{
	list<CPanel*>::iterator p;

	//check for panels
	if (m_pBlocks[_x][_y] != NULL && (m_pBlocks[_x][_y]->getID() == FURNANCE || m_pBlocks[_x][_y]->getID() == CHEST || m_pBlocks[_x][_y]->getID() == CAULDRON))
	{
		//seek for the panel
		for (p = m_PanelList.begin(); p != m_PanelList.end(); p++)
		{
			//if found: delete it
			if (m_pBlocks[_x][_y]->GetSpecialID() == (*p)->GetNumber())
			{
				SAFE_DELETE(*p);
				m_PanelList.erase(p);
				break;
			}
		}
	}

	SAFE_DELETE(m_pBlocks[_x][_y]);
	m_pBlocks[_x][_y] = new CPlaceable;
	m_pBlocks[_x][_y]->Init(ROOMFILL);

	SAFE_DELETE(m_pWalls[_x][_y]);
	m_pWalls[_x][_y] = new CPlaceable;
	m_pWalls[_x][_y]->Init(BRICKWALL);
	m_pWalls[_x][_y]->SetPos((float)_x * 100, (float)_y * 100);
}


//generates a random block
void CWorld::GenerateRandomBlock(int _x, int _y)
{
	int possibility[9];
	int randomNumber;
	int possibilitySum = 0;

	if (m_pBlocks[_x][_y] == NULL)
	{
		//set the start possibilities
		possibility[0] = 84;            //dirt
		possibility[1] = 10;            //stone

		if (_y > 7)
			possibility[2] = 3;            //coal
		else
			possibility[2] = 0;

		if (_y > 10)
			possibility[3] = 2;            //iron
		else
			possibility[3] = 0;

		if (_y > 15)
			possibility[4] = 1;            //gold
		else
			possibility[4] = 0;

		if (_y > 20)
			possibility[5] = 1;              //arcanus
		else
			possibility[5] = 0;

		if (_y > 4)
			possibility[6] = 5;             //marble
		else
			possibility[6] = 0;

		if (_y > 7)
			possibility[7] = 3;            //sulfur
		else
			possibility[7] = 0;

		if (_y > 7)
			possibility[8] = 3;            //salpeter
		else
			possibility[8] = 0;



		//if a near placeable is a specific type: greater chance, that this placeable will be the same type
		if (_y > 4 && _x > 0)
		{
			if (m_pBlocks[_x - 1][_y] != NULL)
				if (m_pBlocks[_x - 1][_y]->getID() < 10 && m_pBlocks[_x - 1][_y]->getID() > 0)
					possibility[m_pBlocks[_x - 1][_y]->getID() - 1] += 50;
			if (m_pBlocks[_x][_y - 1] != NULL && m_pBlocks[_x][_y - 1]->getID() > 0)
				if (m_pBlocks[_x][_y - 1]->getID() < 10)
					possibility[m_pBlocks[_x][_y - 1]->getID() - 1] += 50;
		}



		//Create new Placeable
		m_pBlocks[_x][_y] = new CPlaceable;

		//calculate the sum
		for (int i = 0; i < 9; i++)
			possibilitySum += possibility[i];

		//generate a random number between 1 and 100
		randomNumber = rand() % possibilitySum + 1;

		//decide which placeable is going to be set
		if (randomNumber <= possibility[0])
			m_pBlocks[_x][_y]->Init(DIRT);
		else if (randomNumber <= possibility[1] + possibility[0])
			m_pBlocks[_x][_y]->Init(STONE);
		else if (randomNumber <= possibility[0] + possibility[1] + possibility[2])
			m_pBlocks[_x][_y]->Init(COALBLOCK);
		else if (randomNumber <= possibility[0] + possibility[1] + possibility[2] + possibility[3])
			m_pBlocks[_x][_y]->Init(IRONBLOCK);
		else if (randomNumber <= possibility[0] + possibility[1] + possibility[2] + possibility[3] + possibility[4])
			m_pBlocks[_x][_y]->Init(GOLDBLOCK);
		else if (randomNumber <= possibility[0] + possibility[1] + possibility[2] + possibility[3] + possibility[4] + possibility[5])
			m_pBlocks[_x][_y]->Init(ARCANUSBLOCK);
		else if (randomNumber <= possibility[0] + possibility[1] + possibility[2] + possibility[3] + possibility[4] + possibility[5] + possibility[6])
			m_pBlocks[_x][_y]->Init(MARBLE);
		else if (randomNumber <= possibility[0] + possibility[1] + possibility[2] + possibility[3] + possibility[4] + possibility[5] + possibility[6] + possibility[7])
			m_pBlocks[_x][_y]->Init(SULFURBLOCK);
		else
			m_pBlocks[_x][_y]->Init(SALPETERBLOCK);


		//set position
		m_pBlocks[_x][_y]->SetPos(static_cast<float>(_x * 100), static_cast<float> (_y * 100));

	}
	else if (m_pBlocks[_x][_y]->getID() == ROOMFILL)
	{
		SAFE_DELETE(m_pBlocks[_x][_y]);
	}
}


//generates the princess room
void CWorld::GenerateFinalRoom(int _x, int _y, int _xSize)
{
	bool princess = false;

	//generate the size of the room
	int xSize = _xSize;
	int ySize = 6;

	while (_x + xSize >= m_BlocksX)
	{
		xSize--;
	}

	//build the room
	for (int y = _y; y < _y + ySize; y++)
	{
		for (int x = _x; x < _x + xSize; x++)
		{

			m_pBlocks[x][y] = new CPlaceable;

			//check if this block is one of the outer blocks
			if (y == _y || y == _y + ySize - 1 || x == _x || x == _x + xSize - 1)
			{
				m_pBlocks[x][y]->Init(BRICKS);
				m_pBlocks[x][y]->SetPos(static_cast<float>(x * 100), static_cast<float> (y * 100));
			}
			else if (y == _y + ySize - 2)
			{
				//check for princess
				if (princess == false && (rand() % 5 == 0 || x == _x + xSize -2))
				{
					princess = true;

					if (rand() % 2 == 0)
					{
						SAFE_DELETE(m_pBlocks[x][_y + 1]);
						m_pBlocks[x][_y + 1] = new CPlaceable;
						m_pBlocks[x][_y + 1]->Init(PRINCESSCAGE);
						m_pBlocks[x][_y + 1]->SetSpecialID(0);
						m_pBlocks[x][_y + 1]->SetPos(static_cast<float>(x * 100), static_cast<float> ((_y+1) * 100));
					}
					else
					{
						m_pBlocks[x][y]->Init(PRINCESSCAGE);
						m_pBlocks[x][y]->SetSpecialID(1);
						m_pBlocks[x][y]->SetPos(static_cast<float>(x * 100), static_cast<float> (y * 100));

						m_pWalls[x][y] = new CPlaceable;
						m_pWalls[x][y]->Init(BRICKWALL);
						m_pWalls[x][y]->SetPos(static_cast<float>(x * 100), static_cast<float> (y * 100));

						continue;
					}
					
				}

				int type = rand() % 5;

					if (type == 0)
					{
						m_pBlocks[x][y]->Init(RUBBISH);
						m_pBlocks[x][y]->SetPos(static_cast<float>(x * 100), static_cast<float> (y * 100));
					}
					else if (type == 1)
					{
						m_pBlocks[x][y]->Init(ROOMFILL);
						m_pNpcMachine->AddNpc(GOBLIN, x * 100, y * 100, true);
					}
					else
					{
						m_pBlocks[x][y]->Init(ROOMFILL);
					}


					m_pWalls[x][y] = new CPlaceable;
					m_pWalls[x][y]->Init(BRICKWALL);
					m_pWalls[x][y]->SetPos(static_cast<float>(x * 100), static_cast<float> (y * 100));

				}
				else
				{
					m_pBlocks[x][y]->Init(ROOMFILL);

					m_pWalls[x][y] = new CPlaceable;
					m_pWalls[x][y]->Init(BRICKWALL);
					m_pWalls[x][y]->SetPos(static_cast<float>(x * 100), static_cast<float> (y * 100));
				}

			}
		}
	
	MakeBrickwall(_x, _y + ySize - 2);
	MakeBrickwall(_x + xSize - 1, _y + ySize - 2);

}


//generates a cave
Vector2i CWorld::GenerateCave(int _x, int _y)
{
	bool ogreInCave = false;

	//generate the size of the cave
	int xSize = rand() % 9 + 2;
	int ySize = rand() % 3 + 3;

	if (_x + xSize <= m_BlocksX && _y + ySize <= m_BlocksY - 1)
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
					if (rand() % 3 == 0 && m_pBlocks[x][y - 1] != NULL)
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
						m_pNpcMachine->AddNpc(GOBLIN, x * 100, y * 100, true);
					}
					else if (type == 3 && !ogreInCave)
					{
						m_pBlocks[x][y]->Init(ROOMFILL);
						m_pNpcMachine->AddNpc(OGRE, x * 100, (y - 1) * 100, true);
						ogreInCave = true;
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
	else
		return Vector2i(0, 0);

	return Vector2i(xSize, ySize);
}


//generates a tree
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

	int sunDistance;

	if (m_fast_sun)
		sunDistance = 300;
	else
		sunDistance = 100;
	
	if (viewY < 1000)
	{
		for (int i = viewFirstBlock - sunDistance; i <= viewFirstBlock + m_pView->getSize().x + sunDistance; i += sunDistance)
		{
			m_lightMachine.AddLightCircle(i - i%sunDistance, 0, 1000, Color(255, 255, 255, m_NightAlpha));
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
						if (neighbourID == COALBLOCK || neighbourID == GOLDBLOCK || neighbourID == IRONBLOCK || neighbourID == ARCANUSBLOCK || neighbourID == SULFURBLOCK || neighbourID == SALPETERBLOCK)
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
						if (neighbourID == COALBLOCK || neighbourID == GOLDBLOCK || neighbourID == IRONBLOCK || neighbourID == ARCANUSBLOCK || neighbourID == SULFURBLOCK || neighbourID == SALPETERBLOCK)
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
						if (neighbourID == COALBLOCK || neighbourID == GOLDBLOCK || neighbourID == IRONBLOCK || neighbourID == ARCANUSBLOCK || neighbourID == SULFURBLOCK || neighbourID == SALPETERBLOCK)
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
						if (neighbourID == COALBLOCK || neighbourID == GOLDBLOCK || neighbourID == IRONBLOCK || neighbourID == ARCANUSBLOCK || neighbourID == SULFURBLOCK || neighbourID == SALPETERBLOCK)
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
bool CWorld::CheckPlaceables(IntRect _playerRect, CPlayer *_player)
{

	IntRect rectP;
	list<CPanel*>::iterator p;

	int xView = m_pView->getCenter().x - m_pView->getSize().x / 2;
	int yView = m_pView->getCenter().y - m_pView->getSize().y / 2;
	
	bool lucky = false;
	int amount = 1;

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
			amount = 1;
			lucky = false;

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
					/*	if(m_pBlocks[x][y]->getID() == GOLDBLOCK)
						{
							int soundNumber = rand()%3;

							m_sound.setBuffer(g_pSound->m_goldSound[soundNumber]);
							m_sound.play();
						}*/
						switch (m_pBlocks[x][y]->getID())
						{
							//if block was block with sulfur or salpeter: add stone drop
							case(SULFURBLOCK):
							case(SALPETERBLOCK):
							{
								AddLittleItem(STONE, x * 100 + 23, y * 100 + 23);
							}break;


							//Add exp
							case(GOLDBLOCK):
							case(IRONBLOCK):
							case(ARCANUSBLOCK) :
							{
								_player->AddExp(5);
							}break;


							//check if the broken placeable was a tree
							case(TREETRUNK) :
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
											AddLittleItem(BEEHIVE, m_pBlocks[x - 1][y]->GetRect().left + 23, m_pBlocks[x - 1][y]->GetRect().top + 20);
											SAFE_DELETE(m_pBlocks[x - 1][y]);
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
							}break;


							//give two wood if block was tree
							case(TREECROWN) :
							{
								amount = 2;
							}break;


							//if the placeable was rubbish show animation
							case(RUBBISH) :
							{
								SProjectile projectile;

								//add a projectile
								CSprite *sprite = new CSprite;

								sprite->Load(&g_pTextures->t_rubbishAnimation, 5, 150, 150);
								sprite->SetPos(x * 100 - 25, y * 100 - 50);

								projectile.m_ID = RUBBISHANIMATION;
								projectile.m_Damage = 0;
								projectile.m_fFlown = 0.0f;
								projectile.m_flightLength = 0;
								projectile.m_fromPlayer = true;
								projectile.m_fYVel = 0.0f;
								projectile.m_Sprite = sprite;
								projectile.m_fAnimState = 0;
								g_pProjectiles->NewProjectile(projectile);
							}break;

						
						}

	

						//check if the player could have luck
						//check blocktype for luck
						if((m_pBlocks[x][y]->getID() >=3 && m_pBlocks[x][y]->getID() <= 6) || m_pBlocks[x][y]->getID() == 8 || m_pBlocks[x][y]->getID() == 9)
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

					if (m_pBlocks[x][y]->getID() == PRINCESSCAGE && _player->GetCarriedItem()->getID() == KEY)
					{
						return true;
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

	 for (i = m_LittleItemList.begin(); i != m_LittleItemList.end();)
	{

		if(_playerRect.intersects(i->GetRect()))
		{
			//if it is a dynamite: end burning
			if (i->GetThing()->getID() == DYNAMITE)
			{
				if (((CItem*)(i->GetThing()))->GetSpecialID() == 1)
				{
					i++;
					continue;
				}
			}

			if (_player->Take(i->GetThing(), 1))
			{
				i->Quit();
				i = m_LittleItemList.erase(i);
				continue;
			}
		}

		if (i->GetThing()->getID() == DYNAMITE)
		{
			if (i->DynamiteExploded())
			{
				i->Quit();
				i = m_LittleItemList.erase(i);
				continue;
			}
		}

		i++;
	}

	return false;
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

				if (thing->getID() == DYNAMITE)
					thing->SetSpecialID(1);

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

			//if thing is dynamite: add effect
			if (_ID == DYNAMITE)
			{
				item.SetVel(Vector2f(0, -150.0f));
				m_LittleItemList.push_back(item);

				SProjectile projectile;

				//add a projectile
				CSprite *sprite = new CSprite;

				sprite->Load(&g_pTextures->t_dynamiteAnimation, 5, 100, 50);
				sprite->SetPos(_x, _y);

				projectile.m_ID = DYNAMITEEFFECT;
				projectile.m_Damage = 0;
				projectile.m_fFlown = 5.0f;   //time
				projectile.m_flightLength = 0;
				projectile.m_fromPlayer = false;
				projectile.m_fYVel = 0.0f;
				projectile.m_Sprite = sprite;
				projectile.m_fAnimState = 0;
				projectile.m_xPos = m_LittleItemList.back().GetXPos();
				projectile.m_yPos = m_LittleItemList.back().GetYPos();
				g_pProjectiles->NewProjectile(projectile);

				i++;
				continue;
			}
			else
				item.SetVel(Vector2f(0, -350.0f));

			if (_ID == COOKINGBOOK)
			{
				CItem *book = (CItem*)item.GetThing();
				book->SetSpecialID(AddPanel(COOKINGBOOK, 0, 0));
			}

			m_LittleItemList.push_back(item);
		}
	}
}


//for rare items
void CWorld::AddLittleItem(CThing* _thing, int _x, int _y)
{
	CLittleItem item;
	item.Init(_thing, _x + (rand() % 50 - 25), _y + (rand() % 20));
	item.SetVel(Vector2f(0, -350.0f));
	m_LittleItemList.push_back(item);
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
		if(xEnd > m_BlocksX)
				xEnd = m_BlocksX;

		int yEnd = static_cast<int>(i->GetRect().top/100) +2;
		if(yEnd > m_BlocksY)
			yEnd = m_BlocksY;
	
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

	if ((x < 0 || y < 0) && _number == -1)
		return NULL;

	if (_number == -1 && m_pBlocks[x][y] != NULL)
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
				if(randomNumber > PIBREAK && randomNumber < 72)
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
				else if(randomNumber > CTBREAK && randomNumber < 107)
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
				return true;
			}
		}
	}
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
				return false;
			}
		}
	}

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
	int blockValues[10];
	blockValues[DIRT - 1] = 1;
	blockValues[STONE - 1] = 2;
	blockValues[COALBLOCK - 1] = 2;
	blockValues[IRONBLOCK - 1] = 3;
	blockValues[GOLDBLOCK - 1] = 3;
	blockValues[ARCANUSBLOCK - 1] = 4;
	blockValues[MARBLE - 1] = 2;
	blockValues[SULFURBLOCK - 1] = 2; 
	blockValues[SALPETERBLOCK - 1] = 2;
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
			newID = rand() % 6;

			if (newID == 0)
				newID = STONE;
			else if (newID == 1)
				newID = COALBLOCK;
			else if (newID == 2)
				newID = MARBLE;
			else if (newID == 3)
				newID = WOOD;
			else if (newID == 4)
				newID = SULFURBLOCK;
			else if (newID == 5)
				newID = SALPETERBLOCK;
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
		//delete blocks
		if (m_pBlocks[_x][_y] != NULL && m_pBlocks[_x][_y]->getID() != BEDROCK)
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

		//delete walls
		if (m_pWalls[_x][_y] != NULL)
		{
			AddLittleItem(m_pWalls[_x][_y]->GetLittleID(), m_pWalls[_x][_y]->GetRect().left + 23, m_pWalls[_x][_y]->GetRect().top + 20);

			SAFE_DELETE(m_pWalls[_x][_y]);
		}
	}
}