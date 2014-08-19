#include "testApp.h"

void Controller::add_button(string button_name){
    set_variable(button_name, NULL, BUTTON, this);
}

void Controller::erase_button(string button_name){
    //cout << "remove button from controller..."<<endl;
    Button* button = static_cast<Button*>(get_variable(button_name).value);
    if (button->type_enum != T_NULL){
        // Remove button event from attached tag.
        vector<Item*>::iterator listener_it;
        for (listener_it = button->listeners.end()-1;
             listener_it != button->listeners.begin();
             listener_it--){
             //cout << "Remove button:" << button_name << " from attaced listener:" << (*listener_it)->get_name() << endl;
            (*listener_it)->remove_listener(button);
            //(*listener_it)->remove_listener(button_name,this);
        }
        //cout << "all attached items has be removed successfully." << endl;
    }
    //cout << "delete button:" << button_name << endl;
    erase_variable(button_name);
    //cout << "button deleted." << endl;
}

void Controller::attach_button_parameter(string button_name, string parameter_name, Item* host_item) {
    Button* button = static_cast<Button*>(get_variable(button_name).value);
    button->attached_variables.push_back(shared_variable_key(parameter_name,host_item));
}

void Controller::detach_button_parameter(string button_name, string parameter_name, Item* host_item) {
    Button* button = static_cast<Button*>(get_variable(button_name).value);
    vector<shared_variable_key>::iterator attached_var_it = find(button->attached_variables.begin(),
                                                                 button->attached_variables.end(),
                                                                 shared_variable_key(parameter_name,host_item)); 
    button->attached_variables.erase(attached_var_it);
}

void Controller::add_listener(string button_name, Item* listener){
    Button* button = static_cast<Button*>(get_variable(button_name).value);
    if (button != NULL) {
            // Add this to the button listeners vector<Items*>. 
            button->listeners.push_back(listener);

            // Add button to the listener attached_buttons (vector<Button*>)
            // and add listener(s) to the button event.
            listener->set_listener(button);
    } else {
        cout << "error: Invalid button name for Controller: " << get_name() << "." << endl;
    }
}

void Controller::remove_listener(string button_name, Item* listener){
    cout << "remove button from tag..."<<endl;
    Button* button = static_cast<Button*>(get_variable(button_name).value);
    if (button != NULL) {
        listener->remove_listener(button);
        // Remove listener from the button listeners (vector<Items*>). 
        //cout << "Remove tag:" << get_name() << " from the button listeners." << endl; 
        vector<Item*>::iterator listener_it = find(button->listeners.begin(),button->listeners.end(),listener);
        if(listener_it != button->listeners.end())
            button->listeners.erase(listener_it);
        //cout << "tag:" << get_name() << " removed sccessfully." << endl; 
    } else {
        cout << "error: Invalid button name for Controller: " << get_name() << "." << endl;
    }

}

void Controller::setup() {
    add_button("ctrl1");
    setup_button_parameter<int>("ctrl1",10,pair<int,int>(0,127));
    attach_button_parameter("ctrl1","rad");

    add_button("ctrl2");
    setup_button_parameter<int>("ctrl2",10,pair<int,int>(0,127));
    attach_button_parameter("ctrl2","weight");

    add_button("ctrl3");
    setup_button_parameter<int>("ctrl3",10,pair<int,int>(0,127));
    attach_button_parameter("ctrl3","weight");
}

void Controller::notify_button_event(string button_name) {
    Button* button = static_cast<Button*>(get_variable(button_name).value);
    shared_variable value = shared_variable(button->parameter,button->type_enum);
    pair<vector<shared_variable_key>,shared_variable> sent_value(button->attached_variables, value);
    ofNotifyEvent(button->event, sent_value);
}


void Controller::run() {
    if (get_variable("ctrl3").value != NULL){
        if (ofGetKeyPressed('1')) {
            if (ofGetKeyPressed('+')){
                iterate_button_parameter<int>("ctrl1");
                notify_button_event("ctrl1");
            } else if (ofGetKeyPressed('-')){
                iterate_button_parameter<int>("ctrl1", true);
                notify_button_event("ctrl1");
            }
        } else if (ofGetKeyPressed('2')){
            if (ofGetKeyPressed('+')){
                iterate_button_parameter<int>("ctrl2");
                notify_button_event("ctrl2");
            } else if (ofGetKeyPressed('-')){
                iterate_button_parameter<int>("ctrl2", true);
                notify_button_event("ctrl2");
            }
        } else if (ofGetKeyPressed('3')){
            if (ofGetKeyPressed('+')){
                iterate_button_parameter<int>("ctrl3");
                notify_button_event("ctrl3");
            } else if (ofGetKeyPressed('-')){
                iterate_button_parameter<int>("ctrl3", true);
                notify_button_event("ctrl3");
            }
        }
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
