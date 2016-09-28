//
//  fish.h
//  sandboxSwarm
//
//  Created by Janwillem te Voortwis on 20/01/15.
//
//
#ifndef SWARMBOID_H
#define SWARMBOID_H

#pragma once

#include <stdio.h>
#include "ofMain.h"
#include "swarmBoid.h"
//#include "swarm.h"
//#include "vectorMap.h"

class fish : public swarmBoid{
    public:
    fish();
    void draw();

};
#endif
