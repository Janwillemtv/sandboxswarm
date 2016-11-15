//
//  people.cpp
//  sandboxSwarm
//
//  Created by Janwillem te Voortwis on 20/01/15.
//
//

#include "people.h"

people::people(vectorMap * map, swarm * swarm):swarmBoid(){
    mapPointer = map;
    swarmPointer = swarm;
    maxSpeed = 7;           //swarming weighfactors
    moveCenter = 0.01;
    neighborAtract = 0.001;
    neighborRepel = 0.15;
    matchVelocity = 0.125;
    objectRepel = 0.1;
    mapWeight = -2;
    average = 1;
    c.set(ofRandom(135.0,145.0),ofRandom(35.0,46.0),ofRandom(70.0,75.0));
    drawShip = true;
    //================================================
    scale = ofRandom(2.0, 2.5);//random scale

}

void people::draw(){
    if(drawShip){// draw the boat
    ofVec2f temp = vel;
    ofSetColor(74, 62, 14);
    ofPath shipLine;
    ofVec2f boatFront = pos + (30*temp.normalize());  //calculate front of the boat
    ofVec2f boatBehind = pos - (20*temp.normalize());  //calculate behind of the boat
    ofVec2f boatMiddle = pos + (7*temp.normalize());
    ofVec2f boatBehindLeft = boatBehind - (10*temp.getRotated(90).normalize());  // calculate behind left and right respectively
    ofVec2f boatBehindRight = boatBehind + (10*temp.getRotated(90).normalize());
    ofVec2f boatMiddleLeft = boatMiddle + (10*temp.getRotated(-90).normalize());  // calculate middle left and right respectively
    ofVec2f boatMiddleRight = boatMiddle + (10*temp.getRotated(90).normalize());
    
    // turn all the points into curves
    shipLine.curveTo(boatBehind.x,boatBehind.y);
    shipLine.curveTo(boatBehindRight.x,boatBehindRight.y);
    shipLine.curveTo(boatMiddleRight.x,boatMiddleRight.y);
    shipLine.curveTo(boatFront.x,boatFront.y);
    shipLine.curveTo(boatMiddleLeft.x,boatMiddleLeft.y);
    
    shipLine.curveTo(boatBehindLeft.x,boatBehindLeft.y);
    shipLine.curveTo(boatBehind.x,boatBehind.y);
    
    shipLine.close();
    shipLine.setFilled(true);
    shipLine.setFillColor(ofColor(74, 62, 14));
    shipLine.setStrokeWidth(2);
    shipLine.setStrokeColor(ofColor(255,0,0));
    shipLine.draw();
    }
    ofCircle(pos.x, pos.y, scale * 3.0);

}