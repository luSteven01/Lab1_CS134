#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	gui.setup();
	gui.add(setHeading.setup("Draw Heading", true));
	gui.add(setImage.setup("Use Image", false));
    gui.add(triScale.setup("Triangle Scale", 1.0, 0, 10.0));
	gui.add(imgScale.setup("Image Scale", 1.0, 0, 10.0));

	
	// Load Image Shape
	ofImage imagefile;
	imagefile.load("images/ship.png");
	image.setImage(imagefile);
	image.position = glm::vec3( ofGetWidth()/2, ofGetHeight()/2, 0);
	
	// Load Triangle on the middle of the screen
	triangle.position = glm::vec3( ofGetWidth()/2, ofGetHeight()/2, 0);
	shape = &triangle;
	
}

//--------------------------------------------------------------
void ofApp::update(){
	Shape *otherShape = shape;
	
	if (shape == &triangle) {
		float getTriScale = triScale;
		shape -> scale = glm::vec3(getTriScale, getTriScale, 1.0);
	} else if (shape == &image) {
		float getImgScale = imgScale;
		shape -> scale = glm::vec3(getImgScale, getImgScale, 1.0);
	}
	
	// Switch between the image and triangle shape
	if (setImage) {
		shape = &image;
	} else {
		shape = &triangle;
	}
	
	// If shape is not the other shape
	// Use the transformation of the other shape to save to current shape
	if (shape != otherShape) {
		shape->position = otherShape->position;
		shape->rotation = otherShape->rotation;
		shape->scale = otherShape->scale;
	}
	
	if (isLeft) {
		shape -> rotation -= 2.5;
	}
	
	if (isRight) {
		shape -> rotation += 2.5;
	}
	
	if (isUp) {
		// r(t) = o + dt
		// Find d
		float d = glm::radians(shape -> rotation - 90);
		
		//t is speed
		float t = 2.5;
		
		//black magic with math
		shape -> position.x += t * cos(d);
		shape -> position.y += t * sin(d);
	}
	
	if (isDown) {
		// r(t) = o + dt
		// Find d in radians
		float d = glm::radians(shape -> rotation - 90);
		
		// t is speed
		float t = 2.5;
		
		// black magic with math
		shape -> position.x -= t * cos(d);
		shape -> position.y -= t * sin(d);
	}
	
	if (isRotating) {
		glm::vec3 direction = target - shape->position;
		float targetAngle = glm::degrees(atan2(direction.y, direction.x));

		float diff = targetAngle - shape->rotation + 90;

		// take shortest distance to dot
		while (diff < -180) diff += 360;
		while (diff > 180) diff -= 360;
		
		shape->rotation += diff * 0.25;

		if (abs(diff) < 0.1) {
			isRotating = false;
		}
	}

}

//--------------------------------------------------------------
void ofApp::draw(){
	
	shape -> draw();
	if (setHeading) {
		ofPushMatrix();
		ofMultMatrix(shape -> getTransform());
		ofSetColor(ofColor::black);
		ofDrawLine(glm::vec3(0,0,0), glm::vec3(0,-110,0));
		ofPopMatrix();
	}
	gui.draw();
	
	if (isRotating) {
		circle.draw();
	}
}

//--------------------------------------------------------------
void ofApp::exit(){
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == OF_KEY_LEFT) {
		isLeft = true;
	}
	if (key == OF_KEY_RIGHT) {
		isRight = true;
	}
	if (key == OF_KEY_UP) {
		isUp = true;
		cout << "Up "<< isUp << endl;
	}
	if (key == OF_KEY_DOWN) {
		isDown = true;
		cout << "Down " << isDown << endl;
	}
	if (key == OF_KEY_COMMAND || key == OF_KEY_CONTROL) {
		CmdOrControl= true;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if (key == OF_KEY_LEFT) {
		isLeft = false;
	}
	if (key == OF_KEY_RIGHT) {
		isRight = false;
	}
	if (key == OF_KEY_UP) {
		isUp = false;
		cout << "Up " << isUp << endl;
	}
	if (key == OF_KEY_DOWN) {
		isDown = false;
		cout << "Down " << isDown << endl;
	}
	if (key == OF_KEY_COMMAND || key == OF_KEY_CONTROL) {
		CmdOrControl = false;
	}
	
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	// Drag the image if it's selected
	if (shape -> isSelected) {
		shape -> position = glm::vec3(x, y, 0);
	}
	
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	
	if ( shape -> inside(glm::vec3(x,y,0)) ) {
		shape -> isSelected = true;
	} else {
		shape -> isSelected = false;
		if (CmdOrControl) {
			isRotating = true;
			circle.position = glm::vec3(x,y,0);
			target = glm::vec3(x,y,0);
			cout << "New circle position " << circle.position << endl;
		}
	}
	
	
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
