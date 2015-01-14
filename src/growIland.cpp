//
//  growIland.cpp
//  sandboxSwarm
//
//  Created by Janwillem te Voortwis on 10/01/15.
//
//

#include "growIland.h"

growIland::growIland(ofVec2f position){
    finalSize = (int)(ofRandom(10.0,20.0));
    pos = position;
    growFac = (int)(ofRandom(1.0,2.0));
    randomTime = (int)ofRandom(500);
    size = 0;
    erase = 0;
    c.set(ofRandom(220.0,255.0),ofRandom(220,255.0),ofRandom(220.0,255.0));
    
}

void growIland::set(){
    
}

void growIland::update(){
   // if((ofGetElapsedTimeMillis()+randomTime)%5<1){
    size += growFac;
    if(size>finalSize) size = finalSize;
   // }
}

void growIland::draw(){
    ofSetColor(c);
    ofCircle(pos, size);
}

void growIland::setNull(unsigned int time){
    erase = time;
}