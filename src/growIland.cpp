//
//  growIland.cpp
//  sandboxSwarm
//
//  Created by Janwillem te Voortwis on 10/01/15.
//  Improved by Raoul Fasel
//

#include "growIland.h"

growIland::growIland(ofVec2f position){
    finalSize = (int)(ofRandom(10.0,20.0));
    pos = position;
    growFac = (int)(ofRandom(1.0,2.0));
    size = 0;
    erase = 0;
    c.set(ofRandom(15.0,50.0),ofRandom(200,255.0),ofRandom(15.0,50.0));
    
}

void growIland::set(){
    
}

void growIland::update(){
    size += growFac;
    if(size>finalSize) size = finalSize;
}

void growIland::draw(){
    ofSetColor(c);
    ofCircle(pos, size);
}

void growIland::setNull(unsigned int time){
    erase = time;
}