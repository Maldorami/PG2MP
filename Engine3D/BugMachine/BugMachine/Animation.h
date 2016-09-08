#ifndef ANIMATION_H
#define ANIMATION_H

#include "pg1_timer.h"
#include <vector>

#define DLLexport __declspec(dllexport)

class Animation{
public:

//---------------------------------------------------------------------------
	struct Frame{
		float u1, v1, 
			  u2, v2, 
			  u3, v3,
			  u4, v4;
	};
//---------------------------------------------------------------------------

	DLLexport unsigned int currentFrame() const;
	DLLexport const std::vector<Frame>& frames() const;
	DLLexport void addFrame(float widthT, float heighT, float posX, float posY, float widthF, float heighF);
	DLLexport void setLenght(float lenght);
	DLLexport void upDate(Timer& timer);

	DLLexport Animation();

private:
	std::vector<Frame> _frames;
	unsigned int _currentFrame;
	float _currentTime;
	float _length;
};
#endif