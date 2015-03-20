#include "NpcMachine.hpp"




CNpcMachine::CNpcMachine()
{
	m_pWorld = NULL;
	m_pPlayer = NULL;

	m_Npcs.clear();
}



void CNpcMachine::Init(CWorld *_world, CPlayer *_player, View *_view, bool _loaded)
{
	m_pWorld = _world;
	m_pPlayer = _player;
	m_pView = _view;

	m_LastArmUp = false;

	if(_loaded)
	{
		list<CNpc*>::iterator i;
		for(i = m_Npcs.begin(); i != m_Npcs.end(); i++)
			(*i)->Init(0, 0, m_pWorld, true);
	}
}



void CNpcMachine::Quit()
{
	list<CNpc*>::iterator i;
	for(i = m_Npcs.begin(); i != m_Npcs.end(); i++)
	{
		(*i)->Quit();
		SAFE_DELETE(*i);
	}

	m_Npcs.clear();

	m_signMachine.Quit();
}



void CNpcMachine::AddNpc(int _ID, int _x, int _y)
{
	switch(_ID)
	{
		//if the new npc is a bee:
		case(BEE):
		{
			CBee *bee = new CBee;
			bee->Init(_x, _y, m_pWorld);
			m_Npcs.push_back(bee);
		}break;

		//if the new npc is a goblin:
		case(GOBLIN):
		{
			CGoblin *goblin = new CGoblin;
			goblin->Init(_x, _y, m_pWorld);
			m_Npcs.push_back(goblin);
		}break;
	}
}



void CNpcMachine::CheckAllNpcs()
{
	//spawns new Npcs
	SpawnNpcs();

	stringstream stream;

	list<CNpc*>::iterator i;
	for(i = m_Npcs.begin(); i != m_Npcs.end();)
	{
		//if the npc despawned: delete it
		if((*i)->CheckNpc() == false)
		{
			(*i)->Quit();
			SAFE_DELETE((*i));
			i = m_Npcs.erase(i);
			continue;
		}

		//if the arm changed direction the npc is hittable
		if(m_LastArmUp != m_pPlayer->GetArmGoingUp())
			(*i)->m_wasHit = false;

		//if the npc was hit by the player
		if(m_pPlayer->GetWeaponRect().intersects((*i)->GetRect()) && Mouse::isButtonPressed(Mouse::Left))
		{
			if(!(*i)->m_wasHit)
			{
				//set was hit to true
				(*i)->m_wasHit = true;

				//calculate the damage
				int damage = m_pPlayer->GetPlayerAttributes().strength;

				//subtract the lost health
				(*i)->GetAttributes()->currentHealth -= damage;

				//put the damage into a stringstream
				stream.str("");
				stream << damage;

				//shows the damage
				m_signMachine.AddString(stream.str(), 1, (*i)->GetRect().left, (*i)->GetRect().top);

				//if the npc died: delete it 
				if((*i)->GetAttributes()->currentHealth <= 0)
				{
					//give loot
					vector<SItem> loot = (*i)->GetLoot();
					for(int a = 0; a != loot.size(); a++)
					{
						m_pWorld->AddLittleItem(loot[a].thing->getID(), (*i)->GetRect().left, (*i)->GetRect().top, loot[a].amount);
					}

					//adds the experience
					m_pPlayer->AddExp((*i)->GetAttributes()->exp);

					(*i)->Quit();
					SAFE_DELETE((*i));
					i = m_Npcs.erase(i);
					continue;
				}
			}
		}
		else
			(*i)->m_wasHit = false;

		i++;
	}


	m_LastArmUp = m_pPlayer->GetArmGoingUp();
}




void CNpcMachine::RenderAllNpcs()
{
	list<CNpc*>::iterator i;
	for(i = m_Npcs.begin(); i != m_Npcs.end(); i++)
	{
		(*i)->Render();
	}
}




void CNpcMachine::SpawnNpcs()
{
	m_spawnTime -= g_pTimer->GetElapsedTime().asSeconds();

	if(m_spawnTime <= 0)
	{
		//get the rect of the view
		IntRect viewRect;
		viewRect.left = m_pView->getCenter().x - m_pView->getSize().x/2;
		viewRect.top = m_pView->getCenter().y - m_pView->getSize().y/2;
		viewRect.width = m_pView->getSize().x;
		viewRect.height = m_pView->getSize().y;

		//get all places, where npcs could spawn
		vector<Vector2i> spawnPlaces = m_pWorld->GetSpawnPlaces(viewRect);

		//get a random spawn place
		int newPlace = rand()%spawnPlaces.size();

		if(spawnPlaces.size() > 0)
		{
			//spawn new npc
			AddNpc(BEE, spawnPlaces[newPlace].x + 50, spawnPlaces[newPlace].y + 50);
		}

		//get new spawn time
		m_spawnTime = rand()%40 + 20;
	}
}