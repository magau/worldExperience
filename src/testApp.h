#pragma once

#include "ofMain.h"
#include <typeinfo>
//#include <sstream>
#include <algorithm>
#include <boost/regex.hpp>
using namespace boost;
#include <tr1/unordered_map> 
using namespace tr1;
using namespace std;
#include "math.h"
#include "PointersVector.h"
//#include "ofxMidi.h"
#include "Item.h"
#include "Controller.h"
#include "Action.h"
#include "Behaviors.h"
#include "Interactions.h"
#include "Particles.h"
#include "Particles_System.h"
//#include "Particles_Manager.h"
#include "Items_Factory.h"
#include "World_Camera.h"
#include "World.h"
#include "Tags.h"

#define USE_UNORDERED_MAP
#define USE_MOUSE_THREAD
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
           
           //Controller* cl;
  
           World world;

           Particle* buffer_particle;
           Tag* buffer_tag;
           Interaction* buffer_interaction;
           Behavior* buffer_behavior;
           //Manager_KeyboardInterface managerInterface;
            
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
