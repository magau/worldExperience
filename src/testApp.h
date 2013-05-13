#pragma once

#include "Pointers_Container.h"
#include "worldExperience.h"
#include "Behaviors.h"
#include "Interactions.h"
#include "Particles.h"
#include "Particles_System.h"
#include "Particles_Manager.h"
#include "ofxKeyMap.h"  
#include "ofMain.h"


////#define SYPHON
////#define OSC_MSG
//
//#ifdef SYPHON
//#include "ofxSyphon.h"
//#endif
//	
//#ifdef OSC_MSG
//#include "ofxOsc.h"
//#endif	
//

class getMouseLocation : public ofThread {
    public:
        int x,y;
        //ofPoint* loc;

        //void setup(ofPoint* _loc){
        //    loc = _loc;
        //}

        void threadedFunction(){
            while(true){
                x = ofGetMouseX();
                y = ofGetMouseY();
                //loc->set(ofGetMouseX(),ofGetMouseY());
            }
        }
};

class testApp : public ofBaseApp{
	public:
           
           ofxKeyMap keys;  
           World world;
           World_Manager manager;
           Particles_Container* buffGroup;
            
//                RegularGrid_PS main_particles_system;
//                RegularGrid_IS regularGrid_interactions_system;
////#ifdef SYPHON
////	        ofxSyphonServer mainOutputSyphonServer;
////#endif
//
//#ifdef OSC_MSG
//               //osc from kinect location recognizer
//               //oscFromKinect_IS external_interactions;
//#else
//               //mouse and keyboard interactions
//                getMouseLocation mouse;  
//                //mouseWaveSrc_IS mouseWave;
////                mouseWaveSrcGenerator_IS mouseWaveGenerator;
//                mouse_IS external_interactions;
//#endif	

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
