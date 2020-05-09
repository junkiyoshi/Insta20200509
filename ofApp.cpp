#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetLineWidth(2);
	ofEnableDepthTest();

	int size = 20;
	ofColor color;
	for (int x = -300; x <= 300; x += size) {

		for (int y = -300; y <= 300; y += size) {

			color.setHsb(ofRandom(255), 255, 255);

			this->box_location_list.push_back(glm::vec2(x, y));
			this->box_height_list.push_back(0);
			this->box_color_list.push_back(color);
		}
	}

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face.clear();
	this->frame.clear();

	auto noise_location = glm::vec2(ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.008), 0, 1, -300, 300), ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.008), 0, 1, -300, 300));

	for (int i = 0; i < this->box_location_list.size(); i++) {

		auto distance = glm::distance(this->box_location_list[i], noise_location);
		if (distance < 40) {

			this->box_height_list[i] += this->box_height_list[i] > 300 ? 1 : distance * 0.5;
		}

		this->setBoxToMesh(this->face, this->frame, glm::vec3(this->box_location_list[i], this->box_height_list[i] * 0.5), 18, 18, this->box_height_list[i], ofColor(this->box_color_list[i], 92), this->box_color_list[i]);

		this->box_height_list[i] = this->box_height_list[i] <= 0 ? 0 : this->box_height_list[i] - 3;
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateZ(45);

	this->face.draw();
	this->frame.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
void ofApp::setBoxToMesh(ofMesh& face_target, ofMesh& frame_target, glm::vec3 location, float size, ofColor face_color, ofColor frame_color) {

	this->setBoxToMesh(face_target, frame_target, location, size, size, size, face_color, frame_color);
}

//--------------------------------------------------------------
void ofApp::setBoxToMesh(ofMesh& face_target, ofMesh& frame_target, glm::vec3 location, float height, float width, float depth, ofColor face_color, ofColor frame_color) {

	int face_index = face_target.getNumVertices();
	int frame_index = frame_target.getNumVertices();

	face_target.addVertex(location + glm::vec3(width * -0.5, height * 0.5, depth * -0.5));
	face_target.addVertex(location + glm::vec3(width * 0.5, height * 0.5, depth * -0.5));
	face_target.addVertex(location + glm::vec3(width * 0.5, height * 0.5, depth * 0.5));
	face_target.addVertex(location + glm::vec3(width * -0.5, height * 0.5, depth * 0.5));

	face_target.addVertex(location + glm::vec3(width * -0.5, height * -0.5, depth * -0.5));
	face_target.addVertex(location + glm::vec3(width * 0.5, height * -0.5, depth * -0.5));
	face_target.addVertex(location + glm::vec3(width * 0.5, height * -0.5, depth * 0.5));
	face_target.addVertex(location + glm::vec3(width * -0.5, height * -0.5, depth * 0.5));

	face_target.addIndex(face_index + 0); face_target.addIndex(face_index + 1); face_target.addIndex(face_index + 2);
	face_target.addIndex(face_index + 0); face_target.addIndex(face_index + 2); face_target.addIndex(face_index + 3);

	face_target.addIndex(face_index + 4); face_target.addIndex(face_index + 5); face_target.addIndex(face_index + 6);
	face_target.addIndex(face_index + 4); face_target.addIndex(face_index + 6); face_target.addIndex(face_index + 7);

	face_target.addIndex(face_index + 0); face_target.addIndex(face_index + 4); face_target.addIndex(face_index + 1);
	face_target.addIndex(face_index + 4); face_target.addIndex(face_index + 5); face_target.addIndex(face_index + 1);

	face_target.addIndex(face_index + 1); face_target.addIndex(face_index + 5); face_target.addIndex(face_index + 6);
	face_target.addIndex(face_index + 6); face_target.addIndex(face_index + 2); face_target.addIndex(face_index + 1);

	face_target.addIndex(face_index + 2); face_target.addIndex(face_index + 6); face_target.addIndex(face_index + 7);
	face_target.addIndex(face_index + 7); face_target.addIndex(face_index + 3); face_target.addIndex(face_index + 2);

	face_target.addIndex(face_index + 3); face_target.addIndex(face_index + 7); face_target.addIndex(face_index + 4);
	face_target.addIndex(face_index + 4); face_target.addIndex(face_index + 0); face_target.addIndex(face_index + 3);

	frame_target.addVertex(location + glm::vec3(width * -0.5, height * 0.5, depth * -0.5));
	frame_target.addVertex(location + glm::vec3(width * 0.5, height * 0.5, depth * -0.5));
	frame_target.addVertex(location + glm::vec3(width * 0.5, height * 0.5, depth * 0.5));
	frame_target.addVertex(location + glm::vec3(width * -0.5, height * 0.5, depth * 0.5));

	frame_target.addVertex(location + glm::vec3(width * -0.5, height * -0.5, depth * -0.5));
	frame_target.addVertex(location + glm::vec3(width * 0.5, height * -0.5, depth * -0.5));
	frame_target.addVertex(location + glm::vec3(width * 0.5, height * -0.5, depth * 0.5));
	frame_target.addVertex(location + glm::vec3(width * -0.5, height * -0.5, depth * 0.5));

	frame_target.addIndex(frame_index + 0); frame_target.addIndex(frame_index + 1);
	frame_target.addIndex(frame_index + 1); frame_target.addIndex(frame_index + 2);
	frame_target.addIndex(frame_index + 2); frame_target.addIndex(frame_index + 3);
	frame_target.addIndex(frame_index + 3); frame_target.addIndex(frame_index + 0);

	frame_target.addIndex(frame_index + 4); frame_target.addIndex(frame_index + 5);
	frame_target.addIndex(frame_index + 5); frame_target.addIndex(frame_index + 6);
	frame_target.addIndex(frame_index + 6); frame_target.addIndex(frame_index + 7);
	frame_target.addIndex(frame_index + 7); frame_target.addIndex(frame_index + 4);

	frame_target.addIndex(frame_index + 0); frame_target.addIndex(frame_index + 4);
	frame_target.addIndex(frame_index + 1); frame_target.addIndex(frame_index + 5);
	frame_target.addIndex(frame_index + 2); frame_target.addIndex(frame_index + 6);
	frame_target.addIndex(frame_index + 3); frame_target.addIndex(frame_index + 7);

	for (int i = 0; i < 8; i++) {

		face_target.addColor(face_color);
		frame_target.addColor(frame_color);
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}