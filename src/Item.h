class World;
class Particle;
class Interaction;
class Behavior;
class Action;

struct bool_attr {
    string name;
    bool value;
};

struct int_attr {
    string name;
    int value;
};

struct float_attr {
    string name;
    float value;
};

struct ofVec3f_attr {
    string name;
    ofVec3f value;
};

struct ofColor_attr {
    string name;
    ofColor value;
};


class Item{

    public:
        Item();
        //Item(World* _world);
        virtual ~Item();

        virtual const type_info& get_typeid();
        string get_type_name();

        string get_name();
        int get_id();
        World* get_world();
        bool is_alive();
        bool is_active();
        void set_name(string _name);
        void set_id(int _id);
        void set_world(World* _world);
        void set_live_state(bool live_state);
        void set_active_state(bool active_state);

        void iterate_attribute(string attr_name, bool forward);

        template <typename T>
        void add_listener(ofEvent<T>* event){
            if (typeid(*event) == typeid(ofEvent<bool_attr>)) {
                ofAddListener(*event, this ,& Item::set_bool_attr);
            } //else if (typeid(*event) == typeid(ofEvent<int_attr>)) {
                //ofAddListener(*event, this ,& Item::set_int_attr);
            //} else if (typeid(*event) == typeid(ofEvent<float_attr>)) {
            //    //ofAddListener(*event, this ,& Item::set_float_attr);
            //} else if (typeid(*event) == typeid(ofEvent<ofVec3f_attr>)) {
            //    //ofAddListener(*event, this ,& Item::set_ofVec3f_attr);
            //} else if (typeid(*event) == typeid(ofEvent<ofColor_attr>)) {
            //    //ofAddListener(*event, this ,& Item::set_ofColor_attr);
            //}
            //...
        }

        void add_bool_listener(ofEvent<bool_attr>* event);
        void add_int_listener(ofEvent<int_attr>* event);
        void add_float_listener(ofEvent<float_attr>* event);
        void add_ofVec3f_listener(ofEvent<ofVec3f_attr>* event);
        void add_ofColor_listener(ofEvent<ofColor_attr>* event);


        //virtual void add_listener(ofEvent<bool_attr>& bool_event);

        //virtual void add_listener(string attr_name);
        void set_bool_attr(bool_attr& _attr);
        void set_int_attr(int_attr& attr);
        void set_float_attr(float_attr& attr);
        void set_ofVec3f_attr(ofVec3f_attr& attr);
        void set_ofColor_attr(ofColor_attr& attr);


        /*
         *  The purpose of the "setup" function is to set and/or
         *  add shared variables.
         *  The "Item" class have an unordered_map
         *  that can be accessed with the member functions:
         *  "add", "set", "get" and "erase" for this purpose.
         */ 
        virtual void setup();
        virtual void run();

        template<typename T>
        void set(pair<string,T> name_value_pair){
            set<T>(name_value_pair.first, name_value_pair.second);
        }

        /*
         *  To manage with variables added by other Items
         *  use the functions below with the Item* pointer
         *  value equals the Item object that has add the
         *  variable.
         */
        template<typename T>
        void set(pair<pair<string,Item*>,T> keypair_val){
            set<T>(keypair_val.first.first, keypair_val.second, keypair_val.first.second);
        }

        template<typename T>
        T& get(pair<string,Item*>var_key){
            return get<T>(var_key.first, var_key.second);
        }

        template<typename T>
        void erase(pair<string,Item*> var_key){
            erase<T>(var_key.first, var_key.second);
        }

        /*
         *  Generic functions to manage with the shared 
         *  variables container "var_ptr_map":
         *  (set, get, erase)
         */

        template<typename T>
        void set(string var_name, T value=(T)0, Item* item_ptr=NULL){
            string var_key;
            if (item_ptr == NULL)
                var_key=string(var_name + ":" + to_string((long unsigned int)this));
            else
                var_key=string(var_name + ":" + to_string((long unsigned int)item_ptr));
            unordered_map <string,pair<void*,size_t>>::const_iterator map_it = var_ptr_map.find(var_key);
            if(map_it == var_ptr_map.end()) {
                // Add new element.
                var_ptr_map[var_key] = pair<void*,size_t>(new T(value),sizeof(T));
            } else if(map_it->second.second != sizeof(T)) {
                // Element already exists with diferent size_t.
	        stringstream error_msg;
                error_msg << "invalid conversion from variable of size_t: " <<
                             sizeof(T) << " to size_t: " << map_it->second.second <<
                             "; variable name:" << var_name;
                throw runtime_error(error_msg.str());
            } else {
                *static_cast<T*>(map_it->second.first) = value;
            }
        }

        template<typename T>
        T& get(string var_name, Item* item_ptr=NULL){
            string var_key;
            if (item_ptr == NULL)
                var_key=string(var_name + ":" + to_string((long unsigned int)this));
            else
                var_key=string(var_name + ":" + to_string((long unsigned int)item_ptr));
            unordered_map <string,pair<void*,size_t>>::const_iterator map_it = var_ptr_map.find(var_key);
            if(map_it == var_ptr_map.end()) {
                // Element doesn't exists.
                stringstream error_msg;
                error_msg << "get undefined variable " << var_name;
                throw runtime_error(error_msg.str());
            } else if(map_it->second.second != sizeof(T)) {
                // Element already exists with diferent size_t.
                stringstream error_msg;
                error_msg << "invalid conversion from variable of size_t: " <<
                             sizeof(T) << " to size_t: " << map_it->second.second <<
                             "; variable name:" << var_name;
                throw runtime_error(error_msg.str());
            }
            return *static_cast<T*>(map_it->second.first);
        }

        template<typename T>
        void erase(string var_name, Item* item_ptr=NULL){
            string var_key;
            if (item_ptr == NULL)
                var_key=string(var_name + ":" + to_string((long unsigned int)this));
            else
                var_key=string(var_name + ":" + to_string((long unsigned int)item_ptr));
            pair<void*,size_t>& map_el = var_ptr_map[var_key];
            if(sizeof(T) != map_el.second) {
	        stringstream error_msg;
                error_msg << "invalid conversion from size_t: " <<
                             sizeof(T) << " to size_t: " << map_el.second <<
                             "; variable name:" << var_name;
                throw runtime_error(error_msg.str());
            }
            delete static_cast<T*>(map_el.first); 
            var_ptr_map.erase(var_key);
        }

        void add_bool(string var_name, bool var_val);
        void set_bool(string var_name, bool var_val);
        void delete_bool(string var_name);
        bool* get_bool(string var_name);

        void add_int(string var_name, int var_val);
        void set_int(string var_name, int var_val);
        void delete_int(string var_name);
        int* get_int(string var_name);

        void add_float(string var_name, float var_val);
        void set_float(string var_name, float var_val);
        void delete_float(string var_name);
        float* get_float(string var_name);

        void add_ofColor(string var_name, ofColor var_val);
        void set_ofColor(string var_name, ofColor var_val);
        void delete_ofColor(string var_name);
        ofColor* get_ofColor(string var_name);

        void add_ofVec3f(string var_name, ofVec3f var_val);
        void set_ofVec3f(string var_name, ofVec3f var_val);
        void delete_ofVec3f(string var_name);
        ofVec3f* get_ofVec3f(string var_name);

        friend class Particle; 
        friend class Interaction; 
        friend class Action; 
        friend class Behavior; 
        friend class Master_Particle; 
        friend class Tag; 

    private:
        World* world;
        bool isAlive, isActive;
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

        //static const types_map(u_int8)

        unordered_map<string,pair<void*,size_t>> var_ptr_map;
        //unordered_map<pair<string,Item*>,pair<void*,size_t>> var_ptr_map;
        //unordered_map<Item*,pair<void*,size_t>> var_ptr_map;

        unordered_map<string, ofVec3f*> ofVec3fPtr_map;
        unordered_map<string, ofColor*> ofColorPtr_map;
        unordered_map<string, int*> intPtr_map;
        unordered_map<string, float*> floatPtr_map;
        unordered_map<string, bool*> boolPtr_map;

};
