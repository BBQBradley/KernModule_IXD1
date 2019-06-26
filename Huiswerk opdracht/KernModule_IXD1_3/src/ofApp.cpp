#include "ofApp.h"

#define PIN_LED 13
#define PIN_LED2 12
#define PIN_LED3 8
#define PIN_LED4 10


#define PIN_BUTTON 11
#define PIN_POTMETER 1

#define PIN_LDR 0

void ofApp::setup()
{
	ofSetFrameRate(60);


	gui.setup();
	gui.add(drawGrid.set("Grid", false));
	gui.add(useLight.set("Light", true));
	gui.add(doRotate.set("Rotation", true));

	light.setDirectional();
	light.setDiffuseColor(ofColor::white);
	light.enable();

	ofBackground(ofColor::black);

	// set listener - call ofApp::setupArduino when arduino is ready for use
	ofAddListener(arduino.EInitialized, this, &ofApp::setupArduino);

	// connect to the Arduino
	// use the same device name used in the Arduino IDE
	arduino.connect("COM3", 57600);
	arduino.sendFirmwareVersionRequest(); // workaround for ofArduino/firmata bug

	Width = 200;
	Height = 200;
	Length = 200;

	x = ofRandom(-100, Width);
	y = ofRandom(-100, Height);
	z = ofRandom(0, Length);

	speedX = (2);
	speedY = (2);
	speedZ = (2);


	radius = 20;
	color = ofColor::blueViolet;

}

void ofApp::setupArduino(const int& version) {
	// remove listener because we don't need it anymore
	ofRemoveListener(arduino.EInitialized, this, &ofApp::setupArduino);

	// print firmware name and version to the console
	ofLog() << "Arduino firmware found: " << arduino.getFirmwareName()
		<< " v" << arduino.getMajorFirmwareVersion() << "." << arduino.getMinorFirmwareVersion();

	arduino.sendDigitalPinMode(PIN_LED, ARD_OUTPUT);
	arduino.sendDigitalPinMode(PIN_BUTTON, ARD_INPUT);
	arduino.sendAnalogPinReporting(PIN_LDR, ARD_ANALOG);
	arduino.sendAnalogPinReporting(PIN_POTMETER, ARD_ANALOG);

	// set listeners for pin events
	ofAddListener(arduino.EDigitalPinChanged, this, &ofApp::digitalPinChanged);
	ofAddListener(arduino.EAnalogPinChanged, this, &ofApp::analogPinChanged);
}

void ofApp::update()
{
	if (arduino.getAnalog(1) < 200)
	{
		rotateY += 1; // zelfde, maar korter dan rotateY = rotateY + 2
	}

	if (arduino.getAnalog(1) > 200 && arduino.getAnalog(1) < 500)
	{
		rotateY += 2; // zelfde, maar korter dan rotateY = rotateY + 2
	}

	if (arduino.getAnalog(1) > 500 && arduino.getAnalog(1) < 800)
	{
		rotateY += 4; // zelfde, maar korter dan rotateY = rotateY + 2
	}

	if (arduino.getAnalog(1) > 800)
	{
		rotateY += 10; // zelfde, maar korter dan rotateY = rotateY + 2
	}

	//cout << AnalogValue << endl;



	if (rotateY > 90 && rotateY < 180)
	{
		arduino.sendDigital(PIN_LED, ARD_LOW);
		arduino.sendDigital(PIN_LED2, ARD_HIGH);
		arduino.sendDigital(PIN_LED3, ARD_LOW);
		arduino.sendDigital(PIN_LED4, ARD_LOW);
	}
	else if (rotateY > 180 && rotateY < 270)
	{
		arduino.sendDigital(PIN_LED, ARD_LOW);
		arduino.sendDigital(PIN_LED2, ARD_LOW);
		arduino.sendDigital(PIN_LED3, ARD_HIGH);
		arduino.sendDigital(PIN_LED4, ARD_LOW);
	}
	else if (rotateY > 270 && rotateY < 360)
	{
		arduino.sendDigital(PIN_LED, ARD_LOW);
		arduino.sendDigital(PIN_LED2, ARD_LOW);
		arduino.sendDigital(PIN_LED3, ARD_LOW);
		arduino.sendDigital(PIN_LED4, ARD_HIGH);
	}
	else if (rotateY > 360)
	{
		rotateY = 0;
		arduino.sendDigital(PIN_LED, ARD_HIGH);
		arduino.sendDigital(PIN_LED2, ARD_LOW);
		arduino.sendDigital(PIN_LED3, ARD_LOW);
		arduino.sendDigital(PIN_LED4, ARD_LOW);
	}

	arduino.update();
	//ofLog() << "isArduinoReady" << arduino.isArduinoReady() << endl;


	if (x < -200)
	{
		//cout << "links" << endl;
		x = -200;
		speedX = -speedX;
	}

	if (x > Width)
	{
		//cout << "rechts" << endl;
		x = Width;
		speedX = -speedX;

	}
	////////////////////

	if (y < -200)
	{
		//cout << "boven" << endl;
		y = -200;
		speedY = -speedY;
	}

	if (y > Height)
	{
		//cout << "onder" << endl;
		y = Height;
		speedY = -speedY;
	}
	/////////////////

	if (z < -200)
	{
		z = -200;
		speedZ = -speedZ;
	}

	if (z > Length)
	{
		z = Length;
		speedZ = -speedZ;
	}

	x += speedX;
	y += speedY;
	z += speedZ;


}

void ofApp::draw()
{
	ofDisableDepthTest();

	gui.draw();

	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);

	cam.begin();
	cam.setVFlip(true);

	if (useLight)
	{
		ofEnableLighting();
	}
	else
	{
		ofDisableLighting();
	}

	if (doRotate)
	{
		ofRotateYDeg(rotateY);
	}

	if (drawGrid)
	{
		ofDrawGrid(200);
	}

	ofEnableDepthTest();

	////////////////


	ofSetColor(color);
	ofDrawSphere(x, y, z, radius);

	ofSetColor(ofColor::yellow);
	ofDrawSphere(0, 0, 0, 100);

	ofSetColor(ofColor::blue);
	ofDrawSphere(200, 0, 0, 50);

	/////////////////
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


void ofApp::mousePressed(int x, int y, int button)
{
	// switch the LED on
	//doRotate = !doRotate;

	//useLight = useLight;
	//drawGrid = !drawGrid;

	cout << "aan" << endl;
}

void ofApp::mouseReleased(int x, int y, int button)
{
	// switch the LED off

	cout << "uit" << endl;
}