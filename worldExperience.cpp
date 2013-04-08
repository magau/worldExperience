#include "worldExperience.h"

BaseParticle::BaseParticle(){
    pType = "baseP";
}

DerivedParticle::DerivedParticle(){
    pType="derivedP";
}

Base_ParticlesSystem::Base_ParticlesSystem(){
    psType = "basePS";
}

Derived_ParticlesSystem::Derived_ParticlesSystem(){
    psType = "derivedPS";
}

vector <BaseParticle*> Base_ParticlesSystem::get_particlesByName(string pType){
    vector <BaseParticle*> result;
    BaseParticle* particle;

    cout<<"psType:"<<psType<<endl;
    for (vector <BaseParticle*>::iterator particle_it = particles.begin();
                                           particle_it != particles.end();
                                                            particle_it++){
        particle = *particle_it;
        if (pType.compare(particle->pType) == 0 || pType.compare("all") == 0){
            cout<<" P.pType:"<<particle->pType<<" P.index:"<<particle->index<<endl;
            result.push_back(particle);
        }
    }
    return result;
}

void Base_ParticlesSystem::pop_particle(string pType){
    BaseParticle* particle;
    int nErase;
    int pNum;
    bool eraseAll;
 
    if(pType.compare("all") == 0){
        eraseAll = true;
        nErase = particles.size();
    } else {
        nErase = get_particlesByName(pType).size();
        if (nErase == particles.size()){
            eraseAll = true;
        } else {
            eraseAll = false;
        }
    }

    pNum = 0;
    for (vector <BaseParticle*>::iterator particle_it = particles.end() - 1;
                          particle_it >= particles.begin() && nErase > pNum;
                                                            particle_it--){
        particle = *particle_it;
        if ( eraseAll || pType.compare(particle->pType) == 0){
            delete particle;
            if (!eraseAll) {
                particles.erase(particle_it);
                pNum++;
            }
        } else if (!eraseAll) {
            particle->index--;
        }
    }
    if (eraseAll) particles.clear();
}


void Base_ParticlesSystem::pop_particle(int index){
    BaseParticle* particle;

    if (index == (int)NULL || index == particles.size() - 1) {
        delete particles.back();
        particles.pop_back();
    } else {
        for (vector <BaseParticle*>::iterator particle_it = particles.end() - 1;
                                               particle_it >= particles.begin() + index;
                                                                particle_it--){
            particle = *particle_it;
            if (index == particle->index){
                delete particle;
                particles.erase(particle_it);
            } else {
                particle->index--;
            }
        }
    }
}


template <class PType>
//PType handles the "BaseParticle" class and all their derived classes.
void Base_ParticlesSystem::add_particle(PType particle){
    particles.push_back(particle);
    particles.back()->index = particles.size() - 1;
}

void Base_ParticlesSystem::setup(){
    for (int i=0;i<10;i++){
        if (i<5){
            add_particle(new BaseParticle());
        } else {
            add_particle(new DerivedParticle());
        }
    }
}


//void World::add_particles_system(string psType,string pType){
//    if(psType.compare("basePS")){
//        base_particles_sys.push_back(Base_ParticlesSystem());
//        base_particles_sys.back().index = base_particles_sys.size() - 1;
//    }
//
//    if(pType.compare("baseP")){
//        base_particles_sys.back().
//    }
//}
//
//void World::get_info(string psType){
//    for (vector<Base_ParticlesSystem>::iterator particles_sys=base_particles_sys.begin(); particles_sys != base_particles_sys.end(); particles_sys++){
//        particles_sys->get_info();
//    }
//}

main(){
    

    Base_ParticlesSystem sys;
    sys.setup();
    sys.get_particlesByName();
    sys.pop_particle(3);
    sys.get_particlesByName();
    sys.pop_particle("derivedP");
    sys.get_particlesByName();
    sys.pop_particle("all");
    sys.get_particlesByName();
    sys.add_particle(new DerivedParticle());
    sys.add_particle(new BaseParticle());
    sys.get_particlesByName();
    cout<<"done"<<endl;
    
    //World world;
    //world.add_particles_system("basePS","baseP");
    //cout<<"size world:"<<world.base_particles_sys.size()<<endl;
    //world.base_particles_sys.back().setup();
    //world.get_info();
}
