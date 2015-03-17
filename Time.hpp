#ifndef TIME_HPP
#define TIME_HPP


#include "singleton.hpp"
#include "SFML\System.hpp"

using namespace sf;

#define g_pTimer CTime::Get()

class CTime : public TSingleton<CTime>
{
public:

	//starts the clock
	CTime();

	//Updates the clock
	void Update();

	//gives the time since the start of the game
	Time GetCurrentTime(){return m_current;}

	//gives the time since the last frame
	Time GetElapsedTime(){return m_elapsed;}
	


private:

	Clock m_clock;
	Time m_current;
	Time m_elapsed;
};






#endif