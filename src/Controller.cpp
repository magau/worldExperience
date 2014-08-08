#include "testApp.h"

void Controller::add_button(string ctrl_name){
    set_variable(ctrl_name, NULL, BUTTON, this);
}

void Controller::erase_button(string ctrl_name){
    // Button event must be removed from attached tag...
    Button* button = static_cast<Button*>(get_variable(ctrl_name).value);
    if (button->type_enum != T_NULL)
        erase_var_ptr(button->parameter, button->type_enum);
    erase_variable(ctrl_name);
}

void Controller::attach_button_parameter(string ctrl_name, string parameter_name, Item* host_item) {
    Button* button = static_cast<Button*>(get_variable(ctrl_name).value);
    button->attached_variables.push_back(shared_variable_key(parameter_name,host_item));
}

void Controller::detach_button_parameter(string ctrl_name, string parameter_name, Item* host_item) {
    Button* button = static_cast<Button*>(get_variable(ctrl_name).value);
    vector<shared_variable_key>::iterator attached_var_it = find(button->attached_variables.begin(),
                                                                 button->attached_variables.end(),
                                                                 shared_variable_key(parameter_name,host_item)); 
    button->attached_variables.erase(attached_var_it);
}

void Controller::setup() {
    add_button("ctrl3");
    setup_button_parameter<int>("ctrl3",10,pair<int,int>(0,500));
    attach_button_parameter("ctrl3","rad");
}

void Controller::notify_button_event(string ctrl_name) {
    Button* button = static_cast<Button*>(get_variable(ctrl_name).value);
    for (typename vector<shared_variable_key>::iterator attached_var_it = button->attached_variables.begin();
                                           attached_var_it != button->attached_variables.end();
                                           attached_var_it++) {
        shared_variable_key key = *attached_var_it;
        shared_variable_value value = shared_variable_value(button->parameter,button->type_enum);
        pair<shared_variable_key,shared_variable_value> sent_value(key, value);
        ofNotifyEvent(button->event, sent_value);
    }
}


void Controller::run() {
    if (ofGetKeyPressed('+')){
        iterate_button_parameter<int>("ctrl3");
        notify_button_event("ctrl3");
    } else if (ofGetKeyPressed('-')){
            
        iterate_button_parameter<int>("ctrl3", true);
        notify_button_event("ctrl3");
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
//      set_event<bool>("ctrl1", NULL, this);
//      set_event<int>("ctrl2", NULL, this);
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
