#include "ofApp.h"

void ofApp::setup(){
	setupMotors();
}

void ofApp::update(){
}

void ofApp::draw(){
	if (scene == "all") {
		for (auto & m : motors) {
			m.val = uiC->pFloat["val"];
		}
	}
	
	else if (scene == "vento") {
		ventando.update();
//		ventando.draw();
		for (auto & m : motors) {
			m.val = ventando.valsEasy[m.index];
		}
	}
	
	else if (scene == "seno") {
		for (auto & m : motors) {
			m.val = (sin(m.index * uiC->pFloat["a"] +
							ofGetElapsedTimef() * uiC->pFloat["tempo"]) * .5 + 0.5)
							* uiC->pFloat["mult"]
							+ uiC->pFloat["offset"]
			;
		}
	}
	
	else if (scene == "seno2") {
		for (auto & m : motors) {
			m.val = sin(m.index * uiC->pFloat["a"] +
							ofGetElapsedTimef() * uiC->pFloat["tempo"]) * .5
							* uiC->pFloat["mult"]
							+ 0.5;
			;
		}
	}

	else if (scene == "noise") {
		for (auto & m : motors) {
			m.val = ofNoise(
				ofGetElapsedTimef() * uiC->pFloat["noiseTempo"],
				uiC->pFloat["noiseA"] * m.index
				);
			m.val *= uiC->pFloat["mult"];
			m.val -= uiC->pFloat["mult"]*.5;
			m.val += uiC->pFloat["piso"];
			m.val = ofClamp(m.val, 0, 1);
		}
	} else if (scene == "noise2") {
		for (auto & m : motors) {
			float soma = 0;
			for (auto & a : { string("0"), string("1") }) {			
				if (uiC->pBool["ok"+a]) {
					float val = ofNoise(
						ofGetElapsedTimef() * uiC->pFloat["noiseTempo" + a],
						uiC->pFloat["noiseA" + a] * m.index
					);
					val += uiC->pFloat["offset" + a];
					val *= uiC->pFloat["mult" + a];
					val -= uiC->pFloat["mult" + a] *.5;
//					val += uiC->pFloat["piso" + a];
					val = ofClamp(val, 0, 1);
					soma += val;
				}
			}
			m.val = soma;
		}
	}

	for (auto & m : motors) {
		m.val = ofClamp(m.val, ui->pFloat["piso"], ui->pFloat["teto"]);
		if (scene != "_") {
			uiM->set("m_"+m.indexs, m.val);
		}
		m.potencia = uiM->pFloat["m_"+m.indexs];
		m.setRpm(uiM->pInt["rpm"]);
		m.update();
	}

	if (u.pBool["draw"]) {
		fbo->begin();
		ofClear(0,255);
		ofSetColor(255);
		ofNoFill();
		for (auto & m : motors) {
			m.draw();
		}
		fbo->end();
		soft.drawFbo();
	}

	if (u.pBool["sendMotors"] ) {
		sendMotors();
	}
}

void ofApp::keyPressed(int key) {
	if (key == 'r') {
		soft.fboToPng();
	}
}
