class Particles_Container;

class Tag;
class Tags_Container : public Pointers_Container<Tag*>{};

class Interaction {
    public:
        int id;
        string name;
        bool isAlive, isActive;
        Particle* host_particle;
        int max_dist;
        int min_dist; 
        int timer;
        float weigth_fact;
        World* world;
        Particles_Container* actuated_particles;
        Tags_Container actuated_tags;
        Interaction();
        Interaction(Particle* _host_particle);
        virtual void setup(Particle* _host_particle);
        virtual void free(Particle* _host_particle);
        virtual void run(Particle* _host_particle=(Particle*)NULL);
        virtual void interact(Particle* actuated_particle, Particle* _host_particle=(Particle*)NULL);
        void add_tag(Tag* tag);
        void remove_tag(Tag* tag);
        void remove_tag_by_name(string tag_name);
};

class Electrical_Repulsion : public Interaction{
    public:
        Electrical_Repulsion();
        Electrical_Repulsion(Particle* _host_particle);
        void interact(Particle* actuated_particle, Particle* _host_particle=(Particle*)NULL);
};

class Electrical_Attraction : public Interaction{
    public:
        Electrical_Attraction();
        Electrical_Attraction(Particle* _host_particle);
        void interact(Particle* actuated_particle, Particle* _host_particle=(Particle*)NULL);
};

class Wave_Source : public Interaction{
    public:
        int wave_speed;
        float weight,weight_fact;

        Wave_Source();
        Wave_Source(Particle* _host_particle);
        void interact(Particle* actuated_particle, Particle* _host_particle=(Particle*)NULL);
        void run(Particle* _host_particle=(Particle*)NULL);
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
        Interaction* add_itemByName(string iName, Particle* host_particle=(Particle*)NULL);
};

