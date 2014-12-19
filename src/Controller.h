

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

class Controller : public ofThread, public Item {
    public:
        virtual void setup();
        virtual void update();
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

class OscParticlesTrackerController :  public Controller{
    // listen on port 12345
    //#define PORT 12345
    public:
        //OscParticlesTrackerController();
        const type_info& get_typeid();
        void setup();
        void update(){};
        void threadedFunction(){
            cout << "start osc thread..." << endl;
            ofxOscMessage m;
            int n_args;
            float last_t = ofGetElapsedTimef(),
            max_time = 2E-1;
            vector<ofVec3f>* osc_tracker =
            &static_cast<Item_Parameter_VectorOfofVect3f*>(get_button("multi-touch")->parameter)->value;
            while(true){
                // check for waiting messages
                if (receiver.hasWaitingMessages()){
                    // get the next message
                    receiver.getNextMessage(&m);
                    // check for Touch app message
                    n_args = m.getNumArgs()/4;
                } else {
                    n_args = 0;
                }
            
                if(n_args > 0 and m.getAddress() == "/touches") {
                        lock();
                        osc_tracker->clear();
                        for (int i=0; i<n_args; i++){
                            osc_tracker->push_back(ofVec3f());
                            // z coord is used to store the id
                            osc_tracker->back().z = m.getArgAsInt32(i*4);
                            osc_tracker->back().x = m.getArgAsFloat(i*4+1);
                            osc_tracker->back().y = m.getArgAsFloat(i*4+2);
                        }
                        unlock();
                    cout << "locations:" << endl;
                    for( vector<ofVec3f>::iterator loc_it = osc_tracker->begin();
                         loc_it != osc_tracker->end(); loc_it++ )
                        cout << *loc_it << endl;

                    last_t = ofGetElapsedTimef();

                } else if (osc_tracker->size() > 0 and ofGetElapsedTimef() - last_t > max_time) {
                    cout << "revove locations:" << endl;
                    for( vector<ofVec3f>::iterator loc_it = osc_tracker->begin();
                         loc_it != osc_tracker->end(); loc_it++ )
                        cout << *loc_it << endl;

                    lock();
                    osc_tracker->clear();
                    unlock();
                    last_t = ofGetElapsedTimef();
                } else {
                    ofSleepMillis(100);
                }
            }
        }
    private:
        int port;
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
//        void update();
//        void newMidiMessage(ofxMidiMessage& eventArgs);
//};
