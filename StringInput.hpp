#ifndef STRINGINPUT_HPP
#define STRINGINPUT_HPP

#include "Framework.hpp"

class CStringInput
{
public:
	CStringInput();
	void Init(Font _font, int _characterSize, int _xPos, int _yPos, Color _colour);
	void Show(RenderTarget *_target);
	void HandleInput();
	string GetString(){return m_str;}
	void SetString(string _str){m_str = _str;}


private:
	string m_str;            //the input string
	Text m_text;
	Font m_font;

	int xPos, yPos;
};


#endif