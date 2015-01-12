#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    map.set(15,20);

    
    int num = 50;
   
    flock.set(num,map.vectorGrid(),map.contours());
    
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    map.update();
    flock.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor(60,60,60), ofColor(10,10,10));
    map.draw();
    flock.draw();
    ofSetColor(255,0,0);
    ofCircle(mouse.x, mouse.y, 15);
   
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key){
        case '>':
        case '.':
            map.farAlter(1);
            break;
            
        case '<':
        case ',':
            map.farAlter(-1);
            break;
            
        case '+':
        case '=':
            map.nearAlter(1);
            break;
            
        case '-':
            map.nearAlter(-1);
            break;
    
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    flock.mouseUpdate(x, y);
    mouse.x = x;
    mouse.y = y;
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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::exit() {
    map.close();
}