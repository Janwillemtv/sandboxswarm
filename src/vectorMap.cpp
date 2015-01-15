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
    weight = 0.1;//vector map values
    max = 90;
    min = 7;
    drawVector = calibrate = thresh = false;
    seaColor =  ofColor(28,91,160);
}
//-------------------------------------------------
void vectorMap::set(){
    nearThreshold = 250;//initail values
    farThreshold = 243;
    
    line.assign((row*column),ofPolyline());
    
    kinect.setRegistration(true);
    kinect.init();
    
    kinect.open();
    colorImg.allocate(kinect.width, kinect.height);// reserve space for the images
    grayImage.allocate(kinect.width, kinect.height);
    seaImg.allocate(kinect.width, kinect.height,OF_IMAGE_COLOR);
    col.allocate(kinect.width, kinect.height,OF_PIXELS_RGB);
    
    colorImg.setROI(borderSide/2, borderTop, colorImg.getWidth()-borderSide, colorImg.getHeight());
    grayImage.setROI(borderSide/2, borderTop, grayImage.getWidth()-borderSide, grayImage.getHeight());// we use ROI because bad kinect
    
    vec.assign((row*column),ofVec4f());
    reposition();

}
//-------------------------------------------------
void vectorMap::update(){
    
    getKinectImage();
    calcVectors();
    makeTrees();
    
    for(int j = 0; j<trees.size(); j++){//update trees
        trees[j].update();
    }
    
}
//-----------------------------------------------------------
void vectorMap::draw(){
    float w = ((640.0)-(borderSide*1.5));
    float h = ((480.0)-borderTop);
    ofSetColor(255); //set values back to white
    seaImg.drawSubsection(0,0, ofGetWidth(),ofGetHeight(), borderSide/2, borderTop,w,h);//draw sea
    for(int j = 0; j<trees.size(); j++){ // draw the trees
        trees[j].draw();
    }
     //---------------------------------------------------------
    if (calibrate) {
        ofSetColor(255);
        colorImg.drawROI(0,0,ofGetWidth(),ofGetHeight());
    }
    //---------------------------------------------------------
    if(drawVector){
    ofSetColor(255, 0, 0);//set color for vectors
    for(int i = 0; i <vec.size(); i++){ //draw the vector map
        line[i].clear();
        line[i].addVertex(vec[i].x,vec[i].y);
        line[i].addVertex(vec[i].x+(5*vec[i].z),vec[i].y+(5*vec[i].w));
        line[i].close();
        line[i].draw();
        
    }
    }
    //---------------------------------------------------------
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


//================================================
vector <ofVec4f> * vectorMap::vectorGrid(){//return the pointers
    return  &vec;
}
//================================================
ofxCvContourFinder * vectorMap::contours(){
    return &contour;
}

//================================================
void vectorMap::reposition(){
    int rowCount = 1;
    int columnCount = 1;
    for(int i = 0; i <vec.size(); i++){// set the positions of the vectors
        vec[i].x = (ofGetWidth()/column)*columnCount;
        vec[i].y = (ofGetHeight()/row)*rowCount;
        
        columnCount++;
        if(columnCount>column){
            columnCount = 1;
            rowCount ++;
        }
    }

}
//=================================================
void vectorMap::getKinectImage(){

    if(kinect.isConnected()){//get kinectdata if connected
        kinect.update();
        if(kinect.isFrameNew()) {
            colorImg.setFromPixels(kinect.getPixels(), kinect.width, kinect.height);
            
            // load grayscale depth image from the kinect source
            grayImage.setFromPixels(kinect.getDepthPixels(), kinect.width, kinect.height);
            
            unsigned char * pix = grayImage.getPixels();
            
            int numPixels = grayImage.getWidth() * grayImage.getHeight();// threshold the image
            for(int i = 0; i < numPixels; i++) {
                if(pix[i] < nearThreshold && pix[i] > farThreshold) {
                    pix[i] = 255;
                } else {
                    pix[i] = 0;
                }
            }
            
            
            grayImage.flagImageChanged();//say that the image is changed
            
            contour.findContours(grayImage, 200, 150000, 10, false);// find the contours in the image
           
            
            for(int i = 0; i < numPixels; i++) {//set the sea and iland colors
                if(pix[i] ==255) {
                    col.setColor(i*3, ofColor(255));
                } else {
                    col.setColor(i*3,seaColor);
                }
                
            }
            seaImg = col;// convert to an ofimage so that it can be drawn
            
        }
    }

}
//========================================
void vectorMap::calcVectors(){

    int rowCount = 1;
    int columnCount = 1;
    float w = ((640.0)-(borderSide*1.5))/ofGetWidth();//translation factors
    float h = ((480.0)-borderTop)/ofGetHeight();
    
    for(int i = 0; i <vec.size(); i++){//calculate the vectors
        diffx = 0.0;
        diffy = 0.0;
        
        
            if((columnCount+1)<column){// calculate height difference in x direction
                
                diffx += kinect.getDistanceAt((int)((vec[i].x*w)+(0.5*borderSide)), (int)((vec[i].y*h)+borderTop))-kinect.getDistanceAt((int)((vec[i+1].x*w)+(0.5*borderSide)), (int)((vec[i+1].y*h)+borderTop));
            }
            if((1+rowCount)<=row){// calculate height difference in y direction
                diffy += kinect.getDistanceAt((int)((vec[i].x*w)+(0.5*borderSide)), (int)(vec[i].y*h)+borderTop)-kinect.getDistanceAt((int)((vec[i+column].x*w)+(0.5*borderSide)), (int)(vec[i+column].y*h)+borderTop);
                
            }
        
        //if a maximum or minimum is exceeded the vector is set to zero
        if((diffx)>max||(diffx)< -max||(diffx>-min && diffx<min))diffx = 0;
        if((diffy)>max||(diffy)< -max||(diffy>-min && diffy<min))diffy = 0;
        
        vec[i].z = (diffx) * -weight;// set the vectors
        vec[i].w = (diffy) * -weight;
        columnCount++;
        if(columnCount>column){
            columnCount = 1;
            rowCount ++;
        }
        
    }


}
//=================================================
void vectorMap::makeTrees(){

    float w = ((640.0)-(borderSide*1.5))/ofGetWidth();//translation factors
    float h = ((480.0)-borderTop)/ofGetHeight();
    
    
    ofVec2f pos;
    pos.set((int)ofRandom(0.0,ofGetWidth()),(int)ofRandom(0.0,ofGetHeight()));// choose a random position
    
    if(contour.nBlobs == 0  && trees.size()>0){// check if this position is inside a blob
        if(ofGetElapsedTimeMillis() - trees[0].erase) trees.clear();
    }
    for(int i = 0; i < contour.nBlobs; i++) {
        ofxCvBlob blob = contour.blobs.at(i);
       
        // do something fun with blob
        
        ofPolyline line;
        
        line.addVertices(blob.pts);
        line.close();
        if(line.inside(floor(((pos.x)*w)+(0.5*borderSide)),floor((pos.y*h)))){// ifso
            if(trees.size()<1000)  trees.push_back(growIland(pos));// add a tree
            
        }
        
        for (auto it = trees.begin(); it != trees.end();){// check if the trees are still in a blob
            
            
            if(line.inside(floor((it->pos.x*w)+(0.5*borderSide)),floor((it->pos.y*h)))){
                it->setNull(ofGetElapsedTimeMillis());// ifso set a timer
                
                it++;
            }else{
                
                if(ofGetElapsedTimeMillis() - it->erase>1000){//if not
                    it = trees.erase(it);// if the timer exceeds one second the tree is removed
                }else it++;
            }
            
        }
        
        
    }

}
//=================================================
void vectorMap::close(){
    kinect.setCameraTiltAngle(0); // zero the tilt on exit
    kinect.close();
    
}

