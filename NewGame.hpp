#ifndef NEWGAME_HPP
#define NEWGAME_HPP


#include "Framework.hpp"
#include "Button.hpp"
#include "StringInput.hpp"
#include "Structures.hpp"

class CNewGame
{
public:

	CNewGame();
	void Init();
	int Run();
	SNewWorldAttributes Quit();

private:

	CSprite *m_pBackground;                           //the background
	CButton *m_pClassLeft;
	CButton *m_pClassRight;
	CButton *m_pWorldLeft;
	CButton *m_pWorldRight;
	CButton *m_pStartGameButton;                       //the button for a new game
	CButton *m_pReturnButton;

	CSprite *m_pClass[4];
	CSprite *m_pWorldSize[3];

	CStringInput m_GameName;                              //the name of the game
	Font m_font;

	int m_class;                                           //currently chosen class
	int m_worldSize;                                         //currently chosen world size

	int m_returnNumber;                                //the number, which is returned
	int m_ButtonEventtype;                           //the event, important for the buttons
	bool is_running;                                 //is it still running?

	void RenderButtons();

};



#endif