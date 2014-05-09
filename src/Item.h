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
         * The purpose of the "setup" function is to set and/or
         * add (only on particles it can be added variables)
         * sepecific variables required by this item to 
         * other items sharing the same tag, "host_items"
         * (taged with the host tag of this item).
         * This variables are used inside the "run" function of 
         * the item.
         * The "host item" class have a set of unordered_maps
         * that can be accessed with the member functions:
         * "add_", "set_", "get_" and "delete_" for certain 
         * types, used for this purpose.
         * It's adviced to add the name and id of this item to the 
         * added and/or seted variable name (key), if the variable is 
         * not suposed to be used by other items.
         */ 
        virtual void setup();
        virtual void run();

        template<typename T>
        void add(pair<string,T> var_val){
            var_ptr_map[pair<string,Item*>(var_val.first,this)] = pair<void*,size_t>(new T(var_val.second),sizeof(T));
        }

        template<typename T>
        void set(pair<string,T> var_val){
            pair<void*,size_t>& map_el = var_ptr_map[pair<string,Item*>(var_val.first,this)];
            if(sizeof(T) != map_el.second) {
	        stringstream error_msg;
                error_msg << "invalid conversion from size_t: " <<
                             sizeof(T) << " to size_t: " << map_el.second <<
                             "; variable name:" << var_val.first;
                throw runtime_error(error_msg);
            } else {
                *static_cast<T*>(map_el.first) = var_val.second;
            }
        }

        template<typename T>
        T& get(string var_name){
            pair<void*,size_t>& map_el = var_ptr_map[pair<string,Item*>(var_name,this)];
            if(sizeof(T) != map_el.second) {
	        stringstream error_msg;
                error_msg << "invalid conversion from size_t: " <<
                             sizeof(T) << " to size_t: " << map_el.second <<
                             "; variable name:" << var_name;
                throw runtime_error(error_msg);
            }
            return *static_cast<T*>(map_el.first);
        }

        void erase(string var_name){
            free(var_ptr_map[pair<string,Item*>(var_name,this)].first); 
            var_ptr_map.erase(pair<string,Item*>(var_name,this));    
        }

        template<typename T>
        void erase(string var_name){
            pair<void*,size_t>& map_el = var_ptr_map[pair<string,Item*>(var_name,this)];
            if(sizeof(T) != map_el.second) {
	        stringstream error_msg;
                error_msg << "invalid conversion from size_t: " <<
                             sizeof(T) << " to size_t: " << map_el.second <<
                             "; variable name:" << var_name;
                throw runtime_error(error_msg);
            } else {
                delete static_cast<T*>(map_el.first); 
                var_ptr_map.erase(pair<string,Item*>(var_name,this));    
            }
        }


        ///*
        // * To manage with variables added by other Items
        // *  use the functions below with the Item* pointer
        // *  value equals the Item object that has add the
        // *  variable.
        // */
        //template<typename T>
        //void add(pair<pair<string,Item*>,T> key_val){
        //    var_ptr_map[pair<string,Item*>(key_val.first.first,key_val.first.second)] = new T(key_val.second);
        //}
        //template<typename T>
        //void set(pair<pair<string,Item*>,T> key_val){
        //    *static_cast<T*> (var_ptr_map[pair<string,Item*>(key_val.first.first,key_val.first.second)]) = key_val.second;
        //}
        //template<typename T>
        //T& get(pair<string,Item*> key_pair){
        //    return *static_cast<T*>(var_ptr_map[pair<string,Item*>(key_pair.first,key_pair.second)]);
        //}
        //template<typename T>
        //void erase(pair<string,Item*> key_pair){
        //    delete static_cast<T*>(var_ptr_map[pair<string,Item*>(key_pair.first,key_pair.second)]); 
        //    var_ptr_map.erase(key_pair);    
        //}

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

        unordered_map<pair<string,Item*>,pair<void*,size_t>> var_ptr_map;

        unordered_map<string, ofVec3f*> ofVec3fPtr_map;
        unordered_map<string, ofColor*> ofColorPtr_map;
        unordered_map<string, int*> intPtr_map;
        unordered_map<string, float*> floatPtr_map;
        unordered_map<string, bool*> boolPtr_map;

};
