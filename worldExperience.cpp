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

void Base_ParticlesSystem::pop_particle(int index){
 /*
 Erase element from "particles" pointers vector after
 deallocate the respective memory using the "delete"
 function. Also redefine the "index" value of each element
 below the erased element.
 */
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

void Base_ParticlesSystem::pop_particle(string pType){
 /*
 Erase elements from "particles" pointers vector after
 deallocate the respective memory using the "delete"
 function. Also redefine the "index" value of each element
 below the erased element.
 */

    BaseParticle* particle;
    vector <BaseParticle*> erase_particles;
    vector <BaseParticle*> :: iterator erase_it;
    int nErase;
    int pNum;
    int indexCorrection;
    bool eraseAll;
 
    if(pType.compare("all") == 0){
        eraseAll = true;
    } else {
        erase_particles = get_particlesByName(pType);
        nErase = erase_particles.size();
        if (nErase == particles.size()){
            eraseAll = true;
        } else {
            eraseAll = false;
        }
    }

    if (eraseAll) {
        for (vector <BaseParticle*>::iterator particle_it = particles.end() - 1;
                                               particle_it >= particles.begin();
                                                                 particle_it--){
            particle = *particle_it;
            delete particle;
        }
        particles.clear();
    } else {
        indexCorrection = nErase;
        pNum = 0;
        erase_it = erase_particles.end() - 1;
        for (vector <BaseParticle*>::iterator particle_it = particles.end() - 1;
                              particle_it >= particles.begin() && nErase > pNum;
                                                                particle_it--){
            particle = *particle_it;
            if ( particle->index == (*erase_it)->index ){
                delete particle;
                particles.erase(particle_it);
                pNum++;
                erase_it--;
                indexCorrection--;
            } else {
                particle->index -= indexCorrection;
            }
        }
    }
}

void Base_ParticlesSystem::clear_particles(){
    pop_particle("all");
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
    sys.add_particle(new BaseParticle());
    sys.add_particle(new BaseParticle());
    sys.get_particlesByName();
    sys.pop_particle(8);
    sys.get_particlesByName();
    sys.pop_particle("baseP");
    sys.get_particlesByName();
    sys.clear_particles();
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
