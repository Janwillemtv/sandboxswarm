//
//  growIland.cpp
//  sandboxSwarm
//
//  Created by Janwillem te Voortwis on 10/01/15.
//  Improved by Raoul Fasel
//

#include "ripple.h"

ripple::ripple(ofVec2f position){ // let land grow with fauna
    finalSize = (int)(ofRandom(10.0,20.0));
    pos = position;
    growFac = (ofRandom(0.1,0.2));
    size = 0;
    erase = 0;
    red =ofRandom(130.0,190.0);
    green = ofRandom(130.0,190.0);
    blue = ofRandom(150.0,200.0);
    c.set(red,green,blue);// set rand colors for trees
    influence = 0;
}


void ripple::update(){//update land
    
    
    size += growFac;
    if(size>finalSize) size = finalSize;//check tree finished growing
}

void ripple::draw(){ //draw
    c = ofColor(c.r,c.g,c.b,255-(size/finalSize)*255);
    ofSetColor(c);
    ofNoFill();
    ofSetLineWidth(1);
    ofEnableAlphaBlending();
    ofDrawCircle(pos, (int)size);
    ofDisableAlphaBlending();
    ofFill();
}

void ripple::setNull(unsigned int time){//resest land
    erase = time;
}

bool ripple::returnSize(){
    if(finalSize == size)return true;
    else return false;
}
