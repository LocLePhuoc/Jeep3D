// Bai3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <math.h>
#include <iostream>
#include "supportClass.h"
#include "Mesh.h"
#include "Wheel.h"
#include "Keyboard.h"
#include "Movement.h"
#include "Tga.h"
#define D2G 3.14159/180

#define PI			3.1415926
using namespace std;

//keyboard 
Keyboard keyboard;

//monitor the movement
Movement movement;
float jeepSteerAngle = 0;


//camera variables
int o_x, o_y;
float eyeX, eyeY, eyeZ;
float centerX, centerY, centerZ;
float upX, upY, upZ;
float alpha = 180;
float beta = 45;
float deltaAngle = 5;
float dR = 0.2;
float Radius = 150;
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

//spin angle of the wheels
float wheelSpinAngle = 0;
float wheelRadius = wheelScaleFactor * 3;

//steering angle for front wheels
float leftFrontWheelSteerAngle = 0;
float rightFrontWheelSteerAngle = 0;

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
float static xCoord;
float yCoord;
float static zCoord;

//obstacles
Mesh pillarObstacle;

//texture
Texture   floorTex;

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

//	Load Texture
void loadTextures(void) {
	char s[] = "pattern2.tga";
	bool status = LoadTGA(&floorTex, s);
	if (status) {
		glGenTextures(1, &floorTex.texID);
		glBindTexture(GL_TEXTURE_2D, floorTex.texID);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, floorTex.width,
			floorTex.height, 0,
			GL_RGB, GL_UNSIGNED_BYTE, floorTex.imageData);

		if (floorTex.imageData)
			free(floorTex.imageData);
	}
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

void myKeyboardDown(unsigned char key, int x, int y)
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
	case 'k' | 'K':
		Radius += 2;
		break;
	case 'i' | 'I':
		Radius -= 2;
		break;
	case 'w' | 'W' :
		keyboard.onKeyEventDown(KEY_FORWARD);
		break;
	case 's' | 'S':
		keyboard.onKeyEventDown(KEY_BACKWARD);
		break;
	case 'a' | 'A':
		keyboard.onKeyEventDown(KEY_LEFT);
		break;
	case 'd' | 'D':
		keyboard.onKeyEventDown(KEY_RIGHT);
		break;
	default:
		break;
	}
}

void myKeyboardUp(unsigned char key, int x, int y) {
	switch (key) {
	case 'w' | 'W':
		keyboard.onKeyEventUp(KEY_FORWARD);
		break;
	case 's' | 'S':
		keyboard.onKeyEventUp(KEY_BACKWARD);
		break;
	case 'a' | 'A':
		keyboard.onKeyEventUp(KEY_LEFT);
		break;
	case 'd' | 'D':
		keyboard.onKeyEventUp(KEY_RIGHT);
		break;
	default:
		break;
	}
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
	setupMaterial(qaTyre, qaTyre, qaBlack, 60.0);
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
	glDisable(GL_TEXTURE_2D);
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

	//glDisable(GL_LIGHTING);
	setupMaterial(qaGray2, qaGray2, qaWhite, 60.0);
	glEnable(GL_TEXTURE_2D);

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

	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
}

void drawFloor() {
	//glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	glColor4f(1, 1, 1, 1.0);

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(10, 0, 10);
	glTexCoord2f(0, 1);
	glVertex3f(10, 0, -10);
	glTexCoord2f(1, 1);
	glVertex3f(-10, 0, -10);
	glTexCoord2f(1, 0);
	glVertex3f(-10, 0, 10);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);

}

void drawJeepFront(float length, float width, float EdgeRadius,float sHeight, float height, float deltaHeight) {
	setupMaterial(qaGray2, qaGray2, qaWhite, 60.0);
	glEnable(GL_TEXTURE_2D);
	loadTextures();

	glBindTexture(GL_TEXTURE_2D, floorTex.texID);
	glColor4f(1, 1, 1, 1.0);
	
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
	glTexCoord2f(0, 0);
	glVertex3f(length, EdgeRadius - deltaHeight, width / 2 - EdgeRadius);
	glTexCoord2f(0, 1);
	glVertex3f(length, EdgeRadius - deltaHeight, -width / 2 + EdgeRadius);
	glTexCoord2f(1, 1);
	glVertex3f(length, - deltaHeight, -width / 2 + EdgeRadius);
	glTexCoord2f(1, 0);
	glVertex3f(length, - deltaHeight, width / 2 - EdgeRadius);

	//top face
	glNormal3f(0, 1, 0);
	glTexCoord2f(0, 0);
	glVertex3f(0, EdgeRadius, width / 2 - EdgeRadius);
	glTexCoord2f(0, 1);
	glVertex3f(0, EdgeRadius, -width / 2 + EdgeRadius);
	glTexCoord2f(1, 1);
	glVertex3f(length, EdgeRadius - deltaHeight, -width / 2 + EdgeRadius);
	glTexCoord2f(1, 0);
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
	glTexCoord2f(0, 0);
	glVertex3f(0, 0, width / 2);
	glTexCoord2f(0, 1);
	glVertex3f(0, -height + EdgeRadius, width / 2);
	glTexCoord2f(1, 1);
	glVertex3f(length, -height + EdgeRadius, width / 2);
	glTexCoord2f(1, 0);
	glVertex3f(length, -deltaHeight, width / 2);

	//side face 1
	glNormal3f(0, 0, -1);
	glTexCoord2f(0, 0);
	glVertex3f(0, 0, -width / 2);
	glTexCoord2f(0, 1);
	glVertex3f(0, -height + EdgeRadius, -width / 2);
	glTexCoord2f(1, 1);
	glVertex3f(length, -height + EdgeRadius, -width / 2);
	glTexCoord2f(1, 0);
	glVertex3f(length, -deltaHeight, -width / 2);
	
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);

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
	setupMaterial(qaGray2, qaGray2, qaWhite, 60.0);

	//glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

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

	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_TEXTURE_2D);

	//glColor3f(0.8, 0.8, 0.8);
	glBegin(GL_QUADS);

	//back
	glNormal3f(-1, 0, 0);
	glTexCoord2f(0, 0);
	glVertex3f(-length + edgeCurveRadius, lHeight, width / 2 - edgeRadius);
	glTexCoord2f(0, 1);
	glVertex3f(-length + edgeCurveRadius, lHeight, -width / 2 + edgeRadius);
	glTexCoord2f(1, 1);
	glVertex3f(-length + edgeCurveRadius, rimHeight * 0.5, -width / 2 + edgeRadius);
	glTexCoord2f(1, 0);
	glVertex3f(-length + edgeCurveRadius, rimHeight * 0.5, width / 2 - edgeRadius);

	//roof
	glNormal3f(0, 1, 0);
	glTexCoord2f(0, 0);
	glVertex3f(0, lHeight + edgeRadius, width / 2 - edgeRadius);
	glTexCoord2f(0, 1);
	glVertex3f(0, lHeight + edgeRadius, -width / 2 + edgeRadius);
	glTexCoord2f(1, 1);
	glVertex3f(-length + edgeRadius + edgeCurveRadius, lHeight + edgeRadius, -width / 2 + edgeRadius);
	glTexCoord2f(1, 0);
	glVertex3f(-length + edgeRadius + edgeCurveRadius, lHeight + edgeRadius, width / 2 - edgeRadius);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	//wind shield
	glBegin(GL_QUADS);
	setupMaterial(glass_ambient, glass_diffuse, qaBlack, glass_shine);

	float frontPanelHeight = lHeight - edgeCurveRadius * (1 - cos(steepAngle * D2G)) - sHeight;
	float frontPanelLength = (lHeight - sHeight) * tan((90 - steepAngle) * D2G);

	glNormal3f(1 / sqrt(2), 1 / sqrt(2), 0);
	glVertex3f(edgeCurveRadius * sin(steepAngle * D2G) + frontPanelLength * 0.1  + edgeRadius, 
		frontPanelHeight * 0.9 + sHeight, (width / 2 - edgeRadius));
	glVertex3f(edgeCurveRadius * sin(steepAngle * D2G) + frontPanelLength * 0.1 + edgeRadius,
		frontPanelHeight * 0.9 + sHeight, (-width / 2 + edgeRadius));
	glVertex3f(edgeCurveRadius * sin(steepAngle * D2G) + frontPanelLength * 0.9 + edgeRadius,
		frontPanelHeight * 0.1 + sHeight, (-width / 2 + edgeRadius));
	glVertex3f(edgeCurveRadius * sin(steepAngle * D2G) + frontPanelLength * 0.9 + edgeRadius,
		frontPanelHeight * 0.1 + sHeight, (width / 2 - edgeRadius));
	glEnd();

	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	setupMaterial(qaGray2, qaGray2, qaWhite, 60.0);
	glColor3f(0.8, 0.8, 0.8);
	glTexCoord2f(0, 0);
	glVertex3f(edgeCurveRadius * sin(steepAngle * D2G) + edgeRadius,
		frontPanelHeight + sHeight, (width / 2 - edgeRadius));
	glTexCoord2f(0, 1);
	glVertex3f(edgeCurveRadius * sin(steepAngle * D2G) + edgeRadius,
		frontPanelHeight + sHeight, (-width / 2 + edgeRadius));
	glTexCoord2f(1, 1);
	glVertex3f(edgeCurveRadius * sin(steepAngle * D2G) + frontPanelLength * 0.1 + edgeRadius,
		frontPanelHeight * 0.9 + sHeight, (-width / 2 + edgeRadius));
	glTexCoord2f(1, 0);
	glVertex3f(edgeCurveRadius * sin(steepAngle * D2G) + frontPanelLength * 0.1 + edgeRadius,
		frontPanelHeight * 0.9 + sHeight, (width / 2 - edgeRadius));

	glTexCoord2f(0, 0);
	glVertex3f(edgeCurveRadius * sin(steepAngle * D2G) + frontPanelLength * 0.9 + edgeRadius,
		frontPanelHeight * 0.1 + sHeight, (width / 2 - edgeRadius));
	glTexCoord2f(0, 1);
	glVertex3f(edgeCurveRadius * sin(steepAngle * D2G) + frontPanelLength * 0.9 + edgeRadius,
		frontPanelHeight * 0.1 + sHeight, (-width / 2 + edgeRadius));
	glTexCoord2f(1, 1);
	glVertex3f(edgeCurveRadius * sin(steepAngle * D2G) + frontPanelLength + edgeRadius,
		sHeight, (-width / 2 + edgeRadius));
	glTexCoord2f(1, 0);
	glVertex3f(edgeCurveRadius * sin(steepAngle * D2G) + frontPanelLength + edgeRadius,
		sHeight, (width / 2 - edgeRadius));
	glEnd();
	glDisable(GL_TEXTURE_2D);

	float windowLength = length / 5;

	//sides

	float sideLength = length - windowLength - edgeRadius - edgeCurveRadius;
	//right side
	setupMaterial(glass_ambient, glass_diffuse, qaBlack, glass_shine);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, -1);
	glColor3f(0.2, 0.2, 0.2);
	glVertex3f(-length + edgeRadius + edgeCurveRadius + sideLength * 1 / 8, lHeight - edgeCurveRadius, -width / 2);
	glVertex3f(-length + edgeRadius + edgeCurveRadius + sideLength * 6 / 8, lHeight - edgeCurveRadius, -width / 2);
	glVertex3f(-length + edgeRadius + edgeCurveRadius + sideLength * 6 / 8, frontPanelHeight * 0.1 + sHeight, -width / 2);
	glVertex3f(-length + edgeRadius + edgeCurveRadius + sideLength * 1 / 8, frontPanelHeight * 0.1 + sHeight, -width / 2);
	glEnd();

	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	setupMaterial(qaGray2, qaGray2, qaWhite, 60.0);
	glNormal3f(0, 0, -1);
	glColor3f(0.8, 0.8, 0.8);
	glTexCoord2f(0, 0);
	glVertex3f(-length + edgeRadius + edgeCurveRadius, lHeight, -width / 2);
	glTexCoord2f(0, 1);
	glVertex3f(-windowLength - edgeRadius, lHeight, -width / 2);
	glTexCoord2f(1, 1);
	glVertex3f(-windowLength - edgeRadius, lHeight - edgeCurveRadius,- width / 2);
	glTexCoord2f(1, 0);
	glVertex3f(-length + edgeRadius + edgeCurveRadius, lHeight - edgeCurveRadius, -width / 2);

	glNormal3f(0, 0, -1);
	glColor3f(0.8, 0.8, 0.8);
	glTexCoord2f(0, 0);
	glVertex3f(-length + edgeRadius + edgeCurveRadius, lHeight - edgeCurveRadius, -width / 2);
	glTexCoord2f(0, 1);
	glVertex3f(-length + edgeRadius + edgeCurveRadius + sideLength * 1 / 8, lHeight - edgeCurveRadius, -width / 2);
	glTexCoord2f(1, 1);
	glVertex3f(-length + edgeRadius + edgeCurveRadius + sideLength * 1 / 8, frontPanelHeight * 0.1 + sHeight, -width / 2);
	glTexCoord2f(1, 0);
	glVertex3f(-length + edgeRadius + edgeCurveRadius, frontPanelHeight * 0.1 + sHeight, -width / 2);

	glNormal3f(0, 0, -1);
	glColor3f(0.8, 0.8, 0.8);
	glTexCoord2f(0, 0);
	glVertex3f(-windowLength - edgeRadius, lHeight - edgeCurveRadius, -width / 2);
	glTexCoord2f(0, 1);
	glVertex3f(-length + edgeRadius + edgeCurveRadius + sideLength * 6 / 8, lHeight - edgeCurveRadius, -width / 2);
	glTexCoord2f(1, 1);
	glVertex3f(-length + edgeRadius + edgeCurveRadius + sideLength * 6 / 8, frontPanelHeight * 0.1 + sHeight, -width / 2);
	glTexCoord2f(1, 0);
	glVertex3f(-windowLength - edgeRadius, frontPanelHeight * 0.1 + sHeight, -width / 2);


	glNormal3f(0, 0, -1);
	glColor3f(0.8, 0.8, 0.8);
	glTexCoord2f(0, 0);
	glVertex3f(-windowLength - edgeRadius, rimHeight, -width / 2);
	glTexCoord2f(0, 1);
	glVertex3f(-length + edgeRadius + edgeCurveRadius, rimHeight, -width / 2);
	glTexCoord2f(1, 1);
	glVertex3f(-length + edgeRadius + edgeCurveRadius, frontPanelHeight * 0.1 + sHeight, -width / 2);
	glTexCoord2f(1, 0);
	glVertex3f(-windowLength - edgeRadius, frontPanelHeight * 0.1 + sHeight, -width / 2);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	//left side
	glBegin(GL_QUADS);
	setupMaterial(glass_ambient, glass_diffuse, qaBlack, glass_shine);
	glNormal3f(0, 0, 1);
	glColor3f(0.2, 0.2, 0.2);
	glVertex3f(-length + edgeRadius + edgeCurveRadius + sideLength * 1 / 8, lHeight - edgeCurveRadius, width / 2);
	glVertex3f(-length + edgeRadius + edgeCurveRadius + sideLength * 6 / 8, lHeight - edgeCurveRadius, width / 2);
	glVertex3f(-length + edgeRadius + edgeCurveRadius + sideLength * 6 / 8, frontPanelHeight * 0.1 + sHeight, width / 2);
	glVertex3f(-length + edgeRadius + edgeCurveRadius + sideLength * 1 / 8, frontPanelHeight * 0.1 + sHeight, width / 2);
	glEnd();

	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	setupMaterial(qaGray2, qaGray2, qaWhite, 60.0);
	glNormal3f(0, 0, 1);
	glColor3f(0.8, 0.8, 0.8);
	glTexCoord2f(0, 0);
	glVertex3f(-length + edgeRadius + edgeCurveRadius, lHeight, width / 2);
	glTexCoord2f(0, 1);
	glVertex3f(-windowLength - edgeRadius, lHeight, width / 2);
	glTexCoord2f(1, 1);
	glVertex3f(-windowLength - edgeRadius, lHeight - edgeCurveRadius, width / 2);
	glTexCoord2f(1, 0);
	glVertex3f(-length + edgeRadius + edgeCurveRadius, lHeight - edgeCurveRadius, width / 2);

	glNormal3f(0, 0, 1);
	glColor3f(0.8, 0.8, 0.8);
	glTexCoord2f(0, 0);
	glVertex3f(-length + edgeRadius + edgeCurveRadius, lHeight - edgeCurveRadius, width / 2);
	glTexCoord2f(0, 1);
	glVertex3f(-length + edgeRadius + edgeCurveRadius + sideLength * 1 / 8, lHeight - edgeCurveRadius, width / 2);
	glTexCoord2f(1, 1);
	glVertex3f(-length + edgeRadius + edgeCurveRadius + sideLength * 1 / 8, frontPanelHeight * 0.1 + sHeight, width / 2);
	glTexCoord2f(1, 0);
	glVertex3f(-length + edgeRadius + edgeCurveRadius, frontPanelHeight * 0.1 + sHeight, width / 2);

	glNormal3f(0, 0, 1);
	glColor3f(0.8, 0.8, 0.8);
	glTexCoord2f(0, 0);
	glVertex3f(-windowLength - edgeRadius, lHeight - edgeCurveRadius, width / 2);
	glTexCoord2f(0, 1);
	glVertex3f(-length + edgeRadius + edgeCurveRadius + sideLength * 6 / 8, lHeight - edgeCurveRadius, width / 2);
	glTexCoord2f(1, 1);
	glVertex3f(-length + edgeRadius + edgeCurveRadius + sideLength * 6 / 8, frontPanelHeight * 0.1 + sHeight, width / 2);
	glTexCoord2f(1, 0);
	glVertex3f(-windowLength - edgeRadius, frontPanelHeight * 0.1 + sHeight, width / 2);


	glNormal3f(0, 0, 1);
	glColor3f(0.8, 0.8, 0.8);
	glTexCoord2f(0, 0);
	glVertex3f(-windowLength - edgeRadius, rimHeight, width / 2);
	glTexCoord2f(0, 1);
	glVertex3f(-length + edgeRadius + edgeCurveRadius , rimHeight, width / 2);
	glTexCoord2f(1, 1);
	glVertex3f(-length + edgeRadius + edgeCurveRadius , frontPanelHeight * 0.1 + sHeight, width / 2);
	glTexCoord2f(1, 0);
	glVertex3f(-windowLength - edgeRadius, frontPanelHeight * 0.1 + sHeight, width / 2);

	glEnd();
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);

	//right door
	glPushMatrix();
		glTranslatef(edgeCurveRadius* sin(steepAngle * D2G) + (lHeight - sHeight) * tan((90 - steepAngle) * D2G), 0, -width / 2);
		glRotatef(-rightDoorAngle, 0, 1, 0);
		glTranslatef(-edgeCurveRadius * sin(steepAngle * D2G) - (lHeight - sHeight) * tan((90 - steepAngle) * D2G), 0, width / 2);

		setupMaterial(glass_ambient, glass_diffuse, qaBlack, glass_shine);
		glDisable(GL_TEXTURE_2D);
		glBegin(GL_POLYGON);
		glColor3f(0.2, 0.2, 0.2);
		glNormal3f(0, 0, -1);
		glVertex3f(0, lHeight - edgeCurveRadius, -width / 2);
		glVertex3f(-windowLength, lHeight - edgeCurveRadius, -width / 2);
		glVertex3f(-windowLength, frontPanelHeight * 0.1 + sHeight, -width / 2);
		glVertex3f((lHeight - edgeCurveRadius - frontPanelHeight * 0.1 - sHeight) / tan(steepAngle * D2G)
			, frontPanelHeight * 0.1 + sHeight, -width / 2);
		glEnd();		

		glEnable(GL_TEXTURE_2D);
		setupMaterial(qaGray2, qaGray2, qaWhite, 60.0);

			glBegin(GL_POLYGON);
			glColor3f(0.8, 0.8, 0.8);
			glNormal3f(0, 0, -1);
			glTexCoord2f(0, 0);
			glVertex3f(-windowLength - edgeRadius, lHeight - edgeCurveRadius, -width/2);
			glTexCoord2f(0, 1);
			glVertex3f(-windowLength - edgeRadius, frontPanelHeight * 0.1 + sHeight, -width/2);
			glTexCoord2f(1, 1);
			glVertex3f(-windowLength, frontPanelHeight * 0.1 + sHeight, -width/2);
			glTexCoord2f(1, 0);
			glVertex3f(-windowLength, lHeight - edgeCurveRadius, -width/2);
			glEnd();

			glBegin(GL_POLYGON);
			glNormal3f(0, 0, -1);
			glTexCoord2f(0, 0);
			glVertex3f(0, lHeight - edgeCurveRadius, -width/2);
			glTexCoord2f(0, 1);
			glVertex3f(-windowLength - edgeRadius, lHeight - edgeCurveRadius, -width/2);
			glTexCoord2f(1, 1);
			glVertex3f(-windowLength - edgeRadius, lHeight, -width/2);
			glTexCoord2f(1, 0);
			glVertex3f(0, lHeight, -width/2);
			glEnd();

			glBegin(GL_POLYGON);
			glNormal3f(0, 0, -1);
			glTexCoord2f(0, 0);
			glVertex3f(-windowLength - edgeRadius, frontPanelHeight * 0.1 + sHeight, -width/2);
			glTexCoord2f(0, 1);
			glVertex3f(-windowLength - edgeRadius, 0, -width/2);
			glTexCoord2f(1, 1);
			glVertex3f(edgeCurveRadius * sin(steepAngle * D2G) + (lHeight - sHeight) * tan((90 - steepAngle) * D2G), 0, -width/2);
			glTexCoord2f(1, 0);
			glVertex3f(edgeCurveRadius * sin(steepAngle * D2G) + (lHeight - sHeight) * tan((90 - steepAngle) * D2G), sHeight, -width/2);
			glVertex3f(edgeCurveRadius * sin(steepAngle * D2G) + (lHeight - sHeight) * tan((90 - steepAngle) * D2G) - frontPanelHeight * 0.1 / tan(steepAngle * D2G)
				, frontPanelHeight * 0.1 + sHeight, -width/2);
			glEnd();

			glBegin(GL_POLYGON);
			glNormal3f(0, 0, -1);
			glTexCoord2f(0, 0);
			glVertex3f(0, lHeight - edgeCurveRadius, -width/2);
			glTexCoord2f(0, 1);
			glVertex3f(edgeCurveRadius * sin(steepAngle * D2G), lHeight - edgeCurveRadius * (1 - cos(steepAngle * D2G)), -width/2);
			glTexCoord2f(1, 1);
			glVertex3f(edgeCurveRadius * sin(steepAngle * D2G) + (lHeight - sHeight) * tan((90 - steepAngle) * D2G) - frontPanelHeight * 0.1 / tan(steepAngle * D2G)
				, frontPanelHeight * 0.1 + sHeight, -width/2);
			glTexCoord2f(1, 0);
			glVertex3f((lHeight - edgeCurveRadius - frontPanelHeight * 0.1 - sHeight) / tan(steepAngle * D2G)
				, frontPanelHeight * 0.1 + sHeight, -width/2);
			glEnd();
			
	drawFan(0, lHeight - edgeCurveRadius, -width / 2, edgeCurveRadius, steepAngle, 20, -1);
	glPopMatrix();

	glEnable(GL_TEXTURE_2D);
	//left door
	glPushMatrix();
		glTranslatef(edgeCurveRadius * sin(steepAngle * D2G) + (lHeight - sHeight) * tan((90 - steepAngle) * D2G), 0, width / 2);
		glRotatef(leftDoorAngle, 0, 1, 0);
		glTranslatef(-edgeCurveRadius * sin(steepAngle * D2G) - (lHeight - sHeight) * tan((90 - steepAngle) * D2G), 0, -width / 2);


	setupMaterial(glass_ambient, glass_diffuse, qaBlack, glass_shine);
	glDisable(GL_TEXTURE_2D);
	glBegin(GL_POLYGON);
	glColor3f(0.2, 0.2, 0.2);
	glNormal3f(0, 0, 1);
	glVertex3f(0, lHeight - edgeCurveRadius, width / 2);
	glVertex3f(-windowLength, lHeight - edgeCurveRadius, width / 2);
	glVertex3f(-windowLength, frontPanelHeight * 0.1 + sHeight, width / 2);
	glVertex3f((lHeight - edgeCurveRadius - frontPanelHeight * 0.1 - sHeight) / tan (steepAngle * D2G)
		, frontPanelHeight * 0.1 + sHeight, width / 2);
	glEnd();

	glEnable(GL_TEXTURE_2D);
	setupMaterial(qaGray2, qaGray2, qaWhite, 60.0);
	glBegin(GL_POLYGON);
	glColor3f(0.8, 0.8, 0.8);
	glNormal3f(0, 0, 1);
	glTexCoord2f(0, 0);
	glVertex3f(-windowLength - edgeRadius, lHeight - edgeCurveRadius, width / 2);
	glTexCoord2f(0, 1);
	glVertex3f(-windowLength - edgeRadius, frontPanelHeight * 0.1 + sHeight, width / 2);
	glTexCoord2f(1, 1);
	glVertex3f(-windowLength, frontPanelHeight * 0.1 + sHeight, width / 2);
	glTexCoord2f(1, 0);
	glVertex3f(-windowLength, lHeight - edgeCurveRadius, width / 2);
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0, 0, 1);
	glTexCoord2f(0, 0);
	glVertex3f(0, lHeight - edgeCurveRadius, width / 2);
	glTexCoord2f(0, 1);
	glVertex3f(-windowLength - edgeRadius, lHeight - edgeCurveRadius, width / 2);
	glTexCoord2f(1, 1);
	glVertex3f(-windowLength - edgeRadius, lHeight, width / 2);
	glTexCoord2f(1, 0);
	glVertex3f(0, lHeight, width / 2);
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0, 0, 1);
	glTexCoord2f(0, 0);
	glVertex3f(-windowLength - edgeRadius, frontPanelHeight * 0.1 + sHeight, width / 2);
	glTexCoord2f(0, 1);
	glVertex3f(-windowLength - edgeRadius, 0, width / 2);
	glTexCoord2f(1, 1);
	glVertex3f(edgeCurveRadius * sin(steepAngle * D2G) + (lHeight - sHeight) * tan((90 - steepAngle) * D2G), 0, width / 2);
	glTexCoord2f(1, 0);
	glVertex3f(edgeCurveRadius * sin(steepAngle * D2G) + (lHeight - sHeight) * tan((90 - steepAngle) * D2G), sHeight, width / 2);
	glVertex3f(edgeCurveRadius * sin(steepAngle * D2G) + (lHeight - sHeight) * tan((90 - steepAngle) * D2G) - frontPanelHeight * 0.1 / tan(steepAngle * D2G)
		, frontPanelHeight * 0.1 + sHeight, width / 2);
	glEnd();
	
	glBegin(GL_POLYGON);
	glNormal3f(0, 0, 1);
	glTexCoord2f(0, 0);
	glVertex3f(0, lHeight - edgeCurveRadius, width / 2);
	glTexCoord2f(0, 1);
	glVertex3f(edgeCurveRadius * sin(steepAngle * D2G), lHeight - edgeCurveRadius * (1 - cos(steepAngle * D2G)), width / 2);
	glTexCoord2f(1, 1);
	glVertex3f(edgeCurveRadius * sin(steepAngle * D2G) + (lHeight - sHeight) * tan((90 - steepAngle) * D2G) - frontPanelHeight * 0.1 / tan(steepAngle * D2G)
		, frontPanelHeight * 0.1 + sHeight, width / 2);
	glTexCoord2f(1, 0);
	glVertex3f((lHeight - edgeCurveRadius - frontPanelHeight * 0.1 - sHeight) / tan(steepAngle * D2G)
		, frontPanelHeight * 0.1 + sHeight, width / 2);
	glEnd();
	
	drawFan(0, lHeight - edgeCurveRadius, width / 2, edgeCurveRadius, steepAngle, 20, 1);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);

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
	//setupMaterial(qaTyre, qaTyre, qaBlack, 60.0);
	setupMaterial(qaGray2, qaGray2, qaWhite, 60.0);
	float rimFullLength = rimLength + edgeCurveRadius * sin(steepAngle * D2G) + rimHeight * tan((90 - steepAngle) * D2G);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_POLYGON);
	glColor3f(0.8, 0.8, 0.8);
	glNormal3f(0, 0, 1);
	glTexCoord2f(0, 0);
	glVertex3f(-windowLength - edgeRadius, 0, width / 2);
	glTexCoord2f(0, 1);
	glVertex3f(-windowLength - edgeRadius, rimHeight, width / 2);
	glTexCoord2f(1, 1);
	glVertex3f(-length + edgeCurveRadius + rimLength + edgeCurveRadius * sin(steepAngle * D2G), rimHeight, width / 2);
	glTexCoord2f(1, 0);
	glVertex3f(-length + rimFullLength + edgeCurveRadius * sin(steepAngle * D2G), 0, width / 2);
	glEnd();

	glPushMatrix();
	glScalef(1, 1, -1);
	glBegin(GL_POLYGON);
	glColor3f(0.8, 0.8, 0.8);
	glNormal3f(0, 0, 1);
	glTexCoord2f(0, 0);
	glVertex3f(-windowLength - edgeRadius, 0, width / 2);
	glTexCoord2f(0, 1);
	glVertex3f(-windowLength - edgeRadius, rimHeight, width / 2);
	glTexCoord2f(1, 1);
	glVertex3f(-length + edgeCurveRadius + rimLength + edgeCurveRadius * sin(steepAngle * D2G), rimHeight, width / 2);
	glTexCoord2f(1, 0);
	glVertex3f(-length + rimFullLength + edgeCurveRadius * sin(steepAngle * D2G), 0, width / 2);
	glEnd();
	glPopMatrix();


	glBegin(GL_POLYGON);
	glNormal3f(-1/ sqrt(2), -1 / sqrt(2),0);
	glTexCoord2f(0, 0);
	glVertex3f(-length + rimFullLength + edgeCurveRadius * sin(steepAngle * D2G), 0, width / 2);
	glTexCoord2f(0, 1);
	glVertex3f(-length + edgeCurveRadius + rimLength + edgeCurveRadius * sin(steepAngle * D2G), rimHeight, width / 2);
	glTexCoord2f(1, 1);
	glVertex3f(-length + edgeCurveRadius + rimLength + edgeCurveRadius * sin(steepAngle * D2G), rimHeight, -width / 2);
	glTexCoord2f(1, 0);
	glVertex3f(-length + rimFullLength + edgeCurveRadius * sin(steepAngle * D2G), 0, -width / 2);
	glEnd();


	//X position of front rim
	float frontRimX = length * 0.8 - rimLength + frontPanelLength;
	float frontRimX2 = frontRimX - rimFullLength + rimLength + edgeCurveRadius * sin(steepAngle * D2G);
	setupMaterial(qaGray2, qaGray2, qaWhite, 60.0);
	glBegin(GL_POLYGON);
	glColor3f(0.8, 0.8, 0.8);
	glNormal3f(0, 0, 1);
	glTexCoord2f(0, 0);
	glVertex3f(edgeCurveRadius * sin(steepAngle * D2G) + (lHeight - sHeight) * tan((90 - steepAngle) * D2G), 0, width / 2);
	glTexCoord2f(0, 1);
	glVertex3f(edgeCurveRadius * sin(steepAngle * D2G) + (lHeight - sHeight) * tan((90 - steepAngle) * D2G), rimHeight, width / 2);
	glTexCoord2f(1, 1);
	glVertex3f(frontRimX, rimHeight, width / 2);
	glTexCoord2f(1, 0);
	glVertex3f(frontRimX2, 0, width / 2);
	glEnd();

	
	glPushMatrix();
	glScalef(1, 1, -1);
	glBegin(GL_POLYGON);
	glColor3f(0.8, 0.8, 0.8);
	glNormal3f(0, 0, 1);
	glTexCoord2f(0, 0);
	glVertex3f(edgeCurveRadius * sin(steepAngle * D2G) + (lHeight - sHeight) * tan((90 - steepAngle) * D2G), 0, width / 2);
	glTexCoord2f(0, 1);
	glVertex3f(edgeCurveRadius * sin(steepAngle * D2G) + (lHeight - sHeight) * tan((90 - steepAngle) * D2G), rimHeight, width / 2);
	glTexCoord2f(1, 1);
	glVertex3f(frontRimX, rimHeight, width / 2);
	glTexCoord2f(1, 0);
	glVertex3f(frontRimX2, 0, width / 2);
	glEnd();
	glPopMatrix();

	glBegin(GL_POLYGON);
	glColor3f(0.8, 0.8, 0.8);
	glNormal3f(1 / sqrt(2), -1 / sqrt(2), 0);
	glTexCoord2f(0, 0);
	glVertex3f(frontRimX + rimLength - rimFullLength, 0, width / 2);
	glTexCoord2f(0, 1);
	glVertex3f(frontRimX - edgeCurveRadius * sin(steepAngle * D2G), rimHeight, width / 2);
	glTexCoord2f(1, 1);
	glVertex3f(frontRimX - edgeCurveRadius * sin(steepAngle * D2G), rimHeight, -width / 2);
	glTexCoord2f(1, 0);
	glVertex3f(frontRimX + rimLength - rimFullLength, 0, -width / 2);
	glEnd();

	//bottom
	setupMaterial(qaGray2, qaGray2, qaWhite, 60.0);
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

	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
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
	eyeX = movement.currentX + Radius * cos(D2G * alpha);
	eyeY = Radius * sin(D2G * beta);
	eyeZ = movement.currentZ + Radius * sin(D2G * alpha);
	centerX = movement.currentX;
	centerY = 0;
	centerZ = movement.currentZ;
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

	//  left front wheel
	glPushMatrix();
	glTranslatef(-wheelAxisLength / 2, 0, 0);
	glRotatef(leftFrontWheelSteerAngle, 0, 1, 0);
	glRotatef(-wheelSpinAngle, 1, 0, 0);
	glScalef(wheelScaleFactor, wheelScaleFactor, wheelScaleFactor);
	drawWheel();
	glPopMatrix();

	//  right front wheel
	glPushMatrix();
	glScalef(-1, 1, 1);
	glPushMatrix();
	glTranslatef(-wheelAxisLength / 2, 0, 0);
	glRotatef(-rightFrontWheelSteerAngle, 0, 1, 0);
	glRotatef(-wheelSpinAngle, 1, 0, 0);
	glScalef(wheelScaleFactor, wheelScaleFactor, wheelScaleFactor);
	drawWheel();
	glPopMatrix();
	glPopMatrix();

	//draw front wheel axis
	glPushMatrix();
	glScalef(1, wheelScaleFactor, wheelScaleFactor);
	glRotatef(90, 0, 0, 1);
	Cl.Draw();
	glPopMatrix();

	glPopMatrix();


	glPushMatrix();
	glTranslatef(-25, -1, 0);
	glRotatef(wheelSpinAngle, 0, 0, 1);
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
	glTranslatef(80, 50, 200);
	glScalef(10, 1, 2);
	pillarObstacle.DrawFaces(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(500, 50, -200);
	glScalef(3, 1, 3);
	pillarObstacle.DrawFaces(1);
	glPopMatrix();
}

void jeepMovement() {
	float backwardVelocity = movement.getBackwardVelocity();
	float forwardVelocity = movement.getForwardVelocity();
	
	keyboard.setVelocities(forwardVelocity, backwardVelocity);

	movement.setDirection(keyboard.getDirection());
	float timeElapsed = movement.move();

	if (backwardVelocity > 0) //move backward
	{
		wheelSpinAngle += (backwardVelocity * timeElapsed * 20 / wheelRadius) / D2G;
	}
	else if (forwardVelocity > 0) // move forward
	{
		wheelSpinAngle -= (forwardVelocity * timeElapsed * 20 / wheelRadius) / D2G;
	}

	if (wheelSpinAngle >= 360) wheelSpinAngle -= 360;
	if (wheelSpinAngle <= -360) wheelSpinAngle += 360;

	//calculate the steering angles of the front wheel
	//radius of steering 
	float R = movement.getDistanceTraveled() / (movement.getSteerAngleIncrement() * D2G);
	float lengthBetweenWheelAxes = 55;
	float lengthBetweenWheels = 52;
	rightFrontWheelSteerAngle = abs(atan(lengthBetweenWheelAxes / (R - lengthBetweenWheels / 2)) / D2G) * 12000;
	leftFrontWheelSteerAngle = abs(atan(lengthBetweenWheelAxes / (R + lengthBetweenWheels / 2)) / D2G) * 12000;
	
	float currentAction = movement.getCurrentAction();
	if (currentAction == IDLE || currentAction == FORWARD || currentAction == BACKWARD) {
		rightFrontWheelSteerAngle = 0;
		leftFrontWheelSteerAngle = 0;
	}
	if (currentAction == TURN_RIGHT_BACKWARD || currentAction == TURN_RIGHT_FORWARD) {
		rightFrontWheelSteerAngle = -rightFrontWheelSteerAngle;
		leftFrontWheelSteerAngle = -leftFrontWheelSteerAngle;
	}
}

void idle() {
	glutPostRedisplay();
}

void turnJeep() {
	Direction currentAction = movement.getCurrentAction();
	if (currentAction == TURN_LEFT_FORWARD || currentAction == TURN_RIGHT_BACKWARD) {
		movement.jeepSteerAngle += movement.getSteerAngleIncrement();
		if (movement.jeepSteerAngle >= 360) {
			movement.jeepSteerAngle -= 360;
		}
	}
	else if (currentAction == TURN_RIGHT_FORWARD || currentAction == TURN_LEFT_BACKWARD) {
		movement.jeepSteerAngle -= movement.getSteerAngleIncrement();
		if (movement.jeepSteerAngle <= -360) {
			movement.jeepSteerAngle += 360;
		}
	}
	glRotatef(movement.jeepSteerAngle, 0, 1, 0);
}
void myDisplay()
{
	initialize();
	jeepMovement();
	view();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	drawObstacles();

	glPushMatrix();
	glTranslatef(movement.currentX, 0, movement.currentZ);
	turnJeep();
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
	glClearColor(0.3, 0.3, 0.3, 0.5);
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
	glEnable(GL_LIGHT1);
	GLfloat light_position1[] = { 30.0f, 10.0f, 30.0f, 0.0f };
	glLightfv(GL_LIGHT1, GL_AMBIENT, qaAmbientLight);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, qaDiffuseLight);
	glLightfv(GL_LIGHT1, GL_SPECULAR, qaSpecularLight);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);

	glEnable(GL_TEXTURE_2D);
	loadTextures();
	glBindTexture(GL_TEXTURE_2D, floorTex.texID);
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
	glutKeyboardFunc(myKeyboardDown);
	glutKeyboardUpFunc(myKeyboardUp);
    glutDisplayFunc(myDisplay);
	glutIdleFunc(idle);
	 //glutTimerFunc(100, processTimer, 10);


	glutMainLoop();
	return 0;
}

