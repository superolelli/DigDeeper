#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP



#pragma region Eventtypes
const int MOUSE_LEFT_UP = 1;
const int MOUSE_RIGHT_UP = 2;
const int MOUSE_LEFT_DOWN = 3;
const int MOUSE_RIGHT_DOWN = 4;
const int E_UP = 5;
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
const int WOOD = 8;
const int FURNANCE = 13;
const int CUPBOARD = 14;
const int DOOR = 15;
const int CHEST = 16;
const int TABLE = 17;
const int LANTERNP = 18;
const int LADDER = 49;

const int PWBREAK = 50;            //the Placeable-Wall-Break shows, where the wall section begins

const int STONEWALL = 51;
const int WOODWALL = 52;
const int MARBLEWALL = 53;

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

const int SPELL = 99;

const int ITBREAK = 100;             //the Item-Tool-Break shows, where the tool section begins

const int PICKAXE = 101;
const int SWORD = 102;
const int LANTERN = 103;

const int TEBREAK = 130;             //the Tool-Equipment-Break shows, where the equipment section begins

const int IRONHELMET = 131;
const int IRONARMOUR = 132;
const int IRONTROUSERS = 133;
const int IRONRING = 134;
const int ARCANUSRING = 135;
const int MAGICHAT = 136;
const int CANDLE = 137;
const int VERYRARERING = 200;

#pragma endregion


#pragma region Npcs

const int BEE = 1;
const int GOBLIN = 2;

#pragma endregion



#pragma region Goblins

const int NORMALGOBLIN = 1;
const int WARRIORGOBLIN = 2;
const int KNIGHTGOBLIN = 3;

#pragma endregion


#pragma region NpcStates

const int IDLE = 1;
const int WALKING = 2;
const int ATTACKING = 3;

#pragma endregion



#pragma region Skills

const int NUMBER_OF_SKILLS = 11;

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

const int AMOUNTOFSPELLS = 1;

const int FIREBALL = 0;

#pragma endregion



#pragma region Projectiles

const int FIREBALLPROJECTILE = 1;
const int EXPLOSION = 2;

#pragma endregion




#endif