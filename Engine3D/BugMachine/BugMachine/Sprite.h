#ifndef SPRITE_H
#define SPRITE_H

#include "Renderer.h"
#include "Entity2D.h"
#include "Animation.h"

#define DLLexport __declspec(dllexport)

class Sprite : public Entity2D{
public:
	DLLexport Sprite();
	DLLexport ~Sprite();
	DLLexport void setTexture(Texture Texture);
	DLLexport void setTexCoords(float fU1, float fV1, float fU2, float fV2, float fU3, float fV3, float fU4, float fV4);
	DLLexport void draw(Renderer& renderer) const;
	DLLexport void setAnimation(Animation* animation);
	DLLexport void upDate(Timer& timer);

	DLLexport void setTile(float widthT, float heighT, float posX, float posY, float widthF, float heighF);
	int ID;
	Texture _texture;
	CustomVertexZ* vertices;

private:		
	Animation* _animation;
	unsigned int _previousFrame;
};
#endif