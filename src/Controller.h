

class Button : public Item{
    public:
        class Button_Item{
            public:
                Button_Item(){};
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
        void set_parameter(arg_t _type_enum, T value, pair<T,T> range){
            if (type_enum != T_NULL)
                erase_var_ptr(parameter, type_enum);
            parameter = create_var_ptr(_type_enum);
            Parameter* param = static_cast<Parameter*>(parameter);
            //Item_Parameter<T>* param = static_cast<Item_Parameter<T>*>(parameter);
            param->set_value(value);
            param->set_range(range);
            type_enum = _type_enum;
        }

        template<typename T>
        void set_parameter(arg_t _type_enum, T value){
            if (type_enum != T_NULL)
                erase_var_ptr(parameter, type_enum);
            parameter = create_var_ptr(_type_enum);
            static_cast<Parameter*>(parameter)->set_value(value);
            type_enum = _type_enum;
        }

        void* parameter;
        arg_t type_enum;
        unordered_map<Item*,Button::Button_Item> listeners_map;

};

class Controller :  public Item{
    public:
        virtual void setup_ctrl();
        virtual void run();

        Button* add_button(string button_name);
        Button* get_button(string button_name);

        template <typename T>
        void setup_button_parameter(string button_name, arg_t _type_enum, T value, pair<T,T> range) {
            Button* button = static_cast<Button*>(get_variable(button_name).value);
            button->set_parameter(_type_enum,value,range);
        }

        template <typename T>
        void setup_button_parameter(string button_name, arg_t _type_enum, T value) {
            Button* button = static_cast<Button*>(get_variable(button_name).value);
            button->set_parameter(_type_enum, value);
        }

        void attach_listener_parameter(string button_name,Item* listener,string parameter_name,Item* host_item=NULL);
        void detach_listener_parameter(string button_name,Item* listener,string parameter_name,Item* host_item=NULL);

        template<typename T>
        void iterate_button_parameter(string button_name, bool reverse=false, bool closed_range=false) {
            Button* button = static_cast<Button*>(get_variable(button_name).value);
            //Parameter* param = static_cast<Parameter*>(button->parameter);
            Item_Parameter<T>* parameter = static_cast<Item_Parameter<T>*>(button->parameter);
            if(reverse){
                if (typeid(T) == typeid(bool)){
                    parameter->value = False;
                } else {
                    if (closed_range){
                        parameter->value = (((parameter->value - parameter->range.first - 1) % parameter->delta) + parameter->delta) % parameter->delta + parameter->range.first;
                    } else {
                        parameter->value -= 1;
                        if (parameter->value < parameter->range.first){
                            parameter->value = parameter->range.first;
                        }// else if (parameter->value > parameter->range.second){
                        //    parameter->value = parameter->range.second;
                        //}
                    }
                }
            } else {
                if (typeid(T) == typeid(bool)){
                    parameter->value = True;
                } else {
                    if (closed_range){
                        parameter->value = (((parameter->value - parameter->range.first + 1) % parameter->delta) + parameter->delta) % parameter->delta + parameter->range.first;
                    } else {
                        parameter->value += 1;
                        //if (parameter->value < parameter->range.first){
                        //    parameter->value = parameter->range.first;
                        //} else 
                        if (parameter->value > parameter->range.second){
                            parameter->value = parameter->range.second;
                        }
                    }
                }
            }
        }

        void notify_button_events(string button_name);
        void erase_button(string button_name);

};

class OscParticlesTrackerController : public ofThread, public Controller{
    // listen on port 12345
    //#define PORT 12345
    #define PORT 44444
    public:
        //OscParticlesTrackerController();
        const type_info& get_typeid();
        void setup_ctrl();
        void run(){};
        void threadedFunction(){
            ofxOscMessage m;
            vector<ofVec3f>* param_ptr =
            &static_cast<Item_Parameter_VectorOfofVect3f*>(get_button("multi-touch")->parameter)->value;
            while(true){
                // check for waiting messages
                if(receiver.hasWaitingMessages() and m.getAddress() == "/touches"){
                    // get the next message
                    receiver.getNextMessage(&m);
            
                    // check for Touch app message
                    int n_args = m.getNumArgs()/4;
                    if(m.getAddress() == "/touches" and n_args > 0) {
                        param_ptr->clear();
                        for (int i=0; i<n_args; i++){
                            param_ptr->push_back(ofVec3f());
                            // z coord is used to store the id
                            param_ptr->back().z = m.getArgAsInt32(i*4);
                            param_ptr->back().x = m.getArgAsFloat(i*4+1);
                            param_ptr->back().y = m.getArgAsFloat(i*4+2);
           
                        }
                    } 
                } 
            }
        }
    private:
        ofxOscReceiver receiver;
};

//class MidiController : public Controller, ofxMidiListener{
//    public:
//        MidiController();
//        const type_info& get_typeid();
//        ofxMidiIn midiIn;
//        ofxMidiMessage midiMessage;
//	stringstream text;
//
//        void setup();
//        void run();
//        void newMidiMessage(ofxMidiMessage& eventArgs);
//};
