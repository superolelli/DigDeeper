#ifndef EFFECTS_HPP
#define EFFECTS_HPP


#include "Framework.hpp"
#include "Structures.hpp"
#include "World.hpp"
#include "LightMachine.hpp"

class CNpcMachine;


#define g_pEffects CEffects::Get()

class CEffects : public TSingleton<CEffects>
{
public:

	CEffects();
	~CEffects();
	void Init(CWorld *_world, CPlayer *_player, CNpcMachine *_Npcs);
	void Quit();
	void Render();
	void CheckEffects();
	void NewEffect(SEffect _effect);
	void AddEffect(int _ID, int _x, int _y, int *_movingX, int *_movingY, int _duration = 5);


private:

	list<SEffect> m_Effects;

	CWorld *m_pWorld;
	CPlayer *m_pPlayer;
	CNpcMachine * m_pNpcs;

};

#endif