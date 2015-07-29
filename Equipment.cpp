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

	m_EquipID = 0;
}



CEquipment::~CEquipment()
{
	SAFE_DELETE(m_pCarriedEquipmentSprite);
}





void CEquipment::InitEquipment(int _ID, bool _loaded)
{
	Init(_ID, _loaded);
	
	m_pCarriedEquipmentSprite = new CSprite;

	switch(_ID)
	{
	case IRONHELMET:
		{
			m_pCarriedEquipmentSprite->Load(&g_pTextures->t_equipment_iron_helmet, 2, 32, 30);
			if(!_loaded)
			{
				m_Attributes.armour = 2;
				m_EquipID = HEAD;
				m_rarity = 1;
			}
		}break;
	case IRONARMOUR:
		{
			m_pCarriedEquipmentSprite->Load(&g_pTextures->t_equipment_iron_armour, 2, 53, 60);
			if(!_loaded)
			{
				m_Attributes.armour = 5;
				m_EquipID = BODY;
				m_rarity = 1;
			}
		}break;
	case IRONTROUSERS:
		{
			m_pCarriedEquipmentSprite->Load(&g_pTextures->t_equipment_iron_trousers, 14, 55, 50);
			if(!_loaded)
			{
				m_Attributes.armour = 3;
				m_EquipID = LEGS;
				m_rarity = 1;
			}
		}break;
	case MAGICHAT:
		{
			m_pCarriedEquipmentSprite->Load(&g_pTextures->t_equipment_magic_hat, 2, 46, 34);
			if(!_loaded)
			{
				m_Attributes.maxMana = 10;
				m_Attributes.manaRegeneration = 1;
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
			m_Attributes.armour = 3;
			m_Attributes.healthRegeneration = 2;
			m_EquipID = BODY;
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
				InitRing();
			}
		}break;
	}
}



void CEquipment::InitEquipmentRandomly(int _ID)
{
	InitEquipment(_ID);

	//because the ring automatically is initialized randomly: end the function
	if(_ID == IRONRING || _ID == ARCANUSRING || _ID == VERYRARERING)
		return;

	//get a rarity
	int number = rand()%100;

	if(number == 99)
		m_rarity = 5;
	else if(number == 98 || number == 97 || number == 96)
		m_rarity = 4;
	else if(number > 90)
		m_rarity = 3;
	else if(number > 80)
		m_rarity = 2;
	else
		m_rarity = 1;


	//add the skills
	for(int i = 1; i < m_rarity; i++)
	{
		number = rand()%11 + 1;

		switch(number)
		{
		case ARMOUR:
			{
				m_Attributes.armour += rand()%5 + 1;
				if(i == 1)
					m_Name.append(" des Schutzes");
			}break;
		case BREAKINGSPEED:
			{
				m_Attributes.breaking_speed += (float)(rand()%3 +1) /10;
				if(i == 1)
					m_Name.append(" des Erdreiches");
			}break;
		case STRENGTH:
			{
				m_Attributes.strength += rand()%5 +1;
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
				m_Attributes.luck += rand()%3 +1;
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
				m_Attributes.healthRegeneration += rand() % 3 + 1;
				if (i == 1)
					m_Name.append(" der Regeneration");
			}break;
			case MANAREGENERATION:
			{
				m_Attributes.manaRegeneration += rand() % 3 + 1;
				if (i == 1)
					m_Name.append(" der arkanen Macht");
			}break;
			case CRITICALCHANCE:
			{
				m_Attributes.criticalChance += rand() % 3 + 1;
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


//inits a ring randomly
void CEquipment::InitRing()
{
		//get a rarity
	int number = rand()%100;

	if(number == 99)
		m_rarity = 5;
	else if(number == 98 || number == 97 || number == 96)
		m_rarity = 4;
	else if(number > 90)
		m_rarity = 3;
	else if(number > 80)
		m_rarity = 2;
	else
		m_rarity = 1;


	int i;

	if(m_ID == IRONRING)
		i = 0;
	else if(m_ID == ARCANUSRING)
		i = -2;
	else if(m_ID == VERYRARERING)
	{
		i = 0;
		m_rarity = 5;
	}

	//add the skills
	for(i; i < m_rarity; i++)
	{
		number = rand()%11 + 1;

		switch(number)
		{
		case ARMOUR:
			{
				m_Attributes.armour += rand()%5 + 1;
				if(i == 1 && m_ID != VERYRARERING)
					m_Name.append(" des Schutzes");
			}break;
		case BREAKINGSPEED:
			{
				m_Attributes.breaking_speed += (float)(rand()%3 +1) /10;
				if(i == 1 && m_ID != VERYRARERING)
					m_Name.append(" des Erdreiches");
			}break;
		case STRENGTH:
			{
				m_Attributes.strength += rand()%5 +1;
				if(i == 1 && m_ID != VERYRARERING)
					m_Name.append(" der Zerstörung");
			}break;
		case HEALTH:
			{
				m_Attributes.maxHealth += rand()%10 +1;
				if(i == 1 && m_ID != VERYRARERING)
					m_Name.append(" der Vitalität");
			}break;
		case SPEED:
			{
				m_Attributes.speed += rand()%10 +1;
				if(i == 1 && m_ID != VERYRARERING)
					m_Name.append(" des Flitzers");
			}break;
		case LUCK:
			{
				m_Attributes.luck += rand()%3 +1;
				if(i == 1 && m_ID != VERYRARERING)
					m_Name.append(" des Schornsteinfegers");
			}break;
		case MANA:
			{
				m_Attributes.maxMana += rand()%10 +1;
				if(i == 1 && m_ID != VERYRARERING)
					m_Name.append(" des Magiers");
			}break;
		case HEALTHREGENERATION:
			{
				m_Attributes.healthRegeneration += rand() % 3 + 1;
				if (i == 1 && m_ID != VERYRARERING)
					m_Name.append(" der Regeneration");
			}break;
		case MANAREGENERATION:
			{
				m_Attributes.manaRegeneration += rand() % 3 + 1;
				if (i == 1 && m_ID != VERYRARERING)
					m_Name.append(" der arkanen Macht");
			}break;
		case CRITICALCHANCE:
			{
				m_Attributes.criticalChance += rand() % 3 + 1;
				if (i == 1 && m_ID != VERYRARERING)
					m_Name.append(" des Zufalls");
			}break;
		case CRITICALDAMAGE:
		{
			m_Attributes.criticalDamage += rand() % 10 + 1;
			if (i == 1 && m_ID != VERYRARERING)
				m_Name.append(" des Vernichtens");
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