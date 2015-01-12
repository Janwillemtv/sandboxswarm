//
//  swarm.cpp
//  sandboxSwarm
//
//  Created by Janwillem te Voortwis on 07/01/15.
//
//
#include "ofMain.h"
#include "swarm.h"

swarm::swarm(){

}
//------------------------------
void swarm::set(int num,vector <ofVec4f> * mapPointer,ofxCvContourFinder * contourPointer){
    b.assign(num, swarmBoid()); // create swarm
    
    for(unsigned int i = 0; i < b.size(); i++){ // set swarm
        b[i].set(mapPointer,contourPointer);
    }
}

void swarm::update(){

    for(unsigned int i = 0; i < b.size(); i++){
        
        b[i].update(b,i); // update swarm
        
    }

}

void swarm::draw(){
    
    for(unsigned int i = 0; i < b.size(); i++){
        ofSetColor(0,255,0);
        b[i].draw();    //draw swarm
    }
}

void swarm::mouseUpdate(int x, int y){
    b[1].mouseUpdate(x,y);
}