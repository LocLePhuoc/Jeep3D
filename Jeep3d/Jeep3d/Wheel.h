#pragma once
#include "Mesh.h"
class Wheel :
	public Mesh
{
public:
	Wheel();
	~Wheel();
	void CreateTyrePart1(float radiusMax, float radiusMin, float widthMax, float rCircle, int n);
	void CreateTyrePart2(float	fSizeX, float fSizeY, float	fSizeZ);
	void CreateTyrePart3(float	fSizeX, float fSizeY, float	fSizeZ);
	void CreateRimPart1(float radiusMax, float radiusMin, float widthMax, int n);
	void CreateRimPart2(float radius,float width,float dWidth,int n);
};

