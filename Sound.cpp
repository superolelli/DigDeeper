#include "Sound.hpp"




//loads all soundss
void SoundLoading::LoadSounds()
{
	m_musicMenu.openFromFile("Data/Music/Music1.ogg");
	m_musicMenu.setLoop(true);

//	m_musicMenu.setVolume(50);

	m_musicGame[0].openFromFile("Data/Music/Music2.ogg");
	m_musicGame[1].openFromFile("Data/Music/Music3.ogg");
	m_musicGame[2].openFromFile("Data/Music/Music4.ogg");
	m_musicGame[3].openFromFile("Data/Music/Music5.ogg");
	m_musicGame[4].openFromFile("Data/Music/Music6.ogg");
	m_musicGame[5].openFromFile("Data/Music/Music7.ogg");
	m_musicGame[6].openFromFile("Data/Music/Music8.ogg");
	m_musicGame[7].openFromFile("Data/Music/Music9.ogg");
	m_musicGame[8].openFromFile("Data/Music/Music10.ogg");
	m_musicGame[9].openFromFile("Data/Music/Music11.ogg");

	for (int i = 0; i < 10; i++)
		m_musicGame[i].setVolume(50);

	m_sound.setVolume(50);

	m_goldSound[0].loadFromFile("Data/Sounds/gold1.ogg");
	m_goldSound[1].loadFromFile("Data/Sounds/gold2.ogg");
	m_goldSound[2].loadFromFile("Data/Sounds/gold3.ogg");

	m_laughSound.loadFromFile("Data/Sounds/laugh.wav");
	m_fanfare.loadFromFile("Data/Sounds/fanfare.wav");
	m_hit1.loadFromFile("Data/Sounds/hit1.wav");
	m_sword1.loadFromFile("Data/Sounds/sword1.wav");
	m_metalSliding.loadFromFile("Data/Sounds/metal1.wav");
	m_footstep.loadFromFile("Data/Sounds/footstep.wav");


	m_buttonClick.loadFromFile("Data/Sounds/button6.wav");
}