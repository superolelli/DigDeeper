#include "Player.hpp"
#include "World.hpp"



CPlayer::CPlayer()
{
	m_pDwarf = NULL;
	m_pTarget = NULL;
	m_pWorld = NULL;
	m_pInventory = NULL;
	m_pBuildingMenu = NULL;
	m_pCharacterInfo = NULL;
	m_pPanelBeam = NULL;
	m_pExpBeam = NULL;
	m_pLifeBeam = NULL;
}



CPlayer::~CPlayer()
{
	m_pWorld = NULL;
	SAFE_DELETE(m_pDwarf);
	SAFE_DELETE(m_pInventory);
	SAFE_DELETE(m_pBuildingMenu);
	SAFE_DELETE(m_pCharacterInfo);
	SAFE_DELETE(m_pPanelBeam);
	SAFE_DELETE(m_PanelInventory.m_Sprite);
	SAFE_DELETE(m_PanelBuilding.m_Sprite);
	SAFE_DELETE(m_PanelAttributes.m_Sprite);
	SAFE_DELETE(m_PanelMagic.m_Sprite);
	SAFE_DELETE(m_pExpBeam);
	SAFE_DELETE(m_pLifeBeam);
}





void CPlayer::Init(int _x, int _y, CWorld *_world, View *_view, int _class)
{
	m_pTarget = g_pFramework->GetWindow();
	m_pWorld = _world;

	m_pDwarf = new CLiving3Part;
	m_pDwarf->Load(&g_pTextures->t_dwarf_body, 53, 60, 2, 0, &g_pTextures->t_dwarf_arm, 58, 38, 4, &g_pTextures->t_dwarf_legs, 55, 50, 14, _x, _y);
	m_pDwarf->SetPartsPos(-13.0f, 7.0f, 22.0f, -2.0f, 0.0f, 45.0f);
	m_pDwarf->SetArmRotatingPoint(50, 7);
	m_pDwarf->SetHandPosition(12.0f, 32.0f);

	m_pInventory = new CInventory;
	m_pInventory->Load(_world, _view, this);

	m_pBuildingMenu = new CBuildingMenu;
	m_pBuildingMenu->Init(m_pInventory);

	m_pCharacterInfo = new CCharacterInfo;
	m_pCharacterInfo->Init(&m_Attributes, &m_modifications, this);

	m_pPanelBeam = new CSprite;
	m_pPanelBeam->Load(&g_pTextures->t_panelBeam);
	m_pPanelBeam->SetPos(g_pFramework->GetWindow()->getSize().x/2 - m_pPanelBeam->GetRect().width/2, m_pInventory->GetRect().top - 75);

	m_PanelInventory.m_Sprite = new CSprite;
	m_PanelInventory.m_Sprite->Load(&g_pTextures->t_buttonInventory, 2, 250, 75);
	m_PanelInventory.m_Sprite->SetPos(m_pPanelBeam->GetRect().left, m_pPanelBeam->GetRect().top);
	m_PanelInventory.m_isClicked = false;

	m_PanelBuilding.m_Sprite = new CSprite;
	m_PanelBuilding.m_Sprite->Load(&g_pTextures->t_buttonBuilding, 2, 250, 75);
	m_PanelBuilding.m_Sprite->SetPos(m_pPanelBeam->GetRect().left + 250, m_pPanelBeam->GetRect().top);
	m_PanelBuilding.m_isClicked = false;

	m_PanelAttributes.m_Sprite = new CSprite;
	m_PanelAttributes.m_Sprite->Load(&g_pTextures->t_buttonAttributes, 2, 250, 75);
	m_PanelAttributes.m_Sprite->SetPos(m_pPanelBeam->GetRect().left + 500, m_pPanelBeam->GetRect().top);
	m_PanelAttributes.m_isClicked = false;

	m_PanelMagic.m_Sprite = new CSprite;
	m_PanelMagic.m_Sprite->Load(&g_pTextures->t_buttonMagic, 2, 250, 75);
	m_PanelMagic.m_Sprite->SetPos(m_pPanelBeam->GetRect().left + 750, m_pPanelBeam->GetRect().top);
	m_PanelMagic.m_isClicked = false;

	m_Attributes.currentHealth = 100;
	m_Attributes.maxHealth = 100;
	m_Attributes.healthRegeneration = 0;
	m_Attributes.armour = 0;
	m_Attributes.strength = 5;
	m_Attributes.luck = 0;
	m_Attributes.breakingSpeed = 1.0f;
	m_Attributes.speed = 150;
	m_Attributes.currentMana = 10;
	m_Attributes.maxMana = 10;
	m_Attributes.manaRegeneration = 0;
	m_Attributes.criticalChance = 0;
	m_Attributes.criticalDamage = 0;

	m_Attributes.currentExp = 0;
	m_Attributes.maxExp = 10;

	switch(_class)
	{
	case MINER:
		{
			m_Attributes.breakingSpeed = 1.5f;

			CTool *pickaxe;
			pickaxe = new CTool;
			pickaxe->InitTool(PICKAXE);
			m_pInventory->Take(pickaxe);

			CItem *iron;
			iron = new CItem;
			iron->Init(IRONORE);
			m_pInventory->Take(iron, 4);

			CItem *gold;
			gold = new CItem;
			gold->Init(GOLDORE);
			m_pInventory->Take(gold, 2);
		}break;
	case BUILDER:
		{
			//gives the player 3 random recipes
			for(int u = 0; u < 3; u++)
			{
				list<int> neededRecipes = GetNotAvailableRecipesList();
				list<int>::iterator a = neededRecipes.begin();
				int randomNumber = rand()%neededRecipes.size();
				for(int i = 0; i < randomNumber; i++)
				{
					a++;
				}
			
				//add the recipe
				CItem *newItem = new CItem;
				newItem->Init(RECIPE);
				newItem->SetSpecialID(*a);
				m_pInventory->Take(newItem);
			}

			//gives the player some building material
			CPlaceable *woodwall;
			woodwall = new CPlaceable;
			woodwall->Init(WOODWALL);
			m_pInventory->Take(woodwall, 9);

			CPlaceable *wood;
			wood = new CPlaceable;
			wood->Init(WOOD);
			m_pInventory->Take(wood, 12);

			CPlaceable *door;
			door = new CPlaceable;
			door->Init(DOOR);
			m_pInventory->Take(door);
		}break;
	case WARRIOR:
		{
			m_Attributes.strength = 10;

			CEquipment *helmet;
			helmet = new CEquipment;
			helmet->InitEquipment(IRONHELMET);
			m_pInventory->Take(helmet);

			CTool *sword;
			sword = new CTool;
			sword->InitTool(SWORD);
			m_pInventory->Take(sword);

			CTool *lantern;
			lantern = new CTool;
			lantern->InitTool(LANTERN);
			m_pInventory->Take(lantern);
		}break;
	case MAGE:
		{
			m_Attributes.maxMana = 20;
			m_Attributes.currentMana = 20;

			CEquipment *hat;
			hat = new CEquipment;
			hat->InitEquipment(MAGICHAT);
			m_pInventory->Take(hat);
		}break;
	default:
		{
		}break;
	}




	m_pLifeBeam = new CBeam();
	m_pLifeBeam->Load(&g_pTextures->t_lifeBeam, &g_pTextures->t_lifeFrame, &m_Attributes.currentHealth, &m_modifications.maxHealth);
	m_pLifeBeam->SetPos(20, 10);
	
	m_pManaBeam = new CBeam();
	m_pManaBeam->Load(&g_pTextures->t_manaBeam, &g_pTextures->t_lifeFrame, &m_Attributes.currentMana, &m_modifications.maxMana);
	m_pManaBeam->SetPos(20, 40);

	m_pExpBeam = new CBeam();
	m_pExpBeam->Load(&g_pTextures->t_expBeam, &g_pTextures->t_expFrame, &m_Attributes.currentExp, &m_Attributes.maxExp);
	m_pExpBeam->SetPos(20, 70);
	m_pExpBeam->SetCharacterSize(10);

	show_beam_numbers = false;

	m_modifications.breaking_speed = 1;

	m_FallingSpeed = 0;
	m_SideSpeed = 0;

	m_State.breaking = false;
	m_State.climbing = false;
	m_State.jumping = false;

	m_turned_left = true;
	m_armGoingUp = true;

	m_fAnimState = 6;
	m_fWaitToBeat = 0;

}




void CPlayer::InitLoaded(int _x, int _y, CWorld *_world, View *_view)
{
	m_pTarget = g_pFramework->GetWindow();
	m_pWorld = _world;

	m_pDwarf = new CLiving3Part;
	m_pDwarf->Load(&g_pTextures->t_dwarf_body, 53, 60, 2, 0, &g_pTextures->t_dwarf_arm, 58, 38, 4, &g_pTextures->t_dwarf_legs, 55, 50, 14, _x, _y);
	m_pDwarf->SetPartsPos(-13.0f, 7.0f, 22.0f, -2.0f, 0.0f, 45.0f);
	m_pDwarf->SetArmRotatingPoint(50, 7);
	m_pDwarf->SetHandPosition(12.0f, 32.0f);

	m_pDwarf->SetPos(m_loadedPosX, m_loadedPosY);

	//m_pInventory = new CInventory;
	m_pInventory->Load(_world, _view, this, true);

	m_pBuildingMenu->InitLoaded(m_pInventory);

	m_pCharacterInfo = new CCharacterInfo;
	m_pCharacterInfo->Init(&m_Attributes, &m_modifications, this);

	m_pPanelBeam = new CSprite;
	m_pPanelBeam->Load(&g_pTextures->t_panelBeam);
	m_pPanelBeam->SetPos(g_pFramework->GetWindow()->getSize().x/2 - m_pPanelBeam->GetRect().width/2, m_pInventory->GetRect().top - 75);

	m_PanelInventory.m_Sprite = new CSprite;
	m_PanelInventory.m_Sprite->Load(&g_pTextures->t_buttonInventory, 2, 250, 75);
	m_PanelInventory.m_Sprite->SetPos(m_pPanelBeam->GetRect().left, m_pPanelBeam->GetRect().top);
	m_PanelInventory.m_isClicked = false;

	m_PanelBuilding.m_Sprite = new CSprite;
	m_PanelBuilding.m_Sprite->Load(&g_pTextures->t_buttonBuilding, 2, 250, 75);
	m_PanelBuilding.m_Sprite->SetPos(m_pPanelBeam->GetRect().left + 250, m_pPanelBeam->GetRect().top);
	m_PanelBuilding.m_isClicked = false;

	m_PanelAttributes.m_Sprite = new CSprite;
	m_PanelAttributes.m_Sprite->Load(&g_pTextures->t_buttonAttributes, 2, 250, 75);
	m_PanelAttributes.m_Sprite->SetPos(m_pPanelBeam->GetRect().left + 500, m_pPanelBeam->GetRect().top);
	m_PanelAttributes.m_isClicked = false;

	m_PanelMagic.m_Sprite = new CSprite;
	m_PanelMagic.m_Sprite->Load(&g_pTextures->t_buttonMagic, 2, 250, 75);
	m_PanelMagic.m_Sprite->SetPos(m_pPanelBeam->GetRect().left + 750, m_pPanelBeam->GetRect().top);
	m_PanelMagic.m_isClicked = false;

	m_pLifeBeam = new CBeam();
	m_pLifeBeam->Load(&g_pTextures->t_lifeBeam, &g_pTextures->t_lifeFrame, &m_Attributes.currentHealth, &m_modifications.maxHealth);
	m_pLifeBeam->SetPos(20, 10);
	
	m_pManaBeam = new CBeam();
	m_pManaBeam->Load(&g_pTextures->t_manaBeam, &g_pTextures->t_lifeFrame, &m_Attributes.currentMana, &m_modifications.maxMana);
	m_pManaBeam->SetPos(20, 40);

	m_pExpBeam = new CBeam();
	m_pExpBeam->Load(&g_pTextures->t_expBeam, &g_pTextures->t_expFrame, &m_Attributes.currentExp, &m_Attributes.maxExp);
	m_pExpBeam->SetPos(20, 70);
	m_pExpBeam->SetCharacterSize(10);

	show_beam_numbers = false;

	m_modifications.breaking_speed = 1;

	m_FallingSpeed = 0;
	m_SideSpeed = 0;

	m_State.breaking = false;
	m_State.climbing = false;
	m_State.jumping = false;

	m_turned_left = true;
	m_armGoingUp = true;

	m_fAnimState = 6;
}




void CPlayer::SetPos(float _x, float _y)
{
	m_pDwarf->SetPos(_x, _y);
}


//Checks wether keys are pressed and sets the velocity; returns the center of the dwarf
Vector2f CPlayer::CheckMovement()
{
	CalculateAttributes();

	/*if (m_Attributes.currentHealth <= 0)
		m_Attributes.currentHealth = 0;*/

	m_fXVel = 0;
	m_fYVel = 0;

	int collisionID = CheckCollisionPassable();

	if(collisionID != -1)
	{
		switch(collisionID)
		{
			case(LADDER):
				m_State.climbing = true;
				break;

			default:
				m_State.climbing = false;
		}
	}
	else 
		m_State.climbing = false;

	//Checks the movement on the x-axis
	CheckXMovement();

	//Checks wether the player would collide with something if he moves
	if(CheckCollisions())
		m_fXVel = 0;

	//Checks the movement on the y-axis
	CheckYMovement();

	//Checks wether the player would collide with something if he moves
	if(CheckCollisions())
	{
		m_fYVel = m_fYVel/2;
		if(CheckCollisions())
		{
			m_fYVel = m_fYVel/2;
			if(CheckCollisions())
			{
				m_fYVel = 0;
				//cout <<"Collided in y direction" << endl;
			}
		}


		//If he reaches the ground he doesn't jump anymore
		if (m_fYVel > 0)
		{
			m_State.jumping = false;
			//	cout <<"Reached ground" << endl;
		}
	}
	//If he hasn't collide with anything he must be falling and you can't jump, while falling ;)
	else
	{
		m_State.jumping = true;
		//cout <<"Didn't collide in y direction" << endl;
	}


	CheckArmAnimation();


	//Move the dwarf
	m_pDwarf->Move((int)m_fXVel, (int)m_fYVel);

	//get the center of the dwarf
	Vector2f returnVector;
	returnVector.x = (float)m_pDwarf->GetRect().left + m_pDwarf->GetRect().width/2;
	returnVector.y = (float)m_pDwarf->GetRect().top + m_pDwarf->GetRect().height/2;

	//return the center of the dwarf
	return returnVector;
}




void CPlayer::CheckXMovement()
{
	//regulate the side speed
	if (m_SideSpeed > 0)
		m_SideSpeed -= 200 * g_pTimer->GetElapsedTime().asSeconds();
	else if (m_SideSpeed < 0)
		m_SideSpeed += 200 * g_pTimer->GetElapsedTime().asSeconds();
	
	if (abs(m_SideSpeed) < 50)
	{
		//if the left key is pressed
		if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))
		{
			m_turned_left = true;

			m_fXVel = (float)-m_modifications.speed * g_pTimer->GetElapsedTime().asSeconds();
			m_fAnimState -= 8.0f * (m_modifications.speed / 150) * g_pTimer->GetElapsedTime().asSeconds();

			//start the animation new if it has reached it's end
			if (m_fAnimState < 0 || m_fAnimState > 7)
				m_fAnimState = 6.99f;

		}
		//if the right key is pressed
		else if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
		{
			m_turned_left = false;

			m_fXVel = (float)m_modifications.speed * g_pTimer->GetElapsedTime().asSeconds();
			m_fAnimState += 8.0f * (m_modifications.speed / 150)* g_pTimer->GetElapsedTime().asSeconds();

			//start the animation new if it has reached it's end
			if (m_fAnimState < 7 || m_fAnimState > 14)
				m_fAnimState = 7;
		}
		else
		{
			if (m_turned_left)
				m_fAnimState = 6;
			else
				m_fAnimState = 7;
		}
	}

	if (m_SideSpeed != 0)
		m_fXVel += m_SideSpeed * g_pTimer->GetElapsedTime().asSeconds();

	//Check if the dwarf is out of the world
	if(m_pDwarf->GetRect().left + m_fXVel < 0 || m_pDwarf->GetRect().left + m_pDwarf->GetRect().width + m_fXVel > m_pWorld->GetDimensions().x*100)
		m_fXVel = 0;
}


void CPlayer::ThrowPlayer(bool _left, int _strength)
{
	if (_left)
		m_SideSpeed = -_strength;
	else
		m_SideSpeed = _strength;

	m_FallingSpeed = -200;
}


void CPlayer::CheckYMovement()
{ 
	//Checks wether the up key is pressed and sets the dwarf jumping, if he isn't already
	if(Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W))
	{
		if(!m_State.jumping && !m_State.climbing)
		{
			cout <<"Player jumped" << endl;
			m_FallingSpeed = -350;
			m_State.jumping = true;
		}
	}

	//if you press the "down" key: set falling speed to maximum
	if(Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
		m_FallingSpeed = 200;


	//Add something to the falling speed if jumping (gravity)
	if(m_FallingSpeed < 200)
	{
		m_FallingSpeed += static_cast<int>(400 * g_pTimer->GetElapsedTime().asSeconds());

		//the normal falling speed is 200
		if(m_FallingSpeed > 200)
			m_FallingSpeed = 200;
	}
	if(m_FallingSpeed < - 350)
	{
		m_FallingSpeed = -350;
	}

	//if the player is climbing: move him up
	if(m_State.climbing == true && (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)))
	{
		m_FallingSpeed = -150;
	}


	//imitates gravity
	m_fYVel = m_FallingSpeed * g_pTimer->GetElapsedTime().asSeconds();


	//Check if the dwarf is out of the world
	if(m_pDwarf->GetRect().top + m_fYVel < 0 || m_pDwarf->GetRect().top + m_pDwarf->GetRect().height + m_fYVel > m_pWorld->GetDimensions().y*100)
		m_fYVel = 0;

}



//returns true if the player would collide
bool CPlayer::CheckCollisions()
{
	//the rect, the dwarf would have, if he moved
	FloatRect newPosition;
	newPosition.left   = m_pDwarf->GetRect().left + m_fXVel;
	newPosition.top    = m_pDwarf->GetRect().top + m_fYVel;
	newPosition.width  = (float)m_pDwarf->GetRect().width;
	newPosition.height = (float)m_pDwarf->GetRect().height;


	return (m_pWorld->CheckLivingCollision(newPosition));

}



int CPlayer::CheckCollisionPassable()
{
	//the rect, the dwarf would have, if he moved
	FloatRect newPosition;
	newPosition.left   = m_pDwarf->GetRect().left + m_fXVel;
	newPosition.top    = m_pDwarf->GetRect().top + m_fYVel;
	newPosition.width  = (float)m_pDwarf->GetRect().width;
	newPosition.height = (float)m_pDwarf->GetRect().height;

	return (m_pWorld->CheckCollisionWithPassable(newPosition));
}


void CPlayer::Render()
{
	//if the player is carrying a tool: render it
	CThing *thing = m_pInventory->GetCarriedThing();
	if(thing != NULL && thing->getID() > ITBREAK && thing->getID() < TEBREAK)
	{
		CTool *tool = (CTool *)thing;

		//if the player carries a lantern: render a light circle
		if(tool->getID() == LANTERN)
			m_pWorld->GetLightMachine()->AddLightCircle(m_pDwarf->GetHandPos(m_turned_left).x, m_pDwarf->GetHandPos(m_turned_left).y, 300, Color::Yellow);

		if(m_turned_left)
		{
			tool->SetRotation(m_fArmAnimState);
			m_pDwarf->Render(0.0f, m_fAnimState);
			m_pInventory->RenderEquipment(m_pDwarf->GetRect().left, m_pDwarf->GetRect().top, true);
			tool->RenderTool(m_pDwarf->GetHandPos(m_turned_left).x, m_pDwarf->GetHandPos(m_turned_left).y);
			m_pDwarf->RenderSecondPart(0);
		}
		else
		{
			tool->SetRotation(-m_fArmAnimState);
			m_pDwarf->Render(1.0f, m_fAnimState);
			m_pInventory->RenderEquipment(m_pDwarf->GetRect().left, m_pDwarf->GetRect().top, false);
			tool->RenderTool(m_pDwarf->GetHandPos(m_turned_left).x, m_pDwarf->GetHandPos(m_turned_left).y);
			m_pDwarf->RenderSecondPart(3);
		}
	}
	else
	{
		//Render the dwarf
		if(m_turned_left)
		{
			m_pDwarf->Render(0.0f, m_fAnimState);
			m_pInventory->RenderEquipment(m_pDwarf->GetRect().left, m_pDwarf->GetRect().top, true);
			m_pDwarf->RenderSecondPart(1);
		}
		else
		{
			m_pDwarf->Render(1.0f, m_fAnimState);
			m_pInventory->RenderEquipment(m_pDwarf->GetRect().left, m_pDwarf->GetRect().top, false);
			m_pDwarf->RenderSecondPart(2);
		}
	}

	//if the player is wearing a candle: render a light circle
	if(m_pInventory->GetHelmetID() == CANDLE)
		m_pWorld->GetLightMachine()->AddLightCircle(m_pDwarf->GetRect().left + m_pDwarf->GetRect().width/2, m_pDwarf->GetRect().top, 250, Color::Yellow);
}


//returns the rect of the carried weapon 
IntRect CPlayer::GetWeaponRect()
{
	CThing *thing = m_pInventory->GetCarriedThing();
	if(thing != NULL && thing->getID() > ITBREAK && thing->getID() < TEBREAK)
	{
		CTool *tool = (CTool *)thing;	
		return tool->GetRect();
	}
	else
	{
		IntRect hand;
		hand.left = m_pDwarf->GetHandPos(m_turned_left).x;
		hand.top = m_pDwarf->GetHandPos(m_turned_left).y;

		if(m_turned_left)
		{
			hand.left -= 8;
			hand.top -= 6;
		}
		else
		{
			hand.left += 8;
			hand.top -= 6;
		}

		hand.width = 16;
		hand.height = 12;

		return hand;
	}
}


//Renders the panels
void CPlayer::RenderInventory()
{
	//render the beams
	if(show_beam_numbers)
	{
		//renders beams with numbers
		m_pLifeBeam->RenderWithNumbers(g_pFramework->GetWindow());
		m_pManaBeam->RenderWithNumbers(g_pFramework->GetWindow());
		m_pExpBeam->RenderWithNumbers(g_pFramework->GetWindow());
	}
	else
	{
		m_pLifeBeam->Render(g_pFramework->GetWindow());
		m_pManaBeam->Render(g_pFramework->GetWindow());
		m_pExpBeam->Render(g_pFramework->GetWindow());
	}


	
	//check wether the player wants to open a panel
	if(g_pFramework->keyStates.eUp && !m_pInventory->GetOpen())
	{
			m_PanelInventory.m_isClicked = true;
			m_PanelAttributes.m_isClicked = false;
			m_PanelBuilding.m_isClicked = false;
			m_PanelMagic.m_isClicked = false;

			m_pBuildingMenu->SetOpen(false);
			m_pCharacterInfo->SetOpen(false);
	}
	else if(g_pFramework->keyStates.bUp && !m_pBuildingMenu->GetOpen())
	{
			m_PanelInventory.m_isClicked = false;
			m_PanelAttributes.m_isClicked = false;
			m_PanelBuilding.m_isClicked = true;
			m_PanelMagic.m_isClicked = false;

			m_pInventory->SetOpen(false);
			m_pCharacterInfo->SetOpen(false);
	}
	else if(g_pFramework->keyStates.cUp && !m_pCharacterInfo->GetOpen())
	{
			m_PanelInventory.m_isClicked = false;
			m_PanelAttributes.m_isClicked = true;
			m_PanelBuilding.m_isClicked = false;
			m_PanelMagic.m_isClicked = false;

			m_pInventory->SetOpen(false);
			m_pBuildingMenu->SetOpen(false);
	}

	if(m_pInventory->GetOpen() || m_pBuildingMenu->GetOpen() || m_pCharacterInfo->GetOpen())
	{
		//render the panels
		m_pPanelBeam->Render(g_pFramework->GetWindow());
	
		//was the inventory button clicked?
		if(m_PanelInventory.m_Sprite->GetRect().contains(Mouse::getPosition()) && Mouse::isButtonPressed(Mouse::Left))
		{
			if(!m_PanelInventory.m_isClicked)
			{
				m_PanelInventory.m_isClicked = true;
				m_PanelAttributes.m_isClicked = false;
				m_PanelBuilding.m_isClicked = false;
				m_PanelMagic.m_isClicked = false;

				m_pInventory->SetOpen(true);
				m_pBuildingMenu->SetOpen(false);
				m_pCharacterInfo->SetOpen(false);
			}
		}
		//was the building button clicked?
		else if(m_PanelBuilding.m_Sprite->GetRect().contains(Mouse::getPosition()) && Mouse::isButtonPressed(Mouse::Left))
		{
			if(!m_PanelBuilding.m_isClicked)
			{
				m_PanelBuilding.m_isClicked = true;
				m_PanelInventory.m_isClicked = false;
				m_PanelAttributes.m_isClicked = false;
				m_PanelMagic.m_isClicked = false;

				m_pInventory->SetOpen(false);
				m_pBuildingMenu->SetOpen(true);
				m_pCharacterInfo->SetOpen(false);
			}
		}
		//was the attributes button clicked?
		else if(m_PanelAttributes.m_Sprite->GetRect().contains(Mouse::getPosition()) && Mouse::isButtonPressed(Mouse::Left))
		{
			if(!m_PanelAttributes.m_isClicked)
			{
				m_PanelInventory.m_isClicked = false;
				m_PanelBuilding.m_isClicked = false;
				m_PanelAttributes.m_isClicked = true;
				m_PanelMagic.m_isClicked = false;

				m_pInventory->SetOpen(false);
				m_pBuildingMenu->SetOpen(false);
				m_pCharacterInfo->SetOpen(true);
			}
		}
		//was the magic button clicked?
		else if(m_PanelMagic.m_Sprite->GetRect().contains(Mouse::getPosition()) && Mouse::isButtonPressed(Mouse::Left))
		{
			if(!m_PanelMagic.m_isClicked)
			{
				m_PanelInventory.m_isClicked = false;
				m_PanelBuilding.m_isClicked = false;
				m_PanelAttributes.m_isClicked = false;
				m_PanelMagic.m_isClicked = true;

				m_pInventory->SetOpen(false);
				m_pBuildingMenu->SetOpen(false);
				m_pCharacterInfo->SetOpen(false);
			}
		}

		//renders the panel buttons
		m_PanelInventory.m_Sprite->Render(g_pFramework->GetWindow(), m_PanelInventory.m_isClicked);
		m_PanelBuilding.m_Sprite->Render(g_pFramework->GetWindow(), m_PanelBuilding.m_isClicked);
		m_PanelAttributes.m_Sprite->Render(g_pFramework->GetWindow(), m_PanelAttributes.m_isClicked);
		m_PanelMagic.m_Sprite->Render(g_pFramework->GetWindow(), m_PanelMagic.m_isClicked);
	}

	//renders the panels
	m_pInventory->Render(m_pDwarf->GetRect());
	m_pBuildingMenu->Render();
	m_pCharacterInfo->Render();
}


//gives the player an item
void CPlayer::Take(CThing *_thing, int amount)
{
	m_pInventory->Take(_thing, amount);
}


//checks the animation state of the arm
void CPlayer::CheckArmAnimation()
{
	if(Mouse::isButtonPressed(Mouse::Left))
	{
		//if dwarf carries sword
		//CThing *thing = m_pInventory->GetCarriedThing();
		//if (thing != NULL && thing->getID() == SWORD)
		//{
		//	if (m_fWaitToBeat <= 0)
		//	{
		//		//if arm reached lowest point: set arm to highest point
		//		if (m_fArmAnimState <= -40)
		//		{
		//			m_fArmAnimState = 110;
		//			m_fWaitToBeat = 0.6;
		//		}

		//		m_fArmAnimState -= g_pTimer->GetElapsedTime().asSeconds() * 500;
		//	}
		//	else
		//		m_fWaitToBeat -= g_pTimer->GetElapsedTime().asSeconds();
		//}
		//else
		//{
			if (m_fArmAnimState >= 90)
				m_armGoingUp = false;
			if (m_fArmAnimState <= -40)
				m_armGoingUp = true;

			if (m_armGoingUp)
				m_fArmAnimState += g_pTimer->GetElapsedTime().asSeconds() * 300;
			else
				m_fArmAnimState -= g_pTimer->GetElapsedTime().asSeconds() * 300;
		//}
	}
	else
	{
		m_fArmAnimState = 0;
	}

	m_pDwarf->RotateArm(m_fArmAnimState);
}




void CPlayer::CalculateAttributes()
{
	m_modifications = m_pInventory->GetEquipmentAttributes();

	CThing *thing = m_pInventory->GetCarriedThing();
	if(thing != NULL && thing->getID() > ITBREAK && thing->getID() < TEBREAK)
	{
		CTool *tool = (CTool *)thing;

		//calculate the attributes
		m_modifications.breaking_speed += tool->GetAttributes().breaking_speed + m_Attributes.breakingSpeed;    //add modification to the breaking speed
		m_modifications.armour += tool->GetAttributes().armour + m_Attributes.armour;
		m_modifications.luck += tool->GetAttributes().luck + m_Attributes.luck;
		m_modifications.maxHealth += tool->GetAttributes().maxHealth + m_Attributes.maxHealth;
		m_modifications.maxMana += tool->GetAttributes().maxMana + m_Attributes.maxMana;
		m_modifications.speed += tool->GetAttributes().speed + m_Attributes.speed;
		m_modifications.strength += tool->GetAttributes().strength + m_Attributes.strength;
		m_modifications.healthRegeneration += tool->GetAttributes().healthRegeneration + m_Attributes.healthRegeneration;
		m_modifications.manaRegeneration += tool->GetAttributes().manaRegeneration + m_Attributes.manaRegeneration;
		m_modifications.criticalChance += tool->GetAttributes().criticalChance + m_Attributes.criticalChance;
		m_modifications.criticalDamage += tool->GetAttributes().criticalDamage + m_Attributes.criticalDamage;

	}
	else
	{
		m_modifications.breaking_speed += m_Attributes.breakingSpeed;
		m_modifications.armour += m_Attributes.armour;
		m_modifications.luck += m_Attributes.luck;
		m_modifications.maxHealth += m_Attributes.maxHealth;
		m_modifications.maxMana += m_Attributes.maxMana;
		m_modifications.speed += m_Attributes.speed;
		m_modifications.strength += m_Attributes.strength;
		m_modifications.healthRegeneration += m_Attributes.healthRegeneration;
		m_modifications.manaRegeneration += m_Attributes.manaRegeneration;
		m_modifications.criticalChance += m_Attributes.criticalChance;
		m_modifications.criticalDamage += m_Attributes.criticalDamage;
	}

}

//returns the player's attributes (with all modifications [equipment, tools etc])
SToolAttributes CPlayer::GetPlayerAttributes()
{
	return m_modifications;
}