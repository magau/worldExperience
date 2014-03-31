//class Particles_Container;
//class Tags_Container;

class Particle : public Item {
    public:
        ofVec3f locat, veloc, accel;
        ofColor color;
        int rad;
        float relax_fact;

        Tags_Container tags;

        Particle ();
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



