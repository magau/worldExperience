class Controller : public Item {
    public:
        virtual void setup();
        virtual void run();

        template <typename T>
        void add_ctrl(string ctrl_name) {
            //set_ctrl<T>(ctrl_name, NULL, this);
            set_variable(ctrl_name, NULL, CTRL_INT, this);
        }

        template <typename T>
        void setup_ctrl_parameter(string ctrl_name, T value, pair<T,T> range) {
            get_ctrl<T>(ctrl_name)->second.first = Item_Parameter<T>(value, range);
        }

        template <typename T>
        void set_ctrl_parameter(string ctrl_name, T value) {
            get_ctrl<T>(ctrl_name)->second.first.value = value;

        }

        template <typename T>
        void iterate_ctrl_parameter(string ctrl_name, bool reverse=false) {
            if(reverse)
                get_ctrl<T>(ctrl_name)->second.first.value--;
            else
                get_ctrl<T>(ctrl_name)->second.first.value++;
        }

        template <typename T>
        void detach_ctrl_parameter(string ctrl_name, string parameter_name) {
            get_ctrl<T>(ctrl_name)->first.pop(parameter_name);
        }
        
        template <typename T>
        void attach_ctrl_parameter(string ctrl_name, string parameter_name) {
            get_ctrl<T>(ctrl_name)->first.push_back(parameter_name);
        }

        template <typename T>
        void notify_ctrl_event(string ctrl_name) {
            pair<vector<string>, pair<Item_Parameter<T>,ofEvent<pair<string,Item_Parameter<T>>>>>* ctrl_aux_all = get_ctrl<T>(ctrl_name);
            for (typename vector<string>::iterator attached_attr_it = ctrl_aux_all->first.begin();
                                                   attached_attr_it != ctrl_aux_all->first.end();
                                                   attached_attr_it++) {
                pair<string,Item_Parameter<T>> attr(*attached_attr_it,ctrl_aux_all->second.first);
                ofNotifyEvent(ctrl_aux_all->second.second, attr);
            }
        }

        template <typename T>
        void remove_ctrl(string ctrl_name) {
            erase_ctrl(ctrl_name);
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
