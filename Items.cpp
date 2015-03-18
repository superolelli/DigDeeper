#include "Items.hpp"




CItem::CItem()
{
	m_pThingSprite = NULL;
	m_pInventorySprite = NULL;
}


CItem::~CItem()
{
	SAFE_DELETE(m_pInventorySprite);
}




void CItem::Init(int _ID, bool _loaded)
{
	if(!_loaded)
	{
		m_ID = _ID;
		m_specialID = 0;
	}

	m_pInventorySprite = new CSprite;

	switch(m_ID)
	{
	case(COAL):
		{
			m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_coal);
			if(!_loaded)
				m_Name = "Kohle";
		}break;
	case(WOODSTAFF):
		{
			m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_woodStaff);
			if(!_loaded)
				m_Name = "Holzstab";
		}break;
	case(IRONORE):
		{
			m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_ironOre);
			if(!_loaded)
				m_Name = "Eisenerz";
		}break;
	case(IRON):
		{
			m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_iron);
			if(!_loaded)
				m_Name = "Eisen";
		}break;
	case(GOLDORE):
		{
			m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_goldOre);
			if(!_loaded)
				m_Name = "Golderz";
		}break;
	case(GOLD):
		{
			m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_gold);
			if(!_loaded)
				m_Name = "Gold";
		}break;
	case(PICKAXE):
		{
			m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_pickaxe);
			if(!_loaded)
				m_Name = "Eisenspitzhacke";
		}break;
	case(GLUE):
		{
			m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_glue);
			if(!_loaded)
				m_Name = "Klebstoff";
		}break;
	case(IRONHELMET):
		{
			m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_iron_helmet);
			if(!_loaded)
				m_Name = "Eisenhelm";
		}break;
	case(IRONARMOUR):
		{
			m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_iron_armour);
			if(!_loaded)
				m_Name = "Eisenr�stung";
		}break;
	case(IRONRING):
		{
			m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_iron_ring);
			if(!_loaded)
				m_Name = "Eisenring";
		}break;
	case(IRONTROUSERS):
		{
			m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_iron_trousers);
			if(!_loaded)
				m_Name = "Eisenleggins";
		}break;
	case(ARCANUSRING):
		{
			m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_arcanus_ring);
			if(!_loaded)
				m_Name = "Arcanusring";
		}break;
	case(ARCANUS):
		{
			m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_arcanusOre);
			if(!_loaded)
				m_Name = "Arcanus";
		}break;
	case(SLIME):
		{
			m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_slime);
			if(!_loaded)
				m_Name = "Schleim";
		}break;
	case(RECIPE):
		{
			m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_recipe);
			if(!_loaded)
			{
				m_Name = "Rezept";
				InitRecipe();
			}
		}break;
	case(VERYRARERING):
		{
			m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_very_rare_ring);
			if(!_loaded)
				m_Name = "Ring des Vollseltenseins";
		}break;
	case(MAGICHAT):
		{
			m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_magic_hat);
			if(!_loaded)
				m_Name = "Zauberhut";
		}break;
	case(SWORD):
		{
			m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_sword);
			if(!_loaded)
				m_Name = "Eisenschwert";
		}break;
	case(CANDLE):
		{
			m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_candle);
			if(!_loaded)
				m_Name = "Kerze";
		}break;
	case(LANTERN):
		{
			m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_lantern);
			if(!_loaded)
				m_Name = "Laterne";
		}break;
	case(WAX):
		{
			m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_wax);
			if(!_loaded)
				m_Name = "Wachs";
		}break;
	}
}




void CItem::InitRecipe()
{
	m_specialID = rand()%6 + 131;

	switch(m_specialID)
	{
	case(IRONHELMET):
		m_Name.append("(Eisenhelm)");
		break;
	case(IRONARMOUR):
		m_Name.append("(Eisenr�stung)");
		break;
	case(IRONTROUSERS):
		m_Name.append("(Eisenleggins)");
		break;
	case(IRONRING):
		m_Name.append("(Eisenring)");
		break;
	case(ARCANUSRING):
		m_Name.append("(Arcanusring)");
		break;
	/*case(MAGICHAT):
		m_Name.append("(Zauberhut)");
		break;*/
	/*case(LANTERN):
		m_Name.append("(Laterne)");
		break;*/
	}
}



void CItem::SetSpecialID(int _ID)
{
	m_specialID = _ID;
	m_Name = "Rezept";

	switch(m_specialID)
	{
	case(IRONHELMET):
		m_Name.append("(Eisenhelm)");
		break;
	case(IRONARMOUR):
		m_Name.append("(Eisenr�stung)");
		break;
	case(IRONTROUSERS):
		m_Name.append("(Eisenleggins)");
		break;
	case(IRONRING):
		m_Name.append("(Eisenring)");
		break;
	case(ARCANUSRING):
		m_Name.append("(Arcanusring)");
		break;
	case(MAGICHAT):
		m_Name.append("(Zauberhut)");
		break;
	case(LANTERN):
		m_Name.append("(Laterne)");
		break;
	}
}