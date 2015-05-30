#include "Bee.hpp"
#include "World.hpp"


void CBee::Init(int _x, int _y, CWorld *_world, CPlayer *_player, View *_view, int _specialID, bool _loaded)
{
	m_pWorld = _world;
	m_pPlayer = _player;
	m_pView = _view;
	m_ID = BEE;

	//Init the sprite
	m_pBeeSprite = new CSprite;
	m_pBeeSprite->Load(&g_pTextures->t_bee, 4, 10, 10);

	m_frozenSprite.Load(&g_pTextures->t_ice_bee);

	m_XVel = 0;
	m_YVel = 0;

	m_fFrozenTimer = 0;

	//Init the attributes
	m_Attributes.maxHealth = 20;
	m_Attributes.armour = 0;
	m_Attributes.speed = 100;
	m_Attributes.strength = 0;
	m_Attributes.exp = 1;

	//Init the state
	m_State = IDLE;

	if(_loaded)
	{
		m_pBeeSprite->SetPos(m_xPos, m_yPos);
	}
	else
	{
		m_pBeeSprite->SetPos(_x, _y);
		m_PointToGo.x = _x;
		m_PointToGo.y = _y;
		m_xPos = _x;
		m_yPos = _y;

		m_left = true;
		m_Attributes.currentHealth = 20;
	}
}



void CBee::Quit()
{
	SAFE_DELETE(m_pBeeSprite);
}



bool CBee::CheckNpc()
{
	if (m_State != FROZEN)
	{
		Vector2i beePos;
		beePos.x = m_pBeeSprite->GetRect().left;
		beePos.y = m_pBeeSprite->GetRect().top;

		//get the x velocity
		if (beePos.x < m_PointToGo.x)
			m_XVel = g_pTimer->GetElapsedTime().asSeconds() * m_Attributes.speed;
		else
			m_XVel = -g_pTimer->GetElapsedTime().asSeconds() * m_Attributes.speed;

		if (CheckCollisions())
		{
			m_XVel = 0;
			NewPointToGo();
		}

		//get the y velocity
		if (beePos.y < m_PointToGo.y)
			m_YVel = g_pTimer->GetElapsedTime().asSeconds() * m_Attributes.speed;
		else
			m_YVel = -g_pTimer->GetElapsedTime().asSeconds() * m_Attributes.speed;

		if (CheckCollisions())
		{
			m_YVel = 0;
			NewPointToGo();
		}

		m_pBeeSprite->Move(m_XVel, m_YVel);
		m_xPos = m_pBeeSprite->GetRect().left;
		m_yPos = m_pBeeSprite->GetRect().top;

		//if bee is outside the world: return false
		if (m_xPos < 0 - m_pBeeSprite->GetRect().width || m_yPos < 0 - m_pBeeSprite->GetRect().height || m_xPos > m_pWorld->GetDimensions().x * 100)
			return false;

		//if the bee reached its destiny: get a new destiny
		if (beePos.x - m_PointToGo.x < 2 && beePos.x - m_PointToGo.x > -2 && beePos.y - m_PointToGo.y < 2 && beePos.y - m_PointToGo.y > -2)
		{
			NewPointToGo();
		}
	}
	else
	{
		m_fFrozenTimer -= g_pTimer->GetElapsedTime().asSeconds();

		if (m_fFrozenTimer <= 0)
			m_State = IDLE;
	}

	return true;
}




void CBee::NewPointToGo()
{
	//get new x distance
	m_PointToGo.x = m_pBeeSprite->GetRect().left + rand()%200 + 100;

		//get the pointing way
		if(rand()%2 == 0)
			m_PointToGo.x *= -1;

		//the point can't be outside the world
		if(m_PointToGo.x < 0)
		{
			m_PointToGo.x /= 2;
		}

		if(m_PointToGo.x < m_pBeeSprite->GetRect().left)
			m_left = true;
		else
			m_left = false;
		
		//get new y distance
		m_PointToGo.y = m_pBeeSprite->GetRect().top + rand()%200 + 100;

		//get the pointing way
		if(rand()%2 == 0)
			m_PointToGo.y *= -1;

		//The point can't be outside the world
		if(m_PointToGo.y < 0)
		{
			m_PointToGo.y /= 2;
		}
}




bool CBee::CheckCollisions()
{
	//the rect, the bee would have, if he moved
	FloatRect newPosition;
	newPosition.left   = m_pBeeSprite->GetRect().left + m_XVel;
	newPosition.top    = m_pBeeSprite->GetRect().top + m_YVel;
	newPosition.width  = (float)m_pBeeSprite->GetRect().width;
	newPosition.height = (float)m_pBeeSprite->GetRect().height;

	return(m_pWorld->CheckLivingCollision(newPosition));
}


void CBee::Render()
{
	if(m_left)
		m_pBeeSprite->Render(g_pFramework->GetRenderWindow(), 0.0f);
	else
		m_pBeeSprite->Render(g_pFramework->GetRenderWindow(), 2.0f);

	if (m_State == FROZEN)
	{
		m_frozenSprite.SetPos(m_pBeeSprite->GetRect().left, m_pBeeSprite->GetRect().top);
		m_frozenSprite.Render(g_pFramework->GetRenderWindow());
	}
}





vector<SItem> CBee::GetLoot()
{
	vector<SItem> loot;
	loot.clear();

	//add wax
	SItem wax;
	wax.amount = 1;
	CItem* thing = new CItem;
	thing->Init(WAX);
	wax.thing = thing;
	loot.push_back(wax);

	return loot;
}