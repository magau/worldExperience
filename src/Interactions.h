class Particles_Container;

class Interaction {
    public:
        u_int id;
        string name;
        bool isAlive, isActive;
        Particle* host_particle;
        int max_dist;
        int min_dist; 
        int timer;
        float weigth_fact;
        World* world;
        Particles_Container* actuated_particles;
        Interaction(Particle* _host_particle);
        virtual void run();
        virtual void interact(Particle* actuated_particle);
};

class Electrical_Repulsion : public Interaction{
    public:
        Electrical_Repulsion(Particle* _host_particle);
        void interact(Particle* actuated_particle);
};

class Electrical_Attraction : public Interaction{
    public:
        Electrical_Attraction(Particle* _host_particle);
        void interact(Particle* actuated_particle);
};

class Wave_Source : public Interaction{
    public:
        int wave_speed;
        float weight,weight_fact;

        Wave_Source(Particle* _host_particle);
        void interact(Particle* actuated_particle);
        void run();
};

/*
class Interaction_IV : public Interaction{
    public:
        ofVec3f temp_loc;
        //vector <Interaction_III> generated_interactions;
        Interaction_IV(Particle* _host_particle);
        void interact(Particle* actuated_particle);
};
*/

class Interactions_Container : public Pointers_Container<Interaction*>{
    public:
        Interaction* add_itemByName(string iName, Particle* init_props);
};

