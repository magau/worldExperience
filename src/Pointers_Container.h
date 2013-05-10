#include "ofMain.h"

class Particle_props{
    public:
        ofVec3f locat;
        ofVec3f veloc;
        ofVec3f accel;
        ofPoint loc;
        ofPoint vel;
        ofPoint acc;
        ofColor color;
        int rad;
        float relax_threshold;
        float relax_fact;
        bool isAlive;
        Particle_props();
};

template <typename IType>
class Pointers_Container{
    public:
        string name;
        int id;
        //Particle_props props;
        string default_addedItemName;
        vector<IType> itemsVector;
        vector<int> freeIdBuff;

        void set_default_itemName(string iName);
        void add(IType item,bool mainContainer=true);
        virtual IType add_itemByName(string iName, Particle_props* host_props);
        virtual IType add_itemByName(string iName, Particle_props init_props);
        IType pop(int index=(int)NULL, bool erase=true);
        IType pop_itemById(int id, bool erase=true);
        vector <IType> pop_itemByName(string iName, bool erase=true);
        vector <IType> clear(bool erase=true);
        vector <IType> get_itemsByName(string iName="all");
        /*
        virtual void setup();
        virtual void update();
        virtual void run();
         "reset_itemTypeById" should be implemented in order to replace
         old items by newers of diferent types, passing the properties
         you plane to keep with from one to the other.
        virtual void reset_itemTypeById(int id, string iName="");
        */
};

/*
template <typename IType> 
//IType handles the "BaseParticle" class and all their derived classes.
Pointers_Container<IType>::Pointers_Container(Particle_props init_props){
    //name = "baseIS";
    props = init_props;
    //default_addedItemName = "baseI";
}
*/

template <typename IType> 
void Pointers_Container<IType>::add(IType item,bool mainContainer){
    itemsVector.push_back(item);
    if (mainContainer) {
        if (freeIdBuff.size() > 0){
            itemsVector.back()->id = freeIdBuff.back();
            freeIdBuff.pop_back();
        } else {
            itemsVector.back()->id = itemsVector.size() - 1;
        }
    }
}

template <typename IType> 
IType Pointers_Container<IType>::add_itemByName(string iName,Particle_props init_props){
    return (int)NULL;
}

template <typename IType> 
IType Pointers_Container<IType>::add_itemByName(string iName,Particle_props* host_props){
    return (int)NULL;

}

template <typename IType> 
void Pointers_Container<IType>::set_default_itemName(string iName){
    default_addedItemName = iName;
}

template <typename IType> 
vector <IType> Pointers_Container<IType>::get_itemsByName(string iName){
    vector<IType> result;
    IType item;
    typename vector<IType>::iterator particle_it;

    //cout<<"IS.name:"<<name<<endl;
    for (particle_it = itemsVector.begin();
         particle_it != itemsVector.end();
         particle_it++){

        item = *particle_it;
        if (iName.compare(item->name) == 0 || iName.compare("all") == 0){
            //cout<<" I.name:"<<item->name<<" I.id:"<<item->id<<endl;
            result.push_back(item);
        }
    }
    return result;
}

template <typename IType> 
IType Pointers_Container<IType>::pop(int index, bool erase){
/*
Erase element from "itemsVector" pointers vector after
deallocate the respective memory using the "delete"
function. Also keep "id" value of each erased element
in "freeIdBuff" vector for future added items.
*/

    IType item = (int)NULL;

    if (index >= 0 && index < itemsVector.size() && itemsVector.size() > 0) {
        item = itemsVector[index];
        if (erase) {
            if (item->id < itemsVector.size() - 1) {
                freeIdBuff.push_back(item->id);
            }
            delete item;
        }
        itemsVector.erase(itemsVector.begin() + index);
    }
    return item;
}

template <typename IType> 
IType Pointers_Container<IType>::pop_itemById(int id, bool erase){
    IType item;
    IType result = (int)NULL;
    typename vector<IType>::iterator particle_it;

    for (particle_it = itemsVector.begin();
         particle_it != itemsVector.end();
         particle_it++){

        item = *particle_it;
        if (item->id == id){
            if (erase){
                if (item->id < itemsVector.size() - 1) {
                    freeIdBuff.push_back(id);
                }
                delete item;
            } else {
                result = item;
            }
            itemsVector.erase(particle_it);
            break;
        }
    }
    return result;
}

template <typename IType> 
vector<IType> Pointers_Container<IType>::pop_itemByName(string iName, bool erase){
    IType item;
    typename vector<IType>::iterator particle_it;
    vector<IType> result;
 
    if ( itemsVector.size() > 0){
        for (particle_it = itemsVector.end() - 1;
             particle_it >= itemsVector.begin();
             particle_it--){

            item = *particle_it;
            if (iName.compare(item->name) == 0) {
                if (erase){
                    if (item->id < itemsVector.size() - 1) {
                        freeIdBuff.push_back(item->id);
                    }
                    delete item;
                }
                itemsVector.erase(particle_it);
                result.push_back(item);
            }
        }
    }
    return result;
}

/*
template <typename IType> 
void Pointers_Container<IType>::reset_itemTypeById(int id, string iName){
    IType item;
    typename vector<IType>::iterator particle_it;
    Particle_props init_props;

    if (iName.size() == 0){
       iName = default_addedItemName;
       cout<<"default added name:"<<default_addedItemName<<endl;
    } 

    for (particle_it = itemsVector.begin();
         particle_it != itemsVector.end();
         particle_it++){

        item = *particle_it;
        if (item->id == id) {
            init_props = item->props;
            delete item;
            itemsVector.erase(particle_it);
            add_itemByName(iName,init_props);
            itemsVector.back()->id = id;
            break;
        }
    }
}
*/

template <typename IType> 
vector<IType> Pointers_Container<IType>::clear(bool erase){
    IType item;
    typename vector<IType>::iterator particle_it;
    vector<IType> result;
    result = itemsVector;

    if ( itemsVector.size() > 0){
        if (erase){
            for (particle_it = itemsVector.end() - 1;
                 particle_it >= itemsVector.begin();
                 particle_it--){

                item = *particle_it;
                delete item;
            }
            freeIdBuff.clear();
        }
        itemsVector.clear();
    }
    return result; 
}

/*
template <class IType> 
void Pointers_Container<IType>::setup(){

}

template <class IType> 
void Pointers_Container<IType>::update(){

}

template <class IType> 
void Pointers_Container<IType>::run(){

}
*/


