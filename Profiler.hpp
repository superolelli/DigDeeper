#ifndef PROFILER_HPP
#define PROFILER_HPP


#include "Framework.hpp"


const int PROFILINGVALUES_AMOUNT = 6;

const int FPS = 0;
const int XPOS = 1;
const int YPOS = 2;
const int NPCAMOUNT = 3;
const int NIGHTLEVEL = 4;
const int MUSICNUMBER = 5;

#define g_pProfiler CProfiler::Get()

class CProfiler : public TSingleton < CProfiler >
{
public:

	void Init();
	void Quit();

	//shows the profiler
	void ShowProfiler();

	//clears the profiler
	void ClearProfiler();

	//sets a specific profiling value
	void SetProfilingValue(int _ID, float _value);
	void SetProfilingValue(int _ID, int _value);


private:

	stringstream m_profilingValues[PROFILINGVALUES_AMOUNT];            //the messages to show
	Text m_text;
	Font m_font;
	bool m_show;

};




#endif