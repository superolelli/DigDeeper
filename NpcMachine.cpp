#include "NpcMachine.hpp"
#include "World.hpp"



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
			(*i)->Init(0, 0, m_pWorld, m_pPlayer, m_pView, -1, true);
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

	g_pSignMachine->Quit();
}



void CNpcMachine::AddNpc(int _ID, int _x, int _y, bool _safe, int _specialID)
{
	switch(_ID)
	{
		//if the new npc is a bee:
		case(BEE):
		{
			CBee *bee = new CBee;
			bee->Init(_x, _y, m_pWorld, m_pPlayer, m_pView);
			bee->SetSafe(_safe);
			m_Npcs.push_back(bee);
		}break;

		//if the new npc is a goblin:
		case(GOBLIN):
		{
			CGoblin *goblin = new CGoblin;
			goblin->Init(_x, _y, m_pWorld, m_pPlayer, m_pView, _specialID);
			goblin->SetSafe(_safe);
			m_Npcs.push_back(goblin);
		}break;

		//if the new npc is an ogre:
		case(OGRE) :
		{
			COgre *ogre = new COgre;
			ogre->Init(_x, _y, m_pWorld, m_pPlayer, m_pView);
			ogre->SetSafe(_safe);
			m_Npcs.push_back(ogre);
		}break;
	}
}



void CNpcMachine::CheckAllNpcs()
{
	cout << "NPC-Machine: Check Npcs" << endl;
	//spawns new Npcs
	SpawnNpcs();

	stringstream stream;

	list<CNpc*>::iterator i;
	for(i = m_Npcs.begin(); i != m_Npcs.end();)
	{
		//if npc is out of range: despawn it
		if (abs((*i)->GetRect().left - m_pPlayer->GetRect().left) > 2500 || abs((*i)->GetRect().top - m_pPlayer->GetRect().top) > 2500)
		{
			if (!((*i)->GetID() == GOBLIN && ((CGoblin*)(*i))->IsChested()) && (*i)->m_safe == false)
			{
				(*i)->Quit();
				SAFE_DELETE((*i));
				i = m_Npcs.erase(i);
				continue;
			}
			else if ((*i)->m_safe)
			{
				i++;
				continue;
			}
		}


		//if the npc despawned: delete it
		if ((*i)->CheckNpc() == false)
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
				if (!(m_pPlayer->GetCarriedItem()->getID() == GOBLINDAGGER && m_pPlayer->GetArmGoingUp()))
				{
					if ((*i)->GetID() == GOBLIN)
						((CGoblin*)(*i))->SetChestedFalse();

					//set was hit to true
					(*i)->m_wasHit = true;

					//calculate the damage
					int damage = m_pPlayer->GetPlayerAttributes().strength - ((float)m_pPlayer->GetPlayerAttributes().strength * ((float)(*i)->GetAttributes()->armour / 100.0f));

					stream.str("");

					if (rand() % 100 < m_pPlayer->GetPlayerAttributes().criticalChance)
					{
						damage += damage * m_pPlayer->GetPlayerAttributes().criticalDamage / 10;

						//put the damage into a stringstream	
						stream << damage;
						g_pSignMachine->AddString(stream.str(), 1, (*i)->GetRect().left, (*i)->GetRect().top, Color(150, 0, 0));
					}
					else
					{
						//put the damage into a stringstream	
						stream << damage;
						g_pSignMachine->AddString(stream.str(), 1, (*i)->GetRect().left, (*i)->GetRect().top);
					}

					//subtract the lost health
					(*i)->GetAttributes()->currentHealth -= damage;

					//reset if npc was frozen
					(*i)->SetFrozen(0.0f);

					//play the hit sound
					(*i)->PlayHitSound();

					//throw the npc if hitted
					if (m_pPlayer->GetRect().left > (*i)->GetRect().left)
						(*i)->ThrowNpc(true, 300);
					else
						(*i)->ThrowNpc(false, 300);



					//shows the damage


					//if the npc died: delete it 
					if ((*i)->GetAttributes()->currentHealth <= 0)
					{
						//give loot
						vector<SItem> loot = (*i)->GetLoot();
						for (int a = 0; a != loot.size(); a++)
						{
							//if thing is tool or equipment: save attributes
							if (loot[a].thing->getID() > CTBREAK)
								m_pWorld->AddLittleItem(loot[a].thing, (*i)->GetRect().left, (*i)->GetRect().top);
							else
							{
								m_pWorld->AddLittleItem(loot[a].thing->getID(), (*i)->GetRect().left, (*i)->GetRect().top, loot[a].amount);
								SAFE_DELETE(loot[a].thing);
							}
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
		}
		else
			(*i)->m_wasHit = false;

		//if the player was hit by the npc
		if ((*i)->GetState() == ATTACKING && (*i)->GetWeaponRect().intersects(m_pPlayer->GetRect()))
		{	
			if ((*i)->IsHitting())
			{
				//calculate the damage
				int damage = (*i)->GetAttributes()->strength - ((float)(*i)->GetAttributes()->strength * ((float)m_pPlayer->GetPlayerAttributes().armour/100.0f));

				//subtract the lost health
				m_pPlayer->DoDamage(damage);

				if (m_pPlayer->GetRect().left < (*i)->GetRect().left)
					m_pPlayer->ThrowPlayer(true, 300);
				else
					m_pPlayer->ThrowPlayer(false, 300);


				//put the damage into a stringstream
				stream.str("");
				stream << damage;

				//shows the damage
				g_pSignMachine->AddString(stream.str(), 1, m_pPlayer->GetRect().left, m_pPlayer->GetRect().top);
			}
		}

		i++;
	}




	m_LastArmUp = m_pPlayer->GetArmGoingUp();

	g_pProfiler->SetProfilingValue(NPCAMOUNT, (int)m_Npcs.size());

	cout << "NPC-Machine: Checked Npcs" << endl;
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
	int newNPC = 0;

	m_spawnTime -= g_pTimer->GetElapsedTime().asSeconds();

	if(m_spawnTime <= 0)
	{
		//get all places, where npcs could spawn
		vector<Vector2i> spawnPlaces = m_pWorld->GetSpawnPlaces();

		//get a random spawn place
		int newPlace = rand()%spawnPlaces.size();

		if (spawnPlaces.size() > 0)
		{
			//if it is day:
			if (m_pWorld->GetNightAlpha() < 200)
			{
				newNPC = rand() % 2 + 1;

				if (newNPC == BEE)
				{
					//spawn new npc
					AddNpc(newNPC, spawnPlaces[newPlace].x + 50, spawnPlaces[newPlace].y + 50);
				}
				else
				{
					//spawn new npc
					AddNpc(newNPC, spawnPlaces[newPlace].x + 50, spawnPlaces[newPlace].y);
				}


				//get new spawn time
				m_spawnTime = rand() % 80 + 20;
			}
			//if it is night
			else
			{
				//spawn new goblin
				AddNpc(GOBLIN, spawnPlaces[newPlace].x + 50, spawnPlaces[newPlace].y);

				//get new spawn time
				m_spawnTime = rand() % 20 + 1;
			}
		}
	}
}



bool CNpcMachine::CheckProjectile(SProjectile *_projectile)
{
	stringstream stream;

	list<CNpc*>::iterator i;
	for (i = m_Npcs.begin(); i != m_Npcs.end();)
	{
		//if projectile hits npcs: do damage
		if (_projectile->m_Sprite->GetRect().intersects((*i)->GetRect()) && _projectile->m_Damage > 0)
		{
			//calculate the damage
			int damage = _projectile->m_Damage - ((float)_projectile->m_Damage * ((float)(*i)->GetAttributes()->armour / 100.0f));

			stream.str("");

			//put the damage into a stringstream	
			stream << damage;
			g_pSignMachine->AddString(stream.str(), 1, (*i)->GetRect().left, (*i)->GetRect().top);
			

			//subtract the lost health
			(*i)->GetAttributes()->currentHealth -= damage;

			//plays the hit sound
			(*i)->PlayHitSound();

			//throw the npc if hitted
			if (m_pPlayer->GetRect().left > (*i)->GetRect().left)
				(*i)->ThrowNpc(true, 200);
			else
				(*i)->ThrowNpc(false, 200);

			//if projectile was iceball: freeze npc
			if (_projectile->m_ID == ICEBALLPROJECTILE)
				(*i)->SetFrozen(_projectile->m_Damage*0.5f);

			//if the npc died: delete it 
			if ((*i)->GetAttributes()->currentHealth <= 0)
			{
				//give loot
				vector<SItem> loot = (*i)->GetLoot();
				for (int a = 0; a != loot.size(); a++)
				{
					//if thing is tool or equipment: save attributes
					if (loot[a].thing->getID() > CTBREAK)
						m_pWorld->AddLittleItem(loot[a].thing, (*i)->GetRect().left, (*i)->GetRect().top);
					else
					{
						m_pWorld->AddLittleItem(loot[a].thing->getID(), (*i)->GetRect().left, (*i)->GetRect().top, loot[a].amount);
						SAFE_DELETE(loot[a].thing);
					}
				}

				//adds the experience
				m_pPlayer->AddExp((*i)->GetAttributes()->exp);

				(*i)->Quit();
				SAFE_DELETE((*i));
				i = m_Npcs.erase(i);
				continue;
			}


			return true;
		}

		i++;
	}

	return false;
}




