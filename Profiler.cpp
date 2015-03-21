#include "Profiler.hpp"




void CProfiler::Init()
{
	//init the text and the font
	m_font.loadFromFile("Data/Fonts/coolsville.ttf");

	m_text.setCharacterSize(18);
	m_text.setColor(Color::Green);
	m_text.setPosition(10, 100);
	m_text.setFont(m_font);

	for (int i = 0; i < PROFILINGVALUES_AMOUNT; i++)
		m_profilingValues[i].str("");

	m_show = false;
}



void CProfiler::Quit()
{
	
}




void CProfiler::SetProfilingValue(int _ID, float _value)
{
	m_profilingValues[_ID] << _value << "\n";
}

void CProfiler::SetProfilingValue(int _ID, int _value)
{
	m_profilingValues[_ID] << _value << "\n";
}



void CProfiler::ShowProfiler()
{
	//if f3 was pressed: set wether the profiler should be shown
	if (g_pFramework->keyStates.f3)
	{
		if (m_show)
			m_show = false;
		else
			m_show = true;
	}

	//render the profiler
	if (m_show)
	{
		string finalString("");

		for (int i = 0; i < PROFILINGVALUES_AMOUNT; i++)
		{
			finalString.append(m_profilingValues[i].str());
		}

		m_text.setString(finalString);
		g_pFramework->GetWindow()->draw(m_text);
	}
}




void CProfiler::ClearProfiler()
{
	m_profilingValues[FPS].str("");
	m_profilingValues[FPS] << "FPS: ";

	m_profilingValues[XPOS].str("");
	m_profilingValues[XPOS] << "X-Position: ";

	m_profilingValues[YPOS].str("");
	m_profilingValues[YPOS] << "Y-Position: ";

	m_profilingValues[NPCAMOUNT].str("");
	m_profilingValues[NPCAMOUNT] << "Amount of NPCs: ";

	m_profilingValues[NIGHTLEVEL].str("");
	m_profilingValues[NIGHTLEVEL] << "Day-Night Timer: ";

	m_profilingValues[MUSICNUMBER].str("");
	m_profilingValues[MUSICNUMBER] << "Current Music: ";

}