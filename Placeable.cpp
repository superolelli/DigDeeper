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
		m_fPlaceableTimer = 60.0f;
		m_is_breakable = true;
	}
	m_fBreakingTime = 0;
	m_fBreakFrame = -1;

	m_OverlappingID[0] = rand() % 3;
	m_OverlappingID[1] = rand() % 3;
	m_OverlappingID[2] = rand() % 3;
	m_OverlappingID[3] = rand() % 3;

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
			m_Priority = 5;
			m_is_passable = false;
			m_is_visible = true;
			m_can_place_on = true;
		}break;
	case STONE:
		{
			m_pThingSprite->Load(&g_pTextures->t_blockTextures_stone);
			m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_stone);
			m_Name = "Stein";
			m_Hardness = 5;
			m_Priority = 1;
			m_is_passable = false;
			m_is_visible = true;
			m_can_place_on = true;
		}break;
	case WOOD:
		{
			m_pThingSprite->Load(&g_pTextures->t_blockTextures_wood);
			m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_wood);
			m_Name = "Holz";
			m_Hardness = 2;
			m_Priority = 0;
			m_is_passable = false;
			m_is_visible = true;
			m_can_place_on = true;
		}break;
	case COALBLOCK:
		{
			m_pThingSprite->Load(&g_pTextures->t_blockTextures_coalBlock);
			m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_coalBlock);
			m_Name = "Block mit Kohle";
			m_Hardness = 3;
			m_Priority = 1;
			m_is_passable = false;
			m_is_visible = true;
			m_can_place_on = true;
		}break;
	case STONEWALL:
		{
			m_pThingSprite->Load(&g_pTextures->t_blockTextures_stoneWall);
			m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_stoneWall);
			m_Name = "Steinwand";
			m_Hardness = 3;
			m_Priority = -1;
			m_is_passable = true;
			m_is_visible = true;
			m_can_place_on = true;
		}break;
	case WOODWALL:
		{
			m_pThingSprite->Load(&g_pTextures->t_blockTextures_woodWall);
			m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_woodWall);
			m_Name = "Holzwand";
			m_Hardness = 2;
			m_Priority = -1;
			m_is_passable = true;
			m_is_visible = true;
			m_can_place_on = true;
		}break;
	case LADDER:
		{
			m_pThingSprite->Load(&g_pTextures->t_blockTextures_ladder);
			m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_ladder);
			m_Name = "Leiter";
			m_Hardness = 2;
			m_Priority = -1;
			m_is_passable = true;
			m_is_visible = true;
			m_can_place_on = false;
		}break;
	case FURNANCE:
		{
			m_pThingSprite->Load(&g_pTextures->t_blockTextures_furnance);
			m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_furnance);
			m_Name = "Ofen";
			m_Hardness = 2;
			m_Priority = -1;
			m_is_passable = true;
			m_is_visible = true;
			m_can_place_on = false;
		}break;
	case CHEST:
		{
			m_pThingSprite->Load(&g_pTextures->t_blockTextures_chest);
			m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_chest);
			m_Name = "Truhe";
			m_Hardness = 2;
			m_Priority = -1;
			m_is_passable = true;
			m_is_visible = true;
			m_can_place_on = false;
		}break;
	case CUPBOARD:
		{
			m_pThingSprite->Load(&g_pTextures->t_blockTextures_cupboard);
			m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_cupboard);
			m_Name = "Schrank";
			m_Hardness = 2;
			m_Priority = -1;
			m_is_passable = true;
			m_is_visible = true;
			m_can_place_on = true;
		}break;
	case DOOR:
		{
			m_pThingSprite->Load(&g_pTextures->t_blockTextures_door, 2, 100, 100);
			m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_door);
			m_Name = "Tür";
			m_Hardness = 2;
			m_Priority = -1;

			if (m_SpecialID == 0)
				m_is_passable = true;
			else
				m_is_passable = false;

			m_is_visible = true;
			m_can_place_on = false;
		}break;
	case IRONBLOCK:
		{
			m_pThingSprite->Load(&g_pTextures->t_blockTextures_ironBlock);
			m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_ironBlock);
			m_Name = "Block mit Eisen";
			m_Hardness = 5;
			m_Priority = 1;
			m_is_passable = false;
			m_is_visible = true;
			m_can_place_on = true;
		}break;
	case GOLDBLOCK:
		{
			m_pThingSprite->Load(&g_pTextures->t_blockTextures_goldBlock);
			m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_goldBlock);
			m_Name = "Block mit Gold";
			m_Hardness = 5;
			m_Priority = 1;
			m_is_passable = false;
			m_is_visible = true;
			m_can_place_on = true;
		}break;
	case ARCANUSBLOCK:
		{
			m_pThingSprite->Load(&g_pTextures->t_blockTextures_arcanusBlock);
			m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_arcanusBlock);
			m_Name = "Block mit Arcanus";
			m_Hardness = 7;
			m_Priority = 1;
			m_is_passable = false;
			m_is_visible = true;
			m_can_place_on = true;
		}break;
	case TABLE:
		{
			m_pThingSprite->Load(&g_pTextures->t_blockTextures_table);
			m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_table);
			m_Name = "Tisch";
			m_Hardness = 2;
			m_Priority = -1;
			m_is_passable = true;
			m_is_visible = true;
			m_can_place_on = false;
		}break;
	case LANTERNP:
		{
			m_pThingSprite->Load(&g_pTextures->t_blockTextures_lantern);
			m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_lantern);
			m_Name = "Laterne";
			m_Hardness = 0;
			m_Priority = -1;
			m_is_passable = true;
			m_is_visible = true;
			m_can_place_on = false;
		}break;
	case MARBLE:
		{
			m_pThingSprite->Load(&g_pTextures->t_blockTextures_marble);
			m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_marble);
			m_Name = "Marmor";
			m_Hardness = 5;
			m_Priority = 0;
			m_is_passable = false;
			m_is_visible = true;
			m_can_place_on = true;
		}break;
	case MARBLEWALL:
		{
			m_pThingSprite->Load(&g_pTextures->t_blockTextures_marblewall);
			m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_marblewall);
			m_Name = "Marmorwand";
			m_Hardness = 3;
			m_Priority = -1;
			m_is_passable = true;
			m_is_visible = true;
			m_can_place_on = true;
		}break;
	case TREETRUNK:
	{
		m_pThingSprite->Load(&g_pTextures->t_blockTextures_treetrunk);
		m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_treetrunk);
		m_Name = "Baumstamm";
		m_Hardness = 2;
		m_Priority = 2;
		m_is_passable = true;
		m_is_visible = true;
		m_can_place_on = true;
	}break;
	case TREECROWN:
	{
		m_pThingSprite->Load(&g_pTextures->t_blockTextures_treecrown);
		m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_treecrown);
		m_Name = "Baumkrone";
		m_Hardness = 2;
		m_Priority = -1;
		m_is_passable = true;
		m_is_visible = true;
		m_can_place_on = true;
	}break;
	case BEEHIVEP:
	{
		m_pThingSprite->Load(&g_pTextures->t_blockTextures_beehive_left);
		m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_beehive);
		m_Name = "Bienenkorb";
		m_Hardness = 1;
		m_Priority = -1;
		m_is_passable = true;
		m_is_visible = true;
		m_can_place_on = false;

		if (_loaded)
			SetSpecialID(m_SpecialID);
	}break;
	case BEEHOUSE:
	{
		m_pThingSprite->Load(&g_pTextures->t_blockTextures_beehouse);
		m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_beehouse);
		m_Name = "Bienenkiste";
		m_Hardness = 2;
		m_Priority = -1;
		m_is_passable = true;
		m_is_visible = true;
		m_can_place_on = true;
	}break;
	case TORCH:
	{
		m_pThingSprite->Load(&g_pTextures->t_blockTextures_torch_ground);
		m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_torch);
		m_Name = "Fackel";
		m_Hardness = 0;
		m_Priority = -1;
		m_is_passable = true;
		m_is_visible = true;
		m_can_place_on = false;

		if (_loaded)
			SetSpecialID(m_SpecialID);

	}break;
	case CAULDRON:
	{
		m_pThingSprite->Load(&g_pTextures->t_blockTextures_cauldron);
		m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_cauldron);
		m_Name = "Kessel";
		m_Hardness = 1;
		m_Priority = -1;
		m_is_passable = true;
		m_is_visible = true;
		m_can_place_on = false;
	}break;
	case CLOVERP:
	{
		m_pThingSprite->Load(&g_pTextures->t_blockTextures_clover);
		m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_clover);
		m_Name = "Kleeblatt";
		m_Hardness = 0;
		m_Priority = -1;
		m_is_passable = true;
		m_is_visible = true;
		m_can_place_on = false;
	}break;
	case RADISHP:
	{
		m_pThingSprite->Load(&g_pTextures->t_blockTextures_radish);
		m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_radish);
		m_Name = "Radieschen";
		m_Hardness = 0;
		m_Priority = -1;
		m_is_passable = true;
		m_is_visible = true;
		m_can_place_on = false;
	}break;
	case MUSHROOMP:
	{
		m_pThingSprite->Load(&g_pTextures->t_blockTextures_mushroom);
		m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_mushroom);
		m_Name = "Pilz";
		m_Hardness = 0;
		m_Priority = -1;
		m_is_passable = true;
		m_is_visible = true;
		m_can_place_on = false;
	}break;
	case STALAGTIT:
	{
		m_pThingSprite->Load(&g_pTextures->t_blockTextures_stalagtit1);
		m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_diadochit);
		m_Name = "Stalagtit";
		m_Hardness = 5;
		m_Priority = -1;
		m_is_passable = true;
		m_is_visible = true;
		m_can_place_on = false;

		if (_loaded)
			SetSpecialID(m_SpecialID);
	}break;
	case RUBBISH:
	{
		m_pThingSprite->Load(&g_pTextures->t_blockTextures_rubbish);
		m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_mushroom);
		m_Name = "Müll";
		m_Hardness = 0;
		m_Priority = -1;
		m_is_passable = true;
		m_is_visible = true;
		m_can_place_on = false;
	}break;
	case BEDROCK:
	{
		m_pThingSprite->Load(&g_pTextures->t_blockTextures_bedrock);
		m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_bedrock);
		m_Name = "Grundgestein";
		m_Hardness = 0;
		m_Priority = 0;
		m_is_passable = false;
		m_is_visible = true;
		m_can_place_on = true;

		if (!_loaded)
			m_is_breakable = false;
	}break;
	case BRICKS:
	{
		m_pThingSprite->Load(&g_pTextures->t_blockTextures_bricks);
		m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_bricks);
		m_Name = "Steinziegel";
		m_Hardness = 5;
		m_Priority = 0;
		m_is_passable = false;
		m_is_visible = true;
		m_can_place_on = true;
	}break;
	case BRICKWALL:
	{
		m_pThingSprite->Load(&g_pTextures->t_blockTextures_brickwall);
		m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_brickwall);
		m_Name = "Steinziegelwand";
		m_Hardness = 3;
		m_Priority = -1;
		m_is_passable = true;
		m_is_visible = true;
		m_can_place_on = true;
	}break;
	case PRINCESSCAGE:
	{
		m_pThingSprite->Load(&g_pTextures->t_blockTextures_princessCage);
		m_pInventorySprite->Load(&g_pTextures->t_blockInventoryTexture_brickwall);
		m_Name = "Prinzessin im Käfig";
		m_Hardness = 3;
		m_Priority = -1;
		m_is_passable = true;
		m_is_visible = true;
		m_can_place_on = true;

		if (!_loaded)
			m_is_breakable = false;
		else
			SetSpecialID(m_SpecialID);
	}break;
	default:
		{
			m_pThingSprite->Load(&g_pTextures->t_blockTextures_noTexture);
			m_Hardness = 100;
			m_Priority = -1;
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
		m_pThingSprite->Render(g_pFramework->GetRenderWindow(), (float)(m_SpecialID));
	}
	else
		//else: just render it
		m_pThingSprite->Render(g_pFramework->GetRenderWindow());

	//if the thing is a beehouse: check the timer
	if (m_ID == BEEHOUSE)
	{
		m_fPlaceableTimer -= g_pTimer->GetElapsedTime().asSeconds();

		if (m_fPlaceableTimer < 0)
			m_fPlaceableTimer = 0;
	}

	//check if the thing should be breaked and show the breaking animation
	if(m_fBreakFrame >= 0)
	{
		m_BreakingAnimation.SetPos(m_pThingSprite->GetRect().left, m_pThingSprite->GetRect().top);
		m_BreakingAnimation.Render(g_pFramework->GetRenderWindow(), m_fBreakFrame);
	}
}


//returns true if placeable is broken
bool CPlaceable::IsBroken(float _modificator)
{
	if (m_is_breakable)
	{
		//is the left mouse button pressed? -> Add time to the timer
		if (Mouse::isButtonPressed(Mouse::Left))
			m_fBreakingTime += _modificator * g_pTimer->GetElapsedTime().asSeconds();

		//Check in which state the block is
		if (m_fBreakingTime <= static_cast<float>(m_Hardness) / 3.0f)
			m_fBreakFrame = 0;
		else if (m_fBreakingTime <= (static_cast<float>(m_Hardness) / 3.0f) * 2)
			m_fBreakFrame = 1;
		else if (m_fBreakingTime <= m_Hardness)
			m_fBreakFrame = 2;


		if (m_fBreakingTime >= m_Hardness)
		{
			return true;
		}
	}

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
	case(TREETRUNK) :
	case(TREECROWN):
		return WOOD;
		break;
	case(BEEHIVEP) :
		return BEEHIVE;
		break;
	case(CLOVERP) :
		return CLOVER;
		break;
	case(RADISHP) :
		return RADISH;
		break;
	case(MUSHROOMP) :
		return MUSHROOM;
		break;
	case(STALAGTIT) :
		return DIADOCHIT;
		break;
	case(RUBBISH) :
		return GetRubbish();
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
//beehives: the direction of the hive
//stalagtit: the appearance of the stalagtit
//princess cage: hanging or standing?
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
	//if thing is a hive
	else if (m_ID == BEEHIVEP)
	{
		if (m_SpecialID == 0)
			m_pThingSprite->Load(&g_pTextures->t_blockTextures_beehive_left);
		else
			m_pThingSprite->Load(&g_pTextures->t_blockTextures_beehive_right);
	}
	//if thing is a torch
	else if (m_ID == TORCH)
	{
		if (m_SpecialID == 0)
			m_pThingSprite->Load(&g_pTextures->t_blockTextures_torch_ground);
		else if (m_SpecialID == 1)
			m_pThingSprite->Load(&g_pTextures->t_blockTextures_torch_wall);
		else if (m_SpecialID == 2)
			m_pThingSprite->Load(&g_pTextures->t_blockTextures_torch_right);
		else 
			m_pThingSprite->Load(&g_pTextures->t_blockTextures_torch_left);
	}
	else if (m_ID == STALAGTIT)
	{
		if (m_SpecialID == 0)
			m_pThingSprite->Load(&g_pTextures->t_blockTextures_stalagtit1);
		else if (m_SpecialID == 1)
			m_pThingSprite->Load(&g_pTextures->t_blockTextures_stalagtit2);
		else if (m_SpecialID == 2)
			m_pThingSprite->Load(&g_pTextures->t_blockTextures_stalagtit3);
		else if (m_SpecialID == 3)
			m_pThingSprite->Load(&g_pTextures->t_blockTextures_stalagtit4);
	}
	else if (m_ID == PRINCESSCAGE)
	{
		if (m_SpecialID == 0)
			m_pThingSprite->Load(&g_pTextures->t_blockTextures_princessCage);
		else
			m_pThingSprite->Load(&g_pTextures->t_blockTextures_princessCage2);
	}
}




bool CPlaceable::IsPlaceableReady()
{
	if (m_ID == BEEHOUSE)
	{
		if (m_fPlaceableTimer <= 0)
		{
			m_fPlaceableTimer = 60.0f;
			return true;
		}
	}
	

	return false;
}




int CPlaceable::GetRubbish()
{
	int number = rand() % 85 + 56;

	if (number > 70 && number < 81)
		number = -1;
	else if (number > 88 && number < 101)
		number = -1;
	else if (number > 104 && number < 131)
		number = -1;
	else if (number == 138)
		number = 200;
	else if (number == 139)
		number = LADDER;
	else if (number == 140)
		number = TORCH;

	return number;
}