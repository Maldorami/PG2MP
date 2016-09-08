#include "Animation.h"
//---------------------------------------------------------------------------
Animation::Animation()
:
_currentFrame(0),
_currentTime(0),
_length(1.0f){}
//---------------------------------------------------------------------------
void Animation::addFrame(float widthT, float heighT, float posX, float posY, float widthF, float heighF){
	Frame frame;
	frame.u1 = (posX / widthT);
	frame.v1 = (posY / heighT);

	frame.u2 = ((posX + widthF) / widthT);
	frame.v2 = (posY / heighT);

	frame.u3 = (posX / widthT);
	frame.v3 = ((posY + heighF) / heighT);

	frame.u4 = ((posX + widthF) / widthT);
	frame.v4 = ((posY + heighF) / heighT);

	_frames.push_back(frame);
}
//---------------------------------------------------------------------------
void Animation::upDate(Timer& timer){

	_currentTime += timer.timeBetweenFrames();

	while (_currentTime > _length){
		_currentTime -= _length;
	}

	_currentFrame = static_cast <unsigned int> ((_currentTime / _length) * _frames.size());
}
//---------------------------------------------------------------------------
unsigned int Animation::currentFrame() const{
	return _currentFrame;
}
//---------------------------------------------------------------------------
const std::vector<Animation::Frame>& Animation::frames() const{
	return _frames;
}
//---------------------------------------------------------------------------
void Animation::setLenght(float length){

	_length = length;

}
//---------------------------------------------------------------------------