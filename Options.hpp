#ifndef OPTIONS_HPP
#define OPTIONS_HPP


#include "Framework.hpp"
#include "Button.hpp"
#include "Structures.hpp"



class COptions
{
public:
	
	COptions();
	void Init();
	void Run();
	void Quit();

private:

	CSprite *m_pBackground;                        //the background

	int m_ButtonEventtype;                           //the event, important for the buttons
	bool is_running;                                 //is it still running?

	SSettings m_Settings;

	CButton *m_pBeamNumbersButton;
	CButton *m_pInventoryNumbersButton;
	CButton *m_pReturnButton;                          //the return button

	void RenderButtons();

};



#endif