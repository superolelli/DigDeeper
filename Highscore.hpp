#ifndef HIGHSCORE_HPP
#define HIGHSCORE_HPP

#include "Framework.hpp"
#include "Button.hpp"
#include "Structures.hpp"


class CHighscore
{
public:
	CHighscore();
	void Init();
	void Run();
	void Quit();


private:

	void RenderHighscore();
	void clearHighscore();

	bool is_running;

	SHighscore m_highscore[10];
	Text m_highscoreText[10];

	CSprite m_background;            //the backgroundsprite
	CButton *m_pReturn_button;         //the return button
	CButton *m_pClear_button;         //the clear button

	int m_mode;
};



#endif