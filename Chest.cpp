#include "Chest.hpp"





CChest::CChest()
{
	m_pPanel = NULL;	
}



CChest::~CChest()
{

}


void CChest::Quit()
{
	for(int y = 0; y < 5; y++)
		{
			for(int x = 0; x < 5; x++)
			{
				SAFE_DELETE(m_chest[x][y].thing);
			}
		}	
}


void CChest::Init(int _Number, bool _loaded)
{
	m_pPanel = new CSprite;
	m_pPanel->Load(&g_pTextures->t_inventoryWindow);
	m_pPanel->SetPos((int)g_pFramework->GetWindow()->getSize().x/2 + 5, (int)g_pFramework->GetWindow()->getSize().y/2 - m_pPanel->GetRect().height/2);

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


	if(!_loaded)
	{
		m_Number = _Number;
		m_PanelType = PANEL_CHEST;

		//Sets the position of the inventory places and sets them unfilled
		for(int y = 0; y < 5; y++)
		{
			for(int x = 0; x < 5; x++)
				{
					m_chest[x][y].amount = 0;
					m_chest[x][y].is_clicked = false;
					m_chest[x][y].position = -1;
					m_chest[x][y].thing = NULL;
				}		
		}
	}
}





void CChest::CheckThings()
{
}




void CChest::Render()
{
	stringstream number;

	//render the window
	m_pPanel->Render(g_pFramework->GetWindow());

	for(int y = 0; y < 5; y++)
	{
		for(int x = 0; x < 5; x++)
		{
			//if there is an item: render it
			if(m_chest[x][y].amount > 0)
			{
				//renders the inventory sprite of the thing
				m_chest[x][y].thing->RenderInventorySprite();

				//renders the amount
				number.str("");
				number << (m_chest[x][y].amount);
				m_text.setString(number.str().c_str());
				m_text.setPosition((float)(m_chest[x][y].thing->GetInventorySprite()->GetRect().left + 70), (float)(m_chest[x][y].thing->GetInventorySprite()->GetRect().top + 70));
				g_pFramework->GetWindow()->draw(m_text);	


				//if needed set tooltip
				if(m_chest[x][y].thing->GetInventorySprite()->GetRect().contains(Mouse::getPosition()) && !Mouse::isButtonPressed(Mouse::Left))
				{
					number.str("");
					number << m_chest[x][y].thing->GetName();

					//if it is a tool or equipment: show possible rarity and additional attributes
					if(m_chest[x][y].thing->getID() > CTBREAK)
					{
						int rarity = 1;

						//if it is equipment:
						if(m_chest[x][y].thing->getID() > TEBREAK)
						{
							CEquipment *equipment = (CEquipment*)m_chest[x][y].thing;
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
							CTool *tool = (CTool*)m_chest[x][y].thing;
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
					m_tooltipText.setPosition((float)(Mouse::getPosition().x + 13), float(Mouse::getPosition().y));

					FloatRect backgroundRect = m_tooltipText.getLocalBounds();
					m_tooltipBackground = RectangleShape(Vector2f(backgroundRect.width, backgroundRect.height + 5));
					m_tooltipBackground.setFillColor(Color::Black);

					show_tooltip = true;
				}
			}
		}
	}


		//render the tooltip
		if(show_tooltip)
		{
			g_pFramework->GetWindow()->draw(m_tooltipBackground, m_tooltipText.getTransform());
			g_pFramework->GetWindow()->draw(m_tooltipText);	
			show_tooltip = false;
		}
}







SItem CChest::Take(SItem _item)
{
	SItem temp = _item;
	Vector2i mousePos = Mouse::getPosition();

	//get the position inside the window
	int xItem = mousePos.x - m_pPanel->GetRect().left;
	int yItem = mousePos.y - m_pPanel->GetRect().top;

	xItem = (xItem - xItem%100);
	yItem = (yItem - yItem%100);

	//if there is already an item
	if(m_chest[xItem/100][yItem/100].amount > 0)
	{
		//if there was no item given: just return the clicked item and delete it
		if(_item.amount == 0)
		{
			temp = m_chest[xItem/100][yItem/100];

			m_chest[xItem/100][yItem/100].amount = 0;
			m_chest[xItem/100][yItem/100].thing = NULL;
		}
		else
		{
			//if the given item is the same as the current item: add the amount
			if(_item.thing->getID() == m_chest[xItem/100][yItem/100].thing->getID() && _item.thing->getID() < CTBREAK && _item.thing->getID() != RECIPE)
			{
				m_chest[xItem/100][yItem/100].amount += _item.amount;
				temp.amount = 0;
			}
			//else: change the items
			else
			{
				//the return item
				temp = m_chest[xItem/100][yItem/100];

				//the given item
				m_chest[xItem/100][yItem/100] = _item;
				m_chest[xItem/100][yItem/100].thing->GetInventorySprite()->SetPos(xItem + m_pPanel->GetRect().left +2, yItem + m_pPanel->GetRect().top +2);
				m_chest[xItem/100][yItem/100].position = -1;
			}
		}
	}
	//if there is no item: place the new item
	else
	{
		//sets the new position of the item
		_item.thing->GetInventorySprite()->SetPos(xItem + m_pPanel->GetRect().left +2, yItem + m_pPanel->GetRect().top +2);

		//adds the item
		m_chest[xItem/100][yItem/100] = _item;
		m_chest[xItem/100][yItem/100].position = -1;

		//sets the return amount to zero
		temp.amount = 0;
	}


	return temp;
}





void CChest::TakeThing(SItem _item)
{
	for(int y = 0; y < 5; y++)
	{
		for(int x = 0; x < 5; x++)
		{
			if(m_chest[x][y].amount <= 0)
			{
				m_chest[x][y] = _item;
				m_chest[x][y].position = -1;
				m_chest[x][y].is_clicked = false; 
				m_chest[x][y].thing->GetInventorySprite()->SetPos(x*100 + m_pPanel->GetRect().left +2, y*100 + m_pPanel->GetRect().top +2);
				return;
			}
		}
	}
}



//returns the content of the chest
vector<SItem> CChest::GetContent()
{
	vector<SItem> items;
	items.clear();

	for(int y = 0; y < 5; y++)
	{
		for(int x = 0; x < 5; x++)
		{
			if(m_chest[x][y].amount > 0)
				items.push_back(m_chest[x][y]);
		}
	}
	return items;
}