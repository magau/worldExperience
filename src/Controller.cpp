#include "testApp.h"

void Controller::add_button(string button_name){
    set_variable(button_name, NULL, BUTTON, this);
}

void Controller::erase_button(string button_name){
    Button* button = static_cast<Button*>(get_variable(button_name).value);
    if (button->type_enum != T_NULL){
        unordered_map <Item*,Button::Button_Item>::iterator b_item_map_it;
        for (b_item_map_it = button->listeners_map.begin();
             b_item_map_it != button->listeners_map.end();
             b_item_map_it++){
             b_item_map_it->second.listener->remove_listener(button,&(b_item_map_it->second.event));
        }
    }
    erase_variable(button_name);
}

void Controller::attach_listener_parameter(string button_name,
                                           Item* listener,
                                           string parameter_name,
                                           Item* host_item) {

    Button* button = static_cast<Button*>(get_variable(button_name).value);
    unordered_map <Item*,Button::Button_Item>::iterator b_item_map_it = button->listeners_map.find(listener);
    if (b_item_map_it == button->listeners_map.end()){
        button->listeners_map[listener] = Button::Button_Item(listener);
        listener->set_listener(button,&(button->listeners_map[listener].event));
    }

    button->listeners_map[listener].attached_variables.push_back(shared_variable_key(parameter_name,host_item));
}

void Controller::detach_listener_parameter(string button_name,
                                           Item* listener,
                                           string parameter_name,
                                           Item* host_item) {

    Button* button = static_cast<Button*>(get_variable(button_name).value);
    unordered_map <Item*,Button::Button_Item>::iterator b_item_map_it = button->listeners_map.find(listener);
    if (b_item_map_it != button->listeners_map.end()){

        vector<shared_variable_key>::iterator attached_var_it = find(b_item_map_it->second.attached_variables.begin(),
                                                                     b_item_map_it->second.attached_variables.end(),
                                                                     shared_variable_key(parameter_name,host_item));
        if (attached_var_it != b_item_map_it->second.attached_variables.end()){
            b_item_map_it->second.attached_variables.erase(attached_var_it);
            if (b_item_map_it->second.attached_variables.size() == 0){
                listener->remove_listener(button,&(b_item_map_it->second.event));
                button->listeners_map.erase(b_item_map_it);
            }
        }
    }
}

void Controller::setup() {
    add_button("ctrl1");
    setup_button_parameter<int>("ctrl1",64,pair<int,int>(0,128));

    add_button("ctrl2");
    setup_button_parameter<int>("ctrl2",64,pair<int,int>(0,128));

    add_button("ctrl3");
    setup_button_parameter<int>("ctrl3",10,pair<int,int>(0,128));

    add_button("switch4");
    setup_button_parameter<bool>("switch4",True,pair<bool,bool>(True,False));

}

void Controller::notify_button_events(string button_name) {
    Button* button = static_cast<Button*>(get_variable(button_name).value);
    shared_variable value = shared_variable(button->parameter,button->type_enum);

    unordered_map <Item*,Button::Button_Item>::iterator b_item_map_it;
    for (b_item_map_it = button->listeners_map.begin();
         b_item_map_it != button->listeners_map.end();
         b_item_map_it++){

         pair<vector<shared_variable_key>,shared_variable> sent_value(b_item_map_it->second.attached_variables, value);
         ofNotifyEvent(b_item_map_it->second.event, sent_value);
         //cout << ((b_item_map_it->second.attached_variables.end()-1)->name) << endl;
    } 
}

void Controller::run() {
    if (ofGetKeyPressed('1')) {
        if (ofGetKeyPressed('+')){
            iterate_button_parameter<int>("ctrl1");
            notify_button_events("ctrl1");
        } if (ofGetKeyPressed('-')){
            iterate_button_parameter<int>("ctrl1", true);
            notify_button_events("ctrl1");
        }
    }
    if (ofGetKeyPressed('2')){
        if (ofGetKeyPressed('+')){
            iterate_button_parameter<int>("ctrl2");
            notify_button_events("ctrl2");
        } else if (ofGetKeyPressed('-')){
            iterate_button_parameter<int>("ctrl2", true);
            notify_button_events("ctrl2");
        }
    }
    if (ofGetKeyPressed('3')){
        if (ofGetKeyPressed('+')){
            iterate_button_parameter<int>("ctrl3");
            notify_button_events("ctrl3");
        } else if (ofGetKeyPressed('-')){
            iterate_button_parameter<int>("ctrl3", true);
            notify_button_events("ctrl3");
        }
    }
    if (ofGetKeyPressed('4')){
        if (ofGetKeyPressed('+')){
            iterate_button_parameter<bool>("switch4");
            notify_button_events("switch4");
        } else if (ofGetKeyPressed('-')){
            iterate_button_parameter<bool>("switch4", true);
            notify_button_events("switch4");
        }

        //Button* button = static_cast<Button*>(get_variable("switch4").value);
        //Item_Parameter<bool>* parameter = static_cast<Item_Parameter<bool>*>(button->parameter);
        //cout << "switch4 value:" << parameter->value << endl;
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
