#ifndef GAMECHOOSE_HPP
#define GAMECHOOSE_HPP


#include "Framework.hpp"
#include "Button.hpp"
#include "LoadGame.hpp"
#include "NewGame.hpp"



class CGameChoose
{
public:
	
	CGameChoose();
	void Init();
	int Run();
	SNewWorldAttributes Quit();

private:

	CSprite *m_pBackground;                        //the background
	CButton *m_pNewGameButton;                       //the button for a new game
	CButton *m_pLoadGameButton;                       //the button for loading a game
	CButton *m_pMultiplayerButton;                    //the multiplayer button

	SNewWorldAttributes m_newWorldAttributes;

	int m_returnNumber;                                //the number, which is returned
	int m_ButtonEventtype;                           //the event, important for the buttons
	bool is_running;                                 //is it still running?


	void RenderButtons();



};






#endif