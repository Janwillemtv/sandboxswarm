//
//  growIland.h
//  sandboxSwarm
//
//  Created by Janwillem te Voortwis on 10/01/15.
//
//

#pragma once

#include <stdio.h>
#include "ofMain.h"



class water{
public:
    water(ofVec2f position);
    
    void set();
    void update();
    void draw();
    void setNull(unsigned int time);
    Boolean returnSize();
    
    ofVec2f pos;
    
    int growFac;
    int size;
    int finalSize;
    unsigned int erase;
    int influence;
    ofColor c;
    float red,green,blue;
    
};