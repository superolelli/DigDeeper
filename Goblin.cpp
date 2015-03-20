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

	//Init the attributes
	m_Attributes.maxHealth = 40;
	m_Attributes.armour = 0;
	m_Attributes.speed = 100;
	m_Attributes.strength = 5;
	m_Attributes.exp = 5;

	//Init the state
	m_State.attacking = false;
	m_State.going = false;
	m_State.idle = true;


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
	if (m_left)
	{
		m_fXVel = -g_pTimer->GetElapsedTime().asSeconds() * m_Attributes.speed;
		m_fLegsAnimState -= 8.0f * (m_Attributes.speed / 100) * g_pTimer->GetElapsedTime().asSeconds();

		//start the animation new if it has reached it's end
		if (m_fLegsAnimState < 0 || m_fLegsAnimState > 6)
			m_fLegsAnimState = 5.99f;

		if (m_pGoblin->GetRect().left < 200)
		{
			m_left = false;
			m_fLegsAnimState = 6;
		}
		
	}
	else
	{
		m_fXVel = g_pTimer->GetElapsedTime().asSeconds() * m_Attributes.speed;
		m_fLegsAnimState += 8.0f * (m_Attributes.speed / 100) * g_pTimer->GetElapsedTime().asSeconds();

		//start the animation new if it has reached it's end
		if (m_fLegsAnimState < 6 || m_fLegsAnimState > 12)
			m_fLegsAnimState = 6;

		if (m_pGoblin->GetRect().left > 1200)
		{
			m_left = true;
			m_fLegsAnimState = 5;
		}
	}
	m_pGoblin->Move(m_fXVel, m_fYVel);


	return true;
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