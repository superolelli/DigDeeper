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
				m_Name = "Eisenrüstung";
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
	case(BEEHIVE) :
	{
		m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_beehive);
		if (!_loaded)
			m_Name = "Bienenkorb";
	}break;
	case(HONEY) :
	{
		m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_honey);
		if (!_loaded)
			m_Name = "Honig";
	}break;
	case(MEAD) :
	{
		m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_mead);
		if (!_loaded)
			m_Name = "Met";
	}break;
	case(SLIMEPUDDING) :
	{
		m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_slimepudding);
		if (!_loaded)
			m_Name = "Schleimpudding";
	}break;
	case(CLOVER) :
	{
		m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_clover);
		if (!_loaded)
			m_Name = "Kleeblatt";
	}break;
	case(BATTLEAXE) :
	{
		m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_battleaxe);
		if (!_loaded)
			m_Name = "Kampfaxt";
	}break;
	case(RADISH) :
	{
		m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_radish);
		if (!_loaded)
			m_Name = "Radieschen";
	}break;
	case(RADISHSOUP) :
	{
		m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_radishsoup);
		if (!_loaded)
			m_Name = "Paradieschensuppe";
	}break;
	case(COOKINGBOOK) :
	{
		m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_cookingbook);
		if (!_loaded)
			m_Name = "Kochbuch";
	}break;
	case(BREAD) :
	{
		m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_bread);
		if (!_loaded)
			m_Name = "Zwergenbrot";
	}break;
	case(SAWDUST) :
	{
		m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_sawdust);
		if (!_loaded)
			m_Name = "Sägespäne";
	}break;
	case(MUSHROOM) :
	{
		m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_mushroom);
		if (!_loaded)
			m_Name = "Pilz";
	}break;
	case(DIADOCHIT) :
	{
		m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_diadochit);
		if (!_loaded)
			m_Name = "Diadochit";
	}break;
	case(BATTLESTONE) :
	{
		m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_battlestone);
		if (!_loaded)
			m_Name = "Kampfstein";
	}break;
	case(DIADOCHITARMOUR) :
	{
		m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_diadochitarmour);
		if (!_loaded)
			m_Name = "Diadochitrüstung";
	}break;
	case(SPELL) :
	{
		if (_loaded)
			InitSpell();
	}break;
	}
}




void CItem::InitRecipe()
{
	m_specialID = rand()%11 + 131;

	switch(m_specialID)
	{
	case(IRONHELMET):
		m_Name.append("(Eisenhelm)");
		break;
	case(IRONARMOUR):
		m_Name.append("(Eisenrüstung)");
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
	//case(MAGICHAT):
	//	m_Name.append("(Zauberhut)");
	//	break;
	case(136):
		m_Name.append("(Laterne)");
		m_specialID = LANTERN;
		break;
	case(DIADOCHITARMOUR) :
		m_Name.append("(Diadochitrüstung)");
		break;
	case(137) :
		m_Name.append("(Bienenkiste)");
		m_specialID = BEEHOUSE;
		break;
	case(139) :
		m_Name.append("(Kessel)");
		m_specialID = CAULDRON;
		break;
	case(140) :
		m_Name.append("(Kampfaxt)");
		m_specialID = BATTLEAXE;
		break;
	case(141) :
		m_Name.append("(Sägespäne)");
		m_specialID = SAWDUST;
		break;
	case(142) :
		m_Name.append("(Kampfstein)");
		m_specialID = BATTLESTONE;
		break;
	}

	stringstream stream;
	stream << "Rezept-ID: " << m_specialID;
	g_pFramework->WriteToLog(INFO, stream.str());
}



void CItem::SetSpecialID(int _ID)
{
	m_specialID = _ID;

	if (m_ID == RECIPE)
	{
		m_Name = "Rezept";

		switch (m_specialID)
		{
		case(IRONHELMET) :
			m_Name.append("(Eisenhelm)");
			break;
		case(IRONARMOUR) :
			m_Name.append("(Eisenrüstung)");
			break;
		case(IRONTROUSERS) :
			m_Name.append("(Eisenleggins)");
			break;
		case(IRONRING) :
			m_Name.append("(Eisenring)");
			break;
		case(ARCANUSRING) :
			m_Name.append("(Arcanusring)");
			break;
		case(MAGICHAT) :
			m_Name.append("(Zauberhut)");
			break;
		case(LANTERN) :
			m_Name.append("(Laterne)");
			break;
		case(BEEHOUSE) :
			m_Name.append("(Bienenkiste)");
			break;
		case(CAULDRON) :
			m_Name.append("(Kessel)");
			break;
		case(BATTLEAXE) :
			m_Name.append("(Kampfaxt)");
			break;
		case(SAWDUST) :
			m_Name.append("(Sägespäne)");
			break;
		case(BATTLESTONE) :
			m_Name.append("(Kampfstein)");
			break;
		case(DIADOCHITARMOUR) :
			m_Name.append("(Diadochitrüstung)");
			break;
		}
	}

	stringstream stream;
	stream << "Set new ID: " << m_specialID;
	g_pFramework->WriteToLog(INFO, stream.str());
}



void CItem::SetSpecialIDSpell(int _ID)
{
	m_specialID = _ID;
	InitSpell();
}


void CItem::InitSpell()
{
	switch (m_specialID)
	{
	case(FIREBALL):
		m_pInventorySprite->Load(&g_pTextures->t_spellInventoryTexture_fireball);
		m_Name = "Feuerball";
		break;

	case(HEAL):
		m_pInventorySprite->Load(&g_pTextures->t_spellInventoryTexture_heal);
		m_Name = "Heilung";
		break;

	case(ICE):
		m_pInventorySprite->Load(&g_pTextures->t_spellInventoryTexture_ice);
		m_Name = "Eispfeil";
		break;

	case(ALCHEMY) :
		m_pInventorySprite->Load(&g_pTextures->t_spellInventoryTexture_alchemy);
		m_Name = "Alchemie";
		break;

	case(LIGHT) :
		m_pInventorySprite->Load(&g_pTextures->t_spellInventoryTexture_light);
		m_Name = "Lichtkugel";
		break;

	default:
		m_Name = "Error";
	}
}