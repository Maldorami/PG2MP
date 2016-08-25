#ifndef RENDERER_H
#define RENDERER_H

#include "pg2_vertexbuffer.h"
#include "RenderTypes.h"
#include "Mat.h"
#include <string>
#include <vector>

struct IDirect3D9;
struct IDirect3DDevice9;
struct IDirect3DVertexBuffer9;
typedef interface ID3DXFont ID3DXFont;
typedef interface ID3DXFont *LPD3DXFONT;
typedef ID3DXFont* Font;

#define DLLexport __declspec(dllexport)

class Renderer{
public:
	DLLexport void draw(CustomVertexZ* apkVertices, _D3DPRIMITIVETYPE ePrimitive, unsigned int uiVertexCount);
	DLLexport void draw(CustomVertex* apkVertices, _D3DPRIMITIVETYPE ePrimitive, unsigned int uiVertexCount);
	DLLexport const Texture loadTexture(const std::string& fileName, int colorKey);

	Renderer(){};
	bool init(HWND hwnd);
	void beginFrame();
	void endFrame();
	void drawText(ID3DXFont* _Font, std::string& _text, RECT& _rect);

	void setMatrix(MatrixType matris, const Matrix& Matrix);
	~Renderer();

	void setCurrentTexture(const Texture& texture);

	IDirect3DDevice9* d3ddev;

private:
	VertexBuffer* v_buffer;
	VertexBuffer* v_bufferS;
	IDirect3D9* d3d;
	std::vector<Texture> textures;
};
#endif