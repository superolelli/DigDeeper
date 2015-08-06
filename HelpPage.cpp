#include "HelpPage.hpp"





void CHelpPage::Init()
{
	m_text.setFont(g_pTextures->f_coolsville);
	m_text.setCharacterSize(35);
	m_text.setColor(Color(150, 150, 0));

	m_pQuitButton = new CButton;
	m_pQuitButton->Load(&g_pTextures->t_menuButtonReturn, g_pFramework->GetWindow()->getSize().x / 2 - 100, g_pFramework->GetWindow()->getSize().y - 100, 3);

	is_running = true;
}




void CHelpPage::Quit()
{
	SAFE_DELETE(m_pQuitButton);
}




void CHelpPage::Run()
{
	stringstream stream;
	stream.str("");

	while (is_running)
	{
		stream.str("");

		g_pFramework->Update();
		g_pFramework->Clear(Color(50, 50 ,200));

		g_pFramework->ProcessEvents();

		stream << "Hilfeseite" << endl;
		m_text.setString(stream.str());
		m_text.setCharacterSize(35);
		m_text.setPosition(Vector2f(g_pFramework->GetWindow()->getSize().x / 2 - m_text.getGlobalBounds().width / 2, 10));
		g_pFramework->GetRenderWindow()->draw(m_text);

		stream.str("");
		stream << "A oder Pfeiltaste 	 : Nach Rechts laufen" << endl;
		stream << "D oder Pfeiltaste 	 : Nach Links laufen" << endl;
		stream << "W, Pfeil-/Leertaste   : Springen" << endl;
		stream << "S                     : Sprung unterbrechen" << endl;
		stream << "E                     : Inventar öffnen/schließen" << endl;
		stream << "B                     : Baumenü öffnen/schließen" << endl;
		stream << "C                     : Charaktermenü öffnen/schließen" << endl;
		stream << "M                     : Magiemenü öffnen/schließen" << endl << endl;
		stream << "Linke Maustaste       : Schlagen (in der Welt), Item auswählen (im Inventar)" << endl;
		stream << "Rechte Maustaste      : Gewähltes Item benutzen, besonderes Objekt benutzen" << endl;
		stream << "Mausrad               : Nächstes/Vorheriges Item auswählen (Inventarleiste)" << endl;
		stream << "1 - 0                 : Bestimmtes Item auswählen(Inventarleiste)" << endl;

		m_text.setString(stream.str());
		m_text.setCharacterSize(25);
		m_text.setPosition(Vector2f(g_pFramework->GetWindow()->getSize().x / 2 - m_text.getGlobalBounds().width / 2, 80));
		g_pFramework->GetRenderWindow()->draw(m_text);

		if (m_pQuitButton->Render(g_pFramework->keyStates.leftMouseUp) == true)
		{
			is_running = false;
		}

		g_pFramework->Flip();
	}
}