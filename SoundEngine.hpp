#ifndef SOUNDENGINE_HPP
#define SOUNDENGINE_HPP

#include <list>
#include "Observer.hpp"
#include "Constants.hpp"
#include "Sound.hpp"

using namespace sf;
using namespace std;


#define SAFE_DELETE(X) {if(X != NULL) {delete(X); X=NULL;}}

class CSoundengine : public CObserver
{
public:

	virtual void onNotify(int _subject, int _action, int _object);

	void CheckAllSounds();


private:

	void NewSound(SoundBuffer *_sound);

	list<Sound*> m_soundList;
};

#endif