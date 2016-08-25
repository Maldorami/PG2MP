#include"Renderer.h"
#include"RenderTypes.h"
//---------------------------------------------------------------------------
#include <d3d9.h>
#pragma comment (lib, "d3d9.lib")

#include <d3dx9.h>
#pragma comment (lib, "d3dx9.lib")
//---------------------------------------------------------------------------
bool Renderer::init(HWND hWnd)
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	d3d->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddev);

	if (hWnd == NULL)
		return false;


	v_buffer = new VertexBuffer(d3ddev,sizeof(CustomVertex),CUSTOMFVF);
	v_bufferS = new VertexBuffer(d3ddev, sizeof(CustomVertexZ), CUSTOMFVFT);

	d3ddev->SetRenderState(D3DRS_LIGHTING, FALSE);

	D3DVIEWPORT9 viewPort;
	d3ddev->GetViewport(&viewPort);

	d3ddev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	d3ddev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	d3ddev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	d3ddev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	d3ddev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);


	float viewPortWidth = static_cast<float> (viewPort.Width);
	float viewPortHeight = static_cast<float> (viewPort.Height);

	D3DXMATRIX projectionMatrix;
    D3DXMatrixPerspectiveLH(&projectionMatrix, viewPortWidth, viewPortHeight, 0.1f, 1000.0f);
	d3ddev->SetTransform(D3DTS_PROJECTION, &projectionMatrix);

	return true;	

}
//---------------------------------------------------------------------------
void Renderer::draw(CustomVertexZ* apkVertices, _D3DPRIMITIVETYPE ePrimitive, unsigned int uiVertexCount)
{
	v_bufferS->bind();
	v_bufferS->draw(apkVertices, ePrimitive, uiVertexCount);
}
//---------------------------------------------------------------------------
void Renderer::draw(CustomVertex* apkVertices, _D3DPRIMITIVETYPE ePrimitive, unsigned int uiVertexCount)
{
	v_buffer->bind();
	v_buffer->draw(apkVertices, ePrimitive, uiVertexCount);
}
//---------------------------------------------------------------------------
void Renderer::beginFrame(){
	d3ddev->BeginScene();
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);	
}
//---------------------------------------------------------------------------
void Renderer::endFrame(){
	d3ddev->EndScene();
	d3ddev->Present(NULL, NULL, NULL, NULL);
}
//---------------------------------------------------------------------------
Renderer::~Renderer()
{
	d3ddev->Release();
	d3d->Release();

	delete v_buffer;
	delete v_bufferS;

	v_buffer = NULL;
	v_bufferS = NULL;

	for (std::vector<Texture>::iterator it = textures.begin(); it != textures.end(); it++){
		(*it)->Release();
		(*it) = NULL;
	}

	textures.clear();
}
//---------------------------------------------------------------------------
void Renderer::setMatrix(MatrixType matris, const Matrix& Matrix){
	d3ddev->SetTransform(D3DTS_WORLD, Matrix);
}
//---------------------------------------------------------------------------
const Texture Renderer::loadTexture(const std::string& fileName, int colorKey){
	IDirect3DTexture9* texture = NULL;

	HRESULT hr = D3DXCreateTextureFromFileEx(
		d3ddev,
		fileName.c_str(),
		0, 0, 0, 0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_FILTER_NONE,
		colorKey,
		NULL,
		NULL,
		&texture
		);

	if (hr != D3D_OK){
		return NoTexture;
	}
	else{
		
		textures.push_back(texture);
		return texture;
	}
}
//---------------------------------------------------------------------------
void Renderer::setCurrentTexture(const Texture& texture){
	d3ddev->SetTexture(0, texture);
}
//---------------------------------------------------------------------------
void Renderer::drawText(ID3DXFont* _Font, std::string& _text, RECT& _rect){
	_Font->DrawTextA(NULL, _text.c_str(), -1, &_rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));
}
//---------------------------------------------------------------------------