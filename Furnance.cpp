#include "Furnance.hpp"



CFurnance::CFurnance(int _x, int _y)
{
	m_BurningMaterial.amount = 0;
	m_BurningMaterial.is_clicked = false;
	m_BurningMaterial.position = -1;
	m_BurningMaterial.thing = NULL;
	m_ThingToBurn.amount = 0;
	m_ThingToBurn.is_clicked = false;
	m_ThingToBurn.position = -1;
	m_ThingToBurn.thing = NULL;
	m_Product.amount = 0;
	m_Product.is_clicked = false;
	m_Product.position = -1;
	m_Product.thing = NULL;

	m_FurnanceX = _x;
	m_FurnanceY = _y;
};


CFurnance::~CFurnance()
{
}


void CFurnance::Quit()
{
	if (m_BurningMaterial.amount > 0)
		SAFE_DELETE(m_BurningMaterial.thing);

	if (m_Product.amount > 0)
		SAFE_DELETE(m_Product.thing);

	if (m_ThingToBurn.amount > 0)
		SAFE_DELETE(m_ThingToBurn.thing);
}

void CFurnance::Init(int _Number, bool _loaded)
{
	m_pPanel = new CSprite;
	m_pPanel->Load(&g_pTextures->t_furnanceMenu);
	m_pPanel->SetPos((int)g_pFramework->GetRenderWindow()->getSize().x/2, (int)g_pFramework->GetRenderWindow()->getSize().y/2 - m_pPanel->GetRect().height/2);

	m_font.loadFromFile("Data/Fonts/ltromatic.ttf");
	m_text.setFont(m_font);
	m_text.setString("");
	m_text.setCharacterSize(20);
	m_text.setColor(Color::Yellow);

	m_Smoke.Load(&g_pTextures->t_smoke, 5, 65, 100);
	m_Smoke.SetPos(m_FurnanceX + 19, m_FurnanceY - 90);

	if(!_loaded)
	{
		m_fBurningTime = 0.0f;
		m_fAnimState = 0.0f;
		m_Number = _Number;
		m_PanelType = PANEL_FURNANCE;
	}
}


SItem CFurnance::Take(SItem _item)
{
	SItem temp = _item;

	//if the mouse is inside the "Thing to burn" place: place it
	if(IntRect(m_pPanel->GetRect().left + 15, m_pPanel->GetRect().top + 50, 97, 97).contains(Mouse::getPosition()) && Mouse::isButtonPressed(Mouse::Left))
	{
		temp = m_ThingToBurn;
		temp.position = -1;
		if(_item.amount != 0)
		{	
			m_ThingToBurn = _item;
			m_ThingToBurn.thing->GetInventorySprite()->SetPos(m_pPanel->GetRect().left + 15, m_pPanel->GetRect().top + 50);		
			m_fBurningTime = 0.0f;
		}
		else		
			m_ThingToBurn.amount = 0;		
		
		
	}
	//if the mouse is inside the "Burning Material" place: place it 
	else if(IntRect(m_pPanel->GetRect().left + 15, m_pPanel->GetRect().top + 340, 97, 97).contains(Mouse::getPosition()) && Mouse::isButtonPressed(Mouse::Left))
	{
		temp = m_BurningMaterial;
		temp.position = -1;
		if(_item.amount != 0)
		{
			m_BurningMaterial = _item;
			m_BurningMaterial.thing->GetInventorySprite()->SetPos(m_pPanel->GetRect().left + 15, m_pPanel->GetRect().top + 340);
			m_fBurningTime = 0.0f;
		}
		else
			m_BurningMaterial.amount = 0;
	}
	//if the mouse is inside the "Product" place: place it 
	else if(IntRect(m_pPanel->GetRect().left + 135, m_pPanel->GetRect().top + 200, 97, 97).contains(Mouse::getPosition()) && Mouse::isButtonPressed(Mouse::Left))
	{
		temp = m_Product;
		temp.position = -1;
		if(_item.amount != 0)
		{
			m_Product = _item;
			m_Product.thing->GetInventorySprite()->SetPos(m_pPanel->GetRect().left + 135, m_pPanel->GetRect().top + 200);
		}
		else
			m_Product.amount = 0;
	}

	//returns the deletet item
		return temp;
}




void CFurnance::Render()
{
	stringstream number;

	//render the window and the things
		m_pPanel->Render(g_pFramework->GetRenderWindow());

		//render the thing to burn inside the window
		if(m_ThingToBurn.amount != 0)
		{
			m_ThingToBurn.thing->RenderInventorySprite();

			//show the amount
			number.str("");
			number << (m_ThingToBurn.amount);
			m_text.setString(number.str().c_str());
			m_text.setPosition((float)(m_ThingToBurn.thing->GetInventorySprite()->GetRect().left + 70), (float)(m_ThingToBurn.thing->GetInventorySprite()->GetRect().top + 70));
			g_pFramework->GetRenderWindow()->draw(m_text);		
		}

		//render the burning material inside the window
		if(m_BurningMaterial.amount != 0)
		{
			m_BurningMaterial.thing->RenderInventorySprite();

			//show amount
			number.str("");
			number << (m_BurningMaterial.amount);
			m_text.setString(number.str().c_str());
			m_text.setPosition((float)(m_BurningMaterial.thing->GetInventorySprite()->GetRect().left + 70), (float)(m_BurningMaterial.thing->GetInventorySprite()->GetRect().top + 70));
			g_pFramework->GetRenderWindow()->draw(m_text);	
		}

		//render the burning material inside the window
		if(m_Product.amount != 0)
		{
			m_Product.thing->RenderInventorySprite();

			//show amount
			number.str("");
			number << (m_Product.amount);
			m_text.setString(number.str().c_str());
			m_text.setPosition((float)(m_Product.thing->GetInventorySprite()->GetRect().left + 70), (float)(m_Product.thing->GetInventorySprite()->GetRect().top + 70));
			g_pFramework->GetRenderWindow()->draw(m_text);	
		}
}





void CFurnance::CheckThings()
{
	
		//"burn" the things
		if(m_ThingToBurn.amount != 0 && m_BurningMaterial.amount != 0)
		{
			//add the elapsed time
			m_fBurningTime += g_pTimer->GetElapsedTime().asSeconds();
			m_fAnimState += g_pTimer->GetElapsedTime().asSeconds() *5;

			if(m_fAnimState >= 5.0f)
				m_fAnimState = 0.0f;


			//if the burning time is at maximum: change the things in the furnance
			switch(m_BurningMaterial.thing->getID())
			{
			case(COAL):
				{
					m_Smoke.Render(g_pFramework->GetRenderWindow(), m_fAnimState);

					if(m_fBurningTime >= 3.0f)
						ChangeBurningThings();				
				}break;
			case(WOOD):
				{
					m_Smoke.Render(g_pFramework->GetRenderWindow(), m_fAnimState);

					if(m_fBurningTime >= 5.0f)
						ChangeBurningThings();
				}break;
			case(WOODSTAFF):
			{
				m_Smoke.Render(g_pFramework->GetRenderWindow(), m_fAnimState);

				if(m_fBurningTime >= 10.0f)
					ChangeBurningThings();
			}break;
			case(RECIPE):
				{
					m_Smoke.Render(g_pFramework->GetRenderWindow(), m_fAnimState);

					if(m_fBurningTime >= 2.0f)
						ChangeBurningThings();
				}break;
			}
		}
}




//resets the timer, deletes the burning material and changes the thing to burn
void CFurnance::ChangeBurningThings()
{
	m_fBurningTime = 0.0f;

	switch(m_ThingToBurn.thing->getID())
	{
	case(IRONORE):
		{
			//if there is no Product: create a new Item 
			if(m_Product.amount <= 0)
			{
				m_Product.thing = new CItem();
				((CItem*)m_Product.thing)->Init(IRON);
				m_Product.thing->GetInventorySprite()->SetPos(m_pPanel->GetRect().left + 135, m_pPanel->GetRect().top + 200);
				m_Product.amount = 1;

				m_ThingToBurn.amount --;
			}
			//if there already is the right product: add one
			else if(m_Product.thing->getID() == IRON)
			{
				m_Product.amount ++;
				m_ThingToBurn.amount --;
			}

			//substract one burning material
			m_BurningMaterial.amount --;
				
		}break;
	case(GOLDORE):
		{
			//if there is no Product: create a new Item 
			if(m_Product.amount <= 0)
			{
				m_Product.thing = new CItem();
				((CItem*)m_Product.thing)->Init(GOLD);
				m_Product.thing->GetInventorySprite()->SetPos(m_pPanel->GetRect().left + 135, m_pPanel->GetRect().top + 200);
				m_Product.amount = 1;

				m_ThingToBurn.amount --;
			}
			//if there already is the right product: add one
			else if(m_Product.thing->getID() == GOLD)
			{
				m_Product.amount ++;
				m_ThingToBurn.amount --;
			}

			//substract one burning material
			m_BurningMaterial.amount --;
				
		}break;
	}

	//if the burning material is empty: delete it
	if(m_BurningMaterial.amount <= 0)
		SAFE_DELETE(m_BurningMaterial.thing);

	//if the thing to burn is empty: delete it
	if(m_ThingToBurn.amount == 0)
		SAFE_DELETE(m_ThingToBurn.thing);
}




vector<SItem> CFurnance::GetContent()
{
	vector<SItem> items;
	items.clear();

	if(m_BurningMaterial.amount > 0)
		items.push_back(m_BurningMaterial);

	if(m_Product.amount > 0)
		items.push_back(m_Product);

	if(m_ThingToBurn.amount > 0)
		items.push_back(m_ThingToBurn);

	return items;
}