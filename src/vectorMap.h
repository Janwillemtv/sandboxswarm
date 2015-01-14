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
    void set(int rows, int columns);
    void update();
    void draw();
    void close();
    void nearAlter(int i);
    void farAlter(int i);
    vector<ofVec4f> * vectorGrid();
    ofxCvContourFinder * contours();
    
    ofxKinect kinect;
    
    ofxCvColorImage colorImg;
    ofxCvGrayscaleImage grayImage; // grayscale depth image
    ofxCvContourFinder contour;
    
    int nearThreshold;
    int farThreshold;
    
    vector<ofPolyline> line;
    vector<growIland> trees;
    
    bool drawVector;
    bool calibrate;
    bool thresh;
    int row, column;
    float weight;
    float diffx, diffy;
    int times;
    float xAvarage;
    float yAvarage;
    float max, min;
//int borderTop;
  //  int borderSide;
};
