#ifndef PLAYER_HPP
#define PLAYER_HPP

class CWorld;

#include "Framework.hpp"
#include "Structures.hpp"
#include "Living3Part.hpp"
#include "Inventory.hpp"
#include "BuildingMenu.hpp"
#include "CharacterInfo.hpp"
#include "Beam.hpp"




class CPlayer
{
public:
	CPlayer();
	~CPlayer();
	void Init(int _x, int _y, CWorld *_world, View *_view, int _class);
	void InitLoaded(int _x, int _y, CWorld *_world, View *_view);
	void LoadNewBody(CSprite *_body){m_pDwarf->LoadNewBody(_body);}
	void LoadNewBody(Texture *_body, int _frameWidth, int _frameHeight, int _frameNumber){m_pDwarf->LoadNewBody(_body, _frameWidth, _frameHeight, _frameNumber);} 
	void LoadNewLegs(CSprite *_legs){m_pDwarf->LoadNewLegs(_legs);}
	void LoadNewLegs(Texture *_legs, int _frameWidth, int _frameHeight, int _frameNumber){m_pDwarf->LoadNewLegs(_legs, _frameWidth, _frameHeight, _frameNumber);} 
	void SetPos(float _x, float _y);
	Vector2f CheckMovement();
	void Render();
	void RenderInventory();
	void Take(CThing *_thing, int amount);
	void AddExp(int _exp){m_Attributes.currentExp += _exp;}
	void DoDamage(int _damage){ m_Attributes.currentHealth -= _damage; }
	void ThrowPlayer(bool _left, int _strength);
	int GetHealth(){ return m_Attributes.currentHealth; }
	bool AddRecipe(int _ID){return m_pBuildingMenu->NewRecipe(_ID);}
	list<int> GetNotAvailableRecipesList(){return m_pBuildingMenu->GetNotAvailableRecipes();}
	inline IntRect GetRect(){return m_pDwarf->GetRect();}
	IntRect GetWeaponRect();
	bool GetArmGoingUp(){return m_armGoingUp;}

	SToolAttributes GetPlayerAttributes();

	SToolAttributes m_modifications;                 //the modifications from tools etc.

private:
	friend class boost::serialization::access;

	//saves the player
	template<class Archive>
	void save(Archive & ar, const unsigned int version) const
	{
		ar & m_pInventory;
		ar & m_pBuildingMenu;
		ar & m_Attributes.armour;
		ar & m_Attributes.breakingSpeed;
		ar & m_Attributes.currentExp;
		ar & m_Attributes.currentHealth;
		ar & m_Attributes.currentMana;
		ar & m_Attributes.luck;
		ar & m_Attributes.maxExp;
		ar & m_Attributes.maxHealth;
		ar & m_Attributes.maxMana;
		ar & m_Attributes.speed;
		ar & m_Attributes.strength;
		ar & m_Attributes.criticalChance;
		ar & m_Attributes.criticalDamage;
		ar & m_Attributes.healthRegeneration;
		ar & m_Attributes.manaRegeneration;
		int x = m_pDwarf->GetRect().left;
		int y = m_pDwarf->GetRect().top;
		ar & x;
		ar & y;
	}

	template<class Archive>
	void load(Archive & ar, const unsigned int version)
	{
		ar & m_pInventory;
		ar & m_pBuildingMenu;
		ar & m_Attributes.armour;
		ar & m_Attributes.breakingSpeed;
		ar & m_Attributes.currentExp;
		ar & m_Attributes.currentHealth;
		ar & m_Attributes.currentMana;
		ar & m_Attributes.luck;
		ar & m_Attributes.maxExp;
		ar & m_Attributes.maxHealth;
		ar & m_Attributes.maxMana;
		ar & m_Attributes.speed;
		ar & m_Attributes.strength;
		ar & m_Attributes.criticalChance;
		ar & m_Attributes.criticalDamage;
		ar & m_Attributes.healthRegeneration;
		ar & m_Attributes.manaRegeneration;
		ar & m_loadedPosX;
		ar & m_loadedPosY;
	}
	BOOST_SERIALIZATION_SPLIT_MEMBER();

	struct SHoldingButtons
	{
		CSprite *m_Sprite;
		bool m_isClicked;
	};

	void CalculateAttributes();

	RenderTarget *m_pTarget;                         //the render target
	CWorld *m_pWorld;                                //a pointer to the world

	CLiving3Part *m_pDwarf;                             //the dwarf
	CInventory *m_pInventory;                            //the inventory
	CBuildingMenu *m_pBuildingMenu;                        //the building menu
	CCharacterInfo *m_pCharacterInfo;                        //the character info

	CSprite *m_pPanelBeam;                                  //this is all for the inventory/building/character/magic menu
	SHoldingButtons m_PanelInventory;
	SHoldingButtons m_PanelBuilding;
	SHoldingButtons m_PanelAttributes;
	SHoldingButtons m_PanelMagic;


	SPlayerAttributes m_Attributes;                  //the player's atttributes
	SPlayerState m_State;                              //the player's current state

	CBeam *m_pExpBeam;                                //the exp beam
	CBeam *m_pLifeBeam;                                //the life beam
	CBeam *m_pManaBeam;                                //the mana beam

	bool show_beam_numbers;                           //should the beam numbers be shown?

	int m_loadedPosX, m_loadedPosY;                 //the loaded position of the dwarf

	float m_fXVel, m_fYVel;                             //the x and y velocity
	float m_fAnimState;                                //the current anim state
	float m_fArmAnimState;                              //the current arm animation state
	float m_fWaitToBeat;
	float m_fRegenerationTime;                       

	int m_FallingSpeed;                                 //the speed with wich the dwarf is falling
	int m_SideSpeed;                                    //the speed to one side (e.g. by being hitted)

	bool m_turned_left;                                //is the player turned to the left side?
	bool m_armGoingUp;                                  //is the arm moved up?


	bool CheckCollisions();                                     //Checks, if the player collides with a unpassable
	int CheckCollisionPassable();                               //Checks, if the player collides with a passable (returns ID)
	void CheckXMovement();                                       //Checks the player's movement on the x-axis
	void CheckYMovement();                                       //Checks the player's movement on the y-axis
	void CheckArmAnimation();                                      //checks the state of the arm
};




#endif