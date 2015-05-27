#include "Projectiles.hpp"
#include "NpcMachine.hpp"


CProjectiles::CProjectiles()
{
	m_Projectiles.clear();
}



CProjectiles::~CProjectiles()
{
	m_pWorld = NULL;
	m_pPlayer = NULL;
	m_pNpcs = NULL;
}


void CProjectiles::Init(CWorld *_world, CPlayer *_player, CNpcMachine *_Npcs)
{
	m_pWorld = _world;
	m_pPlayer = _player;
	m_pNpcs = _Npcs;
}


void CProjectiles::Quit()
{
	list<SProjectile>::iterator i;
	for (i = m_Projectiles.begin(); i != m_Projectiles.end(); i++)
	{
		SAFE_DELETE(i->m_Sprite);
	}

	m_Projectiles.clear();
}



void CProjectiles::Render()
{
	list<SProjectile>::iterator i;
	for (i = m_Projectiles.begin(); i != m_Projectiles.end(); i++)
	{
		if (i->m_ID == FIREBALLPROJECTILE)
			m_pWorld->GetLightMachine()->AddLightCircle(i->m_Sprite->GetRect().left + i->m_Sprite->GetRect().width / 2, i->m_Sprite->GetRect().top + i->m_Sprite->GetRect().height / 2, 100, Color(0,0,0,0));

		if (i->m_fAnimState == -1)
			i->m_Sprite->Render(g_pFramework->GetRenderWindow());
		else
			i->m_Sprite->Render(g_pFramework->GetRenderWindow(), i->m_fAnimState);
	}
}




void CProjectiles::NewProjectile(SProjectile _projectile)
{
	m_Projectiles.push_back(_projectile);
}


void CProjectiles::CheckProjectiles()
{
	float moveX, moveY;
	bool collided = false;
	list<SProjectile>::iterator i;
	for (i = m_Projectiles.begin(); i != m_Projectiles.end();)
	{
		collided = false;

		//check for explosions and healing
		if (i->m_ID == EXPLOSION || i->m_ID == HEALING || i->m_ID == ALCHEMYANIMATION)
		{
			i->m_fAnimState += 20 * g_pTimer->GetElapsedTime().asSeconds();

			if (i->m_ID == HEALING)
				i->m_Sprite->SetPos(m_pPlayer->GetRect().left - 30, m_pPlayer->GetRect().top);

			if (i->m_fAnimState >= 5)
			{
				i = m_Projectiles.erase(i);
				continue;
			}

			i++;
			continue;
		}

		//check for collisions
		if (i->m_fXVel < 0)
			collided = m_pWorld->isBlockPassable(i->m_Sprite->GetRect().left / 100, i->m_Sprite->GetRect().top / 100);
		else
			collided = m_pWorld->isBlockPassable((i->m_Sprite->GetRect().left+70) / 100, (i->m_Sprite->GetRect().top +15) / 100);

			//if collided: erase projectile
			if (collided)
			{
				moveX = i->m_fXVel * g_pTimer->GetElapsedTime().asSeconds();
				moveY = i->m_fYVel* g_pTimer->GetElapsedTime().asSeconds();
				i->m_Sprite->Move(moveX, moveY);
				i->m_fFlown += abs(moveX) + abs(moveY);

				if (i->m_fFlown >= i->m_flightLength)
				{
					if (i->m_ID == FIREBALLPROJECTILE)
					{
						int x = i->m_Sprite->GetRect().left;
						int y = i->m_Sprite->GetRect().top;
						SAFE_DELETE(i->m_Sprite);
						i->m_Sprite = new CSprite;
						i->m_ID = EXPLOSION;
						i->m_fAnimState = 0;
						i->m_Sprite->Load(&g_pTextures->t_explosion, 5, 100, 100);

						if (i->m_fXVel < 0)
							i->m_Sprite->SetPos(x - 40, y - 40);
						else
							i->m_Sprite->SetPos(x + 20, y - 40);

						i++;
					}
					else
						i = m_Projectiles.erase(i);

					continue;
				}
			}
			else
			{
				if (i->m_ID == FIREBALLPROJECTILE)
				{
					int x = i->m_Sprite->GetRect().left;
					int y = i->m_Sprite->GetRect().top;
					SAFE_DELETE(i->m_Sprite);
					i->m_Sprite = new CSprite;
					i->m_ID = EXPLOSION;
					i->m_fAnimState = 0;
					i->m_Sprite->Load(&g_pTextures->t_explosion, 5, 100, 100);

					if (i->m_fXVel < 0)
						i->m_Sprite->SetPos(x - 40, y - 40);
					else
						i->m_Sprite->SetPos(x + 20, y - 40);

					i++;
				}
				else
					i = m_Projectiles.erase(i);

				continue;
			}

		//check if projectile collides with player 
		if (m_pPlayer->GetRect().intersects(i->m_Sprite->GetRect()) && !i->m_fromPlayer)
		{
			m_pPlayer->DoDamage(i->m_Damage - (i->m_Damage * (m_pPlayer->GetPlayerAttributes().armour / 100)));

			if (i->m_ID == FIREBALLPROJECTILE)
			{
				int x = i->m_Sprite->GetRect().left;
				int y = i->m_Sprite->GetRect().top;
				SAFE_DELETE(i->m_Sprite);
				i->m_Sprite = new CSprite;
				i->m_ID = EXPLOSION;
				i->m_fAnimState = 0;
				i->m_Sprite->Load(&g_pTextures->t_explosion, 5, 100, 100);

				if (i->m_fXVel < 0)
					i->m_Sprite->SetPos(x - 40, y - 40);
				else
					i->m_Sprite->SetPos(x + 20, y - 40);

				i++;
			}
			else
				i = m_Projectiles.erase(i);

			continue;
		}
			
		//check if projectile collides with npc
		if (i->m_fromPlayer)
		{
			if (m_pNpcs->CheckProjectile(&*i))
			{
				cout << "Projectile collided with npc" << endl;
				if (i->m_ID == FIREBALLPROJECTILE)
				{
					int x = i->m_Sprite->GetRect().left;
					int y = i->m_Sprite->GetRect().top;
					SAFE_DELETE(i->m_Sprite);
					i->m_Sprite = new CSprite;
					i->m_ID = EXPLOSION;
					i->m_fAnimState = 0;
					i->m_Sprite->Load(&g_pTextures->t_explosion, 5, 100, 100);

					if (i->m_fXVel < 0)
						i->m_Sprite->SetPos(x - 40, y - 40);
					else
						i->m_Sprite->SetPos(x + 20, y - 40);

					i++;
				}
				else
					i = m_Projectiles.erase(i);

				continue;
			}
		}


		i++;
	}
}