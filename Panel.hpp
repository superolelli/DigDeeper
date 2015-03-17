#ifndef PANEL_HPP
#define PANEL_HPP

#include "Framework.hpp"
#include "Sprite.hpp"
#include "Structures.hpp"

class CPanel
{
public:
	CPanel();
	~CPanel();

	int GetNumber(){return m_Number;}
	int GetType(){return m_PanelType;}
	IntRect GetRect(){return m_pPanel->GetRect();}

	virtual void Init(int _Number, bool _loaded = false) = 0;
	virtual void Quit() = 0;
	virtual void Render() = 0;
	virtual void CheckThings() = 0;
	virtual SItem Take(SItem _item) = 0;
	virtual vector<SItem> GetContent() = 0;


protected:

	friend class boost::serialization::access;

	//save/load the panel
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version) 
	{
		ar & m_Number;
		ar & m_PanelType;
	}

	CSprite *m_pPanel;                   //the sprite for the window
	int m_Number;                          //which Panel is it?
	int m_PanelType;                       //the type of the panel

};



#endif