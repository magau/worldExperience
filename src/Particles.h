
class Particle{
    public:
        u_int id;
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

        Interactions_Container interactions;
        Behaviors_Container behaviors;
        Particle (World* _world);
        //virtual void setup();
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

// This two methods must be transfered to the Master_Particle class, in Future...
        void attachInteraction_one2one(string iName, Particles_Container* actuated_particles);
        void attachInteraction_many2one(string iName, Particles_Container* actuated_particles);
};

