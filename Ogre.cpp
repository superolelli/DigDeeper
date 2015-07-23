#include "Ogre.hpp"
#include "World.hpp"


void COgre::Init(int _x, int _y, CWorld *_world, CPlayer *_player, View *_view, int _specialID, bool _loaded)
{
	m_pWorld = _world;
	m_pPlayer = _player;
	m_pView = _view;
	m_ID = OGRE;

	//Init the sprite
	m_pOgre = new CLiving3Part;
	
	m_pOgre->Load(&g_pTextures->t_ogre_body, 100, 135, 2, 0, &g_pTextures->t_ogre_arm, 95, 50, 2, &g_pTextures->t_ogre_legs, 90, 65, 12, _x, _y);
	m_pOgre->SetPartsPos(-6.0f, 9.0f, 35.0f, 0.0f, 2.0f, 100.0f);
	m_pOgre->SetArmRotatingPoint(80.0f, 14.0f);
	m_pOgre->SetHandPosition(8.0f, 40.0f);

	m_OgreClub.Load(&g_pTextures->t_ogre_club);
	m_OgreClub.setRotatingPoint(26, 135);

	//Init the attributes
	m_Attributes.maxHealth = 100;
	m_Attributes.armour = 4;
	m_Attributes.speed = 130;
	m_Attributes.strength = 40;
	m_Attributes.exp = 30;

	

	m_fXVel = 0;
	m_fYVel = 0;

	m_fFrozenTimer = 0;

	//m_frozenSprite.Load(&g_pTextures->t_ice_goblin);

	m_fLegsAnimState = 5;
	m_fArmAnimState = 0;

	m_fWaitToBeat = 0;
	m_is_hitting = false;
	m_jumping = false;
	m_is_attacking = false;

	m_fallingSpeed = 0;
	m_sideSpeed = 0;

	//Init the state
	m_State = IDLE;
	m_fStateTime = 8;

	if (_loaded)
	{
		m_pOgre->SetPos(m_xPos, m_yPos);
	}
	else
	{
		m_pOgre->SetPos(_x, _y);
		m_PointToGo.x = _x;
		m_PointToGo.y = _y;
		m_xPos = _x;
		m_yPos = _y;

		m_left = true;
		m_Attributes.currentHealth = m_Attributes.maxHealth;
	}
}




void COgre::Quit()
{
	SAFE_DELETE(m_pOgre);
}



bool COgre::CheckCollision()
{
	//the rect, the ogre would have, if he moved
	FloatRect newPosition;
	newPosition.left = m_pOgre->GetRect().left + m_fXVel;
	newPosition.top = m_pOgre->GetRect().top + m_fYVel;
	newPosition.width = (float)m_pOgre->GetRect().width;
	newPosition.height = (float)m_pOgre->GetRect().height;

	return m_pWorld->CheckLivingCollision(newPosition);
}




bool COgre::CheckNpc()
{
	m_fXVel = 0;
	m_fYVel = 0;

	//Checks/sets the current state
	CheckState();

	//if ogre isn't frozen: check movement
	if (m_State != FROZEN)
	{
		//checks the movement in x-direction
		CheckXMovement();

		//if the ogre would collide: set the x-velocity to 0
		if (CheckCollision())
		{
			m_fXVel = 0;
		}

		//checks the movement in y-direction
		CheckYMovement();

		//if the ogre would collide: set the y-velocity to 0
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

		
		m_pOgre->Move((int)m_fXVel, (int)m_fYVel);
	}
	else
		m_sideSpeed = 0;



	m_xPos = m_pOgre->GetRect().left;
	m_yPos = m_pOgre->GetRect().top;

	//return false if the ogre is outside the world
	if (m_pOgre->GetRect().left + m_pOgre->GetRect().width < 0 || m_pOgre->GetRect().left > m_pWorld->GetDimensions().x * 100)
		return false;
	else
		return true;
}





void COgre::CheckXMovement()
{
	//regulate the side speed
	if (m_sideSpeed > 0)
		m_sideSpeed -= 200 * g_pTimer->GetElapsedTime().asSeconds();
	else if (m_sideSpeed < 0)
		m_sideSpeed += 200 * g_pTimer->GetElapsedTime().asSeconds();

	if (abs(m_sideSpeed) < 50)
	{
		//is the goblin looking to the left?
		if (m_left)
		{
			//is the goblin going?
			if (m_State == WALKING && m_PointToGo.x != m_pOgre->GetRect().left)
			{
				m_fXVel = -g_pTimer->GetElapsedTime().asSeconds() * m_Attributes.speed;
				m_fLegsAnimState -= 8.0f * (m_Attributes.speed / 100) * g_pTimer->GetElapsedTime().asSeconds();

				//start the animation new if it has reached it's end
				if (m_fLegsAnimState < 0 || m_fLegsAnimState > 6)
					m_fLegsAnimState = 5.99f;

			}
		}
		//is the goblin looking to the right
		else
		{
			//is the goblin going?
			if (m_State == WALKING && m_PointToGo.x != m_pOgre->GetRect().left)
			{
				m_fXVel = g_pTimer->GetElapsedTime().asSeconds() * m_Attributes.speed;
				m_fLegsAnimState += 8.0f * (m_Attributes.speed / 100) * g_pTimer->GetElapsedTime().asSeconds();

				//start the animation new if it has reached it's end
				if (m_fLegsAnimState < 6 || m_fLegsAnimState > 12)
					m_fLegsAnimState = 6;

			}
		}
	}


	if (m_sideSpeed != 0)
		m_fXVel += m_sideSpeed * g_pTimer->GetElapsedTime().asSeconds();
}




//an ogre can't be thrown!!!
void COgre::ThrowNpc(bool _left, int _strength)
{
	
}




void COgre::CheckYMovement()
{
	//jump if needed
	if (m_pWorld->CheckForBarrier(m_pOgre->GetRect(), m_left) && m_pWorld->CheckCanJump(m_pOgre->GetRect(), m_left) && m_jumping == false)
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







void COgre::CheckState()
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
		m_fStateTime -= g_pTimer->GetElapsedTime().asSeconds();

		//if the goblin spotted the player: calculate the path and set state to following
		if (m_pOgre->GetRect().intersects(viewRect))
		{
			m_PointToGo = findPath(m_pPlayer->GetRect().left + m_pPlayer->GetRect().width / 2, m_pPlayer->GetRect().top + m_pPlayer->GetRect().height / 2);
			if (m_PointToGo.x != -1 && m_PointToGo.x != m_pOgre->GetRect().left + m_pOgre->GetRect().width / 2)
			{
				m_State = WALKING;

				//set the direction
				if (m_PointToGo.x < m_pOgre->GetRect().left + m_pOgre->GetRect().width / 2)
				{
					m_left = true;
					m_fLegsAnimState = 5;
				}
				else if (m_PointToGo.x > m_pOgre->GetRect().left + m_pOgre->GetRect().width / 2)
				{
					m_left = false;
					m_fLegsAnimState = 6;
				}
			}
			else if (abs(m_pOgre->GetRect().left - m_pPlayer->GetRect().left) > 50 && abs(m_pOgre->GetRect().left - m_pPlayer->GetRect().left) < 120 && abs(m_pOgre->GetRect().top - m_pPlayer->GetRect().top) < 80)
			{
					m_State = WALKING;
			}

		}
		//if the time for being idle is up: seek a new point and start walking towards it
		else if (m_fStateTime <= 0)
		{
			m_State = WALKING;
			NewRandomDestination();
		}

			//if the goblin is near the player: attack
			if (abs(m_pOgre->GetRect().left - m_pPlayer->GetRect().left) < 90 && abs(m_pOgre->GetRect().top - m_pPlayer->GetRect().top) < 90)
				m_State = ATTACKING;
	}break;

	case(WALKING) :
	{
		//if the goblin spotted the player: calculate the path and set state to following
		if (m_pOgre->GetRect().intersects(viewRect))
		{
			m_PointToGo = findPath(m_pPlayer->GetRect().left + m_pPlayer->GetRect().width / 2, m_pPlayer->GetRect().top + m_pPlayer->GetRect().height / 2);

			if (m_PointToGo.x == -1)
			{
				//if player wasn't reached
				if (abs(m_pOgre->GetRect().left - m_pPlayer->GetRect().left) > 60 && abs(m_pOgre->GetRect().left - m_pPlayer->GetRect().left) < 120 && abs(m_pOgre->GetRect().top - m_pPlayer->GetRect().top) < 80)
				{
					m_State = WALKING;
				}
				else
					m_State = IDLE;
			}
			else if (m_PointToGo.x == m_pOgre->GetRect().left + m_pOgre->GetRect().width / 2)
			{
				m_State = IDLE;
				if (m_left)
					m_fLegsAnimState = 5;
				else
					m_fLegsAnimState = 6;
			}
			else
			{
				//set the direction if it has changed
				if (m_PointToGo.x < m_pOgre->GetRect().left + m_pOgre->GetRect().width / 2 && m_left == false)
				{
					m_left = true;
					m_fLegsAnimState = 5;
				}
				else if (m_PointToGo.x > m_pOgre->GetRect().left + m_pOgre->GetRect().width / 2 && m_left == true)
				{
					m_left = false;
					m_fLegsAnimState = 6;
				}
			}

		}

		//if the ogre is near the player: attack
		if (abs(m_pOgre->GetRect().left - m_pPlayer->GetRect().left) < 90 && abs(m_pOgre->GetRect().top - m_pPlayer->GetRect().top) < 90)
			m_State = ATTACKING;
	}break;

	case(ATTACKING) :
	{
		if (m_fWaitToBeat <= 0 && !m_is_attacking)
		{
			m_is_attacking = true;
			m_is_hitting = true;
			m_fArmAnimState = 110;
		}
		else
			m_fWaitToBeat -= g_pTimer->GetElapsedTime().asSeconds();

		//if the ogre isn't near the player: stop attacking
		if (!(abs(m_pOgre->GetRect().left - m_pPlayer->GetRect().left) < 90 && abs(m_pOgre->GetRect().top - m_pPlayer->GetRect().top) < 90))
		{
			m_State = IDLE;
			m_fWaitToBeat = 0;
		}

	}break;

	case(FROZEN) :
	{
		m_fFrozenTimer -= g_pTimer->GetElapsedTime().asSeconds();

		if (m_fFrozenTimer <= 0)
			m_State = IDLE;
	}break;
	}

	CheckArmAnimation();

	if (!m_is_attacking)
		m_pOgre->ResetArmRotation();
}






void COgre::NewRandomDestination()
{
	//get new x distance
	m_PointToGo.x = m_pOgre->GetRect().left + rand() % 400 + 300;

	//get the pointing way
	if (rand() % 2 == 0)
		m_PointToGo.x *= -1;

	//set the direction
	if (m_PointToGo.x < m_pOgre->GetRect().left)
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






void COgre::Render()
{
	m_OgreClub.SetPos(m_pOgre->GetHandPos(m_left).x, m_pOgre->GetHandPos(m_left).y);

	if (m_left)
	{
		m_OgreClub.setRotation(m_fArmAnimState);
		m_pOgre->Render(0, m_fLegsAnimState);
		m_OgreClub.Render(g_pFramework->GetRenderWindow());
		m_pOgre->RenderSecondPart(0);
	}
	else
	{
		m_OgreClub.setRotation(-m_fArmAnimState);
		m_pOgre->Render(1, m_fLegsAnimState);
		m_OgreClub.Render(g_pFramework->GetRenderWindow());
		m_pOgre->RenderSecondPart(1);
	}

	/*if (m_State == FROZEN)
	{
		m_frozenSprite.SetPos(m_pGoblin->GetRect().left - 5, m_pGoblin->GetRect().top);
		m_frozenSprite.Render(g_pFramework->GetRenderWindow());
	}*/
}







vector<SItem> COgre::GetLoot()
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





void COgre::CheckArmAnimation()
{
	if (m_is_attacking)
	{
		//if arm reached lowest point: set arm to highest point
		if (m_fArmAnimState <= -40)
		{
			m_fWaitToBeat = 0.3;
			m_is_attacking = false;
			m_is_hitting = false;
		}

		m_fArmAnimState -= g_pTimer->GetElapsedTime().asSeconds() * 500;

		m_pOgre->RotateArm(m_fArmAnimState);
	}
}




bool COgre::IsHitting()
{
	bool temp;

	temp = m_is_hitting;
	m_is_hitting = false;

	return temp;
}




IntRect COgre::GetWeaponRect()
{
	 return IntRect(m_pOgre->GetHandPos(m_left).x - 5, m_pOgre->GetHandPos(m_left).y - 6, 10, 15);
}