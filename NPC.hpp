#ifndef NPC_HPP
#define NPC_HPP

#include "Framework.hpp"
#include "Structures.hpp"
#include "Player.hpp"

class CWorld;

class CNpc
{
public:
	CNpc();

	virtual void Init(int _x, int _y, CWorld *_world, CPlayer *_player, View *_view, int _specialID, bool _loaded = false) = 0;
	virtual bool CheckNpc() = 0;
	virtual vector<SItem> GetLoot() = 0;
	virtual void Render() = 0;
	virtual void Quit() = 0;
	virtual IntRect GetRect() = 0;
	virtual IntRect GetWeaponRect() = 0;
	virtual bool IsHitting() = 0;
	virtual void ThrowNpc(bool _left, int _strength) = 0;

	SNpcAttributes* GetAttributes(){return &m_Attributes;}
	int GetID(){return m_ID;}
	int GetState(){return m_State;}
	void SetFrozen(float _frozenTime);
	void SetSafe(bool _safe){ m_safe = _safe; }
	void AddEffect(SNpcEffect _effect){m_Attributes.effects.push_back(_effect);}
	void PoisonNpc(int _strength, float _duration);
	void CheckEffects();

	bool m_wasHit;                          //was the npc hit?
	bool m_safe;

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
		ar & m_safe;

		if (version > 0)
			ar & m_Attributes.effects;
		else
			m_Attributes.effects.clear();
	}

	//finds the shortest path to a destination
	Vector2i findPath(int _xDest, int _yDest);

	SNpcAttributes m_Attributes;           //the npc's attributes
	int m_State;                           //the current state
	int m_ID;                              //the npc's id
	int m_xPos;
	int m_yPos; 

	float m_fFrozenTimer;
	float m_fSecondsTimer;

	CWorld *m_pWorld;                         //a pointer to the world
	CPlayer *m_pPlayer;
	View *m_pView;

};

BOOST_CLASS_VERSION(CNpc, 0)

#endif