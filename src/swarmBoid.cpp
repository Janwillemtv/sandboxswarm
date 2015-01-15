//
//  swarmBoid.cpp
//  emptyExample
//
//  Created by Janwillem te Voortwis on 03/01/15.
//  Improved by Raoul Fasel
//
#include "ofMain.h"
#include "swarmBoid.h"
#include "global.h"

ofVec2f mouse;
swarmBoid::swarmBoid(){
  
}


//------------------------------------------------------------------
void swarmBoid::set(int modus, vector<ofVec4f> * map, ofxCvContourFinder * contour, vector<swarmBoid*>  swarm, int self){
    mode = modus;
    contourPointer = contour;
    mapPointer = map;
    swarmPointer = swarm;
    itSelf = self;
    if(mode==1){ // fish
        maxSpeed = 7;           //swarming weighfactors
        moveCenter = 0.01;
        neighborAtract = 0.001;
        neighborRepel = 0.15;
        matchVelocity = 0.125;
        objectRepel = 0.1;
        mapWeight = 1.7;
        average = 1;
        c.set(ofRandom(230.0,255.0),ofRandom(200.0,210.0),ofRandom(0.0,10.0));
        drawShip = false;
        //================================================
        pos.x = ofRandomWidth();// random position
        pos.y = ofRandomHeight();
    
        vel.x = ofRandom(-3.9, 3.9);//random velocity
        vel.y = ofRandom(-3.9, 3.9);
        scale = ofRandom(1.0, 1.5);//random scale
    }else if(mode == 2){ // people
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
        pos.x = ofRandomWidth();// random position
        pos.y = ofRandomHeight();
        
        vel.x = ofRandom(-3.9, 3.9);//random velocity
        vel.y = ofRandom(-3.9, 3.9);
        scale = ofRandom(2.0, 2.5);//random scale
    }

}

//====================================================================
void swarmBoid::update(vector<swarmBoid> b, int p){
    vectorPos = *mapPointer;
    center.set(0,0); // the vector towards the center of the swarm
    nRepel.set(0,0); // the vector to repel from nearby boids
    match.set(0,0); // the vector to match velocity of nearby boids
    nAtract.set(0,0); // the vector to attract to nearby boids
    oRepel.set(0,0); // the vector to repel from objects
    numberNeighbours = 0; // to keep track of the number of nearby boids

    for(unsigned int i = 0; i < b.size(); i++){ // check for every boid
        
            calcSwarm(i);//calculate the swarming vectors
        
    }
    center = center/(numberNeighbours);// calculate avarage
    center = (center - swarmPointer[itSelf]->pos);  // calculate vector
    match = match/(numberNeighbours); // calculate avarage
    
    getMapVector();
    
    if(numberNeighbours != 0) {
        vel+= (moveCenter * center) + (neighborRepel* nRepel) + (matchVelocity*match)+ (neighborAtract*nAtract)+ (objectRepel* oRepel);// add all the vectors with their weightfactors
    }
    else vel+= 0.1 * oRepel; // if a boid has no neighbor it vectors center,2,3,4 have no effect
    
    pos += vel; // update position
    
    calcColision();// calculate collision with ilands
    alterVector();// alter the vectors (maxSpeed&Worldcollision)
 
}

//====================================================================
void swarmBoid::draw(){
    
//    line.clear();
//    line.addVertex(pos.x,pos.y);
//    line.addVertex(pos.x+(20*vel.x),pos.y+(20*vel.y));
//    line.close();
//    line.draw();
   
    
            
    if(drawShip){// draw the boat
        drawBoat();

    }
    ofSetColor(c);
    if(mode==1) { // fish
        drawFish();
    }
    
    ofCircle(pos.x, pos.y, scale * 3.0); // draw boids
    
    
}

//====================================================================
float swarmBoid::distance(ofVec2f v1, ofVec2f v2){//calculates absolute distance between vectors
    
    return abs(v1.distance(v2));
    
}
//====================================================================
void swarmBoid::calcSwarm(int i){
   
    dist = distance(swarmPointer[i]->pos,swarmPointer[itSelf]->pos);// calculate distance from selected boid to checking boid
    
    if(dist<100){ // boids check in 100 units for other boids
        
        if(dist<30){ // if its too close the repel vector gets increased
            nRepel -= (swarmPointer[i]->pos - swarmPointer[itSelf]->pos);
        }else{ // if its too far away the attract vector gets increased
            nAtract += (swarmPointer[i]->pos - swarmPointer[itSelf]->pos);
        }
        
        center += swarmPointer[i]->pos; // movement towards center is the avarge position
        match += swarmPointer[i]->vel; // mathing velocity is the avarage velocity
        numberNeighbours++; // to calculate a avarage you need the number of entries
    }
    if(i==itSelf){
        
        if(distance(mouse,swarmPointer[itSelf]->pos)<50){ // if a object gets close the objectrepel vector gets increased
            oRepel += (swarmPointer[itSelf]->pos - mouse)*4;
        }
    
    }

}

//============================================================================
void swarmBoid::getMapVector(){
    int closestId = (round(swarmPointer[itSelf]->pos.x/(ofGetWidth()/column))-1)+((round(swarmPointer[itSelf]->pos.y/(ofGetHeight()/row))-1)*row);// the the id of the closest vector in vector map
    oRepel.x += (vectorPos[closestId].z)*mapWeight;// add the vectormap-vector
    oRepel.y += (vectorPos[closestId].w)*mapWeight;

}
//=============================================================================
void swarmBoid::calcColision(){
    
    float w = ((640.0)-(borderSide*1.5))/ofGetWidth();// used for to remove black bars in image
    float h = ((480.0)-borderTop)/ofGetHeight();
    
    for(int i = 0; i < contourPointer->nBlobs; i++) {// check for every blob found
        ofxCvBlob blob = contourPointer->blobs.at(i);

        ofPolyline line;
        
        line.addVertices(blob.pts);
        line.close();
        if(line.inside(floor((pos.x*w)+(0.5*borderSide)),(floor((pos.y*h))))){// if the boid is in the blob
            if(mode==1){
                float temp = vel.length();
                vel.set(blob.centroid.x - ((pos.x*w)+(0.5*borderSide)),blob.centroid.y - (pos.y*h));
                vel.normalize();// set maximal velocity away from blob
                vel *= -10;
                c.set(255,0,0);
            }
            if(mode == 2) drawShip = false;// if on land dont draw a ship
            break;
        }else{
            if(mode == 2) drawShip = true;// if on water draw ship
            if(mode==1)c.set(255,204,0);
        }
    }
}
//===============================================================================
void swarmBoid::alterVector(){

    if(vel.length() > maxSpeed){// if a boid exceeds maxspeed it is slowed down
        vel *= 0.8;
        if(vel.length() > maxSpeed) vel = vel.normalize()*maxSpeed;
    }
    
    if(vel.length()  < maxSpeed/10){// if a boid is slower than the minimum speed it gets sped up
        vel.set(1,1);
    }
    //-------------------------------------------
    if( pos.x >= ofGetWidth() ){ // if a boid hits a wall it bounces in the correct direction
        pos.x = ofGetWidth();
        vel.x *= -1.0;
    }else if( pos.x <= 0 ){
        pos.x = 0;
        vel.x *= -1.0;
    }
    if( pos.y >= ofGetHeight() ){
        pos.y = ofGetHeight();
        vel.y *= -1.0;
    }
    else if( pos.y <= 0 ){
        pos.y = 0;
        vel.y *= -1.0;
    }

}
//======================================
void swarmBoid::drawBoat(){
    ofVec2f temp = vel;
    ofVec2f temp2 = pos;
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

void swarmBoid::drawFish(){
    ofVec2f temp = vel;
    ofVec2f triBehind = pos - (10*temp.normalize());  //calculate behind of the tail
    ofVec2f triBehindLeft = triBehind - (8*temp.getRotated(90).normalize());  // calculate left and right respectively
    ofVec2f triBehindRight = triBehind + (8*temp.getRotated(90).normalize());
    ofTriangle(pos.x,pos.y,triBehindLeft.x,triBehindLeft.y,triBehindRight.x,triBehindRight.y);  // draw triangle on calculated vectors

}
//====================================================================
void swarmBoid::mouseUpdate(int x, int y){//update mouse position
    mouse.x = x;
    mouse.y = y;
}