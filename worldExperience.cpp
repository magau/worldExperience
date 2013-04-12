#include "worldExperience.h"

BaseParticle::BaseParticle(){
    name = "baseP";
}

DerivedParticle::DerivedParticle(){
    name="derivedP";
}

template <typename IType> 
//IType handles the "BaseParticle" class and all their derived classes.
Base_ItemsSystem<IType>::Base_ItemsSystem(){
    name = "baseIS";
    default_addedItemName = "baseI";
}

template <typename IType> 
void Base_ItemsSystem<IType>::add(IType item){
    itemsVector.push_back(item);
    if (freeIdBuff.size() > 0){
        itemsVector.back()->id = freeIdBuff.back();
        freeIdBuff.pop_back();
    } else {
        itemsVector.back()->id = itemsVector.size() - 1;
    }
}

template <typename IType> 
void Base_ItemsSystem<IType>::add_itemByName(string iName){

}

template <typename IType> 
void Base_ItemsSystem<IType>::set_default_itemName(string iName){
    default_addedItemName = iName;
}

template <typename IType> 
vector <IType> Base_ItemsSystem<IType>::get_itemsByName(string iName){
    vector<IType> result;
    IType item;
    typename vector<IType>::iterator particle_it;

    cout<<"IS.name:"<<name<<endl;
    for (particle_it = itemsVector.begin();
         particle_it != itemsVector.end();
         particle_it++){

        item = *particle_it;
        if (iName.compare(item->name) == 0 || iName.compare("all") == 0){
            cout<<" I.name:"<<item->name<<" I.id:"<<item->id<<endl;
            result.push_back(item);
        }
    }
    return result;
}


template <typename IType> 
void Base_ItemsSystem<IType>::pop(int index){
/*
Erase element from "itemsVector" pointers vector after
deallocate the respective memory using the "delete"
function. Also keep "id" value of each erased element
in "freeIdBuff" vector for future added items.
*/

    if (index >= 0 && index < itemsVector.size() && itemsVector.size() > 0) {
        IType item = itemsVector[index];
        if (item->id < itemsVector.size() - 1) {
            freeIdBuff.push_back(item->id);
        }
        delete item;
        itemsVector.erase(itemsVector.begin() + index);
    }
}

template <typename IType> 
void Base_ItemsSystem<IType>::pop_itemById(int id){
    IType item;
    typename vector<IType>::iterator particle_it;

    for (particle_it = itemsVector.begin();
         particle_it != itemsVector.end();
         particle_it++){

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

template <typename IType> 
void Base_ItemsSystem<IType>::pop_itemByName(string iName){
    IType item;
    typename vector<IType>::iterator particle_it;
 
    if ( itemsVector.size() > 0){
        for (particle_it = itemsVector.end() - 1;
             particle_it >= itemsVector.begin();
             particle_it--){

            item = *particle_it;
            if (iName.compare(item->name) == 0) {
                if (item->id < itemsVector.size() - 1) {
                    freeIdBuff.push_back(item->id);
                }
                delete item;
                itemsVector.erase(particle_it);
            }
        }
    }
}


template <typename IType> 
void Base_ItemsSystem<IType>::reset_itemTypeById(int id, string iName){
    IType item;
    typename vector<IType>::iterator particle_it;

    if (iName.size() == 0){
       iName = default_addedItemName;
       cout<<"default added Item name:"<<default_addedItemName<<endl;
    } 

    for (particle_it = itemsVector.begin();
         particle_it != itemsVector.end();
         particle_it++){

        item = *particle_it;
        if (item->id == id) {
            delete item;
            itemsVector.erase(particle_it);
            add_itemByName(iName);
            itemsVector.back()->id = id;
            break;
        }
    }
}

template <typename IType> 
void Base_ItemsSystem<IType>::clear(){
    IType item;
    typename vector<IType>::iterator particle_it;


    if ( itemsVector.size() > 0){
        for (particle_it = itemsVector.end() - 1;
             particle_it >= itemsVector.begin();
             particle_it--){

            item = *particle_it;
            delete item;
        }
        itemsVector.clear();
        freeIdBuff.clear();
    }
}

template <class IType> 
void Base_ItemsSystem<IType>::setup(){

}

template <class IType> 
void Base_ItemsSystem<IType>::update(){

}

template <class IType> 
void Base_ItemsSystem<IType>::run(){

}

Base_ParticlesSystem::Base_ParticlesSystem(){
    name = "basePS";
    default_addedItemName = "baseP";
}

void Base_ParticlesSystem::add_itemByName(string iName){
   if (iName.size() == 0){
       iName = default_addedItemName;
       cout<<"default name:"<<default_addedItemName<<endl;
   } 

   if (iName.compare("baseP") == 0){
       add(new BaseParticle());
       //cout<<"add item, iName:"<<iName<<endl;
   } else if (iName.compare("derivedP") == 0){
       add(new DerivedParticle());
       //cout<<"add item, iName:"<<iName<<endl;
   }
   /*
    .
    .
    .
       Add new item types
   */
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

Derived_ParticlesSystem::Derived_ParticlesSystem(){
    name = "derivedPS";
    default_addedItemName = "baseP";
}

Base_World::Base_World(){
    name = "baseW";
    default_addedItemName = "basePS";
}

void Base_World::add_itemByName(string iName){
   if (iName.size() == 0){
       iName = default_addedItemName;
       cout<<"default name:"<<default_addedItemName<<endl;
   } 

   if (iName.compare("basePS") == 0){
       add(new Base_ParticlesSystem());
       //cout<<"add item, iName:"<<iName<<endl;
   } else if (iName.compare("derivedPS") == 0){
       add(new Derived_ParticlesSystem());
       //cout<<"add item, iName:"<<iName<<endl;
   }
   /*
    .
    .
    .
       Add new item types
   */
}

main(){
    
    Base_ParticlesSystem sys;
    sys.setup();
    sys.pop_itemById(8);
    sys.get_itemsByName();
    sys.add(new BaseParticle());
    sys.get_itemsByName();
    sys.pop_itemByName("baseP");
    sys.get_itemsByName();
    sys.add(new DerivedParticle());
    sys.get_itemsByName();
    sys.pop_itemById(2);
    sys.get_itemsByName();
    sys.add_itemByName("derivedP");
    sys.set_default_itemName("derivedP");
    sys.add_itemByName();
    sys.get_itemsByName();
    sys.clear();
    sys.get_itemsByName();
    sys.add_itemByName();
    sys.add_itemByName();
    sys.add_itemByName();
    sys.get_itemsByName();
    sys.reset_itemTypeById(2,"baseP");
    sys.set_default_itemName("baseP");
    sys.reset_itemTypeById(0);
    sys.get_itemsByName();

    cout<<"world..."<<endl;
    Base_World myWorld;
    myWorld.add(&sys);
    myWorld.get_itemsByName()[0]->get_itemsByName();
    cout<<"done"<<endl;
    
    //World world;
    //world.add("basePS","baseP");
    //cout<<"size world:"<<world.base_particles_sys.size()<<endl;
    //world.base_particles_sys.back().setup();
    //world.get_info();
}
