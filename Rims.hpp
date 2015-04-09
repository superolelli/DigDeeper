#ifndef RIMS_HPP
#define RIMS_HPP




#include "Textures.hpp"
#include "Sprite.hpp"

using namespace sf;


//the class for loading all textures at once
#define g_pRims CRims::Get()
class CRims : public TSingleton < CRims >
{
public:

	//loads all textures
	void LoadRims();

	CSprite TopRims[2][3];
	CSprite BottomRims[2][3];
	CSprite LeftRims[2][3];
	CSprite RightRims[2][3];
};


#endif