#ifndef LITTLEITEMS_HPP
#define LITTLEITEMS_HPP

#include "Framework.hpp"
#include "Thing.hpp"


class CLittleItem
{
public:

	CLittleItem();
	~CLittleItem();

	void Init(CThing *_thing, int _x, int _y, bool _loaded = false);
	void Render();
	void Quit(bool _forever = false);

	Vector2f GetVel(){return m_Vel;}
	void SetVel(Vector2f _vel){m_Vel = _vel;}
	void Move();

	//int GetID(){return m_pThing->getID();}
	CThing* GetThing(){return m_pThing;}
	IntRect GetRect(){return m_pLittleItemSprite->GetRect();}



private:

	friend class boost::serialization::access;

	//saves the little item
	template<class Archive>
	void save(Archive & ar, const unsigned int version) const
	{
		int xPos, yPos;
		xPos = m_pLittleItemSprite->GetRect().left;
		yPos = m_pLittleItemSprite->GetRect().top;
		
		//save the thing
		int d = m_pThing->getID();
		//save the ID for checking
		ar & d;
		//save the thing
		if(m_pThing->getID() < PIBREAK)
		{
			CPlaceable* placeable = (CPlaceable*)m_pThing;
			ar & placeable;
		}
		else if(m_pThing->getID() < CTBREAK)
		{
			CItem * item = (CItem*)m_pThing;
			ar & item;
		}
		else if(m_pThing->getID() < TEBREAK)
		{
			CTool * tool = (CTool*)m_pThing;
			ar & tool;
		}
		else
		{
			CEquipment *equipment = (CEquipment*)m_pThing;
			ar & equipment;
		}

		ar & xPos;
		ar & yPos;
	}

	//load the little item
	template<class Archive>
	void load(Archive & ar, const unsigned int version) 
	{
		int xLoaded, yLoaded;

		//load the thing
		int a = -1;

		//load the ID of the thing
		ar & a;
		if(a < PIBREAK)
		{
			//make a new thing with this ID
			CPlaceable *thing;
			//load the saved values
			ar >> thing;
			//Init the sprites etc.
			thing->Init(a, true);

			m_pThing = thing;
		}
		else if(a < CTBREAK)
		{
			CItem *thing;
			ar & thing;
			thing->Init(a, true);

			m_pThing = thing;
		}
		else if(a < TEBREAK)
		{
			CTool *thing;
			ar & thing;
			thing->InitTool(a, true);

			m_pThing = thing;
		}
		else 
		{
			CEquipment *thing;
			ar & thing;
			thing->InitEquipment(a, true);

			m_pThing = thing;
		}

		ar & xLoaded;
		ar & yLoaded;
		m_loaded = true;
		Init(NULL, xLoaded, yLoaded, true);
	}
	BOOST_SERIALIZATION_SPLIT_MEMBER();

	CSprite *m_pLittleItemSprite;                //the sprite
	CThing *m_pThing;                              //the thing
	bool m_loaded;                             //was this item loaded the last frame?
	Vector2f m_Vel;

};



#endif