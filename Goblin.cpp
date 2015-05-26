#include "Goblin.hpp"
#include "World.hpp"


void CGoblin::Init(int _x, int _y, CWorld *_world, CPlayer *_player, View *_view, bool _loaded)
{
	m_pWorld = _world;
	m_pPlayer = _player;
	m_pView = _view;
	m_ID = GOBLIN;

	if (!_loaded)
		m_goblinType = rand() % 3 + 1;

	//Init the sprite
	m_pGoblin = new CLiving3Part;
	if (m_goblinType == NORMALGOBLIN)
	{
		m_pGoblin->Load(&g_pTextures->t_goblin_body, 50, 64, 2, 0, &g_pTextures->t_goblin_arm, 43, 30, 2, &g_pTextures->t_goblin_legs, 48, 58, 12, _x, _y);
		m_pGoblin->SetPartsPos(-4.0f, 16.0f, 22.0f, 6.5f, -3.0f, 40.0f);
		m_pGoblin->SetArmRotatingPoint(38.0f, 5.0f);
		m_pGoblin->SetHandPosition(8.0f, 16.0f);

		//Init the attributes
		m_Attributes.maxHealth = 40;
		m_Attributes.armour = 0;
		m_Attributes.speed = 150;
		m_Attributes.strength = 10;
		m_Attributes.exp = 5;

	}
	else if (m_goblinType == WARRIORGOBLIN)
	{
		m_pGoblin->Load(&g_pTextures->t_goblin_body2, 50, 64, 2, 0, &g_pTextures->t_goblin_arm2, 43, 35, 2, &g_pTextures->t_goblin_legs, 48, 58, 12, _x, _y);
		m_pGoblin->SetPartsPos(-4.0f, 16.0f, 22.0f, 6.5f, -3.0f, 40.0f);
		m_pGoblin->SetArmRotatingPoint(38.0f, 5.0f);
		m_pGoblin->SetHandPosition(10.0f, 17.0f);

		//Init the attributes
		m_Attributes.maxHealth = 40;
		m_Attributes.armour = 0;
		m_Attributes.speed = 180;
		m_Attributes.strength = 20;
		m_Attributes.exp = 15;
	}
	else
	{
		m_pGoblin->Load(&g_pTextures->t_goblin_body3, 53, 68, 2, 0, &g_pTextures->t_goblin_arm3, 39, 54, 2, &g_pTextures->t_goblin_legs2, 48, 53, 12, _x, _y);
		m_pGoblin->SetPartsPos(-4.0f, 16.0f, 0.0f, 3.0f, 1.0f, 45.0f);
		m_pGoblin->SetArmRotatingPoint(33.0f, 29.0f);
		m_pGoblin->SetHandPosition(6.0f, 42.0f);

		//Init the attributes
		m_Attributes.maxHealth = 70;
		m_Attributes.armour = 10;
		m_Attributes.speed = 130;
		m_Attributes.strength = 15;
		m_Attributes.exp = 15;
	}

	m_fXVel = 0;
	m_fYVel = 0;

	m_fFrozenTimer = 0;

	m_frozenSprite.Load(&g_pTextures->t_ice_goblin);

	m_fLegsAnimState = 5;
	m_fArmAnimState = 0;

	m_fWaitToBeat = 0;
	m_is_hitting = false;
	m_jumping = false;

	m_fallingSpeed = 0;
	m_sideSpeed = 0;

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
		m_Attributes.currentHealth = m_Attributes.maxHealth;
	}
}




void CGoblin::Quit()
{
	SAFE_DELETE(m_pGoblin);
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




bool CGoblin::CheckNpc()
{
		m_fXVel = 0;
		m_fYVel = 0;

		//Checks/sets the current state
		CheckState();
	
		//if goblin isn't frozen: check movement
		if (m_State != FROZEN)
		{
			//checks the movement in x-direction
			CheckXMovement();

			//if the goblin would collide: set the x-velocity to 0
			if (CheckCollision())
			{
				m_fXVel = 0;
			}

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
						m_jumping = false;
					}
				}

			}
			m_pGoblin->Move((int)m_fXVel, (int)m_fYVel);
		}
		else
			m_sideSpeed = 0;
	
		m_xPos = m_pGoblin->GetRect().left;
		m_yPos = m_pGoblin->GetRect().top;
	
		//return false if the goblin is outside the world
		if (m_pGoblin->GetRect().left + m_pGoblin->GetRect().width < 0 || m_pGoblin->GetRect().left > m_pWorld->GetDimensions().x*100)
			return false;
		else
			return true;
}



void CGoblin::CheckXMovement()
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
			if (m_State == WALKING && m_PointToGo.x != m_pGoblin->GetRect().left)
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
			if (m_State == WALKING && m_PointToGo.x != m_pGoblin->GetRect().left)
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



void CGoblin::ThrowNpc(bool _left, int _strength)
{
	if (_left)
		m_sideSpeed = -_strength;
	else
		m_sideSpeed = _strength;

	m_fallingSpeed = -200;
}


void CGoblin::CheckYMovement()
{
	//jump if needed
	if (m_pWorld->CheckForBarrier(m_pGoblin->GetRect(), m_left) && m_pWorld->CheckCanJump(m_pGoblin->GetRect(), m_left) && m_jumping == false)
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




void CGoblin::CheckState()
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
			cout << "Idle" << endl;

			m_fStateTime -= g_pTimer->GetElapsedTime().asSeconds();


			//if the goblin spotted the player: calculate the path and set state to following
			if (m_pGoblin->GetRect().intersects(viewRect))
			{
				m_PointToGo = findPath(m_pPlayer->GetRect().left + m_pPlayer->GetRect().width / 2, m_pPlayer->GetRect().top + m_pPlayer->GetRect().height / 2);
				if (m_PointToGo.x != -1 && m_PointToGo.x != m_pGoblin->GetRect().left + m_pGoblin->GetRect().width / 2)
				{
					m_State = WALKING;

					//set the direction
					if (m_PointToGo.x < m_pGoblin->GetRect().left + m_pGoblin->GetRect().width / 2)
					{
						m_left = true;
						m_fLegsAnimState = 5;
					}
					else if (m_PointToGo.x > m_pGoblin->GetRect().left + m_pGoblin->GetRect().width / 2)
					{
						m_left = false;
						m_fLegsAnimState = 6;
					}
				} 
				else if (abs(m_pGoblin->GetRect().left - m_pPlayer->GetRect().left) > 50 && abs(m_pGoblin->GetRect().left - m_pPlayer->GetRect().left) < 120 && abs(m_pGoblin->GetRect().top - m_pPlayer->GetRect().top) < 80)
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
			if (abs(m_pGoblin->GetRect().left - m_pPlayer->GetRect().left) < 50 && abs(m_pGoblin->GetRect().top - m_pPlayer->GetRect().top) < 50)
				m_State = ATTACKING;		

		}break;
		case(WALKING):
		{

			cout << "walking" << endl;
			//if the goblin spotted the player: calculate the path and set state to following
			if (m_pGoblin->GetRect().intersects(viewRect))
			{
				m_PointToGo = findPath(m_pPlayer->GetRect().left + m_pPlayer->GetRect().width / 2, m_pPlayer->GetRect().top + m_pPlayer->GetRect().height / 2);

				if (m_PointToGo.x == -1)
				{
					//if player wasn't reached
					if (abs(m_pGoblin->GetRect().left - m_pPlayer->GetRect().left) > 50 && abs(m_pGoblin->GetRect().left - m_pPlayer->GetRect().left) < 120 && abs(m_pGoblin->GetRect().top - m_pPlayer->GetRect().top) < 80)
					{
						m_State = WALKING;
					}
					else
						m_State = IDLE;
				}
				else if (m_PointToGo.x == m_pGoblin->GetRect().left + m_pGoblin->GetRect().width / 2)
				{
					m_State = IDLE;
					if (m_left)
						m_fLegsAnimState = 5;
					else
						m_fLegsAnimState = 6;
				}
				else
				{
					cout << "XPoint: " << m_PointToGo.x << endl;

					//set the direction if it has changed
					if (m_PointToGo.x < m_pGoblin->GetRect().left + m_pGoblin->GetRect().width / 2 && m_left == false)
					{
						m_left = true;
						m_fLegsAnimState = 5;
					}
					else if (m_PointToGo.x > m_pGoblin->GetRect().left + m_pGoblin->GetRect().width / 2 && m_left == true)
					{
						m_left = false;
						m_fLegsAnimState = 6;
					}
				}	

			}

			//if the goblin is near the player: attack
			if (abs(m_pGoblin->GetRect().left - m_pPlayer->GetRect().left) < 50 && abs(m_pGoblin->GetRect().top - m_pPlayer->GetRect().top) < 50)
				m_State = ATTACKING;
		}break;

		case(ATTACKING) :
		{
			cout << "attacking" << endl;
			//if the goblin is near the player: attack
			if (abs(m_pGoblin->GetRect().left - m_pPlayer->GetRect().left) < 50 && abs(m_pGoblin->GetRect().top - m_pPlayer->GetRect().top) < 50)
			{
				CheckArmAnimation();
			}
			else
			{
				m_State = IDLE;
				m_fWaitToBeat = 0;
				m_pGoblin->ResetArmRotation();
			}

		}break;

		case(FROZEN):
		{
			m_fFrozenTimer -= g_pTimer->GetElapsedTime().asSeconds();

			if (m_fFrozenTimer <= 0)
				m_State = IDLE;
		}break;
	}
}




void CGoblin::NewRandomDestination()
{
	//get new x distance
	m_PointToGo.x = m_pGoblin->GetRect().left + rand() % 400 + 300;

	//get the pointing way
	if (rand() % 2 == 0)
		m_PointToGo.x *= -1;

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

	if (m_State == FROZEN)
	{
		m_frozenSprite.SetPos(m_pGoblin->GetRect().left - 5, m_pGoblin->GetRect().top);
		m_frozenSprite.Render(g_pFramework->GetWindow());
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




void CGoblin::CheckArmAnimation()
{
	if (m_fWaitToBeat <= 0)
	{
		//if arm reached lowest point: set arm to highest point
		if (m_fArmAnimState <= -40)
		{
			m_fArmAnimState = 110;
			m_fWaitToBeat = 0.6;
			m_is_hitting = true;
		}

		m_fArmAnimState -= g_pTimer->GetElapsedTime().asSeconds() * 500;

		m_pGoblin->RotateArm(m_fArmAnimState);
	}
	else
		m_fWaitToBeat -= g_pTimer->GetElapsedTime().asSeconds();
}




bool CGoblin::IsHitting()
{
	bool temp;

	temp = m_is_hitting;
	m_is_hitting = false;

	return temp;
}




IntRect CGoblin::GetWeaponRect()
{
	switch (m_goblinType)
	{
	case(NORMALGOBLIN):
		return IntRect(m_pGoblin->GetHandPos(m_left).x - 5, m_pGoblin->GetHandPos(m_left).y - 5, 10, 10);
		break;
	case(WARRIORGOBLIN) :
		return IntRect(m_pGoblin->GetHandPos(m_left).x - 5, m_pGoblin->GetHandPos(m_left).y, 10, 17);
		break;
	case(KNIGHTGOBLIN) :
		return IntRect(m_pGoblin->GetHandPos(m_left).x + 3, m_pGoblin->GetHandPos(m_left).y - 42, 20, 17);
		break;
	default:
		return IntRect(0, 0, 0, 0);
		break;
	}
}