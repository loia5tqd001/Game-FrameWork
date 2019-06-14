#pragma once


class Sprite
{
private:
	const LPDIRECT3DTEXTURE9 texture;
	const std::vector<Rect>  frames;

public:
	Sprite(LPDIRECT3DTEXTURE9 texture, const std::vector<Rect>& frames);

	void Draw(const Point& pos, UINT frameIndex, const Vector2& vtScale = { 1.0f, 1.0f }, int alpha = 255) const;

	UINT GetNumberOfFrames() const { return frames.size(); }
	Rect GetFrameSize(UINT frameIndex, const Vector2& vtScale = { 1.0f, 1.0f }) const;
};



