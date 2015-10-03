#include "Effects.hpp"
#include "NpcMachine.hpp"


CEffects::CEffects()
{
	m_Effects.clear();
}



CEffects::~CEffects()
{
	m_pWorld = NULL;
	m_pPlayer = NULL;
	m_pNpcs = NULL;
}


void CEffects::Init(CWorld *_world, CPlayer *_player, CNpcMachine *_Npcs)
{
	m_pWorld = _world;
	m_pPlayer = _player;
	m_pNpcs = _Npcs;
}


void CEffects::Quit()
{
	list<SEffect>::iterator i;
	for (i = m_Effects.begin(); i != m_Effects.end(); i++)
	{
		SAFE_DELETE(i->m_Sprite);
	}

	m_Effects.clear();
}



void CEffects::Render()
{
	list<SEffect>::iterator i;
	for (i = m_Effects.begin(); i != m_Effects.end(); i++)
	{
		if (i->m_lightRadius > 0)
			m_pWorld->GetLightMachine()->AddLightCircle(i->m_Sprite->GetRect().left + i->m_Sprite->GetRect().width / 2, i->m_Sprite->GetRect().top + i->m_Sprite->GetRect().height / 2, i->m_lightRadius, Color(0, 0, 0, 0));
	
		if (i->m_fAnimState == -1)
			i->m_Sprite->Render(g_pFramework->GetRenderWindow());
		else
			i->m_Sprite->Render(g_pFramework->GetRenderWindow(), i->m_fAnimState);
	}
}




void CEffects::NewEffect(SEffect _effect)
{
	m_Effects.push_back(_effect);
}




void CEffects::CheckEffects()
{
	float moveX, moveY;
	list<SEffect>::iterator i;
	for (i = m_Effects.begin(); i != m_Effects.end();)
	{
		//animate the effect
		if (i->m_frameNumber > 1)
			i->m_fAnimState += i->m_animSpeed * g_pTimer->GetElapsedTime().asSeconds();
		
		//check animation
		if (i->m_type == LOCALEFFECT_ONCE || i->m_type == MOVINGEFFECT_ONCE)
		{
			//if effect is finished: delete it
			if (i->m_fAnimState >= i->m_frameNumber)
			{
				SAFE_DELETE(i->m_Sprite);
				i = m_Effects.erase(i);
				continue;
			}
		}
		else
		{
			//if effect is finished: restart it
			if (i->m_fAnimState >= i->m_frameNumber)
				i->m_fAnimState = 0;

			//check duration
			i->m_fDuration -= g_pTimer->GetElapsedTime().asSeconds();

			if (i->m_fDuration <= 0)
			{
				if (i->m_ID == DYNAMITEEFFECT)
				{
					g_pEffects->AddEffect(EXPLOSION, i->m_Sprite->GetRect().left - 40, i->m_Sprite->GetRect().top - 40, NULL, NULL);		

					//check for blocks
					for (int x = ((*i->m_movingXPos + 20) / 100) - 1; x < ((*i->m_movingXPos + 20) / 100) + 2; x++)
					{
						for (int y = (*i->m_movingYPos / 100) - 1; y < (*i->m_movingYPos / 100) + 2; y++)
						{
							m_pWorld->DeleteBlock(x, y);
						}
					}

					//check if it hits npc
					m_pNpcs->CheckProjectileOrEffect(i->m_Sprite, 30, i->m_ID);

					//check if it hits player
					if (m_pPlayer->GetRect().intersects(IntRect(i->m_Sprite->GetRect().left -40, i->m_Sprite->GetRect().top- 40, 100, 100)))
					{
						m_pPlayer->DoDamage(30 - (30 * (m_pPlayer->GetPlayerAttributes().armour / 100)));

						//throw player
						if (m_pPlayer->GetRect().left < i->m_Sprite->GetRect().left -40)
							m_pPlayer->ThrowPlayer(true, 200);
						else
							m_pPlayer->ThrowPlayer(false, 200);
					}
				}

				SAFE_DELETE(i->m_Sprite);
				i = m_Effects.erase(i);
				continue;
			}
		}


		//check movement
		if (i->m_type == MOVINGEFFECT_ONCE || i->m_type == MOVINGEFFECT_LOOP)
		{
			i->m_Sprite->SetPos(*i->m_movingXPos + i->m_xDifference, *i->m_movingYPos + i->m_yDifference);
		}


		i++;
	}
}





void CEffects::AddEffect(int _ID, int _x, int _y, int *_movingX, int *_movingY, int _duration)
{
	SEffect effect;
	CSprite *sprite = new CSprite;

	effect.m_ID = _ID;
	effect.m_animSpeed = 20;
	effect.m_fAnimState = 0;
	effect.m_fDuration = _duration;
	effect.m_frameNumber = 5;
	effect.m_lightRadius = 0;
	effect.m_xDifference = 0;
	effect.m_yDifference = 0;
	effect.m_xPos = _x;
	effect.m_yPos = _y;
	effect.m_movingXPos = _movingX;
	effect.m_movingYPos = _movingY;
	

	switch (_ID)
	{
	case(EXPLOSION):
		sprite->Load(&g_pTextures->t_explosion, 5, 100, 100);
		effect.m_type = LOCALEFFECT_ONCE;
		effect.m_lightRadius = 100;
		break;

	case(DYNAMITEEFFECT) :
		sprite->Load(&g_pTextures->t_dynamiteAnimation, 5, 100, 50);
		effect.m_type = MOVINGEFFECT_LOOP;
		effect.m_lightRadius = 50;
		effect.m_xDifference = -30;
		effect.m_yDifference = -20;
		break;

	case(RUBBISHEFFECT) :
		sprite->Load(&g_pTextures->t_rubbishAnimation, 5, 150, 150);
		effect.m_type = LOCALEFFECT_ONCE;
		break;

	case(DUSTEFFECT) :
		sprite->Load(&g_pTextures->t_ground_hit, 5, 100, 100);
		effect.m_type = LOCALEFFECT_ONCE;
		break;
		
	case(ALCHEMYEFFECT) :
		sprite->Load(&g_pTextures->t_alchemy, 5, 100, 100);
		effect.m_type = LOCALEFFECT_ONCE;
		effect.m_xDifference = -30;
		break;

	case(HEALEFFECT) :
		sprite->Load(&g_pTextures->t_healing, 5, 100, 100);
		effect.m_type = MOVINGEFFECT_ONCE;
		effect.m_xDifference = -30;
		break;

	case(TELEPORTEFFECT) :
		sprite->Load(&g_pTextures->t_teleport, 5, 100, 100);
		effect.m_type = LOCALEFFECT_ONCE;
		effect.m_animSpeed = 12;
		break;

	case(POISONEFFECT) :
		sprite->Load(&g_pTextures->t_poisonExplosionBig, 5, 200, 120);
		sprite->SetPos(_x, _y);
		effect.m_type = LOCALEFFECT_ONCE;
		m_pNpcs->CheckProjectileOrEffect(sprite, m_pPlayer->GetPoisonSpellDamage(), POISONEFFECT);
		break;

	case(CREATEEFFECT) :
		sprite->Load(&g_pTextures->t_skeletonEffect, 5, 100, 100);
		effect.m_type = LOCALEFFECT_ONCE;
		effect.m_animSpeed = 12;
		break;

	case(MANASHIELDEFFECT) :
		sprite->Load(&g_pTextures->t_manashield);
		effect.m_type = MOVINGEFFECT_LOOP;
		effect.m_xDifference = -30;
		effect.m_yDifference = -30;
		effect.m_frameNumber = 1;
		effect.m_fAnimState = -1;
		break;
	}


	sprite->SetPos(_x, _y);
	effect.m_Sprite = sprite;
	NewEffect(effect);
}






////check for explosions, alchemy, healing, rubbish and dust
//if (i->m_ID == EXPLOSION || i->m_ID == HEALING || i->m_ID == ALCHEMYANIMATION || i->m_ID == RUBBISHANIMATION || i->m_ID == DUSTANIMATION || i->m_ID == SMOKEEFFECT || i->m_ID == POISONEXPLOSION)
//{
//	if (i->m_ID != SMOKEEFFECT)
//		i->m_fAnimState += 20 * g_pTimer->GetElapsedTime().asSeconds();
//	else
//		i->m_fAnimState += 12 * g_pTimer->GetElapsedTime().asSeconds();

//	if (i->m_ID == HEALING)
//		i->m_Sprite->SetPos(m_pPlayer->GetRect().left - 30, m_pPlayer->GetRect().top);


//	if (i->m_fAnimState >= 5)
//	{
//		i = m_Projectiles.erase(i);
//		continue;
//	}

//	i++;
//	continue;
//}
////check for manashield
//else if (i->m_ID == MANASHIELDPROJECTILE)
//{
//	i->m_Sprite->SetPos(m_pPlayer->GetRect().left - 30, m_pPlayer->GetRect().top - 20);
//	i->m_fFlown -= g_pTimer->GetElapsedTime().asSeconds();

//	if (i->m_fFlown <= 0)
//	{
//		i = m_Projectiles.erase(i);
//		continue;
//	}
//}
////check for dynamite
//else if (i->m_ID == DYNAMITEEFFECT)
//{

//	i->m_fAnimState += 20 * g_pTimer->GetElapsedTime().asSeconds();
//	i->m_fFlown -= g_pTimer->GetElapsedTime().asSeconds();

//	i->m_Sprite->SetPos(*i->m_xPos - 30, *i->m_yPos - 20);

//	if (i->m_fAnimState >= 5)
//		i->m_fAnimState = 0;

//	if (i->m_fFlown <= 0)
//	{
//		int x = i->m_Sprite->GetRect().left;
//		int y = i->m_Sprite->GetRect().top;
//		SAFE_DELETE(i->m_Sprite);
//		i->m_Sprite = new CSprite;
//		i->m_ID = EXPLOSION;
//		i->m_fAnimState = 0;
//		i->m_Sprite->Load(&g_pTextures->t_explosion, 5, 100, 100);
//		i->m_Sprite->SetPos(x - 40, y - 40);
//		i->m_Damage = 30;

//		//check for blocks
//		for (int x = ((*i->m_xPos + 20) / 100) - 1; x < ((*i->m_xPos + 20) / 100) + 2; x++)
//		{
//			for (int y = (*i->m_yPos / 100) - 1; y < (*i->m_yPos / 100) + 2; y++)
//			{
//				m_pWorld->DeleteBlock(x, y);
//			}
//		}

//		//check if it hits npc
//		m_pNpcs->CheckProjectile(&*i);

//		//check if it hits player
//		if (m_pPlayer->GetRect().intersects(i->m_Sprite->GetRect()))
//		{
//			m_pPlayer->DoDamage(i->m_Damage - (i->m_Damage * (m_pPlayer->GetPlayerAttributes().armour / 100)));

//			//throw player
//			if (m_pPlayer->GetRect().left < i->m_Sprite->GetRect().left)
//				m_pPlayer->ThrowPlayer(true, 200);
//			else
//				m_pPlayer->ThrowPlayer(false, 200);
//		}


//		i++;
//		continue;
//	}
//}


//i++;