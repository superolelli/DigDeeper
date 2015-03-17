#include "Bee.hpp"



void CBee::Init(int _x, int _y, CWorld *_world, bool _loaded)
{
	m_pWorld = _world;
	m_ID = BEE;

	//Init the sprite
	m_pNpcSprite = new CSprite;
	m_pNpcSprite->Load(&g_pTextures->t_bee, 4, 10, 10);

	m_XVel = 0;
	m_YVel = 0;

	//Init the attributes
	m_Attributes.maxHealth = 10;
	m_Attributes.armour = 0;
	m_Attributes.speed = 100;
	m_Attributes.strength = 0;

	//Init the state
	m_State.attacking = false;
	m_State.going = false;
	m_State.idle = true;

	if(_loaded)
	{
		m_pNpcSprite->SetPos(m_xPos, m_yPos);
	}
	else
	{
		m_pNpcSprite->SetPos(_x, _y);
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
	SAFE_DELETE(m_pNpcSprite);
}



bool CBee::CheckNpc()
{
	Vector2i beePos;
	beePos.x = m_pNpcSprite->GetRect().left;
	beePos.y = m_pNpcSprite->GetRect().top;

	//get the x velocity
	if(beePos.x < m_PointToGo.x)
		m_XVel = g_pTimer->GetElapsedTime().asSeconds() * m_Attributes.speed;
	else
		m_XVel = - g_pTimer->GetElapsedTime().asSeconds() * m_Attributes.speed;

	if(CheckCollisions())
	{
		m_XVel = 0;
		NewPointToGo();
	}

	//get the y velocity
	if(beePos.y < m_PointToGo.y)
		m_YVel = g_pTimer->GetElapsedTime().asSeconds() * m_Attributes.speed;
	else
		m_YVel = - g_pTimer->GetElapsedTime().asSeconds() * m_Attributes.speed;

	if(CheckCollisions())
	{
		m_YVel = 0;
		NewPointToGo();
	}

	m_pNpcSprite->Move(m_XVel, m_YVel);
	m_xPos = m_pNpcSprite->GetRect().left;
	m_yPos = m_pNpcSprite->GetRect().top;

	//if bee is outside the world: return false
	if(m_xPos < 0 - m_pNpcSprite->GetRect().width || m_yPos < 0 - m_pNpcSprite->GetRect().height || m_xPos > m_pWorld->GetDimensions().x*100)
		return false;

	//if the bee reached its destiny: get a new destiny
	if(beePos.x - m_PointToGo.x < 2 && beePos.x - m_PointToGo.x > -2 && beePos.y - m_PointToGo.y < 2 && beePos.y - m_PointToGo.y > -2)
	{
		NewPointToGo();
	}

	return true;
}




void CBee::NewPointToGo()
{
	//get new x distance
	m_PointToGo.x = m_pNpcSprite->GetRect().left + rand()%200 + 100;

		//get the pointing way
		if(rand()%2 == 0)
			m_PointToGo.x *= -1;

		//the point can't be outside the world
		if(m_PointToGo.x < 0)
		{
			m_PointToGo.x /= 2;
		}
		
		//get new y distance
		m_PointToGo.y = m_pNpcSprite->GetRect().top + rand()%200 + 100;

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
	newPosition.left   = m_pNpcSprite->GetRect().left + m_XVel;
	newPosition.top    = m_pNpcSprite->GetRect().top + m_YVel;
	newPosition.width  = (float)m_pNpcSprite->GetRect().width;
	newPosition.height = (float)m_pNpcSprite->GetRect().height;

	return(m_pWorld->CheckLivingCollision(newPosition));
}


void CBee::Render()
{
	if(m_left)
		m_pNpcSprite->Render(g_pFramework->GetWindow(), 0.0f);
	else
		m_pNpcSprite->Render(g_pFramework->GetWindow(), 2.0f);
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