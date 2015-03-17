#include "StringInput.hpp"





CStringInput::CStringInput()
{
	m_str.clear();
}



void CStringInput::Init(Font _font, int _characterSize, int _xPos, int _yPos, Color _colour)
{
	m_font = _font;
	m_text.setCharacterSize(_characterSize);
	m_text.setColor(_colour);
	m_text.setPosition(_xPos, _yPos);
	m_text.setString(m_str);
	m_text.setFont(m_font);

	xPos = _xPos;
	yPos = _yPos;
}


void CStringInput::HandleInput()
{
	//if text was entered
	if(g_pFramework->keyStates.text_entered && m_str.size() < 30)
	{
		if(!g_pFramework->keyStates.backspace)
			m_str += g_pFramework->keyStates.text_input;
		else if(m_str.size() > 0)
			m_str.erase(m_str.end()-1);
	}
	else
	{
		if(g_pFramework->keyStates.backspace && m_str.size() > 0)
			m_str.erase(m_str.end()-1);
	}
}



void CStringInput::Show(RenderTarget* _target)
{
	m_text.setString(m_str);
	m_text.setPosition(xPos - m_text.getGlobalBounds().width/2, yPos);
	_target->draw(m_text);
}