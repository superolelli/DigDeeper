#ifndef TOOL_HPP
#define TOOL_HPP


#include "Items.hpp"
#include "Structures.hpp"


class CTool : public CItem
{
public:
	CTool();
	~CTool();

	//inits the tool
	void InitTool(int _ID, bool _loaded = false);

	//inits the tool with additional random attributes
	void InitToolRandomly(int _ID);

	//renders the tool
	void RenderTool(int _x, int _y);

	//sets the rotation
	void SetRotation(float _angle);

	SToolAttributes GetAttributes(){return m_Attributes;}

	//returns the rarity
	int GetRarity(){return m_rarity;}

	//gets the rect of the carried tool
	IntRect GetRect();


private:
	friend class boost::serialization::access;

	//saves the equipment
	template<class Archive>
	void save(Archive & ar, const unsigned int version) const
	{
		ar & boost::serialization::base_object<CItem>(*this);
		ar & m_Attributes;
		ar & m_rarity;
		cout << "Tool saved" << endl;
	}

	//load the building menu
	template<class Archive>
	void load(Archive & ar, const unsigned int version) 
	{
		ar & boost::serialization::base_object<CItem>(*this);
		ar & m_Attributes;
		ar & m_rarity;
	}
	BOOST_SERIALIZATION_SPLIT_MEMBER();	



	CSprite *m_pCarriedToolSprite;                //the sprite shown, when the tool is carried
	SToolAttributes m_Attributes;                   //the attributes of the tool

	int m_rarity;                                   //the rarity of the tool
};


#endif