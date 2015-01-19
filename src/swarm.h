//
//  swarm.h
//  sandboxSwarm
//
//  Created by Janwillem te Voortwis on 07/01/15.
//
//

#pragma once

#include <stdio.h>
#include "swarmBoid.h"
#include "ofMain.h"
#include "vectorMap.h"

class swarm{
    public:
        swarm();
        void set(int mode, int num,vectorMap * mapPointer);
        void update();
        void draw();
        void mouseUpdate(int x, int y);

        vector <swarmBoid> b;
        vector <swarmBoid*> p;
};