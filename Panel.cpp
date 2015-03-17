#include "Panel.hpp"




CPanel::CPanel()
{
	m_pPanel = NULL;
	m_Number = 0;
}


CPanel::~CPanel()
{
	SAFE_DELETE(m_pPanel);
}