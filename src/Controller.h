class Controller : public Item {
    public:

        // inputs:
        unordered_map<string,bool> switch_map;
        unordered_map<string,int8_t> knob_8bit_map;

        // outputs:
        //ofEvent<bool>    bool_var;
        //ofEvent<int>     int_var;
        //ofEvent<float>   float_var;
        //ofEvent<ofVec3f> ofVec3f_var;
        //ofEvent<ofColor> of_Color_var;

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
