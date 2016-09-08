#ifndef QUAD_H
#define QUAD_H

#include "RenderTypes.h"
#include "Renderer.h"
#include "Entity2D.h"

#define DLLexport __declspec(dllexport)

class Quad : public Entity2D
{
public:
	DLLexport Quad();
	DLLexport ~Quad();
	DLLexport void draw(Renderer& render) const;

private:
	CustomVertex* m_vertices;
};
#endif