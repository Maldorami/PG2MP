#include "Sprite.h"
#include "Animation.h"
#include <d3dx9.h>
//---------------------------------------------------------------------------
void Sprite::setTexture(Texture texture){
	_texture = texture;
}
//---------------------------------------------------------------------------
Sprite::Sprite()
	:
	Entity2D(),
	_texture(NoTexture),
	vertices(new CustomVertexZ[4]),
	_previousFrame(99999),
	_animation(NULL)
{
	vertices[0].x = -0.5;	vertices[0].y = 0.5;	vertices[0].z = 0.0f;
	vertices[1].x = 0.5;	vertices[1].y = 0.5;	vertices[1].z = 0.0f;
	vertices[2].x = -0.5;	vertices[2].y = -0.5;	vertices[2].z = 0.0f;
	vertices[3].x = 0.5;	vertices[3].y = -0.5;	vertices[3].z = 0.0f;

	vertices[0].u = 0.0;	vertices[0].v = 0.0;
	vertices[1].u = 1.0;	vertices[1].v = 0.0;
	vertices[2].u = 0.0;	vertices[2].v = 1.0;
	vertices[3].u = 1.0;	vertices[3].v = 1.0;
	}
//---------------------------------------------------------------------------
Sprite::~Sprite(){
	delete[] vertices;
	vertices = NULL;
}
//---------------------------------------------------------------------------
void Sprite::setTexCoords(float fU1, float fV1, float fU2, float fV2, float fU3, float fV3, float fU4, float fV4){
	vertices[0].u = fU1;
	vertices[0].v = fV1;
	vertices[1].u = fU2;
	vertices[1].v = fV2;
	vertices[2].u = fU3;
	vertices[2].v = fV3;
	vertices[3].u = fU4;
	vertices[3].v = fV4;
}
//---------------------------------------------------------------------------
void Sprite::setTile(float widthT, float heighT, float posX, float posY, float widthF, float heighF){
	vertices[0].u = (posX / widthT);
	vertices[0].v = (posY / heighT);

	vertices[1].u = ((posX + widthF) / widthT);
	vertices[1].v = (posY / heighT);

	vertices[2].u = (posX / widthT);
	vertices[2].v = ((posY + heighF) / heighT);

	vertices[3].u = ((posX + widthF) / widthT);
	vertices[3].v = ((posY + heighF) / heighT);
}
//---------------------------------------------------------------------------
void Sprite::draw(Renderer& renderer) const{
	renderer.setCurrentTexture(_texture);
	renderer.setMatrix(World, _transformationMatrix);
	renderer.draw(vertices, D3DPT_TRIANGLESTRIP, 4);
}
//---------------------------------------------------------------------------
void Sprite::setAnimation(Animation* animation){

	_animation = animation;

}
//---------------------------------------------------------------------------
void Sprite::upDate(Timer& timer){
	if (!_animation){
		return;
	}

	_animation->upDate(timer);
	unsigned int currentFrame = _animation->currentFrame();

	if (currentFrame != _previousFrame){
		const Animation::Frame& frame = _animation->frames()[currentFrame];
		setTexCoords(frame.u1, frame.v1, frame.u2, frame.v2, frame.u3, frame.v3, frame.u4, frame.v4);
	}
}
//---------------------------------------------------------------------------