#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){

	ofWindowSettings settings;
	settings.setSize(720, 320);
	settings.windowMode = OF_WINDOW;
    
	auto mainWindow = ofCreateWindow(settings);
	auto mainApp = make_shared<ofApp>();

	ofRunApp(mainWindow, mainApp);
	ofRunMainLoop();
}
