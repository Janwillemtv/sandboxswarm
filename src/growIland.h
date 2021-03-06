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



class growIland{
    public:
        growIland(ofVec2f position);
    
        void set();
        void update();
        void draw();
        void setNull(unsigned int time);
    
        ofVec2f pos;
        ofImage tree;
        int angle;
    
        int growFac;
        int size;
        int finalSize;
        unsigned int erase;
        int influence;
        ofColor c;
        float red,green,blue;

};