class Particles_Container;
class Groups_Container : public Pointers_Container<Particles_Container*>{};

//class Tag;
//class Tags_Container : public Pointers_Container<Tag*>{};

class Particle{
    public:
        int id;
        string name;
        World* world;
        ofVec3f locat, veloc, accel;
        ofColor color;
        int rad;
        float relax_fact;
        bool isAlive, isActive;

        unordered_map<string, ofVec3f*> ofVec3fPtr_map;
        unordered_map<string, ofColor*> ofColorPtr_map;
        unordered_map<string, int*> intPtr_map;
        unordered_map<string, float*> floatPtr_map;
        unordered_map<string, bool*> boolPtr_map;

        Groups_Container groups;
        Tags_Container tags;
        Interactions_Container interactions;
        Behaviors_Container behaviors;
        Particle (World* _world);
        ~Particle();
        void set_var(string var_name, ofVec3f var_val);
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
        Circle (World* _world);
        void display();
};


class Particles_Container : public Pointers_Container<Particle*>{
    public:
        Particle* add_itemByName(string iName, World* world);
        Particle* add(Particle* particles, bool mainContainer=true);

// This two methods must be transfered to the Master_Particle class, in Future...
        void attachInteraction_one2one(string iName, Particles_Container* actuated_particles);
        void attachInteraction_many2one(string iName, Particles_Container* actuated_particles);
};

