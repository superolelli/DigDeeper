#include "Placeable.hpp"




CPlaceable::CPlaceable()
{
	m_pThingSprite = NULL;
	m_pInventorySprite = NULL;
}


CPlaceable::~CPlaceable()
{
	SAFE_DELETE(m_pThingSprite);
	SAFE_DELETE(m_pInventorySprite);
}


//loads the textures for the placeables and sets the frames and IDs
void CPlaceable::Init(int _ID, bool _loaded)
{
	if(!_loaded)
	{
		m_ID = _ID;
		m_SpecialID = 0;
	}
	m_fBreakingTime = 0;
	m_fBreakFrame = -1;

	m_pThingSprite = new CSprite;
	m_pInventorySprite = new CSprite;

	m_BreakingAnimation.Load(&g_pTextures->t_breakingAnimation, 3, 100, 100);

	switch(m_ID)
	{
	case ROOMFILL:
		{

		}break;
	case DIRT:
		{
			m_pThingSprite->Load(&g_pTextures->t_blockTextures_dirt);
			m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_dirt);
			m_Name = "Erde";
			m_Hardness = 2;
			m_is_passable = false;
			m_is_visible = true;
		}break;
	case STONE:
		{
			m_pThingSprite->Load(&g_pTextures->t_blockTextures_stone);
			m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_stone);
			m_Name = "Stein";
			m_Hardness = 5;
			m_is_passable = false;
			m_is_visible = true;
		}break;
	case WOOD:
		{
			m_pThingSprite->Load(&g_pTextures->t_blockTextures_wood);
			m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_wood);
			m_Name = "Holz";
			m_Hardness = 2;
			m_is_passable = false;
			m_is_visible = true;
		}break;
	case COALBLOCK:
		{
			m_pThingSprite->Load(&g_pTextures->t_blockTextures_coalBlock);
			m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_coalBlock);
			m_Name = "Block mit Kohle";
			m_Hardness = 3;
			m_is_passable = false;
			m_is_visible = true;
		}break;
	case STONEWALL:
		{
			m_pThingSprite->Load(&g_pTextures->t_blockTextures_stoneWall);
			m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_stoneWall);
			m_Name = "Steinwand";
			m_Hardness = 3;
			m_is_passable = true;
			m_is_visible = true;
		}break;
	case WOODWALL:
		{
			m_pThingSprite->Load(&g_pTextures->t_blockTextures_woodWall);
			m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_woodWall);
			m_Name = "Holzwand";
			m_Hardness = 2;
			m_is_passable = true;
			m_is_visible = true;
		}break;
	case LADDER:
		{
			m_pThingSprite->Load(&g_pTextures->t_blockTextures_ladder);
			m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_ladder);
			m_Name = "Leiter";
			m_Hardness = 2;
			m_is_passable = true;
			m_is_visible = true;
		}break;
	case FURNANCE:
		{
			m_pThingSprite->Load(&g_pTextures->t_blockTextures_furnance);
			m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_furnance);
			m_Name = "Ofen";
			m_Hardness = 2;
			m_is_passable = true;
			m_is_visible = true;
		}break;
	case CHEST:
		{
			m_pThingSprite->Load(&g_pTextures->t_blockTextures_chest);
			m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_chest);
			m_Name = "Truhe";
			m_Hardness = 2;
			m_is_passable = true;
			m_is_visible = true;
		}break;
	case CUPBOARD:
		{
			m_pThingSprite->Load(&g_pTextures->t_blockTextures_cupboard);
			m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_cupboard);
			m_Name = "Schrank";
			m_Hardness = 2;
			m_is_passable = true;
			m_is_visible = true;
		}break;
	case DOOR:
		{
			m_pThingSprite->Load(&g_pTextures->t_blockTextures_door, 2, 100, 100);
			m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_door);
			m_Name = "Tür";
			m_Hardness = 2;
			m_is_passable = true;
			m_is_visible = true;
		}break;
	case IRONBLOCK:
		{
			m_pThingSprite->Load(&g_pTextures->t_blockTextures_ironBlock);
			m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_ironBlock);
			m_Name = "Block mit Eisen";
			m_Hardness = 5;
			m_is_passable = false;
			m_is_visible = true;
		}break;
	case GOLDBLOCK:
		{
			m_pThingSprite->Load(&g_pTextures->t_blockTextures_goldBlock);
			m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_goldBlock);
			m_Name = "Block mit Gold";
			m_Hardness = 5;
			m_is_passable = false;
			m_is_visible = true;
		}break;
	case ARCANUSBLOCK:
		{
			m_pThingSprite->Load(&g_pTextures->t_blockTextures_arcanusBlock);
			m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_arcanusBlock);
			m_Name = "Block mit Arcanus";
			m_Hardness = 7;
			m_is_passable = false;
			m_is_visible = true;
		}break;
	case TABLE:
		{
			m_pThingSprite->Load(&g_pTextures->t_blockTextures_table);
			m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_table);
			m_Name = "Tisch";
			m_Hardness = 2;
			m_is_passable = true;
			m_is_visible = true;
		}break;
	case LANTERNP:
		{
			m_pThingSprite->Load(&g_pTextures->t_blockTextures_lantern);
			m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_lantern);
			m_Name = "Laterne";
			m_Hardness = 0;
			m_is_passable = true;
			m_is_visible = true;
		}break;
	case MARBLE:
		{
			m_pThingSprite->Load(&g_pTextures->t_blockTextures_marble);
			m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_marble);
			m_Name = "Marmor";
			m_Hardness = 5;
			m_is_passable = false;
			m_is_visible = true;
		}break;
	case MARBLEWALL:
		{
			m_pThingSprite->Load(&g_pTextures->t_blockTextures_marblewall);
			m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_marblewall);
			m_Name = "Marmorwand";
			m_Hardness = 3;
			m_is_passable = true;
			m_is_visible = true;
		}break;
	default:
		{
			m_pThingSprite->Load(&g_pTextures->t_blockTextures_noTexture);
			m_Hardness = 100;
			m_is_passable = true;
			m_is_visible = true;
		}
	}
}




void CPlaceable::SetPos(float _x, float _y)
{
	m_pThingSprite->SetPos(_x, _y);
}


void CPlaceable::SetPos(int _x, int _y)
{
	m_pThingSprite->SetPos(_x, _y);
}


void CPlaceable::Render()
{
	//if the thing is a door: check the animation frame
	if(m_ID == DOOR)
	{
		m_pThingSprite->Render(g_pFramework->GetWindow(), (float)(m_SpecialID));
	}
	else
		//else: just render it
		m_pThingSprite->Render(g_pFramework->GetWindow());

	//check if the thing should be breaked and show the breaking animation
	if(m_fBreakFrame >= 0)
	{
		m_BreakingAnimation.SetPos(m_pThingSprite->GetRect().left, m_pThingSprite->GetRect().top);
		m_BreakingAnimation.Render(g_pFramework->GetWindow(), m_fBreakFrame);
	}
}


//returns true if placeable is broken
bool CPlaceable::IsBroken(float _modificator)
{
	//is the left mouse button pressed? -> Add time to the timer
	if(Mouse::isButtonPressed(Mouse::Left))
		m_fBreakingTime += _modificator * g_pTimer->GetElapsedTime().asSeconds();

	//Check in which state the block is
	if(m_fBreakingTime <= static_cast<float>(m_Hardness)/3.0f)
		m_fBreakFrame = 0;
	else if(m_fBreakingTime <= (static_cast<float>(m_Hardness)/3.0f) * 2 )
		m_fBreakFrame = 1;
	else if(m_fBreakingTime <= m_Hardness)
		m_fBreakFrame = 2;
	
	
	if(m_fBreakingTime >= m_Hardness)
		return true;

		return false;	
}



//returns the ID of the item which you get if breaking the placeable
int CPlaceable::GetLittleID()
{
	switch(m_ID)
	{
	case(COALBLOCK):
		return COAL;
		break;
	case(IRONBLOCK):
		return IRONORE;
		break;
	case(GOLDBLOCK):
		return GOLDORE;
		break;
	case(ARCANUSBLOCK):
		return ARCANUS;
		break;
	case(LANTERNP):
		return LANTERN;
		break;

	default:
		return m_ID;
	}
}


 IntRect CPlaceable::GetRect()
{
	if(m_ID == DOOR)
	{
		if(m_SpecialID == 1)
		{
			IntRect rect;
			rect.left = m_pThingSprite->GetRect().left + 75;
			rect.top = m_pThingSprite->GetRect().top;
			rect.width = 14;
			rect.height = m_pThingSprite->GetRect().height;
			return rect;
		}
		else
			return m_pThingSprite->GetRect();
	}
	else
		return m_pThingSprite->GetRect();
}



//sets the special ID
//Used for:
//Furnances: the Panel ID
//doors: the frame number (set any SID, it is going to be handled inside the function)
void CPlaceable::SetSpecialID(int _SID)
{
	//set the special ID
	m_SpecialID = _SID;


	//is the thing a door?
	if(m_ID == DOOR)
	{
		if(m_is_passable)
		{
			m_is_passable = false;
			m_SpecialID = 1;
		}
		else
		{
			m_is_passable = true;
			m_SpecialID = 0;
		}
	}
}