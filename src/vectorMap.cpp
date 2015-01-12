//
//  vectorMap.cpp
//  emptyExample
//
//  Created by Janwillem te Voortwis on 06/01/15.
//
//
#include "ofMain.h"
#include "vectorMap.h"
#include "global.h"



vectorMap::vectorMap(){
    weight = 0.1;
    times = 5;
    max = 90;
    min = 7;
}
//-------------------------------------------------
void vectorMap::set(int rows, int columns){
    //ofSetLogLevel(OF_LOG_VERBOSE);
    nearThreshold = 250;
    farThreshold = 243;
    
    row = rows;
    column = columns;
    line.assign((row*column),ofPolyline());
    
    kinect.setRegistration(true);
    kinect.init();
    //kinect.init(false, false); // disable video image (faster fps)
    
    kinect.open();
    colorImg.allocate(kinect.width, kinect.height);
    grayImage.allocate(kinect.width, kinect.height);

    
    colorImg.setROI(borderSide/2, borderTop, colorImg.getWidth()-borderSide, colorImg.getHeight());
    grayImage.setROI(borderSide/2, borderTop, grayImage.getWidth()-borderSide, grayImage.getHeight());
    
    vec.assign((row*column),ofVec4f());
    
    int rowCount = 1;
    int columnCount = 1;
    for(unsigned int i = 0; i <vec.size(); i++){
        vec[i].x = (ofGetWidth()/columns)*columnCount;
        vec[i].y = (ofGetHeight()/rows)*rowCount;
        
        columnCount++;
        if(columnCount>columns){
            columnCount = 1;
            rowCount ++;
        }
    }

}
//-------------------------------------------------
void vectorMap::update(){
    kinect.update();
    if(kinect.isFrameNew()) {
        colorImg.setFromPixels(kinect.getPixels(), kinect.width, kinect.height);
        
        // load grayscale depth image from the kinect source
        grayImage.setFromPixels(kinect.getDepthPixels(), kinect.width, kinect.height);
        
        unsigned char * pix = grayImage.getPixels();
        
        int numPixels = grayImage.getWidth() * grayImage.getHeight();
        for(int i = 0; i < numPixels; i++) {
            if(pix[i] < nearThreshold && pix[i] > farThreshold) {
                pix[i] = 255;
            } else {
                pix[i] = 0;
            }
        }

        grayImage.flagImageChanged();
        
        contour.findContours(grayImage, 30, 150000, 10, false);
        
        for(int i = 0; i < numPixels; i++) {
            if(pix[i] ==255) {
                pix[i] = 0;
            } else {
                pix[i] = 255;
            }
        }
        
    }
    
    
    
        int rowCount = 1;
        int columnCount = 1;
        float w = ((640.0)-(borderSide*1.5))/ofGetWidth();
        float h = ((480.0)-borderTop)/ofGetHeight();
    
        for(unsigned int i = 0; i <vec.size(); i++){
            diffx = 0.0;
            diffy = 0.0;
         
            for( int j = 0; j<times; j++){
            if((columnCount+1)<column){
               
         diffx += kinect.getDistanceAt((int)((vec[i].x*w)+(0.5*borderSide)), (int)((vec[i].y*h)+borderTop))-kinect.getDistanceAt((int)((vec[i+1].x*w)+(0.5*borderSide)), (int)((vec[i+1].y*h)+borderTop));
            }
            if((1+rowCount)<=row){
        diffy += kinect.getDistanceAt((int)((vec[i].x*w)+(0.5*borderSide)), (int)(vec[i].y*h)+borderTop)-kinect.getDistanceAt((int)((vec[i+column].x*w)+(0.5*borderSide)), (int)(vec[i+column].y*h)+borderTop);
                
            }
            }
            
            diffx = diffx/times;
            diffy = diffy/times;
            
            if((diffx)>max||(diffx)< -max||(diffx>-min && diffx<min))diffx = 0;
            if((diffy)>max||(diffy)< -max||(diffy>-min && diffy<min))diffy = 0;
        
            vec[i].z = (diffx) * -weight;
            vec[i].w = (diffy) * -weight;
            columnCount++;
            if(columnCount>column){
                columnCount = 1;
                rowCount ++;
            }
            
        }

}

void vectorMap::draw(){
    ofSetColor(255);
   //colorImg.drawROI(0, 0, ofGetWidth(), ofGetHeight());
    ofSetColor(20,20,200);
   grayImage.drawROI(0, 0, ofGetWidth(), ofGetHeight());
    ofSetColor(255, 0, 0);
    for(unsigned int i = 0; i <vec.size(); i++){
        line[i].clear();
        line[i].addVertex(vec[i].x,vec[i].y);
        line[i].addVertex(vec[i].x+(5*vec[i].z),vec[i].y+(5*vec[i].w));
        line[i].close();
        line[i].draw();
        
    }
    
    
    stringstream reportStream;
    reportStream
    << "set near threshold " << nearThreshold << " (press: + -)" << endl
    << "set far threshold " << farThreshold << " (press: < >) num blobs found " << contour.nBlobs<<endl
    << "press c to close the connection and o to open it again, connection is: " << kinect.isConnected() << endl;
   ofDrawBitmapString(reportStream.str(), 20, 652);
}

//-------------------------------------------------
vector <ofVec4f> * vectorMap::vectorGrid(){
    
    return  &vec;
}

ofxCvContourFinder * vectorMap::contours(){
    return &contour;
}

void vectorMap::nearAlter(int i){
    nearThreshold+= i;
    if(nearThreshold >= 255) nearThreshold = 255;
    if(nearThreshold<= 0) nearThreshold = 0;
}

void vectorMap::farAlter(int i){
    farThreshold+= i;
    if(farThreshold >= 255) farThreshold = 255;
    if(farThreshold<= 0) farThreshold = 0;
}

void vectorMap::close(){
    kinect.setCameraTiltAngle(0); // zero the tilt on exit
    kinect.close();
    
}

