class World;
class Particle;
class Interaction;
class Behavior;
class Action;
class Button;
class Item;

enum arg_t{

    T_NULL,

    IP_INT,
    IP_FLOAT,
    IP_BOOL,
    IP_VEC3F,
    IP_COLOR,

    EVENT_SH_VAR,

    BUTTON
};

template<typename T>
class Item_Parameter{
    public:
        Item_Parameter<T>() {}

        Item_Parameter<T>(T var) {
            value = var;
        }

        Item_Parameter<T>(T val, pair<T,T> ran) {
           value = val;
           range = ran; 
        }

        T value;
        pair<T,T> range;
};

struct shared_variable_key {
    Item* host_item;
    string name;

    shared_variable_key(){}

    shared_variable_key(string var_name, Item* item=NULL){
        name = var_name;
        host_item = item;
    }

    bool operator==(const shared_variable_key &other) const {
         return (host_item == other.host_item && name == other.name);
    } 
};

struct shared_variable_hasher {
    size_t operator()(const shared_variable_key& k) const {
        using std::hash;
        return hash<string>()(k.name) ^ (hash<long unsigned int>()((long unsigned int)k.host_item) << 1);
    }
};

struct shared_variable_value {

    shared_variable_value(){
        value = NULL;
        type_enum = T_NULL;
    }

    shared_variable_value(void* var_value, arg_t var_type_enum){
        value = var_value;
        type_enum = var_type_enum;
    }

    void* value;
    arg_t type_enum;
    bool is_new;
};

static arg_t type_info_2_arg_t(const type_info& type_id){
    arg_t result = T_NULL;

    if(type_id==typeid(ofEvent<pair<shared_variable_key,shared_variable_value>>*)){
        result = EVENT_SH_VAR;
    } else if(type_id==typeid(Item_Parameter<int>*)){
        result = IP_INT;
    } else if(type_id==typeid(Item_Parameter<float>*)){
        result = IP_FLOAT;
    } else if(type_id==typeid(Item_Parameter<bool>*)){
        result = IP_BOOL;
    } else if(type_id==typeid(Item_Parameter<ofVec3f>*)){
        result = IP_VEC3F;
    } else if(type_id==typeid(Item_Parameter<ofColor>*)){
        result = IP_COLOR;
    } else if(type_id==typeid(Button*)){
        result = BUTTON;
    }

    //...
    return result;
};


class Item{

    public:
        Item();

        //Item(World* _world);
        virtual ~Item();

        virtual const type_info& get_typeid();
        virtual string get_type_name();

        string get_name();
        int get_id();
        World* get_world();
        void set_name(string _name);
        void set_id(int _id);
        void set_world(World* _world);
        void print_shared_var_names();

        void iterate_attribute(string attr_name, bool forward);

        void add_listener(ofEvent<pair<shared_variable_key, shared_variable_value>>* event);
        void add_listener(Item* host_controller, string button_name);

        void remove_listener(ofEvent<pair<shared_variable_key, shared_variable_value>>* event);
        virtual void remove_listener(string event_name, Item* host_ctrl_ptr);

        void map_event_parameter(pair<shared_variable_key, shared_variable_value>& received_var);

        /*
         *  The purpose of the "setup" function is to set and/or
         *  add shared variables.
         *  The "Item" class have an unordered_map
         *  that can be accessed with the member functions:
         *  "add", "set", "get" and "erase" for this purpose.
         */ 
        virtual void setup();
        virtual void run();

        /*
         *  Generic functions to manage with the shared 
         *  variables container "var_ptr_map":
         *  (set, get, erase)
         */

        template<typename U>
        void set_variable(string var_name, U value, Item* host_item_ptr=NULL){

            shared_variable_value raw_value;

            if (host_item_ptr == NULL)
                host_item_ptr = this;
    
            shared_variable_key key;
            key.host_item = host_item_ptr;
            key.name      = var_name;
    
            arg_t type_enum = type_info_2_arg_t(typeid(&value));

            unordered_map <shared_variable_key, shared_variable_value, shared_variable_hasher>::iterator shvar_map_it = shared_variables_map.find(key);

            if (shvar_map_it == shared_variables_map.end()) {
                // Add new element.
                U* new_var = new U(value);

                //var_ptr_map[var_key] = pair<void*,pair<arg_t,bool>>(new_var, pair<arg_t,bool>(type_enum,true));

                raw_value.value     = new_var;
                raw_value.type_enum = type_enum;
                raw_value.is_new    = true;
                shared_variables_map[key] = raw_value;
                    
                //cout << "add new variable:" << key.name << endl;
            } else if(shvar_map_it->second.type_enum != type_enum) {
                // Element already exists with diferent enumerator arg_t.
                stringstream error_msg;
                error_msg << "invalid assignement from variable of arg_t: " <<
                             type_enum << " to arg_t: " << shvar_map_it->second.type_enum <<
                             "; variable name:" << var_name;
                //throw runtime_error(error_msg.str());
                cout << error_msg.str() << endl;
            } else if(type_enum == T_NULL) {
                // Enumerator arg_t not defined for this type.
                stringstream error_msg;
                error_msg << "Enumerator arg_t not defined for this type." <<
                             "; variable name:" << var_name;
                //throw runtime_error(error_msg.str());
                cout << error_msg.str() << endl;
            } else {
                // Replace value.
                *static_cast<U*>(shvar_map_it->second.value) = value;
                //U* variable = static_cast<U*>(shvar_map_it->second.value);
                //*variable = value;
                //cout << "overwiting var:" << var_key << " value:" << variable->value << endl;
                //cout << "new value:" << value.value << endl;
            }
        }

        template<typename T>
        void set_item_parameter(string var_name, Item_Parameter<T> value, Item* host_item_ptr=NULL){
            set_variable<Item_Parameter<T>>(var_name, value, host_item_ptr);
        }

        /*
         *  Add elements with already existent pointers.
         */

        template<typename U>
        void set_variable(string var_name, U* var_ptr, Item* host_item_ptr=NULL){
            set_variable(var_name, var_ptr, type_info_2_arg_t(typeid(var_ptr)), host_item_ptr);
        }

        void* create_var_ptr(arg_t type_enum);

        void erase_var_ptr(void* var_value, arg_t type_enum);

        void set_variable(string var_name, void* var_ptr=NULL, arg_t type_enum=T_NULL, Item* host_item_ptr=NULL,
             unordered_map <shared_variable_key, shared_variable_value, shared_variable_hasher>* shvar_map_ptr=NULL);
 
        template<typename T>
        void set_item_parameter(string var_name, Item_Parameter<T>* var_ptr, Item* host_item_ptr=NULL){
            set_variable<Item_Parameter<T>>(var_name, var_ptr, host_item_ptr);
        }

        template<typename T>
        void set_event(string event_name, ofEvent<pair<shared_variable_key,Item_Parameter<T>>>* event_ptr=NULL, Item* host_item_ptr=NULL){
            set_variable<ofEvent<pair<shared_variable_key,Item_Parameter<T>>>>(event_name, event_ptr, host_item_ptr);
        }

        template<typename T>
        void set_ctrl(string event_name, pair<vector<string>, pair<Item_Parameter<T>,ofEvent<pair<shared_variable_key,Item_Parameter<T>>>>>* ctrl_ptr=NULL, Item* host_item_ptr=NULL){
            set_variable<pair<vector<string>, pair<Item_Parameter<T>,ofEvent<pair<shared_variable_key,Item_Parameter<T>>>>>>(event_name, ctrl_ptr, host_item_ptr);
        }

        template<typename U>
        U* get_variable(string var_name, Item* host_item_ptr=NULL,
             unordered_map <shared_variable_key, shared_variable_value, shared_variable_hasher>* shvar_map_ptr=NULL){
            U* result = (U*)NULL;

            arg_t type_enum = type_info_2_arg_t(typeid(result));
            shared_variable_value raw_value;

            if (host_item_ptr == NULL)
                host_item_ptr = this;
            
            shared_variable_key key;
            key.host_item = host_item_ptr;
            key.name      = var_name;
            
            unordered_map <shared_variable_key, shared_variable_value, shared_variable_hasher>::iterator shvar_map_it = shared_variables_map.find(key);

            if(shvar_map_it == shared_variables_map.end()) {
                // Element doesn't exists.
                stringstream error_msg;
                error_msg << "get undefined variable " << var_name;
                cout << error_msg.str() << endl;
                //throw runtime_error(error_msg.str());
            } else {

                raw_value = shvar_map_it->second;

                if( shvar_map_it->second.type_enum != type_enum) {// or type_enum == T_NULL) {
                    // Element already exists with diferent arg_t.
                    stringstream error_msg;
                    error_msg << "arg_t(T_NULL):" << T_NULL << " invalid conversion from variable of arg_t: " <<
                                 type_enum << " to arg_t: " << shvar_map_it->second.type_enum <<
                                 "; variable name:" << var_name;
                    cout << error_msg.str() << endl;
                    //throw runtime_error(error_msg.str());
                } else if(type_enum == T_NULL) {
                    // Enumerator arg_t not defined for this type.
                    stringstream error_msg;
                    error_msg << "Enumerator arg_t not defined for this type." <<
                                 "; variable name:" << var_name;
                    //throw runtime_error(error_msg.str());
                    cout << error_msg.str() << endl;
                }  else {
                    result = static_cast<U*>(shvar_map_it->second.value);
                    //cout << result->value << endl;
                }
            }
            return result;
        }

        shared_variable_value get_variable(string var_name, Item* host_item_ptr=NULL,
             unordered_map <shared_variable_key, shared_variable_value, shared_variable_hasher>* shvar_map_ptr=NULL);

        template<typename T>
        Item_Parameter<T>* get_item_parameter(string var_name, Item* host_item_ptr=NULL){
            return get_variable<Item_Parameter<T>>(var_name, host_item_ptr);
        }

        template<typename T>
        ofEvent<pair<shared_variable_key,Item_Parameter<T>>>* get_event(string var_name, Item* host_item_ptr=NULL){
            return get_variable<ofEvent<pair<shared_variable_key,Item_Parameter<T>>>>(var_name, host_item_ptr);
        }

        template<typename T>
        pair<vector<string>, pair<Item_Parameter<T>,ofEvent<pair<shared_variable_key,Item_Parameter<T>>>>>* get_ctrl(string event_name, Item* host_item_ptr=NULL){
            return get_variable<pair<vector<string>, pair<Item_Parameter<T>,ofEvent<pair<shared_variable_key,Item_Parameter<T>>>>>>(event_name, host_item_ptr);
        }

        void erase_variable(string var_name, Item* host_item_ptr=NULL,
             unordered_map <shared_variable_key, shared_variable_value, shared_variable_hasher>* shvar_map_ptr=NULL);

        void erase_item_parameter(string var_name, Item* host_item_ptr=NULL);
        
        void erase_event(string var_name, Item* host_item_ptr=NULL);
        
        void erase_ctrl(string event_name, Item* host_item_ptr=NULL);

        template<typename T>
        void map_parameter(string var_name, Item_Parameter<T> param, Item* host_item_ptr=NULL){
            if (typeid(T) == typeid(int) or typeid(T) == typeid(float) or typeid(T) == typeid(double)) {
                Item_Parameter<T>* current_param = get_item_parameter<T>(var_name,host_item_ptr);
                current_param->value = (param.value - param.range.first) *
                                       (current_param->range.second - current_param->range.first) /
                                       (param.range.second - param.range.first) + current_param->range.first;
            } else {
                set_item_parameter<T>(var_name,param,host_item_ptr);
            }
        }

        template<typename T>
        void set_item_parameter(pair<string,Item_Parameter<T>>& name_value_pair){
            set_item_parameter<T>(name_value_pair.first, name_value_pair.second);
        }

        template<typename T>
        void set_item_parameter(string var_name,T value, Item* host_item_ptr=NULL){
            set_item_parameter<T>(var_name, Item_Parameter<T>(value), host_item_ptr);
        }

        template<typename T>
        void set_item_parameter(string var_name,T value, pair<T,T> range, Item* host_item_ptr=NULL){
            set_item_parameter<T>(var_name, Item_Parameter<T>(value,range), host_item_ptr);
        }


        /*
         *  To manage with variables added by other Items
         *  use the functions below with the Item* pointer
         *  value equals the Item object that has add the
         *  variable.
         */
        template<typename T>
        void set_item_parameter(pair<pair<string,Item*>,Item_Parameter<T>>& keypair_val){
            set_item_parameter<T>(keypair_val.first.first, keypair_val.second, keypair_val.first.second);
        }

        template<typename T>
        Item_Parameter<T>* get_item_parameter(pair<string,Item*>& var_key){
            return get_item_parameter<T>(var_key.first, var_key.second);
        }

        //template<typename T>
        void erase_item_parameter(pair<string,Item*>& var_key){
            //erase_item_parameter<T>(var_key.first, var_key.second);
            erase_item_parameter(var_key.first, var_key.second);
        }

        template<typename T>
        void map_parameter(pair<shared_variable_key,Item_Parameter<T>>& name_value_pair){
            map_parameter<T>(name_value_pair.first.name, name_value_pair.second);
        }

        template<typename T>
        void map_parameter(pair<string,Item_Parameter<T>>& name_value_pair){
            map_parameter<T>(name_value_pair.first, name_value_pair.second);
        }

        friend class Particle; 
        friend class World; 
        friend class Interaction; 
        friend class Action; 
        friend class Behavior; 
        friend class Master_Particle; 
        friend class Tag; 

    private:
        World* world;
        Item_Parameter<bool> is_alive, is_active;
        int id;
        string name;

    protected:
        /* 
         * All the shared variables must be added to the "var_ptr_map" inside
         * the Item constructor or setup functions using the template function "add".
         * The keys of the "var_ptr_map" are of type std::pair<string,Item*> with the name
         * of the variable and a pointer to the Item object that has set the
         * variable. The Item* pointer allows the Items to add variables to each other 
         * with the same name without overwrite or delete them, preserving the unicity
         * of the key. In most cases the Item* value is "this", because the most part
         * of the shared variables are added by the Item it self.
         */

        //unordered_map<string,pair<void*,pair<arg_t,bool>>> var_ptr_map;
        unordered_map<shared_variable_key, shared_variable_value, shared_variable_hasher> shared_variables_map;
        vector<Button*> attached_buttons;

};



