
#include "ofApp.h"

void ofApp::setup() {
	ofBackground(ofColor::black);

	primitive = ofIcoSpherePrimitive(sphereRadius, 1);
	primitive2.set(100);
}

void ofApp::update() {


	vector<ofMeshFace> triangles = primitive.getMesh().getUniqueFaces();

	float displacement = sin(ofGetElapsedTimef() * 2) * 3;

	for (size_t i = 0; i < triangles.size(); i += 1) {
		ofVec3f faceNormal = triangles[i].getFaceNormal();
		
		for (int j = 0; j < 10; j++) {
			triangles[i].setVertex(j, triangles[i].getVertex(j) + faceNormal * displacement);
		}
		
	}

	primitive.getMesh().setFromTriangles(triangles);
}

void ofApp::draw() {

	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);

	primitive.rotateDeg(spinX, 1.0, 0.0, 0.0);   
	primitive.rotateDeg(spinY, 0, 1.0, 0.0);

	primitive2.rotateDeg(spinX, 0, 0.0, 1.0);
	primitive2.rotateDeg(spinY, 0, 1.0, 0.0);

	if (drawWireframe) 
	{
		ofTranslate(-200, 0);
		//primitive.setRadius(170);
		primitive.drawWireframe();

		ofTranslate(400, 0);
		primitive2.set(170, 200, 50); 
		primitive2.drawWireframe();
	}
	else 
	{

		ofTranslate(-200, 0);
		primitive = ofIcoSpherePrimitive(sphereRadius, 2);
		primitive.setRadius(50);
		primitive.drawWireframe();

		ofTranslate(400, 0);
		primitive2.set(200, 200, 200);
		primitive2.drawWireframe();
	}
}


void ofApp::keyPressed(int key) {
	if (key == ' ') {
		drawWireframe = !drawWireframe;
	}
}