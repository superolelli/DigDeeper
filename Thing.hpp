#ifndef THING_HPP
#define THING_HPP


#include "Framework.hpp"

class CThing// abstract
{
public: 
	inline int getID(){return m_ID;}

	CSprite *GetInventorySprite(){return m_pInventorySprite;}
	string GetName(){return m_Name;}
	void RenderInventorySprite(){m_pInventorySprite->Render(g_pFramework->GetWindow());}

protected:
	friend class boost::serialization::access;

	//saves the thing
	template<class Archive>
	void save(Archive & ar, const unsigned int version) const
	{
		ar & m_ID;
		ar & m_Name;
	}

	//load the thing
	template<class Archive>
	void load(Archive & ar, const unsigned int version) 
	{
		ar & m_ID;
		ar & m_Name;
	}

	BOOST_SERIALIZATION_SPLIT_MEMBER();



	int m_ID;                                        //the thing's ID
	string m_Name;                                   //the name

	CSprite *m_pThingSprite;                        //the thing sprite
	CSprite *m_pInventorySprite;                    //the inventory sprite


};






#endif