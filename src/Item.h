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

    shared_variable_key(){
        host_item = NULL;
    }

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

struct shared_variable {

    shared_variable(){
        value = NULL;
        type_enum = T_NULL;
        is_new = true;
    }

    shared_variable(void* var_value, arg_t var_type_enum, bool var_is_new = true){
        value = var_value;
        type_enum = var_type_enum;
        is_new = var_is_new;
    }

    void* value;
    arg_t type_enum;
    bool is_new;
};

static arg_t type_info_2_arg_t(const type_info& type_id){
    arg_t result = T_NULL;

    if(type_id==typeid(ofEvent<pair<vector<shared_variable_key>,shared_variable>>*)){
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

        //virtual void set_listener(Button* button);
        virtual void set_listener(Button* button, ofEvent<pair<vector<shared_variable_key>,shared_variable>>* event);
        virtual void remove_listener(Button* button, ofEvent<pair<vector<shared_variable_key>,shared_variable>>* event);
        void add_listener(ofEvent<pair<vector<shared_variable_key>, shared_variable>>* event);
        void remove_listener(ofEvent<pair<vector<shared_variable_key>,shared_variable>>* event);
        virtual void remove_attached_buttons();

        void map_event_contents(pair<vector<shared_variable_key>, shared_variable>& received_var);

        template<typename IN_T, typename OUT_T>
        Item_Parameter<OUT_T> cast_item_parameter(Item_Parameter<IN_T> input_ip){
           return Item_Parameter<OUT_T> ((OUT_T)input_ip.value,
                                         pair<OUT_T,OUT_T>((OUT_T)input_ip.range.first,
                                                           (OUT_T)input_ip.range.second));
        }

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
         *  variables container "shared_variables_map":
         *  (set, get, erase)
         */

        template<typename U>
        void set_variable(string var_name, U value, Item* host_item_ptr=NULL){

            if (host_item_ptr == NULL)
                host_item_ptr = this;
    
            shared_variable_key key(var_name,host_item_ptr);
    
            arg_t type_enum = type_info_2_arg_t(typeid(&value));

            unordered_map <shared_variable_key, shared_variable, shared_variable_hasher>::iterator shvar_map_it = shared_variables_map.find(key);

            if (shvar_map_it == shared_variables_map.end()) {
                // Add new element.
                U* new_var = new U(value);
                shared_variables_map[key] = shared_variable(new_var,type_enum);
                    
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
             unordered_map <shared_variable_key, shared_variable, shared_variable_hasher>* shvar_map_ptr=NULL);
 
        template<typename T>
        void set_item_parameter(string var_name, Item_Parameter<T>* var_ptr, Item* host_item_ptr=NULL){
            set_variable<Item_Parameter<T>>(var_name, var_ptr, host_item_ptr);
        }

        template<typename U>
        U* get_variable(string var_name, Item* host_item_ptr=NULL,
             unordered_map <shared_variable_key, shared_variable, shared_variable_hasher>* shvar_map_ptr=NULL){
            U* result = (U*)NULL;

            arg_t type_enum = type_info_2_arg_t(typeid(result));

            if (host_item_ptr == NULL)
                host_item_ptr = this;
            
            shared_variable_key key(var_name, host_item_ptr);
            
            unordered_map <shared_variable_key, shared_variable, shared_variable_hasher>::iterator shvar_map_it = shared_variables_map.find(key);

            if(shvar_map_it != shared_variables_map.end()) {
                shared_variable& raw_value = shvar_map_it->second;

                if( raw_value.type_enum == type_enum and type_enum != T_NULL) {
                    result = static_cast<U*>(raw_value.value);
                    //cout << result->value << endl;
                } else if(type_enum == T_NULL) {
                    // Enumerator arg_t not defined for this type.
                    stringstream error_msg;
                    error_msg << "Enumerator arg_t not defined for this type." <<
                                 "; variable name:" << var_name;
                    //throw runtime_error(error_msg.str());
                    cout << error_msg.str() << endl;
                }  else {
                    // Element already exists with diferent arg_t.
                    stringstream error_msg;
                    error_msg << "Invalid conversion from variable of arg_t: " <<
                                 type_enum << " to arg_t: " << raw_value.type_enum <<
                                 "; variable name:" << var_name;
                    cout << error_msg.str() << endl;
                    //throw runtime_error(error_msg.str());
                }
            }// else {
            //    // Element doesn't exists.
            //    stringstream error_msg;
            //    error_msg << "get undefined variable " << var_name;
            //    cout << error_msg.str() << endl;
            //    //throw runtime_error(error_msg.str());
            //}
            return result;
        }

        shared_variable get_variable(string var_name, Item* host_item_ptr=NULL,
             unordered_map <shared_variable_key, shared_variable, shared_variable_hasher>* shvar_map_ptr=NULL);

        template<typename T>
        Item_Parameter<T>* get_item_parameter(string var_name, Item* host_item_ptr=NULL){
            return get_variable<Item_Parameter<T>>(var_name, host_item_ptr);
        }

        void erase_variable(string var_name, Item* host_item_ptr=NULL,
             unordered_map <shared_variable_key, shared_variable, shared_variable_hasher>* shvar_map_ptr=NULL);

        void clear_variables(unordered_map <shared_variable_key, shared_variable, shared_variable_hasher>* shvar_map_ptr=NULL);

        template <typename T>
        T map_parameter(Item_Parameter<T> current_var, Item_Parameter<T> input_var){
            return (input_var.value - input_var.range.first) *
                   (current_var.range.second - current_var.range.first) /
                   (input_var.range.second - input_var.range.first) + current_var.range.first;
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
         * All the shared variables must be added to the "shared_variables_map" inside
         * the Item constructor or setup functions using the template function "add".
         * The keys of the "shared_variables_map" are of type shared_variable_key with the name
         * of the variable and a pointer to the Item object that has set the
         * variable. The Item* pointer allows the Items to add variables to each other 
         * with the same name without overwrite or delete them, preserving the unicity
         * of the key. In most cases the Item* value is "this", because the most part
         * of the shared variables are added by the Item it self.
         */

        unordered_map<shared_variable_key, shared_variable, shared_variable_hasher> shared_variables_map;
        vector<Button*> attached_buttons;

};


struct item_hasher {
    size_t operator()(const Item*& k) const {
        using std::hash;
        return hash<long unsigned int>()((long unsigned int)k);
    }
};

