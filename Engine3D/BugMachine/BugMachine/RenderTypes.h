#ifndef RENDERTYPES_H
#define RENDERTYPES_H
//---------------------------------------------------------------------------
#include <d3d9.h>
//---------------------------------------------------------------------------
#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_DIFFUSE)
#define CUSTOMFVFT (D3DFVF_XYZ | D3DFVF_TEX1)
//---------------------------------------------------------------------------
class CustomVertex{
public:
	float x, y, z;
	DWORD color;
};
//---------------------------------------------------------------------------
extern const int ColorVertexType;
//---------------------------------------------------------------------------
class CustomVertexZ{
public:
	float x, y, z, u, v;
};
//---------------------------------------------------------------------------
enum Primitive{
	TriangleList = 0,
	TriangleStrip,
	PointList,
	LineList,
	LineStrip,
	TriangleFan,
	PrimitiveCount
};
//---------------------------------------------------------------------------
enum MatrixType
{
	View = 0,
	Projection,
	World,
	MatrixTypeCount
};

//---------------------------------------------------------------------------
struct TexCoordVertex{
	float x;
	float y;
	float z;
	float u;
	float v;
};
//---------------------------------------------------------------------------
typedef IDirect3DTexture9* Texture;
static const Texture NoTexture = NULL;
//---------------------------------------------------------------------------
#define COLOR_RGB(r,g,b) COLOR_ARGB(0xff,r,g,b)
#define COLOR_ARGB(a,r,g,b) ((DWORD)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))
//---------------------------------------------------------------------------
#endif