struct ventania {
public:
	
	ofxMicroUI * uiC = NULL;
	
	struct vento {
	public:
		float pos = 0;
		float vel = 0;
		
		vento(float p, float v) : pos(p), vel(v) {}
		
		void update() {
			pos += vel;
		}
	};

	vector <vento> ventos;
	float vals[20]  { 0 };
	float valsEasy[20]  { 0 };

	int cursor = 0;
	float nextJump = 0;
	float vel = 0;
	
	ventania(ofxMicroUI * _uiC) : uiC(_uiC) {
		vel = ofRandom(-1, 1);
		jump();
	}
	
	void jump() {
		nextJump = ofGetElapsedTimef() + ofRandom(uiC->pFloat["minTime"], uiC->pFloat["maxTime"]);
	}
	
	float nextCheckApi = 0;
//	float intervalApi = 5;
	float intervalApi = 3600;

	void update() {
		if (ofGetElapsedTimef() > nextCheckApi) {
			nextCheckApi = ofGetElapsedTimef() + intervalApi;
//			string command ="cd /Volumes/tool/ofw/apps/WerkApps/Timidez01/bin/python/; /opt/homebrew/bin/python3 vento.py"; // + fullPath;
			string command ="./python3 vento.py"; // + fullPath;
	//		cout << "update api : " << command << endl;
			string res = ofSystem(command);
			try {
				nlohmann::json j = nlohmann::json::parse(res);
				cout << j["dir"] << endl;
				cout << j["direction"] << endl;
				cout << j["speed"] << endl;
				
				uiC->set("oeste", j["dir"] < 0 );

				uiC->set("max", ofMap(j["speed"], 0, 100, 0, 2));
//				if (j["dir"] < 0) {
					

			} catch(std::exception & e) {
				cout << res << endl;
				cout << "error " << e.what() << endl;
			}
			cout << "----- command complete" << endl;
		}
		
		if (ofGetElapsedTimef() > nextJump) {
			float vel = ofRandom(uiC->pFloat["minVel"], uiC->pFloat["maxVel"]);
			if (uiC->pBool["oeste"]) {
				vel = -vel;
			}
			float inicio = vel < 0 ? 22 : -2;
			jump();
			ventos.emplace_back( inicio, vel );
//			cout << "VENTO " << inicio << " :: " << vel << endl;
		}
		
		for (auto & v : vals) {
			v = 0;
		}
		for (auto & v : ventos) {
			v.update();
			if (int(v.pos) >= 0 && int(v.pos) < 20) {
				// potencia maxima
//				cout << v.pos << endl;
//				cout << int(v.pos) << endl;
				vals[int(v.pos)] = uiC->pFloat["max"];
			}
		}
		
//		float e = uiC->pFloat["easing"];
		for (int a=0; a<20; a++) {
			float e = 0;
			if (vals[a] > valsEasy[a]) {
				e = uiC->pFloat["easing"];
			} else {
				e = uiC->pFloat["easing2"];
			}

//			cout << e << endl;
			if (e > 0) {
				valsEasy[a] += (vals[a]-valsEasy[a]) / e;
			} else {
				valsEasy[a] = vals[a];
			}
		}
	}

	void draw() {
		ofSetColor(255);
		for (int a=0; a<20; a++) {
			ofDrawRectangle(0, a*10, valsEasy[a] * 220 + 2, 8);
		}
	}
} ;

ventania ventando { uiC };
//
