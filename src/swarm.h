//
//  swarm.h
//  sandboxSwarm
//
//  Created by Janwillem te Voortwis on 07/01/15.
//
//

#pragma once

#include <stdio.h>
#include "ofMain.h"
#include "vectorMap.h"
#include "swarmBoid.h"
#include "fish.h"
#include "people.h"

class swarm{
    public:
        swarm(int mode, int num,vectorMap * mapPointer);
<<<<<<< Updated upstream
        //void set(int mode, int num,vectorMap * mapPointer);
=======
        void set();
>>>>>>> Stashed changes
        void update();
        void draw();
        void drawShadow();
        void mouseUpdate(int x, int y);

    int mode;
        //vector <swarmBoid> b;
        vector <swarmBoid *> p;
};