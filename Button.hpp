#ifndef BUTTON_HPP
#define BUTTON_HPP


#include "Framework.hpp"

class CButton
{
public:

	//the constants for the buttontypes
	static const int BUTTONTYPE_UP =          1;
	const static int BUTTONTYPE_DOWN =        2;
	const static int BUTTONTYPE_MOTION_UP =   3;
	const static int BUTTONTYPE_MOTION_DOWN = 4;

	CButton();
    ~CButton();

	//Loads the button, defines the type etc.
	void Load(Texture *_texture, int _x, int _y, int _type);

	//Sets the button's position
	void SetPos(int _x, int _y);

	//renders the button, returns true if button was pressed
	bool Render(int eventtype);

	//gets the rect
	IntRect GetRect(){return m_pButtonSprite->GetRect();}

private:

	CSprite *m_pButtonSprite;               //the buttonsprite
	RenderWindow *m_pRenderWindow;                //the renderwindow
	int m_Buttontype;                       //the buttontype

};




#endif