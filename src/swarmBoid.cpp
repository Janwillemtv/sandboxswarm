//
//  swarmBoid.cpp
//  emptyExample
//
//  Created by Janwillem te Voortwis on 03/01/15.
//
//
#include "ofMain.h"
#include "swarmBoid.h"
#include "global.h"

ofVec2f mouse;
swarmBoid::swarmBoid(){
  
}


//------------------------------------------------------------------
void swarmBoid::set(int modus, vector<ofVec4f> * map, ofxCvContourFinder * contour){
    mode = modus;
    contourPointer = contour;
    mapPointer = map;
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
        mapWeight = -1;
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

//------------------------------------------------------------------
void swarmBoid::update(vector<swarmBoid> b, int p){
    vectorPos = *mapPointer;
    v1.set(0,0); // the vector towards the center of the swarm
    v2.set(0,0); // the vector to repel from nearby boids
    v3.set(0,0); // the vector to match velocity of nearby boids
    v4.set(0,0); // the vector to attract to nearby boids
    v5.set(0,0); // the vector to repel from objects
    numberNeighbours = 0; // to keep track of the number of nearby boids

    for(unsigned int i = 0; i < b.size(); i++){ // check for every boid
        
        if(i !=p) { // exclude the boid that is currently updating
           
            dist = distance(b[i].pos,b[p].pos);// calculate distance from selected boid to checking boid
            
            if(dist<100){ // boids check in 100 units for other boids
                
                if(dist<30){ // if its too close the repel vector gets increased
                    v2 -= (b[i].pos - b[p].pos);
                }else{ // if its too far away the attract vector gets increased
                    v4 += (b[i].pos - b[p].pos);
                }
               
                v1 += b[i].pos; // movement towards center is the avarge position
                v3 += b[i].vel; // mathing velocity is the avarage velocity
                numberNeighbours++; // to calculate a avarage you need the number of entries
            }
            
        }else{
            int closestId = (round(b[p].pos.x/(ofGetWidth()/20))-1)+((round(b[p].pos.y/(ofGetHeight()/15))-1)*20);// the the id of the closest vector in vector map
            ofVec2f temp;

                    v5.x += (vectorPos[closestId].z)*mapWeight;// add the vectormap-vector
                    v5.y += (vectorPos[closestId].w)*mapWeight;
         
            
            if(distance(mouse,b[p].pos)<50){ // if a object gets close the objectrepel vector gets increased
                    v5 += (b[p].pos - mouse)*10;
            }
        
        }
        
            
        
    }

    v1 = v1/(numberNeighbours);// calculate avarage
    v1 = (v1 - b[p].pos);  // calculate vector
    v3 = v3/(numberNeighbours); // calculate avarage
    
    if(numberNeighbours != 0) {
        vel+= (moveCenter * v1) + (neighborRepel* v2) + (matchVelocity*v3)+ (neighborAtract*v4)+ (objectRepel* v5);// add all the vectors with their weightfactors
    }
    else vel+= 0.1 * v5; // if a boid has no neighbor it vectors v1,2,3,4 have no effect
    
    
    if(vel.length() > maxSpeed){// if a boid exceeds maxspeed it is slowed down
        vel *= 0.8;
        if(vel.length() > maxSpeed) vel = vel.normalize()*maxSpeed;
    }
    
    if(vel.length()  < maxSpeed/10){// if a boid is slower than the minimum speed it gets sped up
        vel.set(1,1);
    }
    
    pos += vel; // update position
    //----------------------------------------//blob-colision
    
   
    float w = ((640.0)-(borderSide*1.5))/ofGetWidth();// used for to remove black bars in image
    float h = ((480.0)-borderTop)/ofGetHeight();
    
    for(int i = 0; i < contourPointer->nBlobs; i++) {// check for every blob found
        ofxCvBlob blob = contourPointer->blobs.at(i);
        // do something fun with blob
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

//------------------------------------------------------------------
void swarmBoid::draw(){
    
//    line.clear();
//    line.addVertex(pos.x,pos.y);
//    line.addVertex(pos.x+(20*vel.x),pos.y+(20*vel.y));
//    line.close();
//    line.draw();
   
       ofVec2f temp = vel;
            
    if(drawShip){// draw the boat
    ofSetColor(74, 62, 14);
        
        ofDrawArrow(pos-(10*temp.normalize()), pos+(20*temp.normalize()),10);
        ofDrawArrow(pos+(10*temp.normalize()), pos-(20*temp.normalize()),10);
    }
    if(mode==1) { // fish
        ofDrawArrow(pos-(20*temp.normalize()), pos,10);
    }
    
    ofSetColor(c);
    ofCircle(pos.x, pos.y, scale * 3.0); // draw boids
    
    
}

//------------------------------------------------------------------
float swarmBoid::distance(ofVec2f v1, ofVec2f v2){//calculates absolute distance between vectors
    
    return abs(v1.distance(v2));
    
}

void swarmBoid::mouseUpdate(int x, int y){//update mouse position
    mouse.x = x;
    mouse.y = y;
}