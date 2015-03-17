#ifndef PLAYEREQUIPMENT_HPP
#define PLAYEREQUIPMENT_HPP

class CPlayer;

#include "Panel.hpp"
#include "Equipment.hpp"

class CPlayerEquipment : public CPanel
{
public:

	CPlayerEquipment();
	~CPlayerEquipment();

	void Init(int _Number, bool _loaded){}

	void InitPlayerEquipment(int _Number, CPlayer *_player);

	//Renders the window
	void Render();

	//Renders the equipment
	void RenderEquipment(int _x, int _y, bool _left);

	//returns the id of the helmet
	int GetHelmetID();

	//does nothing
	void CheckThings();
	void SetPos(int _x, int _y);
	SItem Take(SItem _item); 

	SToolAttributes GetAttributes();

private:
	friend class boost::serialization::access;

	//saves/loads the equipment
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version) 
	{
			ar & m_helmet;
			ar & m_body;
			ar & m_trousers;
			ar & m_ring1;
			ar & m_ring2;
	}


	SItem m_helmet;        //the helmet
	SItem m_body;          //the clothing weared
	SItem m_trousers;      //the trousers
	SItem m_ring1;         //the first ring
	SItem m_ring2;        //the second ring

	CPlayer *m_pPlayer;
};


#endif