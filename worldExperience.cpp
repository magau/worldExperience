#include "worldExperience.h"

BaseParticle::BaseParticle(){
    iType = "baseP";
}

DerivedParticle::DerivedParticle(){
    iType="derivedP";
}

Base_ParticlesSystem::Base_ParticlesSystem(){
    psType = "basePS";
    default_iType = "basePS";
}

Derived_ParticlesSystem::Derived_ParticlesSystem(){
    psType = "derivedPS";
    default_iType = "basePS";
}

template <class IType>
//IType handles the "BaseParticle" class and all their derived classes.
void Base_ParticlesSystem::add(IType item){
    itemsVector.push_back(item);
    if (freeIdBuff.size() > 0){
        itemsVector.back()->id = freeIdBuff.back();
        freeIdBuff.pop_back();
    } else {
        itemsVector.back()->id = itemsVector.size() - 1;
    }
}

void Base_ParticlesSystem::add_itemByType(string iType){
   if (iType.size() == 0){
       iType = default_iType;
       cout<<"default iType:"<<default_iType<<endl;
   } 

   if (iType.compare("baseP") == 0){
       add(new BaseParticle());
       //cout<<"add item, iType:"<<iType<<endl;
   } else if (iType.compare("derivedP") == 0){
       add(new DerivedParticle());
       //cout<<"add item, iType:"<<iType<<endl;
   }
   /*
    .
    .
    .
       Add new item types
   */
}

void Base_ParticlesSystem::set_default_pType(string iType){
    default_iType = iType;
}

vector <BaseParticle*> Base_ParticlesSystem::get_itemsByType(string iType){
    vector<BaseParticle*> result;
    BaseParticle* item;
    vector<BaseParticle*>::iterator particle_it;

    cout<<"psType:"<<psType<<endl;
    for (particle_it = itemsVector.begin();
         particle_it != itemsVector.end();
         particle_it++){

        item = *particle_it;
        if (iType.compare(item->iType) == 0 || iType.compare("all") == 0){
            cout<<" P.iType:"<<item->iType<<" P.id:"<<item->id<<endl;
            result.push_back(item);
        }
    }
    return result;
}

void Base_ParticlesSystem::pop(int index){
/*
Erase element from "itemsVector" pointers vector after
deallocate the respective memory using the "delete"
function. Also keep "id" value of each erased element
in "freeIdBuff" vector for future added items.
*/
    BaseParticle* item = itemsVector[index];

    if (index >= 0 && index < itemsVector.size()) {
        if (item->id < itemsVector.size() - 1) {
            freeIdBuff.push_back(item->id);
        }
        delete item;
        itemsVector.erase(itemsVector.begin() + index);
    }
}

void Base_ParticlesSystem::pop_itemById(int id){
    BaseParticle* item;
    vector<BaseParticle*>::iterator particle_it;

    for (particle_it = itemsVector.end() - 1;
         particle_it >= itemsVector.begin();
         particle_it--){

        item = *particle_it;
        if (item->id == id){
            if (item->id < itemsVector.size() - 1) {
                freeIdBuff.push_back(id);
            }
            delete item;
            itemsVector.erase(particle_it);
            break;
        }
    }
}

void Base_ParticlesSystem::pop_itemByType(string iType){
    BaseParticle* item;
    vector<BaseParticle*>::iterator particle_it;
 
    for (particle_it = itemsVector.end() - 1;
         particle_it >= itemsVector.begin();
         particle_it--){

        item = *particle_it;
        if (iType.compare(item->iType) == 0) {
            if (item->id < itemsVector.size() - 1) {
                freeIdBuff.push_back(item->id);
            }
            delete item;
            itemsVector.erase(particle_it);
        }
    }
}


void Base_ParticlesSystem::reset_itemTypeById(int id, string iType){
    BaseParticle* item;
    vector<BaseParticle*>::iterator particle_it;

    if (iType.size() == 0){
       iType = default_iType;
       cout<<"default iType:"<<default_iType<<endl;
    } 

    for (particle_it = itemsVector.end() - 1;
         particle_it >= itemsVector.begin();
         particle_it--){

        item = *particle_it;
        if (item->id == id) {
            delete item;
            itemsVector.erase(particle_it);
            add_itemByType(iType);
            itemsVector.back()->id = id;
            break;
        }
    }
}

void Base_ParticlesSystem::clear(){
    BaseParticle* item;
    vector<BaseParticle*>::iterator particle_it;

    for (particle_it = itemsVector.end() - 1;
         particle_it >= itemsVector.begin();
         particle_it--){

        item = *particle_it;
        delete item;
    }
    itemsVector.clear();
    freeIdBuff.clear();
}

void Base_ParticlesSystem::setup(){
    for (int i=0;i<10;i++){
        if (i<5){
            add(new BaseParticle());
        } else {
            add(new DerivedParticle());
        }
    }
}


//void World::add(string psType,string iType){
//    if(psType.compare("basePS")){
//        base_particles_sys.push_back(Base_ParticlesSystem());
//        base_particles_sys.back().id = base_particles_sys.size() - 1;
//    }
//
//    if(iType.compare("baseP")){
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
    sys.pop_itemById(8);
    sys.get_itemsByType();
    sys.add(new BaseParticle());
    sys.add(new BaseParticle());
    sys.get_itemsByType();
    sys.pop_itemByType("baseP");
    sys.get_itemsByType();
    sys.add(new BaseParticle());
    sys.add(new BaseParticle());
    sys.add(new BaseParticle());
    sys.add(new BaseParticle());
    sys.add(new BaseParticle());
    sys.get_itemsByType();
    sys.pop_itemById(2);
    sys.get_itemsByType();
    sys.set_default_pType("derivedP");
    sys.add_itemByType();
    sys.add_itemByType();
    sys.add_itemByType();
    sys.add_itemByType();
    sys.get_itemsByType();
    sys.clear();
    sys.get_itemsByType();
    sys.add_itemByType();
    sys.add_itemByType("baseP");
    sys.get_itemsByType();
    sys.set_default_pType("baseP");
    sys.add_itemByType();
    sys.add_itemByType();
    sys.add_itemByType();
    sys.add_itemByType();
    sys.get_itemsByType();
    sys.reset_itemTypeById(5,"derivedP");
    sys.reset_itemTypeById(0);
    sys.get_itemsByType();
    cout<<"done"<<endl;
    
    //World world;
    //world.add("basePS","baseP");
    //cout<<"size world:"<<world.base_particles_sys.size()<<endl;
    //world.base_particles_sys.back().setup();
    //world.get_info();
}
