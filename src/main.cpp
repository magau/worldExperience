#include "testApp.h"
#include "ofAppGlutWindow.h"

//--------------------------------------------------------------
int main(){
        //ofSetupOpenGL(1024,768, OF_WINDOW);                     // <-------- setup the GL context
	ofAppGlutWindow window; // create a window
	// set width, height, mode (OF_WINDOW or OF_FULLSCREEN)
        ofSetupOpenGL(&window, 1024, 768, OF_FULLSCREEN);
        //ofSetupOpenGL(&window, 1024, 768, OF_WINDOW);
//	ofSetupOpenGL(&window, 600, 400, OF_WINDOW);
        
	ofRunApp(new testApp()); // start the app
}
