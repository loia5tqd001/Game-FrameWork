#include "MyException.h"
#include "GameObject.h"
#include "GameInit.h"



void GameObject::Update(DWORD dt)
{
	x += vx * dt;
	if ((vx > 0 && x > 290) || (x < 0 && vx < 0)) vx = -vx;
}

void GameObject::Render()
{
	LPANIMATION ani;
	if (vx > 0) ani = animations[0]; else ani = animations[1];
	ani->Render(x, y);
}

void GameObject::AddAnimation(int aniId)
{
	LPANIMATION ani = CAnimations::GetInstance()->Get(aniId);
	animations.push_back(ani);
}