#ifndef PLACEABLE_HPP
#define PLACEABLE_HPP


#include "Thing.hpp"



class CPlaceable : public CThing
{
public:
	CPlaceable();
	~CPlaceable();
	void Init(int _ID, bool _loaded = false);
	void SetPos(float _x, float _y);
	void SetPos(int _x, int _y);
	void Render();
	void SetBreakingFalse(){m_fBreakingTime = 0.0f; m_fBreakFrame = -1;}
	void SetSpecialID(int _SID);
	bool IsPassable(){return m_is_passable;}
	bool CanBePlacedOn(){ return m_can_place_on; }
	bool IsBroken(float _modificator);
	bool IsPlaceableReady();                   //for beehouses
	IntRect GetRect();
	int GetLittleID();
	int GetSpecialID(){return m_SpecialID;}
	int GetPriority(){ return m_Priority; }
	int GetOverlappingID(int _side){ return m_OverlappingID[_side]; }


private:

	friend class boost::serialization::access;

	//saves the equipment
	template<class Archive>
	void save(Archive & ar, const unsigned int version) const
	{
		ar & boost::serialization::base_object<CThing>(*this);
		ar & m_SpecialID;
		ar & m_fPlaceableTimer;
	}

	//load the building menu
	template<class Archive>
	void load(Archive & ar, const unsigned int version) 
	{
		ar & boost::serialization::base_object<CThing>(*this);
		ar & m_SpecialID;
		ar & m_fPlaceableTimer;
	}
	BOOST_SERIALIZATION_SPLIT_MEMBER();

	int m_Hardness;                                //the hardness of the placeable
	int m_SpecialID;                                //a settable ID for different things (e.g. counting furnances, chests etc.) (doors: the frame)
	int m_Priority;                               //the priority for overlapping
	int m_OverlappingID[4];
	float m_fBreakingTime;                        //how long has the player trying to break the placeable?
	float m_fBreakFrame;                           //the frame of the breaking animation

	float m_fPlaceableTimer;                       //for beehouses

	bool m_is_visible;                          //is the placeable visible?
	bool m_is_passable;                         //is the placealbe passable?
	bool m_can_place_on;                        //can be something placed upon this?

	 CSprite m_BreakingAnimation;


	 int GetRubbish();                           //gets random thing
};

BOOST_CLASS_VERSION(CPlaceable, 0)

#endif