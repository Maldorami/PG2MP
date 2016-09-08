#include"Map.h"
#include "Renderer.h"
#include "tinyxml2.h" 
//---------------------------------------------------------------------------
 void Map::draw(Renderer& rkRenderer)
 {	 
	 std::vector<Sprite*>::iterator iter;
	 for (size_t i = 0; i < _layers.size(); i++)
	 {
		 for (iter = _layers[i]->_tiles.begin(); iter != _layers[i]->_tiles.end(); iter++)
		 {
			 (*iter)->draw(rkRenderer);
		 }
		 for (iter = _layers[i]->_collisionTiles.begin(); iter != _layers[i]->_collisionTiles.end(); iter++)
		 {
			 (*iter)->draw(rkRenderer);
		 }
	 }
 } 
 //---------------------------------------------------------------------------
 bool Map::importMap(Renderer& Renderer, const std::string& Filename){

	 tinyxml2::XMLDocument XMLDoc;
	 XMLDoc.LoadFile(Filename.c_str());

	 tinyxml2::XMLElement* MapElement = XMLDoc.FirstChildElement("map");

	 _Width = atoi(MapElement->Attribute("width"));
	 _Height = atoi(MapElement->Attribute("height"));
	 
	 _TileWidth = atoi(MapElement->Attribute("tilewidth"));
	 _TileHeight = atoi(MapElement->Attribute("tileheight"));
	 
	 tinyxml2::XMLElement* TilesetElement = MapElement->FirstChildElement("tileset");
	 int firstTileID = atoi(TilesetElement->Attribute("firstgid"));
	 tinyxml2::XMLElement* ImageElement = TilesetElement->FirstChildElement("image");

	 std::string ImagePath = "Assets/";
	 ImagePath += ImageElement->Attribute("source");

	 _texture = Renderer.loadTexture(ImagePath, COLOR_RGB(0, 0, 0));

	 int MapWidth = atoi(ImageElement->Attribute("width"));
	 int MapHeight = atoi(ImageElement->Attribute("height"));
	 setScale((float)MapWidth, (float)MapHeight);

	 int columns = (int) scaleX() / _TileWidth;
	 int rows = (int) scaleY() / _TileHeight;
	 MapWidth = (int) _Width * _TileWidth;
	 MapHeight = (int) _Height * _TileHeight;

	 int maxTiles = atoi(TilesetElement->Attribute("tilecount"));
	 std::map <int, Sprite*> subRects;
	 std::pair<int, Sprite*> tile;

	 std::vector<int> colisionTiles;
	 tinyxml2::XMLElement* tilePropieties = TilesetElement->FirstChildElement("tile");

	 while (tilePropieties){
		 int tileIDCollidable = atoi(tilePropieties->Attribute("id"));
		 colisionTiles.push_back(tileIDCollidable);
		 tilePropieties = tilePropieties->NextSiblingElement("tile");
	 }

	 int x = 0, y = 0, id = 0;
	 do{
		 do{
			 do{
				 Sprite* rect = new Sprite();
				 rect->setTexture(_texture);
				 rect->setTile((float)scaleX(), (float)scaleY(), (float)x * _TileWidth, (float)y * _TileHeight, (float)_TileWidth, (float)_TileHeight);
				 tile.first = id;
				 tile.second = rect;
				 subRects.insert(tile);
				 id++;
				 x++;
			 } while (x < columns);
			 y++;
			 x = 0;
		 } while (y < rows);
	 } while (id < maxTiles);

	 tinyxml2::XMLElement*layerElement;
	 layerElement = MapElement->FirstChildElement("layer");
	 int tileGID = 0, subRectToUse = 0, i = 0, j = 0;
	 while (layerElement)
	 {
		 Layer* layer = new Layer();
		 tinyxml2::XMLElement* layerDataElement = layerElement->FirstChildElement("data");
		 tinyxml2::XMLElement* tileElement = layerDataElement->FirstChildElement("tile");

		 while (tileElement)
		 {
			 tileGID = atoi(tileElement->Attribute("gid"));
			 subRectToUse = tileGID - 1;
			 if (subRectToUse >= 0)
			 {
				 Sprite *asc = new Sprite();
				 asc->ID = subRectToUse;
				 asc->_texture = subRects[subRectToUse]->_texture;
				 asc->vertices = subRects[subRectToUse]->vertices;
				 asc->setScale((float)_TileWidth, (float)_TileHeight);
				 asc->setPos((float)(-MapWidth / 2  + i * _TileWidth), (float)(MapHeight / 2) - j * _TileHeight);

				 bool colisiona = false;
				 for (size_t tmp = 0; tmp < colisionTiles.size(); tmp++)
				 if (subRectToUse == colisionTiles[tmp])
					 colisiona = true;
				 if (colisiona)
					 layer->_collisionTiles.push_back(asc);
				 else
					layer->_tiles.push_back(asc);

			 }

			 tileElement = tileElement->NextSiblingElement("tile");

			 i++;
			 if (i >= _Width)
			 {
				 i = 0;
				 j++;
				 if (j >= _Height)
				 {
					 j = 0;
				 }
			 }
		 }	
		 _layers.push_back(layer);
		 layerElement = layerElement->NextSiblingElement("layer");
	 }
	 return true;
 }
 //---------------------------------------------------------------------------