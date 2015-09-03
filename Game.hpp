#ifndef GAME_HPP
#define GAME_HPP


#include "Framework.hpp"
#include "World.hpp"
#include "Player.hpp"
#include "Placeable.hpp"
#include "NpcMachine.hpp"
#include "Profiler.hpp"
#include "Projectiles.hpp"
#include "StringInput.hpp"
#include "HelpPage.hpp"


class CGame
{
public:

	CGame();
	void Init(SNewWorldAttributes _attributes, bool _loaded = false);
	void Run();
	void Quit();

	void Load(string _path);

private:

	int m_frame;                          //the frames per second
	int m_currentFPS;                        //the current FPS rate
	int m_music;                             //the current music
	float m_seconds;                     //the timer for the frame checking
	float m_zoom;                          //the zoom factor
	bool m_rotatingDown;                  //is the view rotating down?
	string m_Name;                         //the name of the game

	float m_TimeRunning;                        //how long is the game running

	bool is_running;                   //is the game still running?
	bool song_played[10];                //has this song already been played?
	View m_View;                       //the view(camera)
	vector<int> eventtype;             //the eventtype vector

	SSettings m_Settings;

	CSprite *m_pBackground;            //the background
	CSprite *m_pNightSky;               //the sky at night
	CSprite *m_pPauseMenu;             //the pause menu
										//the buttons of the pause menu
	CButton *m_pContinueButton;
	CButton *m_pSaveButton; 
	CButton *m_pQuitButton;

	CWorld *m_pWorld;                       //the world
	CPlayer *m_pPlayer;                      //the player
	CNpcMachine m_NpcMachine;                //the npc machine

	void CheckFps();                    //prints the fps
	void RenderBackground();           //renders the background
	void CheckView();                    //updates the view
	void CheckMusic();                 //checks the music
	void PauseGame();
	void SaveGame();
	void SaveHighscore();
	void ClearHighscore();
	void Zoom();



};


#endif