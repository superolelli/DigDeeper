#ifndef INVENTORY_HPP
#define INVENTORY_HPP

class CWorld;

#include "Framework.hpp"
#include "Thing.hpp"
#include "Placeable.hpp"
#include "PlayerEquipment.hpp"
#include "Panel.hpp"
#include "Structures.hpp"
#include "Consumable.hpp"


class CInventory
{
public:
	CInventory();
	~CInventory();

	//Loads the inventory
	void Load(CWorld *_world, View *_view, CPlayer *_player, bool _beamNumbers, bool _loaded = false);

	//Renders the inventory
	void Render(IntRect &_playerRect);

	//Insert things into the inventory, the amount is normally 1
	bool Take(CThing *_thing, int _amount = 1);

	//deletes a thing in the inventory
	void DeleteThing(int _ID, int _amount);

	//opens or closes the inventory
	void SetOpen(bool _open);

	//returns wether the inventory is open or closed
	bool GetOpen(){return is_open;}

	//returns true, if this amount of the thing is in the inventory
	bool IsAmountOfThing(int _ID, int _amount);

	//returns the rect of the inventory windwo
	IntRect GetRect(){return m_pInventoryWindow->GetRect();}

	//returns the id of the helmet
	int GetHelmetID(){ return m_pEquipment->GetHelmetID(); }

	//returns the currently carried thing
	CThing *GetCarriedThing();

	//returns the sum of all the equipment attributes
	SToolAttributes GetEquipmentAttributes(){return m_pEquipment->GetAttributes();}

	//Renders the equipment
	void RenderEquipment(int _x, int _y, bool _left);

	//is the inventory full?
	bool IsFull();


private:
	friend class boost::serialization::access;

	//saves the inventory
	template<class Archive>
	void save(Archive & ar, const unsigned int version) const
	{
		ar & m_inventory_place_list;
		ar & m_inventory_beam_place_list;
		//saves the things in the inventory
		BOOST_FOREACH(SItem s, m_inventoryList)
		{
			int d = s.thing->getID();
			//save the ID for checking
			ar & d;
			//save the thing
			if(s.thing->getID() < PIBREAK)
			{
				CPlaceable* placeable = (CPlaceable*)s.thing;
				ar & placeable;
			}
			else if(s.thing->getID() < ICBREAK)
			{
				CItem * item = (CItem*)s.thing;
				ar & item;
			}
			else if (s.thing->getID() < CTBREAK)
			{
				CConsumable *con = (CConsumable*)s.thing;
				ar & con;
			}
			else if(s.thing->getID() < TEBREAK)
			{
				CTool * tool = (CTool*)s.thing;
				ar & tool;
			}
			else
			{
				CEquipment *equipment = (CEquipment*)s.thing;
				ar & equipment;
			}
			//save the item's attributes
			ar & s.amount;
			ar & s.position;
			ar & s.is_clicked;
			//save the position of the sprite
			int x,y;
			x = s.thing->GetInventorySprite()->GetRect().left;
			y = s.thing->GetInventorySprite()->GetRect().top;
			ar & x;
			ar & y;
		}
	//	save the value 1000 to show, that here the inventory section ends
		int a = 1000;
		ar << a;

		//saves the equipment
		ar & m_pEquipment;
	}


	//loads the inventory
	template<class Archive>
	void load(Archive & ar, const unsigned int version) 
	{
		ar & m_inventory_place_list;
		ar & m_inventory_beam_place_list;

		int a = -1;
		do
		{
			//load the ID of the next thing
			ar & a;
			if(a < PIBREAK)
			{
				//make a new thing with this ID
				CPlaceable *thing;
				//load the saved values
				ar >> thing;
				//Init the sprites etc.
				thing->Init(a, true);
				//make a new item with this thing
				SItem item;
				item.thing = thing;
				//load the item's values
				ar & item.amount;
				ar & item.position;
				ar & item.is_clicked;
				//load and set the position of the inventory sprite
				int x, y;
				ar & x;
				ar & y;
				item.thing->GetInventorySprite()->SetPos(x, y);
				m_inventoryList.push_back(item);
			}
			else if(a < ICBREAK)
			{
				CItem *thing;
				ar & thing;
				thing->Init(a, true);
				SItem item;
				item.thing = thing;
				ar & item.amount;
				ar & item.position;
				ar & item.is_clicked;
				int x, y;
				ar & x;
				ar & y;
				item.thing->GetInventorySprite()->SetPos(x, y);
				m_inventoryList.push_back(item);
			}
			else if (a < CTBREAK)
			{
				CConsumable *thing;
				ar & thing;
				thing->InitConsumable(a);
				SItem item;
				item.thing = thing;
				ar & item.amount;
				ar & item.position;
				ar & item.is_clicked;
				int x, y;
				ar & x;
				ar & y;
				item.thing->GetInventorySprite()->SetPos(x, y);
				m_inventoryList.push_back(item);
			}
			else if(a < TEBREAK)
			{
				CTool *thing;
				ar & thing;
				thing->InitTool(a, true);
				SItem item;
				item.thing = thing;
				ar & item.amount;
				ar & item.position;
				ar & item.is_clicked;
				int x, y;
				ar & x;
				ar & y;
				item.thing->GetInventorySprite()->SetPos(x, y);
				m_inventoryList.push_back(item);
			}
			else if( a != 1000)
			{
				CEquipment *thing;
				ar & thing;
				thing->InitEquipment(a, true);
				SItem item;
				item.thing = thing;
				ar & item.amount;
				ar & item.position;
				ar & item.is_clicked;
				int x, y;
				ar & x;
				ar & y;
				item.thing->GetInventorySprite()->SetPos(x, y);
				m_inventoryList.push_back(item);
			}

		}while(a != 1000);

		//loads the equipment
		ar & m_pEquipment;
	}
	BOOST_SERIALIZATION_SPLIT_MEMBER();


	//One Place in the inventory
	struct SInventoryPlace
	{
		//the coordinates of the place
		int x;
		int y;

		//is the place filled?
		bool is_filled;

		template<class Archive>
		void serialize(Archive & ar, const unsigned int version)
		{
			ar & x;
			ar & y;
			ar & is_filled;
		}
	};


	SInventoryPlace m_inventory_place_list[5][5];
	SInventoryPlace m_inventory_beam_place_list[10];
	list<SItem> m_inventoryList;
	CSprite * m_pInventoryWindow;                 //the inventory sprite
	CSprite * m_pInventoryBeam;                   //the sprite for the inventory beam
	CSprite * m_pCarriedObjectFrame;              //the frame, which marks the current carried thing
	CPanel *m_pCurrentPanel;                       //the current panel beside the inventory window (e.g. melting menu or chest menu)
	CPlayerEquipment *m_pEquipment;
	CPlayer *m_pPlayer;                              //the player
	Font m_font;                                    //the font
	Font m_tooltipFont;                              //the font for tooltips
	Text m_text;                                    //a text variable to draw text
	Text m_tooltipText;                             //the tooltip text
	RectangleShape m_tooltipBackground;                 //the background for the tooltips
	CWorld *m_world;                                      //a pointer to the world
	View *m_view;                                          //a pointer to the view

	int CarriedObjectFramePos;                //the position of the carried object frame

	bool is_open;                               //is the inventory open?
	bool show_tooltip;                          //need to show a tooltip?
	bool show_beam_numbers;



	void CheckEvents();

};


BOOST_CLASS_VERSION(CInventory, 0)




#endif