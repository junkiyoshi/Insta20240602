#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetLineWidth(1.5);
	ofEnableDepthTest();

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face.clear();
	this->frame.clear();

	int span = 10;
	float threshold = 0.5;
	float frame_param = ofGetFrameNum() * 0.05;
	float coordinate_param = 0.0065;
	int len = 300;
	ofColor line_color(239);

	int z = len + span * 0.5;

	float angle;
	glm::highp_mat4 rotation, twist;
	for (int i = 0; i <= 4; i++) {

		for (int x = -len; x <= len; x += span) {

			for (int y = -len * 3; y <= len * 3; y += span) {

				if (i <= 4) {

					angle = PI * 0.5 * i;
					rotation = glm::rotate(glm::mat4(), angle, glm::vec3(0, 1, 0));
				}

				auto index = this->face.getNumVertices();
				vector<glm::vec3> vertices;

				vertices.push_back(glm::vec4(x - span * 0.5, y - span * 0.5, z, 0) * rotation);
				vertices.push_back(glm::vec4(x + span * 0.5, y - span * 0.5, z, 0) * rotation);
				vertices.push_back(glm::vec4(x + span * 0.5, y + span * 0.5, z, 0) * rotation);
				vertices.push_back(glm::vec4(x - span * 0.5, y + span * 0.5, z, 0) * rotation);

				for (auto& vertex : vertices) {

					auto noise_value = ofNoise(vertex.y * 0.001 + ofGetFrameNum() * 0.025);
					auto twist_rad = ofMap(noise_value, -1, 1, PI * -6, PI * 6);
					twist = glm::rotate(glm::mat4(), twist_rad, glm::vec3(0, 1, 0));

					vertex = glm::vec4(vertex, 0) * twist;
				}

				this->face.addVertices(vertices);

				this->face.addIndex(index + 0); this->face.addIndex(index + 1); this->face.addIndex(index + 2);
				this->face.addIndex(index + 0); this->face.addIndex(index + 2); this->face.addIndex(index + 3);

				if (x == -len) {

					this->frame.addVertex(vertices[0]);
					this->frame.addVertex(vertices[3]);

					this->frame.addColor(line_color);
					this->frame.addColor(line_color);

					this->frame.addIndex(this->frame.getNumVertices() - 1);
					this->frame.addIndex(this->frame.getNumVertices() - 2);
				}

				if (y == len * 3) {

					this->frame.addVertex(vertices[2]);
					this->frame.addVertex(vertices[3]);

					this->frame.addColor(line_color);
					this->frame.addColor(line_color);

					this->frame.addIndex(this->frame.getNumVertices() - 1);
					this->frame.addIndex(this->frame.getNumVertices() - 2);
				}

				if (x == len) {

					this->frame.addVertex(vertices[1]);
					this->frame.addVertex(vertices[2]);

					this->frame.addColor(line_color);
					this->frame.addColor(line_color);

					this->frame.addIndex(this->frame.getNumVertices() - 1);
					this->frame.addIndex(this->frame.getNumVertices() - 2);
				}

				if (y == -len * 3) {

					this->frame.addVertex(vertices[0]);
					this->frame.addVertex(vertices[1]);

					this->frame.addColor(line_color);
					this->frame.addColor(line_color);

					this->frame.addIndex(this->frame.getNumVertices() - 1);
					this->frame.addIndex(this->frame.getNumVertices() - 2);
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	this->frame.draw();

	ofSetColor(39);
	this->face.draw();

	this->cam.end();

	/*
	int start = 300;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}