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
	bool IsBroken(float _modificator);
	IntRect GetRect();
	int GetLittleID();
	int GetSpecialID(){return m_SpecialID;}
	


private:

	friend class boost::serialization::access;

	//saves the equipment
	template<class Archive>
	void save(Archive & ar, const unsigned int version) const
	{
		ar & boost::serialization::base_object<CThing>(*this);
		ar & m_SpecialID;
	}

	//load the building menu
	template<class Archive>
	void load(Archive & ar, const unsigned int version) 
	{
		ar & boost::serialization::base_object<CThing>(*this);
		ar & m_SpecialID;
	}
	BOOST_SERIALIZATION_SPLIT_MEMBER();



	int m_Hardness;                                //the hardness of the placeable
	int m_SpecialID;                                //a settable ID for different things (e.g. counting furnances, chests etc.) (doors: the frame)
	float m_fBreakingTime;                        //how long has the player trying to break the placeable?
	float m_fBreakFrame;                           //the frame of the breaking animation

	bool m_is_visible;                          //is the placeable visible?
	bool m_is_passable;                         //is the placealbe passable?

	 CSprite m_BreakingAnimation;
};



#endif