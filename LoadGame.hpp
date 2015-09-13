#ifndef LOADGAME_HPP
#define LOADGAME_HPP


#include "Framework.hpp"
#include "Button.hpp"
#include "StringInput.hpp"


class CLoadGame
{
public:

	CLoadGame();
	void Init();
	int Run();
	string Quit();

private:

	struct Savegame
	{
		boost::filesystem::path m_path;
		bool m_clicked;
	};

	CSprite *m_pBackground;                           //the background
	CButton *m_pLoadGameButton;                       //the button for loading a game
	CButton *m_pDeleteGameButton;                       //the button for deleting a game
	CButton *m_pReturnButton;
	CButton *m_pButtonUp;
	CButton *m_pButtonDown;

	list<CSprite*> m_pButtonList;                      //the list with all buttons
	list<Savegame> m_GameNameList;

	Text m_text;
	Font m_font;

	string m_GamePath;

	int m_scrollPosition;                                //the scrolling position
	int m_returnNumber;                                //the number, which is returned
	int m_ButtonEventtype;                           //the event, important for the buttons
	bool is_running;                                 //is it still running?

	void RenderButtons();

};





#endif