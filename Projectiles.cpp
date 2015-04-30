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
			m_pWorld->GetLightMachine()->AddLightCircle(i->m_Sprite->GetRect().left + i->m_Sprite->GetRect().width / 2, i->m_Sprite->GetRect().top + i->m_Sprite->GetRect().height / 2, 100, Color::White);

		i->m_Sprite->Render(g_pFramework->GetWindow());
	}
}




void CProjectiles::NewProjectile(SProjectile _projectile)
{
	m_Projectiles.push_back(_projectile);
}


void CProjectiles::CheckProjectiles()
{
	float moveX, moveY;
	list<SProjectile>::iterator i;
	for (i = m_Projectiles.begin(); i != m_Projectiles.end();)
	{
		//check if projectile collides with block
		if (m_pWorld->isBlockPassable(i->m_Sprite->GetRect().left / 100, i->m_Sprite->GetRect().top / 100))
		{
			moveX = i->m_fXVel * g_pTimer->GetElapsedTime().asSeconds();
			moveY = i->m_fYVel* g_pTimer->GetElapsedTime().asSeconds();
			i->m_Sprite->Move(moveX, moveY);
			i->m_fFlown += abs(moveX) + abs(moveY);

			if (i->m_fFlown >= i->m_flightLength)
			{
				i = m_Projectiles.erase(i);
				continue;
			}
		}
		else
		{
			i = m_Projectiles.erase(i);
			continue;
		}

		//check if projectile collides with player 
		if (m_pPlayer->GetRect().intersects(i->m_Sprite->GetRect()) && !i->m_fromPlayer)
		{
			m_pPlayer->DoDamage(i->m_Damage - (i->m_Damage * (m_pPlayer->GetPlayerAttributes().armour / 100)));
			i = m_Projectiles.erase(i);
			continue;
		}
			
		//check if projectile collides with npc
		if (i->m_fromPlayer)
		{
			if (m_pNpcs->CheckProjectile(&*i))
			{
				i = m_Projectiles.erase(i);
				continue;
			}
		}


		i++;
	}
}