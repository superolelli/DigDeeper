#ifndef HELPPAGE_HPP
#define HELPPAGE_HPP

#include "Framework.hpp"
#include "Button.hpp"

class CHelpPage
{
public:

	void Init();
	void Run();
	void Quit();


private:

	CButton *m_pQuitButton;

	Text m_text;
	bool is_running;

};



#endif