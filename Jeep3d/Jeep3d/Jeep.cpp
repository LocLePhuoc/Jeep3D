// Bai3.cpp : Defines the entry point for the console application.
//


#include <math.h>
#include <iostream>
#include "supportClass.h"
#include "Mesh.h"
#include "Wheel.h"
#define D2G 3.14159/180

#define PI			3.1415926
using namespace std;

//camera variables

int o_x, o_y;
float eyeX, eyeY, eyeZ;
float centerX, centerY, centerZ;
float upX, upY, upZ;
float alpha = 45;
float beta = 45;
float deltaAngle = 5;
float dR = 0.2;
float Radius = 50;
float orthorScaler = 3;

GLfloat angle;
int		screenWidth = 800;
int		screenHeight= 800;

Mesh	cylinder;
Mesh	curvedCylinder;
Mesh	sphere;
int		nChoice = 1;

Wheel TyrePart1;
Wheel TyrePart2;
Wheel TyrePart3;
Wheel RimPart1;
Wheel RimPart2;
Wheel RimPart3;
Mesh Cl;

//jeep bar
Mesh barCurveSide;

//jeep light
Mesh jeepLight;

//front panel
Mesh frontPanelCornerCylinder;
Mesh frontGrille;
Mesh frontPanelTop;
Mesh frontSide;
Mesh frontfrontSide2;

//jeep front
Mesh jeepFrontCylinder;

//Rim
Mesh rimSideCorner;
Mesh rimFrontEdge;
Mesh rimEdge;
Mesh rimBackCorner;
Mesh rimBackTopEdge;
Mesh rimFrontSideEdge;
Mesh rimBackEdge;

//jeep body
Mesh bodyFrontSideCorner;
Mesh bodyFrontEdge;
Mesh bodySideEdge;
Mesh bodyBackCorner;
Mesh bodyBackTopEdge;
Mesh bodyFrontSideEdge;
Mesh bodyBackSideEdge;

float wheelAxisLength = 52.0f;
float wheelScaleFactor = 4.5;
//color
float qaRed[] = { 1.0,0.0,0.0,1.0 };
float qaGreen[] = { 0.0,1.0,0.0,1.0 };
float qaBlue[] = { 0.0,0.0,1.0,1.0 };
float qaYellow[] = { 1.0,1.0,0.0,1.0 };
float qaBlack[] = { 0.0,0.0,0.0,1.0 };
float qaWhite[] = { 1.0,1.0,1.0,1.0 };
float qaPupple[] = { 1.0,0.0,1.0,1.0 };
float qaGray[] = { 0.5,0.5,0.5,1.0 };
float qaTyre[] = { 0.2,0.2,0.2,1.0 };
float qaGray2[] = { 0.95,0.95,0.95,1.0 };

bool isLeftDoorOpen = false;
bool isRightDoorOpen = false;
bool secondLightOn = false;
float leftDoorAngle = 0;
float rightDoorAngle = 0;


//materials for specific parts
float rim_ambient[] = { 0.05375f, 0.05f, 0.06625f, 0.82f };
float rim_diffuse[] = { 0.18275f, 0.17f, 0.22525f, 0.82f };
float rim_specular[] = { 0.4f, 0.4f, 0.4f, 1.0f };
float rim_shine = 60 ;

float glass_ambient[] = { 0.23125f, 0.23125f, 0.23125f, 1.0f };
float glass_diffuse[] = { 0.2775f, 0.2775f, 0.2775f, 1.0f };
float glass_specular[] = { 0.774597f, 0.774597f, 0.774597f, 1.0f };
float glass_shine = 76.8f;

//coordinates of the car, used for moving
float xCoord;
float yCoord;
float zCoord;

//obstacles
Mesh pillarObstacle;

//functions for setting up jeep body parts
void setUpJeepBar(float length, float height, float radius) {
	barCurveSide.CreateOval(radius, length / 3, height);
}

void setUpJeepLight(float radius) {
	jeepLight.CreateSphereCorner(20, 20, radius);
}

void setUpFrontPanelCorner(float length, float height, float radius) {
	frontPanelCornerCylinder.CreateCylinder(20, 20, 2 * height, radius, radius, 90, 0);
}

void setUpFrontPanel(float length, float height, float radius) {
	frontGrille.CreateOvalWithHole(radius, length, height, radius * 2 / 3);
	frontPanelTop.CreateCuboid(height, 26 * radius, height);
	frontSide.CreateCuboid(height, length + 2 * radius, 7 * radius);
	frontfrontSide2.CreateCuboid(height, height + radius / 3, 26 * radius);
}

void setUpJeepFront(float length, float width, float EdgeRadius, float sHeight, float height, float deltaHeight) {
	jeepFrontCylinder.CreateCylinder(10, 10, length, EdgeRadius, EdgeRadius, 90, deltaHeight);
}

void setUpRIM(float length, float width, float lHeight, float sHeight, float edgeRadius, float edgeCurveRadius, float steepAngle) {
	rimSideCorner.CreateCurvedCylinder(20, 20, edgeCurveRadius, edgeRadius, steepAngle, 90);
	rimFrontEdge.CreateCylinder(20, 20, width - 2 * edgeRadius, edgeCurveRadius + edgeRadius, edgeCurveRadius + edgeRadius, steepAngle, 0);
	rimEdge.CreateCylinder(20, 20, length - edgeRadius - edgeCurveRadius, edgeRadius, edgeRadius, 90, 0);
	rimBackCorner.CreateCurvedCylinder(20, 20, edgeCurveRadius, edgeRadius, steepAngle, 90);
	rimBackTopEdge.CreateCylinder(20, 20, width - 2 * edgeRadius, edgeCurveRadius + edgeRadius, edgeCurveRadius + edgeRadius, steepAngle, 0);
	rimFrontSideEdge.CreateCylinder(20, 20, lHeight - sHeight - edgeCurveRadius * (1 - cos(steepAngle * D2G))
		, edgeRadius, edgeRadius, 90, (lHeight - sHeight) * tan((90 - steepAngle) * D2G));
	rimBackEdge.CreateCylinder(20, 20, 0.1*lHeight, edgeRadius, edgeRadius, 90, 0);
}

void setUpJeepBody(float length, float width, float lHeight, float sHeight, float rimLength, float rimHeight, float edgeRadius, float edgeCurveRadius, float steepAngle) {
	bodyFrontSideCorner.CreateCurvedCylinder(20, 20, edgeCurveRadius, edgeRadius, steepAngle, 90);
	bodyFrontEdge.CreateCylinder(20, 20, width - 2 * edgeRadius, edgeCurveRadius + edgeRadius, edgeCurveRadius + edgeRadius, steepAngle, 0);
	bodySideEdge.CreateCylinder(20, 20, length - edgeRadius - edgeCurveRadius, edgeRadius, edgeRadius, 90, 0);
	bodyBackTopEdge.CreateCylinder(20, 20, width - 2 * edgeRadius, edgeRadius, edgeRadius, 90, 0);
	bodyBackCorner.CreateSphereCorner(20, 20, edgeRadius);
	bodyFrontSideEdge.CreateCylinder(20, 20, lHeight - sHeight - edgeCurveRadius * (1 - cos(steepAngle * D2G))
		, edgeRadius, edgeRadius, 90, (lHeight - sHeight) * tan((90 - steepAngle) * D2G));
	bodyBackSideEdge.CreateCylinder(20, 20, lHeight - rimHeight * 0.5, edgeRadius, edgeRadius, 90, 0);
}

void drawAxis()
{
	glColor3f(0.8, 0.8, 0.8);
	glBegin(GL_LINES);
		glVertex3f(0, 0, 0);
		glVertex3f(4, 0, 0);

		glVertex3f(0, 0, 0);
		glVertex3f(0, 4, 0);

		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 4);
	glEnd();
}

void myKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1':
		leftDoorAngle += 5;
		if (leftDoorAngle >= 90)
			leftDoorAngle = 90;
		break;
	case '2':
		leftDoorAngle -= 5;
		if (leftDoorAngle <= 0)
			leftDoorAngle = 0;
		break;
	case '3':
		rightDoorAngle += 5;
		if (rightDoorAngle >= 90)
			rightDoorAngle = 90;
		break;
	case '4':
		rightDoorAngle -= 5;
		if (rightDoorAngle <= 0)
			rightDoorAngle = 0;
		break;
	case 'l' | 'L':
		secondLightOn = !secondLightOn;
		break;
	case 'k' | 'K':
		Radius += 2;
		break;
	case 'i' | 'I':
		Radius -= 2;
		break;
	case 'w' | 'W' :
		xCoord += 5;
		break;
	case 's' | 'S':
		xCoord -= 5;
		break;
	case 'a' | 'A':
		zCoord -= 5;
		break;
	case 'd' | 'D':
		zCoord += 5;
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

void setupMaterial(float ambient[], float diffuse[], float specular[], float shiness)
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiness);
}

void drawTyrePart2() {
	glPushMatrix();
	glTranslatef(-0.75 + 0.35 / 2, 0, 0);
	int n = 96;
	float phi = 2 * PI / n;
	for (int i = 0; i < n; i++) {
		glPushMatrix();
		glTranslatef(0, 3 * cos(i*phi), 3 * sin(i*phi));
		glRotatef(i * 360.f / n, 1, 0, 0);
		TyrePart2.Draw();
		glTranslatef(0.35 / 2 + 0.02 + 0.38 / 2, 0, 0);
		TyrePart3.Draw();
		glPopMatrix();
	}
	glPopMatrix();
}
void drawRimPart2() {
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	for (int i = 0; i < 4; i++) {
		glRotatef(90, 0, 1, 0);
		glPushMatrix();
		RimPart2.Draw();
		glScalef(1, 1, -1);
		RimPart2.Draw();
		glPopMatrix();
	}
	glPopMatrix();
	//
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	for (int i = 0; i < 4; i++) {
		glRotatef(90, 0, 1, 0);
		glPushMatrix();
		glScalef(1.0, -1.0, 1.0);
		RimPart3.Draw();
		glScalef(1, 1, -1);
		RimPart3.Draw();
		glPopMatrix();
	}
	glPopMatrix();
}
void drawRimPart1() {
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	RimPart1.Draw();

	glPopMatrix();
}
void drawTyrePart1() {
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	TyrePart1.Draw();
	glPopMatrix();
}
void drawHaftWheel() {
	glPushMatrix();
	//Setup Material
	setupMaterial(qaTyre, qaTyre, qaBlack, 60.0);
	//Draw
	drawTyrePart1();
	//Setup Material
	setupMaterial(qaTyre, qaTyre, qaBlack, 60.0);
	//Draw
	drawTyrePart2();
	//Setup Material
	setupMaterial(qaGray2, qaGray2, qaWhite, 60.0);
	//Draw
	drawRimPart1();
	glPopMatrix();
}
void drawWheel() {
	glPushMatrix();
	drawHaftWheel();
	glScalef(-1, 1, 1);
	drawHaftWheel();
	//Setup Material
	setupMaterial(qaGray2, qaGray2, qaWhite, 60.0);
	glPopMatrix();
	//Draw
	drawRimPart2();

}

void drawWheelWithCylinderAxis() {
	glPushMatrix();
	glTranslatef(-wheelAxisLength / 2, 0, 0);
	glScalef(wheelScaleFactor, wheelScaleFactor, wheelScaleFactor);
	drawWheel();
	glPopMatrix();

	glPushMatrix();
	glScalef(-1, 1, 1);
		glPushMatrix();
		glTranslatef(-wheelAxisLength / 2, 0, 0);
		glScalef(wheelScaleFactor, wheelScaleFactor, wheelScaleFactor);
		drawWheel();
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glScalef(1, wheelScaleFactor, wheelScaleFactor);
	glRotatef(90, 0, 0, 1);
	Cl.Draw();
	glPopMatrix();

}

/*
*    length: width of the bar
*    height: height of the bar
*    radius: curveness of corner & depth of the bar
*/
void drawFan(float x, float y, float z, float radius, float angle, float nSegment, int flag) {
	float alpha = angle * D2G / nSegment;
	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(0, 0, flag);
	glVertex3f(x, y, z);
	float cx, cy;
	for (int i = 0; i <= nSegment; i++) {
		cx = x + radius * sin(alpha * i);
		cy = y + radius * cos(alpha * i);
		glVertex3f(cx, cy, z);
	}
	glEnd();
}

void drawBar(float length, float height, float radius) {
	glPushMatrix();
	glTranslatef(length / 3, 0, 0);
	barCurveSide.DrawFaces(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-length / 3, 0, 0);
	barCurveSide.DrawFaces(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -length / 50);
	barCurveSide.DrawFaces(1);
	glPopMatrix();
}

void drawLight(float radius) {
	glPushMatrix();
	glRotatef(-90, 0, 0, 1);
	glPushMatrix();
	jeepLight.DrawFaces(-1);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	jeepLight.DrawFaces(-1);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-90, 0, 1, 0);
	jeepLight.DrawFaces(-1);
	glPopMatrix();
	
	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	jeepLight.DrawFaces(-1);
	glPopMatrix();
	glPopMatrix();
}

void drawFrontPanelCorner(float length, float height, float radius) {
	glPushMatrix();
	glTranslatef(1.5 * height, length / 2 + height, 13 * radius);
	glRotatef(90, 0, 0, 1);
	glPushMatrix();
	frontPanelCornerCylinder.DrawFaces(-1);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	drawFan(0, 0, 0, radius, 90, 20, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 2 * height, 0);
	glRotatef(90, 1, 0, 0);
	drawFan(0, 0, 0, radius, 90, 20, -1);
	glPopMatrix();
	glPopMatrix();

}

void drawFront(float length, float height, float radius) {
	glPushMatrix();
	glPushMatrix();
	glTranslatef(0, 0, 6 * radius);
	glRotatef(90, 0, 0, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 4 * radius);
	glRotatef(90, 0, 0, 1);
	frontGrille.DrawFaces(-1);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0, 0, 2 * radius);
	glRotatef(90, 0, 0, 1);
	frontGrille.DrawFaces(-1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 0);
	glRotatef(90, 0, 0, 1);
	frontGrille.DrawFaces(-1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -2 * radius);
	glRotatef(90, 0, 0, 1);
	frontGrille.DrawFaces(-1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -4 * radius);
	glRotatef(90, 0, 0, 1);
	frontGrille.DrawFaces(-1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -6 * radius);
	glRotatef(90, 0, 0, 1);
	frontGrille.DrawFaces(-1);
	glPopMatrix();

	//      Draw Light
	glPushMatrix();
	glTranslatef(3 * height / 2, 0, 10 * radius);
	drawLight(2 * radius);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3 * height / 2, 0, -10 * radius);
	drawLight(2 * radius);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0, length / 2 + radius + height / 2, 0);
	glRotatef(90, 1, 0, 0);
	frontPanelTop.DrawFaces(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -(length / 2 + radius + height / 2), 0);
	glRotatef(90, 1, 0, 0);
	frontPanelTop.DrawFaces(1);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0, 0, 10.5 * radius);
	frontSide.DrawFaces(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -10.5 * radius);
	frontSide.DrawFaces(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(height, 0, 0);
	glPushMatrix();
	glTranslatef(0, 0, 10.5 * radius);
	frontSide.DrawFaces(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -10.5 * radius);
	frontSide.DrawFaces(1);
	glPopMatrix();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(height, length /  2 + radius + height- (height + radius / 3) / 2, 0);
	frontfrontSide2.DrawFaces(1);
	glPopMatrix();

	frontfrontSide2.CreateCuboid(height, height + radius / 3, 26 * radius);
	frontfrontSide2.SetColor(0);
	glPushMatrix();
	glTranslatef(height, -(length / 2 + radius + height - (height + radius / 3) / 2), 0);
	frontfrontSide2.DrawFaces(1);
	glPopMatrix();

	drawFrontPanelCorner(length, height, radius);
	glPushMatrix();
	glScalef(1, 1, -1);
	drawFrontPanelCorner(length, height, radius);
	glPopMatrix();

	glPushMatrix();
	glScalef(1, -1, 1);
	drawFrontPanelCorner(length, height, radius);
	glPopMatrix();

	glPushMatrix();
	glScalef(1, -1, -1);
	drawFrontPanelCorner(length, height, radius);
	glPopMatrix();
	glPopMatrix();
}

void drawJeepFront(float length, float width, float EdgeRadius,float sHeight, float height, float deltaHeight) {
	glColor3f(0.8,0.8,0.8);
	glPushMatrix();
	glTranslatef(length,-deltaHeight,0);
	glRotatef(90, 0, 0, 1);
	glPushMatrix();
	glTranslatef(0, 0, width/2 - EdgeRadius);
	jeepFrontCylinder.DrawFaces(-1);
	glPopMatrix();

	glPushMatrix();
	glScalef(1, 1, -1);
	glTranslatef(0, 0, width / 2 - EdgeRadius);
	jeepFrontCylinder.DrawFaces(-1);
	glPopMatrix();
	glPopMatrix();

	glBegin(GL_QUADS);


	//front face1
	glNormal3f(1, 0, 0);
	glVertex3f(length, EdgeRadius - deltaHeight, width / 2 - EdgeRadius);
	glVertex3f(length, EdgeRadius - deltaHeight, -width / 2 + EdgeRadius);
	glVertex3f(length, - deltaHeight, -width / 2 + EdgeRadius);
	glVertex3f(length, - deltaHeight, width / 2 - EdgeRadius);

	//top face
	glNormal3f(0, 1, 0);
	glVertex3f(0, EdgeRadius, width / 2 - EdgeRadius);
	glVertex3f(0, EdgeRadius, -width / 2 + EdgeRadius);
	glVertex3f(length, EdgeRadius - deltaHeight, -width / 2 + EdgeRadius);
	glVertex3f(length, EdgeRadius - deltaHeight, width / 2 - EdgeRadius);

	glEnd();

	glBegin(GL_QUADS);
	//front face 2
	glNormal3f(1, 0, 0);
	glVertex3f(length, -height + EdgeRadius, width / 2);
	glVertex3f(length, -height + EdgeRadius, -width / 2);
	glVertex3f(length, -deltaHeight, -width / 2);
	glVertex3f(length, -deltaHeight, width / 2);
	
	//bottom face
	glNormal3f(0, -1, 0);
	glVertex3f(0, -height + EdgeRadius, width / 2);
	glVertex3f(0, -height + EdgeRadius, -width / 2);
	glVertex3f(length, -height + EdgeRadius, -width / 2);
	glVertex3f(length, -height + EdgeRadius, width / 2);

	//side face 1
	glNormal3f(0, 0, 1);
	glVertex3f(0, 0, width / 2);
	glVertex3f(0, -height + EdgeRadius, width / 2);
	glVertex3f(length, -height + EdgeRadius, width / 2);
	glVertex3f(length, -deltaHeight, width / 2);

	//side face 1
	glNormal3f(0, 0, -1);
	glVertex3f(0, 0, -width / 2);
	glVertex3f(0, -height + EdgeRadius, -width / 2);
	glVertex3f(length, -height + EdgeRadius, -width / 2);
	glVertex3f(length, -deltaHeight, -width / 2);
	
	glEnd();

	//draw front panel
	float panelHeight = width / 28;
	float panelEdgeRadius = width / 28;
	float panelLength = height;
	glPushMatrix();
	glTranslatef(length + (width / 28) / 2, - (2 * panelHeight + panelLength) / 2 -deltaHeight / 1.5, 0);
	drawFront(panelLength, panelHeight, panelEdgeRadius);
	glPopMatrix();

	float barLength = width * 1.1;
	float barHeight = height;
	float barEdge = EdgeRadius;

	//Y position of the bar
	float barY =  - deltaHeight - barHeight / 3 - (2 * panelHeight + panelLength);
	glPushMatrix();
	glTranslatef(length + (width / 28) * 1.1 + 2 * barEdge, barY, 0);
	//glRotatef(-90, 0, 0, 1);
	glRotatef(90, 0, 1, 0);
	drawBar(barLength, barHeight, barEdge);
	glPopMatrix();

}

void drawRIM(float length, float width, float lHeight, float sHeight, float edgeRadius, float edgeCurveRadius, float steepAngle) {
	setupMaterial(rim_ambient, rim_diffuse, qaBlack, rim_shine);
	float halfsteepAngle = steepAngle / 2;

	//front side corners
	glPushMatrix();
	glTranslatef(0, lHeight - edgeCurveRadius, width / 2 - edgeRadius);
	glRotatef(90, 0, 0, 1);
	glRotatef(90, 1, 0, 0);
	rimSideCorner.DrawFaces(1);
	glPopMatrix();

	glPushMatrix();
	glScalef(1, 1, -1);
	glTranslatef(0, lHeight - edgeCurveRadius, width / 2 - edgeRadius);
	glRotatef(90, 0, 0, 1);
	glRotatef(90, 1, 0, 0);
	rimSideCorner.DrawFaces(1);
	glPopMatrix();

	//front edge
	glPushMatrix();
	glTranslatef(0, lHeight - edgeCurveRadius, -width / 2 + edgeRadius);
	glRotatef(90, 0, 0, 1);
	glRotatef(90, 1, 0, 0);
	rimFrontEdge.DrawFaces(-1);
	glPopMatrix();

	//side edge
	glPushMatrix();
	glTranslatef(-length + edgeRadius + edgeCurveRadius, lHeight, -width / 2 + edgeRadius);
	glRotatef(90, 0, 1, 0);
	glRotatef(90, 0, 0, 1);
	glRotatef(90, 1, 0, 0);
	rimEdge.DrawFaces(-1);
	glPopMatrix();

	glPushMatrix();
	glScalef(1, 1, -1);
	glTranslatef(-length + edgeRadius + edgeCurveRadius, lHeight, -width / 2 + edgeRadius);
	glRotatef(90, 0, 1, 0);
	glRotatef(90, 0, 0, 1);
	glRotatef(90, 1, 0, 0);
	rimEdge.DrawFaces(-1);
	glPopMatrix();


	//back corners
	//sphere.CreateSphereCorner(20, 20, edgeRadius);
	glPushMatrix();
	glTranslatef(-length + edgeRadius + edgeCurveRadius, lHeight - edgeCurveRadius, -width / 2 + edgeRadius);
	glRotatef(-90, 0, 1, 0);
	glRotatef(90, 0, 0, 1);
	rimBackCorner.DrawFaces(1);
	glPopMatrix();

	glPushMatrix();
	glScalef(1, 1, -1);
	glTranslatef(-length + edgeRadius + edgeCurveRadius, lHeight - edgeCurveRadius, -width / 2 + edgeRadius);
	glRotatef(-90, 0, 1, 0);
	glRotatef(90, 0, 0, 1);
	rimBackCorner.DrawFaces(1);
	glPopMatrix();


	//back top edges
	//cylinder.CreateCylinder(20, 20, width - 2 * edgeRadius, edgeRadius, edgeRadius, 90, 0);
	glPushMatrix();
	glTranslatef(-length + edgeRadius + edgeCurveRadius, lHeight - edgeCurveRadius, width / 2 - edgeRadius);
	glRotatef(180, 0, 1, 0);
	glRotatef(90, 0, 0, 1);
	glRotatef(90, 1, 0, 0);
	rimBackTopEdge.DrawFaces(-1);
	glPopMatrix();

	//front side edges
	glPushMatrix();
	glTranslatef(edgeCurveRadius * sin(steepAngle * D2G),
		lHeight - edgeCurveRadius * (1 - cos(steepAngle * D2G)),
		-width / 2 + edgeRadius);
	glRotatef(180, 1, 0, 0);
	rimFrontSideEdge.DrawFaces(-1);
	glPopMatrix();

	glPushMatrix();
	glScalef(1, 1, -1);
	glTranslatef(edgeCurveRadius * sin(steepAngle * D2G), lHeight - edgeCurveRadius * (1 - cos(steepAngle * D2G)), -width / 2 + edgeRadius);
	glRotatef(180, 1, 0, 0);
	rimFrontSideEdge.DrawFaces(-1);
	glPopMatrix();

	//back edges
	glPushMatrix();
	glTranslatef(-length + edgeCurveRadius * sin(steepAngle * D2G) - edgeRadius / 4,
		0.88*lHeight,
		-width / 2 + edgeRadius);
	glRotatef(180, 0, 1, 0);
	rimBackEdge.DrawFaces(-1);
	glPopMatrix();

	glPushMatrix();
	glScalef(1, 1, -1);
	glTranslatef(-length + edgeCurveRadius * sin(steepAngle * D2G) - edgeRadius / 4,
		0.88*lHeight,
		-width / 2 + edgeRadius);
	glRotatef(180, 0, 1, 0);
	rimBackEdge.DrawFaces(-1);
	glPopMatrix();

	glBegin(GL_QUADS);
	////back
	glVertex3f(-length + edgeCurveRadius * sin(steepAngle * D2G) - edgeRadius,
		lHeight - edgeCurveRadius * (1 - cos(steepAngle * D2G)),
		width / 2 - edgeRadius);
	glVertex3f(-length + edgeCurveRadius * sin(steepAngle * D2G) - edgeRadius,
		lHeight - edgeCurveRadius * (1 - cos(steepAngle * D2G)),
		-width / 2 + edgeRadius);
	glVertex3f(-length + edgeCurveRadius * sin(steepAngle * D2G) - edgeRadius,
		0.9*lHeight,
		-width / 2 + edgeRadius);
	glVertex3f(-length + edgeCurveRadius * sin(steepAngle * D2G) - edgeRadius,
		0.9*lHeight,
		width / 2 - edgeRadius);

	//top
	glNormal3f(0, 1, 0);
	glVertex3f(0, lHeight + edgeRadius, width / 2 - edgeRadius);
	glVertex3f(0, lHeight + edgeRadius, -width / 2 + edgeRadius);
	glVertex3f(-length + edgeRadius + edgeCurveRadius, lHeight + edgeRadius, -width / 2 + edgeRadius);
	glVertex3f(-length + edgeRadius + edgeCurveRadius, lHeight + edgeRadius, width / 2 - edgeRadius);

	//front leap
	glNormal3f(sin(steepAngle * D2G), cos(steepAngle * D2G), 0);
	glVertex3f(edgeCurveRadius * sin(steepAngle * D2G) + edgeRadius, lHeight - edgeCurveRadius * (1 - cos(steepAngle * D2G)), width / 2 - edgeRadius);
	glVertex3f(edgeCurveRadius * sin(steepAngle * D2G) + edgeRadius, lHeight - edgeCurveRadius * (1 - cos(steepAngle * D2G)), -width / 2 + edgeRadius);
	glVertex3f(edgeCurveRadius * sin(steepAngle * D2G) + (lHeight - sHeight) * tan((90 - steepAngle) * D2G) + edgeRadius,
		sHeight, -width / 2 + edgeRadius);
	glVertex3f(edgeCurveRadius * sin(steepAngle * D2G) + (lHeight - sHeight) * tan((90 - steepAngle) * D2G) + edgeRadius,
		sHeight, width / 2 - edgeRadius);

	glEnd();
}

void drawJeepBody(float length, float width, float lHeight, float sHeight, float rimLength, float rimHeight , float edgeRadius, float edgeCurveRadius, float steepAngle) {
	setupMaterial(qaTyre, qaTyre, qaBlack, 60.0);

	//front side corners
	glPushMatrix();
	glTranslatef(0, lHeight - edgeCurveRadius, width / 2 - edgeRadius);
	glRotatef(90, 0, 0, 1);
	glRotatef(90, 1, 0, 0);
	bodyFrontSideCorner.DrawFaces(1);
	glPopMatrix();

	glPushMatrix();
	glScalef(1, 1, -1);
	glTranslatef(0, lHeight - edgeCurveRadius, width / 2 - edgeRadius);
	glRotatef(90, 0, 0, 1);
	glRotatef(90, 1, 0, 0);
	bodyFrontSideCorner.DrawFaces(1);
	glPopMatrix();

	//front edge
	glPushMatrix();
	glTranslatef(0, lHeight - edgeCurveRadius, - width / 2 + edgeRadius);
	glRotatef(90, 0, 0, 1);
	glRotatef(90, 1, 0, 0);
	bodyFrontEdge.DrawFaces(-1);
	glPopMatrix();

	//side edges
	glPushMatrix();
	glTranslatef(-length + edgeRadius + edgeCurveRadius, lHeight, -width / 2 + edgeRadius);
	glRotatef(90, 0, 1, 0);
	glRotatef(90, 0, 0, 1);
	glRotatef(90, 1, 0, 0);
	bodySideEdge.DrawFaces(-1);
	glPopMatrix();

	glPushMatrix();
	glScalef(1, 1, -1);
	glTranslatef(-length + edgeRadius + edgeCurveRadius, lHeight, -width / 2 + edgeRadius);
	glRotatef(90, 0, 1, 0);
	glRotatef(90, 0, 0, 1);
	glRotatef(90, 1, 0, 0);
	bodySideEdge.DrawFaces(-1);
	glPopMatrix();

	//back corners 
	glPushMatrix();
	glTranslatef(-length + edgeRadius + edgeCurveRadius, lHeight, width / 2 - edgeRadius);
	glRotatef(-90, 0, 1, 0);
	bodyBackCorner.DrawFaces(-1);
	glPopMatrix();

	glPushMatrix();
	glScalef(1, 1, -1);
	glTranslatef(-length + edgeRadius + edgeCurveRadius, lHeight, width / 2 - edgeRadius);
	glRotatef(-90, 0, 1, 0);
	bodyBackCorner.DrawFaces(-1);
	glPopMatrix();

	//back top edges

	glPushMatrix();
	glTranslatef(-length + edgeRadius + edgeCurveRadius, lHeight, width/2 - edgeRadius);
	glRotatef(180, 0, 1, 0);
	glRotatef(90, 0, 0, 1);
	glRotatef(90, 1, 0, 0);
	bodyBackTopEdge.DrawFaces(-1);
	glPopMatrix();


	//front side edges
	glPushMatrix();
	glTranslatef(edgeCurveRadius * sin(steepAngle * D2G), lHeight - edgeCurveRadius * (1 - cos(steepAngle * D2G)), -width / 2 + edgeRadius);
	glRotatef(180, 1, 0, 0);
	bodyFrontSideEdge.DrawFaces(-1);
	glPopMatrix();

	glPushMatrix();
	glScalef(1, 1, -1);
	glTranslatef(edgeCurveRadius * sin(steepAngle * D2G), lHeight - edgeCurveRadius * (1 - cos(steepAngle * D2G)), -width / 2 + edgeRadius);
	glRotatef(180, 1, 0, 0);
	bodyFrontSideEdge.DrawFaces(-1);
	glPopMatrix();

	//back side edges
	glPushMatrix();
	glTranslatef(-length + edgeRadius + edgeCurveRadius, rimHeight * 0.5, -width / 2 + edgeRadius);
	glRotatef(180, 0, 1, 0);
	bodyBackSideEdge.DrawFaces(-1);
	glPopMatrix();

	glPushMatrix();
	glScalef(1, 1, -1);
	glTranslatef(-length + edgeRadius + edgeCurveRadius, rimHeight * 0.5, -width / 2 + edgeRadius);
	glRotatef(180, 0, 1, 0);
	bodyBackSideEdge.DrawFaces(-1);
	glPopMatrix();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3f(0.8, 0.8, 0.8);
	glBegin(GL_QUADS);

	//back
	glNormal3f(-1, 0, 0);
	glVertex3f(-length + edgeCurveRadius, lHeight, width / 2 - edgeRadius);
	glVertex3f(-length + edgeCurveRadius, lHeight, -width / 2 + edgeRadius);
	glVertex3f(-length + edgeCurveRadius, rimHeight * 0.5, -width / 2 + edgeRadius);
	glVertex3f(-length + edgeCurveRadius, rimHeight * 0.5, width / 2 - edgeRadius);


	//roof
	glNormal3f(0, 1, 0);
	glVertex3f(0, lHeight + edgeRadius, width / 2 - edgeRadius);
	glVertex3f(0, lHeight + edgeRadius, -width / 2 + edgeRadius);
	glVertex3f(-length + edgeRadius + edgeCurveRadius, lHeight + edgeRadius, -width / 2 + edgeRadius);
	glVertex3f(-length + edgeRadius + edgeCurveRadius, lHeight + edgeRadius, width / 2 - edgeRadius);

	//wind shield
	setupMaterial(glass_ambient, glass_diffuse, qaBlack, glass_shine);

	float frontPanelHeight = lHeight - edgeCurveRadius * (1 - cos(steepAngle * D2G)) - sHeight;
	float frontPanelLength = (lHeight - sHeight) * tan((90 - steepAngle) * D2G);
	glColor3f(0.2, 0.2, 0.2);
	glNormal3f(1 / sqrt(2), 1 / sqrt(2), 0);
	glVertex3f(edgeCurveRadius * sin(steepAngle * D2G) + frontPanelLength * 0.1  + edgeRadius, 
		frontPanelHeight * 0.9 + sHeight, (width / 2 - edgeRadius));
	glVertex3f(edgeCurveRadius * sin(steepAngle * D2G) + frontPanelLength * 0.1 + edgeRadius,
		frontPanelHeight * 0.9 + sHeight, (-width / 2 + edgeRadius));
	glVertex3f(edgeCurveRadius * sin(steepAngle * D2G) + frontPanelLength * 0.9 + edgeRadius,
		frontPanelHeight * 0.1 + sHeight, (-width / 2 + edgeRadius));
	glVertex3f(edgeCurveRadius * sin(steepAngle * D2G) + frontPanelLength * 0.9 + edgeRadius,
		frontPanelHeight * 0.1 + sHeight, (width / 2 - edgeRadius));

	setupMaterial(qaTyre, qaTyre, qaBlack, 60.0);
	glColor3f(0.8, 0.8, 0.8);
	glVertex3f(edgeCurveRadius * sin(steepAngle * D2G) + edgeRadius,
		frontPanelHeight + sHeight, (width / 2 - edgeRadius));
	glVertex3f(edgeCurveRadius * sin(steepAngle * D2G) + edgeRadius,
		frontPanelHeight + sHeight, (-width / 2 + edgeRadius));
	glVertex3f(edgeCurveRadius * sin(steepAngle * D2G) + frontPanelLength * 0.1 + edgeRadius,
		frontPanelHeight * 0.9 + sHeight, (-width / 2 + edgeRadius));
	glVertex3f(edgeCurveRadius * sin(steepAngle * D2G) + frontPanelLength * 0.1 + edgeRadius,
		frontPanelHeight * 0.9 + sHeight, (width / 2 - edgeRadius));

	glVertex3f(edgeCurveRadius * sin(steepAngle * D2G) + frontPanelLength * 0.9 + edgeRadius,
		frontPanelHeight * 0.1 + sHeight, (width / 2 - edgeRadius));
	glVertex3f(edgeCurveRadius * sin(steepAngle * D2G) + frontPanelLength * 0.9 + edgeRadius,
		frontPanelHeight * 0.1 + sHeight, (-width / 2 + edgeRadius));
	glVertex3f(edgeCurveRadius * sin(steepAngle * D2G) + frontPanelLength + edgeRadius,
		sHeight, (-width / 2 + edgeRadius));
	glVertex3f(edgeCurveRadius * sin(steepAngle * D2G) + frontPanelLength + edgeRadius,
		sHeight, (width / 2 - edgeRadius));

	float windowLength = length / 5;

	//sides
	float sideLength = length - windowLength - edgeRadius - edgeCurveRadius;
	//right side
	setupMaterial(glass_ambient, glass_diffuse, qaBlack, glass_shine);
	glNormal3f(0, 0, -1);
	glColor3f(0.2, 0.2, 0.2);
	glVertex3f(-length + edgeRadius + edgeCurveRadius + sideLength * 1 / 8, lHeight - edgeCurveRadius, -width / 2);
	glVertex3f(-length + edgeRadius + edgeCurveRadius + sideLength * 6 / 8, lHeight - edgeCurveRadius, -width / 2);
	glVertex3f(-length + edgeRadius + edgeCurveRadius + sideLength * 6 / 8, frontPanelHeight * 0.1 + sHeight, -width / 2);
	glVertex3f(-length + edgeRadius + edgeCurveRadius + sideLength * 1 / 8, frontPanelHeight * 0.1 + sHeight, -width / 2);

	setupMaterial(qaTyre, qaTyre, qaBlack, 60.0);
	glNormal3f(0, 0, -1);
	glColor3f(0.8, 0.8, 0.8);
	glVertex3f(-length + edgeRadius + edgeCurveRadius, lHeight, -width / 2);
	glVertex3f(-windowLength - edgeRadius, lHeight, -width / 2);
	glVertex3f(-windowLength - edgeRadius, lHeight - edgeCurveRadius,- width / 2);
	glVertex3f(-length + edgeRadius + edgeCurveRadius, lHeight - edgeCurveRadius, -width / 2);

	glNormal3f(0, 0, -1);
	glColor3f(0.8, 0.8, 0.8);
	glVertex3f(-length + edgeRadius + edgeCurveRadius, lHeight - edgeCurveRadius, -width / 2);
	glVertex3f(-length + edgeRadius + edgeCurveRadius + sideLength * 1 / 8, lHeight - edgeCurveRadius, -width / 2);
	glVertex3f(-length + edgeRadius + edgeCurveRadius + sideLength * 1 / 8, frontPanelHeight * 0.1 + sHeight, -width / 2);
	glVertex3f(-length + edgeRadius + edgeCurveRadius, frontPanelHeight * 0.1 + sHeight, -width / 2);

	glNormal3f(0, 0, -1);
	glColor3f(0.8, 0.8, 0.8);
	glVertex3f(-windowLength - edgeRadius, lHeight - edgeCurveRadius, -width / 2);
	glVertex3f(-length + edgeRadius + edgeCurveRadius + sideLength * 6 / 8, lHeight - edgeCurveRadius, -width / 2);
	glVertex3f(-length + edgeRadius + edgeCurveRadius + sideLength * 6 / 8, frontPanelHeight * 0.1 + sHeight, -width / 2);
	glVertex3f(-windowLength - edgeRadius, frontPanelHeight * 0.1 + sHeight, -width / 2);


	glNormal3f(0, 0, -1);
	glColor3f(0.8, 0.8, 0.8);
	glVertex3f(-windowLength - edgeRadius, rimHeight, -width / 2);
	glVertex3f(-length + edgeRadius + edgeCurveRadius, rimHeight, -width / 2);
	glVertex3f(-length + edgeRadius + edgeCurveRadius, frontPanelHeight * 0.1 + sHeight, -width / 2);
	glVertex3f(-windowLength - edgeRadius, frontPanelHeight * 0.1 + sHeight, -width / 2);

	//left side
	setupMaterial(glass_ambient, glass_diffuse, qaBlack, glass_shine);
	glNormal3f(0, 0, 1);
	glColor3f(0.2, 0.2, 0.2);
	glVertex3f(-length + edgeRadius + edgeCurveRadius + sideLength * 1 / 8, lHeight - edgeCurveRadius, width / 2);
	glVertex3f(-length + edgeRadius + edgeCurveRadius + sideLength * 6 / 8, lHeight - edgeCurveRadius, width / 2);
	glVertex3f(-length + edgeRadius + edgeCurveRadius + sideLength * 6 / 8, frontPanelHeight * 0.1 + sHeight, width / 2);
	glVertex3f(-length + edgeRadius + edgeCurveRadius + sideLength * 1 / 8, frontPanelHeight * 0.1 + sHeight, width / 2);
	
	setupMaterial(qaTyre, qaTyre, qaBlack, 60.0);
	glNormal3f(0, 0, 1);
	glColor3f(0.8, 0.8, 0.8);
	glVertex3f(-length + edgeRadius + edgeCurveRadius, lHeight, width / 2);
	glVertex3f(-windowLength - edgeRadius, lHeight, width / 2);
	glVertex3f(-windowLength - edgeRadius, lHeight - edgeCurveRadius, width / 2);
	glVertex3f(-length + edgeRadius + edgeCurveRadius, lHeight - edgeCurveRadius, width / 2);

	glNormal3f(0, 0, 1);
	glColor3f(0.8, 0.8, 0.8);
	glVertex3f(-length + edgeRadius + edgeCurveRadius, lHeight - edgeCurveRadius, width / 2);
	glVertex3f(-length + edgeRadius + edgeCurveRadius + sideLength * 1 / 8, lHeight - edgeCurveRadius, width / 2);
	glVertex3f(-length + edgeRadius + edgeCurveRadius + sideLength * 1 / 8, frontPanelHeight * 0.1 + sHeight, width / 2);
	glVertex3f(-length + edgeRadius + edgeCurveRadius, frontPanelHeight * 0.1 + sHeight, width / 2);

	glNormal3f(0, 0, 1);
	glColor3f(0.8, 0.8, 0.8);
	glVertex3f(-windowLength - edgeRadius, lHeight - edgeCurveRadius, width / 2);
	glVertex3f(-length + edgeRadius + edgeCurveRadius + sideLength * 6 / 8, lHeight - edgeCurveRadius, width / 2);
	glVertex3f(-length + edgeRadius + edgeCurveRadius + sideLength * 6 / 8, frontPanelHeight * 0.1 + sHeight, width / 2);
	glVertex3f(-windowLength - edgeRadius, frontPanelHeight * 0.1 + sHeight, width / 2);


	glNormal3f(0, 0, 1);
	glColor3f(0.8, 0.8, 0.8);
	glVertex3f(-windowLength - edgeRadius, rimHeight, width / 2);
	glVertex3f(-length + edgeRadius + edgeCurveRadius , rimHeight, width / 2);
	glVertex3f(-length + edgeRadius + edgeCurveRadius , frontPanelHeight * 0.1 + sHeight, width / 2);
	glVertex3f(-windowLength - edgeRadius, frontPanelHeight * 0.1 + sHeight, width / 2);

	glEnd();

	//right door
	glPushMatrix();
		glTranslatef(edgeCurveRadius* sin(steepAngle * D2G) + (lHeight - sHeight) * tan((90 - steepAngle) * D2G), 0, -width / 2);
		glRotatef(-rightDoorAngle, 0, 1, 0);
		glTranslatef(-edgeCurveRadius * sin(steepAngle * D2G) - (lHeight - sHeight) * tan((90 - steepAngle) * D2G), 0, width / 2);

		setupMaterial(glass_ambient, glass_diffuse, qaBlack, glass_shine);
		glBegin(GL_POLYGON);
		glColor3f(0.2, 0.2, 0.2);
		glNormal3f(0, 0, -1);
		glVertex3f(0, lHeight - edgeCurveRadius, -width / 2);
		glVertex3f(-windowLength, lHeight - edgeCurveRadius, -width / 2);
		glVertex3f(-windowLength, frontPanelHeight * 0.1 + sHeight, -width / 2);
		glVertex3f((lHeight - edgeCurveRadius - frontPanelHeight * 0.1 - sHeight) / tan(steepAngle * D2G)
			, frontPanelHeight * 0.1 + sHeight, -width / 2);
		glEnd();

		setupMaterial(qaTyre, qaTyre, qaBlack, 60.0);

			glBegin(GL_POLYGON);
			glColor3f(0.8, 0.8, 0.8);
			glNormal3f(0, 0, -1);
			glVertex3f(-windowLength - edgeRadius, lHeight - edgeCurveRadius, -width/2);
			glVertex3f(-windowLength - edgeRadius, frontPanelHeight * 0.1 + sHeight, -width/2);
			glVertex3f(-windowLength, frontPanelHeight * 0.1 + sHeight, -width/2);
			glVertex3f(-windowLength, lHeight - edgeCurveRadius, -width/2);
			glEnd();

			glBegin(GL_POLYGON);
			glNormal3f(0, 0, -1);
			glVertex3f(0, lHeight - edgeCurveRadius, -width/2);
			glVertex3f(-windowLength - edgeRadius, lHeight - edgeCurveRadius, -width/2);
			glVertex3f(-windowLength - edgeRadius, lHeight, -width/2);
			glVertex3f(0, lHeight, -width/2);
			glEnd();


			glBegin(GL_POLYGON);
			glNormal3f(0, 0, -1);
			glVertex3f(-windowLength - edgeRadius, frontPanelHeight * 0.1 + sHeight, -width/2);
			glVertex3f(-windowLength - edgeRadius, 0, -width/2);
			glVertex3f(edgeCurveRadius * sin(steepAngle * D2G) + (lHeight - sHeight) * tan((90 - steepAngle) * D2G), 0, -width/2);
			glVertex3f(edgeCurveRadius * sin(steepAngle * D2G) + (lHeight - sHeight) * tan((90 - steepAngle) * D2G), sHeight, -width/2);
			glVertex3f(edgeCurveRadius * sin(steepAngle * D2G) + (lHeight - sHeight) * tan((90 - steepAngle) * D2G) - frontPanelHeight * 0.1 / tan(steepAngle * D2G)
				, frontPanelHeight * 0.1 + sHeight, -width/2);
			glEnd();

			glBegin(GL_POLYGON);
			glNormal3f(0, 0, -1);
			glVertex3f(0, lHeight - edgeCurveRadius, -width/2);
			glVertex3f(edgeCurveRadius * sin(steepAngle * D2G), lHeight - edgeCurveRadius * (1 - cos(steepAngle * D2G)), -width/2);
			glVertex3f(edgeCurveRadius * sin(steepAngle * D2G) + (lHeight - sHeight) * tan((90 - steepAngle) * D2G) - frontPanelHeight * 0.1 / tan(steepAngle * D2G)
				, frontPanelHeight * 0.1 + sHeight, -width/2);
			glVertex3f((lHeight - edgeCurveRadius - frontPanelHeight * 0.1 - sHeight) / tan(steepAngle * D2G)
				, frontPanelHeight * 0.1 + sHeight, -width/2);
			glEnd();

	drawFan(0, lHeight - edgeCurveRadius, -width / 2, edgeCurveRadius, steepAngle, 20, -1);
	glPopMatrix();

	//left door
	glPushMatrix();
		glTranslatef(edgeCurveRadius * sin(steepAngle * D2G) + (lHeight - sHeight) * tan((90 - steepAngle) * D2G), 0, width / 2);
		glRotatef(leftDoorAngle, 0, 1, 0);
		glTranslatef(-edgeCurveRadius * sin(steepAngle * D2G) - (lHeight - sHeight) * tan((90 - steepAngle) * D2G), 0, -width / 2);

	setupMaterial(glass_ambient, glass_diffuse, qaBlack, glass_shine);

	glBegin(GL_POLYGON);
	glColor3f(0.2, 0.2, 0.2);
	glNormal3f(0, 0, 1);
	glVertex3f(0, lHeight - edgeCurveRadius, width / 2);
	glVertex3f(-windowLength, lHeight - edgeCurveRadius, width / 2);
	glVertex3f(-windowLength, frontPanelHeight * 0.1 + sHeight, width / 2);
	glVertex3f((lHeight - edgeCurveRadius - frontPanelHeight * 0.1 - sHeight) / tan (steepAngle * D2G)
		, frontPanelHeight * 0.1 + sHeight, width / 2);
	glEnd();

	setupMaterial(qaTyre, qaTyre, qaBlack, 60.0);
	glBegin(GL_POLYGON);
	glColor3f(0.8, 0.8, 0.8);
	glNormal3f(0, 0, 1);
	glVertex3f(-windowLength - edgeRadius, lHeight - edgeCurveRadius, width / 2);
	glVertex3f(-windowLength - edgeRadius, frontPanelHeight * 0.1 + sHeight, width / 2);
	glVertex3f(-windowLength, frontPanelHeight * 0.1 + sHeight, width / 2);
	glVertex3f(-windowLength, lHeight - edgeCurveRadius, width / 2);
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0, 0, 1);
	glVertex3f(0, lHeight - edgeCurveRadius, width / 2);
	glVertex3f(-windowLength - edgeRadius, lHeight - edgeCurveRadius, width / 2);
	glVertex3f(-windowLength - edgeRadius, lHeight, width / 2);
	glVertex3f(0, lHeight, width / 2);
	glEnd();


	glBegin(GL_POLYGON);
	glNormal3f(0, 0, 1);
	glVertex3f(-windowLength - edgeRadius, frontPanelHeight * 0.1 + sHeight, width / 2);
	glVertex3f(-windowLength - edgeRadius, 0, width / 2);
	glVertex3f(edgeCurveRadius * sin(steepAngle * D2G) + (lHeight - sHeight) * tan((90 - steepAngle) * D2G), 0, width / 2);
	glVertex3f(edgeCurveRadius * sin(steepAngle * D2G) + (lHeight - sHeight) * tan((90 - steepAngle) * D2G), sHeight, width / 2);
	glVertex3f(edgeCurveRadius * sin(steepAngle * D2G) + (lHeight - sHeight) * tan((90 - steepAngle) * D2G) - frontPanelHeight * 0.1 / tan(steepAngle * D2G)
		, frontPanelHeight * 0.1 + sHeight, width / 2);
	glEnd();
	
	glBegin(GL_POLYGON);
	glNormal3f(0, 0, 1);
	glVertex3f(0, lHeight - edgeCurveRadius, width / 2);
	glVertex3f(edgeCurveRadius * sin(steepAngle * D2G), lHeight - edgeCurveRadius * (1 - cos(steepAngle * D2G)), width / 2);
	glVertex3f(edgeCurveRadius * sin(steepAngle * D2G) + (lHeight - sHeight) * tan((90 - steepAngle) * D2G) - frontPanelHeight * 0.1 / tan(steepAngle * D2G)
		, frontPanelHeight * 0.1 + sHeight, width / 2);
	glVertex3f((lHeight - edgeCurveRadius - frontPanelHeight * 0.1 - sHeight) / tan(steepAngle * D2G)
		, frontPanelHeight * 0.1 + sHeight, width / 2);
	glEnd();

	drawFan(0, lHeight - edgeCurveRadius, width / 2, edgeCurveRadius, steepAngle, 20, 1);
	glPopMatrix();

	//draw jeep front

	glPushMatrix();
	glTranslatef(edgeCurveRadius * sin(steepAngle * D2G) + (lHeight - sHeight) * tan((90 - steepAngle) * D2G), sHeight - edgeRadius, 0);
	drawJeepFront(length * 0.8, width, edgeRadius, sHeight, sHeight - rimHeight, edgeRadius);
	glPopMatrix();

	//draw rims
	glPushMatrix();
	glTranslatef(-length + edgeCurveRadius + rimLength , 0, width / 2 + width / 8 + edgeRadius / 2);
	drawRIM(rimLength, width / 4, rimHeight, 0, edgeRadius, edgeCurveRadius, steepAngle);
	glPopMatrix();

	glPushMatrix();
	glScalef(-1, 1, 1);
	glTranslatef(-length * 0.8 + rimLength - (edgeCurveRadius * sin(steepAngle * D2G) + frontPanelLength)
		, 0, width / 2 + width / 8 + edgeRadius / 2) ;
	drawRIM(rimLength, width / 4, rimHeight, 0, edgeRadius, edgeCurveRadius, steepAngle);
	glPopMatrix();

	glPushMatrix();
	glScalef(1, 1, - 1);
	glPushMatrix();
	glTranslatef(-length + edgeCurveRadius + rimLength, 0, width / 2 + width / 8 + edgeRadius / 2);
	drawRIM(rimLength, width / 4, rimHeight, 0, edgeRadius, edgeCurveRadius, steepAngle);
	glPopMatrix();

	glPushMatrix();
	glScalef(-1, 1, 1);
	glTranslatef(-length * 0.8 + rimLength - (edgeCurveRadius * sin(steepAngle * D2G) + frontPanelLength)
		, 0, width / 2 + width / 8 + edgeRadius / 2);
	drawRIM(rimLength, width / 4, rimHeight, 0, edgeRadius, edgeCurveRadius, steepAngle);
	glPopMatrix();
	glPopMatrix();

	//draw jeep body around rims
	setupMaterial(qaTyre, qaTyre, qaBlack, 60.0);

	float rimFullLength = rimLength + edgeCurveRadius * sin(steepAngle * D2G) + rimHeight * tan((90 - steepAngle) * D2G);

	glBegin(GL_POLYGON);
	glColor3f(0.8, 0.8, 0.8);
	glNormal3f(0, 0, 1);
	glVertex3f(-windowLength - edgeRadius, 0, width / 2);
	glVertex3f(-windowLength - edgeRadius, rimHeight, width / 2);
	glVertex3f(-length + edgeCurveRadius + rimLength + edgeCurveRadius * sin(steepAngle * D2G), rimHeight, width / 2);
	glVertex3f(-length + rimFullLength + edgeCurveRadius * sin(steepAngle * D2G), 0, width / 2);
	glEnd();

	glPushMatrix();
	glScalef(1, 1, -1);
	glBegin(GL_POLYGON);
	glColor3f(0.8, 0.8, 0.8);
	glNormal3f(0, 0, 1);
	glVertex3f(-windowLength - edgeRadius, 0, width / 2);
	glVertex3f(-windowLength - edgeRadius, rimHeight, width / 2);
	glVertex3f(-length + edgeCurveRadius + rimLength + edgeCurveRadius * sin(steepAngle * D2G), rimHeight, width / 2);
	glVertex3f(-length + rimFullLength + edgeCurveRadius * sin(steepAngle * D2G), 0, width / 2);
	glEnd();
	glPopMatrix();


	glBegin(GL_POLYGON);
	glNormal3f(-1/ sqrt(2), -1 / sqrt(2),0);
	glVertex3f(-length + rimFullLength + edgeCurveRadius * sin(steepAngle * D2G), 0, width / 2);
	glVertex3f(-length + edgeCurveRadius + rimLength + edgeCurveRadius * sin(steepAngle * D2G), rimHeight, width / 2);
	glVertex3f(-length + edgeCurveRadius + rimLength + edgeCurveRadius * sin(steepAngle * D2G), rimHeight, -width / 2);
	glVertex3f(-length + rimFullLength + edgeCurveRadius * sin(steepAngle * D2G), 0, -width / 2);
	glEnd();

	//X position of front rim
	float frontRimX = length * 0.8 - rimLength + frontPanelLength;
	float frontRimX2 = frontRimX - rimFullLength + rimLength + edgeCurveRadius * sin(steepAngle * D2G);
	glBegin(GL_POLYGON);
	glColor3f(0.8, 0.8, 0.8);
	glNormal3f(0, 0, 1);
	glVertex3f(edgeCurveRadius * sin(steepAngle * D2G) + (lHeight - sHeight) * tan((90 - steepAngle) * D2G), 0, width / 2);
	glVertex3f(edgeCurveRadius * sin(steepAngle * D2G) + (lHeight - sHeight) * tan((90 - steepAngle) * D2G), rimHeight, width / 2);
	glVertex3f(frontRimX, rimHeight, width / 2);
	glVertex3f(frontRimX2, 0, width / 2);
	glEnd();

	
	glPushMatrix();
	glScalef(1, 1, -1);
	glBegin(GL_POLYGON);
	glColor3f(0.8, 0.8, 0.8);
	glNormal3f(0, 0, 1);
	glVertex3f(edgeCurveRadius * sin(steepAngle * D2G) + (lHeight - sHeight) * tan((90 - steepAngle) * D2G), 0, width / 2);
	glVertex3f(edgeCurveRadius * sin(steepAngle * D2G) + (lHeight - sHeight) * tan((90 - steepAngle) * D2G), rimHeight, width / 2);
	glVertex3f(frontRimX, rimHeight, width / 2);
	glVertex3f(frontRimX2, 0, width / 2);
	glEnd();
	glPopMatrix();

	glBegin(GL_POLYGON);
	glColor3f(0.8, 0.8, 0.8);
	glNormal3f(1 / sqrt(2), -1 / sqrt(2), 0);
	glVertex3f(frontRimX + rimLength - rimFullLength, 0, width / 2);
	glVertex3f(frontRimX - edgeCurveRadius * sin(steepAngle * D2G), rimHeight, width / 2);
	glVertex3f(frontRimX - edgeCurveRadius * sin(steepAngle * D2G), rimHeight, -width / 2);
	glVertex3f(frontRimX + rimLength - rimFullLength, 0, -width / 2);
	glEnd();
	
	//bottom
	glBegin(GL_POLYGON);
	glNormal3f(0, -1, 0);
	glVertex3f(frontRimX +rimLength - rimFullLength, 0, width / 2);
	glVertex3f(-length + rimFullLength + edgeCurveRadius * sin(steepAngle * D2G), 0, width / 2);
	glVertex3f(-length + rimFullLength + edgeCurveRadius * sin(steepAngle * D2G), 0, -width / 2);
	glVertex3f(frontRimX + rimLength - rimFullLength, 0, -width / 2);
	glEnd();
	
	//bottom in the back
	glBegin(GL_POLYGON);
	glNormal3f(0, -1, 0);
	glVertex3f(-length + edgeRadius + edgeCurveRadius, rimHeight, width / 2);
	glVertex3f(-length + rimFullLength + edgeCurveRadius * sin(steepAngle * D2G), rimHeight, width / 2);
	glVertex3f(-length + rimFullLength + edgeCurveRadius * sin(steepAngle * D2G), rimHeight, -width / 2);
	glVertex3f(-length + edgeRadius + edgeCurveRadius, rimHeight, -width / 2);
	glEnd();
}

void view() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70, 1, 1, 1000);
	//glOrtho(-50, 50, -50, 50, 1, 100);
	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();
	gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);

}

void initialize() {
	eyeX = xCoord + Radius * cos(D2G * alpha);
	eyeY = Radius * sin(D2G * beta);
	eyeZ = zCoord + Radius * sin(D2G * alpha);
	centerX = xCoord;
	centerY = 0;
	centerZ = zCoord;
	upX = 0;
	upY = 1;
	upZ = 0;

}

void drawJeep() {
	glPushMatrix();
	glTranslatef(-41.5, 22, 0);
	glScalef(wheelScaleFactor, wheelScaleFactor, wheelScaleFactor);
	drawWheel();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(30, -1, 0);
	glRotatef(90, 0, 1, 0);
	drawWheelWithCylinderAxis();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-25, -1, 0);
	glRotatef(90, 0, 1, 0);
	drawWheelWithCylinderAxis();
	glPopMatrix();

	//glEnable(GL_COLOR_MATERIAL);
	drawJeepBody(40, 40, 44, 25, 18, 15, 2, 3, 75);
	glPopMatrix();
}

void drawObstacles() {
	setupMaterial(qaTyre, qaTyre, qaBlack, 60.0);
	glPushMatrix();
	glTranslatef(80, 50, 0);
	pillarObstacle.DrawFaces(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(500, 50, -200);
	pillarObstacle.DrawFaces(1);
	glPopMatrix();
}

void myDisplay()
{
	initialize();
	view();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

	if (secondLightOn) glEnable(GL_LIGHT1);
	else glDisable(GL_LIGHT1);
	drawObstacles();
	glPushMatrix();
	glTranslatef(xCoord, 0, zCoord);
	drawJeep();
	glPopMatrix();

	glFlush();
    glutSwapBuffers();
}


void processTimer(int value) {
	angle += (GLfloat)value;
	if (angle > 360.0f) angle -= 360.0f;
	glutTimerFunc(100, processTimer, value);
	glutPostRedisplay();
}

void myInit()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(
		-4.0,	//left
		4.0,	//right
		-4.0,	//bottom
		4.0,	//top
		10.0,	//near
		100.0	//far
	);
	//Default MatrixMode is MODELVIEW 
	glMatrixMode(GL_MODELVIEW);

	glFrontFace(GL_CCW);
	glClearColor(0.2, 0.2, 0.2, 0.5);
	glShadeModel(GL_SMOOTH);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glEnable(GL_DEPTH_TEST);

	//Set light intensity and color
	float qaAmbientLight[] = { 0.2,0.2,0.2,1.0 };
	float qaDiffuseLight[] = { 0.8,0.8,0.8,1.0 };
	float qaSpecularLight[] = { 1.0,1.0,1.0,1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat light_position1[] = { 30.0f, 10.0f, 30.0f, 0.0f };
	glLightfv(GL_LIGHT1, GL_AMBIENT, qaAmbientLight);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, qaDiffuseLight);
	glLightfv(GL_LIGHT1, GL_SPECULAR, qaSpecularLight);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);

}

void onMouseDown(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		o_x = x;
		o_y = y;
	}
}

void onMotion(int x, int y) {
	alpha += (x - o_x) / 2;
	beta += (y - o_y) / 2;
	o_x = x;
	o_y = y;
	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, (char**)argv); //initialize the tool kit
	glutInitDisplayMode(GLUT_DOUBLE |GLUT_RGB | GLUT_DEPTH);//set the display mode
	glutInitWindowSize(screenWidth, screenHeight); //set window size
	glutInitWindowPosition(100, 100); // set window position on screen
	glutCreateWindow("Lab 2"); // open the screen window
	//create
	int nX = 4;
	TyrePart1.CreateTyrePart1(3, 2, 0.75, 0.8, nX);
	TyrePart2.CreateTyrePart2(0.35, 0.05, 0.15);
	TyrePart3.CreateTyrePart3(0.38, 0.05, 0.15);
	RimPart1.CreateRimPart1(2, 1.8, 0.75, nX);
	RimPart2.CreateRimPart2(1.8, 0.5, 0.3, nX);
	RimPart3.CreateRimPart2(1.8, 0.5, 0.0, nX);
	Cl.CreateCylinder2(32 * nX, wheelAxisLength, 0.4);
	//cal normvector
	TyrePart1.CalculateFacesNorm();
	TyrePart2.CalculateFacesNorm();
	TyrePart3.CalculateFacesNorm();
	RimPart1.CalculateFacesNorm();
	RimPart2.CalculateFacesNorm();
	RimPart3.CalculateFacesNorm();
	Cl.CalculateFacesNorm();

	//set up jeep bar
	setUpJeepBar(40, 10, 2);
	setUpJeepLight((2 * 40.0) / 28);
	setUpFrontPanelCorner(10, 40.0 / 28, 40.0 / 28);
	setUpFrontPanel(10, 40.0 / 28,  40.0 / 28);
	setUpJeepFront(32,40,2,25,10,2);
	setUpRIM(18, 10, 15, 0, 2, 3, 75);
	setUpJeepBody(40, 40, 44, 25, 18, 15, 2, 3, 75);

	//set up obstacles
	pillarObstacle.CreateCuboid(40, 80, 40);
	//set up coordinates for jeep 
	xCoord = yCoord = zCoord = 0;

	myInit();

	glutMotionFunc(onMotion);
	glutMouseFunc(onMouseDown);
	glutKeyboardFunc(myKeyboard);
    glutDisplayFunc(myDisplay);
	glutTimerFunc(100, processTimer, 10);


	glutMainLoop();
	return 0;
}

