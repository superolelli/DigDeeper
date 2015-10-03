#include "SoundEngine.hpp"


void CSoundengine::onNotify(int _subject, int _action, int _object)
{
	switch (_action)
	{
		case(O_HIT) :
		{
			if (_subject == O_PLAYER && _object == O_GOBLIN)
				NewSound(&g_pSound->m_hit1);
		}break;

		default:
		{

		}
	}
}




void CSoundengine::NewSound(SoundBuffer *_sound)
{
	Sound *newSound = new Sound;
	newSound->setBuffer(*_sound);
	newSound->setVolume(30);
	newSound->play();

	m_soundList.push_back(newSound);
}




void CSoundengine::CheckAllSounds()
{
	list<Sound*>::iterator i;

	for (i = m_soundList.begin(); i != m_soundList.end(); i++)
	{
		if ((**i).getStatus() == Sound::Stopped)
		{
			SAFE_DELETE(*i);
			i = m_soundList.erase(i);
			continue;
		}
	}
}