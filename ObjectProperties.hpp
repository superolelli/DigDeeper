#ifndef OBJECTPROPERTIES_HPP
#define OBJECTPROPERTIES_HPP

#include "singleton.hpp"
#include <iostream>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>

struct SNpcAttributes;
struct SToolAttributes;
struct SPlayerXML;

using namespace boost::property_tree;

//the class for loading all properties at once
#define g_pProperties PropertyLoading::Get()
class PropertyLoading : public TSingleton<PropertyLoading>
{
public:

	void LoadProperties();

	map<int, SNpcAttributes> m_NpcProperties;
	map<int, SToolAttributes> m_EquipmentProperties;
	map<int, SPlayerXML> m_StartClassesProperties;

};



#endif