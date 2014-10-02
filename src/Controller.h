

class Button : public Item{
    public:
        class Button_Item{
            public:
                Button_Item(){listener = NULL;};
                Button_Item(Item* new_listener){listener = new_listener;};
                Item* listener;
                vector<shared_variable_key> attached_variables;
                ofEvent<pair<vector<shared_variable_key>,shared_variable>> event;
        };




        Button() {
            type_enum = T_NULL;
            parameter = NULL;
            
        }

        ~Button () {
            if (type_enum != T_NULL)
                erase_var_ptr(parameter, type_enum);
        }

        template<typename T>
        void set_parameter( T value, pair<T,T> range){
            if (type_enum != T_NULL)
                erase_var_ptr(parameter, type_enum);
            parameter = new Item_Parameter<T>(value, range);
            type_enum = type_info_2_arg_t(typeid(Item_Parameter<T>*));
        }

        void* parameter;
        arg_t type_enum;
        //ofEvent<pair<vector<shared_variable_key>,shared_variable>> event;
        //vector<shared_variable_key> attached_variables; 
        //vector<Item*> listeners;
        //vector<Button_Item> attached_listeners;
        unordered_map<Item*,Button::Button_Item> listeners_map;

};

class Controller : public Item {
    public:
        virtual void setup();
        virtual void run();

        void add_button(string button_name);

        template <typename T>
        void setup_button_parameter(string button_name, T value, pair<T,T> range) {
            Button* button = static_cast<Button*>(get_variable(button_name).value);
            button->set_parameter(value, range);
            //if (button->type_enum != T_NULL)
            //    erase_var_ptr(button->parameter, button->type_enum);
            //button->parameter = new Item_Parameter<T>(value, range);
            //button->type_enum = type_info_2_arg_t(typeid(Item_Parameter<T>*));
        }

        void attach_listener_parameter(string button_name,Item* listener,string parameter_name,Item* host_item=NULL);
        void detach_listener_parameter(string button_name,Item* listener,string parameter_name,Item* host_item=NULL);

        template<typename T>
        void iterate_button_parameter(string button_name, bool reverse=false) {
            Button* button = static_cast<Button*>(get_variable(button_name).value);
            Item_Parameter<T>* parameter = static_cast<Item_Parameter<T>*>(button->parameter);
            if(reverse){
                if (typeid(T) == typeid(bool))
                    parameter->value = False;
                else
                    parameter->value = (((parameter->value - parameter->range.first - 1) % parameter->delta) + parameter->delta) % parameter->delta + parameter->range.first;
            } else {
                if (typeid(T) == typeid(bool))
                    parameter->value = True;
                else
                    parameter->value = (((parameter->value - parameter->range.first + 1) % parameter->delta) + parameter->delta) % parameter->delta + parameter->range.first;
            }
        }

        void notify_button_events(string button_name);
        void erase_button(string button_name);

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
