#pragma once

#include "Pointers_Container.h"
#include "worldExperience.h"
#include "Behaviors.h"
#include "Interactions.h"
#include "Particles.h"
#include "Particles_System.h"
#include "Particles_Manager.h"
#include "ofMain.h"


//#define SYPHON
//#define OSC_MSG

#ifdef SYPHON
#include "ofxSyphon.h"
#endif
	
#ifdef OSC_MSG
#include "ofxOsc.h"
#endif	


class getMouseLocation : public ofThread {
    public:
        int x,y;
        void threadedFunction(){
            while(true){
                x = ofGetMouseX();
                y = ofGetMouseY();
            }
        }
};

class testApp : public ofBaseApp{
	public:
           
           World world;
           Particles_Container* buffGroup;
           Manager_KeyboardInterface managerInterface;
           //string msg;
           //bool listenMsg;
            
#ifdef SYPHON
           ofxSyphonServer mainOutputSyphonServer;
#endif

		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
                void exit();
 
};
