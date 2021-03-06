#include "NPC.hpp"
#include "World.hpp"


CNpc::CNpc()
{
	m_wasHit = false;
	m_fSecondsTimer = 0;
}



Vector2i CNpc::findPath(int _xDest, int _yDest)
{
	vector <vector <SWorldPlace> > worldMatrix;

	//get the world matrix
	worldMatrix = m_pWorld->GetWorldMatrix();

	//make the lists
	list<SWorldPlace*> openList;
	list<SWorldPlace*> closedList;
	list<SWorldPlace*>::iterator firstIt;
	list<SWorldPlace*>::iterator secondIt;

	int currentX = -1, currentY = -1, destinationX = -1, destinationY = -1, startX = -1, startY = -1;

	int blockSize = 100;

	bool checkLeft, checkRight, checkTop, checkBottom;

	int estimatedCost;

	//clear both lists
	openList.clear();
	closedList.clear();

	if (m_xPos < 0)
		m_xPos = 0;
	if (m_yPos < 0)
		m_yPos = 0;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//					get the destination and the start place in the matrix									//
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	for (int y = 0; y < worldMatrix[0].size(); y++)
	{
		for (int x = 0; x < worldMatrix.size(); x++)
		{
			//if the destination is inside this world place: save it
			if (_xDest >= worldMatrix[x][y].xPos && _xDest < worldMatrix[x][y].xPos + blockSize && _yDest >= worldMatrix[x][y].yPos && _yDest < worldMatrix[x][y].yPos + blockSize)
			{
				destinationX = x;
				destinationY = y;

				if (startX != -1)
				{
					//end the loops
					x = worldMatrix.size();
					y = worldMatrix[0].size();
					break;
				}
			}

			//if the current place is inside this world place: save it
			if (m_xPos >= worldMatrix[x][y].xPos && m_xPos < worldMatrix[x][y].xPos + blockSize && m_yPos >= worldMatrix[x][y].yPos && m_yPos < worldMatrix[x][y].yPos + blockSize)
			{
				startX = x;
				startY = y;

				if (destinationX != -1)
				{
					//end the loops
					x = worldMatrix.size();
					y = worldMatrix[0].size();
					break;
				}
			}

		}
	}

	//if no start place was found: return
	if (startX == -1 || startY == -1)
		return Vector2i(-1, -1);

	worldMatrix[startX][startY].cost = 0;

	//add the start place to the closed list
	closedList.push_back(&worldMatrix[startX][startY]);

	currentX = startX;
	currentY = startY;


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//					loop until getting to the destination													//
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//while the destination wasn't reached
	while (currentX != destinationX || currentY != destinationY)
	{
		//usually every block should be checked
		checkTop = true;
		checkBottom = true;
		checkLeft = true;
		checkRight = true;

		//check if the neighbour blocks do exist and are passable
		if (currentX - 1 < 0 || !worldMatrix[currentX - 1][currentY].passable)
			checkLeft = false;
		if (currentX + 1 >= worldMatrix.size() || !worldMatrix[currentX + 1][currentY].passable)
			checkRight = false;
		if (currentY - 1 < 0 || !worldMatrix[currentX][currentY - 1].passable)
			checkTop = false;
		if (currentY + 1 >= worldMatrix[0].size() || !worldMatrix[currentX][currentY + 1].passable)
			checkBottom = false;


		//iterate through the closed list 
		for (firstIt = closedList.begin(); firstIt != closedList.end(); firstIt++)
		{
			if (checkTop && (*firstIt) == &worldMatrix[currentX][currentY - 1])
				checkTop = false;
			else if (checkBottom && (*firstIt) == &worldMatrix[currentX][currentY + 1])
				checkBottom = false;
			else if (checkLeft && (*firstIt) == &worldMatrix[currentX - 1][currentY])
				checkLeft = false;
			else if (checkRight && (*firstIt) == &worldMatrix[currentX + 1][currentY])
				checkRight = false;
		}


		//iterate through the open list and correct the values and parents if needed
		for (secondIt = openList.begin(); secondIt != openList.end(); secondIt++)
		{
			if (checkTop && (*secondIt) == &worldMatrix[currentX][currentY - 1])
			{
				if (worldMatrix[currentX][currentY - 1].pathValue > worldMatrix[currentX][currentY].cost + 1 + abs(currentX - destinationX) + abs(currentY - destinationY - 1))
				{
					worldMatrix[currentX][currentY - 1].pathValue = worldMatrix[currentX][currentY].cost + 1 + abs(currentX - destinationX) + abs(currentY - destinationY - 1);
					worldMatrix[currentX][currentY - 1].parentX = currentX;
					worldMatrix[currentX][currentY - 1].parentY = currentY;
				}

				checkTop = false;
			}
			else if (checkBottom && (*secondIt) == &worldMatrix[currentX][currentY + 1])
			{
				if (worldMatrix[currentX][currentY + 1].pathValue > worldMatrix[currentX][currentY].cost + 1 + abs(currentX - destinationX) + abs(currentY - destinationY + 1))
				{
					worldMatrix[currentX][currentY + 1].pathValue = worldMatrix[currentX][currentY].cost + 1 + abs(currentX - destinationX) + abs(currentY - destinationY + 1);

					worldMatrix[currentX][currentY + 1].parentX = currentX;
					worldMatrix[currentX][currentY + 1].parentY = currentY;
				}

				checkBottom = false;
			}
			else if (checkLeft && (*secondIt) == &worldMatrix[currentX - 1][currentY])
			{
				if (worldMatrix[currentX - 1][currentY].pathValue > worldMatrix[currentX][currentY].cost + 1 + abs(currentX - destinationX - 1) + abs(currentY - destinationY))
				{
					worldMatrix[currentX - 1][currentY].pathValue = worldMatrix[currentX][currentY].cost + 1 + abs(currentX - destinationX - 1) + abs(currentY - destinationY);

					worldMatrix[currentX - 1][currentY].parentX = currentX;
					worldMatrix[currentX - 1][currentY].parentY = currentY;
				}

				checkLeft = false;
			}
			else if (checkRight && (*secondIt) == &worldMatrix[currentX + 1][currentY])
			{
				if (worldMatrix[currentX + 1][currentY].pathValue > worldMatrix[currentX][currentY].cost + 1 + abs(currentX - destinationX + 1) + abs(currentY - destinationY))
				{
					worldMatrix[currentX + 1][currentY].pathValue = worldMatrix[currentX][currentY].cost + 1 + abs(currentX - destinationX + 1) + abs(currentY - destinationY);

					worldMatrix[currentX + 1][currentY].parentX = currentX;
					worldMatrix[currentX + 1][currentY].parentY = currentY;
				}

				checkRight = false;
			}
		}




		//check top place
		if (checkTop)
		{
			//estimate the cost (absolute distance betweent start and destination)
			estimatedCost = abs(currentX - destinationX) + abs(currentY - destinationY - 1);

			//calculate the value
			worldMatrix[currentX][currentY - 1].cost = worldMatrix[currentX][currentY].cost + 1;
			worldMatrix[currentX][currentY - 1].pathValue = worldMatrix[currentX][currentY - 1].cost + estimatedCost;

			//add the current place as parent
			worldMatrix[currentX][currentY - 1].parentX = currentX;
			worldMatrix[currentX][currentY - 1].parentY = currentY;

			//add to the open list
			openList.push_front(&worldMatrix[currentX][currentY - 1]);
		}

		//check bottom place
		if (checkBottom)
		{
			//estimate the cost (absolute distance betweent start and destination)
			estimatedCost = abs(currentX - destinationX) + abs(currentY - destinationY + 1);

			//calculate the value
			worldMatrix[currentX][currentY + 1].cost = worldMatrix[currentX][currentY].cost + 1;
			worldMatrix[currentX][currentY + 1].pathValue = worldMatrix[currentX][currentY + 1].cost + estimatedCost;

			//add the current place as parent
			worldMatrix[currentX][currentY + 1].parentX = currentX;
			worldMatrix[currentX][currentY + 1].parentY = currentY;

			//add to the open list
			openList.push_front(&worldMatrix[currentX][currentY + 1]);
		}

		//check left place
		if (checkLeft)
		{
			//estimate the cost (absolute distance betweent start and destination)
			estimatedCost = abs(currentX - destinationX - 1) + abs(currentY - destinationY);

			//calculate the value
			worldMatrix[currentX - 1][currentY].cost = worldMatrix[currentX][currentY].cost + 1;
			worldMatrix[currentX - 1][currentY].pathValue = worldMatrix[currentX - 1][currentY].cost + estimatedCost;

			//add the current place as parent
			worldMatrix[currentX - 1][currentY].parentX = currentX;
			worldMatrix[currentX - 1][currentY].parentY = currentY;

			//add to the open list
			openList.push_front(&worldMatrix[currentX - 1][currentY]);
		}

		//check right place
		if (checkRight)
		{
			//estimate the cost (absolute distance betweent start and destination)
			estimatedCost = abs(currentX - destinationX + 1) + abs(currentY - destinationY);

			//calculate the value
			worldMatrix[currentX + 1][currentY].cost = worldMatrix[currentX][currentY].cost + 1;
			worldMatrix[currentX + 1][currentY].pathValue = worldMatrix[currentX + 1][currentY].cost + estimatedCost;

			//add the current place as parent
			worldMatrix[currentX + 1][currentY].parentX = currentX;
			worldMatrix[currentX + 1][currentY].parentY = currentY;

			//add to the open list
			openList.push_front(&worldMatrix[currentX + 1][currentY]);
		}



		//if no way could be found: return -1
		if (openList.size() <= 0 && currentX != destinationX)
			return Vector2i(-1, -1);


		firstIt = openList.begin();
		currentX = (*firstIt)->matrixXPos;
		currentY = (*firstIt)->matrixYPos;

		//iterate through the open list and seek for the place with the lowest path value
		for (secondIt = openList.begin(); secondIt != openList.end(); secondIt++)
		{
			if ((*secondIt)->pathValue < worldMatrix[currentX][currentY].pathValue)
			{
				currentX = (*secondIt)->matrixXPos;
				currentY = (*secondIt)->matrixYPos;

				firstIt = secondIt;
			}
		}

		//add this place to the closed list and delete it in the open list
		closedList.push_back(&worldMatrix[currentX][currentY]);
		firstIt = openList.erase(firstIt);
	}




	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//					the destination was reached: get the final path											//
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////

	Vector2i nextStep(-1, -1);

	int nextX = -1;
	int nextY = -1;

	while (currentX != startX || currentY != startY)
	{
		nextX = worldMatrix[currentX][currentY].parentX;
		nextY = worldMatrix[currentX][currentY].parentY;

		if (nextX == 0 && nextY == 0)
		{
			checkLeft = true;
		}

		if (nextX == startX && nextY == startY)
		{
			nextStep.x = worldMatrix[currentX][currentY].xPos + blockSize/2;
			nextStep.y = worldMatrix[currentX][currentY].yPos + blockSize/2;
		}

		currentX = nextX;
		currentY = nextY;
	}


	return nextStep;
}




void CNpc::SetFrozen(float _frozenTime)
{
	m_fFrozenTimer = _frozenTime;

	if (m_fFrozenTimer > 0)
		m_State = FROZEN;
}



void CNpc::CheckEffects()
{
	list<SNpcEffect>::iterator i;
	int poison = 0;
	stringstream stream("");

	m_fSecondsTimer -= g_pTimer->GetElapsedTime().asSeconds();

	if (m_fSecondsTimer <= 0)
		m_fSecondsTimer = 1;

	//run through all effects
	for (i = m_Attributes.effects.begin(); i != m_Attributes.effects.end(); i++)
	{
		//reduce the duration
		i->duration -= g_pTimer->GetElapsedTime().asSeconds();

		//check for poison
		if (i->poison > 0)
			poison += i->poison;

		//delete effect, if it is finished
		if (i->duration <= 0)
			i = m_Attributes.effects.erase(i);
	}


	//check if the npc is poisoned
	if (poison > 0 && m_fSecondsTimer == 1)
	{
		m_Attributes.currentHealth -= poison;
		stream << poison;
		g_pSignMachine->AddString(stream.str(), 1, GetRect().left, GetRect().top);
	}
}



void CNpc::PoisonNpc(int _strength, float _duration)
{
	SNpcEffect effect;
	effect.armour = 0;
	effect.speed = 0;
	effect.strength = 0;
	effect.poison = _strength;
	effect.duration = _duration;

	AddEffect(effect);
}