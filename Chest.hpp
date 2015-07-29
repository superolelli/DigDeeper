#ifndef CHEST_HPP
#define CHEST_HPP


#include "Panel.hpp"
#include "Thing.hpp"
#include "Items.hpp"
#include "Equipment.hpp"
#include "Tool.hpp"
#include "Consumable.hpp"


class CChest : public CPanel
{
public:

	CChest();
	~CChest();

	void Init(int _Number, bool _loaded = false);
	void Quit();
	void Render();
	void CheckThings();
	void TakeThing(SItem _item);   //takes an item
	SItem Take(SItem _item);     //takes an item of the inventory
	vector<SItem> GetContent();     //returns the content of the chest



private:
		friend class boost::serialization::access;

	//saves the chest
	template<class Archive>
	void save(Archive & ar, const unsigned int version) const
	{
		ar & boost::serialization::base_object<CPanel>(*this);
		ar & m_chest;	
	}

	//load the chest
	template<class Archive>
	void load(Archive & ar, const unsigned int version) 
	{
		cout << "Init loading chest" << endl;
		ar & boost::serialization::base_object<CPanel>(*this);
		ar & m_chest;

		Init(m_Number, true);
		cout << "Loaded chest" << endl;
	}
	BOOST_SERIALIZATION_SPLIT_MEMBER();


	SItem m_chest[5][5];

	Font m_font;                                    //the font
	Font m_tooltipFont;                              //the font for tooltips
	Text m_text;                                    //a text variable to draw text
	Text m_tooltipText;                             //the tooltip text

	RectangleShape m_tooltipBackground;                 //the background for the tooltips

	bool show_tooltip;                          //need to show a tooltip?

};

BOOST_CLASS_VERSION(CChest, 0)

#endif