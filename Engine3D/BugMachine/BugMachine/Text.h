#ifndef TEXT_H
#define TEXT_H

#include "Renderer.h"
#include <string>

#define DLLexport __declspec(dllexport)

class Text{
public:
	DLLexport Text();
	DLLexport void createText(int x, int y, int width, int height, int charSize, std::string textFont, std::string text, Renderer& renderer);
	DLLexport void setText(std::string text);
	DLLexport void draw(Renderer& renderer);

private:
	ID3DXFont* _Font;
	RECT _rect;
	std::string _text;
	std::string _textFont;

	int _x;
	int	_y;
	int _width;
	int _height;
	int _charSize;
};
#endif