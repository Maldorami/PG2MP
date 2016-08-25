#ifndef ENTITY2D_H
#define ENTITY2D_H

#include "Mat.h"
#include "Renderer.h"
#include "pg1_timer.h"

#define DLLexport __declspec(dllexport)

class Entity2D{
public:
	DLLexport Entity2D();
	DLLexport virtual ~Entity2D();
	DLLexport void setPos(float fPosX, float fPosY);
	DLLexport void setPos(float fPosX, float fPosY, Timer& timer);
	DLLexport void setRotation(float fRotation);
	DLLexport void setScale(float scaleX, float scaleY);

	DLLexport float posX();
	DLLexport float posY();
	DLLexport float rotation();
	DLLexport float scaleX();
	DLLexport float scaleY();

	DLLexport void flipX(bool state);

//---------------------------------------------------------------------------
	DLLexport enum CollisionResult{
		CollisionVertical,
		CollisionHorizontal,
		NoCollision
	};
	DLLexport CollisionResult checkCollision(Entity2D& entity);
	DLLexport void returnToPoss(float posX, float posY);
	DLLexport float previousPosX();
	DLLexport float previousPosY();
//---------------------------------------------------------------------------

private:
	float _posX, _posY;
	float _previousPosX, _previousPosY;
	float _rotation;
	float _scaleX;
	float _scaleY;
	bool _flipX;
	void updateLocalTransformation();

protected:
	Matrix _transformationMatrix;
};
#endif