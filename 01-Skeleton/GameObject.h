#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>
#include "Sprites.h"



class GameObject
{
protected: 
	float x = 0.0f; 
	float y = 0.0f;
	float vx = 0.1f;
	int currentState;

	vector<LPANIMATION> animations;
public: 
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetState(int state) { this->currentState = state; }
	void AddAnimation(int aniId);
	void Update(DWORD dt);
	void Render();
};

//class Mario : public GameObject
//{
//public: 
//	Mario(LPCSTR texturePath) : GameObject(texturePath) {};
//
//	void Update(DWORD dt, UINT dir);
//};