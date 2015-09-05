#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP



#pragma region Eventtypes
const int MOUSE_LEFT_UP = 1;
const int MOUSE_RIGHT_UP = 2;
const int MOUSE_LEFT_DOWN = 3;
const int MOUSE_RIGHT_DOWN = 4;
const int E_UP = 5;
#pragma endregion


#pragma region Shaders

const int NO_SHADER = 0;
const int DRUNK = 1;

#pragma endregion



#pragma region LogIDs
const int INFO = 0;
const int ERROR = 1;
const int WARNING = 2;
#pragma endregion



#pragma region IDs
const int ROOMFILL = -1;

const int DIRT = 1;
const int STONE = 2;
const int COALBLOCK = 3;
const int IRONBLOCK = 4;
const int GOLDBLOCK = 5;
const int ARCANUSBLOCK = 6;
const int MARBLE = 7;
const int SULFURBLOCK = 8;
const int SALPETERBLOCK = 9;
const int WOOD = 10;
const int TREETRUNK = 11;
const int TREECROWN = 12;

const int FURNANCE = 13;
const int CUPBOARD = 14;
const int DOOR = 15;
const int CHEST = 16;
const int TABLE = 17;
const int LANTERNP = 18;
const int BEEHOUSE = 19;
const int TORCH = 20;
const int CAULDRON = 21;
const int CLOVERP = 22;
const int RADISHP = 23;
const int MUSHROOMP = 24;
const int STALAGTIT = 25;
const int RUBBISH = 26;
const int BRICKS = 27;
const int PRINCESSCAGE = 28;
const int BEDROCK = 29;
const int BEEHIVEP = 30;
const int LADDER = 49;

const int PWBREAK = 50;            //the Placeable-Wall-Break shows, where the wall section begins

const int STONEWALL = 51;
const int WOODWALL = 52;
const int MARBLEWALL = 53;
const int BRICKWALL = 54;

const int PIBREAK = 55;            //the Placeable-Item-Break shows, where the item section begins

const int COAL = 56;
const int WOODSTAFF = 57;
const int IRONORE = 58;
const int IRON = 59;
const int GOLDORE = 60;
const int GOLD = 61;
const int GLUE = 62;
const int ARCANUS = 63;
const int SLIME = 64;
const int RECIPE = 65;
const int WAX = 66;
const int BEEHIVE = 67;
const int COOKINGBOOK = 68;
const int SAWDUST = 69;
const int DIADOCHIT = 70;
const int DYNAMITE = 71;
const int SULFUR = 72;
const int SALPETER = 73;
const int KEY = 78;

const int SPELL = 79;

const int ICBREAK = 80;              //the Item-Consumable-Break shows, where the consumable section begins

const int HONEY = 81;
const int MEAD = 82;
const int SLIMEPUDDING = 83;
const int CLOVER = 84;
const int RADISH = 85;
const int RADISHSOUP = 86;
const int BREAD = 87;
const int MUSHROOM = 88;

const int CTBREAK = 100;             //the Consumable-Tool-Break shows, where the tool section begins

const int PICKAXE = 101;
const int SWORD = 102;
const int LANTERN = 103;
const int BATTLEAXE = 104;
const int BATTLESTONE = 105;
const int GOBLINDAGGER = 106;

const int TEBREAK = 130;             //the Tool-Equipment-Break shows, where the equipment section begins

const int IRONHELMET = 131;
const int IRONARMOUR = 132;
const int IRONTROUSERS = 133;
const int IRONRING = 134;
const int ARCANUSRING = 135;
const int MAGICHAT = 136;
const int CANDLE = 137;
const int DIADOCHITARMOUR = 138;
const int VERYRARERING = 200;

#pragma endregion


#pragma region Sprite Sheet IDs

const int SHEET_CHEST_CLOSED = 0;
const int SHEET_CHEST_OPEN = 1;
const int SHEET_ARCANUS = 2;
const int SHEET_CUPBOARD = 3;
const int SHEET_FURNANCE = 4;
const int SHEET_DOOR_OPEN = 5;
const int SHEET_DOOR_CLOSED = 6;
const int SHEET_COAL = 7;
const int SHEET_DIRT = 8;
const int SHEET_GOLD = 9;
const int SHEET_IRON = 10;
const int SHEET_LADDER = 11;
const int SHEET_MARBLE = 12;
const int SHEET_STONEWALL1 = 13;
const int SHEET_TABLE = 14;
const int SHEET_LANTERN = 15;
const int SHEET_MARBLEWALL = 16;
const int SHEET_STONE = 17;
const int SHEET_TREECROWN = 18;
const int SHEET_WOODWALL = 19;
const int SHEET_NOTEXTURE = 20;
const int SHEET_STONEWALL2 = 21;
const int SHEET_TREETRUNK = 22;
const int SHEET_WOOD = 23;

#pragma endregion



#pragma region Npcs

const int GOBLIN = -1;

const int BEE = 1;
const int NORMALGOBLIN = 2;
const int WARRIORGOBLIN = 3;
const int KNIGHTGOBLIN = 4;
const int CHESTGOBLIN = 5;
const int MAGEGOBLIN = 6;
const int OGRE = 7;

#pragma endregion


#pragma region NpcStates

const int IDLE = 1;
const int WALKING = 2;
const int ATTACKING = 3;
const int FROZEN = 4;

#pragma endregion



#pragma region Skills

const int NUMBER_OF_SKILLS = 12;

const int RECIPESKILL = 0;
const int SPEED = 1;
const int BREAKINGSPEED = 2;
const int HEALTH = 3;
const int STRENGTH = 4;
const int ARMOUR = 5;
const int LUCK = 6;
const int MANA = 7;
const int HEALTHREGENERATION = 8;
const int MANAREGENERATION = 9;
const int CRITICALCHANCE = 10;
const int CRITICALDAMAGE = 11;
const int MAGICPOINTS = 12;

#pragma endregion


#pragma region Effects

const int NUMBER_OF_EFFECTS = 10;

const int EFFECT_ARMOUR = 0;
const int EFFECT_BREAKINGSPEED = 1;
const int EFFECT_CRITICALCHANCE = 2;
const int EFFECT_CRITICALDAMAGE = 3;
const int EFFECT_DRUNK = 4;
const int EFFECT_HEALTHREGENERATION = 5;
const int EFFECT_LUCK = 6;
const int EFFECT_MANAREGENERATION = 7;
const int EFFECT_SPEED = 8;
const int EFFECT_STRENGTH = 9;

#pragma endregion

#pragma region Equipment

const int HEAD = 1;
const int BODY = 2;
const int LEGS = 3;
const int HAND = 4;

#pragma endregion


#pragma region Panels

const int PANEL_CHEST = 1;
const int PANEL_FURNANCE = 2;
const int PANEL_CAULDRON = 3;
const int PANEL_COOKINGBOOK = 4;

#pragma endregion


#pragma region Classes

const int TEST = 0;
const int MINER = 1;
const int BUILDER = 2;
const int WARRIOR = 3;
const int MAGE = 4;

#pragma endregion


#pragma region Worldsize

const int SMALL = 1;
const int MEDIUM = 2;
const int BIG = 3;
#pragma endregion



#pragma region Spells

const int AMOUNTOFSPELLS = 6;

const int FIREBALL = 0;
const int HEAL = 1;
const int ICE = 2;
const int ALCHEMY = 3;
const int LIGHT = 4;
const int MANASHIELD = 5;

#pragma endregion



#pragma region Projectiles

const int FIREBALLPROJECTILE = 1;
const int EXPLOSION = 2;
const int HEALING = 3;
const int ICEBALLPROJECTILE = 4;
const int ALCHEMYANIMATION = 5;
const int LIGHTSPHERE = 6;
const int RUBBISHANIMATION = 7;
const int DUSTANIMATION = 8;
const int MANASHIELDPROJECTILE = 9;
const int DYNAMITEEFFECT = 10;

#pragma endregion



#pragma region ConsumableRecipes

const int NUMBER_OF_CONRECIPES = 4;

const int CONRECIPES[4][5] = {
	{ HONEY, HONEY, -1, -1, MEAD },
	{SLIME, SLIME, -1, -1, SLIMEPUDDING},
	{RADISH, RADISH, SLIME, -1, RADISHSOUP},
	{SLIME, SAWDUST, -1, -1, BREAD}
};

#pragma endregion



#endif