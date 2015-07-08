#ifndef NPCMACHINE_HPP
#define NPCMACHINE_HPP

#include "Framework.hpp"
#include "Bee.hpp"
#include "Goblin.hpp"
#include "Ogre.hpp"
#include "SignMachine.hpp"
#include "Profiler.hpp"

class CWorld;

class CNpcMachine
{
public:
	CNpcMachine();

	//Inits the Npc machine
	void Init(CWorld *_world, CPlayer *_player, View *_view, bool _loaded = false);

	//checks all npcs
	void CheckAllNpcs();

	//checks if a npc was hit by a projectile
	bool CheckProjectile(SProjectile *_projectile);

	//Renders all npcs
	void RenderAllNpcs();

	//renders the damage indicator
	void RenderDamageIndicator(){g_pSignMachine->Render();}

	//adds a npc
	void AddNpc(int _ID, int _x, int _y, int _specialID = -1);

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
			else if (n->GetID() == GOBLIN)
			{
				CGoblin* goblin = (CGoblin*)n;
				a = goblin->GetID();
				ar & a;
				ar & goblin;
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
			else if (a == GOBLIN)
			{
				CGoblin *goblin = new CGoblin;
				ar & goblin;
				m_Npcs.push_back(goblin);
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

#endif