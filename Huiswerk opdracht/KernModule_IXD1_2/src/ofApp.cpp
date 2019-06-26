#include "ofApp.h"
#define PIN_LED 13

#define PIN_LDR 0

void ofApp::setup() {

	// set listener - call ofApp::setupArduino when arduino is ready for use
	ofAddListener(arduino.EInitialized, this, &ofApp::setupArduino);

	// connect to the Arduino
	// use the same device name used in the Arduino IDE
	arduino.connect("COM3", 57600);
	arduino.sendFirmwareVersionRequest(); // workaround for ofArduino/firmata bug

	//--------------------------------------

	x = ofRandom(0, ofGetWidth());
	y = ofRandom(0, ofGetHeight());

	speedX = ofRandom(-10, 10);
	speedY = ofRandom(-10, 10);

	radius = 40;
	color = ofColor::red;
}

void ofApp::setupArduino(const int& version) {
	// remove listener because we don't need it anymore
	ofRemoveListener(arduino.EInitialized, this, &ofApp::setupArduino);

	// print firmware name and version to the console
	ofLog() << "Arduino firmware found: " << arduino.getFirmwareName()
		<< " v" << arduino.getMajorFirmwareVersion() << "." << arduino.getMinorFirmwareVersion();

	arduino.sendDigitalPinMode(PIN_LED, ARD_OUTPUT);
	arduino.sendAnalogPinReporting(PIN_LDR, ARD_ANALOG);

	// set listeners for pin events
	ofAddListener(arduino.EDigitalPinChanged, this, &ofApp::digitalPinChanged);
	ofAddListener(arduino.EAnalogPinChanged, this, &ofApp::analogPinChanged);
}

void ofApp::update() {

	arduino.update();
	//ofLog() << "isArduinoReady" << arduino.isArduinoReady() << endl;

	if (x < 0) {
		x = 0;
		speedX = -speedX;

		cout << "bounce" << endl;
		arduino.sendDigitalPinMode(PIN_LED, ARD_HIGH);
	}

	if (x > ofGetWidth()) {
		x = ofGetWidth();
		speedX = -speedX;

		cout << "bounce" << endl;
		arduino.sendDigitalPinMode(PIN_LED, ARD_LOW);
	}
	if (y < 0) {
		y = 0;
		speedY = -speedY;

		cout << "bounce" << endl;
		arduino.sendDigitalPinMode(PIN_LED, ARD_OUTPUT);
	}

	if (y > ofGetHeight()) {
		y = ofGetHeight();
		speedY = -speedY;

		cout << "bounce" << endl;
		arduino.sendDigitalPinMode(PIN_LED, ARD_LOW);
	}

	x += speedX;
	y += speedY;
}

void ofApp::draw() {
	ofSetColor(color);
	ofDrawCircle(x, y, radius);
}

void ofApp::keyPressed(int key) {

}

void ofApp::digitalPinChanged(const int& pinNum)
{
	// get value with arduino.getDigital(pinNum)
	//arduino.getDigital(pinNum);
	ofLogNotice() << "Digital Pin " << pinNum << " value: " << arduino.getDigital(pinNum) << endl;
}

void ofApp::analogPinChanged(const int& pinNum)
{
	// get value with arduino.getAnalog(pinNum));
	//arduino.getAnalog(pinNum);
	ofLogNotice() << "Analog Pin " << pinNum << " value: " << arduino.getAnalog(pinNum) << endl;
}