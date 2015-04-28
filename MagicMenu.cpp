#include "MagicMenu.hpp"



CMagicMenu::CMagicMenu()
{
	m_pMagicMenu = NULL;
	m_pInventory = NULL;
	m_pPlus = NULL;
}


CMagicMenu::~CMagicMenu()
{
	m_pInventory = NULL;

	SAFE_DELETE(m_pMagicMenu);
	SAFE_DELETE(m_pPlus);

	for (int i = 0; i < AMOUNTOFSPELLS; i++)
		SAFE_DELETE(m_Spells[i].m_Sprite);
}



void CMagicMenu::Init(CInventory *_inventory, bool _loaded)
{
	m_pInventory = _inventory;

	m_pMagicMenu = new CSprite;
	m_pMagicMenu->Load(&g_pTextures->t_magicMenu);
	m_pMagicMenu->SetPos((int)(g_pFramework->GetWindow()->getSize().x / 2 - m_pMagicMenu->GetRect().width / 2), (int)(g_pFramework->GetWindow()->getSize().y / 2 - m_pMagicMenu->GetRect().height / 2));

	m_pPlus = new CButton;
	m_pPlus->Load(&g_pTextures->t_buttonPlus, 0, 0, 1);

	//init the spells
	for (int i = 0; i < AMOUNTOFSPELLS; i++)
	{
		m_Spells[i].m_Sprite = new CSprite;
		m_Spells[i].m_Sprite->Load(&g_pTextures->t_spell[i], 2, 97, 97);

		if (!_loaded)
			m_SpellLevel[i] = 0;
	}

	//set position of the spells
	m_Spells[FIREBALL].m_Sprite->SetPos(m_pMagicMenu->GetRect().left + 41, m_pMagicMenu->GetRect().top + 91);

	m_text.setFont(g_pTextures->f_coolsville);
	m_text.setCharacterSize(25);
	m_text.setColor(Color::Black);
	m_text.setPosition(m_pMagicMenu->GetRect().left + 565, m_pMagicMenu->GetRect().top + 12);

	m_levelText.setFont(g_pTextures->f_coolsville);
	m_levelText.setCharacterSize(18);
	m_levelText.setColor(Color::Black);

	m_MagicPoints = 2;

	is_open = false;
}




void CMagicMenu::Render()
{
	//if m was pressed: Open or close the menu
	if (g_pFramework->keyStates.mUp)
	{
		if (is_open)
			is_open = false;
		else
			is_open = true;
	}



	if (is_open)
	{
		m_pMagicMenu->Render(g_pFramework->GetWindow());

		//render the magic points
		stringstream str("");
		str << m_MagicPoints;
		m_text.setString(str.str());
		g_pFramework->GetWindow()->draw(m_text);

		//render the spells
		for (int i = 0; i < AMOUNTOFSPELLS; i++)
		{
			//if the spell was clicked
			if (m_Spells[i].m_Sprite->GetRect().contains(Mouse::getPosition()) && g_pFramework->keyStates.leftMouseUp)
			{
				//level the spell if enough magic points and spell hasn't reached the highest level yet
				if (m_MagicPoints > 0 && m_SpellLevel[i] < 10)
				{
					m_MagicPoints--;
					m_SpellLevel[i]++;
				}
			} 
			//if spell was rightclicked: add it to the inventory
			else if (m_Spells[i].m_Sprite->GetRect().contains(Mouse::getPosition()) && g_pFramework->keyStates.rightMouseUp)
			{
				if (m_SpellLevel[i] > 0)
				{
					CItem* spell = new CItem;
					spell->SetSpecialID(i);
					spell->Init(SPELL);
					m_pInventory->Take(spell);
				}
			}


			if (m_SpellLevel[i] > 0)
				m_Spells[i].m_Sprite->Render(g_pFramework->GetWindow(), 0.0f);
			else
				m_Spells[i].m_Sprite->Render(g_pFramework->GetWindow(), 1.0f);

			str.str("");
			str << m_SpellLevel[i] << "/10";
			m_levelText.setString(str.str());
			m_levelText.setPosition(m_Spells[i].m_Sprite->GetRect().left + 10, m_Spells[i].m_Sprite->GetRect().top + 100);
			g_pFramework->GetWindow()->draw(m_levelText);
		}
	}
}




void CMagicMenu::CastSpell(int _ID)
{
	switch (_ID)
	{
		case(FIREBALL) :
		{
			m_pInventory->SetOpen(true);
		}
	}
}