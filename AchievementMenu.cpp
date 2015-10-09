#include "AchievementMenu.hpp"




CAchievementMenu::CAchievementMenu()
{
	m_pBackground = NULL;
	m_pReturnButton = NULL;
}




//Load the button textures
void CAchievementMenu::Init()
{
	is_running = true;

	m_pBackground = new CSprite;
	m_pBackground->Load(&g_pTextures->t_menuBackground);


	char* var = getenv("APPDATA");
	boost::filesystem::path Path;
	Path = var;
	Path.append("/Dig Deeper/Achievements.ach");

	if (boost::filesystem::exists(Path))
	{
		ifstream Input(Path.string());
		Input.read((char *)&m_achieved, sizeof(m_achieved));
		Input.close();
	}
	else
	{
		BOOST_FOREACH(bool b, m_achieved)
			b = false;
	}


	m_pReturnButton = new CButton;
	m_pReturnButton->Load(&g_pTextures->t_menuButtonReturn, g_pFramework->GetRenderWindow()->getSize().x / 2 - 100, g_pFramework->GetRenderWindow()->getSize().y - 80, CButton::BUTTONTYPE_MOTION_UP);


}





void CAchievementMenu::Quit()
{
	SAFE_DELETE(m_pBackground);
	SAFE_DELETE(m_pReturnButton);
}





void CAchievementMenu::Run()
{

	//the loop
	while (is_running == true)
	{
		//Update and clear the Window
		g_pFramework->Update();
		g_pFramework->Clear();

		//get the events
		g_pFramework->ProcessEvents();
		m_ButtonEventtype = 0;

		//If an event happened, important for the buttons, save it (Left mouse up)
		if (g_pFramework->keyStates.leftMouseUp)
			m_ButtonEventtype = MOUSE_LEFT_UP;

		//Render the background
		m_pBackground->Render(g_pFramework->GetRenderWindow());

		//Render the buttons
		RenderAchievements();


		g_pFramework->Flip();
	}


	//	ofstream Output("Data/Settings.stt");
	char* var = getenv("APPDATA");
	string Path = var;
	Path.append("/Dig Deeper/Achievements");

	ofstream Output(Path);
	Output.write((char *)&m_achieved, sizeof(m_achieved));
	Output.close();

}





void CAchievementMenu::RenderAchievements()
{
	if (m_pReturnButton->Render(m_ButtonEventtype) == true)
		is_running = false;
}