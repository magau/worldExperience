class Button{
    public:
        Button() {
            type_enum = T_NULL;
            parameter = NULL;
        }

        void* parameter;
        arg_t type_enum;
        ofEvent<pair<shared_variable_key,shared_variable_value>> event;
        vector<shared_variable_key> attached_variables; 
        
};

class Controller : public Item {
    public:
        virtual void setup();
        virtual void run();

        void add_button(string ctrl_name);

        template <typename T>
        void setup_button_parameter(string ctrl_name, T value, pair<T,T> range) {
            Button* button = static_cast<Button*>(get_variable(ctrl_name).value);
            if (button->type_enum != T_NULL)
                erase_var_ptr(button->parameter, button->type_enum);
            button->parameter = new Item_Parameter<T>(value, range);
            button->type_enum = type_info_2_arg_t(typeid(Item_Parameter<T>*));
        }

        void attach_button_parameter(string ctrl_name, string parameter_name, Item* host_item = NULL);

        void detach_button_parameter(string ctrl_name, string parameter_name, Item* host_item = NULL);

        template<typename T>
        void iterate_button_parameter(string ctrl_name, bool reverse=false) {
            Button* button = static_cast<Button*>(get_variable(ctrl_name).value);
            Item_Parameter<T>* parameter = static_cast<Item_Parameter<T>*>(button->parameter);
            if(reverse)
                parameter->value--;
            else
                parameter->value++;
        }

        void notify_button_event(string ctrl_name);

        void erase_button(string ctrl_name);

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
};
