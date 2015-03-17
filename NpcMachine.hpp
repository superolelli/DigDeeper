#ifndef NPCMACHINE_HPP
#define NPCMACHINE_HPP

#include "Framework.hpp"
#include "Bee.hpp"
#include "World.hpp"
#include "SignMachine.hpp"

class CNpcMachine
{
public:
	CNpcMachine();

	//Inits the Npc machine
	void Init(CWorld *_world, CPlayer *_player, View *_view, bool _loaded = false);

	//checks all npcs
	void CheckAllNpcs();

	//Renders all npcs
	void RenderAllNpcs();

	//renders the damage indicator
	void RenderDamageIndicator(){m_signMachine.Render();}

	//adds a npc
	void AddNpc(int _ID, int _x, int _y);

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
		}while(a != 1000);
	}

	BOOST_SERIALIZATION_SPLIT_MEMBER();
	

	list<CNpc*> m_Npcs;         //all npcs
	CWorld *m_pWorld;             //pointer to the world
	CPlayer *m_pPlayer;           //pointer to the player
	View * m_pView;               //the view

	CSignMachine m_signMachine;       //the sign machine

	bool m_LastArmUp;               //was the arm going up last frame?
	float m_spawnTime;              //the time until something spawns

	void SpawnNpcs();                //spawns new npcs

};

#endif