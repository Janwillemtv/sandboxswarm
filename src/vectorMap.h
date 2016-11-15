//
//  vectorMap.h
//  emptyExample
//
//  Created by Janwillem te Voortwis on 06/01/15.
//
//
#pragma once

//#include "ofMain.h"
#include <stdio.h>
#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "growIland.h"


class vectorMap{
    public:
    vectorMap();
    vector<ofVec4f> vec;
    vector<ofFloatColor> color;
    ofMesh mesh;
    ofMesh * getMesh();
    void set();
    void update();
    void draw();
    void close();
    void reposition();
    void getKinectImage();
    void calcVectors();
    void makeTrees();
    void infect(ofVec2f pos, int infuence);
    ofxKinect kinect;
    
    ofxCvColorImage colorImg;
    ofImage seaImg;
    ofPixels col;
    ofxCvGrayscaleImage grayImage; // grayscale depth image
    ofxCvContourFinder contour;
    
    int nearThreshold;
    int farThreshold;
    
    vector<ofPolyline> line;
    vector<growIland> trees;
    vector<ofColor> ilandColors;
    
    bool drawVector;
    bool calibrate;
    bool thresh;
    ofColor seaColor;
    float weight;
    float diffx, diffy;
    float xAvarage;
    float yAvarage;
    float max, min;

};
