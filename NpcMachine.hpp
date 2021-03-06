#ifndef NPCMACHINE_HPP
#define NPCMACHINE_HPP

#include "Framework.hpp"
#include "Bee.hpp"
#include "Goblin.hpp"
#include "Ogre.hpp"
#include "Keykeeper.hpp"
#include "AnimatedAnimal.hpp"
#include "SignMachine.hpp"
#include "Profiler.hpp"

class CWorld;

class CNpcMachine : public CSubject
{
public:
	CNpcMachine();

	//Inits the Npc machine
	void Init(CWorld *_world, CPlayer *_player, View *_view, bool _loaded = false);

	//checks all npcs
	void CheckAllNpcs();

	//checks if a npc was hit by a projectile
	bool CheckProjectileOrEffect(CSprite *_sprite, int _damage, int _ID);

	//Renders all npcs
	void RenderAllNpcs();

	//renders the damage indicator
	void RenderDamageIndicator(){g_pSignMachine->Render();}

	//adds a npc
	void AddNpc(int _ID, int _x, int _y, bool m_safe = false, int _specialID = -1);

	void Quit();


private:
	friend class boost::serialization::access;

	template<class Archive>
	void save(Archive & ar, const unsigned int version) const
	{
		int a;
		BOOST_FOREACH(CNpc* n, m_Npcs)
		{
			if(n->GetID() == BEE)
			{
				CBee* bee = (CBee*)n;
				a = bee->GetID();
				ar & a;
				ar & bee;
			}
			else if (n->GetID() >= NORMALGOBLIN && n->GetID() <= MAGEGOBLIN)
			{
				CHumanoid* goblin = (CHumanoid*)n;
				a = goblin->GetID();
				ar & a;
				ar & goblin;
			}
			else if (n->GetID() == OGRE)
			{
				COgre* ogre = (COgre*)n;
				a = ogre->GetID();
				ar & a;
				ar & ogre;
			}
			else if (n->GetID() == KEYKEEPER)
			{
				CKeyKeeper* keeper = (CKeyKeeper*)n;
				a = keeper->GetID();
				ar & a;
				ar & keeper;
			}
		}

		a = 1000;
		ar << a;
	}

	template<class Archive>
	void load(Archive & ar, const unsigned int version) 
	{
		int a = -1;
		do
		{
			//load the ID of the next npc
			ar & a;
			if(a == BEE)
			{
				CBee *bee = new CBee;
				ar & bee;
				m_Npcs.push_back(bee);
			}
			else if (a >= NORMALGOBLIN && a <= MAGEGOBLIN)
			{
				CHumanoid *goblin = new CHumanoid;
				ar & goblin;
				m_Npcs.push_back(goblin);
			}
			else if (a == OGRE)
			{
				COgre *ogre = new COgre;
				ar & ogre;
				m_Npcs.push_back(ogre);
			}
			else if (a == KEYKEEPER)
			{
				CKeyKeeper *keeper = new CKeyKeeper;
				ar & keeper;
				m_Npcs.push_back(keeper);
			}
		}while(a != 1000);
	}

	BOOST_SERIALIZATION_SPLIT_MEMBER();
	

	list<CNpc*> m_Npcs;         //all npcs
	CWorld *m_pWorld;             //pointer to the world
	CPlayer *m_pPlayer;           //pointer to the player
	View * m_pView;               //the view

	bool m_LastArmUp;               //was the arm going up last frame?
	float m_spawnTime;              //the time until something spawns

	void SpawnNpcs();                //spawns new npcs

};

BOOST_CLASS_VERSION(CNpcMachine, 0)

#endif