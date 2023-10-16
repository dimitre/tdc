#pragma once
#include "ofMain.h"
#include "ofxMicroUI.h"
#include "ofxMicroUISoftware.h"

#include "polar.h"
//#include "ofxSerial.h"


class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);

	ofxMicroUI u { "u.txt" };
	ofxMicroUISoftware soft { &u, "Timidez", 1 };
	ofxMicroUI * ui = &u.uis["ui"];
	ofxMicroUI * uiC = &u.uis["scene"];
	ofxMicroUI * uiM = &u.uis["motors"];
	ofFbo * fbo = &soft.fbos[0];
	string & scene = ui->pString["scene"];

	ofSerial serial;
//	ofxSerial serial;

	ofBuffer buffer;
	string serialData;

	#include "timidez.h"
	#include "vento.h"

	void uiEvents(ofxMicroUI::element & e) {
		if (e.name == "alinha") {
			for (auto & m : motors) {
				m.angle = 0;
			}
		}
		else if (e.name == "desalinha") {
			for (auto & m : motors) {
				m.angle = ofRandom(0,360);
			}
		}
	}
	
	void exit() {
		exitMotors();
	}
	// #include "fract.h"
};
