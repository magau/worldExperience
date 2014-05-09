#include "testApp.h"

void MidiController::setup() {
    //midiIn.listPorts();
    midiIn.openPort(1);
    // don't ignore sysex, timing, & active sense messages,
    // these are ignored by default
    midiIn.ignoreTypes(false, true, false);
    midiIn.addListener(this);
    midiIn.setVerbose(true);
}

void MidiController::run() {
    if (midiMessage.control != 0){
        text.str(""); // clear
        text << "Received control: " << midiMessage.control << "; value: "<< midiMessage.value;
    }
    //draw the last recieved message contents to the screen
    ofDrawBitmapString(text.str(), 20, 20);
}

void MidiController::newMidiMessage(ofxMidiMessage& eventArgs) {
    // make a copy of the latest message
    midiMessage = eventArgs;
}
