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
				if (m_chest[x][y].amount > 0)
					SAFE_DELETE(m_chest[x][y].thing);
			}
		}	
}


void CChest::Init(int _Number, bool _loaded)
{
	m_pPanel = new CSprite;
	m_pPanel->Load(&g_pTextures->t_inventoryWindow);
	m_pPanel->SetPos((int)g_pFramework->GetRenderWindow()->getSize().x/2 + 5, (int)g_pFramework->GetRenderWindow()->getSize().y/2 - m_pPanel->GetRect().height/2);

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
	m_pPanel->Render(g_pFramework->GetRenderWindow());

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
				g_pFramework->GetRenderWindow()->draw(m_text);	


				//if needed set tooltip
				if(m_chest[x][y].thing->GetInventorySprite()->GetRect().contains(Mouse::getPosition()) && !Mouse::isButtonPressed(Mouse::Left))
				{
					m_tooltipText.setString(GetTooltip(m_chest[x][y].thing).str().c_str());
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
			g_pFramework->GetRenderWindow()->draw(m_tooltipBackground, m_tooltipText.getTransform());
			g_pFramework->GetRenderWindow()->draw(m_tooltipText);	
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




stringstream CChest::GetTooltip(CThing *_thing)
{
	stringstream number;
	SToolAttributes attributes;
	int rarity = 1;
	
	number.str("");
	number << _thing->GetName();

	if (_thing->getID() > ICBREAK)
	{
		//if it is a tool or equipment: show possible rarity and additional attributes
		if (_thing->getID() > CTBREAK)
		{
			//if it is equipment:
			if (_thing->getID() > TEBREAK)
			{
				attributes = ((CEquipment*)_thing)->GetAttributes();
				rarity = ((CEquipment*)(_thing))->GetRarity();
			}
			else if (_thing->getID() > CTBREAK)
			{
				attributes = ((CTool*)_thing)->GetAttributes();
				rarity = ((CTool*)(_thing))->GetRarity();
			}

			//show the additional attributes
			if (attributes.armour != 0)
				number << "\n" << g_pStringContainer->m_Strings[STRING_ARMOUR] << ": " << attributes.armour;
			if (attributes.breaking_speed != 0)
				number << "\n" << g_pStringContainer->m_Strings[STRING_BREAKINGSPEED] << ": " << attributes.breaking_speed;
			if (attributes.luck != 0)
				number << "\n" << g_pStringContainer->m_Strings[STRING_LUCK] << ": " << attributes.luck;
			if (attributes.maxHealth != 0)
				number << "\n" << g_pStringContainer->m_Strings[STRING_HEALTH] << ": " << attributes.maxHealth;
			if (attributes.healthRegeneration != 0)
				number << "\n" << g_pStringContainer->m_Strings[STRING_HEALTHREGENERATION] << ": " << attributes.healthRegeneration;
			if (attributes.maxMana != 0)
				number << "\n" << g_pStringContainer->m_Strings[STRING_MANA] << ": " << attributes.maxMana;
			if (attributes.manaRegeneration != 0)
				number << "\n" << g_pStringContainer->m_Strings[STRING_MANAREGENERATION] << ": " << attributes.manaRegeneration;
			if (attributes.speed != 0)
				number << "\n" << g_pStringContainer->m_Strings[STRING_SPEED] << ": " << attributes.speed;
			if (attributes.strength != 0)
				number << "\n" << g_pStringContainer->m_Strings[STRING_STRENGTH] << ": " << attributes.strength;
			if (attributes.criticalChance != 0)
				number << "\n" << g_pStringContainer->m_Strings[STRING_CRITICALCHANCE] << ": " << attributes.criticalChance;
			if (attributes.criticalDamage != 0)
				number << "\n" << g_pStringContainer->m_Strings[STRING_CRITICALDAMAGE] << ": " << attributes.criticalDamage;
			if (attributes.light != 0)
				number << "\n" << g_pStringContainer->m_Strings[STRING_LIGHT] << ": " << attributes.light;
		}
		else
		{
			CConsumable *con = (CConsumable*)_thing;

			number << " " << g_pStringContainer->m_Strings[STRING_CONSUMABLE];

			if (con->GetAttributes().armour != 0)
				number << "\n" << g_pStringContainer->m_Strings[STRING_ARMOUR] << ": " << con->GetAttributes().armour;
			if (con->GetAttributes().breaking_speed != 0)
				number << "\n" << g_pStringContainer->m_Strings[STRING_BREAKINGSPEED] << ": " << con->GetAttributes().breaking_speed;
			if (con->GetAttributes().luck != 0)
				number << "\n" << g_pStringContainer->m_Strings[STRING_LUCK] << ": " << con->GetAttributes().luck;
			if (con->GetAttributes().health != 0)
				number << "\n" << g_pStringContainer->m_Strings[STRING_HEALTH] << ": " << con->GetAttributes().health;
			if (con->GetAttributes().healthRegeneration != 0)
				number << "\n" << g_pStringContainer->m_Strings[STRING_HEALTHREGENERATION] << ": " << con->GetAttributes().healthRegeneration;
			if (con->GetAttributes().mana != 0)
				number << "\n" << g_pStringContainer->m_Strings[STRING_MANA] << ": " << con->GetAttributes().mana;
			if (con->GetAttributes().manaRegeneration != 0)
				number << "\n" << g_pStringContainer->m_Strings[STRING_MANAREGENERATION] << ": " << con->GetAttributes().manaRegeneration;
			if (con->GetAttributes().speed != 0)
				number << "\n" << g_pStringContainer->m_Strings[STRING_SPEED] << ": " << con->GetAttributes().speed;
			if (con->GetAttributes().strength != 0)
				number << "\n" << g_pStringContainer->m_Strings[STRING_STRENGTH] << ": " << con->GetAttributes().strength;
			if (con->GetAttributes().criticalChance != 0)
				number << "\n" << g_pStringContainer->m_Strings[STRING_CRITICALCHANCE] << ": " << con->GetAttributes().criticalChance;
			if (con->GetAttributes().criticalDamage != 0)
				number << "\n" << g_pStringContainer->m_Strings[STRING_CRITICALDAMAGE] << ": " << con->GetAttributes().criticalDamage;

			number << "\n" << g_pStringContainer->m_Strings[STRING_DURATION] << ": " << con->GetAttributes().duration;
		}
	}

	//sets the color
	switch (rarity)
	{
	case(2) :
		m_tooltipText.setColor(Color::Magenta);
		break;
	case(3) :
		m_tooltipText.setColor(Color::Red);
		break;
	case(4) :
		m_tooltipText.setColor(Color::Blue);
		break;
	case(5) :
		m_tooltipText.setColor(Color::Cyan);
		break;
	default:
		m_tooltipText.setColor(Color::Yellow);
	}

	return number;
}