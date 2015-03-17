#ifndef BUILDINGMENU_HPP
#define BULIDINGMENU_HPP


#include "Framework.hpp"
#include "Inventory.hpp"
#include "Items.hpp"
#include "Tool.hpp"
#include "Equipment.hpp"
#include "Button.hpp"
#include <map>


class CBuildingMenu
{
public:
	CBuildingMenu();
	~CBuildingMenu();
	void Init(CInventory * _inventory);
	void InitLoaded(CInventory *_inventory);
	void Render();

	//opens or closes the building menu
	void SetOpen(bool _open){is_open = _open;}

	//returns wether the building menu is open or closed
	bool GetOpen(){return is_open;}

	//adds if possible a new recipe
	bool NewRecipe(int _ID);

	//returns all the things not in the building menu
	list<int> GetNotAvailableRecipes(){return m_notAvailableRecipes;}


private:
	friend class boost::serialization::access;

	//saves the building menu
	template<class Archive>
	void save(Archive & ar, const unsigned int version) const
	{
		ar & m_notAvailableRecipes;
		ar & m_recipes;
	}

	//load the building menu
	template<class Archive>
	void load(Archive & ar, const unsigned int version) 
	{
		ar & m_notAvailableRecipes;
		ar & m_recipes;
	}
	BOOST_SERIALIZATION_SPLIT_MEMBER();



	//the struct, which contains the ID and name of a thing and the resources required to build it
	struct SBuildingItem
	{
		int ID;
		string Name;
		CSprite *m_pInfoSprite;           //the sprite with information of the thing
		map<int, int> resources;       //first int is id, second int is amount
		int amountOfProducts;          //the amount of things you get by building this

		template<class Archive>
		void serialize(Archive & ar, const unsigned int version)
		{
			ar & ID;
		}
	};

	//Fills the recipe list with the start recipes
	void FillRecipeList();

	//Inits a new recipe, where only the id is given
	void InitRecipe(SBuildingItem *_recipe);

	//shows text messages on the menu
	void ShowText();

	

	CInventory *m_pInventory;
	CButton *m_pBuildButton;              //the button to build something
	CButton *m_pArrowUp;                  //the arrow for scrolling up
	CButton *m_pArrowDown;                //the arrow for scrolling down
	CSprite *m_pBuildingMenu;             //the building menu sprite
	CSprite *m_pThingBackground;          //the background of the things you can build
	

	SBuildingItem m_chosenItem;             //the item currently chosen

	list<SBuildingItem> m_recipes;       //all things the player can build
	list<int> m_notAvailableRecipes;      //all things the player can't build

	Font m_font;                            //the font
	Text m_text;                            //the text to display
	Text m_message; 

	float m_textTime;                          //how long was the text shown already?
	int m_scroll_number;                       //how far has the user scrolled down

	bool is_open;                         //is the window open?
	

	
};

#endif