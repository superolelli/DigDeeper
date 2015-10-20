#ifndef STRINGCONTAINER_HPP
#define STRINGCONTAINER_HPP


#include "singleton.hpp"
#include <string>
#include <map>
#include <iostream>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>

using namespace boost::property_tree;
using namespace std;


#pragma region String_IDs

const int STRING_HEALTH = 0;
const int STRING_HEALTHREGENERATION = 1;
const int STRING_ARMOUR = 2;
const int STRING_STRENGTH = 3;
const int STRING_CRITICALCHANCE = 4;
const int STRING_CRITICALDAMAGE = 5;
const int STRING_LUCK = 6;
const int STRING_BREAKINGSPEED = 7;
const int STRING_SPEED = 8;
const int STRING_MANA = 9;
const int STRING_MANAREGENERATION = 10;
const int STRING_LIGHT = 11;

const int STRING_LEVELUP = 12;
const int STRING_SKILL_ARMOUR_TITLE = 13;
const int STRING_SKILL_ARMOUR_DESCRIPTION = 14;
const int STRING_SKILL_BREAKINGSPEED_TITLE = 15;
const int STRING_SKILL_BREAKINGSPEED_DESCRIPTION = 16;
const int STRING_SKILL_CRITICALCHANCE_TITLE = 17;
const int STRING_SKILL_CRITICALCHANCE_DESCRIPTION = 18;
const int STRING_SKILL_CRITICALDAMAGE_TITLE = 19;
const int STRING_SKILL_CRITICALDAMAGE_DESCRIPTION = 20;
const int STRING_SKILL_HEALTH_TITLE = 21;
const int STRING_SKILL_HEALTH_DESCRIPTION = 22;
const int STRING_SKILL_HEALTHREGENERATION_TITLE = 23;
const int STRING_SKILL_HEALTHREGENERATION_DESCRIPTION = 24;
const int STRING_SKILL_LUCK_TITLE = 25;
const int STRING_SKILL_LUCK_DESCRIPTION = 26;
const int STRING_SKILL_MAGICPOINT_TITLE = 27;
const int STRING_SKILL_MAGICPOINT_DESCRIPTION = 28;
const int STRING_SKILL_MANA_TITLE = 29;
const int STRING_SKILL_MANA_DESCRIPTION = 30;
const int STRING_SKILL_MANAREGENERATION_TITLE = 31;
const int STRING_SKILL_MANAREGENERATION_DESCRIPTION = 32;
const int STRING_SKILL_RECIPE_TITLE = 33;
const int STRING_SKILL_RECIPE_DESCRIPTION = 34;
const int STRING_SKILL_SPEED_TITLE = 35;
const int STRING_SKILL_SPEED_DESCRIPTION = 36;
const int STRING_SKILL_STRENGTH_TITLE = 37;
const int STRING_SKILL_STRENGTH_DESCRIPTION = 38;

const int STRING_CONSUMABLE = 43;
const int STRING_DURATION = 44;

const int STRING_OF_ARMOUR = 45;
const int STRING_OF_BREAKINGSPEED = 46;
const int STRING_OF_STRENGTH = 47;
const int STRING_OF_HEALTH = 48;
const int STRING_OF_SPEED = 49;
const int STRING_OF_LUCK = 50;
const int STRING_OF_MANA = 51;
const int STRING_OF_HEALTHREGENERATION = 52;
const int STRING_OF_MANAREGENERATION = 53;
const int STRING_OF_CRITICALCHANCE = 54;
const int STRING_OF_CRITICALDAMAGE = 55;
const int STRING_OF_LIGHT = 56;

const int STRING_WRITE_YOUR_NAME = 60;
const int STRING_NOBODY = 61;
const int STRING_MINUTES = 62;
const int STRING_NO_HIGHSCORE = 63;
const int STRING_LEVEL_REACHED = 64;
const int STRING_STARTCLASS = 65;

const int STRING_MINER = 70;
const int STRING_BUILDER = 71;
const int STRING_WARRIOR = 72;
const int STRING_MAGE = 73;
const int STRING_CHEATER = 74;

const int STRING_NEW_WORLD = 77;

const int STRING_SPELL_NOT_LEARNED = 80;
const int STRING_SPELL_ON_HIGHEST_LEVEL = 81;
const int STRING_SPELL_ON_NEXT_LEVEL = 82;
const int STRING_DAMAGE = 83;
const int STRING_MANACOSTS = 84;

const int STRING_FIREBALL = 85;
const int STRING_FIREBALL_DESCRIPTION = 86;
const int STRING_ICEBALL = 87;
const int STRING_ICEBALL_DESCRIPTION = 88;
const int STRING_FROZEN_TIME = 89;
const int STRING_POISONCLOUD = 90;
const int STRING_POISONCLOUD_DESCRIPTION = 91;
const int STRING_POISON_LEVEL = 92;
const int STRING_POISON_DURATION = 93;

const int STRING_HEAL = 103;
const int STRING_HEAL_DESCRIPTION = 104;
const int STRING_HEALTHPOINTS = 105;
const int STRING_MANASHIELD = 106;
const int STRING_MANASHIELD_DESCRIPTION = 107;

const int STRING_ALCHEMY = 121;
const int STRING_ALCHEMY_DESCRIPTION = 122;
const int STRING_CHANCE_FOR_HIGHER_BLOCK = 123;
const int STRING_CHANCE_FOR_LOWER_BLOCK = 124;
const int STRING_LIGHTSPELL = 125;
const int STRING_LIGHTSPELL_DESCRIPTION = 126;
const int STRING_LIGHTRADIUS = 127;
const int STRING_TELEPORT = 128;
const int STRING_TELEPORT_DESCRIPTION = 129;
const int STRING_WIDTH = 130;

const int STRING_INVENTORY = 145;
const int STRING_BUILDING = 146;
const int STRING_ATTRIBUTES = 147;
const int STRING_MAGIC = 148;

const int STRING_IRONPICKAXE = 100;
const int STRING_IRONSWORD = 101;
const int STRING_WOODSTAFF = 102;

#pragma endregion



#pragma endregion


//the class for loading all properties at once
#define g_pStringContainer CStringContainer::Get()
class CStringContainer : public TSingleton<CStringContainer>
{
public:

	void LoadStrings(int _language);

	map<int, string> m_Strings;
	
};



#endif