#ifndef LITTLEITEMS_HPP
#define LITTLEITEMS_HPP

#include "Framework.hpp"


class CLittleItem
{
public:

	CLittleItem();
	~CLittleItem();

	void Init(int _ID, int _x, int _y);
	void Render();
	void Quit();

	Vector2f GetVel(){return m_Vel;}
	void SetVel(Vector2f _vel){m_Vel = _vel;}
	void Move();

	int GetID(){return m_ID;}
	IntRect GetRect(){return m_pLittleItemSprite->GetRect();}



private:

	friend class boost::serialization::access;

	//saves the little item
	template<class Archive>
	void save(Archive & ar, const unsigned int version) const
	{
		int xPos, yPos;
		xPos = m_pLittleItemSprite->GetRect().left;
		yPos = m_pLittleItemSprite->GetRect().top;
		ar & m_ID;
		ar & xPos;
		ar & yPos;
	}

	//load the little item
	template<class Archive>
	void load(Archive & ar, const unsigned int version) 
	{
		int xLoaded, yLoaded;
		ar & m_ID;
		ar & xLoaded;
		ar & yLoaded;
		m_loaded = true;
		Init(m_ID, xLoaded, yLoaded);
	}
	BOOST_SERIALIZATION_SPLIT_MEMBER();

	CSprite *m_pLittleItemSprite;                //the sprite
	int m_ID;
	bool m_loaded;                             //was this item loaded the last frame?
	Vector2f m_Vel;

};



#endif