//
//  growIland.cpp
//  sandboxSwarm
//
//  Created by Janwillem te Voortwis on 10/01/15.
//  Improved by Raoul Fasel
//

#include "growIland.h"

growIland::growIland(ofVec2f position){ // let land grow with fauna
    finalSize = (int)(ofRandom(10.0,20.0));
    pos = position;
    growFac = (int)(ofRandom(1.0,2.0));
    size = 0;
    erase = 0;
    red =ofRandom(15.0,50.0);
    green = ofRandom(200,255.0);
    blue = ofRandom(15.0,50.0);
    c.set(red,green,blue);// set rand colors for trees
    influence = 0;
}


void growIland::update(){//update land
   
    size += growFac;
    if(size>finalSize) size = finalSize;//check tree finished growing
}

void growIland::draw(){ //draw
    ofSetColor(c);
    ofCircle(pos, size);
}

void growIland::setNull(unsigned int time){//resest land
    erase = time;
}