#ifndef COOKINGBOOK_HPP
#define COOKINGBOOK_HPP



#include "Panel.hpp"



class CCookingBook : public CPanel
{
public:

	CCookingBook();
	~CCookingBook();

	void Init(int _Number, bool _loaded = false);
	void Quit();
	void Render();
	void CheckThings();
	SItem Take(SItem _item){return _item;}
	vector<SItem> GetContent();



private:
	friend class boost::serialization::access;

	//saves the book
	template<class Archive>
	void save(Archive & ar, const unsigned int version) const
	{
		ar & boost::serialization::base_object<CPanel>(*this);
	}

	//load the book
	template<class Archive>
	void load(Archive & ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<CPanel>(*this);

		Init(m_Number, true);
	}
	BOOST_SERIALIZATION_SPLIT_MEMBER();


	CSprite m_bookSprite; 

	vector<int> cookingRecipes;            //which recipes are in the book?

	Text m_text;                    //the text for writing amounts of things

};


#endif