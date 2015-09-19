#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include "NPC.hpp"


class CAnimatedAnimal : public CNpc
{
public:

	void Init(int _x, int _y, CWorld *_world, CPlayer *_player, View *_view, int _specialID = -1, bool _loaded = false);
	bool CheckNpc();
	void Render();
	void Quit();
	IntRect GetRect(){ return m_pAnimalSprite->GetRect(); }
	IntRect GetWeaponRect(){ return m_pAnimalSprite->GetRect(); }
	bool IsHitting(){ return false; }
	void ThrowNpc(bool _left, int _strength);
	void SetFleeing(){ m_State = FLEEING; }

	vector<SItem> GetLoot();

private:
	friend class boost::serialization::access;

	//saves the equipment
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<CNpc>(*this);
		ar & m_left;
		ar & m_PointToGo;
	}



	CSprite *m_pAnimalSprite;              //the sprite
	CSprite m_frozenSprite;

	bool m_left;                   //is the animal looking to the left
	bool m_jumping;
	int m_PointToGo;          //the point where the animal should go
	float m_fXVel, m_fYVel;             //the velocity
	int m_fallingSpeed;               //the speed with which the goblin falls
	int m_sideSpeed;

	float m_fIdleTimer;
	float m_fAnimState;

	void CheckState();
	bool CheckCollision();            //would the animal collide with something
	void CheckXMovement();                //checks the movement in x-direction
	void CheckYMovement();                //checks the movement in y-direction
	void NewPointToGo();                 //gets a new point to go
};

BOOST_CLASS_VERSION(CAnimatedAnimal, 0)

#endif
