#pragma once

class Sprite
{
private:
	const LPDIRECT3DTEXTURE9 texture;
	const std::vector<Rect>  frames;

public:
	Sprite(const Sprite&) = delete;
	Sprite(Sprite&& other) noexcept; // for forcing move semantic
	Sprite(LPDIRECT3DTEXTURE9 texture, const std::vector<Rect>& frames);

	UINT GetNumberOfFrames() const { return (UINT)frames.size(); }
	Rect GetFrameSize(UINT frameIndex, const Vector2& vtScale = { 1.0f, 1.0f }) const;

	void Draw(const Vector2& pos, UINT frameIndex, const Vector2& vtScale = { 1.0f, 1.0f }, int alpha = 255) const;

};



