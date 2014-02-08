class Particles_Container;

class Particle : public Item {
    public:
        ofVec3f locat, veloc, accel;
        ofColor color;
        int rad;
        float relax_fact;

        unordered_map<string, ofVec3f*> ofVec3fPtr_map;
        unordered_map<string, ofColor*> ofColorPtr_map;
        unordered_map<string, int*> intPtr_map;
        unordered_map<string, float*> floatPtr_map;
        unordered_map<string, bool*> boolPtr_map;

        Tags_Container tags;
        Interactions_Container interactions;
        Behaviors_Container behaviors;

        Particle ();
        Particle (World* _world);
        ~Particle();

        void create_bool(string var_name, bool var_val);
        void set_bool(string var_name, bool var_val);
        void delete_bool(string var_name);
        bool* get_bool(string var_name);

        void create_int(string var_name, int var_val);
        void set_int(string var_name, int var_val);
        void delete_int(string var_name);
        int* get_int(string var_name);

        void create_float(string var_name, float var_val);
        void set_float(string var_name, float var_val);
        void delete_float(string var_name);
        float* get_float(string var_name);

        void create_ofColor(string var_name, ofColor var_val);
        void set_ofColor(string var_name, ofColor var_val);
        void delete_ofColor(string var_name);
        ofColor* get_ofColor(string var_name);

        void create_ofVec3f(string var_name, ofVec3f var_val);
        void set_ofVec3f(string var_name, ofVec3f var_val);
        void delete_ofVec3f(string var_name);
        ofVec3f* get_ofVec3f(string var_name);

        virtual void setup();
        virtual void run();
        virtual void behave();
        virtual void interact();
        virtual void update();
        virtual void display();
        //void bound_particles_location();
        //void set_speedLimit(int max_speed);
        void elastic_boundery();
};

class Circle : public Particle{
    public:
        Circle ();
        void display();
};


class Particles_Container : public Pointers_Container<Particle*>{
    public:
        Particle* create_itemByName(string iName);
};

