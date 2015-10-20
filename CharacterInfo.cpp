#include "CharacterInfo.hpp"
#include "Player.hpp"




CCharacterInfo::CCharacterInfo()
{
	m_pCharacterWindow = NULL;
	m_pLevelUp = NULL;
	for (int i = 0; i < 4; i++)
		m_SkillButtons[i].button = 0;
	m_pLevelUpButton = NULL;
	m_pPlayer = NULL;
}




CCharacterInfo::~CCharacterInfo()
{
	SAFE_DELETE(m_pCharacterWindow);
	SAFE_DELETE(m_pLevelUp);
	SAFE_DELETE(m_pLevelUpButton);

	for (int i = 0; i < 4; i++)
		SAFE_DELETE(m_SkillButtons[i].button);
}




void CCharacterInfo::Init(SPlayerAttributes *_attributes, SToolAttributes *_modifications, CPlayer *_player, bool _loaded)
{
	m_pAttributes = _attributes;
	m_pModifications = _modifications;
	m_pPlayer = _player;

	m_pCharacterWindow = new CSprite;
	m_pCharacterWindow->Load(&g_pTextures->t_skillPage);
	m_pCharacterWindow->SetPos((int)(g_pFramework->GetRenderWindow()->getSize().x/2 - m_pCharacterWindow->GetRect().width/2), (int)(g_pFramework->GetRenderWindow()->getSize().y/2 - m_pCharacterWindow->GetRect().height/2));

	m_pLevelUp = new CSprite;
	m_pLevelUp->Load(&g_pTextures->t_levelUp);
	m_pLevelUp->SetPos((int)(g_pFramework->GetRenderWindow()->getSize().x/2 - m_pLevelUp->GetRect().width/2), (int)(g_pFramework->GetRenderWindow()->getSize().y/2 - m_pLevelUp->GetRect().height/2));

	m_pLevelUpButton = new CButton;
	m_pLevelUpButton->Load(&g_pTextures->t_levelUp_button, g_pFramework->GetWindow()->getSize().x - 100, 20, 1);

	//loads the font and applies it to the text
	m_text.setFont(g_pTextures->f_cents18);
	m_text.setCharacterSize(30);
	m_text.setColor(Color::Black);

	m_title.setFont(g_pTextures->f_plantc);
	m_title.setCharacterSize(28);
	m_title.setColor(Color::Black);

	m_description.setFont(g_pTextures->f_plantc);
	m_description.setCharacterSize(18);
	m_description.setColor(Color::Black);

	m_levelUpTime = 0.0f;

	Skills[0] = 0;
	Skills[1] = 0;
	Skills[2] = 0;
	Skills[3] = 0;

	for(int i = 0; i < NUMBER_OF_SKILLS; i++)
	{
		AllSkills[i] = false;
	}

	is_open = false;
	level_up = false;
	choosing_skill = false;

	if (!_loaded)
	{
		m_levelUpCounter = 0;
		m_playerLevel = 1;
	}
}




void CCharacterInfo::Render()
{
	stringstream stream;

	//if c was pressed: Open or close the window
	if(g_pFramework->keyStates.cUp)
	{
		if(is_open)
			is_open = false;
		else
			is_open = true;
	}


	if(is_open)
	{	
		g_pFramework->WriteToLog(INFO, "Inventory is open");
		m_pCharacterWindow->Render(g_pFramework->GetRenderWindow());

		//show the level
		m_text.setCharacterSize(60);
		stream.str("");
		stream << m_playerLevel;
		m_text.setString(stream.str());
		m_text.setPosition((float)(m_pCharacterWindow->GetRect().left + 340), (float)(m_pCharacterWindow->GetRect().top - 20));
		g_pFramework->GetRenderWindow()->draw(m_text);
		m_text.setCharacterSize(30);

		//show the health
		m_text.setString(g_pStringContainer->m_Strings[STRING_HEALTH]);
		m_text.setPosition((int)(m_pCharacterWindow->GetRect().left + 10), (int)(m_pCharacterWindow->GetRect().top + 99));
		g_pFramework->GetRenderWindow()->draw(m_text);

		stream.str("");
		stream << m_pModifications->maxHealth;
		m_text.setString(stream.str());
		m_text.setPosition((float)(m_pCharacterWindow->GetRect().left + 280), (float)(m_pCharacterWindow->GetRect().top + 99));
		g_pFramework->GetRenderWindow()->draw(m_text);

		//show the healthregeneration
		m_text.setString(g_pStringContainer->m_Strings[STRING_HEALTHREGENERATION]);
		m_text.setPosition((int)(m_pCharacterWindow->GetRect().left + 10), (int)(m_pCharacterWindow->GetRect().top + 126));
		g_pFramework->GetRenderWindow()->draw(m_text);

		stream.str("");
		stream << m_pModifications->healthRegeneration;
		m_text.setString(stream.str());
		m_text.setPosition((float)(m_pCharacterWindow->GetRect().left + 280), (float)(m_pCharacterWindow->GetRect().top + 126));
		g_pFramework->GetRenderWindow()->draw(m_text);

		//show the armour
		m_text.setString(g_pStringContainer->m_Strings[STRING_ARMOUR]);
		m_text.setPosition((int)(m_pCharacterWindow->GetRect().left + 10), (int)(m_pCharacterWindow->GetRect().top + 158));
		g_pFramework->GetRenderWindow()->draw(m_text);

		stream.str("");
		stream << m_pModifications->armour;
		m_text.setString(stream.str());
		m_text.setPosition((float)(m_pCharacterWindow->GetRect().left + 280), (float)(m_pCharacterWindow->GetRect().top + 158));
		g_pFramework->GetRenderWindow()->draw(m_text);

		//show the strength
		m_text.setString(g_pStringContainer->m_Strings[STRING_STRENGTH]);
		m_text.setPosition((int)(m_pCharacterWindow->GetRect().left + 10), (int)(m_pCharacterWindow->GetRect().top + 228));
		g_pFramework->GetRenderWindow()->draw(m_text);

		stream.str("");
		stream << m_pModifications->strength;
		m_text.setString(stream.str());
		m_text.setPosition((float)(m_pCharacterWindow->GetRect().left + 280), (float)(m_pCharacterWindow->GetRect().top + 228));
		g_pFramework->GetRenderWindow()->draw(m_text);
		
		//show the critical chance
		m_text.setString(g_pStringContainer->m_Strings[STRING_CRITICALCHANCE]);
		m_text.setPosition((int)(m_pCharacterWindow->GetRect().left + 10), (int)(m_pCharacterWindow->GetRect().top + 254));
		g_pFramework->GetRenderWindow()->draw(m_text);

		stream.str("");
		stream << m_pModifications->criticalChance;
		m_text.setString(stream.str());
		m_text.setPosition((float)(m_pCharacterWindow->GetRect().left + 280), (float)(m_pCharacterWindow->GetRect().top + 254));
		g_pFramework->GetRenderWindow()->draw(m_text);
		
		//show the critical damage
		m_text.setString(g_pStringContainer->m_Strings[STRING_CRITICALDAMAGE]);
		m_text.setPosition((int)(m_pCharacterWindow->GetRect().left + 10), (int)(m_pCharacterWindow->GetRect().top + 287));
		g_pFramework->GetRenderWindow()->draw(m_text);

		stream.str("");
		stream << m_pModifications->criticalDamage;
		m_text.setString(stream.str());
		m_text.setPosition((float)(m_pCharacterWindow->GetRect().left + 280), (float)(m_pCharacterWindow->GetRect().top + 287));
		g_pFramework->GetRenderWindow()->draw(m_text);

		//show the luck
		m_text.setString(g_pStringContainer->m_Strings[STRING_LUCK]);
		m_text.setPosition((int)(m_pCharacterWindow->GetRect().left + 10), (int)(m_pCharacterWindow->GetRect().top +352));
		g_pFramework->GetRenderWindow()->draw(m_text);

		stream.str("");
		stream << m_pModifications->luck;
		m_text.setString(stream.str());
		m_text.setPosition((float)(m_pCharacterWindow->GetRect().left + 280), (float)(m_pCharacterWindow->GetRect().top + 352));
		g_pFramework->GetRenderWindow()->draw(m_text);

		//show the breakingSpeed
		m_text.setString(g_pStringContainer->m_Strings[STRING_BREAKINGSPEED]);
		m_text.setPosition((int)(m_pCharacterWindow->GetRect().left + 10), (int)(m_pCharacterWindow->GetRect().top + 380));
		g_pFramework->GetRenderWindow()->draw(m_text);

		stream.str("");
		stream << m_pModifications->breaking_speed;
		m_text.setString(stream.str());
		m_text.setPosition((float)(m_pCharacterWindow->GetRect().left + 280), (float)(m_pCharacterWindow->GetRect().top + 380));
		g_pFramework->GetRenderWindow()->draw(m_text);

		//show the speed
		m_text.setString(g_pStringContainer->m_Strings[STRING_SPEED]);
		m_text.setPosition((int)(m_pCharacterWindow->GetRect().left + 10), (int)(m_pCharacterWindow->GetRect().top + 412));
		g_pFramework->GetRenderWindow()->draw(m_text);

		stream.str("");
		stream << m_pModifications->speed;
		m_text.setString(stream.str());
		m_text.setPosition((float)(m_pCharacterWindow->GetRect().left + 280), (float)(m_pCharacterWindow->GetRect().top + 412));
		g_pFramework->GetRenderWindow()->draw(m_text);

		//show the mana
		m_text.setString(g_pStringContainer->m_Strings[STRING_MANA]);
		m_text.setPosition((int)(m_pCharacterWindow->GetRect().left + 380), (int)(m_pCharacterWindow->GetRect().top + 100));
		g_pFramework->GetRenderWindow()->draw(m_text);

		stream.str("");
		stream << m_pModifications->maxMana;
		m_text.setString(stream.str());
		m_text.setPosition((float)(m_pCharacterWindow->GetRect().left + 595), (float)(m_pCharacterWindow->GetRect().top + 100));
		g_pFramework->GetRenderWindow()->draw(m_text);

		//show the manaregeneration
		m_text.setString(g_pStringContainer->m_Strings[STRING_MANAREGENERATION]);
		m_text.setPosition((int)(m_pCharacterWindow->GetRect().left + 380), (int)(m_pCharacterWindow->GetRect().top + 125));
		g_pFramework->GetRenderWindow()->draw(m_text);

		stream.str("");
		stream << m_pModifications->manaRegeneration;
		m_text.setString(stream.str());
		m_text.setPosition((float)(m_pCharacterWindow->GetRect().left + 595), (float)(m_pCharacterWindow->GetRect().top + 125));
		g_pFramework->GetRenderWindow()->draw(m_text);
	
	}

	CheckForLevelUp();

	//if the player has reached a new level: show the new skills
	if(m_levelUpCounter > 0)
	{
		choosing_skill = true;

		//if the level up button was pressed:
		if (m_pLevelUpButton->Render(g_pFramework->keyStates.leftMouseUp))
		{
			is_open = true;
			m_pPlayer->SetMenuOpen(2);
		}
	}


	if (choosing_skill && is_open)
	{
		LevelUp();
	}
	//else set all skills to zero
	else if (choosing_skill == false && m_levelUpCounter == 0)
	{
		choosing_skill = false;
		level_up = false;

		Skills[0] = 0;
		Skills[1] = 0;
		Skills[2] = 0;
		Skills[3] = 0;

		for(int i = 0; i < NUMBER_OF_SKILLS; i++)
		{
			AllSkills[i] = false;
		}
	}
}




//checks if the player reached a new level
void CCharacterInfo::CheckForLevelUp()
{

	if (m_pAttributes->currentExp >= m_pAttributes->maxExp)
	{
		//subtract the exp needed to level up
		m_pAttributes->currentExp -= m_pAttributes->maxExp;
		m_pAttributes->maxExp += m_pAttributes->maxExp/2;
		level_up = true;

		m_levelUpTime = 0.0f;

		m_levelUpCounter++;

		//increase the player's level
		m_playerLevel++;

		g_pSignMachine->AddString("Level Up!", 2, m_pPlayer->GetRect().left - m_pPlayer->GetRect().width/2, m_pPlayer->GetRect().top, Color::Blue);
	}


	if (m_levelUpCounter > 0 && choosing_skill == false)
	{
		for (int i = 0; i < 4; i++)
			SAFE_DELETE(m_SkillButtons[i].button);

		//loads new buttons
		if (m_pPlayer->GetNotAvailableRecipesList().size() > 0)
		{
			m_SkillButtons[0].button = new CButton;
			m_SkillButtons[0].button->Load(&g_pTextures->t_newSkillClear, 0, 0, 1);
			m_SkillButtons[0].title = g_pStringContainer->m_Strings[STRING_SKILL_RECIPE_TITLE];
			m_SkillButtons[0].description = g_pStringContainer->m_Strings[STRING_SKILL_RECIPE_DESCRIPTION];
			Skills[0] = RECIPESKILL;
		}
		else
			m_SkillButtons[0] = RandomSkill(0);


		for (int i = 1; i < 4; i++)
			m_SkillButtons[i] = RandomSkill(i);

		m_SkillButtons[0].button->SetPos(m_pLevelUp->GetRect().left, m_pLevelUp->GetRect().top + 50);
		m_SkillButtons[1].button->SetPos(m_pLevelUp->GetRect().left + 300, m_pLevelUp->GetRect().top + 50);
		m_SkillButtons[2].button->SetPos(m_pLevelUp->GetRect().left, m_pLevelUp->GetRect().top + 250);
		m_SkillButtons[3].button->SetPos(m_pLevelUp->GetRect().left + 300, m_pLevelUp->GetRect().top + 250);

	}
}





//render the sill buttons
void CCharacterInfo::LevelUp()
{
	int eventtype = -1;

	//add time
	m_levelUpTime += g_pTimer->GetElapsedTime().asSeconds();

	//check for the key state if the starting time of 1 second has already passed
	if(m_levelUpTime >= 1)
	{
		if(g_pFramework->keyStates.leftMouseUp)
			eventtype = MOUSE_LEFT_UP;
	}

	//render the window and the buttons
	m_pLevelUp->Render(g_pFramework->GetRenderWindow());


	for (int i = 0; i < 4; i++)
	{
		//render the button
		if (m_SkillButtons[i].button->Render(eventtype))
		{
			choosing_skill = false;
			m_levelUpCounter--;
			AddSkill(Skills[i]);
		}

		//render the text
		m_title.setString(m_SkillButtons[i].title);
		m_title.setPosition((int)(m_SkillButtons[i].button->GetRect().left + (m_SkillButtons[i].button->GetRect().width - m_title.getGlobalBounds().width)/2), (int)(m_SkillButtons[i].button->GetRect().top +5));
		g_pFramework->GetRenderWindow()->draw(m_title);

		m_description.setString(m_SkillButtons[i].description);
		m_description.setPosition((int)(m_SkillButtons[i].button->GetRect().left + (m_SkillButtons[i].button->GetRect().width - m_description.getGlobalBounds().width) / 2), (int)(m_SkillButtons[i].button->GetRect().top + m_SkillButtons[i].button->GetRect().height - m_description.getGlobalBounds().height)-20);
		g_pFramework->GetRenderWindow()->draw(m_description);

	}
}


//returns a random skill
SkillButton CCharacterInfo::RandomSkill(int _skillNumber)
{
	SkillButton skillButton;
	CButton *newButton = new CButton;

	int number = -1;

	//gets a random number, which isn't used already
	do
	{
		 number = rand()%NUMBER_OF_SKILLS + 1; //the +1 is for the recipe-skill
	}while(AllSkills[number] == true);

	AllSkills[number] = true;

	switch(number)
	{
	case SPEED:
		{
				//newButton->Load(&g_pTextures->t_newSkillSpeed, 0, 0, 1);
				skillButton.title = g_pStringContainer->m_Strings[STRING_SKILL_SPEED_TITLE];
				skillButton.description = g_pStringContainer->m_Strings[STRING_SKILL_SPEED_DESCRIPTION];
		}break;
	case BREAKINGSPEED:
		{
				//newButton->Load(&g_pTextures->t_newSkillBreakingSpeed, 0, 0, 1);
				skillButton.title = g_pStringContainer->m_Strings[STRING_SKILL_BREAKINGSPEED_TITLE];
				skillButton.description = g_pStringContainer->m_Strings[STRING_SKILL_BREAKINGSPEED_DESCRIPTION];
		}break;
	case HEALTH:
		{
				//newButton->Load(&g_pTextures->t_newSkillHealth, 0, 0, 1);
				skillButton.title = g_pStringContainer->m_Strings[STRING_SKILL_HEALTH_TITLE];
				skillButton.description = g_pStringContainer->m_Strings[STRING_SKILL_HEALTH_DESCRIPTION];
		}break;
	case STRENGTH:
		{
				//newButton->Load(&g_pTextures->t_newSkillStrength, 0, 0, 1);
				skillButton.title = g_pStringContainer->m_Strings[STRING_SKILL_STRENGTH_TITLE];
				skillButton.description = g_pStringContainer->m_Strings[STRING_SKILL_STRENGTH_DESCRIPTION];
		}break;
	case ARMOUR:
		{
				//newButton->Load(&g_pTextures->t_newSkillArmour, 0, 0, 1);
				skillButton.title = g_pStringContainer->m_Strings[STRING_SKILL_ARMOUR_TITLE];
				skillButton.description = g_pStringContainer->m_Strings[STRING_SKILL_ARMOUR_DESCRIPTION];
		}break;
	case LUCK:
		{
				//newButton->Load(&g_pTextures->t_newSkillLuck, 0, 0, 1);
				skillButton.title = g_pStringContainer->m_Strings[STRING_SKILL_LUCK_TITLE];
				skillButton.description = g_pStringContainer->m_Strings[STRING_SKILL_LUCK_DESCRIPTION];
		}break;
	case MANA:
		{
				//newButton->Load(&g_pTextures->t_newSkillMana, 0, 0, 1);
				skillButton.title = g_pStringContainer->m_Strings[STRING_SKILL_MANA_TITLE];
				skillButton.description = g_pStringContainer->m_Strings[STRING_SKILL_MANA_DESCRIPTION];
		}break;
	case HEALTHREGENERATION:
		{
			//newButton->Load(&g_pTextures->t_newSkillHealthRegeneration, 0, 0, 1);
			skillButton.title = g_pStringContainer->m_Strings[STRING_SKILL_HEALTHREGENERATION_TITLE];
			skillButton.description = g_pStringContainer->m_Strings[STRING_SKILL_HEALTHREGENERATION_DESCRIPTION];
		}break;
	case MANAREGENERATION:
		{
			//newButton->Load(&g_pTextures->t_newSkillManaRegeneration, 0, 0, 1);
			skillButton.title = g_pStringContainer->m_Strings[STRING_SKILL_MANAREGENERATION_TITLE];
			skillButton.description = g_pStringContainer->m_Strings[STRING_SKILL_MANAREGENERATION_DESCRIPTION];
		}break;
	case CRITICALCHANCE:
		{
			//newButton->Load(&g_pTextures->t_newSkillCriticalChance, 0, 0, 1);
			skillButton.title = g_pStringContainer->m_Strings[STRING_SKILL_CRITICALCHANCE_TITLE];
			skillButton.description = g_pStringContainer->m_Strings[STRING_SKILL_CRITICALCHANCE_DESCRIPTION];
		}break;
	case CRITICALDAMAGE:
		{
			//newButton->Load(&g_pTextures->t_newSkillCriticalDamage, 0, 0, 1);
			skillButton.title = g_pStringContainer->m_Strings[STRING_SKILL_CRITICALDAMAGE_TITLE];
			skillButton.description = g_pStringContainer->m_Strings[STRING_SKILL_CRITICALDAMAGE_DESCRIPTION];
		}break;
	case MAGICPOINTS:
	{
		//newButton->Load(&g_pTextures->t_newSkillMagicPoints, 0, 0, 1);
		skillButton.title = g_pStringContainer->m_Strings[STRING_SKILL_MAGICPOINT_TITLE];
		skillButton.description = g_pStringContainer->m_Strings[STRING_SKILL_MAGICPOINT_DESCRIPTION];
	}break;
	default:
		{
			cout <<"Couldn't load Skill button!" << endl;
		}break;
	};

	newButton->Load(&g_pTextures->t_newSkillClear, 0, 0, 1);
	skillButton.button = newButton;
	Skills[_skillNumber] = number;

	return skillButton;
}



//adds a new skill
void CCharacterInfo::AddSkill(int _skill)
{
	switch(_skill)
	{
	case SPEED:
		{
			m_pAttributes->speed += 10;
		}break;
	case BREAKINGSPEED:
		{
			m_pAttributes->breakingSpeed += 0.5f;
		}break;
    case HEALTH:
		{
			m_pAttributes->maxHealth += 10;
			m_pAttributes->currentHealth += 10;
		}break;
	case STRENGTH:
		{
			m_pAttributes->strength += 1;
		}break;
	case ARMOUR:
		{
			m_pAttributes->armour += 3;
		}break;
	case LUCK:
		{
			m_pAttributes->luck += 10;
		}break;
	case MANA:
		{
			m_pAttributes->maxMana += 10;
			m_pAttributes->currentMana += 10;
		}break;
	case HEALTHREGENERATION:
		{
			m_pAttributes->healthRegeneration += 1;
		}break;
	case MANAREGENERATION:
		{
			m_pAttributes->manaRegeneration += 2;
		}break;
	case CRITICALCHANCE:
		{
			m_pAttributes->criticalChance += 5;
		}break;
	case CRITICALDAMAGE:
		{
			m_pAttributes->criticalDamage += 10;
		}break;
	case MAGICPOINTS:
	{
		m_pPlayer->AddMagicPoints(1);
	}break;
	case RECIPESKILL:
		{
			//get a needed recipe
			list<int> neededRecipes = m_pPlayer->GetNotAvailableRecipesList();
			list<int>::iterator a = neededRecipes.begin();
			int randomNumber = rand()%neededRecipes.size();
			for(int i = 0; i < randomNumber; i++)
			{
				a++;
			}
			
			//add the recipe
			CItem *newItem = new CItem;
			newItem->Init(RECIPE);
			newItem->SetSpecialID(*a);
			m_pPlayer->Take(newItem, 1);
		}break;
	};
}