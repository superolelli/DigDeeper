#ifndef MINIMAP_HPP
#define MINIMAP_HPP


#include "SFML\Graphics.hpp"
#include "SFML\System.hpp"
#include <vector>


using namespace sf;
using namespace std;


class CMiniMap : public Drawable, public Transformable
{
public:

	void load(vector < vector<int> > _blocks);
	void update(int _x, int _y, int _ID);


private:
	
	virtual void draw(RenderTarget& target, RenderStates states) const
	{
		// apply the transform
		states.transform *= getTransform();

		// apply the tileset texture
		states.texture = NULL;

		// draw the vertex array
		target.draw(m_vertices, states);
	}


	Color GetBlockColor(int _ID);


	VertexArray m_vertices;

	vector <vector<int> > m_blocks;

	int m_xSize, m_ySize;
	int m_tileSize;
};


#endif