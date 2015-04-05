#ifndef BEE_HPP
#define BEE_HPP

#include "NPC.hpp"


class CBee : public CNpc
{
public:

	void Init(int _x, int _y, CWorld *_world, CPlayer *_player, View *_view, bool _loaded = false);
	bool CheckNpc();
	void Render();
	void Quit();
	IntRect GetRect(){ return m_pBeeSprite->GetRect();}
	IntRect GetWeaponRect(){ return m_pBeeSprite->GetRect(); }
	bool IsHitting(){ return false; }

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

	CSprite *m_pBeeSprite;              //the sprite

	bool m_left;                   //is the bee looking to the left
	Vector2i m_PointToGo;          //the point where the bee should go
	int m_XVel, m_YVel;             //the velocity

	bool CheckCollisions();            //would the bee collide with something
	void NewPointToGo();                 //gets a new point to go


};



#endif