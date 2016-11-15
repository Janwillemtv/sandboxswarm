//
//  growIland.cpp
//  sandboxSwarm
//
//  Created by Janwillem te Voortwis on 10/01/15.
//  Improved by Raoul Fasel
//

#include "growIland.h"

growIland::growIland(ofVec2f position){ // let land grow with fauna
    tree.loadImage("tree_mini.png");
    finalSize = (int)(ofRandom(20.0,30.0));
    pos = position;
    growFac = (int)(ofRandom(1.0,2.0));
    size = 0;
    erase = 0;
    angle = ofRandom(0,50);
    red =ofRandom(15.0,50.0);
    green = ofRandom(200,255.0);
    blue = ofRandom(15.0,50.0);
    c.set(red,green,blue);// set rand colors for trees
    influence = 0;
}

void growIland::set(){
    
}

void growIland::update(){//update land
    
    if(red+influence>=255) {
        c.set(255,0,blue);
        influence = 255-red;
    }
    else if(green-influence>=255){
        c.set(0,255,blue);
        influence =-1* (255-green);
    }
    else if(green-influence<=0) c.set(255,0,blue);
    else if(red+influence<=0) c.set(0,255,blue);
    else c.set((int)red+influence,(int)green-influence,blue);
   
    size += growFac;
    if(size>finalSize) size = finalSize;//check tree finished growing
}

void growIland::draw(){ //draw
    ofSetColor(c);
    glPushMatrix();
    ofTranslate(pos.x,pos.y);
    ofRotate(angle);
    //ofSetColor(255);
    ofEnableAlphaBlending();
    tree.draw(-size/2,-size/2,size,size);
    ofDisableAlphaBlending();
    glPopMatrix();
    //ofCircle(pos, size);
}

void growIland::setNull(unsigned int time){//resest land
    erase = time;
}