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

		//if the new npc is a bunny
		case(BUNNY) :
		{
			CAnimatedAnimal *bunny = new CAnimatedAnimal;
			bunny->Init(_x, _y, m_pWorld, m_pPlayer, m_pView);
			bunny->SetSafe(_safe);
			m_Npcs.push_back(bunny);
		}break;

		//if the new npc is a goblin:
		case(GOBLIN):
		{
			CHumanoid *goblin = new CHumanoid;
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

		//if the new npc is a keykeeper:
		case(KEYKEEPER) :
		{
			CKeyKeeper *keeper = new CKeyKeeper;
			keeper->Init(_x, _y, m_pWorld, m_pPlayer, m_pView);
			keeper->SetSafe(_safe);
			m_Npcs.push_back(keeper);
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
		//check if npc is in range
		if (abs((*i)->GetRect().left - m_pPlayer->GetRect().left) < g_pFramework->GetRenderWindow()->getSize().x + 400 && abs((*i)->GetRect().top - m_pPlayer->GetRect().top) < g_pFramework->GetRenderWindow()->getSize().y + 400)
		{
			//if npc is out of range: despawn it
			if (abs((*i)->GetRect().left - m_pPlayer->GetRect().left) > 2500 || abs((*i)->GetRect().top - m_pPlayer->GetRect().top) > 2500)
			{
				if (!(((*i)->GetID() >= NORMALGOBLIN && (*i)->GetID() <= MAGEGOBLIN) && ((CHumanoid*)(*i))->IsChested()) && (*i)->m_safe == false)
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


			(*i)->CheckEffects();


			//if the arm changed direction the npc is hittable
			if (m_LastArmUp != m_pPlayer->GetArmGoingUp())
				(*i)->m_wasHit = false;



			//if the npc was hit by the player
			if (m_pPlayer->GetWeaponRect().intersects((*i)->GetRect()) && Mouse::isButtonPressed(Mouse::Left))
			{
				if (!(*i)->m_wasHit)
				{
					if (!((m_pPlayer->GetCarriedItem() != NULL && m_pPlayer->GetCarriedItem()->getID() == GOBLINDAGGER) && m_pPlayer->GetArmGoingUp()))
					{
						if ((*i)->GetID() >= NORMALGOBLIN && (*i)->GetID() <= MAGEGOBLIN)
							((CHumanoid*)(*i))->SetChestedFalse();

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
						notify(O_PLAYER, O_HIT, O_GOBLIN);

						//throw the npc if hitted
						if (m_pPlayer->GetRect().left > (*i)->GetRect().left)
							(*i)->ThrowNpc(true, 300);
						else
							(*i)->ThrowNpc(false, 300);
					}
				}
			}
			else
				(*i)->m_wasHit = false;


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

				if ((*i)->GetID() == SKELETONRUNNER)
					((CHumanoid*)(*i))->Explode();

				(*i)->Quit();
				SAFE_DELETE((*i));
				i = m_Npcs.erase(i);
				continue;
			}


			//if the npc despawned: delete it
			if ((*i)->CheckNpc() == false)
			{
				(*i)->Quit();
				SAFE_DELETE((*i));
				i = m_Npcs.erase(i);
				continue;
			}

			//if the player was hit by the npc
			if ((*i)->GetState() == ATTACKING && (*i)->GetWeaponRect().intersects(m_pPlayer->GetRect()))
			{
				if ((*i)->IsHitting())
				{
					//calculate the damage
					int damage = (*i)->GetAttributes()->strength - ((float)(*i)->GetAttributes()->strength * ((float)m_pPlayer->GetPlayerAttributes().armour / 100.0f));

					//subtract the lost health
					m_pPlayer->DoDamage(damage);

					if (m_pPlayer->GetRect().left < (*i)->GetRect().left)
						m_pPlayer->ThrowPlayer(true, 300);
					else
						m_pPlayer->ThrowPlayer(false, 300);
				}
			}
		}

		i++;
	}




	m_LastArmUp = m_pPlayer->GetArmGoingUp();

	g_pProfiler->SetProfilingValue(NPCAMOUNT, (int)m_Npcs.size());
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

			//if player is not below the earth
			if (m_pPlayer->GetRect().top < 800)
			{
				if (m_pWorld->GetNightAlpha() < 200)
				{
					newNPC = rand() % 3 + 1;

					if (newNPC == BEE)
					{
						//spawn new npc
						AddNpc(BEE, spawnPlaces[newPlace].x + 50, spawnPlaces[newPlace].y + 50);
					}
					else if (newNPC == 1)
					{
						//spawn new goblin
						AddNpc(GOBLIN, spawnPlaces[newPlace].x + 50, spawnPlaces[newPlace].y, false, rand()%5 +2);
					}
					else
					{
						//spawn new npc
						AddNpc(BUNNY, spawnPlaces[newPlace].x + 50, spawnPlaces[newPlace].y + 10);
					}


					//get new spawn time
					m_spawnTime = rand() % 80 + 20;
				}
				else
				{
					//spawn new random humanoid
					AddNpc(GOBLIN, spawnPlaces[newPlace].x + 50, spawnPlaces[newPlace].y);

					//get new spawn time
					m_spawnTime = rand() % 20 + 5;
				}
			}
			//if player is below the earth
			else if (m_pView->getCenter().y < (m_pWorld->GetDimensions().y * 100) / 2)
			{
				//spawn new goblin
				AddNpc(GOBLIN, spawnPlaces[newPlace].x + 50, spawnPlaces[newPlace].y, false, rand()%5 +2);

				//get new spawn time
				m_spawnTime = rand() % 80 + 20;
			}
			//if player is in the goblintown
			else if (m_pView->getCenter().y < (m_pWorld->GetDimensions().y * 100) - 15)
			{
				//spawn new goblin
				AddNpc(GOBLIN, spawnPlaces[newPlace].x + 50, spawnPlaces[newPlace].y, false, rand() % 5 + 2);

				//get new spawn time
				m_spawnTime = rand() % 40 + 10;
			}
			//if player is in the dungeon
			else
			{
				newNPC = rand() % 15;

				if (newNPC == 0)
					AddNpc(OGRE, spawnPlaces[newPlace].x + 50, spawnPlaces[newPlace].y);
				else
					AddNpc(GOBLIN, spawnPlaces[newPlace].x + 50, spawnPlaces[newPlace].y);

				//get new spawn time
				m_spawnTime = rand() % 20 + 1;
			}
		}
	}
}



bool CNpcMachine::CheckProjectileOrEffect(CSprite *_sprite, int _damage, int _ID)
{
	stringstream stream;

	list<CNpc*>::iterator i;
	for (i = m_Npcs.begin(); i != m_Npcs.end();)
	{
		//if projectile hits npcs: do damage
		if (_sprite->GetRect().intersects((*i)->GetRect()) && _damage > 0)
		{
			if (_ID == POISONEFFECT)
			{
				(*i)->PoisonNpc(_damage, m_pPlayer->GetPoisonSpellDuration());
				i++;
				continue;
			}

			//calculate the damage
			int damage = _damage - ((float)_damage * ((float)(*i)->GetAttributes()->armour / 100.0f));

			stream.str("");

			//put the damage into a stringstream	
			stream << damage;
			g_pSignMachine->AddString(stream.str(), 1, (*i)->GetRect().left, (*i)->GetRect().top);
			

			//subtract the lost health
			(*i)->GetAttributes()->currentHealth -= damage;

			//plays the hit sound
			notify(O_PLAYER, O_HIT, O_GOBLIN);

			//throw the npc if hitted
			if (m_pPlayer->GetRect().left > (*i)->GetRect().left)
				(*i)->ThrowNpc(true, 200);
			else
				(*i)->ThrowNpc(false, 200);

			//if projectile was iceball: freeze npc
			if (_ID == ICEBALLPROJECTILE)
				(*i)->SetFrozen(_damage*0.5f);

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

				if ((*i)->GetID() == SKELETONRUNNER)
					((CHumanoid*)(*i))->Explode();

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



