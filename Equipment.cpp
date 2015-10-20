#include "Equipment.hpp"




CEquipment::CEquipment()
{
	m_pCarriedEquipmentSprite = NULL;
	m_Attributes.armour = 0;
	m_Attributes.breaking_speed = 0;
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

	m_EquipID = 0;
}



CEquipment::~CEquipment()
{
	SAFE_DELETE(m_pCarriedEquipmentSprite);
}





void CEquipment::InitEquipment(int _ID, bool _loaded, bool _inited)
{
	Init(_ID, _loaded);
	
	m_pCarriedEquipmentSprite = new CSprite;

	if (!_loaded)
		m_Attributes = g_pProperties->m_EquipmentProperties[_ID];

	switch(_ID)
	{
	case IRONHELMET:
		{
			m_pCarriedEquipmentSprite->Load(&g_pTextures->t_equipment_iron_helmet, 2, 32, 30);
			if(!_loaded)
			{
				m_EquipID = HEAD;
				m_rarity = 1;
			}
		}break;
	case IRONARMOUR:
		{
			m_pCarriedEquipmentSprite->Load(&g_pTextures->t_equipment_iron_armour, 2, 53, 60);
			if(!_loaded)
			{
				m_EquipID = BODY;
				m_rarity = 1;
			}
		}break;
	case IRONTROUSERS:
		{
			m_pCarriedEquipmentSprite->Load(&g_pTextures->t_equipment_iron_trousers, 14, 55, 50);
			if(!_loaded)
			{
				m_EquipID = LEGS;
				m_rarity = 1;
			}
		}break;
	case MAGICHAT:
		{
			m_pCarriedEquipmentSprite->Load(&g_pTextures->t_equipment_magic_hat, 2, 46, 34);
			if(!_loaded)
			{
				m_EquipID = HEAD;
				m_rarity = 1;
			}
		}break;
	case CANDLE:
		{
			m_pCarriedEquipmentSprite->Load(&g_pTextures->t_equipment_candle, 2, 14, 41);
			if(!_loaded)
			{
				m_EquipID = HEAD;
				m_rarity = 1;
			}
		}break;
	case DIADOCHITARMOUR:
	{
		m_pCarriedEquipmentSprite->Load(&g_pTextures->t_equipment_diadochitarmour, 2, 53, 60);
		if (!_loaded)
		{
			m_EquipID = BODY;
			m_rarity = 1;
		}
	}break;
	case LEATHERARMOUR:
	{
		m_pCarriedEquipmentSprite->Load(&g_pTextures->t_equipment_leatherarmour, 2, 53, 60);
		if (!_loaded)
		{
			m_EquipID = BODY;
			m_rarity = 1;
		}
	}break;
	case LEATHERHELMET:
	{
		m_pCarriedEquipmentSprite->Load(&g_pTextures->t_equipment_leatherhelmet, 2, 40, 24);
		if (!_loaded)
		{
			m_EquipID = HEAD;
			m_rarity = 1;
		}
	}break;
	case IRONRING:
	case ARCANUSRING:
	case VERYRARERING:
		{
			if(!_loaded)
			{
				m_EquipID = HAND;
				m_rarity = 1;

				if (!_inited)
					InitEquipmentRandomly(_ID);
			}
		}break;
	}
}



void CEquipment::InitEquipmentRandomly(int _ID)
{
	InitEquipment(_ID, false, true);

	//get a rarity
	int number = rand()%1000;

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


	int i = 1;

	if (_ID == IRONRING)
		i = 0;
	else if (_ID == ARCANUSRING)
		i = -2;
	else if (_ID == VERYRARERING)
	{
		i = 0;
		m_rarity = 5;
	}


	//add the skills
	for(i; i < m_rarity; i++)
	{
		number = rand()%12 + 1;

		switch(number)
		{
		case ARMOUR:
			{
				m_Attributes.armour += rand()%3 + 1;
				if(i == 1)
					m_Name.append(g_pStringContainer->m_Strings[STRING_OF_ARMOUR]);
			}break;
		case BREAKINGSPEED:
			{
				m_Attributes.breaking_speed += (float)(rand()%5 +1) /10;
				if(i == 1)
					m_Name.append(g_pStringContainer->m_Strings[STRING_OF_BREAKINGSPEED]);
			}break;
		case STRENGTH:
			{
				m_Attributes.strength += 1;
				if(i == 1)
					m_Name.append(g_pStringContainer->m_Strings[STRING_OF_STRENGTH]);
			}break;
		case HEALTH:
			{
				m_Attributes.maxHealth += rand()%10 +1;
				if(i == 1)
					m_Name.append(g_pStringContainer->m_Strings[STRING_OF_HEALTH]);
			}break;
		case SPEED:
			{
				m_Attributes.speed += rand()%10 +1;
				if(i == 1)
					m_Name.append(g_pStringContainer->m_Strings[STRING_OF_SPEED]);
			}break;
		case LUCK:
			{
				m_Attributes.luck += rand()%10 +1;
				if(i == 1)
					m_Name.append(g_pStringContainer->m_Strings[STRING_OF_LUCK]);
			}break;
		case MANA:
			{
				m_Attributes.maxMana += rand()%10 +1;
				if(i == 1)
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



void CEquipment::RenderEquipment(int _x, int _y, float _frameNumber)
{
	m_pCarriedEquipmentSprite->SetPos(_x, _y);
	m_pCarriedEquipmentSprite->Render(g_pFramework->GetRenderWindow(), _frameNumber);
}