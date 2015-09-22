#ifndef TEXTURES_HPP
#define TEXTURES_HPP




#include"SFML\Graphics.hpp"
#include "SFML\Audio.hpp"
#include "singleton.hpp"

using namespace sf;


//the class for loading all textures at once
#define g_pTextures TextureLoading::Get()
class TextureLoading : public TSingleton<TextureLoading>
{
public:

	//loads all textures
	void LoadTextures();

	//the textures
	Texture t_menuBackground;                //the menu background
	Texture t_menuButtonPlay;                   //the play buttons
	Texture t_menuButtonOptions;                //the Options button
	Texture t_menuButtonHighscore;                 //the highscore button
	Texture t_menuButtonQuit;                 //the quit button
	Texture t_menuButtonDeleteHighscore;         //clears the highscore
	Texture t_menuButtonSaveHighscore;
	Texture t_menuButtonNewGame;               //the new game button
	Texture t_menuButtonLoadGame;             //the load game button
	Texture t_menuButtonMultiplayer;           //the multiplayer button
	Texture t_menuButtonSettings;                //the settings button
	Texture t_menuButtonAchievements;              //the achievements button
	Texture t_menuButtonUpgrades;                   //the upgrades button
	Texture t_menuButtonReturn;                  //the return button
	Texture t_menuButtonLoad;                     //the load button
	Texture t_menuButtonLoadThisGame;             //the button in the load menu
	Texture t_menuButtonDeleteThisGame;           //the button in the load menu
	Texture t_menuButtonUp;
	Texture t_menuButtonDown;
	Texture t_menuButtonBlank;                    //a blank button
	Texture t_optionsButton_beam_on;
	Texture t_optionsButton_beam_off;
	Texture t_optionsButton_inventory_on;
	Texture t_optionsButton_inventory_off;
	Texture t_optionsButton_fastLight_on;
	Texture t_optionsButton_fastLight_off;

	Texture t_newGameBackground;                   //the background of the "New Game" window
	Texture t_newGameButtonLeft;
	Texture t_newGameButtonRight;
	Texture t_newGameSmallWorld;
	Texture t_newGameMediumWorld;
	Texture t_newGameBigWorld;
	Texture t_newGameMiner;
	Texture t_newGameBuilder;
	Texture t_newGameWarrior;
	Texture t_newGameMage;

	Texture t_pauseMenu;                         //the pause menu
	Texture t_pauseMenuContinueButton;            //the buttons of the pause menu
	Texture t_pauseMenuSaveButton;
	Texture t_pauseMenuQuitButton;       

	Texture t_BackgroundDead;
	Texture t_BackgroundWon;

	Texture t_gameBackground;                      //the ingame background
	Texture t_gameNightSky;                          //the sky at night

	Texture t_panelBeam;
	Texture t_buttonInventory;                       //the buttons on the panel beam
	Texture t_buttonBuilding;
	Texture t_buttonAttributes;
	Texture t_buttonMagic;
	Texture t_buttonClose;

	Texture t_inventoryWindow;                     //the inventory
	Texture t_inventoryBeam;                        //the inventory beam
	Texture t_inventoryBeamFrame;                   //the frame, which shows, which item is chosen on the beam 

	Texture t_equipmentWindow;                      //the equipment window

	Texture t_cookingBookWindow;
	Texture t_nextPageLeft;
	Texture t_nextPageRight;
	Texture t_cookingMead;
	Texture t_cookingSlimepudding;
	Texture t_cookingRadishsoup;
	Texture t_cookingBread;

	Texture t_expFrame;                              //the frame of the exp beam
	Texture t_expBeam;                               //the beam, which shows the current exp
	Texture t_lifeFrame;                             //the frame of the life beam
	Texture t_lifeBeam;                              //the beam, which shows the current life
	Texture t_manaBeam;                              //the beam, which shows the current mana

	//the status symbols
	Texture t_status[11];

	Texture t_buildingWindow;                           //the building menu
	Texture t_buildButton;                              //the "build" button
	Texture t_arrowUp;                                   //the arrow up button
	Texture t_arrowDown;                                //the arrow down button
	Texture t_buildThingBackground;                    //the background of the recipes

	Texture t_skillPage;                                //the character window
	Texture t_levelUp;                                  //the level-Up window
	Texture t_levelUp_button;                           //the level up button
	
	//the available skills
	Texture t_newSkillSpeed;                            
	Texture t_newSkillStrength;
	Texture t_newSkillBreakingSpeed;
	Texture t_newSkillHealth;
	Texture t_newSkillArmour;
	Texture t_newSkillLuck;
	Texture t_newSkillMana;
	Texture t_newSkillHealthRegeneration;
	Texture t_newSkillManaRegeneration;
	Texture t_newSkillCriticalChance;
	Texture t_newSkillCriticalDamage;
	Texture t_newSkillMagicPoints;
	Texture t_newSkillRecipe;

	Texture t_furnanceMenu;                                //the melting menu
	Texture t_cauldronMenu;                                 //the cooking menu
	Texture t_cookingButton;

	Texture t_magicMenu;                            //the magic menu
	Texture t_buttonPlus;
	Texture t_spell[6];                             //the buttons for the spells in the menu
	Texture t_fireballLeft;
	Texture t_fireballRight;
	Texture t_explosion;
	Texture t_poisonballLeft;
	Texture t_poisonballRight;
	Texture t_poisonExplosion;
	Texture t_healing;
	Texture t_skeletonEffect;
	Texture t_teleport;
	Texture t_alchemy;
	Texture t_lightsphere;
	Texture t_manashield;
	Texture t_rubbishAnimation;
	Texture t_dynamiteAnimation;
	Texture t_iceballLeft;
	Texture t_iceballRight;
	Texture t_ice_goblin;
	Texture t_ice_bee;
	Texture t_ice_bunny;
	Texture t_ice_ogre;


	//the information for the things
	Texture t_buildingInfo_woodwall;
	Texture t_buildingInfo_stonewall;
	Texture t_buildingInfo_woodstaff;
	Texture t_buildingInfo_pickaxe;
	Texture t_buildingInfo_ladder;
	Texture t_buildingInfo_furnance;
	Texture t_buildingInfo_chest;
	Texture t_buildingInfo_cupboard;
	Texture t_buildingInfo_door;
	Texture t_buildingInfo_glue;
	Texture t_buildingInfo_iron_helmet;
	Texture t_buildingInfo_iron_armour;
	Texture t_buildingInfo_iron_trousers;
	Texture t_buildingInfo_iron_ring;
	Texture t_buildingInfo_arcanus_ring;
	Texture t_buildingInfo_table;
	Texture t_buildingInfo_sword;
	Texture t_buildingInfo_lantern;
	Texture t_buildingInfo_candle;
	Texture t_buildingInfo_marblewall;
	Texture t_buildingInfo_beehouse;
	Texture t_buildingInfo_torch;
	Texture t_buildingInfo_cauldron;
	Texture t_buildingInfo_battleaxe;
	Texture t_buildingInfo_sawdust;
	Texture t_buildingInfo_battlestone;
	Texture t_buildingInfo_diadochitarmour;
	Texture t_buildingInfo_bricks;
	Texture t_buildingInfo_brickwall;
	Texture t_buildingInfo_dynamite;
	Texture t_buildingInfo_leatherarmour;
	Texture t_buildingInfo_leatherhelmet;

	Texture t_blockTextures_dirt;                     //the dirt textures
	Texture t_blockTextures_stone;                      //the stone texture
	Texture t_blockTextures_wood;                           //the wood texture
	Texture t_blockTextures_coalBlock;                     //the coal(block) texture
	Texture t_blockTextures_ironBlock;                     //the iron(block) texture
	Texture t_blockTextures_goldBlock;                      //the gold(block) texture
	Texture t_blockTextures_arcanusBlock;
	Texture t_blockTextures_stoneWall;                     //the stone wall texture
	Texture t_blockTextures_woodWall;
	Texture t_blockTextures_ladder;                   //the ladder texture;
	Texture t_blockTextures_furnance;                 //the furnance texture;
	Texture t_blockTextures_chest;                    //the chest texture
	Texture t_blockTextures_cupboard;                 //the cupboard texture
	Texture t_blockTextures_door;                     //the door texture
	Texture t_blockTextures_table;
	Texture t_blockTextures_lantern;
	Texture t_blockTextures_marble;                   //the marble texture
	Texture t_blockTextures_marblewall;
	Texture t_blockTextures_treetrunk;
	Texture t_blockTextures_treecrown;
	Texture t_blockTextures_beehive_left;
	Texture t_blockTextures_beehive_right;
	Texture t_blockTextures_beehouse;
	Texture t_blockTextures_torch_ground;
	Texture t_blockTextures_torch_wall;
	Texture t_blockTextures_torch_left;
	Texture t_blockTextures_torch_right;
	Texture t_blockTextures_cauldron;
	Texture t_blockTextures_clover;
	Texture t_blockTextures_radish;
	Texture t_blockTextures_mushroom;
	Texture t_blockTextures_stalagtit1;
	Texture t_blockTextures_stalagtit2;
	Texture t_blockTextures_stalagtit3;
	Texture t_blockTextures_stalagtit4;
	Texture t_blockTextures_rubbish;
	Texture t_blockTextures_bedrock;
	Texture t_blockTextures_bricks;
	Texture t_blockTextures_brickwall;
	Texture t_blockTextures_princessCage;
	Texture t_blockTextures_princessCage2;
	Texture t_blockTextures_sulfurBlock;
	Texture t_blockTextures_salpeterBlock[4];
	Texture t_blockTextures_metalbars;
	Texture t_blockTextures_noTexture;               //the no_texture texture

	Texture t_dirtRimTop;
	Texture t_dirtRimBottom;
	Texture t_dirtRimLeft;
	Texture t_dirtRimRight;
	Texture t_stoneRimTop;
	Texture t_stoneRimBottom;
	Texture t_stoneRimLeft;
	Texture t_stoneRimRight;
	Texture t_treeRim;


	//The inventory pictures of the things
	Texture t_blockInventoryTexture_dirt;      
	Texture t_blockInventoryTexture_stone;
	Texture t_blockInventoryTexture_wood;
	Texture t_blockInventoryTexture_coal;
	Texture t_blockInventoryTexture_iron;
	Texture t_blockInventoryTexture_ironOre;
	Texture t_blockInventoryTexture_coalBlock;
	Texture t_blockInventoryTexture_ironBlock;
	Texture t_blockInventoryTexture_gold;
	Texture t_blockInventoryTexture_goldOre;
	Texture t_blockInventoryTexture_goldBlock;
	Texture t_blockInventoryTexture_ladder;
	Texture t_blockInventoryTexture_furnance;
	Texture t_blockInventoryTexture_chest;
	Texture t_blockInventoryTexture_cupboard;
	Texture t_blockInventoryTexture_door;
	Texture t_blockInventoryTexture_stoneWall;       
	Texture t_blockInventoryTexture_woodWall;
	Texture t_blockInventoryTexture_woodStaff;
	Texture t_blockInventoryTexture_pickaxe;
	Texture t_blockInventoryTexture_glue;
	Texture t_blockInventoryTexture_iron_helmet;
	Texture t_blockInventoryTexture_iron_armour;
	Texture t_blockInventoryTexture_iron_trousers;
	Texture t_blockInventoryTexture_iron_ring;
	Texture t_blockInventoryTexture_arcanusBlock;
	Texture t_blockInventoryTexture_arcanusOre;
	Texture t_blockInventoryTexture_arcanus_ring;
	Texture t_blockInventoryTexture_slime;
	Texture t_blockInventoryTexture_recipe;
	Texture t_blockInventoryTexture_table;
	Texture t_blockInventoryTexture_very_rare_ring;
	Texture t_blockInventoryTexture_magic_hat;
	Texture t_blockInventoryTexture_sword;
	Texture t_blockInventoryTexture_lantern;
	Texture t_blockInventoryTexture_candle;
	Texture t_blockInventoryTexture_wax;
	Texture t_blockInventoryTexture_marble;
	Texture t_blockInventoryTexture_marblewall;
	Texture t_blockInventoryTexture_treetrunk;
	Texture t_blockInventoryTexture_treecrown;
	Texture t_blockInventoryTexture_beehive;
	Texture t_blockInventoryTexture_beehouse;
	Texture t_blockInventoryTexture_honey;
	Texture t_blockInventoryTexture_torch;
	Texture t_blockInventoryTexture_cauldron;
	Texture t_blockInventoryTexture_mead;
	Texture t_blockInventoryTexture_slimepudding;
	Texture t_blockInventoryTexture_clover;
	Texture t_blockInventoryTexture_battleaxe;
	Texture t_blockInventoryTexture_radish;
	Texture t_blockInventoryTexture_radishsoup;
	Texture t_blockInventoryTexture_cookingbook;
	Texture t_blockInventoryTexture_bread;
	Texture t_blockInventoryTexture_sawdust;
	Texture t_blockInventoryTexture_mushroom;
	Texture t_blockInventoryTexture_diadochit;
	Texture t_blockInventoryTexture_battlestone;
	Texture t_blockInventoryTexture_diadochitarmour;
	Texture t_blockInventoryTexture_bedrock;
	Texture t_blockInventoryTexture_bricks;
	Texture t_blockInventoryTexture_brickwall;
	Texture t_blockInventoryTexture_dynamite;
	Texture t_blockInventoryTexture_key;
	Texture t_blockInventoryTexture_sulfurBlock;
	Texture t_blockInventoryTexture_salpeterBlock;
	Texture t_blockInventoryTexture_sulfur;
	Texture t_blockInventoryTexture_salpeter;
	Texture t_blockInventoryTexture_goblindagger;
	Texture t_blockInventoryTexture_metalbars;
	Texture t_blockInventoryTexture_leather;
	Texture t_blockInventoryTexture_leatherarmour;
	Texture t_blockInventoryTexture_leatherhelmet;
	Texture t_spellInventoryTexture_fireball;
	Texture t_spellInventoryTexture_heal;
	Texture t_spellInventoryTexture_ice;
	Texture t_spellInventoryTexture_alchemy;
	Texture t_spellInventoryTexture_light;
	Texture t_spellInventoryTexture_manashield;

	//the little item pictures of the things
	Texture t_blockLittleTexture_dirt;
	Texture t_blockLittleTexture_stone;
	Texture t_blockLittleTexture_wood;
	Texture t_blockLittleTexture_coal;
	Texture t_blockLittleTexture_iron;
	Texture t_blockLittleTexture_ironOre;
	Texture t_blockLittleTexture_coalBlock;
	Texture t_blockLittleTexture_ironBlock;
	Texture t_blockLittleTexture_gold;
	Texture t_blockLittleTexture_goldOre;
	Texture t_blockLittleTexture_goldBlock;
	Texture t_blockLittleTexture_ladder;
	Texture t_blockLittleTexture_furnance;
	Texture t_blockLittleTexture_chest;
	Texture t_blockLittleTexture_door;
	Texture t_blockLittleTexture_cupboard;
	Texture t_blockLittleTexture_stoneWall;
	Texture t_blockLittleTexture_woodWall;
	Texture t_blockLittleTexture_woodStaff;
	Texture t_blockLittleTexture_pickaxe;
	Texture t_blockLittleTexture_glue;
	Texture t_blockLittleTexture_iron_helmet;
	Texture t_blockLittleTexture_iron_armour;
	Texture t_blockLittleTexture_iron_trousers;
	Texture t_blockLittleTexture_iron_ring;
	Texture t_blockLittleTexture_arcanusBlock;
	Texture t_blockLittleTexture_arcanusOre;
	Texture t_blockLittleTexture_arcanus_ring;
	Texture t_blockLittleTexture_slime;
	Texture t_blockLittleTexture_recipe;
	Texture t_blockLittleTexture_table;
	Texture t_blockLittleTexture_very_rare_ring;
	Texture t_blockLittleTexture_magic_hat;
	Texture t_blockLittleTexture_sword;
	Texture t_blockLittleTexture_lantern;
	Texture t_blockLittleTexture_candle;
	Texture t_blockLittleTexture_wax;
	Texture t_blockLittleTexture_marble;
	Texture t_blockLittleTexture_marblewall;
	Texture t_blockLittleTexture_beehive;
	Texture t_blockLittleTexture_beehouse;
	Texture t_blockLittleTexture_honey;
	Texture t_blockLittleTexture_torch;
	Texture t_blockLittleTexture_cauldron;
	Texture t_blockLittleTexture_mead;
	Texture t_blockLittleTexture_slimepudding;
	Texture t_blockLittleTexture_clover;
	Texture t_blockLittleTexture_battleaxe;
	Texture t_blockLittleTexture_radish;
	Texture t_blockLittleTexture_radishsoup;
	Texture t_blockLittleTexture_cookingbook;
	Texture t_blockLittleTexture_bread;
	Texture t_blockLittleTexture_sawdust;
	Texture t_blockLittleTexture_mushroom;
	Texture t_blockLittleTexture_diadochit;
	Texture t_blockLittleTexture_battlestone;
	Texture t_blockLittleTexture_diadochitarmour;
	Texture t_blockLittleTexture_bedrock;
	Texture t_blockLittleTexture_bricks;
	Texture t_blockLittleTexture_brickwall;
	Texture t_blockLittleTexture_dynamite;
	Texture t_blockLittleTexture_key;
	Texture t_blockLittleTexture_sulfurBlock;
	Texture t_blockLittleTexture_salpeterBlock;
	Texture t_blockLittleTexture_sulfur;
	Texture t_blockLittleTexture_salpeter;
	Texture t_blockLittleTexture_goblindagger;
	Texture t_blockLittleTexture_metalbars;
	Texture t_blockLittleTexture_magicpoint;
	Texture t_blockLittleTexture_leather;
	Texture t_blockLittleTexture_leatherarmour;
	Texture t_blockLittleTexture_leatherhelmet;


	//the "carried" texture of the tools
    Texture t_tool_pickaxe;
	Texture t_tool_sword;
	Texture t_tool_lantern;
	Texture t_tool_battleaxe;
	Texture t_tool_battlestone;
	Texture t_tool_dynamite;
	Texture t_tool_goblindagger;
	
	//the "carried" texture of the equipment
	Texture t_equipment_iron_helmet;
	Texture t_equipment_iron_armour;
	Texture t_equipment_iron_trousers;
	Texture t_equipment_magic_hat;
	Texture t_equipment_candle;
	Texture t_equipment_diadochitarmour;
	Texture t_equipment_leatherarmour;
	Texture t_equipment_leatherhelmet;

	Texture t_breakingAnimation;                          //the breaking animation for placeables
	Texture t_smoke;                                      //the smoke cloud animation

	Texture t_dwarf_body;                           //the dwarf's body
	Texture t_dwarf_legs;                             //the dwarf's legs
	Texture t_dwarf_arm;                             //the dwarf's arm

	Texture t_bee;                                      //a bee

	Texture t_bunny;

	Texture t_goblin_body;                       //a goblin
	Texture t_goblin_body2;
	Texture t_goblin_body3;
	Texture t_goblin_body4;
	Texture t_goblin_body_chest;
	Texture t_goblin_legs;
	Texture t_goblin_legs2;
	Texture t_goblin_legs3;
	Texture t_goblin_arm;
	Texture t_goblin_arm2;
	Texture t_goblin_arm3;
	Texture t_goblin_arm4;

	Texture t_ogre_body;
	Texture t_ogre_arm;
	Texture t_ogre_legs;
	Texture t_ground_hit;

	Texture t_keykeeper_body;
	Texture t_keykeeper_arm;
	Texture t_keykeeper_legs;

	Texture t_skeleton_body;
	Texture t_skeleton_body2;
	Texture t_skeleton_body3;
	Texture t_skeleton_arm;
	Texture t_skeleton_arm2;
	Texture t_skeleton_legs;

	Shader s_drunkShader;

	Font f_coolsville;
	Font f_ltromatic;
	Font f_cents18; 
};






#endif