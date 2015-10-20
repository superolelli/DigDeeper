#include "MagicMenu.hpp"
#include "Projectiles.hpp"
#include "Effects.hpp"


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

		m_Cooldown[i] = 0;

		if (!_loaded)
			m_SpellLevel[i] = 0;
	}

	//set position of the spells
	m_Spells[FIREBALL].m_Sprite->SetPos(m_pMagicMenu->GetRect().left + 41, m_pMagicMenu->GetRect().top + 91);
	m_Spells[ICE].m_Sprite->SetPos(m_pMagicMenu->GetRect().left + 186, m_pMagicMenu->GetRect().top + 91);
	m_Spells[POISONCLOUD].m_Sprite->SetPos(m_pMagicMenu->GetRect().left + 41, m_pMagicMenu->GetRect().top + 221);
	m_Spells[HEAL].m_Sprite->SetPos(m_pMagicMenu->GetRect().left + 374, m_pMagicMenu->GetRect().top + 91);
	m_Spells[MANASHIELD].m_Sprite->SetPos(m_pMagicMenu->GetRect().left + 519, m_pMagicMenu->GetRect().top + 91);
	m_Spells[ALCHEMY].m_Sprite->SetPos(m_pMagicMenu->GetRect().left + 707, m_pMagicMenu->GetRect().top + 91);
	m_Spells[LIGHT].m_Sprite->SetPos(m_pMagicMenu->GetRect().left + 852, m_pMagicMenu->GetRect().top + 91);
	m_Spells[TELEPORT].m_Sprite->SetPos(m_pMagicMenu->GetRect().left + 707, m_pMagicMenu->GetRect().top + 221);


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
		m_text.setCharacterSize(25);
		m_text.setColor(Color::Black);
		m_text.setPosition(m_pMagicMenu->GetRect().left + 565, m_pMagicMenu->GetRect().top + 12);
		g_pFramework->GetRenderWindow()->draw(m_text);

		string tooltip("");
		RectangleShape tooltipBackground;

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
			else if (m_Spells[i].m_Sprite->GetRect().contains(Mouse::getPosition()))
			{
				tooltip = GetTooltip(i);
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


		//show tooltip
		if (tooltip != "")
		{
			m_text.setString(tooltip);
			m_text.setPosition((float)(Mouse::getPosition().x + 13), (float)(Mouse::getPosition().y));
			m_text.setCharacterSize(15);
			m_text.setColor(Color::Yellow);

			FloatRect backgroundRect = m_text.getLocalBounds();
			tooltipBackground = RectangleShape(Vector2f(backgroundRect.width, backgroundRect.height + 5));
			tooltipBackground.setFillColor(Color::Black);

			g_pFramework->GetRenderWindow()->draw(tooltipBackground, m_text.getTransform());
			g_pFramework->GetRenderWindow()->draw(m_text);
		}
	}


	//manage the cooldown
	for (int i = 0; i < AMOUNTOFSPELLS; i++)
	{
		m_Cooldown[i] -= g_pTimer->GetElapsedTime().asSeconds();

		if (m_Cooldown[i] <= 0)
			m_Cooldown[i] = 0;
	}
	
}




void CMagicMenu::CastSpell(int _ID)
{
	//if the spell is ready
	if (m_Cooldown[_ID] <= 0)
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

		case(POISONCLOUD) :
		{
			if (m_pPlayer->GetMana() >= m_SpellLevel[POISONCLOUD] * 5)
			{
				g_pEffects->AddEffect(POISONEFFECT, m_pPlayer->GetRect().left - 60, m_pPlayer->GetRect().top, NULL, NULL);

				//substract mana
				m_pPlayer->SubstractMana(m_SpellLevel[POISONCLOUD] * 5);
			}
		}break;

		case(HEAL) :
		{
			if (m_pPlayer->GetMana() >= m_SpellLevel[HEAL] * 10)
			{
				m_pPlayer->Heal(m_SpellLevel[HEAL] * 10);

				g_pEffects->AddEffect(HEALEFFECT, m_pPlayer->GetRect().left - 30, m_pPlayer->GetRect().top, m_pPlayer->GetPosXPointer(), m_pPlayer->GetPosYPointer());

				//substract mana
				m_pPlayer->SubstractMana(m_SpellLevel[HEAL] * 10);
			}
		}break;

		case(MANASHIELD) :
		{
			if (m_pPlayer->GetMana() >= m_pPlayer->GetPlayerAttributes().maxMana * ((float)m_SpellLevel[MANASHIELD] * 0.03))
			{
				g_pEffects->AddEffect(MANASHIELDEFFECT, m_pPlayer->GetRect().left - 30, m_pPlayer->GetRect().top, m_pPlayer->GetPosXPointer(), m_pPlayer->GetPosYPointer(), m_SpellLevel[MANASHIELD] * 5);

				SConsumableAttributes effect;
				effect.armour = m_pPlayer->GetPlayerAttributes().maxMana * (m_SpellLevel[MANASHIELD] * 0.05);
				effect.breaking_speed = 0;
				effect.luck = 0;
				effect.health = 0;
				effect.mana = 0;
				effect.speed = 0;
				effect.strength = 0;
				effect.healthRegeneration = 0;
				effect.manaRegeneration = 0;
				effect.criticalChance = 0;
				effect.criticalDamage = 0;
				effect.poison = 0;
				effect.duration = m_SpellLevel[MANASHIELD] * 5;

				m_pPlayer->AddEffect(effect);

				//substract mana
				m_pPlayer->SubstractMana(m_pPlayer->GetPlayerAttributes().maxMana * (float)m_SpellLevel[MANASHIELD] * 0.03);
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
			if (m_pPlayer->GetMana() >= m_SpellLevel[LIGHT] * 3)
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
			}

		}break;

		case(TELEPORT) :
		{
			if (m_pPlayer->GetMana() >= m_SpellLevel[TELEPORT] * 5)
			{
				m_pPlayer->Teleport(m_SpellLevel[TELEPORT]);

				g_pEffects->AddEffect(TELEPORT, m_pPlayer->GetRect().left, m_pPlayer->GetRect().top, NULL, NULL);

				//substract mana
				m_pPlayer->SubstractMana(m_SpellLevel[TELEPORT] * 5);
			}

		}break;
		}


		m_Cooldown[_ID] = 1;
	}
}



//returns the tooltip for the spell
string CMagicMenu::GetTooltip(int _spellID)
{
	stringstream tooltip;
 

	switch (_spellID)
	{
	case(FIREBALL) :
	{
		tooltip << g_pStringContainer->m_Strings[STRING_FIREBALL_DESCRIPTION] << endl << endl;

		if (m_SpellLevel[FIREBALL] == 0)
		{
			tooltip << g_pStringContainer->m_Strings[STRING_SPELL_NOT_LEARNED] << endl << endl;
		}
		else
		{
			tooltip << g_pStringContainer->m_Strings[STRING_DAMAGE] << " " << m_SpellLevel[FIREBALL] * 3 << endl;
			tooltip << g_pStringContainer->m_Strings[STRING_MANACOSTS] <<" " << m_SpellLevel[FIREBALL] * 5 << endl << endl;
		}

		if (m_SpellLevel[FIREBALL] == 10)
		{
			tooltip << g_pStringContainer->m_Strings[STRING_SPELL_ON_HIGHEST_LEVEL];
		}
		else
		{
			tooltip << g_pStringContainer->m_Strings[STRING_SPELL_ON_NEXT_LEVEL] << " " << endl;
			tooltip << g_pStringContainer->m_Strings[STRING_DAMAGE] << " " << (m_SpellLevel[FIREBALL]+1) * 3 << endl;
			tooltip << g_pStringContainer->m_Strings[STRING_MANACOSTS] << " " << (m_SpellLevel[FIREBALL]+1) * 5;
		}
	}break;
	case(ICE) :
	{
		tooltip << g_pStringContainer->m_Strings[STRING_ICEBALL_DESCRIPTION] << endl << endl;

		if (m_SpellLevel[ICE] == 0)
		{
			tooltip << g_pStringContainer->m_Strings[STRING_SPELL_NOT_LEARNED] << " " << endl << endl;
		}
		else
		{
			tooltip << g_pStringContainer->m_Strings[STRING_DAMAGE] << " " << m_SpellLevel[ICE] * 1 << endl;
			tooltip << g_pStringContainer->m_Strings[STRING_FROZEN_TIME] << " " << m_SpellLevel[ICE] * 0.5 << endl;
			tooltip << g_pStringContainer->m_Strings[STRING_MANACOSTS] << " " << m_SpellLevel[ICE] * 5 << endl << endl;
		}

		if (m_SpellLevel[ICE] == 10)
		{
			tooltip << g_pStringContainer->m_Strings[STRING_SPELL_ON_HIGHEST_LEVEL];
		}
		else
		{
			tooltip << g_pStringContainer->m_Strings[STRING_SPELL_ON_NEXT_LEVEL] << " " << endl;
			tooltip << g_pStringContainer->m_Strings[STRING_DAMAGE] << " " << (m_SpellLevel[ICE] + 1) * 1 << endl;
			tooltip << g_pStringContainer->m_Strings[STRING_FROZEN_TIME] << " " << (m_SpellLevel[ICE] + 1) * 0.5 << endl;
			tooltip << g_pStringContainer->m_Strings[STRING_MANACOSTS] << " " << (m_SpellLevel[ICE] + 1) * 5;
		}
	}break;
	case(POISONCLOUD) :
	{
		tooltip << g_pStringContainer->m_Strings[STRING_POISONCLOUD_DESCRIPTION] << endl << endl;

		if (m_SpellLevel[POISONCLOUD] == 0)
		{
			tooltip << g_pStringContainer->m_Strings[STRING_SPELL_NOT_LEARNED] << " " << endl << endl;
		}
		else
		{
			tooltip << g_pStringContainer->m_Strings[STRING_POISON_LEVEL] << " " << (int)(m_SpellLevel[POISONCLOUD] * +1)/2 << endl;
			tooltip << g_pStringContainer->m_Strings[STRING_POISON_DURATION] << " " << m_SpellLevel[POISONCLOUD] * 2 << endl;
			tooltip << g_pStringContainer->m_Strings[STRING_MANACOSTS] << " " << m_SpellLevel[POISONCLOUD] * 5 << endl << endl;
		}

		if (m_SpellLevel[POISONCLOUD] == 10)
		{
			tooltip << g_pStringContainer->m_Strings[STRING_SPELL_ON_HIGHEST_LEVEL];
		}
		else
		{
			tooltip << g_pStringContainer->m_Strings[STRING_SPELL_ON_NEXT_LEVEL] << " " << endl;
			tooltip << g_pStringContainer->m_Strings[STRING_POISON_LEVEL] << " " << ((int)(m_SpellLevel[POISONCLOUD] + 2) / 2) << endl;
			tooltip << g_pStringContainer->m_Strings[STRING_POISON_DURATION] << " " << (m_SpellLevel[POISONCLOUD] + 1) * 2 << endl;
			tooltip << g_pStringContainer->m_Strings[STRING_MANACOSTS] << " " << (m_SpellLevel[POISONCLOUD] + 1) * 5;
		}
	}break;
	case(HEAL) :
	{
		tooltip << g_pStringContainer->m_Strings[STRING_HEAL_DESCRIPTION] << endl << endl;

		if (m_SpellLevel[HEAL] == 0)
		{
			tooltip << g_pStringContainer->m_Strings[STRING_SPELL_NOT_LEARNED] << " " << endl << endl;
		}
		else
		{
			tooltip << g_pStringContainer->m_Strings[STRING_HEALTHPOINTS] << " " << m_SpellLevel[HEAL] * 10 << endl;
			tooltip << g_pStringContainer->m_Strings[STRING_MANACOSTS] << " " << m_SpellLevel[HEAL] * 10 << endl << endl;
		}

		if (m_SpellLevel[HEAL] == 10)
		{
			tooltip << g_pStringContainer->m_Strings[STRING_SPELL_ON_HIGHEST_LEVEL];
		}
		else
		{
			tooltip << g_pStringContainer->m_Strings[STRING_SPELL_ON_NEXT_LEVEL] << " " << endl;
			tooltip << g_pStringContainer->m_Strings[STRING_HEALTHPOINTS] << " " << (m_SpellLevel[HEAL] + 1) * 10 << endl;
			tooltip << g_pStringContainer->m_Strings[STRING_MANACOSTS] << " " << (m_SpellLevel[HEAL] + 1) * 10;
		}
	}break;
	case(MANASHIELD) :
	{
		tooltip << g_pStringContainer->m_Strings[STRING_MANASHIELD_DESCRIPTION] << endl << endl;

		if (m_SpellLevel[MANASHIELD] == 0)
		{
			tooltip << g_pStringContainer->m_Strings[STRING_SPELL_NOT_LEARNED] << " " << endl << endl;
		}
		else
		{
			tooltip << g_pStringContainer->m_Strings[STRING_ARMOUR] << ": " << m_pPlayer->GetPlayerAttributes().maxMana * (float)(m_SpellLevel[MANASHIELD] * 0.05) << endl;
			tooltip << g_pStringContainer->m_Strings[STRING_DURATION] << ": " << m_SpellLevel[MANASHIELD] * 5 << endl;
			tooltip << g_pStringContainer->m_Strings[STRING_MANACOSTS] << " " << m_pPlayer->GetPlayerAttributes().maxMana * (float)(m_SpellLevel[MANASHIELD] * 0.03) << endl << endl;
		}

		if (m_SpellLevel[MANASHIELD] == 10)
		{
			tooltip << g_pStringContainer->m_Strings[STRING_SPELL_ON_HIGHEST_LEVEL];
		}
		else
		{
			tooltip << g_pStringContainer->m_Strings[STRING_SPELL_ON_NEXT_LEVEL] << " " << endl;
			tooltip << g_pStringContainer->m_Strings[STRING_ARMOUR] << ": " << m_pPlayer->GetPlayerAttributes().maxMana * (float)((m_SpellLevel[MANASHIELD] + 1) * 0.05) << endl;
			tooltip << g_pStringContainer->m_Strings[STRING_DURATION] << ": " << (m_SpellLevel[MANASHIELD] + 1) * 5 << endl;
			tooltip << g_pStringContainer->m_Strings[STRING_MANACOSTS] << " " << m_pPlayer->GetPlayerAttributes().maxMana * (float)((m_SpellLevel[MANASHIELD] + 1) * 0.03);
		}
	}break;
	case(ALCHEMY) :
	{
		tooltip << g_pStringContainer->m_Strings[STRING_ALCHEMY_DESCRIPTION] << endl << endl;

		if (m_SpellLevel[ALCHEMY] == 0)
		{
			tooltip << g_pStringContainer->m_Strings[STRING_SPELL_NOT_LEARNED] << " " << endl << endl;
		}
		else
		{
			tooltip << g_pStringContainer->m_Strings[STRING_CHANCE_FOR_HIGHER_BLOCK] << " " << m_SpellLevel[ALCHEMY] * 1 << "%" << endl;
			tooltip << g_pStringContainer->m_Strings[STRING_CHANCE_FOR_LOWER_BLOCK] << " 5%" << endl;
			tooltip << g_pStringContainer->m_Strings[STRING_MANACOSTS] << " " << m_SpellLevel[ALCHEMY] * 5 << endl << endl;
		}

		if (m_SpellLevel[ALCHEMY] == 10)
		{
			tooltip << g_pStringContainer->m_Strings[STRING_SPELL_ON_HIGHEST_LEVEL];
		}
		else
		{
			tooltip << g_pStringContainer->m_Strings[STRING_SPELL_ON_NEXT_LEVEL] << " " << endl;
			tooltip << g_pStringContainer->m_Strings[STRING_CHANCE_FOR_HIGHER_BLOCK] << " " << (m_SpellLevel[ALCHEMY] + 1) * 1 << "%" << endl;
			tooltip << g_pStringContainer->m_Strings[STRING_CHANCE_FOR_LOWER_BLOCK] << " 5%" << endl;
			tooltip << g_pStringContainer->m_Strings[STRING_MANACOSTS] << " " << (m_SpellLevel[ALCHEMY] + 1) * 5;
		}
	}break;
	case(LIGHT) :
	{

		tooltip << g_pStringContainer->m_Strings[STRING_LIGHTSPELL_DESCRIPTION] << endl << endl;

		if (m_SpellLevel[LIGHT] == 0)
		{
			tooltip << g_pStringContainer->m_Strings[STRING_SPELL_NOT_LEARNED] << " " << endl << endl;
		}
		else
		{
			tooltip << g_pStringContainer->m_Strings[STRING_LIGHTRADIUS] << " " << m_SpellLevel[LIGHT] * 50 << endl;
			tooltip << g_pStringContainer->m_Strings[STRING_DURATION] << ": " << m_SpellLevel[LIGHT] * 5 << endl;
			tooltip << g_pStringContainer->m_Strings[STRING_MANACOSTS] << " " << m_SpellLevel[LIGHT] * 5 << endl << endl;
		}

		if (m_SpellLevel[LIGHT] == 10)
		{
			tooltip << g_pStringContainer->m_Strings[STRING_SPELL_ON_HIGHEST_LEVEL];
		}
		else
		{
			tooltip << g_pStringContainer->m_Strings[STRING_SPELL_ON_NEXT_LEVEL] << " " << endl;
			tooltip << g_pStringContainer->m_Strings[STRING_LIGHTRADIUS] << " " << (m_SpellLevel[LIGHT] + 1) * 50 << endl;
			tooltip << g_pStringContainer->m_Strings[STRING_DURATION] << ": " << (m_SpellLevel[LIGHT] + 1) * 5 << endl;
			tooltip << g_pStringContainer->m_Strings[STRING_MANACOSTS] << " " << (m_SpellLevel[LIGHT] + 1) * 5;
		}
	}break;
	case(TELEPORT) :
	{

		tooltip << g_pStringContainer->m_Strings[STRING_TELEPORT_DESCRIPTION] << endl << endl;

		if (m_SpellLevel[TELEPORT] == 0)
		{
			tooltip << g_pStringContainer->m_Strings[STRING_SPELL_NOT_LEARNED] << " " << endl << endl;
		}
		else
		{
			tooltip << g_pStringContainer->m_Strings[STRING_WIDTH] << " " << m_SpellLevel[TELEPORT] * 100 << endl;
			tooltip << g_pStringContainer->m_Strings[STRING_MANACOSTS] << " " << m_SpellLevel[TELEPORT] * 5 << endl << endl;
		}

		if (m_SpellLevel[TELEPORT] == 10)
		{
			tooltip << g_pStringContainer->m_Strings[STRING_SPELL_ON_HIGHEST_LEVEL];
		}
		else
		{
			tooltip << g_pStringContainer->m_Strings[STRING_SPELL_ON_NEXT_LEVEL] << " " << endl;
			tooltip << g_pStringContainer->m_Strings[STRING_WIDTH] << " " << (m_SpellLevel[TELEPORT] + 1) * 100 << endl;
			tooltip << g_pStringContainer->m_Strings[STRING_MANACOSTS] << " " << (m_SpellLevel[TELEPORT] + 1) * 5;
		}
	}break;
	default:
		tooltip << "---";
	}


	return tooltip.str();
}