#ifndef PROJECTILES_HPP
#define PROJECTILES_HPP


#include "Framework.hpp"
#include "Structures.hpp"
#include "World.hpp"
#include "LightMachine.hpp"


class CNpcMachine;


#define g_pProjectiles CProjectiles::Get()

class CProjectiles : public TSingleton<CProjectiles>
{
public:

	CProjectiles();
	~CProjectiles();
	void Init(CWorld *_world, CPlayer *_player, CNpcMachine *_Npcs);
	void Quit();
	void Render();
	void CheckProjectiles();
	void NewProjectile(SProjectile _projectile);


private:

	list<SProjectile> m_Projectiles;

	CWorld *m_pWorld;
	CPlayer *m_pPlayer;
	CNpcMachine * m_pNpcs;

};

#endif