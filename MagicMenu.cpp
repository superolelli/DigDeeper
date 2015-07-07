#include "MagicMenu.hpp"
#include "Projectiles.hpp"


CMagicMenu::CMagicMenu()
{
	m_pMagicMenu = NULL;
	m_pInventory = NULL;
}


CMagicMenu::~CMagicMenu()
{
	m_pInventory = NULL;

	SAFE_DELETE(m_pMagicMenu);

	for (int i = 0; i < AMOUNTOFSPELLS; i++)
		SAFE_DELETE(m_Spells[i].m_Sprite);
}



void CMagicMenu::Init(CInventory *_inventory, CPlayer *_player, bool _loaded)
{
	m_pInventory = _inventory;
	m_pPlayer = _player;

	m_pMagicMenu = new CSprite;
	m_pMagicMenu->Load(&g_pTextures->t_magicMenu);
	m_pMagicMenu->SetPos((int)(g_pFramework->GetRenderWindow()->getSize().x / 2 - m_pMagicMenu->GetRect().width / 2), (int)(g_pFramework->GetRenderWindow()->getSize().y / 2 - m_pMagicMenu->GetRect().height / 2));

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
	m_Spells[ICE].m_Sprite->SetPos(m_pMagicMenu->GetRect().left + 186, m_pMagicMenu->GetRect().top + 91);
	m_Spells[HEAL].m_Sprite->SetPos(m_pMagicMenu->GetRect().left + 374, m_pMagicMenu->GetRect().top + 91);
	m_Spells[ALCHEMY].m_Sprite->SetPos(m_pMagicMenu->GetRect().left + 707, m_pMagicMenu->GetRect().top + 91);
	m_Spells[LIGHT].m_Sprite->SetPos(m_pMagicMenu->GetRect().left + 852, m_pMagicMenu->GetRect().top + 91);

	m_text.setFont(g_pTextures->f_coolsville);
	m_text.setCharacterSize(25);
	m_text.setColor(Color::Black);
	m_text.setPosition(m_pMagicMenu->GetRect().left + 565, m_pMagicMenu->GetRect().top + 12);

	m_levelText.setFont(g_pTextures->f_coolsville);
	m_levelText.setCharacterSize(18);
	m_levelText.setColor(Color::Black);

	if (!_loaded)
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
		m_pMagicMenu->Render(g_pFramework->GetRenderWindow());

		//render the magic points
		stringstream str("");
		str << m_MagicPoints;
		m_text.setString(str.str());
		g_pFramework->GetRenderWindow()->draw(m_text);

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
					spell->Init(SPELL);
					spell->SetSpecialIDSpell(i);
					m_pInventory->Take(spell);
				}
			}


			if (m_SpellLevel[i] > 0)
				m_Spells[i].m_Sprite->Render(g_pFramework->GetRenderWindow(), 0.0f);
			else
				m_Spells[i].m_Sprite->Render(g_pFramework->GetRenderWindow(), 1.0f);

			str.str("");
			str << m_SpellLevel[i] << "/10";
			m_levelText.setString(str.str());
			m_levelText.setPosition(m_Spells[i].m_Sprite->GetRect().left + 10, m_Spells[i].m_Sprite->GetRect().top + 100);
			g_pFramework->GetRenderWindow()->draw(m_levelText);
		}
	}
}




void CMagicMenu::CastSpell(int _ID)
{
	switch (_ID)
	{
		case(FIREBALL) :
		{
			if (m_pPlayer->GetMana() >= m_SpellLevel[FIREBALL] * 5)
			{
				SProjectile projectile;

				//add a projectile
				CSprite *sprite = new CSprite;

				if (m_pPlayer->IsLeft())
				{
					projectile.m_fXVel = -200;
					sprite->Load(&g_pTextures->t_fireballLeft);
				}
				else
				{
					projectile.m_fXVel = 200;
					sprite->Load(&g_pTextures->t_fireballRight);
				}
				
				sprite->SetPos(m_pPlayer->GetWeaponRect().left - sprite->GetRect().left / 2, m_pPlayer->GetWeaponRect().top - sprite->GetRect().top / 2);
	
				projectile.m_ID = FIREBALLPROJECTILE;
				projectile.m_Damage = m_SpellLevel[FIREBALL] * 3;
				projectile.m_fFlown = 0.0f;
				projectile.m_flightLength = 400;
				projectile.m_fromPlayer = true;
				projectile.m_fYVel = 0.0f;
				projectile.m_Sprite = sprite;
				projectile.m_fAnimState = -1;

				g_pProjectiles->NewProjectile(projectile);

				//substract mana
				m_pPlayer->SubstractMana(m_SpellLevel[FIREBALL] * 5);
			}
		}break;

		case(ICE) :
		{
			if (m_pPlayer->GetMana() >= m_SpellLevel[ICE] * 5)
			{
				SProjectile projectile;

				//add a projectile
				CSprite *sprite = new CSprite;

				if (m_pPlayer->IsLeft())
				{
					projectile.m_fXVel = -200;
					sprite->Load(&g_pTextures->t_iceballLeft);
				}
				else
				{
					projectile.m_fXVel = 200;
					sprite->Load(&g_pTextures->t_iceballRight);
				}

				sprite->SetPos(m_pPlayer->GetWeaponRect().left - sprite->GetRect().left / 2, m_pPlayer->GetWeaponRect().top - sprite->GetRect().top / 2);

				projectile.m_ID = ICEBALLPROJECTILE;
				projectile.m_Damage = m_SpellLevel[ICE] * 1;
				projectile.m_fFlown = 0.0f;
				projectile.m_flightLength = 400;
				projectile.m_fromPlayer = true;
				projectile.m_fYVel = 0.0f;
				projectile.m_Sprite = sprite;
				projectile.m_fAnimState = -1;

				g_pProjectiles->NewProjectile(projectile);

				//substract mana
				m_pPlayer->SubstractMana(m_SpellLevel[ICE] * 5);
			}
		}break;

		case(HEAL) :
		{
			if (m_pPlayer->GetMana() >= m_SpellLevel[HEAL] * 10)
			{
				m_pPlayer->Heal(m_SpellLevel[HEAL] * 10);


				SProjectile projectile;

				//add a projectile
				CSprite *sprite = new CSprite;

				sprite->Load(&g_pTextures->t_healing, 5, 100, 100);
				sprite->SetPos(m_pPlayer->GetRect().left - 30, m_pPlayer->GetRect().top);

				projectile.m_ID = HEALING;
				projectile.m_Damage = 0;
				projectile.m_fFlown = 0.0f;
				projectile.m_flightLength = 0;
				projectile.m_fromPlayer = true;
				projectile.m_fYVel = 0.0f;
				projectile.m_Sprite = sprite;
				projectile.m_fAnimState = 0;
				g_pProjectiles->NewProjectile(projectile);

				//substract mana
				m_pPlayer->SubstractMana(m_SpellLevel[HEAL] * 10);
			}
		}break;

		case(ALCHEMY) :
		{
			if (m_pPlayer->GetMana() >= m_SpellLevel[ALCHEMY] * 5)
			{
				m_pPlayer->DoAlchemy(m_SpellLevel[ALCHEMY]);

				//substract mana
				m_pPlayer->SubstractMana(m_SpellLevel[ALCHEMY] * 5);
			}

		}break;

		case(LIGHT) :
		{
			SProjectile projectile;

			//add a projectile
			CSprite *sprite = new CSprite;

			sprite->Load(&g_pTextures->t_lightsphere);
			
			sprite->SetPos(m_pPlayer->GetWeaponRect().left - sprite->GetRect().left / 2, m_pPlayer->GetRect().top);

			projectile.m_ID = LIGHTSPHERE;
			projectile.m_Damage = 0;
			projectile.m_fFlown = 5.0f * m_SpellLevel[LIGHT];            //stands for duration
			projectile.m_flightLength = 50 * m_SpellLevel[LIGHT];          //stands for radius
			projectile.m_fromPlayer = true;
			projectile.m_fXVel = 0;
			projectile.m_fYVel = 0.0f;
			projectile.m_Sprite = sprite;
			projectile.m_fAnimState = -1;

			g_pProjectiles->NewProjectile(projectile);

			//substract mana
			m_pPlayer->SubstractMana(m_SpellLevel[LIGHT] * 3);

		}break;
	}
}