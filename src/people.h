//
//  people.h
//  sandboxSwarm
//
//  Created by Janwillem te Voortwis on 20/01/15.
//
//

#pragma once

#include <stdio.h>
#include "swarmBoid.h"
#include "swarm.h"
#include "vectorMap.h"

class people: public swarmBoid{
    public:
    people(vectorMap * map, swarm * swarm);
    
    void draw();

};
