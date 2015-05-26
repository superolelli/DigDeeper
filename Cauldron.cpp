#include "Cauldron.hpp"




CCauldron::CCauldron()
{
	for (int i = 0; i < 4; i++)
	{
		m_Ingredience[i].thing = NULL;
		m_Ingredience[i].amount = 0;
		m_Ingredience[i].is_clicked = false;
		m_Ingredience[i].position = -1;
	}


	m_Output.thing = NULL;
	m_Output.amount = 0;
	m_Output.is_clicked = false;
	m_Output.position = -1;


	m_pCookingButton = NULL;
}


CCauldron::~CCauldron()
{

}




void CCauldron::Init(int _number, bool _loaded)
{
	m_pPanel = new CSprite;
	m_pPanel->Load(&g_pTextures->t_cauldronMenu);
	m_pPanel->SetPos((int)g_pFramework->GetWindow()->getSize().x / 2, (int)g_pFramework->GetWindow()->getSize().y / 2 - m_pPanel->GetRect().height / 2);

	m_pCookingButton = new CButton;
	m_pCookingButton->Load(&g_pTextures->t_cookingButton, m_pPanel->GetRect().left + 120, m_pPanel->GetRect().top + 235, 3);

	m_font.loadFromFile("Data/Fonts/ltromatic.ttf");
	m_text.setFont(m_font);
	m_text.setString("");
	m_text.setCharacterSize(20);
	m_text.setColor(Color::Yellow);

	m_cooking = false;


	if (!_loaded)
	{
		m_Number = _number;
		m_PanelType = PANEL_CAULDRON;
	}
}





void CCauldron::Quit()
{
	for (int i = 0; i < 4; i++)
	{
		if (m_Ingredience[i].amount > 0)
			SAFE_DELETE(m_Ingredience[i].thing);
	}

	if (m_Output.amount > 0)
		SAFE_DELETE(m_Output.thing);

	SAFE_DELETE(m_pCookingButton);
}







SItem CCauldron::Take(SItem _item)
{
	int x = 20;

	SItem temp = _item;

	//if the mouse is inside of one ingredience place: place it
	for (int i = 0; i < 4; i++)
	{
		if (IntRect(m_pPanel->GetRect().left + x, m_pPanel->GetRect().top + 40, 100, 100).contains(Mouse::getPosition()))
		{
			if (m_Ingredience[i].thing != NULL && m_Ingredience[i].amount > 0 && _item.thing != NULL && m_Ingredience[i].thing->getID() == _item.thing->getID())
			{
				return temp;
			}

			temp = m_Ingredience[i];
			temp.position = -1;

			if (_item.amount == 1)
			{
				m_Ingredience[i] = _item;
				m_Ingredience[i].thing->GetInventorySprite()->SetPos(m_pPanel->GetRect().left + x, m_pPanel->GetRect().top + 40);
			}
			else if (_item.amount >  1)
			{

				//make a new thing
				if (_item.thing->getID() < PIBREAK)
				{
					CPlaceable *thing = new CPlaceable;
					thing->Init(_item.thing->getID());
					temp.thing = thing;
				}
				//if thing is an item
				else if (_item.thing->getID() > PIBREAK && _item.thing->getID() < ICBREAK)
				{
					CItem *thing = new CItem;
					thing->Init(_item.thing->getID());
					temp.thing = thing;
				}
				else if (_item.thing->getID() > ICBREAK && _item.thing->getID() < CTBREAK)
				{
					CConsumable *thing = new CConsumable;
					thing->InitConsumable(_item.thing->getID());
					temp.thing = thing;
				}
				//if thing is a tool
				else if (_item.thing->getID() > CTBREAK && _item.thing->getID() < TEBREAK)
				{
					CTool *thing = new CTool;
					thing->InitTool(_item.thing->getID());
					temp.thing = thing;
				}
				//if thing is equipment
				else
				{
					CEquipment *thing = new CEquipment;
					thing->InitEquipment(_item.thing->getID());
					temp.thing = thing;
				}

				temp.amount = _item.amount - 1;

				m_Ingredience[i] = _item;
				m_Ingredience[i].thing->GetInventorySprite()->SetPos(m_pPanel->GetRect().left + x, m_pPanel->GetRect().top + 40);
				m_Ingredience[i].amount = 1;
			}
			else
				m_Ingredience[i].amount = 0;
		}

		x += 120;
	}


	//check the output 
	if (IntRect(m_pPanel->GetRect().left + 200, m_pPanel->GetRect().top + 360, 100, 100).contains(Mouse::getPosition()))
	{
		temp = m_Output;
		temp.position = -1;
		if (_item.amount != 0)
		{
			m_Output = _item;
			m_Output.thing->GetInventorySprite()->SetPos(m_pPanel->GetRect().left + 200, m_pPanel->GetRect().top + 360);
		}
		else
			m_Output.amount = 0;
	}


	//returns the deleted item
	return temp;
}





void CCauldron::Render()
{
	stringstream number;

	//render the window and the things
	m_pPanel->Render(g_pFramework->GetWindow());

	for (int i = 0; i < 4; i++)
	{
		//render ingredience
		if (m_Ingredience[i].amount != 0)
		{
			m_Ingredience[i].thing->RenderInventorySprite();

			//show the amount
			number.str("");
			number << (m_Ingredience[i].amount);
			m_text.setString(number.str().c_str());
			m_text.setPosition((float)(m_Ingredience[i].thing->GetInventorySprite()->GetRect().left + 70), (float)(m_Ingredience[i].thing->GetInventorySprite()->GetRect().top + 70));
			g_pFramework->GetWindow()->draw(m_text);
		}
	}


	//render output
	if (m_Output.amount != 0)
	{
		m_Output.thing->RenderInventorySprite();

		//show the amount
		number.str("");
		number << (m_Output.amount);
		m_text.setString(number.str().c_str());
		m_text.setPosition((float)(m_Output.thing->GetInventorySprite()->GetRect().left + 70), (float)(m_Output.thing->GetInventorySprite()->GetRect().top + 70));
		g_pFramework->GetWindow()->draw(m_text);
	}


	//render the button
	if (m_pCookingButton->Render(g_pFramework->keyStates.leftMouseUp))
		m_cooking = true;

}





void CCauldron::CheckThings()
{
	bool matches[4] = { false, false, false, false };
	bool can_cook = false;
	bool got_ingredient = false;

	if (m_cooking)
	{
		if (m_Ingredience[0].amount > 0 || m_Ingredience[1].amount > 0 || m_Ingredience[2].amount > 0 || m_Ingredience[3].amount > 0)
		{
			//loop through every recipe
			for (int s = 0; s < NUMBER_OF_CONRECIPES; s++)
			{
				can_cook = true;
				matches[0] = false;
				matches[1] = false;
				matches[2] = false;
				matches[3] = false;
				//loop through the ingredients of this recipe
				for (int i = 0; i < 4; i++)
				{
					got_ingredient = false;
					//loop through the given ingredients
					for (int a = 0; a < 4; a++)
					{
						if (m_Ingredience[a].amount > 0 && matches[a] == false)
						{
							//if the ingredience matches: set it
							if (m_Ingredience[a].thing->getID() == CONRECIPES[s][i])
							{
								matches[a] = true;
								got_ingredient = true;
								a = 4;
							}
						}
						//if theres no ingredience needed
						else if (m_Ingredience[a].amount <= 0 && matches[a] == false && CONRECIPES[s][i] == -1)
						{
							matches[a] = true;
							got_ingredient = true;
							a = 4;
						}
					}

					
					if (!got_ingredient)
						can_cook = false;
				}


				//if all ingrediences match: cook it
				if (can_cook)
				{
					if (m_Output.amount <= 0)
					{
						//cook food		
						CConsumable* consumable = new CConsumable;
						consumable->InitConsumable(CONRECIPES[s][4]);
						consumable->GetInventorySprite()->SetPos(m_pPanel->GetRect().left + 200, m_pPanel->GetRect().top + 360);

						m_Output.thing = consumable;
						m_Output.amount = 1;

						for (int b = 0; b < 4; b++)
						{
							SAFE_DELETE(m_Ingredience[b].thing);
							m_Ingredience[b].amount = 0;
						}

						m_cooking = false;
						return;
					}
					else if (m_Output.thing->getID() == CONRECIPES[s][4])
					{
						m_Output.amount++;

						for (int b = 0; b < 4; b++)
						{
							SAFE_DELETE(m_Ingredience[b].thing);
							m_Ingredience[b].amount = 0;
						}

						m_cooking = false;
						return;
					}
				}
			}
		}

		m_cooking = false;
	}
}






vector<SItem> CCauldron::GetContent()
{
	vector<SItem> items;
	items.clear();

	if (m_Output.amount > 0)
		items.push_back(m_Output);

	for (int i = 0; i < 4; i++)
	{
		if (m_Ingredience[i].amount > 0)
			items.push_back(m_Ingredience[i]);
	}

	return items;
}