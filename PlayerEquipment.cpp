#include "PlayerEquipment.hpp"
#include "Player.hpp"



CPlayerEquipment::CPlayerEquipment()
{
	m_helmet.amount = 0;
	m_helmet.thing = NULL;
	m_body.amount = 0;
	m_body.thing = NULL;
	m_trousers.amount = 0;
	m_trousers.thing = NULL;
	m_ring1.amount = 0;
	m_ring1.thing = NULL;
	m_ring2.amount = 0;
	m_ring2.thing = NULL;

	m_pPlayer = NULL;
}



CPlayerEquipment::~CPlayerEquipment()
{
	if(m_helmet.amount > 0)
		SAFE_DELETE(m_helmet.thing);
	if(m_body.amount > 0)	
		SAFE_DELETE(m_body.thing);
	if(m_trousers.amount > 0)
		SAFE_DELETE(m_trousers.thing);
	if(m_ring1.amount > 0)
		SAFE_DELETE(m_ring1.thing);
	if(m_ring2.amount > 0)
		SAFE_DELETE(m_ring2.thing);
}




void CPlayerEquipment::InitPlayerEquipment(int _Number, CPlayer *_player)
{
	m_pPanel = new CSprite;
	m_pPanel->Load(&g_pTextures->t_equipmentWindow);

	m_pPlayer = _player;

	m_Number = _Number;

	//loads everything for the tooltips
	m_tooltipFont.loadFromFile("Data/Fonts/coolsville.ttf");
	m_tooltipText.setFont(m_tooltipFont);
	m_tooltipText.setString("");
	m_tooltipText.setCharacterSize(15);
	m_tooltipText.setColor(Color::Yellow);
	m_showTooltip = false;
}


void CPlayerEquipment::SetPos(int _x, int _y)
{
	m_pPanel->SetPos(_x, _y);
}


//places a new item and returns the old one
SItem CPlayerEquipment::Take(SItem _item)
{
	SItem temp = _item;

	//if there was no item given
	if(_item.amount == 0)
	{
		//if the mouse is inside the helmet place: delete the thing
		if(IntRect(m_pPanel->GetRect().left + 200, m_pPanel->GetRect().top + 20, 97, 97).contains(Mouse::getPosition()) && Mouse::isButtonPressed(Mouse::Left))
		{
			temp = m_helmet;
			temp.position = -1;
			m_helmet.amount = 0;
		} 
		//if the mouse is inside the body place: delete the thing
		else if(IntRect(m_pPanel->GetRect().left + 200, m_pPanel->GetRect().top + 193, 97, 97).contains(Mouse::getPosition()) && Mouse::isButtonPressed(Mouse::Left))
		{			
			temp = m_body;
			temp.position = -1;
			m_body.amount = 0;			

			m_pPlayer->LoadNewBody(&g_pTextures->t_dwarf_body, 53, 60, 2);
		}
			//if the mouse is inside the legs place: delete the thing
		else if(IntRect(m_pPanel->GetRect().left + 200, m_pPanel->GetRect().top + 353, 97, 97).contains(Mouse::getPosition()) && Mouse::isButtonPressed(Mouse::Left))
		{
			temp = m_trousers;
			temp.position = -1;
			m_trousers.amount = 0;	

			m_pPlayer->LoadNewLegs(&g_pTextures->t_dwarf_legs, 55, 50, 14);
		}
		//if the mouse is inside the ring1 place: delete the thing
		else if(IntRect(m_pPanel->GetRect().left + 50, m_pPanel->GetRect().top + 263, 97, 97).contains(Mouse::getPosition()) && Mouse::isButtonPressed(Mouse::Left))
		{
			temp = m_ring1;
			temp.position = -1;
			m_ring1.amount = 0;
		}
		//if the mouse is inside the ring2 place: delete it
		else if(IntRect(m_pPanel->GetRect().left + 360, m_pPanel->GetRect().top + 263, 97, 97).contains(Mouse::getPosition()) && Mouse::isButtonPressed(Mouse::Left))
		{
			temp = m_ring2;
			temp.position = -1;
			m_ring2.amount = 0;
		}
	}
	//if there was an item given
	else
	{
		//check if the thing to place is equipment
		if(_item.thing->getID() > TEBREAK)
		{
			CEquipment * equipment = (CEquipment*)_item.thing;

			//if the mouse is inside the helmet place: place the thing
			if(IntRect(m_pPanel->GetRect().left + 200, m_pPanel->GetRect().top + 20, 97, 97).contains(Mouse::getPosition()) && Mouse::isButtonPressed(Mouse::Left))
			{
				//check if this thing is for the head
				if(equipment->GetEquipID() ==  HEAD)
				{
					temp = m_helmet;
					temp.position = -1;
					m_helmet = _item;
					m_helmet.thing->GetInventorySprite()->SetPos(m_pPanel->GetRect().left + 200, m_pPanel->GetRect().top + 23);
				}
			}
			//if the mouse is inside the body place: place the thing
			else if(IntRect(m_pPanel->GetRect().left + 200, m_pPanel->GetRect().top + 193, 97, 97).contains(Mouse::getPosition()) && Mouse::isButtonPressed(Mouse::Left))
			{
				if(equipment->GetEquipID() == BODY)
				{
					temp = m_body;
					temp.position = -1;
					m_body = _item;
					m_body.thing->GetInventorySprite()->SetPos(m_pPanel->GetRect().left + 200, m_pPanel->GetRect().top + 193);

					m_pPlayer->LoadNewBody(equipment->GetEquipmentSprite());
				}
			}
			//if the mouse is inside the legs place: place the thing
			else if(IntRect(m_pPanel->GetRect().left + 200, m_pPanel->GetRect().top + 353, 97, 97).contains(Mouse::getPosition()) && Mouse::isButtonPressed(Mouse::Left))
			{
				if(equipment->GetEquipID() == LEGS)
				{
					temp = m_trousers;
					temp.position = -1;
					m_trousers = _item;
					m_trousers.thing->GetInventorySprite()->SetPos(m_pPanel->GetRect().left + 200, m_pPanel->GetRect().top + 353);

					m_pPlayer->LoadNewLegs(equipment->GetEquipmentSprite());
				}
			}
			//if the mouse is inside the ring1 place: place the thing
			else if(IntRect(m_pPanel->GetRect().left + 50, m_pPanel->GetRect().top + 263, 97, 97).contains(Mouse::getPosition()) && Mouse::isButtonPressed(Mouse::Left))
			{
				if(equipment->GetEquipID() == HAND)
				{
					temp = m_ring1;
					temp.position = -1;
					m_ring1 = _item;
					m_ring1.thing->GetInventorySprite()->SetPos(m_pPanel->GetRect().left + 50, m_pPanel->GetRect().top + 263);
				}
			}
			//if the mouse is inside the ring2 place: place it
			else if(IntRect(m_pPanel->GetRect().left + 360, m_pPanel->GetRect().top + 263, 97, 97).contains(Mouse::getPosition()) && Mouse::isButtonPressed(Mouse::Left))
			{
				if(equipment->GetEquipID() == HAND)
				{
					temp = m_ring2;
					temp.position = -1;
					m_ring2 = _item;
					m_ring2.thing->GetInventorySprite()->SetPos(m_pPanel->GetRect().left + 360, m_pPanel->GetRect().top + 263);
				}
			}
		}
	}
	

	//returns the deleted item
	return temp;
}



//renders the equipment window
void CPlayerEquipment::Render()
{
	m_pPanel->Render(g_pFramework->GetWindow());

	if(m_helmet.amount != 0)
	{
		m_helmet.thing->RenderInventorySprite();

		if(m_helmet.thing->GetInventorySprite()->GetRect().contains(Mouse::getPosition()) && !Mouse::isButtonPressed(Mouse::Left))
			SetTooltip(m_helmet.thing);
	}

	if(m_body.amount != 0)
	{
		m_body.thing->RenderInventorySprite();

		if(m_body.thing->GetInventorySprite()->GetRect().contains(Mouse::getPosition()) && !Mouse::isButtonPressed(Mouse::Left))
			SetTooltip(m_body.thing);
	}

	if(m_trousers.amount != 0)
	{
		m_trousers.thing->RenderInventorySprite();

		if(m_trousers.thing->GetInventorySprite()->GetRect().contains(Mouse::getPosition()) && !Mouse::isButtonPressed(Mouse::Left))
			SetTooltip(m_trousers.thing);
	}

	if(m_ring1.amount != 0)
	{
		m_ring1.thing->RenderInventorySprite();

		if(m_ring1.thing->GetInventorySprite()->GetRect().contains(Mouse::getPosition()) && !Mouse::isButtonPressed(Mouse::Left))
			SetTooltip(m_ring1.thing);
	}
	
	if(m_ring2.amount != 0)
	{
		m_ring2.thing->RenderInventorySprite();

		if(m_ring2.thing->GetInventorySprite()->GetRect().contains(Mouse::getPosition()) && !Mouse::isButtonPressed(Mouse::Left))
			SetTooltip(m_ring2.thing);
	}

	//render the tooltip
	if(m_showTooltip)
	{
		g_pFramework->GetWindow()->draw(m_tooltipBackground, m_tooltipText.getTransform());
		g_pFramework->GetWindow()->draw(m_tooltipText);	
		m_showTooltip = false;
	}
}




void CPlayerEquipment::CheckThings()
{

}




int CPlayerEquipment::GetHelmetID()
{
	if(m_helmet.amount != 0)
		return m_helmet.thing->getID();
	else 
		return -1;
}



const SToolAttributes operator+(SToolAttributes const &lhs, SToolAttributes const &rhs)	
{
	SToolAttributes temp(lhs);

	temp.armour += rhs.armour;
	temp.breaking_speed += rhs.breaking_speed;
	temp.luck += rhs.luck;
	temp.maxHealth += rhs.maxHealth;
	temp.healthRegeneration += rhs.healthRegeneration;
	temp.maxMana += rhs.maxMana;
	temp.manaRegeneration += rhs.manaRegeneration;
	temp.speed += rhs.speed;
	temp.strength += rhs.strength;
	temp.criticalChance += rhs.criticalChance;
	temp.criticalDamage += rhs.criticalDamage;

	return temp;
}


//returns the sum of all attributes of the equipment
SToolAttributes CPlayerEquipment::GetAttributes()
{
	SToolAttributes attributes;
	CEquipment* equipment;

	attributes.armour = 0;
	attributes.breaking_speed = 0.0f;
	attributes.luck = 0;
	attributes.maxHealth = 0;
	attributes.healthRegeneration = 0;
	attributes.maxMana = 0;
	attributes.manaRegeneration = 0;
	attributes.speed = 0;
	attributes.strength = 0;
	attributes.criticalChance = 0;
	attributes.criticalDamage = 0;

	equipment = (CEquipment*)(m_helmet.thing);
	if(equipment != NULL && m_helmet.amount > 0)
		attributes = equipment->GetAttributes();

	equipment = (CEquipment*)(m_body.thing);
	if(equipment != NULL && m_body.amount > 0)
		attributes = attributes + equipment->GetAttributes();

	equipment = (CEquipment*)(m_trousers.thing);
	if(equipment != NULL && m_trousers.amount > 0)
		attributes = attributes + equipment->GetAttributes();

	equipment = (CEquipment*)(m_ring1.thing);
	if(equipment != NULL && m_ring1.amount > 0)
		attributes = attributes + equipment->GetAttributes();

	equipment = (CEquipment*)(m_ring2.thing);
	if(equipment != NULL && m_ring2.amount > 0)
		attributes = attributes + equipment->GetAttributes();

	equipment = NULL;

	return attributes;
}




void CPlayerEquipment::RenderEquipment(int _x, int _y, bool _left)
{
	CEquipment *equipment;

	//renders the helmet
	equipment = (CEquipment*)(m_helmet.thing);
	if(equipment != NULL && m_helmet.amount > 0)
	{
		if(_left)
		{
			switch(equipment->getID())
			{
			case IRONHELMET:
				equipment->RenderEquipment(_x + 21, _y - 12, 0.0f);
				break;

			case MAGICHAT:
				equipment->RenderEquipment(_x + 20, _y - 22, 0.0f);
				break;

			case CANDLE:
				equipment->RenderEquipment(_x + 30, _y - 20, 0.0f);
				break;
			}
		}
		else
		{
			switch(equipment->getID())
			{
			case IRONHELMET:
				equipment->RenderEquipment(_x - 1, _y - 12, 1.0f);
				break;

			case MAGICHAT:
				equipment->RenderEquipment(_x -11, _y - 22, 1.0f);
				break;

			case CANDLE:
				equipment->RenderEquipment(_x + 12, _y - 20, 1.0f);
				break;
			}
		
		}
	}


	equipment = NULL;
}





vector<SItem> CPlayerEquipment::GetContent()
{
	vector<SItem> items;

	return items;
}



void CPlayerEquipment::SetTooltip(CThing *_thing)
{
	m_stream.str("");
	m_stream << (_thing->GetName());

	int rarity = 1;

	CEquipment *equipment = (CEquipment*)_thing;
	rarity = equipment->GetRarity();

	//show the additional attributes
	if(equipment->GetAttributes().armour != 0)
		m_stream << "\nRüstung: " << equipment->GetAttributes().armour;
	if(equipment->GetAttributes().breaking_speed != 0)
		m_stream << "\nAbbaugeschwindigkeit: " << equipment->GetAttributes().breaking_speed;
	if(equipment->GetAttributes().luck != 0)
		m_stream << "\nGlück: " << equipment->GetAttributes().luck;
	if(equipment->GetAttributes().maxHealth != 0)
		m_stream << "\nLeben " << equipment->GetAttributes().maxHealth;
	if (equipment->GetAttributes().healthRegeneration != 0)
		m_stream << "\nLebensregeneration " << equipment->GetAttributes().healthRegeneration;
	if(equipment->GetAttributes().maxMana != 0)
		m_stream << "\nMana " << equipment->GetAttributes().maxMana;
	if (equipment->GetAttributes().manaRegeneration != 0)
		m_stream << "\nManaregeneration " << equipment->GetAttributes().manaRegeneration;
	if(equipment->GetAttributes().speed != 0)
		m_stream << "\nGeschwindigkeit " << equipment->GetAttributes().speed;
	if(equipment->GetAttributes().strength != 0)
		m_stream << "\nStärke " << equipment->GetAttributes().strength;
	if (equipment->GetAttributes().criticalChance != 0)
		m_stream << "\nKritische Chance " << equipment->GetAttributes().criticalChance;
	if (equipment->GetAttributes().criticalDamage != 0)
		m_stream << "\nKritischer Schaden " << equipment->GetAttributes().criticalDamage;

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

	m_tooltipText.setString(m_stream.str().c_str());
	m_tooltipText.setPosition((float)(Mouse::getPosition().x + 13), (float)(Mouse::getPosition().y));

	FloatRect backgroundRect = m_tooltipText.getLocalBounds();
	m_tooltipBackground = RectangleShape(Vector2f(backgroundRect.width, backgroundRect.height + 5));
	m_tooltipBackground.setFillColor(Color::Black);

	m_showTooltip = true;
}