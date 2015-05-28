#ifndef FRAMEWORK_HPP
#define FRAMEWORK_HPP


#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <list>
#include <boost/filesystem.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/array.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/foreach.hpp>
#include "SFML\Graphics.hpp"
#include "SFML\System.hpp"
#include "SFML\Window.hpp"
#include "SFML\Audio.hpp"
#include "singleton.hpp"
#include "Time.hpp"
#include "Textures.hpp"
#include "Sound.hpp"
#include "Rims.hpp"
#include "Sprite.hpp"
#include "Constants.hpp"
#include "KeyStates.hpp"
#include "Filelogger.hpp"

using namespace std;
using namespace sf;
using namespace boost::filesystem;
using namespace boost::archive;




#define SAFE_DELETE(X) {if(X != NULL) {delete(X); X=NULL;}}



#define g_pFramework CFramework::Get()

//The framwork holds the window and processes the events
class CFramework : public TSingleton<CFramework>
{
public:

	
	 KeyStates keyStates;

	//Inits the window and all the framwork
	void Init();

	//Quits everything safe
	void Quit();

	//Updates the timer 
	void Update();

	//Fills the background black
	void Clear();

	//flips the double-buffer and shows the new frame
	void Flip();

	//returns a list of all events, happened
	void ProcessEvents();

	//applies a shader
	void ApplyShader(int _shader){ m_Shader = _shader; }

	//returns a pointer to the window
	inline RenderWindow *GetWindow(){return m_pRealWindow;}


	inline RenderTexture *GetRenderWindow(){ return m_pWindow; }

	//writes an log entry
	void WriteToLog(int _ID, string _message);

private:

	//the window to render on
	RenderWindow *m_pRealWindow;
	RenderTexture *m_pWindow;

	int m_Shader;

	//the logfile
	ige::FileLogger *m_pMyLog;

	//sets all states to false
	void ClearKeyStates();

};



#endif