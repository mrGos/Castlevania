#pragma once
#include "CAnimationFrame.h"
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>
#include "AppConfiguration.h"

class CAnimation
{
private:
	DWORD lastFrameTime;
	int defaultTime;
	int currentFrame = -1;
	std::vector<LPANIMATION_FRAME> frames;
public:
	CAnimation(int defaultTime) { this->defaultTime = defaultTime; lastFrameTime = -1; currentFrame = -1; }
	void Add(int spriteId, DWORD time = 0); //add sprite and time to nextsprite
	LPANIMATION_FRAME GetCurrentAnimFrame();
	void Render(float x, float y, int alpha = 255, bool isFlip = false, bool isRepeat = true);
	void resetAnim() { currentFrame = -1; }
	int getCurrent() { return currentFrame; }
	void setCurrent(int curAnim) { currentFrame = curAnim; }

	int getPreviousAnim() {
		if ((currentFrame - 1) > -0)
			return currentFrame - 1;
		return 0;
	}
	int getSize() { return frames.size(); }
	~CAnimation() {}
};

typedef CAnimation *LPANIMATION;

class CAnimations
{
	static CAnimations * _instance;

	std::unordered_map<int, LPANIMATION> animations;

public:
	void Add(int id, LPANIMATION ani);
	LPANIMATION Get(int id);

	static CAnimations * getInstance();
	~CAnimations() {}
};
