#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	circle.scale.x += 4.0;
	
	
	// Load Image Shape
//	imageShape.scale.x = 3.0;
//	ofImage image;
//	image.load("images/ship.png");
//	imageShape.setImage(image);
//	imageShape.position = glm::vec3(300,300,0);
	
	// Load Triangle on the middle of the screen
	triangleShape.position = glm::vec3( ofGetWidth()/2, ofGetHeight()/2, 0);
	cout << ofGetHeight() << endl;
	cout << ofGetWidth() << endl;

}

//--------------------------------------------------------------
void ofApp::update(){
	//imageShape.rotation += 0.5;
}

//--------------------------------------------------------------
void ofApp::draw(){
	//imageShape.draw();
	
	triangleShape.draw();
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	if (triangleShape.inside(glm::vec3(x,y,0)))
		cout << "point is inside" << endl;
	else
		cout << "point is outside" << endl;
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
