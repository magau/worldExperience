class Controller : public Item {
    public:

        // inputs:
        unordered_map<string,bool> switch_map;
        unordered_map<string,int8_t> knob_8bit_map;

        // outputs:
        ofEvent<bool_attr>    bool_var;
        ofEvent<int_attr>     int_var;
        ofEvent<float_attr>   float_var;
        ofEvent<ofVec3f_attr> ofVec3f_var;
        ofEvent<ofColor_attr> of_Color_var;

        //void notify(){ofNotifyEvent(iterate_variable,rise,this);}
        //void set_val(bool rise){_rise = rise;}
};

class MidiController : public Controller, ofxMidiListener{
    public:

        ofxMidiIn midiIn;
        ofxMidiMessage midiMessage;
	stringstream text;

        void setup();
        void run();
        void newMidiMessage(ofxMidiMessage& eventArgs);
        //void notify(){ofNotifyEvent(iterate_variable,rise,this);}
        //void set_val(bool rise){_rise = rise;}
};
