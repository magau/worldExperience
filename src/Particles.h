#include "testApp.h"

class Particle{
    public:
        u_int id;
        string name;
        Particle_props props;
        Interactions_Container interactions;
        Behaviors_Container behaviors;
        Particle (Particle_props init_props);
        //virtual void setup(Particle_props _props);
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
        Circle (Particle_props init_props);
        void display();
};


class Particles_Container : public Pointers_Container<Particle*>{
    public:
        Particle* add_itemByName(string iName, Particle_props init_props);

// This two methods must be transfered to the Master_Particle class, in Future...
        void attachInteraction_one2one(string iName, Particles_Container* actuated_particles);
        void attachInteraction_many2one(string iName, Particles_Container* actuated_particles);
};

