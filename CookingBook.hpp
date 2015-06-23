#ifndef COOKINGBOOK_HPP
#define COOKINGBOOK_HPP



#include "Panel.hpp"
#include "Button.hpp"



class CCookingBook : public CPanel
{
public:

	CCookingBook(){};
	~CCookingBook(){};

	void Init(int _Number, bool _loaded = false);
	void Quit();
	void Render();
	void CheckThings(){};
	SItem Take(SItem _item){return _item;}
	vector<SItem> GetContent();

	void AddRecipe(int _ID);

private:
	friend class boost::serialization::access;

	//saves the book
	template<class Archive>
	void save(Archive & ar, const unsigned int version) const
	{
		ar & boost::serialization::base_object<CPanel>(*this);
		ar & cookingRecipes;
	}

	//load the book
	template<class Archive>
	void load(Archive & ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<CPanel>(*this);
		ar & cookingRecipes;

		Init(m_Number, true);
	}
	BOOST_SERIALIZATION_SPLIT_MEMBER();

	CButton *m_pNextPageLeft;
	CButton *m_pNextPageRight;

	vector<int> cookingRecipes;            //which recipes are in the book?
	vector<CSprite> cookingRecipeSprites;

	int m_currentPage;
};


#endif