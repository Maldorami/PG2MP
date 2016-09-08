#ifndef MAP_H
#define MAP_H

#include "Entity2D.h"
#include "RenderTypes.h"
#include <vector>
#include <map>
#include "Sprite.h"

#define DLLexport __declspec(dllexport)

//---------------------------------------------------------------------------
struct Layer{
	std::vector<Sprite*> _tiles;
	std::vector<Sprite*> _collisionTiles;
};
//---------------------------------------------------------------------------

class Map : public Entity2D{
public:
	DLLexport bool importMap(Renderer& Renderer, const std::string& Filename);
	DLLexport void draw(Renderer& rkRenderer);	
	std::vector<Layer*> _layers;

private:
	Texture _texture;
	int _Width, _Height;
	int _TileWidth, _TileHeight;
};
#endif