#ifndef DmtrPolar
#define DmtrPolar

static float r2x (float a, float m) { return m * cos(ofDegToRad(a)); }
static float r2y (float a, float m) { return m * sin(ofDegToRad(a)); }

#ifdef C2A
static float c2a (float x, float y) { return ofRadToDeg(atan2(y,x)); }
static float c2m (float x, float y) { return sqrt(pow(x,2)+pow(y,2)); }

static float c2a3d (float x, float y, float z) { return ofRadToDeg(atan2(y,x)); }
static float c2m3d (float x, float y, float z) { return sqrt(pow(x,2) + pow(y,2) + pow(z,2)); }

//static float c2p3d (float x, float y, float z) { return acos(z / radius); }
//phi = acos(Z / radius)


static glm::vec2 c2p (glm::vec2 pos) {
	return glm::vec2(
		ofRadToDeg(atan2(pos.y, pos.x)),
		sqrt(pow(pos.x,2)+pow(pos.y,2))
	);
}

static glm::vec2 p2c (glm::vec2 pos) {
	return glm::vec2(pos.y * cos(ofDegToRad(pos.x)), pos.y * sin(ofDegToRad(pos.x)));
}

#endif /* DmtrPolar */
#endif /* DmtrPolar */
