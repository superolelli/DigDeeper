#include "Consumable.hpp"



CConsumable::CConsumable()
{
	m_Attributes.armour = 0;
	m_Attributes.breaking_speed = 0;
	m_Attributes.luck = 0;
	m_Attributes.health = 0;
	m_Attributes.mana = 0;
	m_Attributes.speed = 0;
	m_Attributes.strength = 0;
	m_Attributes.healthRegeneration = 0;
	m_Attributes.manaRegeneration = 0;
	m_Attributes.criticalChance = 0;
	m_Attributes.criticalDamage = 0;
	m_Attributes.duration = 0.0f;
}




void CConsumable::InitConsumable(int _ID)
{
	Init(_ID);

	switch (_ID)
	{
	case(HONEY) :
	{
		m_Attributes.luck = 1;
		m_Attributes.duration = 10.0f;
	}break;
	case(MEAD) :
	{
		m_Attributes.health = 10;
	}break;
	case(SLIMEPUDDING) :
	{
		m_Attributes.manaRegeneration = 1;
		m_Attributes.duration = 5;
	}break;
	case(CLOVER) :
	{
		m_Attributes.luck = 5;
		m_Attributes.duration = 20.0f;
	}break;
	case(RADISH) :
	{
		m_Attributes.armour = 5;
		m_Attributes.duration = 20.0f;
	}break;
	case(RADISHSOUP) :
	{
		m_Attributes.armour = 10;
		m_Attributes.duration = 40.0f;
	}break;
	}
}