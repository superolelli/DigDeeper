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
const int STRING_HEALTHREGNERATION = 1;
const int STRING_ARMOUR = 2;
const int STRING_STRENGTH = 3;
const int STRING_CRITICALCHANCE = 4;
const int STRING_CRITICALDAMAGE = 5;
const int STRING_LUCK = 6;
const int STRING_BREAKINGSPEED = 7;
const int STRING_SPEED = 8;
const int STRING_MANA = 9;
const int STRING_MANAREGNERATION = 10;

const int STRING_LEVELUP = 11;
const int STRING_SKILL_ARMOUR_TITLE = 12;
const int STRING_SKILL_ARMOUR_DESCRIPTION = 13;
const int STRING_SKILL_BREAKINGSPEED_TITLE = 14;
const int STRING_SKILL_BREAKINGSPEED_DESCRIPTION = 15;
const int STRING_SKILL_CRITICALCHANCE_TITLE = 16;
const int STRING_SKILL_CRITICALCHANCE_DESCRIPTION = 17;
const int STRING_SKILL_CRITICALDAMAGE_TITLE = 18;
const int STRING_SKILL_CRITICALDAMAGE_DESCRIPTION = 19;
const int STRING_SKILL_HEALTH_TITLE = 20;
const int STRING_SKILL_HEALTH_DESCRIPTION = 21;
const int STRING_SKILL_HEALTHREGENERATION_TITLE = 22;
const int STRING_SKILL_HEALTHREGENERATION_DESCRIPTION = 23;
const int STRING_SKILL_LUCK_TITLE = 24;
const int STRING_SKILL_LUCK_DESCRIPTION = 25;
const int STRING_SKILL_MAGICPOINT_TITLE = 26;
const int STRING_SKILL_MAGICPOINT_DESCRIPTION = 27;
const int STRING_SKILL_MANA_TITLE = 28;
const int STRING_SKILL_MANA_DESCRIPTION = 29;
const int STRING_SKILL_MANAREGNERATION_TITLE = 30;
const int STRING_SKILL_MANAREGENERATION_DESCRIPTION = 31;
const int STRING_SKILL_RECIPE_TITLE = 32;
const int STRING_SKILL_RECIPE_DESCRIPTION = 33;
const int STRING_SKILL_SPEED_TITLE = 34;
const int STRING_SKILL_SPEED_DESCRIPTION = 35;
const int STRING_SKILL_STRENGTH_TITLE = 36;
const int STRING_SKILL_STRENGTH_DESCRIPTION = 37;

const int STRING_MAGIC_ALCHEMY_DESCRIPTION = 50;

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