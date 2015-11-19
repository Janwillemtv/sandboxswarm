//
//  swarmBoid.cpp
//  emptyExample
//
//  Created by Janwillem te Voortwis on 03/01/15.
//  Improved by Raoul Fasel
//
#include "swarmBoid.h"
#include "global.h"
#include <math.h>


ofVec2f mouse;
swarmBoid::swarmBoid(){
    pos.x = ofRandomWidth();// random position
    pos.y = ofRandomHeight();
    vel.x = ofRandom(-3.9, 3.9);//random velocity
    vel.y = ofRandom(-3.9, 3.9);
    maxSpeed = 3;
}


//------------------------------------------------------------------
void swarmBoid::set(vectorMap * map, vector<swarmBoid*>  swarm, int self){
    mapPointer = map;
    swarmPointer = swarm;
    itSelf = self;
    oldmillis = ofGetElapsedTimeMillis();
}
//===================================================================
fish::fish() : swarmBoid(){
    boat.loadImage("fish.png");
    shadow.loadImage("fishshadow.png");
    moveCenter = 0.00000;//swarming weighfactors
    neighborAtract = 0.0001;
    neighborRepel = 0.007;
    matchVelocity = 0.04;
    objectRepel = 0.01;
    mapWeight = 1.7;
    average = 1;
    c.set(ofRandom(230.0,255.0),ofRandom(200.0,210.0),ofRandom(100.0,130.0));
    drawShip = false;
    scale = ofRandom(1.0, 1.5);//random scale
    
}
//===================================================================
people::people() : swarmBoid(){
    boat.loadImage("boat.png");
    shadow.loadImage("boatshadow.png");
    offset = ofRandom(0.0,1000.0);
    
    moveCenter = 0.00000;
    neighborAtract = 0.0000;
    neighborRepel = 0.0005;
    matchVelocity = 0.00;
    objectRepel = 0.01;
    mapWeight = -2;
    average = 1;
    c.set(ofRandom(135.0,145.0),ofRandom(35.0,46.0),ofRandom(70.0,75.0));
    drawShip = true;
    scale = ofRandom(2.0, 2.5);//random scale
}

//====================================================================
void fish::update(){
    //vectorPos = *mapPointer;
    
    center.set(0,0); // the vector towards the center of the swarm
    nRepel.set(0,0); // the vector to repel from nearby boids
    match.set(0,0); // the vector to match velocity of nearby boids
    nAtract.set(0,0); // the vector to attract to nearby boids
    oRepel.set(0,0); // the vector to repel from objects
    numberNeighbours = 0; // to keep track of the number of nearby boids

    for(unsigned int i = 0; i < swarmPointer.size(); i++){ // check for every boid
        
            calcSwarm(i,20);//calculate the swarming vectors
        
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
    
    //calcColision();// calculate collision with ilands
    alterVector();// alter the vectors (maxSpeed&Worldcollision)
 
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void people::update(){
    nRepel.set(0,0); // the vector to repel from nearby boids
    oRepel.set(0,0); // the vector to repel from objects
    
    for(unsigned int i = 0; i < swarmPointer.size(); i++){ // check for every boid
        
        calcSwarm(i,70);//calculate the swarming vectors
        
    }
    
    getMapVector();
    
    if(numberNeighbours != 0) {
        vel+= (neighborRepel* nRepel) + (objectRepel* oRepel);// add all the vectors with their weightfactors
    }
    else vel+= 0.1 * oRepel; // if a boid has no neighbor it vectors center,2,3,4 have no effect
    
    //calcColision();// calculate collision with ilands
    alterVector();
    vel.normalize();
    vel *= (sin((ofGetElapsedTimef()*3)+offset)+1.5);
    pos += vel; // update position
    
    // alter the vectors (maxSpeed&Worldcollision)
    
    
    if(!ripples.empty()){
        
        for(int j = 0; j<ripples.size(); j++){//update trees
            ripples[j].update();
        }
        
        
        
        for (auto it = ripples.begin(); it != ripples.end();){// check if the trees are still in a blob
            
            
            if(!it->returnSize()){
                it++;
            }else{
                it = ripples.erase(it);// if the timer exceeds one second the tree is removed
            }
            
        }
    }
    
    
   

}
//====================================================================

void fish::draw(){
    double angle = atan2(vel.y,vel.x);
    
    glPushMatrix();
    ofTranslate(pos.x,pos.y);
    ofRotate(((angle/(2*PI))*360)+90);
    ofSetColor(255);
    ofEnableAlphaBlending();
    boat.draw(-15,-15,30,30);
    ofDisableAlphaBlending();
    glPopMatrix();
}

void people::draw(){
    if(drawShip){
        
        for(int j = 0; j<ripples.size(); j++){//update trees
            ripples[j].draw();
        }
        

        double angle = atan2(vel.y,vel.x);
        
        glPushMatrix();
        ofTranslate(pos.x,pos.y);
        ofRotate(((angle/(2*PI))*360)+180);
        ofSetColor(255);
        cout << angle << endl;
        ripples.push_back(ripple(ofVec2f(pos.x+(-10*cos(angle+ofDegToRad(90))),pos.y+(-10*sin(angle+ofDegToRad(90))))));// add a ripple
        ripples.push_back(ripple(ofVec2f(pos.x+(10*cos(angle+ofDegToRad(90))),pos.y+(10*sin(angle+ofDegToRad(90))))));// add a ripple
        ofEnableAlphaBlending();
        boat.draw(-30,-15,60,30);
        ofDisableAlphaBlending();
        
        
        glPushMatrix();
        ofTranslate(0,10);
        float angleTemp = 30*sin((ofGetElapsedTimef()*3)+offset+185);
        ofRotate(angleTemp);
       
   

        ofSetColor(148,102,1);
        ofSetLineWidth(3);
        ofLine(0,0,0,30);
        glPopMatrix();
        
        glPushMatrix();
        ofTranslate(0,-10);
        ofRotate(30*sin((ofGetElapsedTimef()*3)+offset));
        ofLine(0,0,0,-30);
        glPopMatrix();
        
        glPopMatrix();

    }
    ofSetColor(c);
    ofCircle(pos.x, pos.y, scale * 3.0); // draw boids
}

void fish::drawShadow(){
    double angle = atan2(vel.y,vel.x);
    
    glPushMatrix();
    ofTranslate(pos.x+5,pos.y+5);
    ofRotate(((angle/(2*PI))*360)+90);
    ofSetColor(255);
    ofEnableAlphaBlending();
    shadow.draw(-30,-15,60,30);
    ofDisableAlphaBlending();
    glPopMatrix();

}

void people::drawShadow(){
    double angle = atan2(vel.y,vel.x);
    
    glPushMatrix();
    ofTranslate(pos.x+15,pos.y+15);
    ofRotate(((angle/(2*PI))*360)+180);
    ofSetColor(255);
    ofEnableAlphaBlending();
    shadow.draw(-30,-15,60,30);
    ofDisableAlphaBlending();
    glPopMatrix();

    
}

//====================================================================
float swarmBoid::distance(ofVec2f v1, ofVec2f v2){//calculates absolute distance between vectors
    
    return abs(v1.distance(v2));
    
}
//====================================================================
void swarmBoid::calcSwarm(int i, int repelDist){
   
    dist = distance(swarmPointer[i]->pos,swarmPointer[itSelf]->pos);// calculate distance from selected boid to checking boid
    
    if(dist<100){ // boids check in 100 units for other boids
        
        if(dist<repelDist){ // if its too close the repel vector gets increased
            nRepel -= (swarmPointer[i]->pos - swarmPointer[itSelf]->pos)*0.35*(repelDist-dist);
        }else{ // if its too far away the attract vector gets increased
            nAtract += (swarmPointer[i]->pos - swarmPointer[itSelf]->pos)*0.004*dist;
        }
        
        center += swarmPointer[i]->pos; // movement towards center is the avarge position
        match += swarmPointer[i]->vel; // mathing velocity is the avarage velocity
        numberNeighbours++; // to calculate a avarage you need the number of entries
    }
    if(i==itSelf){
        
        if(distance(mouse,swarmPointer[itSelf]->pos)<50){ // if a object gets close the objectrepel vector gets increased
            oRepel += (swarmPointer[itSelf]->pos - mouse)*4;
        }
        ofVec2f left = *new ofVec2f(0,swarmPointer[itSelf]->pos.y);
        ofVec2f right = *new ofVec2f(ofGetWidth(),swarmPointer[itSelf]->pos.y);
        ofVec2f up = *new ofVec2f(swarmPointer[itSelf]->pos.x,0);
        ofVec2f down = *new ofVec2f(swarmPointer[itSelf]->pos.x,ofGetHeight());
        if(swarmPointer[itSelf]->pos.x<100){
            oRepel += (swarmPointer[itSelf]->pos-left)*0.01*(100-swarmPointer[itSelf]->pos.x);
        }
        if(swarmPointer[itSelf]->pos.x>ofGetWidth()-100){
            oRepel += (swarmPointer[itSelf]->pos-right)*0.01*(swarmPointer[itSelf]->pos.x-(ofGetWidth()-100));
        }
        if(swarmPointer[itSelf]->pos.y<100){
            oRepel += (swarmPointer[itSelf]->pos-up)*0.01*(100-swarmPointer[itSelf]->pos.y);
        }
        if(swarmPointer[itSelf]->pos.y>ofGetHeight()-100){
            oRepel += (swarmPointer[itSelf]->pos-down)*0.01*(swarmPointer[itSelf]->pos.y-(ofGetHeight()-100));
        }
    
    }

}

//============================================================================
void swarmBoid::getMapVector(){
    int closestId = (round(swarmPointer[itSelf]->pos.x/(ofGetWidth()/column))-1)+((round(swarmPointer[itSelf]->pos.y/(ofGetHeight()/row))-1)*row);// the the id of the closest vector in vector map
    oRepel.x += (mapPointer->vec[closestId].z)*mapWeight;// add the vectormap-vector
    oRepel.y += (mapPointer->vec[closestId].w)*mapWeight;

}
//=============================================================================
void fish::calcColision(){
    
    float w = ((640.0)-(borderSide*1.5))/ofGetWidth();// used for to remove black bars in image
    float h = ((480.0)-borderTop)/ofGetHeight();
    
    for(int i = 0; i < mapPointer->contour.nBlobs; i++) {// check for every blob found
        ofxCvBlob blob = mapPointer->contour.blobs.at(i);

        ofPolyline line;
        
        line.addVertices(blob.pts);
        line.close();
        if(line.inside(floor(((pos.x+2*vel.x)*w)+(0.5*borderSide)),(floor(((pos.y+2*vel.y)*h))))){// if the boid is in the blob
                mapPointer->infect(pos, -5);
                float temp = vel.length();
                vel.set(blob.centroid.x - ((pos.x*w)+(0.5*borderSide)),blob.centroid.y - (pos.y*h));
                vel.normalize();// set maximal velocity away from blob
                vel *= -10;
                c.set(255,0,0);
            
            break;
        }else{
            c.set(255,204,0);
        }
    }
}
//=============================================================================
void people::calcColision(){
    
    float w = ((640.0)-(borderSide*1.5))/ofGetWidth();// used for to remove black bars in image
    float h = ((480.0)-borderTop)/ofGetHeight();
    
    for(int i = 0; i < mapPointer->contour.nBlobs; i++) {// check for every blob found
        ofxCvBlob blob = mapPointer->contour.blobs.at(i);
        
        ofPolyline line;
        
        line.addVertices(blob.pts);
        line.close();
        if(line.inside(floor((pos.x*w)+(0.5*borderSide)),(floor((pos.y*h))))){// if the boid is in the blob
                drawShip = false;// if on land dont draw a ship
                if(ofGetElapsedTimeMillis()%10<2)    mapPointer->infect(pos, 3);
            
            break;
        }else{
            drawShip = true;// if on water draw ship
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
        vel.normalize();
        vel *=10;
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
//====================================================================
void swarmBoid::mouseUpdate(int x, int y){//update mouse position
    mouse.x = x;
    mouse.y = y;
}