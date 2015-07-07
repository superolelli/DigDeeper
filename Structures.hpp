#ifndef STRUCTURES_HPP
#define STRUCTURES_HPP

#include "Thing.hpp"

struct SPlayerAttributes
{
	//the attributes
	int currentHealth;
	int maxHealth;
	int healthRegeneration;
	int armour;
	int strength;
	int criticalChance;
	int criticalDamage;
	int luck;
	float breakingSpeed;
	int speed;
	int currentMana;
	int maxMana;
	int manaRegeneration;

	//the experience
	int currentExp;
	int maxExp;
};


struct SPlayerModifications
{
	float breakingSpeed;
	float runningSpeed;
};

struct SPlayerState
{
	bool jumping;
	bool climbing;
	bool breaking;
};



struct SNpcAttributes
{
	int maxHealth;
	int currentHealth;
	int armour;
	int strength;
	int speed;
	int exp;
};


struct SToolAttributes
{
	float breaking_speed;
	int armour;
	int maxHealth;
	int maxMana;
	int healthRegeneration;
	int manaRegeneration;
	int criticalChance;
	int criticalDamage;
	int strength;
	int luck;
	int speed;

	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & breaking_speed;
		ar & armour;
		ar & maxHealth;
		ar & maxMana;
		ar & strength;
		ar & luck;
		ar & speed;
		ar & healthRegeneration;
		ar & manaRegeneration;
		ar & criticalChance;
		ar & criticalDamage;
	}
};



struct SConsumableAttributes
{
	float breaking_speed;
	int armour;
	int health;
	int mana;
	int healthRegeneration;
	int manaRegeneration;
	int criticalChance;
	int criticalDamage;
	int strength;
	int luck;
	int speed;
	float duration;

	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & breaking_speed;
		ar & armour;
		ar & health;
		ar & mana;
		ar & strength;
		ar & luck;
		ar & speed;
		ar & healthRegeneration;
		ar & manaRegeneration;
		ar & criticalChance;
		ar & criticalDamage;
		ar & duration;
	}
};


struct SNewWorldAttributes
{
	int PlayerClass;
	int WorldSize;
	string GameName;
};



struct SWorldPlace
{
	bool passable;
	int xPos;
	int yPos;
	int matrixXPos;
	int matrixYPos;
	int parentX;
	int parentY;
	int pathValue;
	int cost;
};

//const SToolAttributes operator+(SToolAttributes const &lhs, SToolAttributes const &rhs)
//{
//	SToolAttributes temp(lhs);
//
//	temp.armour += rhs.armour;
//	temp.breaking_speed += rhs.breaking_speed;
//
//	return temp;
//}


//one item in the inventory
struct SItem
{
	//the thing, which the item is
	CThing *thing;

	//the amount of the item
	int amount;

	//the position on the beam (if not on the beam it is -1)
	int position;

	bool is_clicked;

	friend class boost::serialization::access;

	//saves the item
	template<class Archive>
	void save(Archive & ar, const unsigned int version) const
	{
		cout <<"About to save an item" << endl;
		if(amount > 0)
		{
			cout << "Amount greater than zero" << endl;
			//show, that the amount is greater than 0
			int d = 1;
			ar & d;

			d = thing->getID();
			//save the ID for checking
			ar & d;
			//save the thing
			cout <<"Going to save the thing now..." << endl;
			if(thing->getID() < PIBREAK)
			{
				CPlaceable* placeable = (CPlaceable*)thing;
				ar & placeable;
			}
			else if(thing->getID() < CTBREAK)
			{
				CItem * item = (CItem*)thing;
				ar & item;
			}
			else if(thing->getID() < TEBREAK)
			{
				CTool * tool = (CTool*)thing;
				ar & tool;
			}
			else
			{
				CEquipment *equipment = (CEquipment*)thing;
				ar & equipment;
			}

			cout << "Saved the thing" << endl;
			//save the item's attributes
			ar & amount;
			ar & position;
			ar & is_clicked;
			//save the position of the sprite
			int x,y;
			x = thing->GetInventorySprite()->GetRect().left;
			y = thing->GetInventorySprite()->GetRect().top;
			ar & x;
			ar & y;
			cout <<"Saved the other attributes" << endl;
		}
		else
		{
			cout <<"Amount not greater than zero" << endl;
			int a = 0;
			ar & a;
		}
	}


	template<class Archive>
	void load(Archive & ar, const unsigned int version) 
	{
		int a = -1;
		//check if the amount is greater than zero
		ar & a;
		if(a > 0)
		{
			//load the ID
			ar & a;
			if(a < PIBREAK)
			{
				//make a new thing with this ID
				CPlaceable *newThing;
				//load the saved values
				ar >> newThing;
				//Init the sprites etc.
				newThing->Init(a, true);
				//load the thing
				thing = newThing;
			}
			else if(a < CTBREAK)
			{
				//make a new thing with this ID
				CItem *newThing;
				//load the saved values
				ar >> newThing;
				//Init the sprites etc.
				newThing->Init(a, true);
				//load the thing
				thing = newThing;
			}
			else if(a < TEBREAK)
			{
				//make a new thing with this ID
				CTool *newThing;
				//load the saved values
				ar >> newThing;
				//Init the sprites etc.
				newThing->InitTool(a, true);
				//load the thing
				thing = newThing;
			}
			else 
			{
				//make a new thing with this ID
				CEquipment *newThing;
				//load the saved values
				ar >> newThing;
				//Init the sprites etc.
				newThing->InitEquipment(a, true);
				//load the thing
				thing = newThing;
			}

			//load the item's values
			ar & amount;
			ar & position;
			ar & is_clicked;
			//load and set the position of the inventory sprite
			int x, y;
			ar & x;
			ar & y;
			thing->GetInventorySprite()->SetPos(x, y);
		}
		else
		{
			amount = 0;
			is_clicked = false;
			position = -1;
			thing = NULL;
		}
	}


	BOOST_SERIALIZATION_SPLIT_MEMBER();

};




struct SHoldingButtons
{
	CSprite *m_Sprite;
	bool m_isClicked;
};


struct SProjectile
{
	CSprite *m_Sprite;
	int m_ID;
	bool m_fromPlayer;
	int m_Damage;
	float m_fFlown;
	int m_flightLength;
	float m_fXVel;
	float m_fYVel;
	float m_fAnimState;
};



struct SEffect
{
	CSprite *m_Sprite;
	float m_fDuration;
	float m_fTimeLeft;


	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & m_fDuration;
		ar & m_fTimeLeft;
	}
};



struct SHighscore
{
	SPlayerAttributes m_attributes;
	int m_level;
	int m_class;
	string m_name;
};



struct SSettings
{
	bool m_beam_numbers;
	bool m_inventory_numbers;
	bool m_fast_light;
};

#endif