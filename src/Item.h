class World;
class Particle;
class Interaction;
class Behavior;
class Action;

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

class Item{

    public:
        Item();

        //Item(World* _world);
        virtual ~Item();

        virtual const type_info& get_typeid();
        virtual string get_type_name();

        void print_shared_var_names();
        string get_name();
        int get_id();
        World* get_world();
        void set_name(string _name);
        void set_id(int _id);
        void set_world(World* _world);

        void iterate_attribute(string attr_name, bool forward);

        template <typename T>
        void add_listener(ofEvent<pair<string,T>>* event){
            ofAddListener(*event, this ,& Item::set<T>);
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

        template<typename T>
        void set(string var_name, Item_Parameter<T> value, Item* item_ptr=NULL){
            string var_key;
            if (item_ptr == NULL)
                var_key=string(var_name + ":" + to_string((long unsigned int)this));
            else
                var_key=string(var_name + ":" + to_string((long unsigned int)item_ptr));
            unordered_map <string,pair<void*,pair<size_t,bool>>>::iterator map_it = var_ptr_map.find(var_key);
            Item_Parameter<T>* new_var;
            if (map_it == var_ptr_map.end()) {
                // Add new element.
                new_var = new Item_Parameter<T>(value);
                pair<size_t,bool> aux_param = pair<size_t,bool>(sizeof(T),true);
                var_ptr_map[var_key] = pair<void*,pair<size_t,bool>>(new_var,aux_param);
                //cout << "set var:" << var_key << " value:" << new_var->value << endl;
                    
            } else if(map_it->second.second.first != sizeof(T)) {
                // Element already exists with diferent size_t.
	        stringstream error_msg;
                error_msg << "invalid conversion from variable of size_t: " <<
                             sizeof(T) << " to size_t: " << map_it->second.second.first <<
                             "; variable name:" << var_name;
                //throw runtime_error(error_msg.str());
                cout << error_msg.str() << endl;
            } else {
                Item_Parameter<T>* parameter = static_cast<Item_Parameter<T>*>(map_it->second.first);
                //cout << "overwiting var:" << var_key << " value:" << parameter->value << endl;
                *parameter = value;
                //cout << "new value:" << value.value << endl;
            }
        }

        /*
         *  Add elements with already existent pointers.
         */
        template<typename T>
        void set(string var_name, Item_Parameter<T>* var_ptr, Item* item_ptr=NULL){
            string var_key;
            if (item_ptr == NULL)
                var_key=string(var_name + ":" + to_string((long unsigned int)this));
            else
                var_key=string(var_name + ":" + to_string((long unsigned int)item_ptr));
            unordered_map <string,pair<void*,pair<size_t,bool>>>::iterator map_it = var_ptr_map.find(var_key);
            if (map_it == var_ptr_map.end()) {
                // Add an existent poiter as a new element.
                pair<size_t,bool> aux_param = pair<size_t,bool>(sizeof(T),false);
                var_ptr_map[var_key] = pair<void*,pair<size_t,bool>>(var_ptr,aux_param);
                //cout << "set var ptr:" << var_key << " value:" << var_ptr->value << endl;
            } else if(map_it->second.second.first != sizeof(T)) {
                // Element already exists with diferent size_t.
	        stringstream error_msg;
                error_msg << "invalid conversion from variable of size_t: " <<
                             sizeof(T) << " to size_t: " << map_it->second.second.first <<
                             "; variable name:" << var_name;
                //throw runtime_error(error_msg.str());
                cout << error_msg.str() << endl;
            } else {
                // Replace element with an existent pointer.
                Item_Parameter<T>* old_var = static_cast<Item_Parameter<T>*>(map_it->second.first);
                //cout << "overwiting var:" << var_key << " value:" << old_var->value << endl;
                if (map_it->second.second.second)
                    delete old_var; 
                pair<size_t,bool> aux_param = pair<size_t,bool>(sizeof(T),false);
                pair<void*,pair<size_t,bool>> new_el = pair<void*,pair<size_t,bool>>(var_ptr,aux_param);
                map_it->second = new_el;
                //cout << "new value:" << var_ptr->value << endl;
            }
        }

        template<typename T>
        Item_Parameter<T>* get(string var_name, Item* item_ptr=NULL){
            Item_Parameter<T>* result = (Item_Parameter<T>*)NULL;
            string var_key;
            if (item_ptr == NULL)
                var_key=string(var_name + ":" + to_string((long unsigned int)this));
            else
                var_key=string(var_name + ":" + to_string((long unsigned int)item_ptr));
            //cout << "get map key:" << var_key << endl;
            unordered_map <string,pair<void*,pair<size_t,bool>>>::const_iterator map_it = var_ptr_map.find(var_key);
            if(map_it == var_ptr_map.end()) {
                // Element doesn't exists.
                stringstream error_msg;
                error_msg << "get undefined variable " << var_name;
                cout << error_msg.str() << endl;
                //throw runtime_error(error_msg.str());
            } else if(map_it->second.second.first != sizeof(T)) {
                // Element already exists with diferent size_t.
                stringstream error_msg;
                error_msg << "invalid conversion from variable of size_t: " <<
                             sizeof(T) << " to size_t: " << map_it->second.second.first <<
                             "; variable name:" << var_name;
                cout << error_msg.str() << endl;
                //throw runtime_error(error_msg.str());
            } else {
                result = static_cast<Item_Parameter<T>*>(map_it->second.first);
                //cout << result->value << endl;
            }
            return result;
        }

        template<typename T>
        void erase(string var_name, Item* item_ptr=NULL){
            string var_key;
            if (item_ptr == NULL)
                var_key=string(var_name + ":" + to_string((long unsigned int)this));
            else
                var_key=string(var_name + ":" + to_string((long unsigned int)item_ptr));
            unordered_map <string,pair<void*,pair<size_t,bool>>>::const_iterator map_it = var_ptr_map.find(var_key);
            if(map_it == var_ptr_map.end()) {
                // Element doesn't exists.
                stringstream error_msg;
                error_msg << "erase undefined variable " << var_name;
                cout << error_msg.str() << endl;
                //throw runtime_error(error_msg.str());
            } else if(map_it->second.second.first != sizeof(T)) {
                // Element already exists with diferent size_t.
                stringstream error_msg;
                error_msg << "invalid conversion from variable of size_t: " <<
                             sizeof(T) << " to size_t: " << map_it->second.second.first <<
                             "; erase variable name:" << var_name;
                cout << error_msg.str() << endl;
                //throw runtime_error(error_msg.str());
            } else {
                Item_Parameter<T>* parameter = static_cast<Item_Parameter<T>*>(map_it->second.first);
                if (map_it->second.second.second)
                    delete parameter; 
                var_ptr_map.erase(map_it);
            }
        }

        template<typename T>
        void set_event(string event_name, Item* item_ptr=NULL){
        //    string var_key;
        //    if (item_ptr == NULL)
        //        var_key=string(event_name + ":" + to_string((long unsigned int)this));
        //    else
        //        var_key=string(event_name + ":" + to_string((long unsigned int)item_ptr));
        //    unordered_map <string,pair<void*,pair<size_t,bool>>>::const_iterator map_it = var_ptr_map.find(var_key);
        //    if (map_it == var_ptr_map.end()) {
        //        // Add new element.
        //        var_ptr_map[var_key] = pair<void*,size_t>(new ofEvent<T>,sizeof(T));
        //        //value: callback
        //        //var_ptr_map[var_key] = pair<void*,size_t>(new T(value),sizeof(T));
        //            
        //    } else if(map_it->second.second != sizeof(T)) {
        //        // Element already exists with diferent size_t.
	//        stringstream error_msg;
        //        error_msg << "invalid conversion from variable of size_t: " <<
        //                     sizeof(T) << " to size_t: " << map_it->second.second <<
        //                     "; event name:" << event_name;
        //        //throw runtime_error(error_msg.str());
        //        cout << error_msg.str() << endl;
        //    } else {
        //        delete static_cast<ofEvent<T>*>(map_it->second.first); 
        //        var_ptr_map.erase(map_it);
        //        var_ptr_map[var_key] = pair<void*,size_t>(new ofEvent<T>,sizeof(T));
        //        //value: callback
        //        //*static_cast<T*>(map_it->second.first) = value;
        //    }
        }

        template<typename T>
        ofEvent<T>* get_event(string var_name, Item* item_ptr=NULL){
            ofEvent<T>* result = (ofEvent<T>*)NULL;
        //    string var_key;
        //    if (item_ptr == NULL)
        //        var_key=string(var_name + ":" + to_string((long unsigned int)this));
        //    else
        //        var_key=string(var_name + ":" + to_string((long unsigned int)item_ptr));
        //    unordered_map <string,pair<void*,pair<size_t,bool>>>::const_iterator map_it = var_ptr_map.find(var_key);
        //    if(map_it == var_ptr_map.end()) {
        //        // Element doesn't exists.
        //        stringstream error_msg;
        //        error_msg << "get undefined event " << var_name;
        //        cout << error_msg.str() << endl;
        //        //throw runtime_error(error_msg.str());
        //    } else if(map_it->second.second != sizeof(T)) {
        //        // Element already exists with diferent size_t.
        //        stringstream error_msg;
        //        error_msg << "invalid conversion from variable of size_t: " <<
        //                     sizeof(T) << " to size_t: " << map_it->second.second <<
        //                     "; event name:" << var_name;
        //        cout << error_msg.str() << endl;
        //        //throw runtime_error(error_msg.str());
        //    } else {
        //        result = static_cast<ofEvent<T>*>(map_it->second.first);
        //    }
            return result;
        }


        template<typename T>
        void erase_event(string var_name, Item* item_ptr=NULL) {
        //    string var_key;
        //    if (item_ptr == NULL)
        //        var_key=string(var_name + ":" + to_string((long unsigned int)this));
        //    else
        //        var_key=string(var_name + ":" + to_string((long unsigned int)item_ptr));
        //    unordered_map <string,pair<void*,pair<size_t,bool>>>::const_iterator map_it = var_ptr_map.find(var_key);
        //    if(map_it == var_ptr_map.end()) {
        //        // Element doesn't exists.
        //        stringstream error_msg;
        //        error_msg << "erase undefined event " << var_name;
        //        cout << error_msg.str() << endl;
        //        //throw runtime_error(error_msg.str());
        //    } else if(map_it->second.second != sizeof(T)) {
        //        // Element already exists with diferent size_t.
        //        stringstream error_msg;
        //        error_msg << "invalid conversion from variable of size_t: " <<
        //                     sizeof(T) << " to size_t: " << map_it->second.second <<
        //                     "; erase event name:" << var_name;
        //        cout << error_msg.str() << endl;
        //        //throw runtime_error(error_msg.str());
        //    } else {
        //        delete static_cast<ofEvent<T>*>(map_it->second.first); 
        //        var_ptr_map.erase(var_key);
        //    }
        }

        template<typename T>
        void set(pair<string,Item_Parameter<T>>& name_value_pair){
            set<T>(name_value_pair.first, name_value_pair.second);
        }

        template<typename T>
        void set(string name,T value, Item* item_ptr=NULL){
            set<T>(name, Item_Parameter<T>(value), item_ptr);
        }

        template<typename T>
        void set(string name,T value, pair<T,T> range, Item* item_ptr=NULL){
            set<T>(name, Item_Parameter<T>(value,range), item_ptr);
        }


        /*
         *  To manage with variables added by other Items
         *  use the functions below with the Item* pointer
         *  value equals the Item object that has add the
         *  variable.
         */
        template<typename T>
        void set(pair<pair<string,Item*>,Item_Parameter<T>>& keypair_val){
            set<T>(keypair_val.first.first, keypair_val.second, keypair_val.first.second);
        }

        template<typename T>
        Item_Parameter<T>* get(pair<string,Item*>& var_key){
            return get<T>(var_key.first, var_key.second);
        }

        template<typename T>
        void erase(pair<string,Item*>& var_key){
            erase<T>(var_key.first, var_key.second);
        }

        friend class Particle; 
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

        //static const types_map(u_int8)

        unordered_map<string,pair<void*,pair<size_t,bool>>> var_ptr_map;

};
