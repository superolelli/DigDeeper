#include "StringContainer.hpp"
#include "Constants.hpp"


void CStringContainer::LoadStrings(int _language)
{
	// populate tree structure pt
	using boost::property_tree::ptree;
	ptree pt;

	switch (_language)
	{
	case(GERMAN) :
		read_xml("Data/Xml/TextFileGerman.xml", pt);
		break;
	case(ENGLISH) :
		read_xml("Data/Xml/TextFileEnglish.xml", pt);
		break;
	}


	//loads the attributes of each start class type into a map
	BOOST_FOREACH(ptree::value_type const& v, pt.get_child("stringtable"))
	{
		if (v.first == "string")
			m_Strings[v.second.get("<xmlattr>.ID", 0)] = v.second.get<std::string>("<xmlattr>.value");
	}
	
	pt.clear();
}