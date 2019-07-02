#pragma once

class Animation
{
private:
	const Sprite& sprite                                  ;
	const float   holdTime                                ;
	      float   holdingTime = 0.0f                      ;
	const UINT    nFrames     = sprite.GetNumberOfFrames();
	      UINT    curFrame    = 0u                        ;
	      bool    doneCycle   = false                     ;

public:
	Animation(SpriteId spriteId, float holdTime = 0.0f);

	void Update(float dt);
	void Render(const Vector2& pos, const Vector2& vtScale = { 1.0f, 1.0f }, int alpha = 255) const;

	bool IsDoneCycle(); // for some animation aimed to animate one cycle each call
	Rect GetFrameSize(const Vector2& vtScale = { 1.0f, 1.0f }) const;

};

