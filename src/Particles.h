class Particles_Container;

class Particle : public Item {
    public:
        ofVec3f locat, veloc, accel;
        ofColor color;
        int rad;
        float relax_fact;

        Tags_Container tags;

        Particle ();
        Particle (World* _world);
        ~Particle();

        virtual void setup();
        virtual void run();
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

