#include "Structures.hpp"
#include "ObjectProperties.hpp"





void PropertyLoading::LoadProperties()
{	
	// populate tree structure pt
	using boost::property_tree::ptree;
	ptree pt;	
	read_xml("Data/Xml/Npcs.xml", pt);


	//loads the attributes of each npc type into a map
	BOOST_FOREACH(ptree::value_type const& v, pt.get_child("npcs"))
	{
		SNpcAttributes atb;	

		atb.maxHealth = v.second.get("<xmlattr>.health", 0);
		atb.currentHealth = atb.maxHealth;
		atb.armour = v.second.get("<xmlattr>.armour", 0);
		atb.speed = v.second.get("<xmlattr>.speed", 0);
		atb.strength = v.second.get("<xmlattr>.strength", 0);
		atb.exp = v.second.get("<xmlattr>.exp", 0);
		atb.effects.clear();
		
		m_NpcProperties[v.second.get("<xmlattr>.ID", 0)] = atb;
	}


	pt.clear();
	read_xml("Data/Xml/Equipment.xml", pt);

	//loads the attributes of each equipment type into a map
	BOOST_FOREACH(ptree::value_type const& v, pt.get_child("equipment"))
	{
		SToolAttributes atb;

		atb.maxHealth = v.second.get("<xmlattr>.health", 0);
		atb.healthRegeneration = v.second.get("<xmlattr>.healthregeneration", 0);
		atb.maxMana = v.second.get("<xmlattr>.mana", 0);
		atb.manaRegeneration = v.second.get("<xmlattr>.manaregeneration", 0);
		atb.armour = v.second.get("<xmlattr>.armour", 0);
		atb.speed = v.second.get("<xmlattr>.speed", 0);
		atb.breaking_speed = v.second.get("<xmlattr>.breakingspeed", 0.0f);
		atb.strength = v.second.get("<xmlattr>.strength", 0);
		atb.luck = v.second.get("<xmlattr>.luck", 0);
		atb.criticalChance = v.second.get("<xmlattr>.criticalchance", 0);
		atb.criticalDamage = v.second.get("<xmlattr>.criticaldamage", 0);
		atb.light = v.second.get("<xmlattr>.light", 0);

		m_EquipmentProperties[v.second.get("<xmlattr>.ID", 0)] = atb;
	}


	pt.clear();
	read_xml("Data/Xml/StartClasses.xml", pt);

	//loads the attributes of each start class type into a map
	BOOST_FOREACH(ptree::value_type const& v, pt.get_child("startclasses"))
	{
		SPlayerAttributes atb;
		vector<Vector2i> itms;

		atb.maxHealth = v.second.get("<xmlattr>.health", 0);
		atb.currentHealth = atb.maxHealth;
		atb.healthRegeneration = v.second.get("<xmlattr>.healthregeneration", 0);
		atb.maxMana = v.second.get("<xmlattr>.mana", 0);
		atb.currentMana = atb.maxMana;
		atb.manaRegeneration = v.second.get("<xmlattr>.manaregeneration", 0);
		atb.armour = v.second.get("<xmlattr>.armour", 0);
		atb.speed = v.second.get("<xmlattr>.speed", 0);
		atb.breakingSpeed = v.second.get("<xmlattr>.breakingspeed", 0.0f);
		atb.strength = v.second.get("<xmlattr>.strength", 0);
		atb.luck = v.second.get("<xmlattr>.luck", 0);
		atb.criticalChance = v.second.get("<xmlattr>.criticalchance", 0);
		atb.criticalDamage = v.second.get("<xmlattr>.criticaldamage", 0);
		atb.currentExp = 0;
		atb.maxExp = 20;

		itms.clear();

		BOOST_FOREACH(ptree::value_type const& w, v.second)
		{
			itms.push_back(Vector2i(w.second.get("<xmlattr>.ID", 0), w.second.get("<xmlattr>.amount", 0)));
		}

		m_StartClassesProperties[v.second.get("<xmlattr>.ID", 0)].attributes = atb;
		m_StartClassesProperties[v.second.get("<xmlattr>.ID", 0)].items = itms;
	}
}