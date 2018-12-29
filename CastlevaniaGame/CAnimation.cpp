#include "CAnimation.h"





CAnimations* CAnimations::_instance = 0;


void CAnimation::Add(int spriteId, DWORD time)
{
	int t = time;
	if (time == 0) t = this->defaultTime;

	LPSPRITE sprite = SPRITES->Get(spriteId);
	LPANIMATION_FRAME frame = new CAnimationFrame(sprite, t);
	frames.push_back(frame);
}

LPANIMATION_FRAME CAnimation::GetCurrentAnimFrame()
{
	if (currentFrame >= 0) {
		return frames[currentFrame];
	}
	else {
		return frames[0];
	}
}

//void CAnimation::Render(float x, float y, int alpha)
//{
//	DWORD now = GetTickCount();
//	if (currentFrame == -1)
//	{
//		currentFrame = 0;
//		lastFrameTime = now;
//	}
//	else
//	{
//		DWORD t = frames[currentFrame]->GetTime();
//		if (now - lastFrameTime > t)
//		{
//			currentFrame++;
//			lastFrameTime = now;
//			if (currentFrame == frames.size()) currentFrame = 0;
//		}
//
//	}
//
//	frames[currentFrame]->GetSprite()->Draw(x, y, alpha);
//}

void CAnimation::Render(float x, float y, int alpha, bool isFlip, bool isRepeat)
{
	DWORD now = GetTickCount();
	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames[currentFrame]->GetTime();
		if (now - lastFrameTime > t)
		{
			currentFrame++;
			lastFrameTime = now;
			if (currentFrame == frames.size()) {
				if (isRepeat) {
					currentFrame = 0;
				}
				else {
					currentFrame = frames.size() - 1;
				}
			}
		}

	}

	frames[currentFrame]->GetSprite()->Draw(x, y, alpha, isFlip);
}

void CAnimations::Add(int id, LPANIMATION ani)
{
	animations[id] = ani;
}

LPANIMATION CAnimations::Get(int id)
{
	return animations[id];
}

CAnimations * CAnimations::getInstance()
{
	if (_instance == 0)
		_instance = new CAnimations();
	return _instance;
}
