//
//  fish.h
//  sandboxSwarm
//
//  Created by Janwillem te Voortwis on 20/01/15.
//
//

#pragma once

#include <stdio.h>
#include "ofMain.h"
#include "swarmBoid.h"
//#include "swarm.h"
//#include "vectorMap.h"

class fish : public swarmBoid{
    public:
    fish(vectorMap * map, swarm * swarm);
    void draw();

};

