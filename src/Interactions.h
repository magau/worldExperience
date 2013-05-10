class Particles_Container;

class Interaction {
    public:
        int id;
        string name;
        Particle_props* props;
        int max_dist;
        int min_dist; 
        int timer;
        float weigth_fact;
        World* world;
        Particles_Container* actuated_particles;
        Interaction(Particle_props* hostParticle_props);
        virtual void run();
        virtual void interact(Particle_props* actuatedParticle_props);
        //virtual void update(Particle_props* p_props);
};

class Interaction_I : public Interaction{
    public:
        Interaction_I(Particle_props* hostParticle_props=(int)NULL);
        void interact(Particle_props* actuatedParticle_props);
};


class Interaction_II : public Interaction{
    public:
        Interaction_II(Particle_props* hostParticle_props);
        void interact(Particle_props* actuatedParticle_props);
};

/*
class Interaction_III : public Interaction{
    public:
        Interaction_III(Particle_props* hostParticle_props);
        void interact(vector<Particle>* particlesVect_ptr);
};

class Interaction_IV : public Interaction{
    public:
        ofVec3f temp_loc;
        //vector <Interaction_III> generated_interactions;
        Interaction_IV(Particle_props* hostParticle_props);
        void interact(Particle_props* actuatedParticle_props);
};
*/

class Interactions_Container : public Pointers_Container<Interaction*>{
    public:
        Interaction* add_itemByName(string iName, Particle_props* init_props);
};

