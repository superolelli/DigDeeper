#ifndef SOUND_HPP
#define SOUND_HPP



#include "SFML\Audio.hpp"
#include "singleton.hpp"

using namespace sf;


//the class for loading all textures at once
#define g_pSound SoundLoading::Get()
class SoundLoading : public TSingleton<SoundLoading>
{
public:

	//loads all sounds
	void LoadSounds();

	//main menu music
	Music m_musicMenu;

	//in-game music
	Music m_musicGame[10];

	Sound m_sound;

	SoundBuffer m_goldSound[3];
	SoundBuffer m_laughSound;
	SoundBuffer m_fanfare;
	SoundBuffer m_hit1;
	SoundBuffer m_sword1;
	SoundBuffer m_metalSliding;
	SoundBuffer m_footstep;

	SoundBuffer m_buttonClick;

};






#endif