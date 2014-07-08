class Controller : public Item {
    public:
        virtual void setup();
        virtual void run();

        template <typename T>
        void add_ctrl(string ctrl_name) {
            set_event<T>(ctrl_name, NULL, this);
            set_variable<pair<vector<string>, Item_Parameter<T>>>(
                ctrl_name,
                pair<vector<string>,Item_Parameter<T>>( vector<string>(), Item_Parameter<T>() )
            );
        }

        template <typename T>
        void setup_ctrl_parameter(string ctrl_name, T value, pair<T,T> range) {
            pair<vector<string>, Item_Parameter<T>>* ctrl_aux_pair = get_variable<pair<vector<string>, Item_Parameter<T>>>(ctrl_name);
            ctrl_aux_pair->second = Item_Parameter<T>(value, range);
        }

        template <typename T>
        void set_ctrl_parameter(string ctrl_name, T value) {
            pair<vector<string>, Item_Parameter<T>>* ctrl_aux_pair = get_variable<pair<vector<string>, Item_Parameter<T>>>(ctrl_name);
            ctrl_aux_pair->second.value = value;
        }

        template <typename T>
        void iterate_ctrl_parameter(string ctrl_name, bool reverse=false) {
            pair<vector<string>, Item_Parameter<T>>* ctrl_aux_pair = get_variable<pair<vector<string>, Item_Parameter<T>>>(ctrl_name);
            if(reverse)
                ctrl_aux_pair->second.value--;
            else
                ctrl_aux_pair->second.value++;
        }

        template <typename T>
        void detach_ctrl_parameter(string ctrl_name, string parameter_name) {
            pair<vector<string>, Item_Parameter<T>>* ctrl_aux_pair = get_variable<pair<vector<string>, Item_Parameter<T>>>(ctrl_name);
            
            ctrl_aux_pair->first.pop(parameter_name);
        }        template <typename T>

        void attach_ctrl_parameter(string ctrl_name, string parameter_name) {
            pair<vector<string>, Item_Parameter<T>>* ctrl_aux_pair = get_variable<pair<vector<string>, Item_Parameter<T>>>(ctrl_name);
            
            ctrl_aux_pair->first.push_back(parameter_name);
        }

        template <typename T>
        void notify_ctrl_event(string ctrl_name) {
            pair<vector<string>, Item_Parameter<T>>* ctrl_aux_pair = get_variable<pair<vector<string>, Item_Parameter<T>>>(ctrl_name);
            

            for (typename vector<string>::iterator attached_attr_it = ctrl_aux_pair->first.begin();
                                                   attached_attr_it != ctrl_aux_pair->first.end();
                                                   attached_attr_it++) {
                pair<string,Item_Parameter<T>> attr(*attached_attr_it,ctrl_aux_pair->second);
                ofNotifyEvent(*(this->get_event<T>(ctrl_name)), attr);
            }
        }

        template <typename T>
        void remove_ctrl(string ctrl_name) {
            erase_event<T>(ctrl_name);
            erase_variable<pair<vector<string>, Item_Parameter<T>>>(ctrl_name);
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
