class Particles_Container;

class Interaction {
    public:
        u_int id;
        string name;
        bool isAlive;
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
};

class Electrical_Repulsion : public Interaction{
    public:
        Electrical_Repulsion(Particle_props* hostParticle_props=(int)NULL);
        void interact(Particle_props* actuatedParticle_props);
};

class Electrical_Attraction : public Interaction{
    public:
        Electrical_Attraction(Particle_props* hostParticle_props);
        void interact(Particle_props* actuatedParticle_props);
};

class Wave_Source : public Interaction{
    public:
        int wave_speed;
        float weight,weight_fact;

        Wave_Source(Particle_props* hostParticle_props);
        void interact(Particle_props* actuatedParticle_props);
        void run();
};

/*
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

