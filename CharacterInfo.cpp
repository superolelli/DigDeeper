#include "CharacterInfo.hpp"
#include "Player.hpp"




CCharacterInfo::CCharacterInfo()
{
	m_pCharacterWindow = NULL;
	m_pLevelUp = NULL;
	m_pFirstSkill = NULL;
	m_pSecondSkill = NULL;
	m_pThirdSkill = NULL;
	m_pFourthSkill = NULL;
	m_pLevelUpButton = NULL;
	m_pPlayer = NULL;
}




CCharacterInfo::~CCharacterInfo()
{
	SAFE_DELETE(m_pCharacterWindow);
	SAFE_DELETE(m_pLevelUp);
	SAFE_DELETE(m_pFirstSkill);
	SAFE_DELETE(m_pSecondSkill);
	SAFE_DELETE(m_pThirdSkill);
	SAFE_DELETE(m_pFourthSkill);
	SAFE_DELETE(m_pLevelUpButton);
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
	m_font.loadFromFile("Data/Fonts/18cents.ttf");
	m_text.setFont(m_font);
	m_text.setCharacterSize(30);
	m_text.setColor(Color::Black);

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
		stream.str("");
		stream << m_pModifications->maxHealth;
		m_text.setString(stream.str());
		m_text.setPosition((float)(m_pCharacterWindow->GetRect().left + 280), (float)(m_pCharacterWindow->GetRect().top + 99));
		g_pFramework->GetRenderWindow()->draw(m_text);

		//show the healthregeneration
		stream.str("");
		stream << m_pModifications->healthRegeneration;
		m_text.setString(stream.str());
		m_text.setPosition((float)(m_pCharacterWindow->GetRect().left + 280), (float)(m_pCharacterWindow->GetRect().top + 126));
		g_pFramework->GetRenderWindow()->draw(m_text);

		//show the armour
		stream.str("");
		stream << m_pModifications->armour;
		m_text.setString(stream.str());
		m_text.setPosition((float)(m_pCharacterWindow->GetRect().left + 280), (float)(m_pCharacterWindow->GetRect().top + 158));
		g_pFramework->GetRenderWindow()->draw(m_text);

		//show the strength
		stream.str("");
		stream << m_pModifications->strength;
		m_text.setString(stream.str());
		m_text.setPosition((float)(m_pCharacterWindow->GetRect().left + 280), (float)(m_pCharacterWindow->GetRect().top + 228));
		g_pFramework->GetRenderWindow()->draw(m_text);
		
		//show the critical chance
		stream.str("");
		stream << m_pModifications->criticalChance;
		m_text.setString(stream.str());
		m_text.setPosition((float)(m_pCharacterWindow->GetRect().left + 280), (float)(m_pCharacterWindow->GetRect().top + 254));
		g_pFramework->GetRenderWindow()->draw(m_text);
		
		//show the critical damage
		stream.str("");
		stream << m_pModifications->criticalDamage;
		m_text.setString(stream.str());
		m_text.setPosition((float)(m_pCharacterWindow->GetRect().left + 280), (float)(m_pCharacterWindow->GetRect().top + 287));
		g_pFramework->GetRenderWindow()->draw(m_text);

		//show the luck
		stream.str("");
		stream << m_pModifications->luck;
		m_text.setString(stream.str());
		m_text.setPosition((float)(m_pCharacterWindow->GetRect().left + 280), (float)(m_pCharacterWindow->GetRect().top + 352));
		g_pFramework->GetRenderWindow()->draw(m_text);

		//show the breakingSpeed
		stream.str("");
		stream << m_pModifications->breaking_speed;
		m_text.setString(stream.str());
		m_text.setPosition((float)(m_pCharacterWindow->GetRect().left + 280), (float)(m_pCharacterWindow->GetRect().top + 380));
		g_pFramework->GetRenderWindow()->draw(m_text);

		//show the speed
		stream.str("");
		stream << m_pModifications->speed;
		m_text.setString(stream.str());
		m_text.setPosition((float)(m_pCharacterWindow->GetRect().left + 280), (float)(m_pCharacterWindow->GetRect().top + 412));
		g_pFramework->GetRenderWindow()->draw(m_text);

		//show the mana
		stream.str("");
		stream << m_pModifications->maxMana;
		m_text.setString(stream.str());
		m_text.setPosition((float)(m_pCharacterWindow->GetRect().left + 595), (float)(m_pCharacterWindow->GetRect().top + 100));
		g_pFramework->GetRenderWindow()->draw(m_text);

		//show the manaregeneration
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
		//clears the buttons
		SAFE_DELETE(m_pFirstSkill);
		SAFE_DELETE(m_pSecondSkill);
		SAFE_DELETE(m_pThirdSkill);
		SAFE_DELETE(m_pFourthSkill);

		//loads new buttons
		if (m_pPlayer->GetNotAvailableRecipesList().size() > 0)
		{
			m_pFirstSkill = new CButton;
			m_pFirstSkill->Load(&g_pTextures->t_newSkillRecipe, 0, 0, 1);
			Skills[1] = RECIPESKILL;
		}
		else
			m_pFirstSkill = RandomSkill(0);

		m_pSecondSkill = RandomSkill(1);
		m_pThirdSkill = RandomSkill(2);
		m_pFourthSkill = RandomSkill(3);

		m_pFirstSkill->SetPos(m_pLevelUp->GetRect().left, m_pLevelUp->GetRect().top + 50);
		m_pSecondSkill->SetPos(m_pLevelUp->GetRect().left + 300, m_pLevelUp->GetRect().top + 50);
		m_pThirdSkill->SetPos(m_pLevelUp->GetRect().left, m_pLevelUp->GetRect().top + 250);
		m_pFourthSkill->SetPos(m_pLevelUp->GetRect().left + 300, m_pLevelUp->GetRect().top + 250);

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

	if(m_pFirstSkill->Render(eventtype))
	{
		choosing_skill = false;
		m_levelUpCounter--;
		AddSkill(Skills[0]);
	}

	if(m_pSecondSkill->Render(eventtype))
	{
		choosing_skill = false;
		m_levelUpCounter--;
		AddSkill(Skills[1]);
	}

	if(m_pThirdSkill->Render(eventtype))
	{
		choosing_skill = false;
		m_levelUpCounter--;
		AddSkill(Skills[2]);
	}

	if(m_pFourthSkill->Render(eventtype))
	{
		choosing_skill = false;
		m_levelUpCounter--;
		AddSkill(Skills[3]);
	}
}


//returns a random skill
CButton* CCharacterInfo::RandomSkill(int _skillNumber)
{
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
				newButton->Load(&g_pTextures->t_newSkillSpeed, 0, 0, 1);
		}break;
	case BREAKINGSPEED:
		{
				newButton->Load(&g_pTextures->t_newSkillBreakingSpeed, 0, 0, 1);
		}break;
	case HEALTH:
		{
				newButton->Load(&g_pTextures->t_newSkillHealth, 0, 0, 1);
		}break;
	case STRENGTH:
		{
				newButton->Load(&g_pTextures->t_newSkillStrength, 0, 0, 1);
		}break;
	case ARMOUR:
		{
				newButton->Load(&g_pTextures->t_newSkillArmour, 0, 0, 1);
		}break;
	case LUCK:
		{
				newButton->Load(&g_pTextures->t_newSkillLuck, 0, 0, 1);
		}break;
	case MANA:
		{
				newButton->Load(&g_pTextures->t_newSkillMana, 0, 0, 1);
		}break;
	case HEALTHREGENERATION:
		{
			newButton->Load(&g_pTextures->t_newSkillHealthRegeneration, 0, 0, 1);
		}break;
	case MANAREGENERATION:
		{
			newButton->Load(&g_pTextures->t_newSkillManaRegeneration, 0, 0, 1);
		}break;
	case CRITICALCHANCE:
		{
			newButton->Load(&g_pTextures->t_newSkillCriticalChance, 0, 0, 1);
		}break;
	case CRITICALDAMAGE:
		{
			newButton->Load(&g_pTextures->t_newSkillCriticalDamage, 0, 0, 1);
		}break;
	case MAGICPOINTS:
	{
		newButton->Load(&g_pTextures->t_newSkillMagicPoints, 0, 0, 1);
	}break;
	default:
		{
			cout <<"Couldn't load Skill button!" << endl;
		}break;
	};

	Skills[_skillNumber] = number;

	return newButton;
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
			m_pAttributes->breakingSpeed += 0.2f;
		}break;
    case HEALTH:
		{
			m_pAttributes->maxHealth += 20;
			m_pAttributes->currentHealth += 20;
		}break;
	case STRENGTH:
		{
			m_pAttributes->strength += 2;
		}break;
	case ARMOUR:
		{
			m_pAttributes->armour += 1;
		}break;
	case LUCK:
		{
			m_pAttributes->luck += 1;
		}break;
	case MANA:
		{
			m_pAttributes->maxMana += 10;
			m_pAttributes->currentMana += 10;
		}break;
	case HEALTHREGENERATION:
		{
			m_pAttributes->healthRegeneration += 3;
		}break;
	case MANAREGENERATION:
		{
			m_pAttributes->manaRegeneration += 3;
		}break;
	case CRITICALCHANCE:
		{
			m_pAttributes->criticalChance += 2;
		}break;
	case CRITICALDAMAGE:
		{
			m_pAttributes->criticalDamage += 2;
		}break;
	case MAGICPOINTS:
	{
		m_pPlayer->AddMagicPoints(2);
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