#ifndef MAGICMENU_HPP
#define MAGICMENU_HPP


#include "Framework.hpp"
#include "Inventory.hpp"
#include "Button.hpp"

class CMagicMenu
{
public:
	CMagicMenu();
	~CMagicMenu();
	void Init(CInventory * _inventory, bool _loaded = false);
	void Render();

	//opens or closes the building menu
	void SetOpen(bool _open){ is_open = _open; }

	//returns wether the building menu is open or closed
	bool GetOpen(){ return is_open; }

	//cast a spell
	void CastSpell(int _ID);


private:

	bool is_open;

	CInventory *m_pInventory;

	CSprite *m_pMagicMenu;
	CButton *m_pPlus;
	SHoldingButtons m_Spells[AMOUNTOFSPELLS];
	int m_SpellLevel[AMOUNTOFSPELLS];

	Text m_text;                            //the text to display
	Text m_levelText;
	int m_MagicPoints;

};



#endif