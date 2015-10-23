#include "Minimap.hpp"





void CMiniMap::load(vector <vector<int> > _blocks)
{
	m_xSize = _blocks.size();
	m_ySize = _blocks[0].size();
	m_tileSize = 10;

	//set the size of the matrix
	m_blocks.resize(m_xSize);
	for (int i = 0; i < m_xSize; i++)
		m_blocks[i].resize(m_ySize);

	m_blocks = _blocks;

	m_vertices.setPrimitiveType(Quads);
	m_vertices.resize(m_xSize * m_ySize * 4);



	for (unsigned int i = 0; i < m_xSize; ++i)
	{
		for (unsigned int j = 0; j < m_ySize; ++j)
		{
			// get a pointer to the current tile's quad
			Vertex* quad = &m_vertices[(i + j * m_xSize) * 4];

			// define its 4 corners
			quad[0].position = Vector2f(i * m_tileSize, j * m_tileSize);
			quad[1].position = Vector2f((i + 1) * m_tileSize, j * m_tileSize);
			quad[2].position = Vector2f((i + 1) * m_tileSize, (j + 1) * m_tileSize);
			quad[3].position = Vector2f(i * m_tileSize, (j + 1) * m_tileSize);

			quad->color = GetBlockColor(m_blocks[i][j]);
		}
	}

}






void CMiniMap::update(int _x, int _y, int _ID)
{
	//set the new ID
	m_blocks[_x][_y] = _ID;

	// get a pointer to the current tile's quad
	Vertex* quad = &m_vertices[(_x + _y * m_xSize) * 4];

	//set the new color
	quad->color = GetBlockColor(m_blocks[_x][_y]);
}





Color CMiniMap::GetBlockColor(int _ID)
{
	return Color::Black;
}