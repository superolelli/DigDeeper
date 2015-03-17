#include "SignMachine.hpp"




CSignMachine::CSignMachine()
{
	m_signs.clear();

	m_font.loadFromFile("Data/Fonts/ltromatic.ttf");
	m_text.setCharacterSize(20);
	m_text.setFont(m_font);
	m_text.setColor(Color::Red);
	m_text.setStyle(Text::Bold);
}




void CSignMachine::Quit()
{
	m_signs.clear();
}




void CSignMachine::Render()
{
	list<SSign>::iterator i;
	for(i = m_signs.begin(); i != m_signs.end();)
	{
		//let the string move upwards
		(*i).yPos += -150* g_pTimer->GetElapsedTime().asSeconds();
		

		//sets string and position
		m_text.setString((*i).str);
		m_text.setPosition((*i).xPos, (*i).yPos);

		//renders the text
		g_pFramework->GetWindow()->draw(m_text);

		//subtract the elapsed time
		(*i).time -= g_pTimer->GetElapsedTime().asSeconds();
		if((*i).time <= 0)
		{
			i= m_signs.erase(i);
			continue;
		}

		i++;
	}
}





void CSignMachine::AddString(string _str, float _time, int _x, int _y, Color _color)
{
	SSign sign;
	sign.str = _str;
	sign.time = _time;
	sign.xPos = _x;
	sign.yPos = _y;

	m_signs.push_back(sign);
}