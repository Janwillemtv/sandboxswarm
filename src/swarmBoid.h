//
//  swarmBoid.h
//  emptyExample
//
//  Created by Janwillem te Voortwis on 03/01/15.
//
//
<<<<<<< Updated upstream
//#pragma once

#ifndef SWARMBOID_H
#define SWARMBOID_H
=======
#ifndef FISH_H
#define FISH_H
#ifndef PEOPLE_H
#define PEOPLE_H
#pragma once
>>>>>>> Stashed changes

#include "ofMain.h"
#include <stdio.h>
#include "vectorMap.h"
#include "fish.h"
#include "people.h"

class swarmBoid{
    public:
    
    swarmBoid();
    
    vectorMap * mapPointer;
    //vector<swarmBoid*> swarmPointer;
   // vector<ofVec4f> vectorPos;
    
    //vector<water> ripple;
    
    unsigned long oldmillis;
    
    
    ofPoint pos;
    ofPoint vel;
    
<<<<<<< Updated upstream
    void set(vectorMap * mapPointer, vector<swarmBoid*>  swarmPointer, int itSelf);
    //void update();
    virtual void draw(){};
    virtual void update(){};
    virtual void drawShadow(){};
=======
    void set(int mode, vectorMap * mapPointer, vector<swarmBoid*>  swarmPointer, int itSelf);
    void update(vector<swarmBoid> b, int p);
    virtual void draw();
    void drawBoat();
    void drawFish();
>>>>>>> Stashed changes
    float distance(ofVec2f v1, ofVec2f v2);
    void calcSwarm(int i, int j);
    virtual void calcColision(){};
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
    ofImage boat;
    ofImage shadow;

};

class fish : public swarmBoid{
    public:
        fish();
        void draw();
        void drawShadow();
        void update();
        void calcColision();
    

};

class people : public swarmBoid{
public:
    people();
    float offset;
    void draw();
    void drawShadow();
    void update();
    void calcColision();
    
};
#endif
<<<<<<< Updated upstream
=======
#endif
>>>>>>> Stashed changes
