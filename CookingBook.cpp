#include "CookingBook.hpp"



void CCookingBook::Quit()
{
	SAFE_DELETE(m_pNextPageLeft);
	SAFE_DELETE(m_pNextPageRight);
}




void CCookingBook::Init(int _Number, bool _loaded)
{
	m_pPanel = new CSprite;
	m_pPanel->Load(&g_pTextures->t_cookingBookWindow);
	m_pPanel->SetPos((int)g_pFramework->GetRenderWindow()->getSize().x / 2 - m_pPanel->GetRect().width / 2, (int)g_pFramework->GetRenderWindow()->getSize().y / 2 - m_pPanel->GetRect().height / 2);

	m_pNextPageLeft = new CButton;
	m_pNextPageLeft->Load(&g_pTextures->t_nextPageLeft, m_pPanel->GetRect().left + 35, m_pPanel->GetRect().top + 450, 3);

	m_pNextPageRight = new CButton;
	m_pNextPageRight->Load(&g_pTextures->t_nextPageRight, m_pPanel->GetRect().left + 710, m_pPanel->GetRect().top + 450, 3);

	m_currentPage = 0;

	if (!_loaded)
	{
		m_Number = _Number;
		m_PanelType = PANEL_COOKINGBOOK;
		cookingRecipes.clear();
		cookingRecipeSprites.clear();

		switch (_Number % 4)
		{
		case(0) :
			AddRecipe(MEAD);
			break;
		case(1) :
			AddRecipe(SLIMEPUDDING);
			break;
		case(2) :
			AddRecipe(RADISHSOUP);
			break;
		case(3) :
			AddRecipe(BREAD);
			break;
		default:
			break;
		}
	}
	else
	{
		vector<int> temp = cookingRecipes;
		cookingRecipes.clear();

		for (int i = 0; i < temp.size(); i++)
			AddRecipe(temp[i]);
	}

}







void CCookingBook::Render()
{
	m_pPanel->Render(g_pFramework->GetRenderWindow());

	if (m_currentPage > 0)
	{
		if (m_pNextPageLeft->Render(g_pFramework->keyStates.leftMouseUp))
			m_currentPage -= 2;
	}
	
	if (m_currentPage < cookingRecipes.size() - 2)
	{
		if (m_pNextPageRight->Render(g_pFramework->keyStates.leftMouseUp))
			m_currentPage += 2;
	}

	if (cookingRecipes.size() >= m_currentPage + 1)
	{
		cookingRecipeSprites[m_currentPage].SetPos(m_pPanel->GetRect().left, m_pPanel->GetRect().top);
		cookingRecipeSprites[m_currentPage].Render(g_pFramework->GetRenderWindow());
	}

	if (cookingRecipes.size() >= m_currentPage + 2)
	{
		cookingRecipeSprites[m_currentPage + 1].SetPos(m_pPanel->GetRect().left + 360, m_pPanel->GetRect().top);
		cookingRecipeSprites[m_currentPage + 1].Render(g_pFramework->GetRenderWindow());
	}
	
}




vector<SItem> CCookingBook::GetContent()
{
	vector<SItem> items;
	
	for (int i = 0; i < cookingRecipes.size(); i++)
	{
		SItem item;
		item.amount = cookingRecipes[i];
		items.push_back(item);
	}

	return items;
}




void CCookingBook::AddRecipe(int _ID)
{
	CSprite sprite;

	for (int i = 0; i < cookingRecipes.size(); i++)
	{
		if (cookingRecipes[i] == _ID)
			return;
	}

	switch (_ID)
	{
	case(MEAD) :
		sprite.Load(&g_pTextures->t_cookingMead);
		cookingRecipeSprites.push_back(sprite);
		cookingRecipes.push_back(MEAD);
		break;
	case(SLIMEPUDDING):
		sprite.Load(&g_pTextures->t_cookingSlimepudding);
		cookingRecipeSprites.push_back(sprite);
		cookingRecipes.push_back(SLIMEPUDDING);
		break;
	case(RADISHSOUP):
		sprite.Load(&g_pTextures->t_cookingRadishsoup);
		cookingRecipeSprites.push_back(sprite);
		cookingRecipes.push_back(RADISHSOUP);
		break;
	case(BREAD) :
		sprite.Load(&g_pTextures->t_cookingBread);
		cookingRecipeSprites.push_back(sprite);
		cookingRecipes.push_back(BREAD);
		break;
	default:
		return;
	}
}