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
    drawVector = calibrate = thresh = false;
}
//-------------------------------------------------
void vectorMap::set(int rows, int columns){
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

        contour.findContours(grayImage, 200, 150000, 10, false);
        
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
    
    //============================================
   
   
        ofVec2f pos;
        pos.set((int)ofRandom(0.0,ofGetWidth()),(int)ofRandom(0.0,ofGetHeight()));

        if(contour.nBlobs == 0  && trees.size()>0){
            if(ofGetElapsedTimeMillis() - trees[0].erase) trees.clear();
        }
        for(int i = 0; i < contour.nBlobs; i++) {
            ofxCvBlob blob = contour.blobs.at(i);
            // do something fun with blob
            
            ofPolyline line;
            
            line.addVertices(blob.pts);
            line.close();
            if(line.inside(floor(((pos.x)*w)+(0.5*borderSide)),floor((pos.y*h)))){
               if(trees.size()<1000)  trees.push_back(growIland(pos));
                  
            }

            for (auto it = trees.begin(); it != trees.end();){
             
            
                if(line.inside(floor((it->pos.x*w)+(0.5*borderSide)),floor((it->pos.y*h)))){
                    it->setNull(ofGetElapsedTimeMillis());
    
                    it++;
                }else{
                    
                    if(ofGetElapsedTimeMillis() - it->erase>1000){
                    it = trees.erase(it);
                    }else it++;
                }
       
            }
            
        
    }
    
    //========================================================
    
    
    for(int j = 0; j<trees.size(); j++){
        trees[j].update();
    }

}
//-----------------------------------------------------------
void vectorMap::draw(){
    
    ofSetColor(28,91,160); //set blue for seacolor
   grayImage.drawROI(0, 0, ofGetWidth(), ofGetHeight());
    
    for(int j = 0; j<trees.size(); j++){ // draw the trees
        trees[j].draw();
    }
    if (calibrate) {
        ofSetColor(255);
        colorImg.drawROI(0,0,ofGetWidth(),ofGetHeight());
    }
    if(drawVector){
    ofSetColor(255, 0, 0);//set color for vectors
    for(unsigned int i = 0; i <vec.size(); i++){ //draw the vector map
        line[i].clear();
        line[i].addVertex(vec[i].x,vec[i].y);
        line[i].addVertex(vec[i].x+(5*vec[i].z),vec[i].y+(5*vec[i].w));
        line[i].close();
        line[i].draw();
        
    }
    }
    
    
    if(thresh){
        ofSetColor(255);
    stringstream reportStream;//calbration information
    reportStream
    << "set near threshold " << nearThreshold << " (press: + -)" << endl
    << "set far threshold " << farThreshold << " (press: < >)"<<endl
    <<    "num blobs found " << contour.nBlobs<<endl;
   ofDrawBitmapString(reportStream.str(), 20, 652);
    }
}


//-------------------------------------------------
vector <ofVec4f> * vectorMap::vectorGrid(){//return the pointers
    
    return  &vec;
}

ofxCvContourFinder * vectorMap::contours(){
    return &contour;
}

void vectorMap::nearAlter(int i){//calibrate the sensor
    nearThreshold+= i;
    if(nearThreshold >= 255) nearThreshold = 255;
    if(nearThreshold<= 0) nearThreshold = 0;
}

void vectorMap::farAlter(int i){//calibrate the sensor
    farThreshold+= i;
    if(farThreshold >= 255) farThreshold = 255;
    if(farThreshold<= 0) farThreshold = 0;
}

void vectorMap::close(){
    kinect.setCameraTiltAngle(0); // zero the tilt on exit
    kinect.close();
    
}

