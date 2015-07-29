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
	m_pMagicMenu = NULL;
	m_pPanelBeam = NULL;
	m_pExpBeam = NULL;
	m_pLifeBeam = NULL;
	m_pCloseButton = NULL;
	m_ActiveEffects.clear();
}



CPlayer::~CPlayer()
{
	m_pWorld = NULL;
	SAFE_DELETE(m_pDwarf);
	SAFE_DELETE(m_pInventory);
	SAFE_DELETE(m_pBuildingMenu);
	SAFE_DELETE(m_pCharacterInfo);
	SAFE_DELETE(m_pMagicMenu);
	SAFE_DELETE(m_pPanelBeam);
	SAFE_DELETE(m_PanelInventory.m_Sprite);
	SAFE_DELETE(m_PanelBuilding.m_Sprite);
	SAFE_DELETE(m_PanelAttributes.m_Sprite);
	SAFE_DELETE(m_PanelMagic.m_Sprite);
	SAFE_DELETE(m_pExpBeam);
	SAFE_DELETE(m_pLifeBeam);
	SAFE_DELETE(m_pCloseButton);

	for (int i = 0; i < NUMBER_OF_EFFECTS; i++)
	{
		SAFE_DELETE(m_StatusEffects[i].m_Sprite);
	}

	m_ActiveEffects.clear();
}





void CPlayer::Init(int _x, int _y, CWorld *_world, View *_view, int _class, bool _inventoryNumbers, bool _beamNumbers)
{
	m_pTarget = g_pFramework->GetRenderWindow();
	m_pWorld = _world;
	m_pView = _view;

	m_pDwarf = new CLiving3Part;
	m_pDwarf->Load(&g_pTextures->t_dwarf_body, 53, 60, 2, 0, &g_pTextures->t_dwarf_arm, 58, 38, 4, &g_pTextures->t_dwarf_legs, 55, 50, 14, _x, _y);
	m_pDwarf->SetPartsPos(-13.0f, 7.0f, 22.0f, -2.0f, 0.0f, 45.0f);
	m_pDwarf->SetArmRotatingPoint(50, 7);
	m_pDwarf->SetHandPosition(12.0f, 32.0f);

	m_pInventory = new CInventory;
	m_pInventory->Load(_world, _view, this, _inventoryNumbers);

	m_pBuildingMenu = new CBuildingMenu;
	m_pBuildingMenu->Init(m_pInventory);

	m_pCharacterInfo = new CCharacterInfo;
	m_pCharacterInfo->Init(&m_Attributes, &m_modifications, this);

	m_pMagicMenu = new CMagicMenu;
	m_pMagicMenu->Init(m_pInventory, this);

	m_pPanelBeam = new CSprite;
	m_pPanelBeam->Load(&g_pTextures->t_panelBeam);
	m_pPanelBeam->SetPos(g_pFramework->GetRenderWindow()->getSize().x/2 - m_pPanelBeam->GetRect().width/2, m_pInventory->GetRect().top - 75);

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

	m_pCloseButton = new CButton;
	m_pCloseButton->Load(&g_pTextures->t_buttonClose, m_pPanelBeam->GetRect().left + m_pPanelBeam->GetRect().width, m_pPanelBeam->GetRect().top + 12, 3);

	for (int i = 0; i < NUMBER_OF_EFFECTS; i++)
	{
		m_StatusEffects[i].m_Sprite = new CSprite;
		m_StatusEffects[i].m_Sprite->Load(&g_pTextures->t_status[i]);
		m_StatusEffects[i].m_fDuration = 0.0f;
		m_StatusEffects[i].m_fTimeLeft = 0.0f;

		m_StatusDuration[i].setPrimitiveType(sf::TrianglesFan);
		m_StatusDuration[i].resize(361);
		m_StatusDuration[i][0].color = Color(0, 0, 0, 255);
	}

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

			CPlaceable *torch;
			torch = new CPlaceable;
			torch->Init(TORCH);
			m_pInventory->Take(torch);
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

			CPlaceable *torch;
			torch = new CPlaceable;
			torch->Init(TORCH);
			m_pInventory->Take(torch);
		}break;
	case WARRIOR:
		{
			m_Attributes.strength = 8;

			CEquipment *helmet;
			helmet = new CEquipment;
			helmet->InitEquipment(IRONHELMET);
			m_pInventory->Take(helmet);

			CTool *sword;
			sword = new CTool;
			sword->InitTool(SWORD);
			m_pInventory->Take(sword);

			CPlaceable *torch;
			torch = new CPlaceable;
			torch->Init(TORCH);
			m_pInventory->Take(torch);
		}break;
	case MAGE:
		{
			m_Attributes.maxMana = 50;
			m_Attributes.currentMana = 50;
			m_Attributes.manaRegeneration = 1;

			m_pMagicMenu->AddMagicPoints(3);

			CEquipment *hat;
			hat = new CEquipment;
			hat->InitEquipment(MAGICHAT);
			m_pInventory->Take(hat);

			CPlaceable *torch;
			torch = new CPlaceable;
			torch->Init(TORCH);
			m_pInventory->Take(torch);
		}break;
	case TEST:
	{
		CTool *lantern;
		lantern = new CTool;
		lantern->InitTool(LANTERN);
		m_pInventory->Take(lantern);

		CTool *pickaxe;
		pickaxe = new CTool;
		pickaxe->InitTool(PICKAXE);
		m_pInventory->Take(pickaxe);

		CTool *battleaxe;
		battleaxe = new CTool;
		battleaxe->InitTool(BATTLEAXE);
		m_pInventory->Take(battleaxe);

		CEquipment *candle;
		candle = new CEquipment;
		candle->InitEquipment(CANDLE);
		m_pInventory->Take(candle);

		CPlaceable *beehouse;
		beehouse = new CPlaceable;
		beehouse->Init(BEEHOUSE);
		m_pInventory->Take(beehouse);

		CPlaceable *torch;
		torch = new CPlaceable;
		torch->Init(TORCH);
		m_pInventory->Take(torch, 10);

		CPlaceable *cauldron;
		cauldron = new CPlaceable;
		cauldron->Init(CAULDRON);
		m_pInventory->Take(cauldron);

		CConsumable *honey;
		honey = new CConsumable;
		honey->InitConsumable(HONEY);
		m_pInventory->Take(honey, 4);

		CConsumable *mead;
		mead = new CConsumable;
		mead->InitConsumable(MEAD);
		m_pInventory->Take(mead, 4);

		CConsumable *radish;
		radish = new CConsumable;
		radish->InitConsumable(RADISH);
		m_pInventory->Take(radish, 4);

		//add the recipe
		CItem *book = new CItem;
		book->Init(COOKINGBOOK);
		book->SetSpecialID(m_pWorld->AddPanel(COOKINGBOOK, 0, 0));
		m_pInventory->Take(book);
	

		CItem *book2 = new CItem;
		book2->Init(COOKINGBOOK);
		book2->SetSpecialID(m_pWorld->AddPanel(COOKINGBOOK, 0, 0));
		m_pInventory->Take(book2);

		CEquipment *darmour;
		darmour = new CEquipment;
		darmour->InitEquipment(DIADOCHITARMOUR);
		m_pInventory->Take(darmour);


		m_pMagicMenu->AddMagicPoints(10);

		m_Attributes.criticalChance = 5;
		m_Attributes.criticalDamage = 4;
		m_Attributes.maxMana = 300;
		m_Attributes.currentMana = 300;
		m_Attributes.manaRegeneration = 5;

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

	show_beam_numbers = _beamNumbers;

	m_modifications.breaking_speed = 1;

	m_class = _class;

	m_FallingSpeed = 0;
	m_SideSpeed = 0;

	m_fFallingDistance = 0;

	m_State.breaking = false;
	m_State.climbing = false;
	m_State.jumping = false;

	m_turned_left = true;
	m_armGoingUp = true;

	m_fAnimState = 6;
	m_fWaitToBeat = 0;
	m_fRegenerationTime = 0;

}




void CPlayer::InitLoaded(int _x, int _y, CWorld *_world, View *_view, bool _inventoryNumbers, bool _beamNumbers)
{
	m_pTarget = g_pFramework->GetRenderWindow();
	m_pWorld = _world;
	m_pView = _view;

	m_pDwarf = new CLiving3Part;
	m_pDwarf->Load(&g_pTextures->t_dwarf_body, 53, 60, 2, 0, &g_pTextures->t_dwarf_arm, 58, 38, 4, &g_pTextures->t_dwarf_legs, 55, 50, 14, _x, _y);
	m_pDwarf->SetPartsPos(-13.0f, 7.0f, 22.0f, -2.0f, 0.0f, 45.0f);
	m_pDwarf->SetArmRotatingPoint(50, 7);
	m_pDwarf->SetHandPosition(12.0f, 32.0f);

	m_pDwarf->SetPos(m_loadedPosX, m_loadedPosY);

	//m_pInventory = new CInventory;
	m_pInventory->Load(_world, _view, this, _inventoryNumbers, true);

	m_pBuildingMenu->InitLoaded(m_pInventory);

	m_pCharacterInfo->Init(&m_Attributes, &m_modifications, this, true);

	m_pMagicMenu->Init(m_pInventory, this, true);

	m_pPanelBeam = new CSprite;
	m_pPanelBeam->Load(&g_pTextures->t_panelBeam);
	m_pPanelBeam->SetPos(g_pFramework->GetRenderWindow()->getSize().x/2 - m_pPanelBeam->GetRect().width/2, m_pInventory->GetRect().top - 75);

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

	m_pCloseButton = new CButton;
	m_pCloseButton->Load(&g_pTextures->t_buttonClose, m_pPanelBeam->GetRect().left + m_pPanelBeam->GetRect().width, m_pPanelBeam->GetRect().top + 12, 3);

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


	for (int i = 0; i < NUMBER_OF_EFFECTS; i++)
	{
		m_StatusEffects[i].m_Sprite = new CSprite;
		m_StatusEffects[i].m_Sprite->Load(&g_pTextures->t_status[i]);

		m_StatusDuration[i].setPrimitiveType(sf::TrianglesFan);
		m_StatusDuration[i].resize(361);
		m_StatusDuration[i][0].color = Color(0, 0, 0, 255);
	}

	show_beam_numbers = _beamNumbers;

	m_modifications.breaking_speed = 1;

	m_FallingSpeed = 0;
	m_SideSpeed = 0;

	m_fFallingDistance = 0;

	m_State.breaking = false;
	m_State.climbing = false;
	m_State.jumping = false;

	m_turned_left = true;
	m_armGoingUp = true;

	m_fAnimState = 6;
	m_fRegenerationTime = 0;
	m_fWaitToBeat = 0;
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
				m_fFallingDistance = 0;
				//cout <<"Collided in y direction" << endl;
			}
		}


		//If he reaches the ground he doesn't jump anymore
		if (m_fYVel > 0)
		{
			m_State.jumping = false;
			//	cout <<"Reached ground" << endl;
		}

		//do damage if player fell long way down
		if (m_fFallingDistance >= 400)
		{
			int damage = ((m_fFallingDistance - 400) / 100) * 20;
			DoDamage(damage - damage * (float)((float)(GetPlayerAttributes().armour)/100.0f));
		}

		m_fFallingDistance = 0;
	}
	//If he hasn't collide with anything he must be falling and you can't jump, while falling ;)
	else
	{
		m_State.jumping = true;
		//cout <<"Didn't collide in y direction" << endl;
	}


	CheckArmAnimation();


	//check if the player felt down 
	if (m_fYVel > 0)
	{
		m_fFallingDistance += m_fYVel;
	}


	stringstream stream;
	stream << "Fallen distance: " << m_fFallingDistance;
	g_pFramework->WriteToLog(INFO, stream.str());

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

	//check the direction of the player
	if (Mouse::getPosition().x + (m_pView->getCenter().x - m_pView->getSize().x/2) < m_pDwarf->GetRect().left + m_pDwarf->GetRect().width/2)
		m_turned_left = true;
	else
		m_turned_left = false;

	
	if (abs(m_SideSpeed) < 50)
	{
		//if the left key is pressed
		if (((Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) && m_StatusEffects[EFFECT_DRUNK].m_fDuration <= 5.0f) || (m_StatusEffects[EFFECT_DRUNK].m_fDuration > 5.0f && (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))))
		{
			//m_turned_left = true;

			m_fXVel = (float)-m_modifications.speed * g_pTimer->GetElapsedTime().asSeconds();

			//check legs
			if (m_turned_left)
			{
				m_fAnimState -= 8.0f * (m_modifications.speed / 150) * g_pTimer->GetElapsedTime().asSeconds();

				//start the animation new if it has reached it's end
				if (m_fAnimState < 0 || m_fAnimState > 7)
					m_fAnimState = 6.99f;
			}
			else
			{

				m_fAnimState += 8.0f * (m_modifications.speed / 150) * g_pTimer->GetElapsedTime().asSeconds();
				//start the animation new if it has reached it's end
				if (m_fAnimState < 7 || m_fAnimState > 14)
					m_fAnimState = 7;
			}
			

		}
		//if the right key is pressed
		else if (((Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) && m_StatusEffects[EFFECT_DRUNK].m_fDuration <= 5.0f) || (m_StatusEffects[EFFECT_DRUNK].m_fDuration> 5.0f && (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))))
		{
			//m_turned_left = false;

			m_fXVel = (float)m_modifications.speed * g_pTimer->GetElapsedTime().asSeconds();

			//check legs
			if (m_turned_left)
			{
				m_fAnimState -= 8.0f * (m_modifications.speed / 150) * g_pTimer->GetElapsedTime().asSeconds();

				//start the animation new if it has reached it's end
				if (m_fAnimState < 0 || m_fAnimState > 7)
					m_fAnimState = 6.99f;
			}
			else
			{

				m_fAnimState += 8.0f * (m_modifications.speed / 150) * g_pTimer->GetElapsedTime().asSeconds();
				//start the animation new if it has reached it's end
				if (m_fAnimState < 7 || m_fAnimState > 14)
					m_fAnimState = 7;
			}

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
	//check health and mana
	m_fRegenerationTime -= g_pTimer->GetElapsedTime().asSeconds();

	//refresh health and mana
	if (m_fRegenerationTime <= 0)
	{
		m_Attributes.currentHealth += m_modifications.healthRegeneration;

		if (m_Attributes.currentHealth > m_modifications.maxHealth)
			m_Attributes.currentHealth = m_modifications.maxHealth;

		m_Attributes.currentMana += m_modifications.manaRegeneration;

		if (m_Attributes.currentMana > m_modifications.maxMana)
			m_Attributes.currentMana = m_modifications.maxMana;

		m_fRegenerationTime = 3;
	}


	//if the player is carrying a tool: render it
	CThing *thing = m_pInventory->GetCarriedThing();
	if(thing != NULL && thing->getID() > CTBREAK && thing->getID() < TEBREAK)
	{
		CTool *tool = (CTool *)thing;

		//if the player carries a lantern: render a light circle
		if(tool->getID() == LANTERN)
			m_pWorld->GetLightMachine()->AddLightCircle(m_pDwarf->GetHandPos(m_turned_left).x, m_pDwarf->GetHandPos(m_turned_left).y, 350, Color(0,0,0,0));

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
		m_pWorld->GetLightMachine()->AddLightCircle(m_pDwarf->GetRect().left + m_pDwarf->GetRect().width/2, m_pDwarf->GetRect().top, 250, Color(0,0,0,0));
}


//returns the rect of the carried weapon 
IntRect CPlayer::GetWeaponRect()
{
	CThing *thing = m_pInventory->GetCarriedThing();
	if(thing != NULL && thing->getID() > CTBREAK && thing->getID() < TEBREAK)
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
		m_pLifeBeam->RenderWithNumbers(g_pFramework->GetRenderWindow());
		m_pManaBeam->RenderWithNumbers(g_pFramework->GetRenderWindow());
		m_pExpBeam->RenderWithNumbers(g_pFramework->GetRenderWindow());
	}
	else
	{
		m_pLifeBeam->Render(g_pFramework->GetRenderWindow());
		m_pManaBeam->Render(g_pFramework->GetRenderWindow());
		m_pExpBeam->Render(g_pFramework->GetRenderWindow());
	}

	//show the status effects
	int x = 10;
	int y = 95;
	for (int i = 0; i < NUMBER_OF_EFFECTS; i++)
	{
		if (m_StatusEffects[i].m_fDuration > 0.0f)
		{
			m_StatusDuration[i].resize((m_StatusEffects[i].m_fTimeLeft / m_StatusEffects[i].m_fDuration) * 361);

			m_StatusDuration[i][0].position = Vector2f(x + 35, y + 35);

			for (int a = 1; a < m_StatusDuration[i].getVertexCount(); a++)
			{
				m_StatusDuration[i][a].position = (Vector2f(x + 34.5 + 39 * cos(a * 3.1415926535 / 180), y + 34.5 + 39 * sin(a * 3.1415926535 / 180)));
				m_StatusDuration[i][a].color = Color(200, 0, 200, 200);
			}

			
			g_pFramework->GetRenderWindow()->draw(m_StatusDuration[i]);

			m_StatusEffects[i].m_Sprite->SetPos(x,y);
			m_StatusEffects[i].m_Sprite->Render(g_pFramework->GetRenderWindow());
			m_StatusEffects[i].m_fTimeLeft -= g_pTimer->GetElapsedTime().asSeconds();


			if (m_StatusEffects[i].m_fTimeLeft < 0)
			{
				m_StatusEffects[i].m_fDuration = 0;
				m_StatusEffects[i].m_fTimeLeft = 0;
			}

			x += 80;
		}
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
			m_pMagicMenu->SetOpen(false);
	}
	else if(g_pFramework->keyStates.bUp && !m_pBuildingMenu->GetOpen())
	{
			m_PanelInventory.m_isClicked = false;
			m_PanelAttributes.m_isClicked = false;
			m_PanelBuilding.m_isClicked = true;
			m_PanelMagic.m_isClicked = false;

			m_pInventory->SetOpen(false);
			m_pCharacterInfo->SetOpen(false);
			m_pMagicMenu->SetOpen(false);
	}
	else if(g_pFramework->keyStates.cUp && !m_pCharacterInfo->GetOpen())
	{
			m_PanelInventory.m_isClicked = false;
			m_PanelAttributes.m_isClicked = true;
			m_PanelBuilding.m_isClicked = false;
			m_PanelMagic.m_isClicked = false;

			m_pInventory->SetOpen(false);
			m_pBuildingMenu->SetOpen(false);
			m_pMagicMenu->SetOpen(false);
	}
	else if (g_pFramework->keyStates.mUp && !m_pMagicMenu->GetOpen())
	{
		m_PanelInventory.m_isClicked = false;
		m_PanelAttributes.m_isClicked = false;
		m_PanelBuilding.m_isClicked = false;
		m_PanelMagic.m_isClicked = true;

		m_pInventory->SetOpen(false);
		m_pBuildingMenu->SetOpen(false);
		m_pCharacterInfo->SetOpen(false);
	}


	if(m_pInventory->GetOpen() || m_pBuildingMenu->GetOpen() || m_pCharacterInfo->GetOpen() || m_pMagicMenu->GetOpen())
	{
		//render the panels
		m_pPanelBeam->Render(g_pFramework->GetRenderWindow());

		//if the player wants to close the menu
		if (m_pCloseButton->Render(g_pFramework->keyStates.leftMouseUp))
		{
			m_pInventory->SetOpen(false);
			m_pBuildingMenu->SetOpen(false);
			m_pCharacterInfo->SetOpen(false);
			m_pMagicMenu->SetOpen(false);
		}
	
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
				m_pMagicMenu->SetOpen(false);
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
				m_pMagicMenu->SetOpen(false);
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
				m_pMagicMenu->SetOpen(false);
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
				m_pMagicMenu->SetOpen(true);
			}
		}

		//renders the panel buttons
		m_PanelInventory.m_Sprite->Render(g_pFramework->GetRenderWindow(), m_PanelInventory.m_isClicked);
		m_PanelBuilding.m_Sprite->Render(g_pFramework->GetRenderWindow(), m_PanelBuilding.m_isClicked);
		m_PanelAttributes.m_Sprite->Render(g_pFramework->GetRenderWindow(), m_PanelAttributes.m_isClicked);
		m_PanelMagic.m_Sprite->Render(g_pFramework->GetRenderWindow(), m_PanelMagic.m_isClicked);
	}

	//renders the panels
	m_pInventory->Render(m_pDwarf->GetRect());
	m_pBuildingMenu->Render();
	m_pCharacterInfo->Render();
	m_pMagicMenu->Render();
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
	list<SConsumableAttributes>::iterator i;

	//add all active effects
	SConsumableAttributes allEffects;
	
	allEffects.armour = 0;
	allEffects.breaking_speed = 0;
	allEffects.luck = 0;
	allEffects.healthRegeneration = 0;
	allEffects.manaRegeneration = 0;
	allEffects.speed = 0;
	allEffects.strength = 0;
	allEffects.criticalChance = 0;
	allEffects.criticalDamage = 0;

	for (i = m_ActiveEffects.begin(); i != m_ActiveEffects.end();)
	{
		//add this effect to the overall effect
		allEffects.armour += i->armour;
		allEffects.breaking_speed += i->breaking_speed;
		allEffects.luck += i->luck;
		allEffects.healthRegeneration += i->healthRegeneration;
		allEffects.manaRegeneration += i->manaRegeneration;
		allEffects.speed += i->speed;
		allEffects.strength += i->strength;
		allEffects.criticalChance += i->criticalChance;
		allEffects.criticalDamage += i->criticalDamage;

		//check duration
		i->duration -= g_pTimer->GetElapsedTime().asSeconds();

		if (i->duration <= 0)
		{
			i = m_ActiveEffects.erase(i);
			continue;
		}


		i++;
	}

	////set status symbols
	//if (allEffects.armour != 0)
	//	m_StatusEffects[EFFECT_ARMOUR].m_show = true;
	//else
	//	m_StatusEffects[EFFECT_ARMOUR].m_show = false;

	//if (allEffects.breaking_speed != 0)
	//	m_StatusEffects[EFFECT_BREAKINGSPEED].m_show = true;
	//else
	//	m_StatusEffects[EFFECT_BREAKINGSPEED].m_show = false;

	//if (allEffects.luck != 0)
	//	m_StatusEffects[EFFECT_LUCK].m_show = true;
	//else
	//	m_StatusEffects[EFFECT_LUCK].m_show = false;

	//if (allEffects.healthRegeneration != 0)
	//	m_StatusEffects[EFFECT_HEALTHREGENERATION].m_show = true;
	//else
	//	m_StatusEffects[EFFECT_HEALTHREGENERATION].m_show = false;

	//if (allEffects.manaRegeneration != 0)
	//	m_StatusEffects[EFFECT_MANAREGENERATION].m_show = true;
	//else
	//	m_StatusEffects[EFFECT_MANAREGENERATION].m_show = false;

	//if (allEffects.speed != 0)
	//	m_StatusEffects[EFFECT_SPEED].m_show = true;
	//else
	//	m_StatusEffects[EFFECT_SPEED].m_show = false;

	//if (allEffects.strength != 0)
	//	m_StatusEffects[EFFECT_STRENGTH].m_show = true;
	//else
	//	m_StatusEffects[EFFECT_STRENGTH].m_show = false;

	//if (allEffects.criticalChance != 0)
	//	m_StatusEffects[EFFECT_CRITICALCHANCE].m_show = true;
	//else
	//	m_StatusEffects[EFFECT_CRITICALCHANCE].m_show = false;

	//if (allEffects.criticalDamage != 0)
	//	m_StatusEffects[EFFECT_CRITICALDAMAGE].m_show = true;
	//else
	//	m_StatusEffects[EFFECT_CRITICALDAMAGE].m_show = false;

	//if (m_fDrunk > 0)
	//	m_StatusEffects[EFFECT_DRUNK].m_show = true;
	//else
	//	m_StatusEffects[EFFECT_DRUNK].m_show = false;



	m_modifications = m_pInventory->GetEquipmentAttributes();

	CThing *thing = m_pInventory->GetCarriedThing();
	if(thing != NULL && thing->getID() > CTBREAK && thing->getID() < TEBREAK)
	{
		CTool *tool = (CTool *)thing;

		//calculate the attributes
		m_modifications.breaking_speed += tool->GetAttributes().breaking_speed + allEffects.breaking_speed + m_Attributes.breakingSpeed;    //add modification to the breaking speed
		m_modifications.armour += tool->GetAttributes().armour + allEffects.armour + m_Attributes.armour;
		m_modifications.luck += tool->GetAttributes().luck + allEffects.luck + m_Attributes.luck;
		m_modifications.maxHealth += tool->GetAttributes().maxHealth + m_Attributes.maxHealth;
		m_modifications.maxMana += tool->GetAttributes().maxMana + m_Attributes.maxMana;
		m_modifications.speed += tool->GetAttributes().speed + allEffects.speed + m_Attributes.speed;
		m_modifications.strength += tool->GetAttributes().strength + allEffects.strength + m_Attributes.strength;
		m_modifications.healthRegeneration += tool->GetAttributes().healthRegeneration + allEffects.healthRegeneration + m_Attributes.healthRegeneration;
		m_modifications.manaRegeneration += tool->GetAttributes().manaRegeneration + allEffects.manaRegeneration + m_Attributes.manaRegeneration;
		m_modifications.criticalChance += tool->GetAttributes().criticalChance + allEffects.criticalChance + m_Attributes.criticalChance;
		m_modifications.criticalDamage += tool->GetAttributes().criticalDamage + allEffects.criticalDamage + m_Attributes.criticalDamage;

	}
	else
	{
		m_modifications.breaking_speed += m_Attributes.breakingSpeed + allEffects.breaking_speed;
		m_modifications.armour += m_Attributes.armour + allEffects.armour;
		m_modifications.luck += m_Attributes.luck + allEffects.luck;
		m_modifications.maxHealth += m_Attributes.maxHealth;
		m_modifications.maxMana += m_Attributes.maxMana;
		m_modifications.speed += m_Attributes.speed + allEffects.speed;
		m_modifications.strength += m_Attributes.strength + allEffects.strength;
		m_modifications.healthRegeneration += m_Attributes.healthRegeneration + allEffects.healthRegeneration;
		m_modifications.manaRegeneration += m_Attributes.manaRegeneration + allEffects.manaRegeneration;
		m_modifications.criticalChance += m_Attributes.criticalChance + allEffects.criticalChance;
		m_modifications.criticalDamage += m_Attributes.criticalDamage + allEffects.criticalDamage;
	}
}

//returns the player's attributes (with all modifications [equipment, tools etc])
SToolAttributes CPlayer::GetPlayerAttributes()
{
	return m_modifications;
}



void CPlayer::Heal(int _life)
{
	if (m_Attributes.currentHealth + _life > m_modifications.maxHealth)
		m_Attributes.currentHealth = m_modifications.maxHealth;
	else
		m_Attributes.currentHealth += _life;

	stringstream stream;
	stream.str("");

	stream << _life;
	g_pSignMachine->AddString(stream.str(), 1, m_pDwarf->GetRect().left, m_pDwarf->GetRect().top, Color(0, 150, 0));
}




void CPlayer::DoAlchemy(int _level)
{
	m_pWorld->DoAlchemy(_level);
}





void CPlayer::AddEffect(SConsumableAttributes _attributes)
{
	//push the effect back
	m_ActiveEffects.push_back(_attributes);

	//if the effect heals instantly: do it
	if (_attributes.health != 0)
	{
		m_Attributes.currentHealth += _attributes.health;

		if (m_Attributes.currentHealth > m_Attributes.maxHealth)
			m_Attributes.currentHealth = m_Attributes.maxHealth;
	}


	if (_attributes.mana != 0)
	{
		m_Attributes.currentMana += _attributes.mana;

		if (m_Attributes.currentMana > m_Attributes.maxMana)
			m_Attributes.currentMana = m_Attributes.maxMana;
	}


	if (_attributes.duration > 0)
	{
		if (_attributes.armour != 0)
		{
			m_StatusEffects[EFFECT_ARMOUR].m_fTimeLeft += _attributes.duration;
			m_StatusEffects[EFFECT_ARMOUR].m_fDuration = m_StatusEffects[EFFECT_ARMOUR].m_fTimeLeft;
		}

		if (_attributes.breaking_speed != 0)
		{
			m_StatusEffects[EFFECT_BREAKINGSPEED].m_fTimeLeft += _attributes.duration;
			m_StatusEffects[EFFECT_BREAKINGSPEED].m_fDuration = m_StatusEffects[EFFECT_BREAKINGSPEED].m_fTimeLeft;
		}

		if (_attributes.luck != 0)
		{
			m_StatusEffects[EFFECT_LUCK].m_fTimeLeft += _attributes.duration;
			m_StatusEffects[EFFECT_LUCK].m_fDuration = m_StatusEffects[EFFECT_LUCK].m_fTimeLeft;
		}

		if (_attributes.healthRegeneration != 0)
		{
			m_StatusEffects[EFFECT_HEALTHREGENERATION].m_fTimeLeft += _attributes.duration;
			m_StatusEffects[EFFECT_HEALTHREGENERATION].m_fDuration = m_StatusEffects[EFFECT_HEALTHREGENERATION].m_fTimeLeft;
		}

		if (_attributes.manaRegeneration != 0)
		{
			m_StatusEffects[EFFECT_MANAREGENERATION].m_fTimeLeft += _attributes.duration;
			m_StatusEffects[EFFECT_MANAREGENERATION].m_fDuration = m_StatusEffects[EFFECT_MANAREGENERATION].m_fTimeLeft;
		}

		if (_attributes.speed != 0)
		{
			m_StatusEffects[EFFECT_SPEED].m_fTimeLeft += _attributes.duration;
			m_StatusEffects[EFFECT_SPEED].m_fDuration = m_StatusEffects[EFFECT_SPEED].m_fTimeLeft;
		}

		if (_attributes.strength != 0)
		{
			m_StatusEffects[EFFECT_STRENGTH].m_fTimeLeft += _attributes.duration;
			m_StatusEffects[EFFECT_STRENGTH].m_fDuration = m_StatusEffects[EFFECT_STRENGTH].m_fTimeLeft;
		}

		if (_attributes.criticalChance != 0)
		{
			m_StatusEffects[EFFECT_CRITICALCHANCE].m_fTimeLeft += _attributes.duration;
			m_StatusEffects[EFFECT_CRITICALCHANCE].m_fDuration = m_StatusEffects[EFFECT_CRITICALCHANCE].m_fTimeLeft;
		}

		if (_attributes.criticalDamage != 0)
		{
			m_StatusEffects[EFFECT_CRITICALDAMAGE].m_fTimeLeft += _attributes.duration;
			m_StatusEffects[EFFECT_CRITICALDAMAGE].m_fDuration = m_StatusEffects[EFFECT_CRITICALDAMAGE].m_fTimeLeft;
		}
	}
}