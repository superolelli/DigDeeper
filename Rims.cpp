#include "Rims.hpp"






void CRims::LoadRims()
{
	//dirt rims
	TopRims[0][0].Load(&g_pTextures->t_dirtRimTop);
	TopRims[0][0].setTextureRect(IntRect(0, 0, 100, 18));

	TopRims[0][1].Load(&g_pTextures->t_dirtRimTop);
	TopRims[0][1].setTextureRect(IntRect(100, 0, 100, 18));
	
	TopRims[0][2].Load(&g_pTextures->t_dirtRimTop);
	TopRims[0][2].setTextureRect(IntRect(200, 0, 100, 18));

	BottomRims[0][0].Load(&g_pTextures->t_dirtRimBottom);
	BottomRims[0][0].setTextureRect(IntRect(0, 0, 100, 18));
	
	BottomRims[0][1].Load(&g_pTextures->t_dirtRimBottom);
	BottomRims[0][1].setTextureRect(IntRect(100, 0, 100, 18));
	
	BottomRims[0][2].Load(&g_pTextures->t_dirtRimBottom);
	BottomRims[0][2].setTextureRect(IntRect(200, 0, 100, 18));

	LeftRims[0][0].Load(&g_pTextures->t_dirtRimLeft);
	LeftRims[0][0].setTextureRect(IntRect(0, 0, 18, 100));
	
	LeftRims[0][1].Load(&g_pTextures->t_dirtRimLeft);
	LeftRims[0][1].setTextureRect(IntRect(0, 100, 18, 100));
	
	LeftRims[0][2].Load(&g_pTextures->t_dirtRimLeft);
	LeftRims[0][2].setTextureRect(IntRect(0, 200, 18, 100));

	RightRims[0][0].Load(&g_pTextures->t_dirtRimRight);
	RightRims[0][0].setTextureRect(IntRect(0, 0, 18, 100));
	
	RightRims[0][1].Load(&g_pTextures->t_dirtRimRight);
	RightRims[0][1].setTextureRect(IntRect(0, 100, 18, 100));
	
	RightRims[0][2].Load(&g_pTextures->t_dirtRimRight);
	RightRims[0][2].setTextureRect(IntRect(0, 200, 18, 100));

	//stone rims
	TopRims[1][0].Load(&g_pTextures->t_stoneRimTop);
	TopRims[1][0].setTextureRect(IntRect(0, 0, 100, 18));

	TopRims[1][1].Load(&g_pTextures->t_stoneRimTop);
	TopRims[1][1].setTextureRect(IntRect(100, 0, 100, 18));

	TopRims[1][2].Load(&g_pTextures->t_stoneRimTop);
	TopRims[1][2].setTextureRect(IntRect(200, 0, 100, 18));

	BottomRims[1][0].Load(&g_pTextures->t_stoneRimBottom);
	BottomRims[1][0].setTextureRect(IntRect(0, 0, 100, 18));

	BottomRims[1][1].Load(&g_pTextures->t_stoneRimBottom);
	BottomRims[1][1].setTextureRect(IntRect(100, 0, 100, 18));

	BottomRims[1][2].Load(&g_pTextures->t_stoneRimBottom);
	BottomRims[1][2].setTextureRect(IntRect(200, 0, 100, 18));

	LeftRims[1][0].Load(&g_pTextures->t_stoneRimLeft);
	LeftRims[1][0].setTextureRect(IntRect(0, 0, 18, 100));

	LeftRims[1][1].Load(&g_pTextures->t_stoneRimLeft);
	LeftRims[1][1].setTextureRect(IntRect(0, 100, 18, 100));

	LeftRims[1][2].Load(&g_pTextures->t_stoneRimLeft);
	LeftRims[1][2].setTextureRect(IntRect(0, 200, 18, 100));

	RightRims[1][0].Load(&g_pTextures->t_stoneRimRight);
	RightRims[1][0].setTextureRect(IntRect(0, 0, 18, 100));

	RightRims[1][1].Load(&g_pTextures->t_stoneRimRight);
	RightRims[1][1].setTextureRect(IntRect(0, 100, 18, 100));

	RightRims[1][2].Load(&g_pTextures->t_stoneRimRight);
	RightRims[1][2].setTextureRect(IntRect(0, 200, 18, 100));
}