#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    
    float * position = new float[numParticles * 3];
    for(int i = 0; i<numParticles; i++){
        position[i * 3 + 0] = ofRandom(-10, 10);
        position[i * 3 + 1] = ofRandom(-10, 10);
        position[i * 3 + 2] = ofRandom(-10, 10);
    }
    
    float * velocity = new float[numParticles * 3];
    for(int i = 0; i<numParticles; i++){
        velocity[i * 3 + 0] = ofRandom(-1, 1);
        velocity[i * 3 + 1] = ofRandom(-1, 1);
        velocity[i * 3 + 2] = ofRandom(-1, 1);
    }
    
    float * age = new float[numParticles];
    for(int i = 0; i<numParticles; i++){
        age[i] = 0;
    }
    
    float * lifetime = new float[numParticles];
    for(int i = 0; i<numParticles; i++){
        lifetime[i] = 1;
    }
    
    tf.setup(numParticles, "shaders/transformFeedback.vert");
    tf.addBufferObject("inPosition", "outPosition", 3, GL_RGB32F, position);
    tf.addBufferObject("inVelocity", "outVelocity", 3, GL_RGB32F, velocity);
    tf.addBufferObject("inAge", "outAge", 1, GL_R32F, age);
    tf.addBufferObject("inLifetime", "outLifetime", 1, GL_R32F, lifetime);
    tf.generate();
    
    renderShader.load("shaders/render");
    
    ofDisableArbTex();
    particleImage.load("spark.png");
    ofEnableArbTex();
    
    gui.setup("particles");
    gui.add(startColor.set("start color", ofFloatColor(1.0, 0.5, 0.0, 1.0), ofFloatColor(0.0, 0.0, 0.0, 1.0), ofFloatColor(1.0, 1.0, 1.0, 1.0)));
    gui.add(endColor.set("end color", ofFloatColor(0.0, 0.5, 1.0, 1.0), ofFloatColor(0.0, 0.0, 0.0, 1.0), ofFloatColor(1.0, 1.0, 1.0, 1.0)));
    gui.add(timestep.set("timestep", 0.5, 0.0, 10.0));
    gui.add(scale.set("scale", 0.05, 0.0, 1.0));
}

//--------------------------------------------------------------
void ofApp::update(){
    tf.begin();
    tf.getShader()->setUniform1f("time", ofGetElapsedTimef());
    tf.getShader()->setUniform1f("timestep", timestep);
    tf.getShader()->setUniform1f("scale", scale);
    tf.getShader()->setUniform1f("maxLifetime", 100.0);
    tf.end();
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableAlphaBlending();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    
    cam.begin();
    ofEnablePointSprites();
    renderShader.begin();
    renderShader.setUniformTexture("spriteTex", particleImage.getTexture(), 1);
    renderShader.setUniform4f("startColor", startColor);
    renderShader.setUniform4f("endColor", endColor);
    tf.getVbo()->draw(GL_POINTS, 0, numParticles);
    renderShader.end();
    ofDisablePointSprites();
    cam.end();
    
    ofDisableAlphaBlending();

    gui.draw();
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

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
