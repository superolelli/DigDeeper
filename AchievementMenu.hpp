#ifndef ACHIEVEMENTMENU_HPP
#define ACHIEVEMENTMENU_HPP


#include "Framework.hpp"
#include "Button.hpp"
#include "Structures.hpp"



class CAchievementMenu
{
public:

	CAchievementMenu();
	void Init();
	void Run();
	void Quit();

private:

	CSprite *m_pBackground;                        //the background

	int m_ButtonEventtype;                           //the event, important for the buttons
	bool is_running;                                 //is it still running?

	bool m_achieved[NUMBER_OF_ACHIEVEMENTS];

	CButton *m_pReturnButton;                          //the return button

	void RenderAchievements();

};



#endif