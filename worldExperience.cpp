#include <iostream>
#include <vector>
#include <string>
#include <iterator>

using namespace std;

class Particle{
    public:
        string pType;
        int id;
        Particle ();
};

Particle::Particle(){
    pType = "baseParticle";
}

class DerivedParticle : public Particle{
    public:
        DerivedParticle();
};

DerivedParticle::DerivedParticle(){
    pType="derivedParticle";
}

class Particle_System{
    public:
        string psType;
        int id;
        vector<Particle> particles;
        vector<DerivedParticle> derived_particles;
        Particle_System();
        void get_info();
        void add_particle();
        void add_derived_particle();
};

Particle_System::Particle_System(){
    psType = "baseParticleSystem";
}

void Particle_System::get_info(){

    for (vector<Particle>::iterator particle=particles.begin(); particle != particles.end(); particle++){
        cout<<"psType:"<<psType<<" P.pType:"<<particle->pType<<" P.id:"<<particle->id<<endl;
    }

    for (vector<DerivedParticle>::iterator particle=derived_particles.begin(); particle != derived_particles.end(); particle++){
        cout<<"psType:"<<psType<<" P.pType:"<<particle->pType<<" P.id:"<<particle->id<<endl;
    }
}

void Particle_System::add_particle(){
    particles.push_back(Particle());
    particles.back().id = particles.size() - 1;
}

void Particle_System::add_derived_particle(){
    derived_particles.push_back(DerivedParticle());
    derived_particles.back().id = derived_particles.size() - 1;
}

main(){
    Particle_System pSys;
    
    for (int i=0;i<10;i++){
        pSys.add_particle();
        pSys.add_derived_particle();
    }

    pSys.get_info();
 
}
