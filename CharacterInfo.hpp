#ifndef CHARACTERINFO
#define CHARACTERINFO

#include "Framework.hpp"
#include "Button.hpp"
#include "Structures.hpp"

class CPlayer;

class CCharacterInfo
{
public:

	CCharacterInfo();
	~CCharacterInfo();
	void Init(SPlayerAttributes *_attributes, SToolAttributes *_modifications, CPlayer *_player);
	void Render();

	//opens or closes the character menu
	void SetOpen(bool _open){is_open = _open;}

	//returns wether the character menu is open or closed
	bool GetOpen(){return is_open;}

private:

	void CheckForLevelUp();
	void LevelUp();
	void AddSkill(int _skill);
	CButton* RandomSkill(int _skillNumber);

	CSprite *m_pCharacterWindow;                       //the character info
	CSprite *m_pLevelUp;                               //the levelUp window

	CButton *m_pFirstSkill;                            //the first skill button
	CButton *m_pSecondSkill;                            //the second skill button
	CButton *m_pThirdSkill;                              //the third skill button
	CButton *m_pFourthSkill;                                //the fourth skill button

	SPlayerAttributes *m_pAttributes;                 //the player's attributes
	SToolAttributes *m_pModifications;
	CPlayer *m_pPlayer;

	Font m_font;                                       //the font
	Text m_text;                                       //the text to display

	float m_levelUpTime;                          //the time since the level up window has shown up

	int Skills[4];                                 //the four skills
	bool AllSkills[NUMBER_OF_SKILLS];              //all skills: Are they already used?

	bool is_open;                                     //is the character info open?
	bool level_up;
};



#endif