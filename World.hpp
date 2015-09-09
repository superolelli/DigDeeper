#ifndef WORLD_HPP
#define WORLD_HPP


#include "Framework.hpp"
#include "LightMachine.hpp"
#include "Placeable.hpp"
#include "LittleItems.hpp"
#include "Items.hpp"
#include "Tool.hpp"
#include "Equipment.hpp"
#include "Player.hpp"
#include "Panel.hpp"
#include "Furnance.hpp"
#include "Cauldron.hpp"
#include "Chest.hpp"
#include "CookingBook.hpp"
#include "Profiler.hpp"
#include "Projectiles.hpp"
#include "NpcMachine.hpp"

//static const int m_BlocksX = 100;
//static const int m_BlocksY = 54;

class CWorld
{
public:
	CWorld();
	~CWorld();

	void Init(int _width, int _height, View* _view, CNpcMachine* _npcs, bool _fastLight, bool _loaded = false);
	void Render();
	void RenderLight();
	bool CheckPlaceables(IntRect _playerRect, CPlayer *_player);              //returns true if the player won
	void AddLittleItem(int _ID, int _x, int _y, int _amount = 1);
	void AddLittleItem(CThing* _thing, int _x, int _y);

	//checks wether the player would collide with the world
	bool CheckLivingCollision(FloatRect _player);
	int CheckCollisionWithPassable(FloatRect _player);

	//can a living object jump in the given direction?
	bool CheckCanJump(IntRect _living, bool _left);

	//is there a barrier blocking the way?
	bool CheckForBarrier(IntRect _living, bool _left);
	
	//returns the panel on which was clicked
	CPanel* GetPanel(int _number = -1);

	//deletes a panel
	void DeletePanel(int _number);

	//returns a pointer to the light machine
	CLightMachine* GetLightMachine(){return &m_lightMachine;}

	//returns the current alpah value
	int GetNightAlpha(){return m_NightAlpha;}

	//returns the world's dimensions in Blocks
	Vector2i GetDimensions(){return Vector2i(m_BlocksX, m_BlocksY);}

	//places a new thing in the world
	bool PlaceNewThing(int _x, int _y, int _ID, IntRect &_playerRect);

	//returns all places, where a npc could spawn
	vector<Vector2i> GetSpawnPlaces();

	//returns a simple matrix of the current view of the blocks
	vector < vector<SWorldPlace> > GetWorldMatrix(bool _big = false);

	//is this block passable?
	bool isBlockPassable(int _x, int _y);

	//deletes a block
	void DeleteBlock(int _x, int _y);

	//tries alchemy
	void DoAlchemy(int _level);

	//adds a panel and returns it's number (x and y is not necessary for all panels, just type in zero or something like that)
	int AddPanel(int _ID, int _x, int _y);


private:
	friend class boost::serialization::access;

	//saves the world
	template<class Archive>
	void save(Archive & ar, const unsigned int version) const
	{
		//save the dimensions
		ar & m_BlocksX;
		ar & m_BlocksY;
		ar & m_NightAlpha;
		ar & m_fNightTimer;
		ar & m_fSecondTimer;

		//save the blocks
		bool no_block = false;
		bool is_block = true;
		for(int y = 0; y < m_BlocksY; y++)
		{
			for(int x = 0; x < m_BlocksX; x++)
			{
				if(m_pBlocks[x][y] == NULL)
					ar & no_block;
				else
				{
					ar & is_block;
					ar & m_pBlocks[x][y];
				}
			}
		}

		//save the walls
		for(int y = 0; y < m_BlocksY; y++)
		{
			for(int x = 0; x < m_BlocksX; x++)
			{
				if(m_pWalls[x][y] == NULL)
					ar & no_block;
				else
				{
					ar & is_block;
					ar & m_pWalls[x][y];
				}
			}
		}

		//saves the little items
		ar & m_LittleItemList;
		
	//	save the panels
		BOOST_FOREACH(CPanel* p, m_PanelList)
		{
			//save the type
			int d = p->GetType();
			ar & d;

			//save the panel
			if(d == PANEL_CHEST)
			{
				CChest* chest = (CChest*)p;
				ar & chest;
			}
			else if(d == PANEL_FURNANCE)
			{
				CFurnance* furnance = (CFurnance*)p;
				ar & furnance;
			}
			else if (d == PANEL_CAULDRON)
			{
				CCauldron* cauldron = (CCauldron*)p;
				ar & cauldron;
			}
			else if (d == PANEL_COOKINGBOOK)
			{
				CCookingBook* book = (CCookingBook*)p;
				ar & book;
			}
		}

		//save  1000 for checking
	    int a = 1000;
		ar & a;
	}

	template<class Archive>
	void load(Archive & ar, const unsigned int version) 
	{
		//load the dimensions
		ar & m_BlocksX;
		ar & m_BlocksY;
		ar & m_NightAlpha;
		ar & m_fNightTimer;
		ar & m_fSecondTimer;

	m_pBlocks.resize(m_BlocksX);
	for(int i = 0; i < m_BlocksX; i++)
		m_pBlocks[i].resize(m_BlocksY);

	m_pWalls.resize(m_BlocksX);
	for(int i = 0; i < m_BlocksX; i++)
		m_pWalls[i].resize(m_BlocksY);

		//load the blocks
		bool is_block = false;
		for(int y = 0; y < m_BlocksY; y++)
		{
			for(int x = 0; x < m_BlocksX; x++)
			{
				ar & is_block;
				if(!is_block)
					m_pBlocks[x][y] = NULL;
				else
				{
					ar & m_pBlocks[x][y];
					m_pBlocks[x][y]->Init(m_pBlocks[x][y]->getID(), true);
					m_pBlocks[x][y]->SetPos(x*100, y*100);
				}
			}
		}

		//load the walls
		for(int y = 0; y < m_BlocksY; y++)
		{
			for(int x = 0; x < m_BlocksX; x++)
			{
				ar & is_block;
				if(!is_block)
					m_pWalls[x][y] = NULL;
				else
				{
					ar & m_pWalls[x][y];
					m_pWalls[x][y]->Init(m_pWalls[x][y]->getID(), true);
					m_pWalls[x][y]->SetPos(x*100, y*100);
				}
			}
		}

		//loads the little items
		ar & m_LittleItemList;
		cout <<"Going to load the panels" << endl;
		int a;
		//loads the panels
		do{
			ar & a;

			if(a == PANEL_CHEST)
			{
				cout <<"Load chest" << endl;
				CChest* chest;
				ar >> chest;
				chest->Init(0, true);
				m_PanelList.push_back(chest);
				cout <<"Loaded chest" << endl;
			}
			else if(a == PANEL_FURNANCE)
			{
				cout <<"Load furnance" << endl;
				CFurnance* furnance;
				ar >> furnance;
				furnance->Init(0, true);
				m_PanelList.push_back(furnance);
				cout <<"Loaded furnance" << endl;
			}
			else if (a == PANEL_CAULDRON)
			{
				CCauldron* cauldron;
				ar >> cauldron;
				cauldron->Init(0, true);
				m_PanelList.push_back(cauldron);
			}
			else if (a == PANEL_COOKINGBOOK)
			{
				CCookingBook* book;
				ar >> book;
				book->Init(0, true);
				m_PanelList.push_back(book);
			}
		}while(a != 1000);
	}

	BOOST_SERIALIZATION_SPLIT_MEMBER();

	int m_WorldWidth, m_WorldHeight;                            //the world's dimensions
	int m_BlocksX, m_BlocksY;
	int m_NightAlpha;											//the current darkness
	float m_fNightTimer;                                          //the timer for one day-night-cycle
	float m_fSecondTimer;                                         //this timer counts to one second
	vector < vector<CPlaceable*> > m_pBlocks;
	vector < vector<CPlaceable*> > m_pWalls;
	list<CLittleItem> m_LittleItemList;                                //the list with all little items

	bool m_fast_sun;

	list<CPanel*> m_PanelList;                                          //the list with all the existing panels

	CLightMachine m_lightMachine;                                        //the light machine
	View *m_pView;
	CNpcMachine *m_pNpcMachine;

	Sound m_sound;                                                        //the sound played

	//generates a new world
	void GenerateWorld();

	//generates the top layer
	void GenerateTopLayer();

	//generates the mid layer
	list<SRoom> GenerateMidLayer();

	//generates the bottom layer
	void GenerateBottomLayer(list<SRoom> _roomlist);

	//generates a random room
	void GenerateRoom(int _x, int _y);

	//generates a random cave
	Vector2i GenerateCave(int _x, int _y);

	//generates an outer room
	Vector2i GenerateOuterRoom(int _x, int _y);

	//generates a goblin room
	Vector2i GenerateGoblinRoom(int _x, int _y, int _sizeX = -1, int _sizeY = -1, bool _dungeon = false);

	//generates a horizontal connection between two rooms
	void GenerateConnectionHorizontal(int _xStart, int _yStart, int _xEnd, int _yEnd);

	//generates a vertical connection between two rooms
	void GenerateConnectionVertical(int _xStart, int _yStart, int _xEnd, int _yEnd);

	//generates the room with the keykeeper
	void GenerateKeyKeeperRoom();

	//generates the final room
	void GenerateFinalRoom(int _x, int _y, int _xSize);

	//makes a block to a free block with brickwall
	void MakeBrickwall(int _x, int _y);

	//generates a random block
	void GenerateRandomBlock(int _x, int _y);

	//sets a tree
	void SetTree(int _x, int _y);

	//fills a given chest with random items
	void FillChestRandomly(int _chestID);

	//checks little things (falling or lying)
	void CheckLittle();

	//checks if you can place a wall and places it
	bool CanPlaceWall(int _x, int _y, int _ID);


};

BOOST_CLASS_VERSION(CWorld, 0)



#endif