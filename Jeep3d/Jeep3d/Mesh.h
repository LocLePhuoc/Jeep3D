#if !defined (_MESH_CLASS)
#define _MESH_CLASS

#include "supportClass.h"


class VertexID
{
public:
	int		vertIndex;
	int		colorIndex;
};

class Face
{
public:
	int		nVerts;
	VertexID*	vert;
	Vector3		facenorm;
	
	Face()
	{
		nVerts	= 0;
		vert	= NULL;
	}
	~Face()
	{
		if(vert !=NULL)
		{
			delete[] vert;
			vert = NULL;
		}
		nVerts = 0;
	}
};

class Mesh
{
public:
	int		numVerts;
	Point3*		pt;
	
	int		numFaces;
	Face*		face;
public:
	Mesh()
	{
		numVerts	= 0;
		pt		= NULL;
		numFaces	= 0;
		face		= NULL;
	}
	~Mesh()
	{
		if (pt != NULL)
		{
			delete[] pt;
		}	
		if(face != NULL)
		{
			delete[] face;
		}
		numVerts = 0;
		numFaces = 0;
	}
	void DrawWireframe(int flag);
	void DrawColor(int flag);

	void CreateTetrahedron();
	void CreateCube(float	fSize);
	void CreateCuboid(float	fSizeX, float fSizeY, float	fSizeZ);
	void CreateCuboid2(float fSizeX, float fSizeY, float fSizeZ, float fSizeX2, float fSizeZ2);
	void CreateCylinder(int nSegment, int nStack, float fHeight, float lRadius, float sRadius, float angle, float deltaX);
	void CreateTiltedCylinder(int nSegment, int nStack, float fHeight, float radius, float deltaX, float angle);
	void CreateCurvedCylinder(int nCurveSegment, int nCircleSegment, float curveRadius, float circleRadius, float curveAngle, float circleAngle);
	void CreateSphere(int nSlice, int nStack, float radius);
	void CreateCylinder2(int n, float h, float R);
	void CreateSphereCorner(int nSlice, int nStack, float radius);
	void CreateSphereHalf(int nSlice, int nStack, float radius);
	void CreateOval(float r, float l, float h);
	Vector3 getNormalVector(Face& face, int flag);
	void CreateOvalWithHole(float R, float l, float h, float r);
	void SetColor(int colorIdx);
	void CalculateFacesNorm();
	void Draw();
	void DrawFaces(int flag);

	void Sym(Point3* pt, int size, int plane);
	void SetUpFace(Face& face, int nVerts, int* index, int color);
	int* SymNumOYZ(int* index, int num);
	int* SymNumOXY(int* index, int num);
};

#endif