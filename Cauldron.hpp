#ifndef CAUDLRON_HPP
#define CAULDRON_HPP


#include "Panel.hpp"
#include "Thing.hpp"
#include "Items.hpp"
#include "Consumable.hpp"
#include "Button.hpp"
#include "Placeable.hpp"
#include "Tool.hpp"
#include "Equipment.hpp"

class CCauldron : public CPanel
{
public:

	CCauldron();
	~CCauldron();

	void Init(int _number, bool _loaded = false);
	void Quit();
	void Render();
	void CheckThings();
	SItem Take(SItem _item);     //takes an item and returns the item that had to leave the melting menu (if no item was placed it returns NULL)
	vector<SItem> GetContent();



private:
	friend class boost::serialization::access;

	//saves the furnance
	template<class Archive>
	void save(Archive & ar, const unsigned int version) const
	{
		ar & boost::serialization::base_object<CPanel>(*this);
		ar & m_Ingredience[0];
		ar & m_Ingredience[1];
		ar & m_Ingredience[2];
		ar & m_Ingredience[3];
		ar & m_Output;
	}

	//load the furnance
	template<class Archive>
	void load(Archive & ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<CPanel>(*this);
		ar & m_Ingredience[0];
		ar & m_Ingredience[1];
		ar & m_Ingredience[2];
		ar & m_Ingredience[3];
		ar & m_Output;

		Init(m_Number, true);
	}
	BOOST_SERIALIZATION_SPLIT_MEMBER();


	SItem m_Ingredience[4];                //the ingrediences

	SItem m_Output;                       //the output

	CButton *m_pCookingButton;

	Text m_text;                    //the text for writing amounts of things
	Font m_font;

	bool m_cooking;
};

BOOST_CLASS_VERSION(CCauldron, 0)

#endif