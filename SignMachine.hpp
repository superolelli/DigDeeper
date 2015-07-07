#ifndef SIGNMACHINE_HPP
#define SIGNMACHINE_HPP


#include "Framework.hpp"

#define g_pSignMachine CSignMachine::Get()

//The framwork holds the window and processes the events
class CSignMachine : public TSingleton<CSignMachine>
{
public:
	CSignMachine();

	void Quit();
	void Render();
	void AddString(string _str, float _time, int _x, int _y, Color _color=Color::Red);


private:

	struct SSign
	{
		string str;
		float time;
		int xPos;
		int yPos;
		Color color;
	};

	list<SSign> m_signs;               //all the signs to render
	Text m_text;
	Font m_font;


};

#endif