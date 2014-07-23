class World;
class Particle;
class Interaction;
class Behavior;
class Action;

enum arg_t{

    T_NULL,

    EAT_BOOL,
    EAT_INT,
    EAT_FLOAT,
    EAT_DOUBLE,

    IP_INT,
    IP_FLOAT,
    IP_BOOL,
    IP_VEC3F,
    IP_COLOR,

    CTRL_INT,
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

static arg_t type_info_2_arg_t(const type_info& type_id){
    arg_t result = T_NULL;

    if       (type_id==typeid(ofEvent<pair<string,Item_Parameter<int>>>*)){
        result = EAT_INT;
    } else if(type_id==typeid(ofEvent<pair<string,Item_Parameter<float>>>*)){
        result = EAT_FLOAT;
    } else if(type_id==typeid(ofEvent<pair<string,Item_Parameter<double>>>*)){
        result = EAT_DOUBLE;
    } else if(type_id==typeid(ofEvent<pair<string,Item_Parameter<bool>>>*)){
        result = EAT_BOOL;
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
    } else if(type_id==typeid(pair<vector<string>,
                                   pair<Item_Parameter<int>, ofEvent<pair<string,Item_Parameter<int>>>>>*)){
        result = CTRL_INT;
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

        template <typename T>
        void add_listener(ofEvent<pair<string,Item_Parameter<T>>>* event){
            ofAddListener(*event, this ,& Item::map_parameter<T>);
        }

        template <typename T>
        void remove_listener(ofEvent<pair<string,Item_Parameter<T>>>* event){
            ofRemoveListener(*event, this ,& Item::map_parameter<T>);
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
         *  variables container "var_ptr_map":
         *  (set, get, erase)
         */

        template<typename U>
        void set_variable(string var_name, U value, Item* item_ptr=NULL){
            string var_key;
            if (item_ptr == NULL)
                var_key=string(var_name + ":" + to_string((long unsigned int)this));
            else
                var_key=string(var_name + ":" + to_string((long unsigned int)item_ptr));

            arg_t arg_num = type_info_2_arg_t(typeid(&value));
            unordered_map <string,pair<void*,pair<arg_t,bool>>>::iterator map_it = var_ptr_map.find(var_key);
            //unordered_map <string,pair<void*,pair<size_t,bool>>>::iterator map_it = var_ptr_map.find(var_key);
            U* new_var;

            if (map_it == var_ptr_map.end()) {
                // Add new element.
                new_var = new U(value);
                var_ptr_map[var_key] = pair<void*,pair<arg_t,bool>>(new_var, pair<arg_t,bool>(arg_num,true));
                //cout << "set var:" << var_key << " value:" << new_var->value << endl;
                    
            } else if(map_it->second.second.first != arg_num) {
                // Element already exists with diferent enumerator arg_t.
	        stringstream error_msg;
                error_msg << "invalid conversion from variable of arg_t: " <<
                             arg_num << " to arg_t: " << map_it->second.second.first <<
                             "; variable name:" << var_name;
                //throw runtime_error(error_msg.str());
                cout << error_msg.str() << endl;
            } else if(arg_num == T_NULL) {
                // Enumerator arg_t not defined for this type.
	        stringstream error_msg;
                error_msg << "Enumerator arg_t not defined for this type." <<
                             "; variable name:" << var_name;
                //throw runtime_error(error_msg.str());
                cout << error_msg.str() << endl;
            } else {
                // Replace value.
                U* variable = static_cast<U*>(map_it->second.first);
                //cout << "overwiting var:" << var_key << " value:" << variable->value << endl;
                *variable = value;
                //cout << "new value:" << value.value << endl;
            }
        }

        template<typename T>
        void set_item_parameter(string var_name, Item_Parameter<T> value, Item* item_ptr=NULL){
            set_variable<Item_Parameter<T>>(var_name, value, item_ptr);
        }

        /*
         *  Add elements with already existent pointers.
         */

        template<typename U>
        void set_variable(string var_name, U* var_ptr, Item* item_ptr=NULL){

            string var_key;
            if (item_ptr == NULL)
                var_key=string(var_name + ":" + to_string((long unsigned int)this));
            else
                var_key=string(var_name + ":" + to_string((long unsigned int)item_ptr));

            arg_t arg_num = type_info_2_arg_t(typeid(var_ptr));
            unordered_map <string,pair<void*,pair<arg_t,bool>>>::iterator map_it = var_ptr_map.find(var_key);

            if (map_it == var_ptr_map.end()) {
                // Add an existent poiter as a new element.
                if (var_ptr == NULL)
                    var_ptr_map[var_key] = pair<void*,pair<arg_t,bool>>(new U, pair<arg_t,bool>(arg_num,true));
                else
                    var_ptr_map[var_key] = pair<void*,pair<arg_t,bool>>(var_ptr, pair<arg_t,bool>(arg_num,false));
                 
                //cout << "set var ptr:" << var_key << " value:" << var_ptr->value << endl;
            } else if(map_it->second.second.first != arg_num) {
                // Element already exists with diferent size_t.
	        stringstream error_msg;
                error_msg << "invalid conversion from variable of arg_t: " <<
                             arg_num << " to arg_t: " << map_it->second.second.first <<
                             "; variable name:" << var_name;
                //throw runtime_error(error_msg.str());
                cout << error_msg.str() << endl;
            } else if(arg_num == T_NULL) {
                // Enumerator arg_t not defined for this type.
	        stringstream error_msg;
                error_msg << "Enumerator arg_t not defined for this type." <<
                             "; variable name:" << var_name;
                //throw runtime_error(error_msg.str());
                cout << error_msg.str() << endl;
            }  else {
                // Replace element with an existent pointer.
                U* old_var = static_cast<U*>(map_it->second.first);
                //cout << "overwiting var:" << var_key << " value:" << old_var->value << endl;
                if (map_it->second.second.second)
                    delete old_var; 

                if (var_ptr == NULL) {
                    map_it->second.first = new U;
                    map_it->second.second.second = true;
                } else {
                    map_it->second.first = var_ptr;
                    map_it->second.second.second = false;
                }

                //cout << "new value:" << var_ptr->value << endl;
            }
        }

        void set_variable(string var_name, void* var_ptr, arg_t arg_num, Item* item_ptr=NULL);

        template<typename T>
        void set_item_parameter(string var_name, Item_Parameter<T>* var_ptr, Item* item_ptr=NULL){
            set_variable<Item_Parameter<T>>(var_name, var_ptr, item_ptr);
        }

        template<typename T>
        void set_event(string event_name, ofEvent<pair<string,Item_Parameter<T>>>* event_ptr=NULL, Item* item_ptr=NULL){
            set_variable<ofEvent<pair<string,Item_Parameter<T>>>>(event_name, event_ptr, item_ptr);
        }

        template<typename T>
        void set_ctrl(string event_name, pair<vector<string>, pair<Item_Parameter<T>,ofEvent<pair<string,Item_Parameter<T>>>>>* ctrl_ptr=NULL, Item* item_ptr=NULL){
            set_variable<pair<vector<string>, pair<Item_Parameter<T>,ofEvent<pair<string,Item_Parameter<T>>>>>>(event_name, ctrl_ptr, item_ptr);
        }

        template<typename U>
        U* get_variable(string var_name, Item* host_item_ptr=NULL){
            U* result = (U*)NULL;
            string var_key;
            if (host_item_ptr == NULL)
                var_key=string(var_name + ":" + to_string((long unsigned int)this));
            else
                var_key=string(var_name + ":" + to_string((long unsigned int)host_item_ptr));
            //cout << "get map key:" << var_key << endl;
            arg_t arg_num = type_info_2_arg_t(typeid(result));
            unordered_map <string,pair<void*,pair<arg_t,bool>>>::const_iterator map_it = var_ptr_map.find(var_key);
            if(map_it == var_ptr_map.end()) {
                // Element doesn't exists.
                stringstream error_msg;
                error_msg << "get undefined variable " << var_name;
                cout << error_msg.str() << endl;
                //throw runtime_error(error_msg.str());
            } else if(map_it->second.second.first != arg_num) {// or arg_num == T_NULL) {
                // Element already exists with diferent arg_t.
                stringstream error_msg;
                error_msg << "arg_t(T_NULL):" << T_NULL << " invalid conversion from variable of arg_t: " <<
                             arg_num << " to arg_t: " << map_it->second.second.first <<
                             "; variable name:" << var_name;
                cout << error_msg.str() << endl;
                //throw runtime_error(error_msg.str());
            } else if(arg_num == T_NULL) {
                // Enumerator arg_t not defined for this type.
	        stringstream error_msg;
                error_msg << "Enumerator arg_t not defined for this type." <<
                             "; variable name:" << var_name;
                //throw runtime_error(error_msg.str());
                cout << error_msg.str() << endl;
            }  else {
                result = static_cast<U*>(map_it->second.first);
                //cout << result->value << endl;
            }
            return result;
        }

        template<typename T>
        Item_Parameter<T>* get_item_parameter(string var_name, Item* host_item_ptr=NULL){
            return get_variable<Item_Parameter<T>>(var_name, host_item_ptr);
        }

        template<typename T>
        ofEvent<pair<string,Item_Parameter<T>>>* get_event(string var_name, Item* host_item_ptr=NULL){
            return get_variable<ofEvent<pair<string,Item_Parameter<T>>>>(var_name, host_item_ptr);
        }

        template<typename T>
        pair<vector<string>, pair<Item_Parameter<T>,ofEvent<pair<string,Item_Parameter<T>>>>>* get_ctrl(string event_name, Item* host_item_ptr=NULL){
            return get_variable<pair<vector<string>, pair<Item_Parameter<T>,ofEvent<pair<string,Item_Parameter<T>>>>>>(event_name, host_item_ptr);
        }

        void erase_variable(string var_name, Item* item_ptr=NULL);

        void erase_item_parameter(string var_name, Item* item_ptr=NULL);
        
        void erase_event(string var_name, Item* item_ptr=NULL);
        
        void erase_ctrl(string event_name, Item* item_ptr=NULL);

        template<typename T>
        void map_parameter(string var_name, Item_Parameter<T> param, Item* item_ptr=NULL){
            if (typeid(T) == typeid(int) or typeid(T) == typeid(float)) {
                Item_Parameter<T>* current_param = get_item_parameter<T>(var_name,item_ptr);
                current_param->value = (param.value - param.range.first) *
                                       (current_param->range.second - current_param->range.first) /
                                       (param.range.second - param.range.first) + current_param->range.first;
            } else {
                set_item_parameter<T>(var_name,param,item_ptr);
            }
        }


        arg_t get_event_arg_t(string event_name, Item* host_item=NULL);

        template<typename T>
        void set_item_parameter(pair<string,Item_Parameter<T>>& name_value_pair){
            set_item_parameter<T>(name_value_pair.first, name_value_pair.second);
        }

        template<typename T>
        void set_item_parameter(string var_name,T value, Item* item_ptr=NULL){
            set_item_parameter<T>(var_name, Item_Parameter<T>(value), item_ptr);
        }

        template<typename T>
        void set_item_parameter(string var_name,T value, pair<T,T> range, Item* item_ptr=NULL){
            set_item_parameter<T>(var_name, Item_Parameter<T>(value,range), item_ptr);
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

        unordered_map<string,pair<void*,pair<arg_t,bool>>> var_ptr_map;
        

};



