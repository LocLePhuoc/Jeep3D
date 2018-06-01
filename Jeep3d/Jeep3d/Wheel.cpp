
#include "Wheel.h"

#define PI			3.1415926

Wheel::Wheel()
{
}


Wheel::~Wheel()
{
}
void Wheel::CreateTyrePart1(float radiusMax, float radiusMin,float widthMax,float rCircle,int n) {
	int numVertOnCircle = 32*n;
	int numCircle = 5*n;
	float delta = (radiusMax- radiusMin)/2;
	int numVerts = numVertOnCircle * (numCircle+1);
	pt = new Point3[numVerts];
	//tinh goc tang sau moi lan lap
	float dphi = 2*PI/ numVertOnCircle;
	float dphi2 = (PI - 2*acos(delta / rCircle))/ (numCircle-1);
	float d = (radiusMax - radiusMin) / (numCircle-1);
	float yCircle = widthMax - sqrt(rCircle*rCircle - delta * delta);
	for (int i = 0;i < numCircle;i++) {
		for (int j = 0;j < numVertOnCircle;j++) {
			int k = i * numVertOnCircle + j;
			float R = radiusMax - d*i;
			pt[k].x = R * cos(j*dphi);
			pt[k].y = yCircle+rCircle * sin(acos(delta / rCircle)+i*dphi2);
			pt[k].z = R * sin(j*dphi);
		}
	}
	for (int j = 0;j < numVertOnCircle;j++) {
		int k = numVertOnCircle * numCircle + j;
		float R = radiusMax;
		pt[k].x = R * cos(j*dphi);
		pt[k].y = 0;
		pt[k].z = R * sin(j*dphi);
	}
	
	numFaces = numVertOnCircle * numCircle;
	face = new Face[numFaces];

	for (int i = 0;i < numFaces- numVertOnCircle;i++) {
		face[i].nVerts = 4;
		face[i].vert = new VertexID[face[i].nVerts];
		face[i].vert[0].vertIndex = i;
		face[i].vert[1].vertIndex = i + numVertOnCircle;
		face[i].vert[2].vertIndex = ((i + 1) % numVertOnCircle == 0 ? i + 1 : (i + numVertOnCircle + 1));
		face[i].vert[3].vertIndex = ((i + 1) % numVertOnCircle == 0 ? i + 1 - numVertOnCircle : (i + 1));
		for (int m = 0; m < face[i].nVerts; m++)
			face[i].vert[m].colorIndex = 0;
	}
	for (int i = numFaces - numVertOnCircle;i < numFaces;i++) {
		int j = i + numVertOnCircle;
		face[i].nVerts = 4;
		face[i].vert = new VertexID[face[i].nVerts];
		face[i].vert[0].vertIndex = j;
		face[i].vert[1].vertIndex = j % numVertOnCircle;
		face[i].vert[2].vertIndex = (j+1) % numVertOnCircle;
		face[i].vert[3].vertIndex = ((j + 1) % numVertOnCircle == 0 ? j + 1 - numVertOnCircle : (j + 1));
		for (int m = 0; m < face[i].nVerts; m++)
			face[i].vert[m].colorIndex = 0;
	}
}
	void Wheel::CreateTyrePart2(float	fSizeX, float fSizeY, float	fSizeZ) {
		int i;
		numVerts = 8;
		float d = 0.8;
		pt = new Point3[numVerts];
		pt[0].set(-fSizeX / 2 * d, fSizeY / 2, fSizeZ / 2 * d);
		pt[1].set(fSizeX / 2 * d, fSizeY / 2, fSizeZ / 2 * d);
		pt[2].set(fSizeX / 2 * d, fSizeY / 2, -fSizeZ / 2 * d);
		pt[3].set(-fSizeX / 2 * d, fSizeY / 2, -fSizeZ / 2 *2/3 * d);
		pt[4].set(-fSizeX / 2 , -fSizeY / 2, fSizeZ / 2 );
		pt[5].set(fSizeX / 2, -fSizeY / 2, fSizeZ / 2);
		pt[6].set(fSizeX / 2 , -fSizeY / 2, -fSizeZ / 2 );
		pt[7].set(-fSizeX / 2 , -fSizeY / 2, -fSizeZ / 2 * 2/3) ;


		numFaces = 6;
		face = new Face[numFaces];

		//Left face
		face[0].nVerts = 4;
		face[0].vert = new VertexID[face[0].nVerts];
		face[0].vert[0].vertIndex = 1;
		face[0].vert[1].vertIndex = 5;
		face[0].vert[2].vertIndex = 6;
		face[0].vert[3].vertIndex = 2;
		for (i = 0; i < face[0].nVerts; i++)
			face[0].vert[i].colorIndex = 0;

		//Right face
		face[1].nVerts = 4;
		face[1].vert = new VertexID[face[1].nVerts];
		face[1].vert[0].vertIndex = 0;
		face[1].vert[1].vertIndex = 3;
		face[1].vert[2].vertIndex = 7;
		face[1].vert[3].vertIndex = 4;
		for (i = 0; i < face[1].nVerts; i++)
			face[1].vert[i].colorIndex = 0;

		//top face
		face[2].nVerts = 4;
		face[2].vert = new VertexID[face[2].nVerts];
		face[2].vert[0].vertIndex = 0;
		face[2].vert[1].vertIndex = 1;
		face[2].vert[2].vertIndex = 2;
		face[2].vert[3].vertIndex = 3;
		for (i = 0; i < face[2].nVerts; i++)
			face[2].vert[i].colorIndex = 0;

		//bottom face
		face[3].nVerts = 4;
		face[3].vert = new VertexID[face[3].nVerts];
		face[3].vert[0].vertIndex = 7;
		face[3].vert[1].vertIndex = 6;
		face[3].vert[2].vertIndex = 5;
		face[3].vert[3].vertIndex = 4;
		for (i = 0; i < face[3].nVerts; i++)
			face[3].vert[i].colorIndex = 0;

		//near face
		face[4].nVerts = 4;
		face[4].vert = new VertexID[face[4].nVerts];
		face[4].vert[0].vertIndex = 4;
		face[4].vert[1].vertIndex = 5;
		face[4].vert[2].vertIndex = 1;
		face[4].vert[3].vertIndex = 0;
		for (i = 0; i < face[4].nVerts; i++)
			face[4].vert[i].colorIndex = 0;

		//Far face
		face[5].nVerts = 4;
		face[5].vert = new VertexID[face[5].nVerts];
		face[5].vert[0].vertIndex = 3;
		face[5].vert[1].vertIndex = 2;
		face[5].vert[2].vertIndex = 6;
		face[5].vert[3].vertIndex = 7;
		for (i = 0; i < face[5].nVerts; i++)
			face[5].vert[i].colorIndex = 0;


	}
	void Wheel::CreateTyrePart3(float	fSizeX, float fSizeY, float	fSizeZ) {
		int i;
		numVerts = 8;
		float d = 0.8;
		pt = new Point3[numVerts];
		pt[0].set(-fSizeX / 2 * d, fSizeY / 2, fSizeZ / 2 * d);
		pt[1].set(fSizeX / 2 , fSizeY / 2, fSizeZ / 2 );
		pt[2].set(fSizeX / 2 , fSizeY / 2, -fSizeZ / 2);
		pt[3].set(-fSizeX / 2 * d, fSizeY / 2, -fSizeZ / 2 * d);
		pt[4].set(-fSizeX / 2, -fSizeY / 2, fSizeZ / 2);
		pt[5].set(fSizeX / 2, -fSizeY / 2, fSizeZ / 2);
		pt[6].set(fSizeX / 2, -fSizeY / 2, -fSizeZ / 2);
		pt[7].set(-fSizeX / 2, -fSizeY / 2, -fSizeZ / 2);


		numFaces = 6;
		face = new Face[numFaces];

		//Left face
		face[0].nVerts = 4;
		face[0].vert = new VertexID[face[0].nVerts];
		face[0].vert[0].vertIndex = 1;
		face[0].vert[1].vertIndex = 5;
		face[0].vert[2].vertIndex = 6;
		face[0].vert[3].vertIndex = 2;
		for (i = 0; i < face[0].nVerts; i++)
			face[0].vert[i].colorIndex = 0;

		//Right face
		face[1].nVerts = 4;
		face[1].vert = new VertexID[face[1].nVerts];
		face[1].vert[0].vertIndex = 0;
		face[1].vert[1].vertIndex = 3;
		face[1].vert[2].vertIndex = 7;
		face[1].vert[3].vertIndex = 4;
		for (i = 0; i < face[1].nVerts; i++)
			face[1].vert[i].colorIndex = 0;

		//top face
		face[2].nVerts = 4;
		face[2].vert = new VertexID[face[2].nVerts];
		face[2].vert[0].vertIndex = 0;
		face[2].vert[1].vertIndex = 1;
		face[2].vert[2].vertIndex = 2;
		face[2].vert[3].vertIndex = 3;
		for (i = 0; i < face[2].nVerts; i++)
			face[2].vert[i].colorIndex = 0;

		//bottom face
		face[3].nVerts = 4;
		face[3].vert = new VertexID[face[3].nVerts];
		face[3].vert[0].vertIndex = 7;
		face[3].vert[1].vertIndex = 6;
		face[3].vert[2].vertIndex = 5;
		face[3].vert[3].vertIndex = 4;
		for (i = 0; i < face[3].nVerts; i++)
			face[3].vert[i].colorIndex = 0;

		//near face
		face[4].nVerts = 4;
		face[4].vert = new VertexID[face[4].nVerts];
		face[4].vert[0].vertIndex = 4;
		face[4].vert[1].vertIndex = 5;
		face[4].vert[2].vertIndex = 1;
		face[4].vert[3].vertIndex = 0;
		for (i = 0; i < face[4].nVerts; i++)
			face[4].vert[i].colorIndex = 0;

		//Far face
		face[5].nVerts = 4;
		face[5].vert = new VertexID[face[5].nVerts];
		face[5].vert[0].vertIndex = 3;
		face[5].vert[1].vertIndex = 2;
		face[5].vert[2].vertIndex = 6;
		face[5].vert[3].vertIndex = 7;
		for (i = 0; i < face[5].nVerts; i++)
			face[5].vert[i].colorIndex = 0;
	}
	void Wheel::CreateRimPart1(float radiusMax, float radiusMin, float widthMax, int n) {
		//ve hinh tru 2 mat
		int numVertsOnCircle = 32 * n;
		numVerts = numVertsOnCircle * 4;
		pt = new Point3[numVerts];
		//tinh goc tang sau moi lan lap
		float dphi = 2 * PI / numVertsOnCircle;
		for (int i = 0;i < numVerts / 4;i++) {
			pt[i].x = radiusMax * cos(i*dphi);
			pt[i].z = radiusMax * sin(i*dphi);
			pt[i].y = widthMax;
		}
		for (int i = numVertsOnCircle;i < 2 * numVertsOnCircle;i++) {
			pt[i].x = radiusMax * cos(i*dphi);
			pt[i].z = radiusMax * sin(i*dphi);
			pt[i].y = 0;
		}
		for (int i = 2 * numVertsOnCircle;i < 3 * numVertsOnCircle;i++) {
			pt[i].x = radiusMin * cos(i*dphi);
			pt[i].z = radiusMin * sin(i*dphi);
			pt[i].y = 0;
		}
		for (int i = 3 * numVertsOnCircle;i < numVerts;i++) {
			pt[i].x = radiusMin * cos(i*dphi);
			pt[i].z = radiusMin * sin(i*dphi);
			pt[i].y = widthMax;
		}
		numFaces = numVerts;
		face = new Face[numFaces];
		int index1, index2, index3, index4;
		for (int i = 0;i < numFaces;i++) {
			face[i].nVerts = 4;
			index1 = i;
			index2 = (index1 + 1) % numVertsOnCircle == 0 ? index1 - index1 % numVertsOnCircle : index1 + 1;
			index4 = i + numVertsOnCircle >= numVerts ? i + numVertsOnCircle - numVerts : i + numVertsOnCircle;
			index3 = (index4 + 1) % numVertsOnCircle == 0 ? index4 - index4 % numVertsOnCircle : index4 + 1;
			face[i].vert = new VertexID[face[i].nVerts];
			face[i].vert[0].vertIndex = index1;
			face[i].vert[1].vertIndex = index2;
			face[i].vert[2].vertIndex = index3;
			face[i].vert[3].vertIndex = index4;
			for (int m = 0; m < face[i].nVerts; m++)
				face[i].vert[m].colorIndex = 0;
		}
		
	}
	void Wheel::CreateRimPart2(float radius, float width, float dWidth, int n) {
		//z=x^2+bValue
		//x^2+z^2=radius*radius
		//giao diem
		float bValue = 1 * radius / 3;
		float c = -bValue - radius * radius;
		float z0 = (-1 + sqrt(1 - 4 * 1 * c)) / 2;
		float x0 = sqrt(z0 - bValue);
		int numVertsCircle = 8 * n;
		int numVertsParabol = 16 * n;
		int additionVerts = numVertsParabol;
		float anpha1 = atan(z0 / x0);
		float phi1 = anpha1 - PI / 4;
		float delta = x0 / (numVertsParabol - 1);
		float insertY = dWidth / (numVertsCircle-1);
		int numVertsOnOneFace = numVertsCircle + numVertsParabol + 1;
		numVerts = 2 * numVertsOnOneFace + additionVerts;
		pt = new Point3[numVerts];
		//vertex on Circle
		for (int i = 0; i < numVertsCircle; i++) {
			int index = i;
			pt[index].x = radius * cos(PI / 4 + phi1 / numVertsCircle * i);
			pt[index].z = radius * sin(PI / 4 + phi1 / numVertsCircle * i);
			pt[index].y = width+ insertY;
		}
		//vertex on Parabol
		for (int i = 0; i < numVertsParabol; i++) {
			int index = i + numVertsCircle;
			pt[index].x = x0 - delta * i;
			pt[index].z = (pt[index].x*pt[index].x + bValue);
			pt[index].y = width;
		}
		//center vertex
		pt[numVertsOnOneFace - 1].x = 0;
		pt[numVertsOnOneFace - 1].z = 0;
		pt[numVertsOnOneFace - 1].y = width;

		for (int i = 0; i < numVertsCircle; i++) {
			int index = i + numVertsOnOneFace;
			pt[index].x = radius * cos(PI / 4 + phi1 / numVertsCircle * i);
			pt[index].z = radius * sin(PI / 4 + phi1 / numVertsCircle * i);
			pt[index].y = 0;
		}
		for (int i = 0; i < numVertsParabol; i++) {
			int index = i + numVertsCircle + numVertsOnOneFace;
			pt[index].x = x0 - delta * i;
			pt[index].z = (pt[index].x*pt[index].x + bValue);
			pt[index].y = 0;
		}
		pt[2 * numVertsOnOneFace - 1].x = 0;
		pt[2 * numVertsOnOneFace - 1].z = 0;
		pt[2 * numVertsOnOneFace - 1].y = 0;
		float x1 = sqrt(radius*radius / 2);
		for (int i = 0; i < additionVerts; i++) {
			int index = i + 2 * numVertsOnOneFace;
			pt[index].x = x1-x1 / (numVertsParabol - 1)*i;
			pt[index].z = pt[index].x;
			pt[index].y = width+ dWidth;
		}



		numFaces = numVertsOnOneFace - 2 + additionVerts ;
		face = new Face[numFaces];
		//faces around
		for (int i = 0; i < numVertsOnOneFace - 2; i++) {
			face[i].nVerts = 4;
			face[i].vert = new VertexID[face[i].nVerts];
			face[i].vert[0].vertIndex = i;
			face[i].vert[1].vertIndex = i + numVertsOnOneFace;
			face[i].vert[2].vertIndex = i + numVertsOnOneFace + 1;
			face[i].vert[3].vertIndex = i + 1;
			for (int m = 0; m < face[i].nVerts; m++)
				face[i].vert[m].colorIndex = 0;
		}
		//Top Faces
		for (int i = 0; i < additionVerts-1; i++) {
			int index = numVertsOnOneFace - 2 + i;
			face[index].nVerts = 4;
			face[index].vert = new VertexID[face[index].nVerts];
			face[index].vert[0].vertIndex = numVertsCircle + i;
			face[index].vert[1].vertIndex = numVertsCircle + i + 1;
			face[index].vert[2].vertIndex = i + numVertsOnOneFace * 2 + 1;
			face[index].vert[3].vertIndex = i + numVertsOnOneFace * 2;
			for (int m = 0; m < face[index].nVerts; m++)
				face[index].vert[m].colorIndex = 0;
		}

		face[numFaces-1].nVerts = numVertsCircle+1;
		face[numFaces - 1].vert = new VertexID[face[numFaces - 1].nVerts];
		for (int i = 0; i <= numVertsCircle; i++) {
			face[numFaces - 1].vert[i].vertIndex = i;
		}
		for (int i = 0; i < face[numFaces - 1].nVerts; i++)
			face[numFaces - 1].vert[i].colorIndex = 0;
	}

