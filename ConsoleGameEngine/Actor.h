#pragma once


class Actor	
{
public:
	Actor();
	virtual ~Actor();


	// TODO : Change Struct
	unsigned int X;
	unsigned int Y;

	// mesh
	wchar_t mesh;
	// getWorld -> 월드에서 스폰 가능. 레벨의 getWOrld를 통해접근.
	// Level
	
};