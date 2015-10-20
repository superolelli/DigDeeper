#include "Settings.hpp"




CSettings::CSettings()
{
	m_pBackground = NULL;
	m_pReturnButton = NULL;
}




//Load the button textures
void CSettings::Init()
{
	is_running = true;

	m_pBackground = new CSprite;
	m_pBackground->Load(&g_pTextures->t_menuBackground);

	m_pBeamNumbersButton = new CButton;
	m_pInventoryNumbersButton = new CButton;
	m_pFastLightButton = new CButton;

	//load the current settings
	//path Path;
	//Path.append("Data/Settings.stt");

	char* var = getenv("APPDATA");
	boost::filesystem::path Path;
	Path = var;
	Path.append("/Dig Deeper/Settings_02.stt");

	if (boost::filesystem::exists(Path))
	{
		/*ifstream Input(Path.string());
		Input.read((char *)&m_Settings, sizeof(m_Settings));
		Input.close();*/

		ifstream inputFile(Path.string(), ios::binary);
		binary_iarchive settingsArchive(inputFile);
		settingsArchive >> m_Settings;
		inputFile.close();
	}
	else
	{
		m_Settings.m_beam_numbers = false;
		m_Settings.m_inventory_numbers = false;
		m_Settings.m_fast_light = false;
		m_Settings.m_language = GERMAN;
		m_Settings.m_showTime = true;
	}

	//Load the buttons
	if (m_Settings.m_beam_numbers)
		m_pBeamNumbersButton->Load(&g_pTextures->t_optionsButton_beam_on, g_pFramework->GetRenderWindow()->getSize().x / 2 - 100, g_pFramework->GetRenderWindow()->getSize().y / 6, CButton::BUTTONTYPE_MOTION_UP);
	else
		m_pBeamNumbersButton->Load(&g_pTextures->t_optionsButton_beam_off, g_pFramework->GetRenderWindow()->getSize().x / 2 - 100, g_pFramework->GetRenderWindow()->getSize().y / 6, CButton::BUTTONTYPE_MOTION_UP);

	if (m_Settings.m_inventory_numbers)
		m_pInventoryNumbersButton->Load(&g_pTextures->t_optionsButton_inventory_on, g_pFramework->GetRenderWindow()->getSize().x / 2 - 100, 3 * (g_pFramework->GetRenderWindow()->getSize().y / 6), CButton::BUTTONTYPE_MOTION_UP);
	else
		m_pInventoryNumbersButton->Load(&g_pTextures->t_optionsButton_inventory_off, g_pFramework->GetRenderWindow()->getSize().x / 2 - 100, 3 * (g_pFramework->GetRenderWindow()->getSize().y / 6), CButton::BUTTONTYPE_MOTION_UP);

	if (m_Settings.m_fast_light)
		m_pFastLightButton->Load(&g_pTextures->t_optionsButton_fastLight_on, g_pFramework->GetRenderWindow()->getSize().x / 2 - 100, 2 * (g_pFramework->GetRenderWindow()->getSize().y / 6), CButton::BUTTONTYPE_MOTION_UP);
	else
		m_pFastLightButton->Load(&g_pTextures->t_optionsButton_fastLight_off, g_pFramework->GetRenderWindow()->getSize().x / 2 - 100, 2 * (g_pFramework->GetRenderWindow()->getSize().y / 6), CButton::BUTTONTYPE_MOTION_UP);

	m_pReturnButton = new CButton;
	m_pReturnButton->Load(&g_pTextures->t_menuButtonReturn, g_pFramework->GetRenderWindow()->getSize().x / 2 - 100, g_pFramework->GetRenderWindow()->getSize().y - 80, CButton::BUTTONTYPE_MOTION_UP);


}





void CSettings::Quit()
{
	SAFE_DELETE(m_pBackground);
	SAFE_DELETE(m_pBeamNumbersButton);
	SAFE_DELETE(m_pInventoryNumbersButton);
	SAFE_DELETE(m_pFastLightButton);
	SAFE_DELETE(m_pReturnButton);
}





void CSettings::Run()
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
		RenderButtons();


		g_pFramework->Flip();
	}


	//	ofstream Output("Data/Settings.stt");
	char* var = getenv("APPDATA");
	string Path = var;
	Path.append("/Dig Deeper/Settings_02.stt");

	/*ofstream Output(Path);
	Output.write((char *)&m_Settings, sizeof(m_Settings));
	Output.close();*/

	ofstream outputFile(Path, ios::binary);
	outputFile.clear();
	binary_oarchive settingsArchive(outputFile);
	settingsArchive << m_Settings;
	outputFile.close();

}





void CSettings::RenderButtons()
{

	if (m_pBeamNumbersButton->Render(m_ButtonEventtype))
	{
		//change the beam setting
		SAFE_DELETE(m_pBeamNumbersButton);
		m_pBeamNumbersButton = new CButton;

		if (m_Settings.m_beam_numbers)
		{
			m_pBeamNumbersButton->Load(&g_pTextures->t_optionsButton_beam_off, g_pFramework->GetRenderWindow()->getSize().x / 2 - 100, g_pFramework->GetRenderWindow()->getSize().y / 6, CButton::BUTTONTYPE_MOTION_UP);
			m_Settings.m_beam_numbers = false;
		}
		else
		{
			m_pBeamNumbersButton->Load(&g_pTextures->t_optionsButton_beam_on, g_pFramework->GetRenderWindow()->getSize().x / 2 - 100, g_pFramework->GetRenderWindow()->getSize().y / 6, CButton::BUTTONTYPE_MOTION_UP);
			m_Settings.m_beam_numbers = true;
		}
	}




	if (m_pInventoryNumbersButton->Render(m_ButtonEventtype))
	{
		//change the inventory settings
		SAFE_DELETE(m_pInventoryNumbersButton);
		m_pInventoryNumbersButton = new CButton;

		if (m_Settings.m_inventory_numbers)
		{
			m_pInventoryNumbersButton->Load(&g_pTextures->t_optionsButton_inventory_off, g_pFramework->GetRenderWindow()->getSize().x / 2 - 100, 3 * (g_pFramework->GetRenderWindow()->getSize().y / 6), CButton::BUTTONTYPE_MOTION_UP);
			m_Settings.m_inventory_numbers = false;
		}
		else
		{
			m_pInventoryNumbersButton->Load(&g_pTextures->t_optionsButton_inventory_on, g_pFramework->GetRenderWindow()->getSize().x / 2 - 100, 3 * (g_pFramework->GetRenderWindow()->getSize().y / 6), CButton::BUTTONTYPE_MOTION_UP);
			m_Settings.m_inventory_numbers = true;
		}
	}


	if (m_pFastLightButton->Render(m_ButtonEventtype))
	{
		//change the beam setting
		SAFE_DELETE(m_pFastLightButton);
		m_pFastLightButton = new CButton;

		if (m_Settings.m_fast_light)
		{
			m_pFastLightButton->Load(&g_pTextures->t_optionsButton_fastLight_off, g_pFramework->GetRenderWindow()->getSize().x / 2 - 100, 2 * (g_pFramework->GetRenderWindow()->getSize().y / 6), CButton::BUTTONTYPE_MOTION_UP);
			m_Settings.m_fast_light = false;
		}
		else
		{
			m_pFastLightButton->Load(&g_pTextures->t_optionsButton_fastLight_on, g_pFramework->GetRenderWindow()->getSize().x / 2 - 100, 2 * (g_pFramework->GetRenderWindow()->getSize().y / 6), CButton::BUTTONTYPE_MOTION_UP);
			m_Settings.m_fast_light = true;
		}
	}


	if (m_pReturnButton->Render(m_ButtonEventtype) == true)
		is_running = false;
}