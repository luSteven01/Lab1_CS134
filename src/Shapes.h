#pragma once

#include "ofMain.h"

class Shape {
public:

	Shape() {}
	virtual void draw() {}
	virtual bool inside(glm::vec3 p) { return false; }
	glm::vec3 position = glm::vec3(0,0,0);
	float rotation = 0.0; // degrees
	glm::vec3 scale = glm::vec3(1.0, 1.0, 1.0);

	glm::mat4 getTransform() {
		glm::mat4 T = glm::translate(glm::mat4(1.0), position);
		glm::mat4 R = glm::rotate(glm::mat4(1.0), glm::radians(rotation), glm::vec3(0,0,1));
		glm::mat4 S = glm::scale(glm::mat4(1.0), scale);
		return (T * R * S);
	}

};

class CircleShape: public Shape {
public:

	CircleShape() {}
	void draw() {
		ofPushMatrix();   // store current state of transform matrix
		ofMultMatrix(getTransform()); // calculate new matrix
		ofSetCircleResolution(500);
		ofSetColor(ofColor::orangeRed);
		ofDrawCircle(glm::vec3(0,0,0), radius);
		ofSetColor(ofColor::white);
		ofDrawLine(glm::vec3(0,0,0), glm::vec3(radius,0,0));
		ofPopMatrix();
	}
	bool inside(glm::vec3 p) {
		glm::vec3 p1 = glm::inverse(getTransform()) * glm::vec4(p, 1);
		return ( glm::distance(p1, glm::vec3(0,0,0)) < radius);
	}
	float radius = 20.0;
};

class TriangleShape: public Shape {
public:
	glm::vec3 triPoint1 = glm::vec3(20,0,0); // right corner
	glm::vec3 triPoint2 = glm::vec3(-20,-20,0); // botton left corner
	glm::vec3 triPoint3 = glm::vec3(-20,20,0); // top left corner
	
	void draw() {
		ofPushMatrix();
		ofMultMatrix(getTransform());
		ofSetColor(ofColor::orangeRed);
		ofDrawTriangle(triPoint1, triPoint2, triPoint3);
		ofPopMatrix();
	}
	
	// Solution inspired by GeeksForGeeks "Check whether a given point lies inside a triangle or not"
	bool inside(glm::vec3 p) {
	
		glm::vec4 p1 = glm::inverse(getTransform()) * glm::vec4(p, 1.0);

		auto area = [](glm::vec3 areapt1, glm::vec3 areapt2, glm::vec3 areapt3) {
			return abs((areapt1.x * (areapt2.y - areapt3.y) + areapt2.x * (areapt3.y - areapt1.y) + areapt3.x * (areapt1.y - areapt2.y)) / 2.0);
		};

		float mainArea = area(triPoint1, triPoint2, triPoint3);

		float Area1 = area(p1, triPoint2, triPoint3);
		float Area2 = area(triPoint1, p1, triPoint3);
		float Area3 = area(triPoint1, triPoint2, p1);

		return ((Area1 + Area2 + Area3) == mainArea);
	}
};

class ImageShape: public Shape {
public:
	ImageShape() {};
	ImageShape( ofImage image) { this->image = image; }
	void setImage(ofImage image) {this->image = image;}

	void draw() {
		ofPushMatrix();   // store current state of transform matrix
		ofMultMatrix(getTransform()); // calculate new matrix
		ofSetColor(ofColor::white);
		image.draw(glm::vec3(-image.getWidth()/2.0,-image.getHeight()/2.0, 0));
		ofPopMatrix();
	}
	
//	bool inside(glm::vec3 p) {
//		
//	}

	ofImage image;
};
