class World;

class Particle_props{
    public:
        ofVec3f locat;
        ofVec3f veloc;
        ofVec3f accel;
        ofColor color;
        int rad;
        float relax_threshold;
        float relax_fact;
        bool isAlive;
        Particle_props();
        World* world;
};
