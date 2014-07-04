#include "testApp.h"

void Controller::setup() {
    set_event<bool>("ctrl1", NULL, this);
    set_event<int>("ctrl2", NULL, this);
    set<bool>("ctrl1",True,pair<bool,bool>(False,True));
    set<int>("ctrl2",10,pair<int,int>(0,500));
    set<vector<string>>("ctrl2_attr",vector<string>());
    get<vector<string>>("ctrl2_attr")->value.push_back("rad");
}

void Controller::run() {
    if (ofGetKeyPressed('+')){
        Item_Parameter<int>* val_ptr = get<int>("ctrl2");
        val_ptr->value++;
        notify_ctrl_event<int>("ctrl2");
    } else if (ofGetKeyPressed('-')){
            
        Item_Parameter<int>* val_ptr = get<int>("ctrl2");
        val_ptr->value--;
        notify_ctrl_event<int>("ctrl2");
    }

}

MidiController::MidiController(){
    set_name(get_type_name());
}

const type_info& MidiController::get_typeid(){
    return typeid(this);
}

string MidiController::get_type_name(){
    regex pattern ("^P?[0-9]*(.*)"); 
    return regex_replace(string(get_typeid().name()), pattern, string("$1"));
};

void MidiController::setup() {
      set_event<bool>("ctrl1", NULL, this);
      set_event<int>("ctrl2", NULL, this);
//    //midiIn.listPorts();
//    midiIn.openPort(1);
//    // don't ignore sysex, timing, & active sense messages,
//    // these are ignored by default
//    midiIn.ignoreTypes(false, true, false);
//    midiIn.addListener(this);
//    midiIn.setVerbose(true);
}

void MidiController::run() {

//    if (midiMessage.control != 0){
//        text.str(""); // clear
//        text << "Received control: " << midiMessage.control << "; value: "<< midiMessage.value;
//    }
//    //draw the last recieved message contents to the screen
//    ofDrawBitmapString(text.str(), 20, 20);
}

void MidiController::newMidiMessage(ofxMidiMessage& eventArgs) {
    // make a copy of the latest message
    midiMessage = eventArgs;
}
