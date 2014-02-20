class World;
class Particle;
class Interaction;
class Behavior;
class Action;

class Item{

    public:
        Item();
        Item(World* _world);
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
        //virtual void setup(Item* _host_item);
        virtual void setup();
        /*
         * The purpose of the "free" function is to delete
         * the variables added to the particles inside the
         * "setup" function.
         * This is called when ever a particle or the behavior
         * it self is removed from the host tag.
         */
        virtual void free(Item* _host_item);
        //virtual void run(Item* _host_item);
        //virtual void free();
        virtual void run();

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
        unordered_map<string, ofVec3f*> ofVec3fPtr_map;
        unordered_map<string, ofColor*> ofColorPtr_map;
        unordered_map<string, int*> intPtr_map;
        unordered_map<string, float*> floatPtr_map;
        unordered_map<string, bool*> boolPtr_map;


};

class Items_Fabric{
    public:
        Action*      create_action(string name);
        Particle*    create_particle(string name);
        Behavior*    create_behavior(string name);
        Interaction* create_interaction(string name);
};
