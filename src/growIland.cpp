//
//  growIland.cpp
//  sandboxSwarm
//
//  Created by Janwillem te Voortwis on 10/01/15.
//
//

#include "growIland.h"

growIland::growIland(ofVec2f position){//init island growth
    finalSize = (int)(ofRandom(10.0,20.0));
    pos = position;
    growFac = (int)(ofRandom(1.0,2.0));
    size = 0;
    erase = 0;
    c.set(ofRandom(220.0,255.0),ofRandom(220,255.0),ofRandom(220.0,255.0));//randomize color
    
}

void growIland::set(){
    
}

void growIland::update(){//controlls growth and checks max growth
    size += growFac;
    if(size>finalSize) size = finalSize;
}

void growIland::draw(){//draw island with color
    ofSetColor(c);
    ofCircle(pos, size);
}

void growIland::setNull(unsigned int time){//set time to zero
    erase = time;
}