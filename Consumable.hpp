#ifndef CONSUMABLE_HPP
#define CONSUMABLE_HPP


#include "Items.hpp"
#include "Structures.hpp"


class CConsumable : public CItem
{
public:
	CConsumable();


	//inits the equipment
	void InitConsumable(int _ID);

	SConsumableAttributes GetAttributes(){return m_Attributes;}


private:

	friend class boost::serialization::access;

	//saves the equipment
	template<class Archive>
	void save(Archive & ar, const unsigned int version) const
	{
		ar & boost::serialization::base_object<CItem>(*this);
		ar & m_Attributes;
	}

	//load the building menu
	template<class Archive>
	void load(Archive & ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<CItem>(*this);
		ar & m_Attributes;
	}
	BOOST_SERIALIZATION_SPLIT_MEMBER();



	SConsumableAttributes m_Attributes;

};

BOOST_CLASS_VERSION(CConsumable, 0)

#endif