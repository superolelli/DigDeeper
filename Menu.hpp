#ifndef MENU_HPP
#define MENU_HPP


#include "Framework.hpp"
#include "Button.hpp"
#include "GameChoose.hpp"
#include "Options.hpp"

class CMenu 
{
public:

	CMenu();
	void Init();
	int Run();
	SNewWorldAttributes Quit();

private:
	
	CSprite * m_pBackground;
	CButton * m_pQuit;                        //the quit button
	CButton * m_pPlay;                        //the play button
	CButton * m_pOptions;                     //the options button

	SNewWorldAttributes m_newWorldAttributes;

	int m_ButtonEventtype;                      //the event important for the buttons
	int m_returnNumber;                          //the number to return
	bool is_running;                                 //is the menu still running?

	void RenderButtons();

};





#endif