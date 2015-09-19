#include "AnimatedAnimal.hpp"
#include "World.hpp"





void CAnimatedAnimal::Init(int _x, int _y, CWorld *_world, CPlayer *_player, View *_view, int _specialID, bool _loaded)
{
	m_pWorld = _world;
	m_pPlayer = _player;
	m_pView = _view;
	m_ID = BUNNY;

	//Init the sprite
	m_pAnimalSprite = new CSprite;
	m_pAnimalSprite->Load(&g_pTextures->t_bunny, 12, 50, 36);

	m_frozenSprite.Load(&g_pTextures->t_ice_bunny);

	m_fXVel = 0;
	m_fYVel = 0;

	m_fAnimState = 5;

	m_safe = false;
	m_jumping = false;

	m_fFrozenTimer = 0;
	m_fIdleTimer = 3;

	m_Attributes = g_pProperties->m_NpcProperties[m_ID];

	//Init the state
	m_State = IDLE;

	if (_loaded)
	{
		m_pAnimalSprite->SetPos(m_xPos, m_yPos);
	}
	else
	{
		m_pAnimalSprite->SetPos(_x, _y);
		m_PointToGo = _x;

		m_xPos = _x;
		m_yPos = _y;

		m_left = true;
		m_Attributes.currentHealth = m_Attributes.maxHealth;
	}
}




void CAnimatedAnimal::Quit()
{
	SAFE_DELETE(m_pAnimalSprite);
}






bool CAnimatedAnimal::CheckCollision()
{
	//the rect, the animal would have, if he moved
	FloatRect newPosition;
	newPosition.left = m_pAnimalSprite->GetRect().left + m_fXVel;
	newPosition.top = m_pAnimalSprite->GetRect().top + m_fYVel;
	newPosition.width = (float)m_pAnimalSprite->GetRect().width;
	newPosition.height = (float)m_pAnimalSprite->GetRect().height;

	return m_pWorld->CheckLivingCollision(newPosition);
}




bool CAnimatedAnimal::CheckNpc()
{
	m_fXVel = 0;
	m_fYVel = 0;

	//Checks/sets the current state
	CheckState();

	//if animal isn't frozen: check movement
	if (m_State != FROZEN)
	{
		//checks the movement in x-direction
		CheckXMovement();

		//if the animal would collide: set the x-velocity to 0
		if (CheckCollision())
		{
			m_fXVel = 0;
		}

		//checks the movement in y-direction
		CheckYMovement();

		//if the animal would collide: set the y-velocity to 0
		if (CheckCollision())
		{
			m_fYVel = m_fYVel / 2;
			if (CheckCollision())
			{
				m_fYVel = m_fYVel / 2;
				if (CheckCollision())
				{
					m_fYVel = 0;
					m_jumping = false;
				}
			}

		}
		else
			m_jumping = true;

		m_pAnimalSprite->Move((int)m_fXVel, (int)m_fYVel);
	}
	else
		m_sideSpeed = 0;

	m_xPos = m_pAnimalSprite->GetRect().left;
	m_yPos = m_pAnimalSprite->GetRect().top;

	//return false if the animal is outside the world
	if (m_pAnimalSprite->GetRect().left + m_pAnimalSprite->GetRect().width < 0 || m_pAnimalSprite->GetRect().left > m_pWorld->GetDimensions().x * 100)
		return false;
	else
		return true;
}





void CAnimatedAnimal::CheckXMovement()
{
	int fleeingSpeed = 0;

	if (m_State == FLEEING)
		fleeingSpeed = 60;

	//regulate the side speed
	if (m_sideSpeed > 0)
		m_sideSpeed -= 200 * g_pTimer->GetElapsedTime().asSeconds();
	else if (m_sideSpeed < 0)
		m_sideSpeed += 200 * g_pTimer->GetElapsedTime().asSeconds();


	if (abs(m_sideSpeed) < 50)
	{
		//is the animal looking to the left?
		if (m_left)
		{
			//is the animal going?
			if (m_State == WALKING || m_State == FLEEING)
			{
				m_fXVel = -g_pTimer->GetElapsedTime().asSeconds() * (m_Attributes.speed + fleeingSpeed);
				m_fAnimState -= 8.0f * ((m_Attributes.speed + fleeingSpeed) / 100) * g_pTimer->GetElapsedTime().asSeconds();

				//start the animation new if it has reached it's end
				if (m_fAnimState < 0 || m_fAnimState >= 6)
					m_fAnimState = 5.99f;

			}
		}
		//is the animal looking to the right
		else
		{
			//is the animal going?
			if (m_State == WALKING || m_State == FLEEING)
			{
				m_fXVel = g_pTimer->GetElapsedTime().asSeconds() * (m_Attributes.speed + fleeingSpeed);
				m_fAnimState += 8.0f * ((m_Attributes.speed + fleeingSpeed) / 100) * g_pTimer->GetElapsedTime().asSeconds();

				//start the animation new if it has reached it's end
				if (m_fAnimState < 6 || m_fAnimState > 12)
					m_fAnimState = 6;

			}
		}
	}


	if (m_sideSpeed != 0)
		m_fXVel += m_sideSpeed * g_pTimer->GetElapsedTime().asSeconds();
}





void CAnimatedAnimal::ThrowNpc(bool _left, int _strength)
{
	if (_left)
		m_sideSpeed = -_strength;
	else
		m_sideSpeed = _strength;

	m_fallingSpeed = -150;

	//set state to fleeing
	m_State = FLEEING;

	//set direction
	if (m_pPlayer->GetRect().left < m_pAnimalSprite->GetRect().left)
	{
		m_left = false;
		m_fAnimState = 6;
	}
	else
	{
		m_left = true;
		m_fAnimState = 5.99f;
	}
}





void CAnimatedAnimal::CheckYMovement()
{
	
	/*if (!m_pWorld->isBlockPassable(m_pAnimalSprite->GetRect().left / 100, m_pAnimalSprite->GetRect().top / 100 + 1))
	{
		m_jumping = true;
		m_fallingSpeed = -350;
	}
*/

	//jump if needed
	if (m_pWorld->CheckForBarrier(m_pAnimalSprite->GetRect(), m_left) && m_pWorld->CheckCanJump(m_pAnimalSprite->GetRect(), m_left) && m_jumping == false)
	{
		m_jumping = true;
		m_fallingSpeed = -350;
	}
	


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







void CAnimatedAnimal::CheckState()
{
	IntRect viewRect;
	viewRect.left = m_pView->getCenter().x - m_pView->getSize().x / 2;
	viewRect.top = m_pView->getCenter().y - m_pView->getSize().y / 2;
	viewRect.width = m_pView->getSize().x;
	viewRect.height = m_pView->getSize().y;

	switch (m_State)
	{
		//if the goblin is idle: check if he should start walking
	case(IDLE) :
	{
		m_fIdleTimer -= g_pTimer->GetElapsedTime().asSeconds();

		//finish animation
		if (m_left && m_fAnimState < 5)
		{
			m_fAnimState -= 8.0f * (m_Attributes.speed / 100) * g_pTimer->GetElapsedTime().asSeconds();

			if (m_fAnimState <= 0)
				m_fAnimState = 5.99f;
		}
		else if (!m_left && m_fAnimState > 6.99)
		{
			m_fAnimState += 8.0f * (m_Attributes.speed / 100) * g_pTimer->GetElapsedTime().asSeconds();

			if (m_fAnimState >= 12)
				m_fAnimState = 6.0f;
		}

		//if the idle timer is up: walk randomly
		if (m_fIdleTimer <= 0)
		{
			NewPointToGo();
			m_State = WALKING;
		}

	}break;

	case(WALKING) :
	{
		//when the destiny was reached: be idle
		if (abs(m_PointToGo - m_pAnimalSprite->GetRect().left) < 5)
		{
			m_fIdleTimer = rand() % 10 + 2;
			m_State = IDLE;
		}

	}break;

	case(FLEEING) :
	{
		//if animal is out of range: set state to idle
		if (abs(m_pAnimalSprite->GetRect().left - m_pPlayer->GetRect().left) > 700)
		{
			m_fIdleTimer = rand() % 10 + 2;
			m_State = IDLE;
		}
	}break;

	case(FROZEN) :
	{
		m_fFrozenTimer -= g_pTimer->GetElapsedTime().asSeconds();

		if (m_fFrozenTimer <= 0)
			m_State = IDLE;
	}break;
	}

}



void CAnimatedAnimal::NewPointToGo()
{
	//get new x distance
	m_PointToGo = m_pAnimalSprite->GetRect().left + rand() % 400 + 300;

	//get the pointing way
	if (rand() % 2 == 0)
		m_PointToGo *= -1;

	//set the direction
	if (m_PointToGo < m_pAnimalSprite->GetRect().left)
	{
		m_left = true;
		m_fAnimState = 5.99f;
	}
	else
	{
		m_left = false;
		m_fAnimState = 6;
	}
}






void CAnimatedAnimal::Render()
{
	
	if (m_left)
		m_pAnimalSprite->Render(g_pFramework->GetRenderWindow(), m_fAnimState);
	else
		m_pAnimalSprite->Render(g_pFramework->GetRenderWindow(), m_fAnimState);

	if (m_State == FROZEN)
	{
		m_frozenSprite.SetPos(m_pAnimalSprite->GetRect().left - 5, m_pAnimalSprite->GetRect().top);
		m_frozenSprite.Render(g_pFramework->GetRenderWindow());
	}
	
}





vector<SItem> CAnimatedAnimal::GetLoot()
{
	vector<SItem> loot;
	loot.clear();

	//add slime
	SItem leather;
	leather.amount = 1;
	CItem* thing = new CItem;
	thing->Init(LEATHER);
	leather.thing = thing;
	loot.push_back(leather);


	return loot;
}





