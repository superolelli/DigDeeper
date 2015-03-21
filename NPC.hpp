#ifndef NPC_HPP
#define NPC_HPP

#include "Framework.hpp"
#include "Structures.hpp"
#include "World.hpp"

class CNpc
{
public:
	CNpc();

	virtual void Init(int _x, int _y, CWorld *_world, bool _loaded = false) = 0;
	virtual bool CheckNpc() = 0;
	virtual vector<SItem> GetLoot() = 0;
	virtual void Render() = 0;
	virtual void Quit() = 0;
	virtual IntRect GetRect() = 0;

	SNpcAttributes* GetAttributes(){return &m_Attributes;}
	int GetID(){return m_ID;}

	bool m_wasHit;                          //was the npc hit?

protected:
	friend class boost::serialization::access;

	//saves the thing
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version) 
	{
		ar & m_ID;
		ar & m_xPos;
		ar & m_yPos;
		ar & m_Attributes.currentHealth;
	}

	SNpcAttributes m_Attributes;           //the npc's attributes
	int m_State;                           //the current state
	int m_ID;                              //the npc's id
	int m_xPos;
	int m_yPos; 

	CWorld *m_pWorld;                         //a pointer to the world

};



#endif