#include "Keykeeper.hpp"
#include "World.hpp"
#include "Effects.hpp"


void CKeyKeeper::Init(int _x, int _y, CWorld *_world, CPlayer *_player, View *_view, int _specialID, bool _loaded)
{
	m_pWorld = _world;
	m_pPlayer = _player;
	m_pView = _view;

	m_ID = KEYKEEPER;


	//load attributes
	m_Attributes = g_pProperties->m_NpcProperties[m_ID];

	//Init the sprite
	m_pKeyKeeper = new CLiving3Part;

	m_pKeyKeeper->Load(&g_pTextures->t_keykeeper_body, 65, 90, 8, 3, &g_pTextures->t_keykeeper_arm, 43, 20, 2, &g_pTextures->t_keykeeper_legs, 20, 20, 1, _x, _y);
	m_pKeyKeeper->SetPartsPos(-30.0f, 42.0f, 40.0f, 13.0f, 30.0f, 75.0f);
	m_pKeyKeeper->SetArmRotatingPoint(38.0f, 5.0f);
	m_pKeyKeeper->SetHandPosition(5.0f, 11.0f);


	m_fXVel = 0;
	m_fYVel = 0;

	m_fFrozenTimer = 0;

	m_frozenSprite.Load(&g_pTextures->t_ice_goblin);

	m_fFlamesAnimState = 3.99f;
	m_fArmAnimState = 0;

	m_fWaitToBeat = 0;
	m_is_hitting = false;
	m_jumping = false;
	m_is_attacking = false;
	m_flamesDown = true;

	m_fallingSpeed = 0;
	m_sideSpeed = 0;

	nextStepDirection = 0;

	//Init the state
	m_State = IDLE;
	m_fStateTime = 8;

	if (_loaded)
	{
		m_pKeyKeeper->SetPos(m_xPos, m_yPos);
	}
	else
	{
		m_pKeyKeeper->SetPos(_x, _y);
		m_PointToGo.x = _x;
		m_PointToGo.y = _y;
		m_xPos = _x;
		m_yPos = _y;

		m_left = true;
		m_Attributes.currentHealth = m_Attributes.maxHealth;
		m_Attributes.effects.clear();
		m_safe = false;
	}
}




void CKeyKeeper::Quit()
{
	SAFE_DELETE(m_pKeyKeeper);
}




bool CKeyKeeper::CheckCollision()
{
	//the rect, the keeper would have, if he moved
	FloatRect newPosition;
	newPosition.left = m_pKeyKeeper->GetRect().left + m_fXVel;
	newPosition.top = m_pKeyKeeper->GetRect().top + m_fYVel;
	newPosition.width = (float)m_pKeyKeeper->GetRect().width;
	newPosition.height = (float)m_pKeyKeeper->GetRect().height;

	return m_pWorld->CheckLivingCollision(newPosition);
}




bool CKeyKeeper::CheckNpc()
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

		
		m_pKeyKeeper->Move((int)m_fXVel, (int)m_fYVel);
	}
	else
		m_sideSpeed = 0;

	m_xPos = m_pKeyKeeper->GetRect().left;
	m_yPos = m_pKeyKeeper->GetRect().top;

	//return false if the goblin is outside the world
	if (m_pKeyKeeper->GetRect().left + m_pKeyKeeper->GetRect().width < 0 || m_pKeyKeeper->GetRect().left > m_pWorld->GetDimensions().x * 100)
		return false;
	else
		return true;
}



void CKeyKeeper::CheckXMovement()
{
	//regulate the side speed
	if (m_sideSpeed > 0)
		m_sideSpeed -= 200 * g_pTimer->GetElapsedTime().asSeconds();
	else if (m_sideSpeed < 0)
		m_sideSpeed += 200 * g_pTimer->GetElapsedTime().asSeconds();

	if (abs(m_sideSpeed) < 50)
	{
		//is the keeper looking to the left?
		if (m_left)
		{
			//is the keeper going?
			if (m_State == WALKING && nextStepDirection == 0)
				m_fXVel = -g_pTimer->GetElapsedTime().asSeconds() * m_Attributes.speed;		
		}
		//is the keeper looking to the right
		else
		{
			//is the keeper going?
			if (m_State == WALKING && nextStepDirection == 2)
				m_fXVel = g_pTimer->GetElapsedTime().asSeconds() * m_Attributes.speed;
		}
	}


	if (m_sideSpeed != 0)
		m_fXVel += m_sideSpeed * g_pTimer->GetElapsedTime().asSeconds();
}



void CKeyKeeper::ThrowNpc(bool _left, int _strength)
{
	if (_left)
		m_sideSpeed = -_strength;
	else
		m_sideSpeed = _strength;

	m_fallingSpeed = -200;

	if (rand() % 2 == 0)
		Teleport();
}



void CKeyKeeper::CheckYMovement()
{

	if (nextStepDirection == 1 && m_jumping == false)
	{
		m_jumping = true;
		m_fallingSpeed = -350;
	}

	//jump if needed
	if (m_pWorld->CheckForBarrier(m_pKeyKeeper->GetRect(), m_left) && m_pWorld->CheckCanJump(m_pKeyKeeper->GetRect(), m_left) && m_jumping == false)
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




void CKeyKeeper::CheckState()
{
	IntRect viewRect;
	viewRect.left = m_pView->getCenter().x - m_pView->getSize().x / 2;
	viewRect.top = m_pView->getCenter().y - m_pView->getSize().y / 2;
	viewRect.width = m_pView->getSize().x;
	viewRect.height = m_pView->getSize().y;

	switch (m_State)
	{
		//if the keeper is idle: check if he should start walking
	case(IDLE) :
	{	
		//if the goblin spotted the player: calculate the path and set state to following
		if (m_pKeyKeeper->GetRect().intersects(viewRect))
		{
			m_State = WALKING;
		}		

	}break;
	case(WALKING) :
	case(ATTACKING) :
	{
		//get next step to player
		m_PointToGo = findPath(m_pPlayer->GetRect().left + m_pPlayer->GetRect().width / 2, m_pPlayer->GetRect().top + m_pPlayer->GetRect().height / 2);

		//if goblin can't reach the player: just stand 
		if (m_PointToGo.x == -1)
		{
			if (abs(m_pKeyKeeper->GetRect().left - m_pPlayer->GetRect().left) < 90)
			{
				if (m_pKeyKeeper->GetRect().left < m_pPlayer->GetRect().left)
					nextStepDirection = 2;
				else
					nextStepDirection = 0;
			}
			else
				m_State = IDLE;
		}
		else
		{
			//check direction of the next step
			if (m_PointToGo.x / 100 > m_pKeyKeeper->GetRect().left / 100)
			{
				nextStepDirection = 2;
				m_left = false;
			}
			else if (m_PointToGo.x / 100 < m_pKeyKeeper->GetRect().left / 100)
			{
				nextStepDirection = 0;
				m_left = true;
			}
			else if (m_PointToGo.y / 100 > m_pKeyKeeper->GetRect().top / 100)
				nextStepDirection = 3;
			else if (m_PointToGo.y / 100 < m_pKeyKeeper->GetRect().top / 100)
				nextStepDirection = 1;
			else
				m_State = IDLE;
		}


		//check if the goblin is attacking
		if (abs(m_pKeyKeeper->GetRect().top - m_pPlayer->GetRect().top) < 50 && abs(m_pKeyKeeper->GetRect().left - m_pPlayer->GetRect().left) < 650 && FreeLineOfSight())
			m_State = ATTACKING;

		//check if the goblin is attacking
		if (m_State == ATTACKING)
		{
			if (m_fWaitToBeat <= 0 && !m_is_attacking)
			{
				m_is_attacking = true;
				m_is_hitting = true;
				m_fArmAnimState = 110;
			}
			else
				m_fWaitToBeat -= g_pTimer->GetElapsedTime().asSeconds();

			//if the goblin isn't near the player: stop attacking
			if (abs(m_pKeyKeeper->GetRect().top - m_pPlayer->GetRect().top) >= 50 || abs(m_pKeyKeeper->GetRect().left - m_pPlayer->GetRect().left) >= 650 || !FreeLineOfSight())
			{
				m_State = WALKING;
				m_fWaitToBeat = 0;
			}
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
		m_pKeyKeeper->ResetArmRotation();
}




void CKeyKeeper::Render()
{
	if (m_left)
	{
		//if keeper is not frozen: change the flames
		if (m_State != FROZEN)
		{
			// add to the anim state
			if (m_flamesDown)
			{
				m_fFlamesAnimState -= 10 * g_pTimer->GetElapsedTime().asSeconds();

				if (m_fFlamesAnimState <= 0)
				{
					m_fFlamesAnimState = 0;
					m_flamesDown = false;
				}

			}
			else
			{

				m_fFlamesAnimState += 10 * g_pTimer->GetElapsedTime().asSeconds();

				if (m_fFlamesAnimState >= 3.99f)
				{
					m_fFlamesAnimState = 3.99f;
					m_flamesDown = true;
				}
			}
		}

		m_pKeyKeeper->Render(m_fFlamesAnimState, 0);
		m_pKeyKeeper->RenderSecondPart(0);
	}
	else
	{
		if (m_State != FROZEN)
		{
			if (m_flamesDown)
			{

				m_fFlamesAnimState -= 10 * g_pTimer->GetElapsedTime().asSeconds();

				if (m_fFlamesAnimState <= 4.0f)
				{
					m_fFlamesAnimState = 4.0f;
					m_flamesDown = false;
				}
			}
			else
			{
				m_fFlamesAnimState += 10 * g_pTimer->GetElapsedTime().asSeconds();

				if (m_fFlamesAnimState >= 7.99)
				{
					m_fFlamesAnimState = 7.99f;
					m_flamesDown = true;
				}
			}
		}

		//render the keeper
		m_pKeyKeeper->Render(m_fFlamesAnimState, 0);
		m_pKeyKeeper->RenderSecondPart(1);
	}

	//if frozen: render the ice block
	if (m_State == FROZEN)
	{
		m_frozenSprite.SetPos(m_pKeyKeeper->GetRect().left - 5, m_pKeyKeeper->GetRect().top);
		m_frozenSprite.Render(g_pFramework->GetRenderWindow());
	}
}





vector<SItem> CKeyKeeper::GetLoot()
{
	vector<SItem> loot;
	loot.clear();

	//add slime
	SItem key;
	key.amount = 1;
	CItem* thing = new CItem;
	thing->Init(KEY);
	key.thing = thing;
	loot.push_back(key);

	return loot;
}




void CKeyKeeper::CheckArmAnimation()
{
	if (m_is_attacking)
	{
		//if arm reached lowest point: set arm to highest point
		if (m_fArmAnimState <= -40)
		{
			m_fWaitToBeat = 3;

			//choose the attack
			switch (rand() % 3)
			{
			case(0) :
				ThrowMultipleFireballs();
				break;
			case(1) :
				CreateSkeleton();
				break;
			case(2) :
				ThrowPoisonBall();
				break;
			}

			m_is_attacking = false;
			m_is_hitting = false;
		}

		m_fArmAnimState -= g_pTimer->GetElapsedTime().asSeconds() * 500;

		m_pKeyKeeper->RotateArm(m_fArmAnimState);
	}
}




bool CKeyKeeper::IsHitting()
{
	bool temp;

	temp = m_is_hitting;
	m_is_hitting = false;

	return temp;
}




IntRect CKeyKeeper::GetWeaponRect()
{
	return IntRect(m_pKeyKeeper->GetHandPos(m_left).x - 5, m_pKeyKeeper->GetHandPos(m_left).y - 5, 10, 10);
}





void CKeyKeeper::ThrowFireball()
{
	SProjectile projectile;

	//add a projectile
	CSprite *sprite = new CSprite;

	if (m_left)
	{
		projectile.m_fXVel = -200;
		sprite->Load(&g_pTextures->t_fireballLeft);
	}
	else
	{
		projectile.m_fXVel = 200;
		sprite->Load(&g_pTextures->t_fireballRight);
	}

	sprite->SetPos(GetWeaponRect().left - sprite->GetRect().width / 2, GetWeaponRect().top - sprite->GetRect().height / 2);

	projectile.m_ID = FIREBALLPROJECTILE;
	projectile.m_Damage = 10;
	projectile.m_fFlown = 0.0f;
	projectile.m_flightLength = 600;
	projectile.m_fromPlayer = false;
	projectile.m_fYVel = 0.0f;
	projectile.m_Sprite = sprite;
	projectile.m_fAnimState = -1;

	g_pProjectiles->NewProjectile(projectile);
}



void CKeyKeeper::ThrowMultipleFireballs()
{
	for (int i = 0; i < 5; i++)
	{
		SProjectile projectile;

		//add a projectile
		CSprite *sprite = new CSprite;

		switch (i)
		{
		case(0) :
			projectile.m_fXVel = -200;
			projectile.m_fYVel = 0;
			sprite->Load(&g_pTextures->t_fireballLeft);
			break;

		case(1):
			projectile.m_fXVel = -100;
			projectile.m_fYVel = -100;
			sprite->Load(&g_pTextures->t_fireballLeft);
			sprite->rotate(45);
			break;

		case(2) :
			projectile.m_fXVel = 0;
			projectile.m_fYVel = -200;
			sprite->Load(&g_pTextures->t_fireballLeft);
			sprite->rotate(90);
			break;

		case(3) :
			projectile.m_fXVel = 100;
			projectile.m_fYVel = -100;
			sprite->Load(&g_pTextures->t_fireballRight);
			sprite->rotate(315);
			break;

		case(4) :
			projectile.m_fXVel = 200;
			projectile.m_fYVel = 0;
			sprite->Load(&g_pTextures->t_fireballRight);
			break;
		}

		sprite->SetPos(GetWeaponRect().left - sprite->GetRect().width / 2, GetWeaponRect().top - sprite->GetRect().height / 2);

		projectile.m_ID = FIREBALLPROJECTILE;
		projectile.m_Damage = 10;
		projectile.m_fFlown = 0.0f;
		projectile.m_flightLength = 600;
		projectile.m_fromPlayer = false;
		projectile.m_Sprite = sprite;
		projectile.m_fAnimState = -1;

		g_pProjectiles->NewProjectile(projectile);
	}
}





void CKeyKeeper::ThrowPoisonBall()
{
	SProjectile projectile;

	//add a projectile
	CSprite *sprite = new CSprite;

	if (m_left)
	{
		projectile.m_fXVel = -200;
		sprite->Load(&g_pTextures->t_poisonballLeft);
	}
	else
	{
		projectile.m_fXVel = 200;
		sprite->Load(&g_pTextures->t_poisonballRight);
	}

	sprite->SetPos(GetWeaponRect().left - sprite->GetRect().width / 2, GetWeaponRect().top - sprite->GetRect().height / 2);

	projectile.m_ID = POISONBALL;
	projectile.m_Damage = 2;
	projectile.m_fFlown = 0.0f;
	projectile.m_flightLength = 600;
	projectile.m_fromPlayer = false;
	projectile.m_fYVel = 0.0f;
	projectile.m_Sprite = sprite;
	projectile.m_fAnimState = -1;

	g_pProjectiles->NewProjectile(projectile);
}




void CKeyKeeper::CreateSkeleton()
{
	int x;
	int y = m_pKeyKeeper->GetRect().top - 9;
	bool place_found = false;
	int counter = 0;

	while (place_found == false)
	{
		x = m_pKeyKeeper->GetRect().left;

		if (rand() % 2 == 0)
			x += rand() % 500;	
		else
			x -= rand() % 500;

		if (m_pWorld->isBlockPassable(x / 100, y / 100))
			place_found = true;

		counter++;

		if (counter > 5)
			return;
	}

	m_pWorld->AddNpc(GOBLIN, x, y, false, rand()%3+ 7);


	g_pEffects->AddEffect(CREATEEFFECT, x, y, NULL, NULL);
}




void CKeyKeeper::Teleport()
{
	int x;
	int counter = 0;

	while (counter < 5)
	{
		x = m_pKeyKeeper->GetRect().left;

		if (rand() % 2 == 0)
			x += (rand() % 5 + 1) * 100;
		else
			x -= (rand() % 5 + 1) * 100;

		if (m_pWorld->isBlockPassable(x / 100, m_pKeyKeeper->GetRect().top / 100))
		{
			m_pKeyKeeper->SetPos(x, m_pKeyKeeper->GetRect().top);

			g_pEffects->AddEffect(TELEPORTEFFECT, x, m_pKeyKeeper->GetRect().top, NULL, NULL);

			return;
		}

		counter++;
	}
	
}



bool CKeyKeeper::FreeLineOfSight()
{
	int x = m_pKeyKeeper->GetRect().left / 100;
	int y = m_pKeyKeeper->GetRect().top / 100;
	bool freeLine = true;

	while (x != m_pPlayer->GetRect().left / 100)
	{
		if (!m_pWorld->isBlockPassable(x, y))
			freeLine = false;

		if (m_pPlayer->GetRect().left < m_pKeyKeeper->GetRect().left)
			x--;
		else
			x++;
	}

	return freeLine;
}