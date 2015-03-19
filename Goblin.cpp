#include "Goblin.hpp"



void CGoblin::Init(int _x, int _y, CWorld *_world, bool _loaded)
{
	m_pWorld = _world;
	m_ID = GOBLIN;

	//Init the sprite
	m_pGoblin = new CLiving3Part;
	m_pGoblin->Load(&g_pTextures->t_goblin_arm, 44, 52, 2, 0, &g_pTextures->t_goblin_arm, 38, 24, 2, &g_pTextures->t_goblin_legs, 40, 35, 12, _x, _y);
	m_pGoblin->SetPartsPos();
}