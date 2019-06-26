#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {

public:
	void setup();

	void update();

	void draw();

	void keyPressed(int key);

	ofIcoSpherePrimitive primitive;
	ofBoxPrimitive primitive2;

	float spinX = 2;
	float spinY = 0.5;
	float sphereRadius = 100;

	int size = 1;

	bool drawWireframe = true;
};