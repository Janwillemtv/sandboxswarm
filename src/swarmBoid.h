//
//  swarmBoid.h
//  emptyExample
//
//  Created by Janwillem te Voortwis on 03/01/15.
//
//
//#pragma once

#ifndef SWARMBOID_H
#define SWARMBOID_H

#include "ofMain.h"
#include <stdio.h>
#include "vectorMap.h"




class swarmBoid{
    public:
    
    swarmBoid();
    
    vectorMap * mapPointer;
    vector<swarmBoid*> swarmPointer;
    vector<ofVec4f> vectorPos;
    
    
    
    ofPoint pos;
    ofPoint vel;
    
    void set(vectorMap * mapPointer, vector<swarmBoid*>  swarmPointer, int itSelf);
    void update();
    virtual void draw(){};
    float distance(ofVec2f v1, ofVec2f v2);
    void calcSwarm(int i);
    void calcColision();
    void alterVector();
    void getMapVector();
    void mouseUpdate(int x, int y);
    
    int mode;
    float scale;
    ofColor c;
    bool drawShip;
    
    ofVec2f center, nRepel, match, nAtract, oRepel;
    
    float dist;
    
    ofPolyline line;
    ofMesh traingle;
    
    int itSelf;
    float maxSpeed;
    float moveCenter;
    float neighborAtract;
    float neighborRepel;
    float matchVelocity;
    float objectRepel;
    float mapWeight;
    int numberNeighbours;
    int average;

};

class fish : public swarmBoid{
    public:
        fish();
        void draw();


};

class people : public swarmBoid{
public:
    people();
    void draw();
    
    
};
#endif
