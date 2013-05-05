#include "testApp.h"

class Particle{
    public:
        int id;
        string itemType;
        Particle_props props;
        Interactions_Container interactions;
        Behaviors_Container behaviors;
        ParticlesManager* manager;
        Particle (Particle_props init_props);
        //virtual void setup(Particle_props _props);
        virtual void run();
        virtual void update();
        virtual void display();
        //void bound_particles_location();
        //void set_speedLimit(int max_speed);
        //void enable_screenElasticBoundery();
};

class Circle : public Particle{
    public:
        Circle (Particle_props init_props);
        //virtual void setup(Particle_props _props);
        void display();
        //void bound_particles_location();
        //void set_speedLimit(int max_speed);
        //void enable_screenElasticBoundery();
};

/*
class InteractiveParticle : public BaseParticle{
    public:
        InteractiveParticle (Particle_props init_props);
        void run();
        //virtual void interact(Particle* actuated_particle);
        //virtual void interact(vector<BaseParticle>* particlesVect_ptr);
};

class DerivedParticle : public BaseParticle{
    public:
        DerivedParticle(Particle_props init_props);
};
*/

