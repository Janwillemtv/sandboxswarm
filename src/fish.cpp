//
//  fish.cpp
//  sandboxSwarm
//
//  Created by Janwillem te Voortwis on 20/01/15.
//
//

//#include "fish.h"
//
//fish::fish(vectorMap * map, swarm * swarm):swarmBoid(){
//    mapPointer = map;
//    swarmPointer = swarm;
//    maxSpeed = 7;           //swarming weighfactors
//    moveCenter = 0.01;
//    neighborAtract = 0.001;
//    neighborRepel = 0.15;
//    matchVelocity = 0.125;
//    objectRepel = 0.1;
//    mapWeight = 1.7;
//    average = 1;
//    c.set(ofRandom(230.0,255.0),ofRandom(200.0,210.0),ofRandom(0.0,10.0));
//    drawShip = false;
//    //================================================
//    
//    scale = ofRandom(1.0, 1.5);//random scale
//
//}
//
//void fish::draw(){
//    ofSetColor(c);
//    ofVec2f temp = vel;
//    ofVec2f triBehind = pos - (10*temp.normalize());  //calculate behind of the tail
//    ofVec2f triBehindLeft = triBehind - (8*temp.getRotated(90).normalize());  // calculate left and right respectively
//    ofVec2f triBehindRight = triBehind + (8*temp.getRotated(90).normalize());
//    ofTriangle(pos.x,pos.y,triBehindLeft.x,triBehindLeft.y,triBehindRight.x,triBehindRight.y);  // draw triangle on calculated vectors
//    ofCircle(pos.x, pos.y, scale * 3.0);
//}
