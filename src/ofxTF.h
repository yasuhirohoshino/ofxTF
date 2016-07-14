#pragma once

#include "ofMain.h"

struct TFObject {
	string inLocationName;
	char* outLocationName;
	int num;
	ofTexture texBuffer[2];
	ofBufferObject bufferObject[2];
};

class ofxTF {
public:
	void setup(int total, string shaderPath);
	void generate();
	void loadShader(string shaderPath);
	void begin();
	void end();
	void addBufferObject(string inLocationName, string outLocationName, int num, int internalFormat, float * values);
	ofTexture* getTexture(int index);
	ofShader* getShader();
	ofVbo* getVbo();

private:
	GLuint feedback[2];
	ofVbo vbo[2];
	int frame;
	vector<TFObject> tfObjects;
	int total;
	ofShader shader;
	vector<char*> feedbackVaryings;
    string shaderPath;
};