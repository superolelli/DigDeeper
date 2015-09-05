#include "Tool.hpp"


CTool::CTool()
{
	m_pCarriedToolSprite = NULL;
	m_Attributes.breaking_speed = 0;
	m_Attributes.armour = 0;
	m_Attributes.luck = 0;
	m_Attributes.maxHealth = 0;
	m_Attributes.maxMana = 0;
	m_Attributes.speed = 0;
	m_Attributes.strength = 0;
	m_Attributes.healthRegeneration = 0;
	m_Attributes.manaRegeneration = 0;
	m_Attributes.criticalChance = 0;
	m_Attributes.criticalDamage = 0;
}


CTool::~CTool()
{
	SAFE_DELETE(m_pCarriedToolSprite);
}


void CTool::InitTool(int _ID, bool _loaded)
{
	Init(_ID, _loaded);

	m_pCarriedToolSprite = new CSprite;

	switch(m_ID)
	{
	case(PICKAXE):
		{	
			m_pCarriedToolSprite->Load(&g_pTextures->t_tool_pickaxe);
			m_pCarriedToolSprite->setRotatingPoint(30.0f, 50.0f);
			if(!_loaded)
			{
				m_Attributes.breaking_speed = 0.7f;
				m_Attributes.strength = 1;
				m_rarity = 1;
			}
		}break;
	case(SWORD):
		{	
			m_pCarriedToolSprite->Load(&g_pTextures->t_tool_sword);
			m_pCarriedToolSprite->setRotatingPoint(31.0f, 53.0f);
			if(!_loaded)
			{
				m_Attributes.strength = 5;
				m_rarity = 1;
			}
		}break;
	case(BATTLEAXE) :
	{
		m_pCarriedToolSprite->Load(&g_pTextures->t_tool_battleaxe);
		m_pCarriedToolSprite->setRotatingPoint(30.0f, 70.0f);
		if (!_loaded)
		{
			m_Attributes.strength = 5;
			m_Attributes.criticalChance = 5;
			m_Attributes.criticalDamage = 5;
			m_rarity = 1;
		}
	}break;
	case(BATTLESTONE) :
	{
		m_pCarriedToolSprite->Load(&g_pTextures->t_tool_battlestone);
		m_pCarriedToolSprite->setRotatingPoint(10.0f, 8.0f);
		if (!_loaded)
		{
			m_Attributes.strength = 2;
			m_Attributes.healthRegeneration = 2;
			m_rarity = 1;
		}
	}break;
	case(LANTERN):
	{	
		m_pCarriedToolSprite->Load(&g_pTextures->t_tool_lantern);
		m_pCarriedToolSprite->setRotatingPoint(10.0f, 0.0f);
		if(!_loaded)
		{
			m_rarity = 1;
		}
	}break;
	case(GOBLINDAGGER) :
	{
		m_pCarriedToolSprite->Load(&g_pTextures->t_tool_goblindagger, 2, 16, 38);
		m_pCarriedToolSprite->setRotatingPoint(5.0f, 7.0f);
		if (!_loaded)
		{
			m_Attributes.strength = 7;
			m_rarity = 1;
		}
	}break;
	}
}



void CTool::InitToolRandomly(int _ID)
{
	InitTool(_ID);

	//get a rarity
	int number = rand()%1000;

	if(number < 5)
		m_rarity = 5;
	else if(number < 20)
		m_rarity = 4;
	else if(number < 50)
		m_rarity = 3;
	else if(number < 100)
		m_rarity = 2;
	else
		m_rarity = 1;


	//add the skills
	for(int i = 1; i < m_rarity; i++)
	{
		number = rand()%NUMBER_OF_SKILLS + 1;

		switch(number)
		{
		case ARMOUR:
			{
				m_Attributes.armour += rand()%3 + 1;
				if(i == 1)
					m_Name.append(" des Schutzes");
			}break;
		case BREAKINGSPEED:
			{
				m_Attributes.breaking_speed += (float)(rand()%5 +1) /10;
				if(i == 1)
					m_Name.append(" des Erdreichs");
			}break;
		case STRENGTH:
			{
				m_Attributes.strength += 1;
				if(i == 1)
					m_Name.append(" der Zerstörung");
			}break;
		case HEALTH:
			{
				m_Attributes.maxHealth += rand()%10 +1;
				if(i == 1)
					m_Name.append(" der Vitalität");
			}break;
		case SPEED:
			{
				m_Attributes.speed += rand()%10 +1;
				if(i == 1)
					m_Name.append(" des Flitzers");
			}break;
		case LUCK:
			{
				m_Attributes.luck += rand()%10 +1;
				if(i == 1)
					m_Name.append(" des Schornsteinfegers");
			}break;
		case MANA:
			{
				m_Attributes.maxMana += rand()%10 +1;
				if(i == 1)
					m_Name.append(" des Magiers");
			}break;
		case HEALTHREGENERATION:
			{
				m_Attributes.healthRegeneration += 1;
				if (i == 1)
					m_Name.append(" der Regeneration");
			}break;
		case MANAREGENERATION:
			{
				m_Attributes.manaRegeneration += rand() % 2 + 1;
				if (i == 1)
					m_Name.append(" der arkanen Macht");
			}break;
		case CRITICALCHANCE:
			{
				m_Attributes.criticalChance += rand() % 5 + 1;
				if (i == 1)
					m_Name.append(" des Zufalls");
			}break;
		case CRITICALDAMAGE:
			{
				m_Attributes.criticalDamage += rand() % 10 + 1;
				if (i == 1)
					m_Name.append(" des Vernichtens");
			}break;
		default:
			{
				 
			}
		}
	}
}




void CTool::RenderTool(int _x, int _y, bool _left)
{
	

	if (m_ID == GOBLINDAGGER)
	{
		if (_left)
		{
			m_pCarriedToolSprite->SetPos(_x, _y);
			m_pCarriedToolSprite->Render(g_pFramework->GetRenderWindow(), 0.0f);
		}
		else
		{
			m_pCarriedToolSprite->SetPos(_x - 5, _y);
			m_pCarriedToolSprite->Render(g_pFramework->GetRenderWindow(), 1.0f);
		}
	}
	else
	{
		m_pCarriedToolSprite->SetPos(_x, _y);
		m_pCarriedToolSprite->Render(g_pFramework->GetRenderWindow());
	}
}


void CTool::SetRotation(float _angle)
{
	m_pCarriedToolSprite->setRotation(_angle);
}



IntRect CTool::GetRect()
{
	switch(m_ID)
	{
	case(PICKAXE):
		{
			IntRect rect;
			rect = m_pCarriedToolSprite->GetGlobalRect();
			rect.height = 15;
			return rect;
		}break;
	case(SWORD):
		{
			IntRect rect;
			rect = m_pCarriedToolSprite->GetGlobalRect();
			rect.height = 47;
			rect.width = 8;
			rect.left += 26;
			return rect;
		}break;
	case(BATTLEAXE) :
	{
		IntRect rect;
		rect = m_pCarriedToolSprite->GetGlobalRect();
		rect.height = 55;
		return rect;
	}break;
	case(GOBLINDAGGER) :
	{
		IntRect rect;
		rect = m_pCarriedToolSprite->GetGlobalRect();
		rect.top += 9;
		rect.height -= 9;

		return rect;
	}break;
	default:
		return m_pCarriedToolSprite->GetGlobalRect();
	}
}