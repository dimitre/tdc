
uint8_t motorData[20] = { 0 };

struct motor {
public:
	int index = 0;
	string indexs = "";
	float angle = 0;
	float rpm = 13;
	float vel = 0;

	// 19 de setembro - tentando armazenar tudo aqui antes da cena fechar.
	float val = 0;

	
	float potencia = 1;
	glm::ivec2 pos = { 0, 0 };
	float lastTime = 0;
	motor(int i, glm::ivec2 p) : index(i), pos(p) {
		setRpm(18);
		indexs = ofToString(index);
		angle = ofRandom(0, 360);
	}
	
	void setRpm(float r) {
		float rps = r/60.0;
		vel = rps * 360.0;
	}
	void update() {
		float deltaTime = ofGetElapsedTimef() - lastTime;
		angle += vel * deltaTime * potencia;
		lastTime = ofGetElapsedTimef();
	}
	
	void draw() {
		ofPushMatrix();
		ofTranslate(pos);
		ofDrawCircle(0, 0, 10);
		{
		float x = r2x(angle, 15);
		float y = r2y(angle, 15);
		ofDrawCircle(x, y, 4);
		}
		
		float y = 20 + sin(ofDegToRad(angle)) * 20.0;
		ofDrawLine(0, y, 0, y+10);
		ofPopMatrix();
	}
};

vector <motor> motors;

//int sendNumber = 0;
void sendMotors() {
	if (serial.isInitialized()) {
		for (auto & m : motors) {
			motorData[m.index] = uint8_t(int(255.0 * m.potencia));
		}
		serial.writeBytes(motorData, 20);
	}
//	serial.flush(false, true);
}

void exitMotors() {
	if (serial.isInitialized()) {
		for (auto & m : motors) {
			motorData[m.index] = 0;
		}
		serial.writeBytes(motorData, 20);
	}
}


void setupMotors() {
	for (int a=0; a<20; a++) {
		motors.emplace_back(motor(a, { 25 + a * 50, 75 }));
	}
	ofAddListener(uiM->uiEvent, this, &ofApp::uiEvents);
	
	vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
	if (deviceList.size() > 0) {
//		cout << deviceList[0].getDeviceName() << endl;
		if (deviceList[0].getDeviceName() != "cu.Bluetooth-Incoming-Port") {
			serial.setup(0, 57600); //open the first device
		}
	}
}

void updateMotors() {
	//	if (serial.isInitialized()) {
	//		int avail = serial.available();
	//		if (avail > 0) {
	//			ofBuffer buffer;
	//			serial.readBytes(buffer, avail);
	//			string serialData = buffer.getText();
	//			//		cout << "----> serial available " << avail << endl;
	//			//		cout << serialData << endl;
	//			serial.flush(true, false);
	//		} else {
	//		}
	//	}
}
