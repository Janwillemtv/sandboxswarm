#pragma once

#include "ofMain.h"
#include "swarmBoid.h"
#include "swarm.h"
#include "vectorMap.h"
#include "water.h"


class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
        void exit();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);

    
        swarm * fish;
        swarm * people;
        vector <water> ripples;
    
        vectorMap map;

        ofVec2f mouse;
};
