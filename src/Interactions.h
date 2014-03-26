class Particles_Container;
class Tag;
class Tags_Container : public Pointers_Container<Tag*>{};

class Interaction : public Action {
    public:

        int max_dist;
        int min_dist; 
        int timer;
        float weigth_fact;
        Tags_Container actuated_tags;

        Interaction();
        virtual void run(Particle* _host_particle);
        virtual void interact(Particle* actuated_particle, Particle* _host_particle);
        void add_actuated_tag(Tag* tag);
        void remove_actuated_tag(Tag* tag);
        
    protected:
        Tag* tag;
};

class Electrical_Repulsion : public Interaction{
    public:
        Electrical_Repulsion();
        void add_listener(string var_name);
        void interact(Particle* actuated_particle, Particle* _host_particle);
};

class Electrical_Attraction : public Interaction{
    public:
        Electrical_Attraction();
        void interact(Particle* actuated_particle, Particle* _host_particle);
};

class Wave_Source : public Interaction{
    public:
        int wave_speed;
        float weight,weight_fact;

        Wave_Source();
        void interact(Particle* actuated_particle, Particle* _host_particle);
        void run(Particle* _host_particle);
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
