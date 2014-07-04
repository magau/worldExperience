class Controller : public Item {
    public:
        virtual void setup();
        virtual void run();
        template <typename T>
        void notify_ctrl_event(string ctrl_name) {
            Item_Parameter<int>* val_ptr = get<int>(ctrl_name);
            //val_ptr->value++;
            vector<string> attached_attrs = get<vector<string>>(ctrl_name+"_attr")->value;
            for (typename vector<string>::iterator attached_attr_it = attached_attrs.begin();
                                                   attached_attr_it != attached_attrs.end();
                                                   attached_attr_it++) {
                pair<string,Item_Parameter<T>> attr(*attached_attr_it,*val_ptr);
                ofNotifyEvent(*(this->get_event<T>(ctrl_name)), attr);
            }
        }
};

class MidiController : public Controller, ofxMidiListener{
    public:
        MidiController();
        const type_info& get_typeid();
        string get_type_name();
        ofxMidiIn midiIn;
        ofxMidiMessage midiMessage;
	stringstream text;

        void setup();
        void run();
        void newMidiMessage(ofxMidiMessage& eventArgs);
        //void notify(){ofNotifyEvent(iterate_variable,rise,this);}
        //void set_val(bool rise){_rise = rise;}
};
