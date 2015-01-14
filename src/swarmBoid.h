//
//  swarmBoid.h
//  emptyExample
//
//  Created by Janwillem te Voortwis on 03/01/15.
//
//
#pragma once

#include "ofMain.h"
#include <stdio.h>
#include "vectorMap.h"




class swarmBoid{
    public:
    
    swarmBoid();
    
    vector <ofVec4f> * mapPointer;
    vector<swarmBoid*> swarmPointer;
    vector<ofVec4f> vectorPos;
    
    ofxCvContourFinder * contourPointer;
    
    
    ofPoint pos;
    ofPoint vel;
    
    void set(int mode, vector<ofVec4f> * mapPointer, ofxCvContourFinder * contourPointer, vector<swarmBoid*>  swarmPointer, int itSelf);
    void update(vector<swarmBoid> b, int p);
    void draw();
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
