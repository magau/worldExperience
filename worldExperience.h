#include <iostream>
#include <vector>
#include <string>
#include <iterator>
using namespace std;

class BaseParticle{
    public:
        string pType;
        int index;
        BaseParticle ();
};

class DerivedParticle : public BaseParticle{
    public:
        DerivedParticle();
};

class Base_ParticlesSystem{
    public:
        int index;
        string psType;
        string default_pType;
        vector<BaseParticle*> particles;

        Base_ParticlesSystem();
        template <class PType>
        void add_particle(PType particle);
        void pop_particle(int index=(int)NULL);
        void pop_particle(string pType);
        void setup();
        vector <BaseParticle*> get_particlesByName(string pType="all");
};

class Derived_ParticlesSystem : public Base_ParticlesSystem{
    public:
        Derived_ParticlesSystem();
};

//class World{
//    public:
//    vector<Base_ParticlesSystem> base_particles_sys;
//    void add_particles_system(string psType="basePS",string pType="baseP");
//    void get_info(string psType="all");
//};


