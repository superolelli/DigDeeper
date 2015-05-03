#ifndef GOBLIN_HPP
#define GOBLIN_HPP

#include "NPC.hpp"


class CGoblin : public CNpc
{
public:

	void Init(int _x, int _y, CWorld *_world, CPlayer *_player, View *_view, bool _loaded = false);
	bool CheckNpc();
	void Render();
	void Quit();
	IntRect GetRect(){ return m_pGoblin->GetRect(); }
	IntRect GetWeaponRect();
	bool IsHitting();
	void ThrowNpc(bool _left, int _strength);

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
		ar & m_goblinType;
	}

	CLiving3Part *m_pGoblin;          //the goblin

	CSprite m_frozenSprite;

	int m_goblinType;                   //the goblin type

	bool m_left;                   //is the goblin looking to the left
	bool m_is_hitting;
	bool m_jumping;
	Vector2i m_PointToGo;          //the point where the goblin should go
	float m_fXVel, m_fYVel;             //the velocity
	float m_fLegsAnimState;           //the animation state of the legs
	float m_fArmAnimState;           //the animation state of the arm
	float m_fWaitToBeat;             //how long must the goblin wait to hit the dwarf?

	float m_fStateTime;               //how long does the current state last?
	int m_fallingSpeed;               //the speed with which the goblin falls
	int m_sideSpeed;

	void CheckState();                 //checks the state
	void NewRandomDestination();        //gets a new random destination
	void CheckXMovement();                //checks the movement in x-direction
	void CheckYMovement();                //checks the movement in y-direction
	bool CheckCollision();                //Checks, if the goblin collided with anything
	void CheckArmAnimation();
};



#endif