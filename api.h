//float nextCheck = 0;
//float interval = 5;
//
//void updateApi() {
//
//	if (ofGetElapsedTimef() > nextCheck) {
//		nextCheck = ofGetElapsedTimef() + interval;
//		string command ="cd /Volumes/tool/ofw/apps/WerkApps/Timidez01/bin/python/; /opt/homebrew/bin/python3 vento.py"; // + fullPath;
////		cout << "update api : " << command << endl;
//		string res = ofSystem(command);
//		nlohmann::json j = nlohmann::json::parse(res);
//		cout << j["dir"] << endl;
//		cout << j["direction"] << endl;
//		cout << j["speed"] << endl;
//	}
//}
//
