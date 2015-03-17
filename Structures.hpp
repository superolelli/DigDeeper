#ifndef STRUCTURES_HPP
#define STRUCTURES_HPP

#include "Thing.hpp"

struct SPlayerAttributes
{
	//the attributes
	int currentHealth;
	int maxHealth;
	int armour;
	int strength;
	int luck;
	float breakingSpeed;
	int speed;
	int currentMana;
	int maxMana;

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

struct SNpcState
{
	bool idle;
	bool attacking;
	bool going;
};

struct SToolAttributes
{
	float breaking_speed;
	int armour;
	int maxHealth;
	int maxMana;
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
	}
};



struct SNewWorldAttributes
{
	int PlayerClass;
	int WorldSize;
	string GameName;
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
			else if(thing->getID() < ITBREAK)
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
			else if(a < ITBREAK)
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




#endif