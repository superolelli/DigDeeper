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
		
		m_NpcProperties[v.second.get("<xmlattr>.ID", 0)] = atb;
	}
}