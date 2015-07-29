#ifndef FURNANCE_HPP
#define FURNANCE_HPP


#include "Panel.hpp"
#include "Thing.hpp"
#include "Items.hpp"


class CFurnance : public CPanel
{
public:

	CFurnance(int _x, int _y);
	CFurnance(){}
	~CFurnance();

	void Init(int _Number, bool _loaded = false);
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
		ar & m_fBurningTime;
		ar & m_fAnimState;
		ar & m_FurnanceX;
		ar & m_FurnanceY;
		ar & m_BurningMaterial;
		ar & m_ThingToBurn;
		ar & m_Product;
	}

	//load the furnance
	template<class Archive>
	void load(Archive & ar, const unsigned int version) 
	{
		ar & boost::serialization::base_object<CPanel>(*this);
		ar & m_fBurningTime;
		ar & m_fAnimState;
		ar & m_FurnanceX;
		ar & m_FurnanceY;
		ar & m_BurningMaterial;
		ar & m_ThingToBurn;
		ar & m_Product;

		Init(m_Number, true);
	}
	BOOST_SERIALIZATION_SPLIT_MEMBER();


	void ChangeBurningThings();

	SItem m_BurningMaterial;                //the burning material like wood or coal
	SItem m_ThingToBurn;                   //the thing, that is going to be burned or melted 
	SItem m_Product;                     //the thing, that is attached to the mouse currently

	float m_fBurningTime;                   //the time, this thing has burned already
	float m_fAnimState;                        //the current animation state of the furnance

	int m_FurnanceX, m_FurnanceY;                     //the position of the furnance (for rendering smoke)

	Text m_text;                    //the text for writing amounts of things
	Font m_font;

	CSprite m_Smoke;                //the smoke sprite
};

BOOST_CLASS_VERSION(CFurnance, 0)

#endif