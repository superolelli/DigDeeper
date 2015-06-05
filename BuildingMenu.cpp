#include "BuildingMenu.hpp"




CBuildingMenu::CBuildingMenu()
{
	m_pBuildButton = NULL;
	m_pArrowDown = NULL;
	m_pArrowUp = NULL;
	m_pBuildingMenu = NULL;
	m_pThingBackground = NULL;
}


CBuildingMenu::~CBuildingMenu()
{
	SAFE_DELETE(m_pBuildButton);
	SAFE_DELETE(m_pArrowUp);
	SAFE_DELETE(m_pArrowDown);
	SAFE_DELETE(m_pBuildingMenu);
	SAFE_DELETE(m_pThingBackground);

	list<SBuildingItem>::iterator i;
	for(i = m_recipes.begin(); i != m_recipes.end(); i++)
	{
		SAFE_DELETE(i->m_pInfoSprite);
		i->resources.clear();
	}
	
	m_recipes.clear();
	m_notAvailableRecipes.clear();
}



void CBuildingMenu::Init(CInventory * _inventory)
{
	m_pInventory = _inventory;

	m_pBuildingMenu = new CSprite;
	m_pBuildingMenu->Load(&g_pTextures->t_buildingWindow);
	m_pBuildingMenu->SetPos((int)(g_pFramework->GetRenderWindow()->getSize().x/2 - m_pBuildingMenu->GetRect().width/2), (int)(g_pFramework->GetRenderWindow()->getSize().y/2 - m_pBuildingMenu->GetRect().height/2));

	m_pBuildButton = new CButton();
	m_pBuildButton->Load(&g_pTextures->t_buildButton, m_pBuildingMenu->GetRect().left + 470, m_pBuildingMenu->GetRect().top + 420, 3);

	m_pArrowUp = new CButton();
	m_pArrowUp->Load(&g_pTextures->t_arrowUp, m_pBuildingMenu->GetRect().left + 250, m_pBuildingMenu->GetRect().top + 400, 1);

	m_pArrowDown = new CButton();
	m_pArrowDown->Load(&g_pTextures->t_arrowDown, m_pBuildingMenu->GetRect().left + 250, m_pBuildingMenu->GetRect().top + 450, 1);

	m_pThingBackground = new CSprite();
	m_pThingBackground->Load(&g_pTextures->t_buildThingBackground);

	//loads the font and applies it to the text
	m_font.loadFromFile("Data/Fonts/18cents.ttf");
	m_text.setFont(m_font);
	m_text.setCharacterSize(20);
	m_text.setColor(Color::Black);

	m_message.setFont(m_font);
	m_message.setCharacterSize(20);
	m_message.setColor(Color::Black);
	m_message.setString("");
	m_message.setPosition((float)(m_pBuildingMenu->GetRect().left + 250),(float)( m_pBuildingMenu->GetRect().top + 465));

	m_textTime = 0.0f;
	m_scroll_number = 0;

	is_open = false;

	FillRecipeList();

}



void CBuildingMenu::InitLoaded(CInventory * _inventory)
{
	m_pInventory = _inventory;

	m_pBuildingMenu = new CSprite;
	m_pBuildingMenu->Load(&g_pTextures->t_buildingWindow);
	m_pBuildingMenu->SetPos((int)(g_pFramework->GetRenderWindow()->getSize().x/2 - m_pBuildingMenu->GetRect().width/2), (int)(g_pFramework->GetRenderWindow()->getSize().y/2 - m_pBuildingMenu->GetRect().height/2));

	m_pBuildButton = new CButton();
	m_pBuildButton->Load(&g_pTextures->t_buildButton, m_pBuildingMenu->GetRect().left + 470, m_pBuildingMenu->GetRect().top + 420, 3);

	m_pArrowUp = new CButton();
	m_pArrowUp->Load(&g_pTextures->t_arrowUp, m_pBuildingMenu->GetRect().left + 250, m_pBuildingMenu->GetRect().top + 400, 1);

	m_pArrowDown = new CButton();
	m_pArrowDown->Load(&g_pTextures->t_arrowDown, m_pBuildingMenu->GetRect().left + 250, m_pBuildingMenu->GetRect().top + 450, 1);

	m_pThingBackground = new CSprite();
	m_pThingBackground->Load(&g_pTextures->t_buildThingBackground);

	//loads the font and applies it to the text
	m_font.loadFromFile("Data/Fonts/18cents.ttf");
	m_text.setFont(m_font);
	m_text.setCharacterSize(20);
	m_text.setColor(Color::Black);

	m_message.setFont(m_font);
	m_message.setCharacterSize(20);
	m_message.setColor(Color::Black);
	m_message.setString("");
	m_message.setPosition((float)(m_pBuildingMenu->GetRect().left + 250),(float)( m_pBuildingMenu->GetRect().top + 465));

	m_textTime = 0.0f;
	m_scroll_number = 0;

	is_open = false;

	list<SBuildingItem>::iterator i;

	for(i = m_recipes.begin(); i != m_recipes.end(); i++)
	{
		InitRecipe(&*i);
	}

	m_chosenItem = *m_recipes.begin();
}




//inits a given recipe (ID needed)
void CBuildingMenu::InitRecipe(SBuildingItem *_recipe)
{
	_recipe->m_pInfoSprite = new CSprite;
	_recipe->amountOfProducts = 1;

	switch(_recipe->ID)
		{
		case(PICKAXE):
			{
				_recipe->Name = "Spitzhacke (Eisen)";
				_recipe->m_pInfoSprite->Load(&g_pTextures->t_buildingInfo_pickaxe);
				_recipe->resources[WOODSTAFF] = 2;
				_recipe->resources[IRON] = 1;
			}break;
		case(SWORD):
			{
				_recipe->Name = "Eisenschwert";
				_recipe->m_pInfoSprite->Load(&g_pTextures->t_buildingInfo_sword);
				_recipe->resources[WOODSTAFF] = 1;
				_recipe->resources[IRON] = 3;
			}break;
		case(WOODSTAFF):
			{
				_recipe->Name = "Stab";
				_recipe->m_pInfoSprite->Load(&g_pTextures->t_buildingInfo_woodstaff);
				_recipe->resources[WOOD] = 1;
				_recipe->amountOfProducts = 2;
			}break;
		case(WOODWALL):
			{
				_recipe->Name = "Holzwand";
				_recipe->m_pInfoSprite->Load(&g_pTextures->t_buildingInfo_woodwall);
				_recipe->resources[WOOD] = 2;
			}break;
		case(STONEWALL):
			{
				_recipe->Name = "Steinwand";
				_recipe->m_pInfoSprite->Load(&g_pTextures->t_buildingInfo_stonewall);
				_recipe->resources[STONE] = 2;
			}break;
		case(LADDER):
			{
				_recipe->Name = "Leiter";
				_recipe->m_pInfoSprite->Load(&g_pTextures->t_buildingInfo_ladder);
				_recipe->resources[WOODSTAFF] = 6;
				_recipe->amountOfProducts = 3;
			}break;
		case(FURNANCE):
			{
				_recipe->Name = "Ofen";
				_recipe->m_pInfoSprite->Load(&g_pTextures->t_buildingInfo_furnance);
				_recipe->resources[STONE] = 8;
			}break;
		case(CHEST):
			{
				_recipe->Name = "Truhe";
				_recipe->m_pInfoSprite->Load(&g_pTextures->t_buildingInfo_chest);
				_recipe->resources[WOOD] = 3;
				_recipe->resources[IRON] = 2;
				_recipe->resources[GOLD] = 1;
			}break;
		case(CUPBOARD):
			{
				_recipe->Name = "Schrank";
				_recipe->m_pInfoSprite->Load(&g_pTextures->t_buildingInfo_cupboard);
				_recipe->resources[WOOD] = 5;
			}break;
		case(DOOR):
			{
				_recipe->Name = "Tür";
				_recipe->m_pInfoSprite->Load(&g_pTextures->t_buildingInfo_door);
				_recipe->resources[WOOD] = 2;
				_recipe->resources[IRON] = 2;
			}break;
		case(GLUE):
			{
				_recipe->Name = "Klebstoff";
				_recipe->m_pInfoSprite->Load(&g_pTextures->t_buildingInfo_glue);
				_recipe->resources[DIRT] = 1;
				_recipe->resources[SLIME] = 1;
			}break;
		case(IRONHELMET):
			{
				_recipe->Name = "Eisenhelm";
				_recipe->m_pInfoSprite->Load(&g_pTextures->t_buildingInfo_iron_helmet);
				_recipe->resources[IRON] = 4;
				_recipe->resources[GLUE] = 1;
			}break;
		case(IRONARMOUR):
			{
				_recipe->Name = "Eisenrüstung";
				_recipe->m_pInfoSprite->Load(&g_pTextures->t_buildingInfo_iron_armour);
				_recipe->resources[IRON] = 8;
				_recipe->resources[GLUE] = 3;
			}break;
		case(IRONRING):
			{
				_recipe->Name = "Eisenring";
				_recipe->m_pInfoSprite->Load(&g_pTextures->t_buildingInfo_iron_ring);
				_recipe->resources[IRON] = 2;
			}break;
		case(IRONTROUSERS):
			{
				_recipe->Name = "Eisenleggins";
				_recipe->m_pInfoSprite->Load(&g_pTextures->t_buildingInfo_iron_trousers);
				_recipe->resources[IRON] = 5;
				_recipe->resources[GLUE] = 2;
			}break;
		case(TABLE):
			{
				_recipe->Name = "Tisch";
				_recipe->m_pInfoSprite->Load(&g_pTextures->t_buildingInfo_table);
				_recipe->resources[WOOD] = 4;
			}break;
		case(ARCANUSRING):
			{
				_recipe->Name = "Arcanusring";
				_recipe->m_pInfoSprite->Load(&g_pTextures->t_buildingInfo_arcanus_ring);
				_recipe->resources[ARCANUS] = 2;
			}break;
		case(CANDLE):
			{
				_recipe->Name = "Kerze";
				_recipe->m_pInfoSprite->Load(&g_pTextures->t_buildingInfo_candle);
				_recipe->resources[WAX] = 2;
			}break;
		case(LANTERN):
			{
				_recipe->Name = "Laterne";
				_recipe->m_pInfoSprite->Load(&g_pTextures->t_buildingInfo_lantern);
				_recipe->resources[IRON] = 3;
				_recipe->resources[CANDLE] = 1;
			}break;
		case(MARBLEWALL):
			{
				_recipe->Name = "Marmorwand";
				_recipe->m_pInfoSprite->Load(&g_pTextures->t_buildingInfo_marblewall);
				_recipe->resources[MARBLE] = 2;
			}break;
		case(BEEHOUSE) :
		{
			_recipe->Name = "Bienenkiste";
			_recipe->m_pInfoSprite->Load(&g_pTextures->t_buildingInfo_beehouse);
			_recipe->resources[WOOD] = 4;
			_recipe->resources[BEEHIVE] = 1;
		}break;
		case(TORCH) :
		{
			_recipe->Name = "Fackel";
			_recipe->m_pInfoSprite->Load(&g_pTextures->t_buildingInfo_torch);
			_recipe->resources[WOODSTAFF] = 1;
			_recipe->resources[WAX] = 1;
		}break;
		case(CAULDRON) :
		{
			_recipe->Name = "Kessel";
			_recipe->m_pInfoSprite->Load(&g_pTextures->t_buildingInfo_cauldron);
			_recipe->resources[IRON] = 5;
		}break;
		case(BATTLEAXE) :
		{
			_recipe->Name = "Kampfaxt";
			_recipe->m_pInfoSprite->Load(&g_pTextures->t_buildingInfo_battleaxe);
			_recipe->resources[IRON] = 5;
			_recipe->resources[WOODSTAFF] = 1;
		}break;
		}

		_recipe->m_pInfoSprite->SetPos(m_pBuildingMenu->GetRect().left + 250, m_pBuildingMenu->GetRect().top + 4);
}



void CBuildingMenu::FillRecipeList()
{
	SBuildingItem pickaxe;
	pickaxe.ID = PICKAXE;
	InitRecipe(&pickaxe);

	SBuildingItem sword;
	sword.ID = SWORD;
	InitRecipe(&sword);

	SBuildingItem woodstaff;
	woodstaff.ID = WOODSTAFF;
	InitRecipe(&woodstaff);

	SBuildingItem woodwall;
	woodwall.ID = WOODWALL;
	InitRecipe(&woodwall);

	SBuildingItem stonewall;
	stonewall.ID = STONEWALL;
	InitRecipe(&stonewall);

	SBuildingItem ladder;
	ladder.ID = LADDER;
	InitRecipe(&ladder);

	SBuildingItem furnance;
	furnance.ID = FURNANCE;
	InitRecipe(&furnance);

	SBuildingItem chest;
	chest.ID = CHEST;
	InitRecipe(&chest);

	SBuildingItem cupboard;
	cupboard.ID = CUPBOARD;
	InitRecipe(&cupboard);

	SBuildingItem door;
	door.ID = DOOR;
	InitRecipe(&door);

	SBuildingItem glue;
	glue.ID = GLUE;
	InitRecipe(&glue);

	SBuildingItem iron_armour;
	iron_armour.ID = IRONARMOUR;
	InitRecipe(&iron_armour);

	SBuildingItem iron_ring;
	iron_ring.ID = IRONRING;
	InitRecipe(&iron_ring);

	SBuildingItem table;
	table.ID = TABLE;
	InitRecipe(&table);

	SBuildingItem candle;
	candle.ID = CANDLE;
	InitRecipe(&candle);

	SBuildingItem marblewall;
	marblewall.ID = MARBLEWALL;
	InitRecipe(&marblewall);


	SBuildingItem torch;
	torch.ID = TORCH;
	InitRecipe(&torch);


	m_recipes.push_back(iron_ring);
	m_recipes.push_back(iron_armour);
	m_recipes.push_back(torch);
	m_recipes.push_back(woodwall);
	m_recipes.push_back(candle);
	m_recipes.push_back(glue);
	m_recipes.push_back(ladder);
	m_recipes.push_back(marblewall);
	m_recipes.push_back(furnance);
	m_recipes.push_back(cupboard);
	m_recipes.push_back(sword);
	m_recipes.push_back(pickaxe);
	m_recipes.push_back(woodstaff);
	m_recipes.push_back(stonewall);
	m_recipes.push_back(table);
	m_recipes.push_back(chest);
	m_recipes.push_back(door);


	m_notAvailableRecipes.push_back(ARCANUSRING);
	m_notAvailableRecipes.push_back(IRONHELMET);
	m_notAvailableRecipes.push_back(IRONTROUSERS);
	m_notAvailableRecipes.push_back(LANTERN);
	//m_notAvailableRecipes.push_back(MAGICHAT);
	m_notAvailableRecipes.push_back(BEEHOUSE);
	m_notAvailableRecipes.push_back(CAULDRON);
	m_notAvailableRecipes.push_back(BATTLEAXE);


	m_chosenItem = pickaxe;
}



//Renders the building menu
void CBuildingMenu::Render()
{
	//if b was pressed: Open or close the menu
	if(g_pFramework->keyStates.bUp)
	{
		if(is_open)
			is_open = false;
		else
			is_open = true;
	}

	//if it is open
	if(is_open)
	{
		list<SBuildingItem>::iterator i;
		map<int, int>::iterator m;

		//set the starting coordinates
		int x = m_pBuildingMenu->GetRect().left + 5;
		int y = m_pBuildingMenu->GetRect().top + 5;

		bool enough_resources = true;

		//Render the menu
		m_pBuildingMenu->Render(g_pFramework->GetRenderWindow());
	
		//if the build button was pressed: build if possible the chosen thing
		if(g_pFramework->keyStates.leftMouseUp)
		{
			//if the build button was pressed
			if(m_pBuildButton->Render(1) == true)
			{	
				//Check if there are enough resources
				for(m = m_chosenItem.resources.begin(); m != m_chosenItem.resources.end(); m++)
				{
					if(m_pInventory->IsAmountOfThing(m->first, m->second) == false)
						enough_resources = false;
				}

				//if there are enough resources
				if(enough_resources)
				{
					//if thing is a placeable
					if(m_chosenItem.ID < PIBREAK)
					{
						CPlaceable *thing = new CPlaceable;
						thing->Init(m_chosenItem.ID);
						m_pInventory->Take(thing, m_chosenItem.amountOfProducts);		
					}
					else if(m_chosenItem.ID > PIBREAK && m_chosenItem.ID < CTBREAK)
					{
						CItem *thing = new CItem;
						thing->Init(m_chosenItem.ID);
						m_pInventory->Take(thing, m_chosenItem.amountOfProducts);	
					}
					//if thing is a tool
					else if(m_chosenItem.ID > CTBREAK && m_chosenItem.ID < TEBREAK)
					{
						CTool *thing = new CTool;
						thing->InitToolRandomly(m_chosenItem.ID);
						m_pInventory->Take(thing, m_chosenItem.amountOfProducts);

						//if tool is a sword: play sound
						if (m_chosenItem.ID == SWORD)
						{
							m_variousSounds.setBuffer(g_pSound->m_metalSliding);
							m_variousSounds.play();
						}
					}
					//if the thing is equipment
					else
					{
						CEquipment *thing = new CEquipment;
						thing->InitEquipmentRandomly(m_chosenItem.ID);
						m_pInventory->Take(thing, m_chosenItem.amountOfProducts);
					}

					//and delete the resources required to build the thing
					for(m = m_chosenItem.resources.begin(); m != m_chosenItem.resources.end(); m++)
					{
						m_pInventory->DeleteThing(m->first, m->second);
					}
				}
				else
				{
					m_message.setString("Nicht genug Materialien!");	
				}
			}

			//Render the buttons
			if(m_pArrowUp->Render(1) == true)
			{
				if(m_scroll_number > 0)
					m_scroll_number --;
			}

			if(m_pArrowDown->Render(1) == true)
			{
				if(m_scroll_number < m_recipes.size()-12)
					m_scroll_number++;
			}
		}
		else
		{
			m_pBuildButton->Render(0);
			m_pArrowUp->Render(0);
			m_pArrowDown->Render(0);
		}


		ShowText();

		//go to the right position
		list<SBuildingItem>::iterator c;
		c = m_recipes.begin();
		for(int a = 0; a < m_scroll_number; a++)
			c++;

		int counter = 0;

		//render the recipes
		for(i = c; i != m_recipes.end(); i++)
		{
			m_pThingBackground->SetPos(x, y);
			m_pThingBackground->Render(g_pFramework->GetRenderWindow());

			if(m_pThingBackground->GetRect().contains(Mouse::getPosition()) && Mouse::isButtonPressed(Mouse::Left))
			{
				m_chosenItem = *i;
			}


			m_text.setPosition((float)(x + 5) , (float)(y));
			m_text.setString(i->Name);
			g_pFramework->GetRenderWindow()->draw(m_text);

			y += 41;
			counter++;

			if(counter == 12)
				break;
		}

		//renders the building information of the chosen item
		m_chosenItem.m_pInfoSprite->Render(g_pFramework->GetRenderWindow());
	}
}



//Shows text on the building menu for 3.5 seconds
void CBuildingMenu::ShowText()
{
	if(m_message.getString() != "")
	{
		m_textTime += g_pTimer->GetElapsedTime().asSeconds();
		g_pFramework->GetRenderWindow()->draw(m_message);

		if(m_textTime >= 3.0f)
		{
			m_message.setString("");
			m_textTime = 0.0f;
		}
	}
}




bool CBuildingMenu::NewRecipe(int _ID)
{	
	list<SBuildingItem>::iterator i;

	//is this recipe already in the list?
	for(i = m_recipes.begin(); i != m_recipes.end(); i++)
	{
		if(i->ID == _ID)
			return false;
	}

	//add the recipe
	SBuildingItem newItem;
	newItem.ID = _ID;
	InitRecipe(&newItem);

	m_recipes.push_back(newItem);


	list<int>::iterator a;

	for(a = m_notAvailableRecipes.begin(); a != m_notAvailableRecipes.end(); a++)
	{
		if(*a == _ID)
		{
			a = m_notAvailableRecipes.erase(a);
			return true;
		}
	}

	return true;
}


