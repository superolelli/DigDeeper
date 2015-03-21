#ifndef GOBLIN_HPP
#define GOBLIN_HPP

#include "NPC.hpp"


class CGoblin : public CNpc
{
public:

	void Init(int _x, int _y, CWorld *_world, bool _loaded = false);
	bool CheckNpc();
	void Render();
	void Quit();
	IntRect GetRect(){ return m_pGoblin->GetRect(); }

	vector<SItem> GetLoot();

private:
	friend class boost::serialization::access;

	//saves the equipment
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<CNpc>(*this);
		ar & m_left;
		ar & m_PointToGo.x;
		ar & m_PointToGo.y;
	}

	CLiving3Part *m_pGoblin;          //the goblin

	bool m_left;                   //is the goblin looking to the left
	Vector2i m_PointToGo;          //the point where the goblin should go
	float m_fXVel, m_fYVel;             //the velocity
	float m_fLegsAnimState;           //the animation state of the legs

	float m_fStateTime;               //how long does the current state last?

	void CheckState();                 //checks the state
	void CheckXMovement();                //checks the movement in x-direction
	void CheckYMovement();                //checks the movement in y-direction
};



#endif