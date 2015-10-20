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
	m_Attributes.light = 0;
}


CTool::~CTool()
{
	SAFE_DELETE(m_pCarriedToolSprite);
}


void CTool::InitTool(int _ID, bool _loaded)
{
	Init(_ID, _loaded);

	if (!_loaded)
	{
		m_Attributes = g_pProperties->m_EquipmentProperties[m_ID];
		m_rarity = 1;
	}

	m_pCarriedToolSprite = new CSprite;

	switch(m_ID)
	{
	case(PICKAXE):
		{	
			m_pCarriedToolSprite->Load(&g_pTextures->t_tool_pickaxe);
			m_pCarriedToolSprite->setRotatingPoint(30.0f, 50.0f);
		}break;
	case(SWORD):
		{	
			m_pCarriedToolSprite->Load(&g_pTextures->t_tool_sword);
			m_pCarriedToolSprite->setRotatingPoint(31.0f, 53.0f);
		}break;
	case(BATTLEAXE) :
	{
		m_pCarriedToolSprite->Load(&g_pTextures->t_tool_battleaxe);
		m_pCarriedToolSprite->setRotatingPoint(30.0f, 70.0f);
	}break;
	case(BATTLESTONE) :
	{
		m_pCarriedToolSprite->Load(&g_pTextures->t_tool_battlestone);
		m_pCarriedToolSprite->setRotatingPoint(10.0f, 8.0f);
	}break;
	case(LANTERN):
	{	
		m_pCarriedToolSprite->Load(&g_pTextures->t_tool_lantern);
		m_pCarriedToolSprite->setRotatingPoint(10.0f, 0.0f);
	}break;
	case(GOBLINDAGGER) :
	{
		m_pCarriedToolSprite->Load(&g_pTextures->t_tool_goblindagger, 2, 16, 38);
		m_pCarriedToolSprite->setRotatingPoint(5.0f, 7.0f);
	}break;
	}
}



void CTool::InitToolRandomly(int _ID)
{
	InitTool(_ID);

	//get a rarity
	int number = rand() % 1000;

	if (number < 5)
		m_rarity = 5;
	else if (number < 20)
		m_rarity = 4;
	else if (number < 50)
		m_rarity = 3;
	else if (number < 100)
		m_rarity = 2;
	else
		m_rarity = 1;


	//add the skills
	for (int i = 0; i < m_rarity; i++)
	{
		number = rand() % 12 + 1;

		switch (number)
		{
			case ARMOUR:
			{
				m_Attributes.armour += rand() % 3 + 1;
				if (i == 1)
					m_Name.append(g_pStringContainer->m_Strings[STRING_OF_ARMOUR]);
			}break;
			case BREAKINGSPEED:
			{
				m_Attributes.breaking_speed += (float)(rand() % 5 + 1) / 10;
				if (i == 1)
					m_Name.append(g_pStringContainer->m_Strings[STRING_OF_BREAKINGSPEED]);
			}break;
			case STRENGTH:
			{
				m_Attributes.strength += 1;
				if (i == 1)
					m_Name.append(g_pStringContainer->m_Strings[STRING_OF_STRENGTH]);
			}break;
			case HEALTH:
			{
				m_Attributes.maxHealth += rand() % 10 + 1;
				if (i == 1)
					m_Name.append(g_pStringContainer->m_Strings[STRING_OF_HEALTH]);
			}break;
			case SPEED:
			{
				m_Attributes.speed += rand() % 10 + 1;
				if (i == 1)
					m_Name.append(g_pStringContainer->m_Strings[STRING_OF_SPEED]);
			}break;
			case LUCK:
			{
				m_Attributes.luck += rand() % 10 + 1;
				if (i == 1)
					m_Name.append(g_pStringContainer->m_Strings[STRING_OF_LUCK]);
			}break;
			case MANA:
			{
				m_Attributes.maxMana += rand() % 10 + 1;
				if (i == 1)
					m_Name.append(g_pStringContainer->m_Strings[STRING_OF_MANA]);
			}break;
			case HEALTHREGENERATION:
			{
				m_Attributes.healthRegeneration += 1;
				if (i == 1)
					m_Name.append(g_pStringContainer->m_Strings[STRING_OF_HEALTHREGENERATION]);
			}break;
			case MANAREGENERATION:
			{
				m_Attributes.manaRegeneration += rand() % 2 + 1;
				if (i == 1)
					m_Name.append(g_pStringContainer->m_Strings[STRING_OF_MANAREGENERATION]);
			}break;
			case CRITICALCHANCE:
			{
				m_Attributes.criticalChance += rand() % 5 + 1;
				if (i == 1)
					m_Name.append(g_pStringContainer->m_Strings[STRING_OF_CRITICALCHANCE]);
			}break;
			case CRITICALDAMAGE:
			{
				m_Attributes.criticalDamage += rand() % 10 + 1;
				if (i == 1)
					m_Name.append(g_pStringContainer->m_Strings[STRING_OF_CRITICALDAMAGE]);
			}break;
			case 12:
			{
				m_Attributes.light += rand() % 100 + 50;
				if (i == 1)
					m_Name.append(g_pStringContainer->m_Strings[STRING_OF_LIGHT]);
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