#include "Goblin.hpp"



void CGoblin::Init(int _x, int _y, CWorld *_world, bool _loaded)
{
	m_pWorld = _world;
	m_ID = GOBLIN;

	//Init the sprite
	m_pGoblin = new CLiving3Part;
	//m_pGoblin->Load(&g_pTextures->t_goblin_body, 44, 52, 2, 0, &g_pTextures->t_goblin_arm, 38, 24, 2, &g_pTextures->t_goblin_legs, 40, 35, 12, _x, _y);
	//m_pGoblin->SetPartsPos(-3.0f, 9.0f, 17.0f, 5.0f, -3.0f, 40.0f);
	m_pGoblin->Load(&g_pTextures->t_goblin_body, 50, 64, 2, 0, &g_pTextures->t_goblin_arm, 43, 30, 2, &g_pTextures->t_goblin_legs, 48, 58, 12, _x, _y);
	m_pGoblin->SetPartsPos(-4.0f, 16.0f, 22.0f, 6.5f, -3.0f, 40.0f);
	m_pGoblin->SetArmRotatingPoint(38.0f, 5.0f);
	m_pGoblin->SetHandPosition(8.0f, 16.0f);

	m_fXVel = 0;
	m_fYVel = 0;

	m_fLegsAnimState = 5;

	m_fallingSpeed = 0;

	//Init the attributes
	m_Attributes.maxHealth = 40;
	m_Attributes.armour = 0;
	m_Attributes.speed = 100;
	m_Attributes.strength = 5;
	m_Attributes.exp = 5;

	//Init the state
	m_State = IDLE;
	m_fStateTime = 8;

	if (_loaded)
	{
		m_pGoblin->SetPos(m_xPos, m_yPos);
	}
	else
	{
		m_pGoblin->SetPos(_x, _y);
		m_PointToGo.x = _x;
		m_PointToGo.y = _y;
		m_xPos = _x;
		m_yPos = _y;

		m_left = true;
		m_Attributes.currentHealth = 40;
	}
}




void CGoblin::Quit()
{
	SAFE_DELETE(m_pGoblin);
}




bool CGoblin::CheckNpc()
{
	//Checks/sets the current state
	CheckState();

	//checks the movement in x-direction
	CheckXMovement();
	
	//if the goblin would collide: set the x-velocity to 0
	if (CheckCollision())
		m_fXVel = 0;

	//checks the movement in y-direction
	CheckYMovement();

	//if the goblin would collide: set the y-velocity to 0
	if (CheckCollision())
	{
		m_fYVel = m_fYVel / 2;
		if (CheckCollision())
		{
			m_fYVel = m_fYVel / 2;
			if (CheckCollision())
			{
				m_fYVel = 0;
			}
		}

	}
	m_pGoblin->Move(m_fXVel, m_fYVel);

	//return false if the goblin is outside the world
	if (m_pGoblin->GetRect().left + m_pGoblin->GetRect().width < 0 || m_pGoblin->GetRect().left > m_pWorld->GetDimensions().x*100)
		return false;
	else
		return true;
}




void CGoblin::CheckXMovement()
{
	//is the goblin looking to the left?
	if (m_left)
	{
		//is the goblin going?
		if (m_State == WALKING)
		{
			m_fXVel = -g_pTimer->GetElapsedTime().asSeconds() * m_Attributes.speed;
			m_fLegsAnimState -= 8.0f * (m_Attributes.speed / 100) * g_pTimer->GetElapsedTime().asSeconds();

			//start the animation new if it has reached it's end
			if (m_fLegsAnimState < 0 || m_fLegsAnimState > 6)
				m_fLegsAnimState = 5.99f;

			//if the goblin reached it's destination: wait for a few seconds
			if (m_pGoblin->GetRect().left <= m_PointToGo.x)
			{
				m_fStateTime = rand() % 15 + 5;
				m_State = IDLE;
			}
		}
		//is the goblin doing nothing?
		else if (m_State == IDLE)
		{
			m_fXVel = 0.0f;
			m_fLegsAnimState = 5;
		}

	}
	//is the goblin looking to the right
	else
	{
		//is the goblin going?
		if (m_State == WALKING)
		{
			m_fXVel = g_pTimer->GetElapsedTime().asSeconds() * m_Attributes.speed;
			m_fLegsAnimState += 8.0f * (m_Attributes.speed / 100) * g_pTimer->GetElapsedTime().asSeconds();

			//start the animation new if it has reached it's end
			if (m_fLegsAnimState < 6 || m_fLegsAnimState > 12)
				m_fLegsAnimState = 6;

			if (m_pGoblin->GetRect().left + m_pGoblin->GetRect().width >= m_PointToGo.x)
			{
				m_fStateTime = rand() % 15 + 5;
				m_State = IDLE;
			}
		}
		//is the goblin doing nothing?
		else if (m_State == IDLE)
		{
			m_fXVel = 0.0f;
			m_fLegsAnimState = 6;
		}
	}
}




void CGoblin::CheckYMovement()
{
	//add something to the falling speed if it hasn't reached it's limit
	if (m_fallingSpeed < 200)
	{
		m_fallingSpeed += static_cast<int>(400 * g_pTimer->GetElapsedTime().asSeconds());

		//the normal falling speed is 200
		if (m_fallingSpeed > 200)
			m_fallingSpeed = 200;
	}

	//imitates gravity
	m_fYVel = m_fallingSpeed * g_pTimer->GetElapsedTime().asSeconds();
}



bool CGoblin::CheckCollision()
{
	//the rect, the dwarf would have, if he moved
	FloatRect newPosition;
	newPosition.left = m_pGoblin->GetRect().left + m_fXVel;
	newPosition.top = m_pGoblin->GetRect().top + m_fYVel;
	newPosition.width = (float)m_pGoblin->GetRect().width;
	newPosition.height = (float)m_pGoblin->GetRect().height;

	return m_pWorld->CheckLivingCollision(newPosition);
}


void CGoblin::CheckState()
{
	switch (m_State)
	{
		//if the goblin is idle: check if he should start walking
		case(IDLE) :
		{
			m_fStateTime -= g_pTimer->GetElapsedTime().asSeconds();

			//if the time for being idle is up: seek a new point and start walking towards it
			if (m_fStateTime <= 0)
			{
				m_State = WALKING;

				//get new x distance
				m_PointToGo.x = m_pGoblin->GetRect().left + rand() % 400 + 300;

				//get the pointing way
				if (rand() % 2 == 0)
					m_PointToGo.x *= -1;

				//the point can't be outside the world
				if (m_PointToGo.x < 0)
				{
					m_PointToGo.x /= 2;
				}

				//set the direction
				if (m_PointToGo.x < m_pGoblin->GetRect().left)
				{
					m_left = true;
					m_fLegsAnimState = 5;
				}
				else
				{
					m_left = false;
					m_fLegsAnimState = 6;
				}
			}
		}break;
	}
}



void CGoblin::Render()
{
	if(m_left)
	{
		m_pGoblin->Render(0, m_fLegsAnimState);
		m_pGoblin->RenderSecondPart(0);
	}
	else
	{
		m_pGoblin->Render(1, m_fLegsAnimState);
		m_pGoblin->RenderSecondPart(1);
	}
}





vector<SItem> CGoblin::GetLoot()
{
	vector<SItem> loot;
	loot.clear();

	//add slime
	SItem slime;
	slime.amount = 1;
	CItem* thing = new CItem;
	thing->Init(SLIME);
	slime.thing = thing;
	loot.push_back(slime);

	return loot;
}