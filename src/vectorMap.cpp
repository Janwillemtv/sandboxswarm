//
//  vectorMap.cpp
//  emptyExample
//
//  Created by Janwillem te Voortwis on 06/01/15.
//  Improved by Raoul Fasel
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
    color.assign((row+1)*(column+1),ofFloatColor());
    
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    mesh.enableColors();
    
}
//-------------------------------------------------
void vectorMap::set(){
    nearThreshold = 250;//initail values
    farThreshold = 243;
    
    line.assign(((row+1)*(column+1)),ofPolyline());
    //init kinect
    kinect.setRegistration(true);
    kinect.init();
    
    kinect.open();
    // reserve space for the images
    colorImg.allocate(kinect.width, kinect.height); //image for camera
//    grayImage.allocate(kinect.width, kinect.height);// image for grayscale heightmap
//    seaImg.allocate(kinect.width, kinect.height,OF_IMAGE_COLOR);
//    col.allocate(kinect.width, kinect.height,OF_PIXELS_RGB);
    
    colorImg.setROI(borderSide/2, borderTop, colorImg.getWidth()-borderSide, colorImg.getHeight());
//    grayImage.setROI(borderSide/2, borderTop, grayImage.getWidth()-borderSide, grayImage.getHeight());// we use ROI because bad kinect
    
    vec.assign((row*column+column+row),ofVec4f());//empty array of 4d vectors for the height difference vectors
    color.assign((row*column),ofColor());
    reposition();

}
//-------------------------------------------------
void vectorMap::update(){
    if(ofGetElapsedTimeMillis()%500<=20){
    getKinectImage();
    calcVectors();
       
       }
    if(ofGetElapsedTimeMillis()%20<=5){
         makeTrees();
    }
    
    for(int j = 0; j<trees.size(); j++){//update trees
        trees[j].update();
    }
    
}
//-----------------------------------------------------------
void vectorMap::draw(){
    float w = ((640.0)-(borderSide*1.5));
    float h = ((480.0)-borderTop);
    ofSetColor(255); //set values back to white
    //seaImg.drawSubsection(0,0, ofGetWidth(),ofGetHeight(), borderSide/2, borderTop,w,h);//draw sea
    mesh.draw();
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
    //set color for vectors
    for(int i = 0; i <vec.size(); i++){ //draw the vector map
        //ofSetColor(color[i]);
        line[i].clear();
        line[i].addVertex(vec[i].x,vec[i].y);
        ofSetColor(255);
        line[i].addVertex(vec[i].x-10,vec[i].y-10);
        //line[i].addVertex(vec[i].x+(5*vec[i].z),vec[i].y+(5*vec[i].w));
        line[i].close();
        line[i].draw();
    
        
    }
    }
    //---------------------------------------------------------
    if(thresh){
        ofSetColor(255);// alter threshold variable via keyboard
    stringstream reportStream;//calbration information
    reportStream
    << "set near threshold " << nearThreshold << " (press: + -)" << endl// for objects close to kinect
    << "set far threshold " << farThreshold << " (press: < >)"<<endl// for objects closte table
    <<    "num blobs found " << contour.nBlobs<<endl;
   ofDrawBitmapString(reportStream.str(), 20, 652);
    }
}

//================================================
void vectorMap::reposition(){
    int rowCount = 0;
    int columnCount = 0;
    for(int i = 0; i <vec.size(); i++){// set the positions of the vectors
        vec[i].x = (ofGetWidth()/column)*columnCount;
        vec[i].y = (ofGetHeight()/row)*rowCount;
        columnCount++;
        if(columnCount>column){
            columnCount = 0;
            rowCount ++;
        }
    }

}
//=================================================
void vectorMap::getKinectImage(){

    if(kinect.isConnected()){//get kinectdata if connected
        kinect.update();
        if(kinect.isFrameNew()) {
            //colorImg.setFromPixels(kinect.getPixels(),kinect.width,kinect.height);
            colorImg.setFromPixels(kinect.getPixels());
            // load grayscale depth image from the kinect source
            //grayImage.setFromPixels(kinect.getDepthPixels(), kinect.width, kinect.height);
            
//            unsigned char * pix = grayImage.getPixels();
//            
//            int numPixels = grayImage.getWidth() * grayImage.getHeight();// threshold the image from grayscale height data
//            for(int i = 0; i < numPixels; i++) {
//                if(pix[i] < nearThreshold && pix[i] > farThreshold) {
//                    pix[i] = 255;
//                } else {
//                    pix[i] = 0;
//                }
//            }
            
       //     grayImage.flagImageChanged();//say that the image is changed
            
      //      contour.findContours(grayImage, 200, 150000, 10, false);// find the contours in the image
           
//            
//            for(int i = 0; i < numPixels; i++) {//set the sea and island colors
//                if(pix[i] ==255) {
//                    col.setColor(i*3, ofColor(255));
//                } else {
//                    col.setColor(i*3,seaColor);
//                }
//                
//            }
//            seaImg = col;// convert to an ofimage so that it can be drawn
//            
        }
    }

}
//========================================
void vectorMap::calcVectors(){
    mesh.clear();
    mesh.enableIndices();
    int rowCount = 0;
    int columnCount = 0;
    float w = ((640.0)-(borderSide*1.5))/ofGetWidth();//translation factors for kinect
    float h = ((480.0)-borderTop)/ofGetHeight();
    
    for(int i = 0; i <vec.size(); i++){//calculate the vectors
        diffx = 0.0;
        diffy = 0.0;

        
//            if((columnCount+1)<column){// calculate height difference in x direction
//                        
//                diffx += kinect.getDistanceAt((int)((vec[i].x*w)+(0.5*borderSide)), (int)((vec[i].y*h)+borderTop))-kinect.getDistanceAt((int)((vec[i+1].x*w)+(0.5*borderSide)), (int)((vec[i+1].y*h)+borderTop));
//            }
//            if((1+rowCount)<=row){// calculate height difference in y direction
//                diffy += kinect.getDistanceAt((int)((vec[i].x*w)+(0.5*borderSide)), (int)(vec[i].y*h)+borderTop)-kinect.getDistanceAt((int)((vec[i+column].x*w)+(0.5*borderSide)), (int)(vec[i+column].y*h)+borderTop);
//                
//            }
//        
//        //if a maximum or minimum is exceeded the vector is set to zero
//        if((diffx)>max||(diffx)< -max||(diffx>-min && diffx<min))diffx = 0;
//        if((diffy)>max||(diffy)< -max||(diffy>-min && diffy<min))diffy = 0;
        
        //vec[i].z = (diffx) * -weight;// set the vectors
      //  vec[i].w = (diffy) * -weight;
        
        mesh.addVertex(ofVec3f(vec[i].x,vec[i].y,0));
        int dist = kinect.getDistanceAt((int)((vec[i].x*w)+(0.5*borderSide)), (int)((vec[i].y*h)+borderTop));
       // cout<<dist<<"    "<<i<<endl;
        vec[i].z = (float)dist;
        ofColor c;
        if(dist<1100){
            c.r = 1100-dist+130;
            c.g = 1100-dist+130;
            c.b = 0;
          //  cout<<i<<endl;
        }else{
            c.b = 1150-dist+150;
            c.r = 1150-dist+100;
            c.g = 1150-dist+100;
        }
        mesh.addColor(c);
        
        
        columnCount++;
        
        if(rowCount!=0&&columnCount>1){
   
            mesh.addTriangle(i-(column+2), i-1, i);
            mesh.addTriangle(i-(column+2), i-(column+1), i);
        }

        if(columnCount>column){
            columnCount = 0;
          
            rowCount ++;
            
//
        }
//
        
        
    }


}
//=================================================
void vectorMap::makeTrees(){

    float w = ((640.0)-(borderSide*1.5))/ofGetWidth();//translation factors
    float h = ((480.0)-borderTop)/ofGetHeight();
    color = mesh.getColors();
    
    ofVec2f pos;
    pos.set((int)ofRandom(0.0,ofGetWidth()),(int)ofRandom(0.0,ofGetHeight()));// choose a random position
    
//    if(contour.nBlobs == 0  && trees.size()>0){// check if this position is inside a blob
//        if(ofGetElapsedTimeMillis() - trees[0].erase) trees.clear();
//    }
    
    int closestId = (round((pos.x)/(ofGetWidth()/column)))+((round((pos.y)/(ofGetHeight()/row)))*(column+1));
    ofFloatColor c = color[closestId];
    
    if(c.r*255>170&&c.b==0){
            if(trees.size()<50)  trees.push_back(growIland(pos));// add a tree
        cout<<"test"<<endl;
    }
    
    
    for (auto it = trees.begin(); it != trees.end();){// check if the trees are still in a blob
        
        int closestId = (round((it->pos.x)/(ofGetWidth()/column)))+((round((it->pos.y)/(ofGetHeight()/row)))*(column+1));
        ofFloatColor c = mesh.getColor(closestId);
        if(c.r*255>170&&c.b==0){
            it->setNull(ofGetElapsedTimeMillis());// ifso set a timer
            
            it++;
        }else{
            
            if(ofGetElapsedTimeMillis() - it->erase>50){//if not
                it = trees.erase(it);// if the timer exceeds one second the tree is removed
            }else it++;
        }
        
    }

}
//=================================================
void vectorMap::infect(ofVec2f position, int influence){
    for(int i = 0; i < trees.size(); i++){
        float dist = abs(position.distance(trees[i].pos));
        if(dist<=100){
            trees[i].influence += influence;
        }
    }
}
//=================================================
void vectorMap::close(){
    kinect.setCameraTiltAngle(0); // zero the tilt on exit
    kinect.close();
    
}

ofMesh * vectorMap::getMesh(){
    return &mesh;
}

