#include "LittleItems.hpp"




CLittleItem::CLittleItem()
{
	m_pLittleItemSprite = NULL;
	m_pThing = false;
	m_loaded = false;
}



CLittleItem::~CLittleItem()
{

}


void CLittleItem::Quit(bool _forever)
{
	SAFE_DELETE(m_pLittleItemSprite);

	if(_forever)
		SAFE_DELETE(m_pThing);
}



//Loads the sprite for the little item
void CLittleItem::Init(CThing *_thing, int _x, int _y, bool _loaded)
{
	m_dynamiteTime = 0;
	m_xPos = 0;
	m_yPos = 0;

	m_pLittleItemSprite = new CSprite;

	if(!_loaded)
		m_pThing = _thing;

	switch(m_pThing->getID())
	{
	case(DIRT):
		{
			m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_dirt);
		}break;
	case(STONE):
		{
			m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_stone);
		}break;
	case(STONEWALL):
		{
			m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_stoneWall);
		}break;
	case(WOODWALL):
		{
			m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_woodWall);
		}break;
	case(COALBLOCK):
		{
			m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_coalBlock); 
		}break;
	case(IRONBLOCK):
		{
			m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_ironBlock);
		}break;
	case(GOLDBLOCK):
		{
			m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_goldBlock);
		}break;
	case(WOOD):
		{
			m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_wood);
		}break;
	case(COAL):
		{
			m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_coal);
		}break;
	case(IRONORE):
		{
			m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_ironOre);
		}break;
	case(IRON):
		{
			m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_iron);
		}break;
	case(GOLDORE):
		{
			m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_goldOre);
		}break;
	case(GOLD):
		{
			m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_gold);
		}break;
	case(LADDER):
		{
			m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_ladder);
		}break;
	case (FURNANCE):
		{
			m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_furnance);
		}break;
	case (CHEST):
		{
			m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_chest);
		}break;
	case (CUPBOARD):
		{
			m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_cupboard);
		}break;
	case (DOOR):
		{
			m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_door);
		}break;
	case(WOODSTAFF):
		{
			m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_woodStaff);
		}break;
	case(PICKAXE):
		{
			m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_pickaxe);
		}break;
	case(GLUE):
		{
			m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_glue);
		}break;
	case(IRONHELMET):
		{
			m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_iron_helmet);
		}break;
	case(IRONARMOUR):
		{
			m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_iron_armour);
		}break;
	case(IRONRING):
		{
			m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_iron_ring);
		}break;
	case(IRONTROUSERS):
		{
			m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_iron_trousers);
		}break;
	case(ARCANUSBLOCK):
		{
			m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_arcanusBlock);
		}break;
	case(ARCANUS):
		{
			m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_arcanusOre);
		}break;
	case(ARCANUSRING):
		{
			m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_arcanus_ring);
		}break;
	case(SLIME):
		{
			m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_slime);
		}break;
	case(RECIPE):
		{
			m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_recipe);
		}break;
	case(TABLE):
		{
			m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_table);
		}break;
	case(VERYRARERING):
		{
			m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_very_rare_ring);
		}break;
	case(MAGICHAT):
		{
			m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_magic_hat);
		}break;
	case(SWORD):
		{
			m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_sword);
		}break;
	case(CANDLE):
		{
			m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_candle);
		}break;
	case(LANTERN):
		{
			m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_lantern);
		}break;
	case(WAX):
		{
			m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_wax);
		}break;
	case(MARBLE):
		{
			m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_marble);
		}break;
	case(MARBLEWALL):
		{
			m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_marblewall);
		}break;
	case(BEEHIVE) :
	{
		m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_beehive);
	}break;
	case(BEEHOUSE) :
	{
		m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_beehouse);
	}break;
	case(HONEY) :
	{
		m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_honey);
	}break;
	case(TORCH) :
	{
		m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_torch);
	}break;
	case(CAULDRON) :
	{
		m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_cauldron);
	}break;
	case(MEAD) :
	{
		m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_mead);
	}break;
	case(SLIMEPUDDING) :
	{
		m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_slimepudding);
	}break;
	case(CLOVER) :
	{
		m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_clover);
	}break;
	case(BATTLEAXE) :
	{
		m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_battleaxe);
	}break;
	case(RADISH) :
	{
		m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_radish);
	}break;
	case(RADISHSOUP) :
	{
		m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_radishsoup);
	}break;
	case(COOKINGBOOK) :
	{
		m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_cookingbook);
	}break;
	case(BREAD) :
	{
		m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_bread);
	}break;
	case(SAWDUST) :
	{
		m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_sawdust);
	}break;
	case(MUSHROOM) :
	{
		m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_mushroom);
	}break;
	case(DIADOCHIT) :
	{
		m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_diadochit);
	}break;
	case(BATTLESTONE) :
	{
		m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_battlestone);
	}break;
	case(DIADOCHITARMOUR) :
	{
		m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_diadochitarmour);
	}break;
	case(BEDROCK) :
	{
		m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_bedrock);
	}break;
	case(BRICKS) :
	{
		m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_bricks);
	}break;
	case(BRICKWALL) :
	{
		m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_brickwall);
	}break;
	case(KEY) :
	{
		m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_key);
	}break;
	case(DYNAMITE) :
	{
		if (((CItem*)(_thing))->GetSpecialID() == 0)
			m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_dynamite);
		else
			m_pLittleItemSprite->Load(&g_pTextures->t_tool_dynamite);

		m_dynamiteTime = 5;
	}break;
	case(SULFURBLOCK) :
	{
		m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_sulfurBlock);
	}break;
	case(SALPETERBLOCK) :
	{
		m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_salpeterBlock);
	}break;
	case(SULFUR) :
	{
		m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_sulfur);
	}break;
	case(SALPETER) :
	{
		m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_salpeter);
	}break;
	case(GOBLINDAGGER) :
	{
		m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_goblindagger);
	}break;
	case(METALBARS) :
	{
		m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_metalbars);
	}break;
	case(MAGICPOINT) :
	{
		m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_magicpoint);
	}break;
	case(LEATHER) :
	{
		m_pLittleItemSprite->Load(&g_pTextures->t_blockLittleTexture_leather);
	}break;
	}


	m_pLittleItemSprite->SetPos(_x, _y);
}



//Renders the sprite
void CLittleItem::Render()
{
	m_xPos = m_pLittleItemSprite->GetRect().left;
	m_yPos = m_pLittleItemSprite->GetRect().top;

	if (m_pThing->getID() == DYNAMITE)
	{
		m_dynamiteTime -= g_pTimer->GetElapsedTime().asSeconds();
	}

	m_pLittleItemSprite->Render(g_pFramework->GetRenderWindow());
}




void CLittleItem::Move()
{
	if(!m_loaded)
		m_pLittleItemSprite->Move(m_Vel.x * g_pTimer->GetElapsedTime().asSeconds(), m_Vel.y * g_pTimer->GetElapsedTime().asSeconds());
	else
		m_loaded = false;
}


bool CLittleItem::DynamiteExploded()
{
	if (m_dynamiteTime <= 0)
		return true;
	else
		return false;
}
