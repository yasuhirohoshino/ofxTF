#include "ofxTF.h"

void ofxTF::setup(int total, string shaderPath)
{
	this->total = total;
    this->shaderPath = shaderPath;
}

void ofxTF::generate()
{
	loadShader(shaderPath);

	glGenTransformFeedbacks(2, feedback);

	for (int i = 0; i<2; i++) {
		for (int j = 0; j < tfObjects.size(); j++) {
			vbo[i].setAttributeBuffer(shader.getAttributeLocation(tfObjects[j].inLocationName), 
				tfObjects[j].bufferObject[i], 
				tfObjects[j].num,
				0);
		}

		glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, feedback[i]);

		for (int j = 0; j < tfObjects.size(); j++) {
			glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, j, tfObjects[j].bufferObject[i].getId());
		}

		glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);
	}

	frame = 1;
}

void ofxTF::loadShader(string shaderPath)
{
    this->shaderPath = shaderPath;
	shader.setupShaderFromFile(GL_VERTEX_SHADER, shaderPath);
	for (int i = 0; i < tfObjects.size(); i++) {
		feedbackVaryings.push_back(tfObjects[i].outLocationName);
	}
	glTransformFeedbackVaryings(shader.getProgram(), tfObjects.size(), &feedbackVaryings[0], GL_SEPARATE_ATTRIBS);
	shader.linkProgram();
}

void ofxTF::begin()
{
	frame = 1 - frame;
	shader.begin();
}

void ofxTF::end()
{
	glEnable(GL_RASTERIZER_DISCARD);
	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, feedback[frame]);
	glBeginTransformFeedback(GL_POINTS);
	vbo[1 - frame].draw(GL_POINTS, 0, total);
	glEndTransformFeedback();
	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);
	glDisable(GL_RASTERIZER_DISCARD);
	shader.end();
}

void ofxTF::addBufferObject(string inLocationName, string outLocationName, int num, int internalFormat, float * values)
{
	TFObject object;
	object.inLocationName = inLocationName;
    int length = outLocationName.length();
    char* name = new char[length + 1];
    memcpy(name, outLocationName.c_str(), length + 1);
	object.outLocationName = name;
	object.num = num;
	for (int i = 0; i < 2; i++) {
		object.bufferObject[i].allocate();
		object.bufferObject[i].bind(GL_TEXTURE_BUFFER);
		object.bufferObject[i].setData(sizeof(float) * total * object.num, values, GL_STREAM_DRAW);
		object.texBuffer[i].allocateAsBufferTexture(object.bufferObject[i], internalFormat);
	}
	tfObjects.push_back(object);
}

ofTexture * ofxTF::getTexture(int index)
{
	return  &tfObjects[index].texBuffer[frame];
}

ofShader * ofxTF::getShader()
{
	return &shader;
}

ofVbo * ofxTF::getVbo()
{
	return &vbo[frame];
}
