#include "Inventory.hpp"
#include "World.hpp"



CInventory::CInventory()
{
	m_pInventoryWindow = NULL;
	m_pInventoryBeam = NULL;
	m_pCarriedObjectFrame = NULL;
	m_pCurrentPanel = NULL;
	m_pEquipment = NULL;
	m_pPlayer = NULL;

	CarriedObjectFramePos = 0;

	is_open = false;
}




CInventory::~CInventory()
{
	list<SItem>::iterator i;

	for(i = m_inventoryList.begin(); i != m_inventoryList.end(); i++)
	{
		SAFE_DELETE(i->thing);
	}

	m_inventoryList.clear();

	SAFE_DELETE(m_pInventoryWindow); 
	SAFE_DELETE(m_pInventoryBeam);
	SAFE_DELETE(m_pCarriedObjectFrame);
	SAFE_DELETE(m_pEquipment);
}




//Loads the sprites and sets the position of the places
void CInventory::Load(CWorld *_world, View *_view, CPlayer *_player, bool _loaded)
{
	m_world = _world;
	m_pPlayer = _player;
	m_view = _view;

	m_pInventoryWindow = new CSprite;
	m_pInventoryWindow->Load(&g_pTextures->t_inventoryWindow);
	m_pInventoryWindow->SetPos((int)(g_pFramework->GetWindow()->getSize().x/2 - m_pInventoryWindow->GetRect().width - 5), (int)(g_pFramework->GetWindow()->getSize().y/2 - m_pInventoryWindow->GetRect().height/2));

	m_pInventoryBeam = new CSprite;
	m_pInventoryBeam->Load(&g_pTextures->t_inventoryBeam);
	m_pInventoryBeam->SetPos((int)(g_pFramework->GetWindow()->getSize().x/2 - m_pInventoryBeam->GetRect().width/2), g_pFramework->GetWindow()->getSize().y - m_pInventoryBeam->GetRect().height - 5);

	m_pCarriedObjectFrame = new CSprite;
	m_pCarriedObjectFrame->Load(&g_pTextures->t_inventoryBeamFrame);
	m_pCarriedObjectFrame->SetPos(m_pInventoryBeam->GetRect().left, m_pInventoryBeam->GetRect().top);

	if(!_loaded)
		m_pEquipment = new CPlayerEquipment;
	m_pEquipment->InitPlayerEquipment(0, _player);
	m_pEquipment->SetPos(g_pFramework->GetWindow()->getSize().x/2 + 5, m_pInventoryWindow->GetRect().top);

	m_font.loadFromFile("Data/Fonts/ltromatic.ttf");
	m_text.setFont(m_font);
	m_text.setString("");
	m_text.setCharacterSize(20);
	m_text.setColor(Color::Yellow);

	m_tooltipFont.loadFromFile("Data/Fonts/coolsville.ttf");
	m_tooltipText.setFont(m_tooltipFont);
	m_tooltipText.setString("");
	m_tooltipText.setCharacterSize(15);
	m_tooltipText.setColor(Color::Yellow);

	show_tooltip = false;

	//if this is no loaded inventory: reset the places and fill the inventory with stuff for testing :)
	if(!_loaded)
	{
		//Sets the position of the inventory places and sets them unfilled
		for(int y = 0; y < 5; y++)
		{
			for(int x = 0; x < 5; x++)
				{
					m_inventory_place_list[x][y].x = x*100 + m_pInventoryWindow->GetRect().left;
					m_inventory_place_list[x][y].y = y*100 + m_pInventoryWindow->GetRect().top;
					m_inventory_place_list[x][y].is_filled = false;
				}		
		}

		//Sets the position of the beam places and sets them unfilled
		for(int a = 0; a < 10; a++)
		{
			m_inventory_beam_place_list[a].x = a*100 + m_pInventoryBeam->GetRect().left;
			m_inventory_beam_place_list[a].y = m_pInventoryBeam->GetRect().top;
			m_inventory_beam_place_list[a].is_filled = false;
		}
	


	/*CItem *block;
	block = new CItem;
	block->Init(GOLD);
	Take(block, 2);

	CPlaceable *block2;
	block2 = new CPlaceable;
	block2->Init(STONE);
	Take(block2, 8);

	CPlaceable *block5;
	block5 = new CPlaceable;
	block5->Init(WOOD);
	Take(block5, 10);
	
	CPlaceable *block4;
	block4 = new CPlaceable;
	block4->Init(LADDER);
	Take(block4, 10);

	CItem *block7;
	block7 = new CItem;
	block7->Init(IRON);
	Take(block7, 10);

	CItem *block3;
	block3 = new CItem;
	block3->Init(SLIME);
	Take(block3, 10);

	CItem *block6;
	block6 = new CItem;
	block6->Init(RECIPE);
	Take(block6, 1);

	CPlaceable *block8;
	block8 = new CPlaceable;
	block8->Init(WOODWALL);
	Take(block8, 10);

	CTool *block9;
	block9 = new CTool;
	block9->InitTool(PICKAXE);
	Take(block9, 1);*/
	}
	
}



//adds an item to the inventory
void CInventory::Take(CThing *_thing, int _amount)
{
	list<SItem>::iterator i;

	//Check if the item is already in the inventory and no tool or equipment
	for(i = m_inventoryList.begin(); i != m_inventoryList.end(); i++)
	{
		if(i->thing->getID() == _thing->getID() && i->thing->getID() < ITBREAK && i->thing->getID() != RECIPE)
		{
			//if the spell is already in the inventory: return
			if (i->thing->getID() == SPELL)
			{
				CItem *newItem = (CItem*)_thing;
				CItem *currentItem = (CItem*)(*i).thing;

				if (newItem->GetSpecialID() == currentItem->GetSpecialID())
					return;
			}

			if (i->thing->getID() != SPELL)
			{
				//if it is, add the amount to it and delete the added thing
				i->amount += _amount;
				SAFE_DELETE(_thing);
				return;
			}
		}
	}


	//Look for a free place in the beam
	for(int a = 0; a < 10; a++)
	{
		if(m_inventory_beam_place_list[a].is_filled == false)
		{
			SItem newItem;
			newItem.amount = _amount;
			newItem.position = a;
			newItem.is_clicked = false;
			newItem.thing = _thing;
			newItem.thing->GetInventorySprite()->SetPos(static_cast<float>(m_inventory_beam_place_list[a].x +2), static_cast<float>(m_inventory_beam_place_list[a].y +2));
			m_inventoryList.push_back(newItem);

			m_inventory_beam_place_list[a].is_filled = true;
			
			return;
		}
	}

	//if there was no place in the beam: return
	if (_thing->getID() == SPELL)
		return;

	//Look for a free place in the inventory
	for(int y = 0; y < 5; y++)
	{
		for(int x = 0; x < 5; x++)
		{
			if(m_inventory_place_list[x][y].is_filled == false)
			{
				SItem newItem;
				newItem.amount = _amount;
				newItem.position = -1;
				newItem.is_clicked = false;
				newItem.thing = _thing;
				newItem.thing->GetInventorySprite()->SetPos(static_cast<float>(m_inventory_place_list[x][y].x +2), static_cast<float>(m_inventory_place_list[x][y].y +2));
				m_inventoryList.push_back(newItem);

				m_inventory_place_list[x][y].is_filled = true;

				return;
			}
		}

	}

	SAFE_DELETE(_thing);
}





void CInventory::DeleteThing(int _ID, int _amount)
{
	list<SItem>::iterator i;

	for(i = m_inventoryList.begin(); i != m_inventoryList.end(); i++)
	{
		if(i->thing->getID() == _ID)
		{
			i->amount -= _amount;
			if(i->amount <= 0)
			{
				if(i->position == -1)
					m_inventory_place_list[(i->thing->GetInventorySprite()->GetRect().left - m_pInventoryWindow->GetRect().left -2)/100][(i->thing->GetInventorySprite()->GetRect().top - m_pInventoryWindow->GetRect().top -2)/100].is_filled = false;
				else
					m_inventory_beam_place_list[i->position].is_filled = false;

				SAFE_DELETE(i->thing);
				m_inventoryList.erase(i);
				return;
			}

		}
	}
}



void CInventory::Render(IntRect &_playerRect)
{
	list<SItem>::iterator i;
	list<SItem>::iterator c;
	c = m_inventoryList.end();
	stringstream number;
	Vector2i mousePos = Mouse::getPosition();
	bool is_one_clicked = false;

	//get the current panel
	CPanel *temp = m_world->GetPanel();
	if(temp != NULL)
	{
		m_pCurrentPanel = temp;
		is_open = true;
	}

	//if e was pressed: Open or close the inventory
	if(g_pFramework->keyStates.eUp)
	{
		if(is_open)
		{
			is_open = false;
			m_pCurrentPanel = NULL;
		}
		else
		{
			is_open = true;

			if(m_pCurrentPanel == NULL)
			{
				m_pCurrentPanel = m_pEquipment;
			}
		}
	}

	//Render the beam
	m_pInventoryBeam->Render(g_pFramework->GetWindow());

	//get the clicked item
	for(i = m_inventoryList.begin(); i != m_inventoryList.end(); i++)
	{
		if(i->is_clicked == true)
		{
			c = i;
			break;
		}
	}

	//If the inventory is open: Render the window and it's content
	if(is_open)
	{
		//Renders the window
		m_pInventoryWindow->Render(g_pFramework->GetWindow());

		//if there is a panel: render it
		if(m_pCurrentPanel != NULL)
			m_pCurrentPanel->Render();

		for(i = m_inventoryList.begin(); i != m_inventoryList.end();)
		{
			//if the item was clicked
			if(i->thing->GetInventorySprite()->GetRect().contains(mousePos))
			{
				if(g_pFramework->keyStates.leftMouseDown == true)
				{
					//If the thing isn't clicked already it is now and the inventory place is now empty
					if(i->is_clicked == false)
					{
						//if the clicked item is the same as this one: add the amounts
						if(c != m_inventoryList.end() && c->thing->getID() == i->thing->getID() && i->thing->getID() < ITBREAK && i->thing->getID() != RECIPE && i->thing->getID() != SPELL)
						{
							//add the amount and delete the clicked thing
							i->amount += c->amount;
							SAFE_DELETE(c->thing);
							m_inventoryList.erase(c);
							c = m_inventoryList.end();
						}
						else
						{
							//if item is in normal inventory: empty the inventory place
							if(i->position == -1)
							{
								m_inventory_place_list[(i->thing->GetInventorySprite()->GetRect().left - m_pInventoryWindow->GetRect().left -2)/100][(i->thing->GetInventorySprite()->GetRect().top - m_pInventoryWindow->GetRect().top -2)/100].is_filled = false;
				
							}
							//else: empty the beam place and set the position to -1
							else
							{
								m_inventory_beam_place_list[(i->thing->GetInventorySprite()->GetRect().left - m_pInventoryBeam->GetRect().left -2)/100].is_filled = false;
								i->position = -1;
							}

							//item now is clicked
							i->is_clicked = true;
						}
					}
					//if the item is clicked: place or delete it
					else
					{
						//if the mouse is inside the window: place the item
						if(m_pInventoryWindow->GetRect().contains(mousePos))
						{
							int xItem = mousePos.x - m_pInventoryWindow->GetRect().left;
							int yItem = mousePos.y - m_pInventoryWindow->GetRect().top;

							xItem = (xItem - xItem%100);
							yItem = (yItem- yItem%100);

							i->thing->GetInventorySprite()->SetPos(xItem + m_pInventoryWindow->GetRect().left +2, yItem + m_pInventoryWindow->GetRect().top +2);
							i->position = -1;
							m_inventory_place_list[xItem/100][yItem/100].is_filled = true;
							
							i->is_clicked = false;
						}
						//if it is inside the beam: place it
						else if(m_pInventoryBeam->GetRect().contains(mousePos))
						{
							int xItem = mousePos.x - m_pInventoryBeam->GetRect().left;						

							xItem = (xItem - xItem%100);

							i->thing->GetInventorySprite()->SetPos(xItem + m_pInventoryBeam->GetRect().left +2, m_pInventoryBeam->GetRect().top +2);
							i->position = xItem/100;
							m_inventory_beam_place_list[xItem/100].is_filled = true;
						
							i->is_clicked = false;
						}
						//if it is inside a panel: try to place it there
						else if(m_pCurrentPanel != NULL && m_pCurrentPanel->GetRect().contains(mousePos))
						{
							//set position to 100 for a later check
							(*i).position = 100;

							//try to give the item
							SItem item = m_pCurrentPanel->Take(*i);
							//if a item is returned
							if(item.amount != 0)
							{		
								//and this item isn't the same item that was given
								if(item.position != 100)
								{
									//add the new item to the inventory and delete the given one
									item.is_clicked = true;
									item.position = -1;
									m_inventoryList.insert(i, item);
									i = m_inventoryList.erase(i);

									//to show, that a thing was placed this frame (you can't take it this frame)
									is_one_clicked = true;
									continue;		
								}
								else
									(*i).position = -1;
							}
							//if no new item was returned: just delete the given one
							else
							{
								i = m_inventoryList.erase(i);
								is_one_clicked = true;
								continue;
							}
						}
						//else: delete it
						else
						{
							SAFE_DELETE(i->thing);
							i = m_inventoryList.erase(i);
							continue;
						}

					}
				}
				//if right mouse was clicked: check for recipe
				else if(g_pFramework->keyStates.rightMouseDown)
				{
					if(i->thing->getID() == RECIPE)
					{
						CItem *item = (CItem*)i->thing;
						if(m_pPlayer->AddRecipe(item->GetSpecialID()) == true)
						{
							SAFE_DELETE(i->thing);
							i = m_inventoryList.erase(i);

							//declare the inventory place free
							if(m_pInventoryWindow->GetRect().contains(mousePos))
							{
								int xItem = mousePos.x - m_pInventoryWindow->GetRect().left;
								int yItem = mousePos.y - m_pInventoryWindow->GetRect().top;

								xItem = (xItem - xItem%100);
								yItem = (yItem- yItem%100);

								m_inventory_place_list[xItem/100][yItem/100].is_filled = false;
							}
							else
							{
								int xItem = mousePos.x - m_pInventoryBeam->GetRect().left;						

								xItem = (xItem - xItem%100);

								m_inventory_beam_place_list[xItem/100].is_filled = false;
							}

							continue;
						}
					}

					if(i->is_clicked == false)
					{
						//if the clicked item is the same as this one: add the amounts
						if(c != m_inventoryList.end() && c->thing->getID() == i->thing->getID() && i->thing->getID() < ITBREAK && i->thing->getID() != RECIPE)
						{
							//add the amount and delete the clicked thing
							i->amount ++;
							c->amount--;
							if(c->amount <= 0)
							{
								SAFE_DELETE(c->thing);
								m_inventoryList.erase(c);
								c = m_inventoryList.end();
							}
						}
					}
					else if(i->thing->getID() < ITBREAK)
					{
							//if the mouse is inside the window: place the item
						if(m_pInventoryWindow->GetRect().contains(mousePos))
						{
							int xItem = mousePos.x - m_pInventoryWindow->GetRect().left;
							int yItem = mousePos.y - m_pInventoryWindow->GetRect().top;

							xItem = (xItem - xItem%100);
							yItem = (yItem- yItem%100);

							if(m_inventory_place_list[xItem/100][yItem/100].is_filled == false)
							{
								SItem item;
								item.amount = 1;
								item.is_clicked = false;
								item.position = -1;

								if(i->thing->getID() < PIBREAK)
								{
									item.thing = new CPlaceable;
									((CPlaceable*)item.thing)->Init(i->thing->getID());
								}
								else if(i->thing->getID() > PIBREAK && i->thing->getID() < ITBREAK)
								{
									item.thing = new CItem;
									((CItem*)item.thing)->Init(i->thing->getID());	
								}
								
								item.thing->GetInventorySprite()->SetPos(xItem + m_pInventoryWindow->GetRect().left +2, yItem + m_pInventoryWindow->GetRect().top +2);
								m_inventoryList.insert(i,item);
								m_inventory_place_list[xItem/100][yItem/100].is_filled = true;

								i->amount--;
								if(i->amount <= 0)
								{
									i++;
									SAFE_DELETE(c->thing);
									m_inventoryList.erase(c);
									c = m_inventoryList.end();
									continue;
								}
							}
				
						}
						//if it is inside the beam: place it
						else if(m_pInventoryBeam->GetRect().contains(mousePos))
						{
							int xItem = mousePos.x - m_pInventoryBeam->GetRect().left;						

							xItem = (xItem - xItem%100);

							if(m_inventory_beam_place_list[xItem/100].is_filled == false)
							{
								SItem item;
								item.amount = 1;
								item.is_clicked = false;
								item.position = xItem/100;

								if(i->thing->getID() < PIBREAK)
								{
									item.thing = new CPlaceable;
									((CPlaceable*)item.thing)->Init(i->thing->getID());
								}
								else if(i->thing->getID() > PIBREAK && i->thing->getID() < ITBREAK)
								{
									item.thing = new CItem;
									((CItem*)item.thing)->Init(i->thing->getID());	
								}
								
								item.thing->GetInventorySprite()->SetPos(xItem + m_pInventoryBeam->GetRect().left +2, m_pInventoryBeam->GetRect().top +2);
								m_inventoryList.insert(i,item);
								m_inventory_beam_place_list[xItem/100].is_filled = true;

								i->amount--;
								if(i->amount <= 0)
								{				
									i++;
									SAFE_DELETE(c->thing);
									m_inventoryList.erase(c);
									c = m_inventoryList.end();
									continue;
								}
							}
						}	
						else if(m_pCurrentPanel != NULL && m_pCurrentPanel->GetRect().contains(mousePos))
						{
							SItem item;
							item.amount = 1;
							item.position = 100;

							if(i->thing->getID() < PIBREAK)
							{
								item.thing = new CPlaceable;
								((CPlaceable*)item.thing)->Init(i->thing->getID());
							}
							else if(i->thing->getID() > PIBREAK && i->thing->getID() < ITBREAK)
							{
								item.thing = new CItem;
								((CItem*)item.thing)->Init(i->thing->getID());	
							}

							//try to give the item
							item = m_pCurrentPanel->Take(item);

							//if a item is returned
							if(item.amount != 0)
							{		
								//and this item isn't the same item that was given: give it back
								if(item.position != 100)
								{
									m_pCurrentPanel->Take(item);

									//to show, that a thing was placed this frame (you can't take it this frame)
									is_one_clicked = true;	
								}
							}
							//if no new item was returned: just delete the given one
							else
							{
								i->amount--;
								if(i->amount <= 0)
								{
									i++;
									SAFE_DELETE(c->thing);
									m_inventoryList.erase(c);
									c = m_inventoryList.end();
								}
								else
									i++;

								is_one_clicked = true;
							
								continue;
							}
						}

					}
				}
				//if there is no item clicked: prepare the tooltip
				else if(c == m_inventoryList.end())
				{	
					number.str("");
					number << (i->thing->GetName());

					//if the thing is equipment or a tool: change the coulor of the text
					if(i->thing->getID() > ITBREAK)
					{
						int rarity = 1;

						//if it is equipment:
						if(i->thing->getID() > TEBREAK)
						{
							CEquipment *equipment = (CEquipment*)i->thing;
							rarity = equipment->GetRarity();

							//show the additional attributes
							if(equipment->GetAttributes().armour != 0)
								number << "\nRüstung: " << equipment->GetAttributes().armour;
							if(equipment->GetAttributes().breaking_speed != 0)
								number << "\nAbbaugeschwindigkeit: " << equipment->GetAttributes().breaking_speed;
							if(equipment->GetAttributes().luck != 0)
								number << "\nGlück: " << equipment->GetAttributes().luck;
							if(equipment->GetAttributes().maxHealth != 0)
								number << "\nLeben " << equipment->GetAttributes().maxHealth;
							if (equipment->GetAttributes().healthRegeneration != 0)
								number << "\nLebensregeneration " << equipment->GetAttributes().healthRegeneration;
							if(equipment->GetAttributes().maxMana != 0)
								number << "\nMana " << equipment->GetAttributes().maxMana;
							if (equipment->GetAttributes().manaRegeneration != 0)
								number << "\nManaregeneration " << equipment->GetAttributes().manaRegeneration;
							if(equipment->GetAttributes().speed != 0)
								number << "\nGeschwindigkeit " << equipment->GetAttributes().speed;
							if(equipment->GetAttributes().strength != 0)
								number << "\nStärke " << equipment->GetAttributes().strength;
							if (equipment->GetAttributes().criticalChance != 0)
								number << "\nKritische Chance " << equipment->GetAttributes().criticalChance;
							if (equipment->GetAttributes().criticalDamage != 0)
								number << "\nKritischer Schaden " << equipment->GetAttributes().criticalDamage;
						
						}
						//if it is a tool
						else
						{
							CTool *tool = (CTool*)i->thing;
							rarity = tool->GetRarity();
							
							if(tool->GetAttributes().armour != 0)
								number << "\nRüstung: " << tool->GetAttributes().armour;
							if(tool->GetAttributes().breaking_speed != 0)
								number << "\nAbbaugeschwindigkeit: " << tool->GetAttributes().breaking_speed;
							if(tool->GetAttributes().luck != 0)
								number << "\nGlück: " << tool->GetAttributes().luck;
							if(tool->GetAttributes().maxHealth != 0)
								number << "\nLeben " << tool->GetAttributes().maxHealth;
							if (tool->GetAttributes().healthRegeneration != 0)
								number << "\nLebensregeneration " << tool->GetAttributes().healthRegeneration;
							if(tool->GetAttributes().maxMana != 0)
								number << "\nMana " << tool->GetAttributes().maxMana;
							if (tool->GetAttributes().manaRegeneration != 0)
								number << "\nManaregeneration " << tool->GetAttributes().manaRegeneration;
							if(tool->GetAttributes().speed != 0)
								number << "\nGeschwindigkeit " << tool->GetAttributes().speed;
							if(tool->GetAttributes().strength != 0)
								number << "\nStärke " << tool->GetAttributes().strength;
							if (tool->GetAttributes().criticalChance != 0)
								number << "\nKritische Chance " << tool->GetAttributes().criticalChance;
							if (tool->GetAttributes().criticalDamage != 0)
								number << "\nKritischer Schaden " << tool->GetAttributes().criticalDamage;
						}

						//sets the color
						switch(rarity)
						{
						case(2):
							m_tooltipText.setColor(Color::Magenta);
							break;
						case(3):
							m_tooltipText.setColor(Color::Red);
							break;
						case(4):
							m_tooltipText.setColor(Color::Blue);
							break;
						case(5):
							m_tooltipText.setColor(Color::Cyan);
							break;
						default:
							m_tooltipText.setColor(Color::Yellow);
						}
					}
					else
						m_tooltipText.setColor(Color::Yellow);

					m_tooltipText.setString(number.str().c_str());
					m_tooltipText.setPosition((float)(Mouse::getPosition().x + 13), (float)(Mouse::getPosition().y));

					FloatRect backgroundRect = m_tooltipText.getLocalBounds();
					m_tooltipBackground = RectangleShape(Vector2f(backgroundRect.width, backgroundRect.height + 5));
					m_tooltipBackground.setFillColor(Color::Black);
				
					show_tooltip = true;
				}

			}
			
			


			//If the item is clicked: the position is the mouse position
			if(i->is_clicked)
			{
				i->thing->GetInventorySprite()->SetPos(mousePos.x - 49, mousePos.y - 49);
				is_one_clicked = true;
			}
			

			//Renders the inventory sprite of the thing
			i->thing->RenderInventorySprite();

			number.str("");
			number << (i->amount);
			m_text.setString(number.str().c_str());
			m_text.setPosition((float)(i->thing->GetInventorySprite()->GetRect().left + 70), (float)(i->thing->GetInventorySprite()->GetRect().top + 70));
			g_pFramework->GetWindow()->draw(m_text);			

			i++;
		}

		//render the tooltip
		if(show_tooltip)
		{
			g_pFramework->GetWindow()->draw(m_tooltipBackground, m_tooltipText.getTransform());
			g_pFramework->GetWindow()->draw(m_tooltipText);	
			show_tooltip = false;
		}

		//check if player wants to get a thing from a panel
		if(!is_one_clicked && g_pFramework->keyStates.leftMouseDown == true)
		{
			if(m_pCurrentPanel != NULL && m_pCurrentPanel->GetRect().contains(mousePos))
			{
				SItem item;
				item.amount = 0;

				//try to give the item
				item = m_pCurrentPanel->Take(item);
				
				//if a item is returned
				if(item.amount != 0)
				{	
					//add the new item to the inventory 
					item.is_clicked = true;
					item.position = -1;
					m_inventoryList.push_back(item);
				}
			}
		}


	}
	//if the inventory isn't open
	else
	{
		for(i = m_inventoryList.begin(); i != m_inventoryList.end();)
		{
			//If the thing is in the beam: Render it
			if(i->position > -1)
			{
				//if the player wants to place an placeable
				if(CarriedObjectFramePos == i->position && Mouse::isButtonPressed(Mouse::Right) && (i->thing->getID() < PIBREAK || i->thing->getID() == LANTERN))
				{
					if(m_world->PlaceNewThing((int)(Mouse::getPosition().x + (m_view->getCenter().x - m_view->getSize().x/2)), (int)(Mouse::getPosition().y + (m_view->getCenter().y - m_view->getSize().y/2)), i->thing->getID(), _playerRect) == true)
					{
						i->amount --;

						//if the placed thing was the last of it's type: free the inventory place
						if(i->amount <= 0)
						{
							m_inventory_beam_place_list[i->position].is_filled = false;
							SAFE_DELETE(i->thing);
							i = m_inventoryList.erase(i);
							continue;
						}
					}
				}
				//if the player wants to cast a spell
				else if (CarriedObjectFramePos == i->position && g_pFramework->keyStates.rightMouseUp && i->thing->getID() == SPELL)
				{
					CItem *spell;
					spell = (CItem*)(i->thing);

					//cast the spell
					m_pPlayer->CastSpell(spell->GetSpecialID());
				}

				i->thing->RenderInventorySprite();

				number.str("");
				number << (i->amount);
				m_text.setString(number.str().c_str());
				m_text.setPosition((float)(i->thing->GetInventorySprite()->GetRect().left + 70), (float)(i->thing->GetInventorySprite()->GetRect().top + 70));
				g_pFramework->GetWindow()->draw(m_text);
			}

			i++;
		}
	}


	//sets the beam frame and renders it
	//if the player has pressed a num key: set the frame
	if(Keyboard::isKeyPressed(Keyboard::Num1))
		CarriedObjectFramePos = 0;
	else if(Keyboard::isKeyPressed(Keyboard::Num2))
		CarriedObjectFramePos = 1;
	else if(Keyboard::isKeyPressed(Keyboard::Num3))
		CarriedObjectFramePos = 2;
	else if(Keyboard::isKeyPressed(Keyboard::Num4))
		CarriedObjectFramePos = 3;
	else if(Keyboard::isKeyPressed(Keyboard::Num5))
		CarriedObjectFramePos = 4;
	else if(Keyboard::isKeyPressed(Keyboard::Num6))
		CarriedObjectFramePos = 5;
	else if(Keyboard::isKeyPressed(Keyboard::Num7))
		CarriedObjectFramePos = 6;
	else if(Keyboard::isKeyPressed(Keyboard::Num8))
		CarriedObjectFramePos = 7;
	else if(Keyboard::isKeyPressed(Keyboard::Num9))
		CarriedObjectFramePos = 8;
	else if(Keyboard::isKeyPressed(Keyboard::Num0))
		CarriedObjectFramePos = 9;
	
	//if the player scrolled the mouse wheel: move the frame
	CarriedObjectFramePos -= g_pFramework->keyStates.mouseWheelMovement;
	
    //if the frame pos is to high or low: reset it
	if(CarriedObjectFramePos > 9)
		CarriedObjectFramePos = 0;
	else if(CarriedObjectFramePos < 0)
		CarriedObjectFramePos = 9;

	

	m_pCarriedObjectFrame->SetPos(CarriedObjectFramePos*100 + m_pInventoryBeam->GetRect().left, m_pInventoryBeam->GetRect().top);
	m_pCarriedObjectFrame->Render(g_pFramework->GetWindow());
}




//returns the currently carried thing
CThing *CInventory::GetCarriedThing()
{
	list<SItem>::iterator i;
	for(i = m_inventoryList.begin(); i != m_inventoryList.end(); i++)
	{		
		//if reached the carried thing: return it
		if(CarriedObjectFramePos == i->position)
			return i->thing;		
	}

	return NULL;
}


//returns true if this amount of the thing is in the inventory
bool CInventory::IsAmountOfThing(int _ID, int _amount)
{
	list<SItem>::iterator i;

	for(i = m_inventoryList.begin(); i != m_inventoryList.end(); i++)
	{
		if(i->thing->getID() == _ID)
		{
			if(i->amount >= _amount)
				return true;
			else
				return false;
		}
	}

	return false;
}




void CInventory::RenderEquipment(int _x, int _y, bool _left)
{
	m_pEquipment->RenderEquipment(_x, _y, _left);
}