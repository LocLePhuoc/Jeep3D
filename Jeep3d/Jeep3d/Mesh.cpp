
#include "Mesh.h"
#include <math.h>
#include <iostream>

#define PI			3.1415926
#define	COLORNUM		14
#define OXY 0
#define OYZ 1
#define OXZ 2
#define D2G  PI/180

static int count = 0;

float	ColorArr[COLORNUM][3] = {{0.8, 0.8, 0.8}, {0.1, 0.1, 0.1}, { 0.0,  0.0, 1.0}, 
								{1.0, 1.0,  0.0}, { 1.0, 0.0, 1.0},{ 0.0, 1.0, 1.0}, 
								 {0.3, 0.3, 0.3}, {0.5, 0.5, 0.5}, { 0.9,  0.9, 0.9},
								{1.0, 0.5,  0.5}, { 0.5, 1.0, 0.5},{ 0.5, 0.5, 1.0},
									{0.0, 0.0, 0.0}, {1.0, 1.0, 1.0}};





void Mesh::CreateCube(float	fSize)
{
	int i;

	numVerts=8;
	pt = new Point3[numVerts];
	pt[0].set(-fSize, fSize, fSize);
	pt[1].set( fSize, fSize, fSize);
	pt[2].set( fSize, fSize, -fSize);
	pt[3].set(-fSize, fSize, -fSize);
	pt[4].set(-fSize, -fSize, fSize);
	pt[5].set( fSize, -fSize, fSize);
	pt[6].set( fSize, -fSize, -fSize);
	pt[7].set(-fSize, -fSize, -fSize);


	numFaces= 6;
	face = new Face[numFaces];

	//Left face
	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 5;
	face[0].vert[2].vertIndex = 6;
	face[0].vert[3].vertIndex = 2;
	for(i = 0; i<face[0].nVerts ; i++)
		face[0].vert[i].colorIndex = 0;
	
	//Right face
	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 3;
	face[1].vert[2].vertIndex = 7;
	face[1].vert[3].vertIndex = 4;
	for(i = 0; i<face[1].nVerts ; i++)
		face[1].vert[i].colorIndex = 1;

	//top face
	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 1;
	face[2].vert[2].vertIndex = 2;
	face[2].vert[3].vertIndex = 3;
	for(i = 0; i<face[2].nVerts ; i++)
		face[2].vert[i].colorIndex = 2;

	//bottom face
	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 7;
	face[3].vert[1].vertIndex = 6;
	face[3].vert[2].vertIndex = 5;
	face[3].vert[3].vertIndex = 4;
	for(i = 0; i<face[3].nVerts ; i++)
		face[3].vert[i].colorIndex = 3;

	//near face
	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 4;
	face[4].vert[1].vertIndex = 5;
	face[4].vert[2].vertIndex = 1;
	face[4].vert[3].vertIndex = 0;
	for(i = 0; i<face[4].nVerts ; i++)
		face[4].vert[i].colorIndex = 4;

	//Far face
	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 3;
	face[5].vert[1].vertIndex = 2;
	face[5].vert[2].vertIndex = 6;
	face[5].vert[3].vertIndex = 7;
	for(i = 0; i<face[5].nVerts ; i++)
		face[5].vert[i].colorIndex = 5;

}




void Mesh::CreateTetrahedron()
{
	int i;
	numVerts=4;
	pt = new Point3[numVerts];
	pt[0].set(0, 0, 0);
	pt[1].set(1, 0, 0);
	pt[2].set(0, 1, 0);
	pt[3].set(0, 0, 1);

	numFaces= 4;
	face = new Face[numFaces];

	face[0].nVerts = 3;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 2;
	face[0].vert[2].vertIndex = 3;
	for(i = 0; i<face[0].nVerts ; i++)
		face[0].vert[i].colorIndex = 0;
	

	face[1].nVerts = 3;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;	
	face[1].vert[1].vertIndex = 2;
	face[1].vert[2].vertIndex = 1;
	for(i = 0; i<face[1].nVerts ; i++)
		face[1].vert[i].colorIndex = 1;

	
	face[2].nVerts = 3;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 3;
	face[2].vert[2].vertIndex = 2;
	for(i = 0; i<face[2].nVerts ; i++)
		face[2].vert[i].colorIndex = 2;


	face[3].nVerts = 3;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 1;
	face[3].vert[1].vertIndex = 3;
	face[3].vert[2].vertIndex = 0;
	for(i = 0; i<face[3].nVerts ; i++)
		face[3].vert[i].colorIndex = 3;
}


void Mesh::CreateCuboid(float	fSizeX, float fSizeY, float	fSizeZ)
{
	int i;

	numVerts = 8;
	pt = new Point3[numVerts];
	pt[0].set(-fSizeX/2, fSizeY/2, fSizeZ/2);
	pt[1].set(fSizeX/2, fSizeY/2, fSizeZ/2);
	pt[2].set(fSizeX/2, fSizeY/2, -fSizeZ/2);
	pt[3].set(-fSizeX/2, fSizeY/2, -fSizeZ/2);
	pt[4].set(-fSizeX/2, -fSizeY/2, fSizeZ/2);
	pt[5].set(fSizeX/2, -fSizeY/2, fSizeZ/2);
	pt[6].set(fSizeX/2, -fSizeY/2, -fSizeZ/2);
	pt[7].set(-fSizeX/2, -fSizeY/2, -fSizeZ/2);


	numFaces = 6;
	face = new Face[numFaces];

	//Left face
	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 5;
	face[0].vert[2].vertIndex = 6;
	face[0].vert[3].vertIndex = 2;
	for (i = 0; i<face[0].nVerts; i++)
		face[0].vert[i].colorIndex = 0;

	//Right face
	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 3;
	face[1].vert[2].vertIndex = 7;
	face[1].vert[3].vertIndex = 4;
	for (i = 0; i<face[1].nVerts; i++)
		face[1].vert[i].colorIndex = 1;

	//top face
	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 1;
	face[2].vert[2].vertIndex = 2;
	face[2].vert[3].vertIndex = 3;
	for (i = 0; i<face[2].nVerts; i++)
		face[2].vert[i].colorIndex = 2;

	//bottom face
	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 7;
	face[3].vert[1].vertIndex = 6;
	face[3].vert[2].vertIndex = 5;
	face[3].vert[3].vertIndex = 4;
	for (i = 0; i<face[3].nVerts; i++)
		face[3].vert[i].colorIndex = 3;

	//near face
	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 4;
	face[4].vert[1].vertIndex = 5;
	face[4].vert[2].vertIndex = 1;
	face[4].vert[3].vertIndex = 0;
	for (i = 0; i<face[4].nVerts; i++)
		face[4].vert[i].colorIndex = 4;

	//Far face
	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 3;
	face[5].vert[1].vertIndex = 2;
	face[5].vert[2].vertIndex = 6;
	face[5].vert[3].vertIndex = 7;
	for (i = 0; i<face[5].nVerts; i++)
		face[5].vert[i].colorIndex = 5;

}

void Mesh::CreateCuboid2(float	fSizeX, float fSizeY, float	fSizeZ, float fSizeX2, float fSizeZ2)
{
	int i;

	numVerts = 16;
	pt = new Point3[numVerts];
	pt[0].set(-fSizeX/2, fSizeY/2, fSizeZ/2);
	pt[1].set(fSizeX/2, fSizeY/2, fSizeZ/2);
	pt[2].set(fSizeX/2, fSizeY/2, -fSizeZ/2);
	pt[3].set(-fSizeX/2, fSizeY/2, -fSizeZ/2);
	pt[4].set(-fSizeX/2, -fSizeY/2, fSizeZ/2);
	pt[5].set(fSizeX/2, -fSizeY/2, fSizeZ/2);
	pt[6].set(fSizeX/2, -fSizeY/2, -fSizeZ/2);
	pt[7].set(-fSizeX/2, -fSizeY/2, -fSizeZ/2);
// hinh trong
	pt[8].set(-fSizeX2, fSizeY/2, fSizeZ2/2);
	pt[9].set(fSizeX2, fSizeY/2, fSizeZ2/2);
	pt[10].set(fSizeX2, fSizeY/2, -fSizeZ2/2);
	pt[11].set(-fSizeX2, fSizeY/2, -fSizeZ2/2);
	pt[12].set(-fSizeX2, -fSizeY/2, fSizeZ2/2);
	pt[13].set(fSizeX2, -fSizeY/2, fSizeZ2/2);
	pt[14].set(fSizeX2, -fSizeY/2, -fSizeZ2/2);
	pt[15].set(-fSizeX2, -fSizeY/2, -fSizeZ2/2);


	numFaces = 16;
	face = new Face[numFaces];

	//Left face
	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 5;
	face[0].vert[2].vertIndex = 6;
	face[0].vert[3].vertIndex = 2;
	for (i = 0; i<face[0].nVerts; i++)
		face[0].vert[i].colorIndex = 0;

	//Right face
	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 3;
	face[1].vert[2].vertIndex = 7;
	face[1].vert[3].vertIndex = 4;
	for (i = 0; i<face[1].nVerts; i++)
		face[1].vert[i].colorIndex = 1;

	//near face
	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 4;
	face[2].vert[1].vertIndex = 5;
	face[2].vert[2].vertIndex = 1;
	face[2].vert[3].vertIndex = 0;
	for (i = 0; i<face[2].nVerts; i++)
		face[2].vert[i].colorIndex = 2;

	//Far face
	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 3;
	face[3].vert[1].vertIndex = 2;
	face[3].vert[2].vertIndex = 6;
	face[3].vert[3].vertIndex = 7;
	for (i = 0; i<face[3].nVerts; i++)
		face[3].vert[i].colorIndex = 3;



	//top face


	//top-left
	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 1;
	face[4].vert[1].vertIndex = 2;
	face[4].vert[2].vertIndex = 10;
	face[4].vert[3].vertIndex = 9;
	for (i = 0; i<face[4].nVerts; i++)
		face[4].vert[i].colorIndex = 4;

	//top-right

	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 0;
	face[5].vert[1].vertIndex = 8;
	face[5].vert[2].vertIndex = 11;
	face[5].vert[3].vertIndex = 3;
	for (i = 0; i<face[5].nVerts; i++)
		face[5].vert[i].colorIndex = 5;

	//top-far
	face[6].nVerts = 4;
	face[6].vert = new VertexID[face[6].nVerts];
	face[6].vert[0].vertIndex = 0;
	face[6].vert[1].vertIndex = 1;
	face[6].vert[2].vertIndex = 9;
	face[6].vert[3].vertIndex = 8;
	for (i = 0; i<face[6].nVerts; i++)
		face[6].vert[i].colorIndex = 6;

	//top-near
	face[7].nVerts = 4;
	face[7].vert = new VertexID[face[7].nVerts];
	face[7].vert[0].vertIndex = 3;
	face[7].vert[1].vertIndex = 11;
	face[7].vert[2].vertIndex = 10;
	face[7].vert[3].vertIndex = 2;
	for (i = 0; i<face[7].nVerts; i++)
		face[7].vert[i].colorIndex = 7;

	//bottom face

	//bottom-left
	face[8].nVerts = 4;
	face[8].vert = new VertexID[face[8].nVerts];
	face[8].vert[0].vertIndex = 5;
	face[8].vert[1].vertIndex = 13;
	face[8].vert[2].vertIndex = 14;
	face[8].vert[3].vertIndex = 6;
	for (i = 0; i<face[8].nVerts; i++)
		face[8].vert[i].colorIndex = 8;

	//bottom-right

	face[9].nVerts = 4;
	face[9].vert = new VertexID[face[9].nVerts];
	face[9].vert[0].vertIndex = 7;
	face[9].vert[1].vertIndex = 15;
	face[9].vert[2].vertIndex = 12;
	face[9].vert[3].vertIndex = 4;
	for (i = 0; i<face[9].nVerts; i++)
		face[9].vert[i].colorIndex = 9;

	//bottom-far
	face[10].nVerts = 4;
	face[10].vert = new VertexID[face[10].nVerts];
	face[10].vert[0].vertIndex = 5;
	face[10].vert[1].vertIndex = 4;
	face[10].vert[2].vertIndex = 8;
	face[10].vert[3].vertIndex = 9;
	for (i = 0; i<face[10].nVerts; i++)
		face[10].vert[i].colorIndex = 10;

	//bottom-near
	face[11].nVerts = 4;
	face[11].vert = new VertexID[face[11].nVerts];
	face[11].vert[0].vertIndex = 6;
	face[11].vert[1].vertIndex = 14;
	face[11].vert[2].vertIndex = 15;
	face[11].vert[3].vertIndex = 7;
	for (i = 0; i<face[11].nVerts; i++)
		face[11].vert[i].colorIndex = 11;


	//Left-in face
	face[12].nVerts = 4;
	face[12].vert = new VertexID[face[12].nVerts];
	face[12].vert[0].vertIndex = 9;
	face[12].vert[1].vertIndex = 13;
	face[12].vert[2].vertIndex = 14;
	face[12].vert[3].vertIndex = 10;
	for (i = 0; i<face[12].nVerts; i++)
		face[12].vert[i].colorIndex = 12;

	//Right-in face
	face[13].nVerts = 4;
	face[13].vert = new VertexID[face[13].nVerts];
	face[13].vert[0].vertIndex = 8;
	face[13].vert[1].vertIndex = 12;
	face[13].vert[2].vertIndex = 15;
	face[13].vert[3].vertIndex = 11;
	for (i = 0; i<face[13].nVerts; i++)
		face[13].vert[i].colorIndex = 13;

	//near-in face
	face[14].nVerts = 4;
	face[14].vert = new VertexID[face[14].nVerts];
	face[14].vert[0].vertIndex = 10;
	face[14].vert[1].vertIndex = 11;
	face[14].vert[2].vertIndex = 15;
	face[14].vert[3].vertIndex = 14;
	for (i = 0; i<face[14].nVerts; i++)
		face[14].vert[i].colorIndex = 14;

	//Far-in face
	face[15].nVerts = 4;
	face[15].vert = new VertexID[face[15].nVerts];
	face[15].vert[0].vertIndex = 8;
	face[15].vert[1].vertIndex = 9;
	face[15].vert[2].vertIndex = 13;
	face[15].vert[3].vertIndex = 12;
	for (i = 0; i<face[15].nVerts; i++)
		face[15].vert[i].colorIndex = 0;


}


void Mesh::CreateCylinder(int nSegment, int nStack, float fHeight, float lRadius, float sRadius, float angle, float deltaX)
{
	numVerts = 2 + (nSegment + 1) * (nStack + 1);
	int bottomCenterIndex = (nSegment + 1) * (nStack + 1);
	int topCenterIndex = bottomCenterIndex + 1;
	pt = new Point3[numVerts];

	//difference in radius in each stack
	float dRadius = (lRadius - sRadius) / nStack;

	//difference in X coordinate of top and bottom in each stack
	float d = deltaX / nStack;

	//angle of each segment
	float alpha = angle / nSegment;

	float currentRadius = lRadius;
	float x, y, z;
	for (int i = 0; i <= nStack; i++) {
		currentRadius -= dRadius;
		for (int j = 0; j <= nSegment; j++) {
			x = currentRadius * cos(alpha * j * D2G) + d*i;
			y = i * fHeight / nStack;
			z = currentRadius * sin(alpha * j * D2G);
			pt[nSegment * i + j + i].set(x, y, z);
		}
	}
	pt[bottomCenterIndex].set(0, 0, 0);
	pt[topCenterIndex].set(deltaX, fHeight, 0);

	numFaces = nSegment * nStack;
	face = new Face[numFaces];
	for (int i = 0; i < nStack; i++) {
		for (int j = 0; j < nSegment; j++) {
			int index = nSegment * i + j;
			face[index].nVerts = 4;
			face[index].vert = new VertexID[4];
			face[index].vert[0].vertIndex = nSegment * i + j + i;
			face[index].vert[1].vertIndex = nSegment * i + j + i + 1;
			face[index].vert[2].vertIndex = nSegment * (i + 1) + j + i + 2;
			face[index].vert[3].vertIndex = nSegment * (i + 1)  + j + i + 1;
		}
	}
}


void Mesh::CreateCurvedCylinder(int nCurveSegment, int nCircleSegment, float curveRadius, float circleRadius, float curveAngle, float circleAngle) {
	numVerts = (nCurveSegment + 1) * (nCircleSegment + 1);
	pt = new Point3[numVerts];

	//angle of curve segment
	float alpha = curveAngle / nCurveSegment;

	//angle of circle segment
	float beta = circleAngle / nCircleSegment;

	float x, y, z;
	for (int j = 0; j <= nCurveSegment; j++) {
		for (int k = 0; k <= nCircleSegment; k++) {
			x = curveRadius * cos(alpha * j * D2G) + circleRadius * cos(beta * k * D2G) * cos(alpha * j * D2G);
			y = circleRadius * sin(beta * k * D2G);
			z = curveRadius * sin(alpha * j * D2G) + circleRadius * cos(beta * k * D2G) * sin(alpha * j * D2G);
			pt[j * nCircleSegment + k + j].set(x, y, z);
		}
	}

	numFaces = nCurveSegment * nCircleSegment;
	face = new Face[numFaces];

	for (int i = 0; i < nCurveSegment; i++) {  //layer
		for (int j = 0; j < nCircleSegment; j++) {
			int index = nCircleSegment * i + j;
			face[index].nVerts = 4;
			face[index].vert = new VertexID[4];
			face[index].vert[0].vertIndex = nCircleSegment * i + j + i;
			face[index].vert[1].vertIndex = nCircleSegment * i + j + i + 1;
			face[index].vert[2].vertIndex = nCircleSegment * (i + 1) + j + i + 2;
			face[index].vert[3].vertIndex = nCircleSegment * (i + 1) + j + i + 1;
		}
	}
}

void Mesh::CreateSphere(int nSlice, int nStack, float radius)
{
	numVerts = nSlice*(nStack + 1);
	pt = new Point3[numVerts];
	float alpha = PI / nStack;
	float beta = 2 * PI / nSlice;
	float x, y, z;
	int stack, slice, i, pos;
	for (stack = 0; stack <= nStack; stack++) {
		for (slice = 0; slice < nSlice; slice++) {
			x = radius*sin((stack)*alpha)*cos(slice*beta);
			z = radius*cos((stack)*alpha);
			y = radius*sin((stack)*alpha)*sin(slice*beta);
			pos = stack*nSlice + slice;
			pt[pos].set(x, y, z);
		};
	}
	numFaces = nSlice*(nStack);
	face = new Face[numFaces];
	for (stack = 0; stack < nStack; stack++) {
		for (slice = 0; slice < nSlice; slice++) {
			pos = stack*nSlice + slice;		// ok roi
			face[pos].nVerts = 4;
			face[pos].vert = new VertexID[face[pos].nVerts];
			face[pos].vert[0].vertIndex = pos;
			if (slice != nSlice - 1)
				face[pos].vert[1].vertIndex = pos + 1; //di chuyen toi
			else 
				face[pos].vert[1].vertIndex = pos - slice;// quay lai dau vong

			if (slice != nSlice - 1)
				face[pos].vert[2].vertIndex = pos + 1 + nSlice; //di chuyen len 1 tang
			else 
				face[pos].vert[2].vertIndex = pos - slice + nSlice;// quay lai dau vong, len 1 tang

			face[pos].vert[3].vertIndex = pos + nSlice;

		for (i = 0; i<face[pos].nVerts; i++)
				face[pos].vert[i].colorIndex = pos % 14;
		}
	}
}

void Mesh::CreateSphereCorner(int nSlice, int nStack, float radius) {
	numVerts = (nSlice + 1) * (nStack + 1);
	pt = new Point3[numVerts];
	float alpha = 90 * D2G / nSlice;
	float phi = 90 * D2G / nStack;
	float x, y, z;
	for (int i = 0; i <= nStack; i++) {
		for (int j= 0; j <= nSlice; j++) {
			x = radius * cos(phi * i) * cos(alpha * j);
			y = radius * sin(phi * i);
			z = radius * cos(phi * i) * sin(alpha * j);
			pt[i * nSlice + i + j].set(x, y, z);
		}
	}


	numFaces = nStack * nSlice;
	face = new Face[numFaces];

	for (int i = 0; i < nStack; i++) {  //layer
		for (int j = 0; j < nSlice; j++) {
			int index = nSlice * i + j;
			face[index].nVerts = 4;
			face[index].vert = new VertexID[4];
			face[index].vert[0].vertIndex = nSlice * i + j + i;
			face[index].vert[1].vertIndex = nSlice * i + j + i + 1;
			face[index].vert[2].vertIndex = nSlice * (i + 1) + j + i + 2;
			face[index].vert[3].vertIndex = nSlice * (i + 1) + j + i + 1;
		}
	}
}

void Mesh::CreateSphereHalf(int nSlice, int nStack, float radius) {
	numVerts = (nSlice + 1) * (nStack + 1);
	pt = new Point3[numVerts];
	float alpha = 180 * D2G / nSlice;
	float phi = 180 * D2G / nStack;
	float x, y, z;
	for (int i = 0; i <= nStack; i++) {
		for (int j = 0; j <= nSlice; j++) {
			x = radius * cos(phi * i) * cos(alpha * j);
			y = radius * sin(phi * i);
			z = radius * cos(phi * i) * sin(alpha * j);
			pt[i * nSlice + i + j].set(x, y, z);
		}
	}


	numFaces = nStack * nSlice;
	face = new Face[numFaces];

	for (int i = 0; i < nStack; i++) {  //layer
		for (int j = 0; j < nSlice; j++) {
			int index = nSlice * i + j;
			face[index].nVerts = 4;
			face[index].vert = new VertexID[4];
			face[index].vert[0].vertIndex = nSlice * i + j + i;
			face[index].vert[1].vertIndex = nSlice * i + j + i + 1;
			face[index].vert[2].vertIndex = nSlice * (i + 1) + j + i + 2;
			face[index].vert[3].vertIndex = nSlice * (i + 1) + j + i + 1;
		}
	}
}

void Mesh::CreateOval(float r, float l, float h) {
	int num = 21;
	numVerts = num * 4;

	pt = new Point3[numVerts];
	for (int i = 0; i<num; i++) {
		pt[i].set(l / 2 + r*sin(PI / (num - 1)*i), h / 2, r*cos(PI / (num - 1)*i));
	}
	Sym(pt, num, OXZ);
	Sym(pt, num*2, OYZ);

	numFaces = num*2 + 2;
	face = new Face[numFaces];

	int j = 0;
	for (int i = 0; i<num - 1; i++) {
		int index1[4] = { i, i + num, i + num + 1, i + 1 };
		int index2[4] = { i + 2*num, i + 3*num, i + 3*num + 1, i + 2*num + 1 };
		SetUpFace(face[j++], 4, index1, j);
		SetUpFace(face[j++], 4, index2, j);
	}
	int sizeArr = num * 2;
	int *index1 = new int[num*2];
	for (int i = 0; i<num * 2; i++) {
		if (i<num) index1[i] = i;
		else index1[i] = 4 * num - i - 1;
	}
	SetUpFace(face[j++], num * 2, index1, j);

	int *index2 = new int[num * 2];
	for (int i = 0; i<num * 2; i++) {
		if (i<num) index2[i] = num + i;
		else index2[i] = 5 * num - i - 1;
	}
	SetUpFace(face[j++], num * 2, index2, j);
	int index3[4] = { 0, num, 3 * num, 2 * num };
	int index4[4] = { num - 1, 2 * num - 1, 4 * num - 1, 3 * num - 1 };
	SetUpFace(face[j++], 4, index3, j);
	SetUpFace(face[j++], 4, index4, j);
}

void Mesh::CreateOvalWithHole(float R, float l, float h, float r) {
	int num = 21;
	numVerts = num * 8;

	pt = new Point3[numVerts];
	for (int i = 0; i<num; i++) {
		pt[2 * i].set(l / 2 + R*sin(PI / (num - 1)*i), h / 2, R*cos(PI / (num - 1)*i));
		pt[2 * i + 1].set(l / 2 + r*sin(PI / (num - 1)*i), h / 2, r*cos(PI / (num - 1)*i));
	}
	Sym(pt, num * 2, OXZ);
	Sym(pt, num * 4, OYZ);

	numFaces = (num - 1) * 8 + 8;
	face = new Face[numFaces];

	int j = 0;
	for (int i = 0; i<num - 1; i++) {
		int index1[4] = { 2 * i, 2 * i + 1, 2 * i + 3, 2 * i + 2 };//tren trai
		int index2[4] = { 2 * i + 2 * num, 2 * i + 2 * num + 1, 2 * i + 2 * num + 3, 2 * i + 2 * num + 2 };// duoi trai
		int index3[4] = { 2 * i, 2 * i + 2, 2 * i + 2 * num + 2, 2 * i + 2 * num };//truoc trai
		int index4[4] = { 2 * i + 1, 2 * i + 3, 2 * i + 3 + 2 * num, 2 * i + 1 + 2 * num };// trong trai
		SetUpFace(face[j++], 4, index1, j);
		SetUpFace(face[j++], 4, index2, j);
		SetUpFace(face[j++], 4, index3, j);
		SetUpFace(face[j++], 4, index4, j);

		SetUpFace(face[j++], 4, SymNumOYZ(index1, 4 * num), j);
		SetUpFace(face[j++], 4, SymNumOYZ(index2, 4 * num), j);
		SetUpFace(face[j++], 4, SymNumOYZ(index3, 4 * num), j);
		SetUpFace(face[j++], 4, SymNumOYZ(index4, 4 * num), j);
	}

	int index1[4] = { 0, 1, num * 4 + 1, num * 4 }; // tren truoc
	int index2[4] = { num * 2, num * 2 + 1, num * 6 + 1, num * 6 }; //   duoi trong
	int index3[4] = { 0, 2 * num, 6 * num, 4 * num };//truoc gan
	int index4[4] = { 1, 2 * num + 1, 6 * num + 1, 4 * num + 1 };//sau gan
	SetUpFace(face[j++], 4, index1, j);
	SetUpFace(face[j++], 4, index2, j);
	SetUpFace(face[j++], 4, index3, j);
	SetUpFace(face[j++], 4, index4, j);

	SetUpFace(face[j++], 4, SymNumOXY(index1, num), j);
	SetUpFace(face[j++], 4, SymNumOXY(index2, num), j);
	SetUpFace(face[j++], 4, SymNumOXY(index3, num), j);
	SetUpFace(face[j++], 4, SymNumOXY(index4, num), j);
}


void Mesh::DrawWireframe(int flag)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for (int f = 0; f < numFaces; f++)
	{
		Vector3 norm = getNormalVector(face[f], 1 * flag);
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			glNormal3f(norm.x, norm.y, norm.z);
			int		iv = face[f].vert[v].vertIndex;

			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

void Mesh::DrawColor(int flag)
{ 
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	for (int f = 0; f < numFaces; f++)
	{
		Vector3 norm = getNormalVector(face[f], 1 * flag);
		glBegin(GL_POLYGON);
		glNormal3f(norm.x,norm.y,norm.z);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int		iv = face[f].vert[v].vertIndex;
			int		ic = face[f].vert[v].colorIndex;
			
			//ic = f % COLORNUM;

			glColor3f(ColorArr[ic][0], ColorArr[ic][1], ColorArr[ic][2]); 
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

Vector3 Mesh::getNormalVector(Face& face, int flag) { 
	count++;
	Vector3 firstVec(pt[face.vert[1].vertIndex] - pt[face.vert[0].vertIndex]);
	Vector3 secondVec(pt[face.vert[2].vertIndex] - pt[face.vert[0].vertIndex]);

	firstVec = firstVec.cross(secondVec);
	firstVec.normalize();

	if (flag == -1) firstVec.flip();
	return firstVec;
}


void Mesh::Sym(Point3* pt, int size, int surface) {
	switch (surface) {
	case OYZ:
		for (int i = 0; i<size; i++) {
			pt[i + size].set(-pt[i].x, pt[i].y, pt[i].z);
		}
		break;
	case OXZ:
		for (int i = 0; i<size; i++) {
			pt[i + size].set(pt[i].x, -pt[i].y, pt[i].z);
		}
		break;
	default:
		for (int i = 0; i<size; i++) {
			pt[i + size].set(pt[i].x, pt[i].y, -pt[i].z);
		}
	}
}

void Mesh::SetUpFace(Face& face, int nVerts, int* index, int color) {
	face.nVerts = nVerts;
	face.vert = new VertexID[face.nVerts];
	for (int i = 0; i<nVerts; i++) {
		face.vert[i].vertIndex = index[i];
		face.vert[i].colorIndex = color % 14;
	}
}

int* Mesh::SymNumOYZ(int* index, int num) {
	int* newIndex = new int[4];
	for (int i = 0; i<4; i++) {
		newIndex[i] = index[i] + num;
	}
	return newIndex;
}

int* Mesh::SymNumOXY(int* index, int num) {
	int* newIndex = new int[4];
	for (int i = 0; i<4; i++) {
		newIndex[i] = index[i] + 2 * (num - 1);
	}
	return newIndex;
}

void Mesh::SetColor(int colorIdx) {
	for (int f = 0; f < numFaces; f++) {
		for (int v = 0; v < face[f].nVerts; v++) {
			face[f].vert[v].colorIndex = colorIdx;
		}
	}
}

void Mesh::CalculateFacesNorm() {
	//for each face
	for (int i = 0; i < numFaces; i++) {
		//calculate normVector MartinNewell
		float normX = 0, normY = 0, normZ = 0;
		for (int j = 0; j < face[i].nVerts; j++) {
			int vertexIndex1 = face[i].vert[j].vertIndex;
			int ptIndex = ((j + 1) == face[i].nVerts) ? 0 : j + 1;
			int vertexIndex2 = face[i].vert[ptIndex].vertIndex;
			normX = normX + (pt[vertexIndex1].y - pt[vertexIndex2].y)*(pt[vertexIndex1].z + pt[vertexIndex2].z);
			normY = normY + (pt[vertexIndex1].z - pt[vertexIndex2].z)*(pt[vertexIndex1].x + pt[vertexIndex2].x);
			normZ = normZ + (pt[vertexIndex1].x - pt[vertexIndex2].x)*(pt[vertexIndex1].y + pt[vertexIndex2].y);
		}
		float normValue = sqrtf(normX *normX + normY * normY + normZ * normZ);
		normX = normX / normValue;
		normY = normY / normValue;
		normZ = normZ / normValue;
		face[i].facenorm = { normX,normY,normZ };
	}
}
void Mesh::Draw() {
	for (int f = 0; f < numFaces; f++) {
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++) {
			int		iv = face[f].vert[v].vertIndex;
			glNormal3f(face[f].facenorm.x, face[f].facenorm.y, face[f].facenorm.z);
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

void Mesh::DrawFaces(int flag) {
	for (int f = 0; f < numFaces; f++)
	{
		Vector3 norm = getNormalVector(face[f], 1 * flag);
		glBegin(GL_POLYGON);
		glNormal3f(norm.x, norm.y, norm.z);
		for (int v = 0; v < face[f].nVerts; v++)
		{

			int		iv = face[f].vert[v].vertIndex;

			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

void Mesh::CreateCylinder2(int n, float h, float R) {
	numVerts = 2 * n + 2;
	float phi = 2 * PI / (n - 1);
	pt = new Point3[numVerts];
	for (int i = 0; i < n; i++) {
		float iphi = i * phi;
		pt[i].set(R*sin(iphi), h / 2, R*cos(iphi));
		pt[i + n].set(R*sin(iphi), -h / 2, R*cos(iphi));
	}
	pt[2 * n].set(0, h / 2, 0);
	pt[2 * n + 1].set(0, -h / 2, 0);
	numFaces = n * 3;
	face = new Face[numFaces];
	//Top faces
	for (int i = 0; i < n; i++)
	{
		face[i].nVerts = 3;
		face[i].vert = new VertexID[face[i].nVerts];
		if (i == n - 1) {
			face[i].vert[0].vertIndex = 0;
			face[i].vert[1].vertIndex = n - 1;
			face[i].vert[2].vertIndex = 2 * n;
		}
		else
		{
			face[i].vert[0].vertIndex = i;
			face[i].vert[1].vertIndex = i + 1;
			face[i].vert[2].vertIndex = 2 * n;
		}
		for (int j = 0; j < face[i].nVerts; j++)
			face[0].vert[j].colorIndex = 0;
	}
	//Bottom faces
	for (int i = n; i < 2 * n; i++)
	{
		face[i].nVerts = 3;
		face[i].vert = new VertexID[face[i].nVerts];
		if (i == 2 * n - 1) {
			face[i].vert[0].vertIndex = 2 * n - 1;
			face[i].vert[1].vertIndex = n;
			face[i].vert[2].vertIndex = 2 * n + 1;
		}
		else
		{
			face[i].vert[0].vertIndex = i + 1;
			face[i].vert[1].vertIndex = i;
			face[i].vert[2].vertIndex = 2 * n + 1;
		}
		for (int j = 0; j < face[i].nVerts; j++)
			face[0].vert[j].colorIndex = 0;
	}
	//
	for (int j = 0; j < n; j++)
	{
		int i = j + n * 2;
		face[i].nVerts = 4;
		face[i].vert = new VertexID[face[i].nVerts];
		if (j == n - 1) {
			face[i].vert[0].vertIndex = n - 1;
			face[i].vert[1].vertIndex = 0;
			face[i].vert[2].vertIndex = n;
			face[i].vert[3].vertIndex = 2 * n - 1;
		}
		else
		{
			face[i].vert[0].vertIndex = j;
			face[i].vert[1].vertIndex = j + n;
			face[i].vert[2].vertIndex = j + n + 1;
			face[i].vert[3].vertIndex = j + 1;
		}
		for (int k = 0; k < face[i].nVerts; k++)
			face[0].vert[k].colorIndex = 0;
	}




}