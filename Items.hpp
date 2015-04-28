#ifndef ITEMS_HPP
#define ITEMS_HPP

#include "Thing.hpp"


class CItem : public CThing
{
public:
	CItem();
	~CItem();

	void Init(int _ID, bool _loaded = false);
	int GetSpecialID(){return m_specialID;}
	void SetSpecialID(int _ID);

private:
	friend class boost::serialization::access;

	//saves the item
	template<class Archive>
	void save(Archive & ar, const unsigned int version) const
	{
		ar & boost::serialization::base_object<CThing>(*this);
		ar & m_specialID;
	}

	//load the item
	template<class Archive>
	void load(Archive & ar, const unsigned int version) 
	{
		ar & boost::serialization::base_object<CThing>(*this);
		ar & m_specialID;
	}
	BOOST_SERIALIZATION_SPLIT_MEMBER();



	int m_specialID;        //for recipes

	void InitRecipe();
	void InitSpell();


};



#endif