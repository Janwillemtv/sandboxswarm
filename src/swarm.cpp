//
//  swarm.cpp
//  sandboxSwarm
//
//  Created by Janwillem te Voortwis on 07/01/15.
//  Improved by Raoul Fasel
//
#include "ofMain.h"
#include "swarm.h"

swarm::swarm(int mode, int num,vectorMap * mapPointer){
    if(mode==1){
        for(int i = 0; i< num; i++){
            p.push_back(new fish());
        }
    }else if(mode==2){
        for(int i = 0; i< num; i++){
            p.push_back(new people());
        }
    }
    
    for(unsigned int i = 0; i < p.size(); i++){ // set swarm
        p[i]->set(mapPointer,p,i);
    }
}
//------------------------------


void swarm::update(){

    for(unsigned int i = 0; i < p.size(); i++){
        
        p[i]->update(); // update swarm
        
    }

}

void swarm::draw(){
    
    for(unsigned int i = 0; i < p.size(); i++){
        ofSetColor(0,255,0);
        p[i]->draw();    //draw swarm
    }
}

void swarm::drawShadow(){
    for(unsigned int i = 0; i < p.size(); i++){
        p[i]->drawShadow();    //draw swarm
    }
}
void swarm::mouseUpdate(int x, int y){
    p[0]->mouseUpdate(x,y);
}