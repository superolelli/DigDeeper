#ifndef EQUIPMENT_HPP
#define EQUIPMENT_HPP


#include "Items.hpp"
#include "Structures.hpp"


class CEquipment : public CItem
{
public:
	CEquipment();
	~CEquipment();

	//inits the equipment
	void InitEquipment(int _ID, bool _loaded = false);
	
	//inits the equipment with additional random values
	void InitEquipmentRandomly(int _ID);

	//renders the equipment
	void RenderEquipment(int _x, int _y, float _frameNumber);

	//returns the sprite
	CSprite *GetEquipmentSprite(){return m_pCarriedEquipmentSprite;}

	//returns the equip id
	int GetEquipID(){return m_EquipID;}

	SToolAttributes GetAttributes(){return m_Attributes;}

	//returns the rarity
	int GetRarity(){return m_rarity;}


private:
	friend class boost::serialization::access;

	//saves the equipment
	template<class Archive>
	void save(Archive & ar, const unsigned int version) const
	{
		ar & boost::serialization::base_object<CItem>(*this);
		ar & m_Attributes;
		ar & m_EquipID;
		ar & m_rarity;
	}

	//load the building menu
	template<class Archive>
	void load(Archive & ar, const unsigned int version) 
	{
		ar & boost::serialization::base_object<CItem>(*this);
		ar & m_Attributes;
		ar & m_EquipID;
		ar & m_rarity;
	}
	BOOST_SERIALIZATION_SPLIT_MEMBER();



	void InitRing();

	CSprite *m_pCarriedEquipmentSprite;                //the sprite shown, when the tool is carried
	SToolAttributes m_Attributes;                   //the attributes of the tool

	int m_EquipID;                                  //shows the part this equipment is used for
	int m_rarity;                                   //how rare is the item?

};

BOOST_CLASS_VERSION(CEquipment, 0)

#endif