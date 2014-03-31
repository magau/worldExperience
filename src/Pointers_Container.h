class Particle;
class Action;
class Tag;

template <typename IType>
class Pointers_Container{
    public:
        string name;
        int id;
        bool isMainContainer;
        string default_addedItemName;
        vector<IType> itemsVector;
        vector<int> freeIdBuff;
        Pointers_Container();
        Pointers_Container(bool isMainContainer);
        Pointers_Container(const Pointers_Container& ptr_container);
        Pointers_Container<IType>& operator=(Pointers_Container& ptr_container);
        void set_default_itemName(string iName);
        void add(IType item);
        virtual IType create_itemByName(string iName);
        IType pop(u_int index=(u_int)NULL);
        void erase(u_int index=(u_int)NULL);
        IType pop(typename vector<IType>::iterator item_it);
        void erase(typename vector<IType>::iterator item_it);
        IType pop_itemById(int id);
        void erase_itemById(int id);
        IType get_itemById(int id);
        vector <IType> get_items();
        void show_items_name_and_id();
        vector <IType> pop_itemsByName(string iName);
        void erase_itemsByName(string iName);
        vector <IType> clear();
        void erase_all();
        vector <IType> get_itemsByName(string iName="all");
        /*
         "reset_itemTypeById" should be implemented in order to replace
         old items by newers of diferent types, passing the properties
         you plane to keep with from one to the other.
        virtual void reset_itemTypeById(int id, string iName="");
        */
};

/*
template <typename IType> 
//IType handles the "BaseParticle" class and all their derived classes.
Pointers_Container<IType>::Pointers_Container(){
    //name = "baseIS";
    //default_addedItemName = "baseI";
}
*/

template <typename IType> 
Pointers_Container<IType>& Pointers_Container<IType>::operator=(Pointers_Container<IType>& ptr_container){
    name = ptr_container.name;
    id = ptr_container.id;
    isMainContainer = ptr_container.isMainContainer;
    itemsVector = ptr_container.itemsVector;
    freeIdBuff = ptr_container.freeIdBuff;
    return *this;
}

template <typename IType> 
Pointers_Container<IType>::Pointers_Container(const Pointers_Container& ptr_container){
    name = ptr_container.name;
    id = ptr_container.id;
    isMainContainer = ptr_container.isMainContainer;
    itemsVector = ptr_container.itemsVector;
    freeIdBuff = ptr_container.freeIdBuff;
}

template <typename IType> 
Pointers_Container<IType>::Pointers_Container(){
    isMainContainer=true;
}

template <typename IType> 
Pointers_Container<IType>::Pointers_Container(bool _isMainContainer){
    isMainContainer = _isMainContainer;
}

template <typename IType> 
void Pointers_Container<IType>::add(IType item){
    itemsVector.push_back(item);
    // If 'mainContainer' is setted true we give an id number to the added item.
    // The mainContainer is setted true wen a particle is added to 'world.groups'.
    if (isMainContainer) {
        if (freeIdBuff.size() > 0){
            itemsVector.back()->set_id(freeIdBuff.back());
            freeIdBuff.pop_back();
        } else {
            itemsVector.back()->set_id(itemsVector.size() - 1);
        }
    }
}

template <typename IType> 
IType Pointers_Container<IType>::create_itemByName(string iName){
    return (int)NULL;
}

template <typename IType> 
void Pointers_Container<IType>::set_default_itemName(string iName){
    default_addedItemName = iName;
}

template <typename IType> 
vector<IType> Pointers_Container<IType>::get_items(){
    return itemsVector;
}

template <typename IType> 
vector <IType> Pointers_Container<IType>::get_itemsByName(string iName){
    vector<IType> result;
    IType item;
    typename vector<IType>::iterator item_it;

    for (item_it = itemsVector.begin();
         item_it != itemsVector.end();
         item_it++){

        item = *item_it;
        if (iName.compare(item->get_name()) == 0 || iName.compare("all") == 0){
            //cout<<" I.name:"<<item->name<<" I.id:"<<item->id<<endl;
            result.push_back(item);
        }
    }
    return result;
}

template <typename IType> 
IType Pointers_Container<IType>::pop(typename vector<IType>::iterator item_it){
/*
Erase element from "itemsVector" pointers vector after
deallocate the respective memory using the "delete"
function. Also keep "id" value of each erased element
in "freeIdBuff" vector for future added items.
*/
    IType item; 
    if (item_it >= itemsVector.begin() && item_it < itemsVector.end() && itemsVector.size() > 0) {
        if (isMainContainer) {
            if ((*item_it)->get_id() < (int)(itemsVector.size() - 1)) {
                freeIdBuff.push_back((*item_it)->get_id());
            }
            item = *item_it;
            delete item;
        }
        itemsVector.erase(item_it);
    }
    return *item_it;
}

template <typename IType>
void Pointers_Container<IType>::erase(typename vector<IType>::iterator item_it){
/*
 * Erase element from "itemsVector" pointers vector after
 * deallocate the respective memory using the "delete"
 * function. Also keep "id" value of each erased element
 * in "freeIdBuff" vector for future added items.
 * */
    pop(item_it,true);
}

template <typename IType> 
IType Pointers_Container<IType>::pop(u_int index){
/*
Erase element from "itemsVector" pointers vector after
deallocate the respective memory using the "delete"
function. Also keep "id" value of each erased element
in "freeIdBuff" vector for future added items.
*/

    IType item = (int)NULL;

    if (index >= 0 && index < itemsVector.size() && itemsVector.size() > 0) {
        item = itemsVector[index];
        itemsVector.erase(itemsVector.begin() + index);
        if (isMainContainer) {
            if (item->get_id() < (int)(itemsVector.size())) {
                freeIdBuff.push_back(item->get_id());
            }
            delete item;
        }
    }
    return item;
}

template <typename IType> 
void Pointers_Container<IType>::erase(u_int index){
/*
Erase element from "itemsVector" pointers vector after
deallocate the respective memory using the "delete"
function. Also keep "id" value of each erased element
in "freeIdBuff" vector for future added items.
*/
    pop(index,true);
}

template <typename IType> 
void Pointers_Container<IType>::show_items_name_and_id(){
    typename vector<IType>::iterator item_it;

    for (item_it = itemsVector.begin();
         item_it != itemsVector.end();
         item_it++){

        cout<<"name:"<<(*item_it)->get_name()<<" id:"<<(*item_it)->get_id()<<endl;
    }

}

template <typename IType> 
IType Pointers_Container<IType>::get_itemById(int id){
    IType item;
    IType result = (int)NULL;
    typename vector<IType>::iterator item_it;

    for (item_it = itemsVector.begin();
         item_it != itemsVector.end();
         item_it++){

        item = *item_it;
        if (item->get_id() == id){
            result = item;
            //cout<<"got item - name:"<<item->name<<"; id:"<<id<<endl;
            break;
        }
    }
    return result;
}

template <typename IType> 
IType Pointers_Container<IType>::pop_itemById(int id){
    IType item;
    IType result = (int)NULL;
    typename vector<IType>::iterator item_it;

    for (item_it = itemsVector.begin();
         item_it != itemsVector.end();
         item_it++){

        item = *item_it;
        if (item->get_id() == id){
            itemsVector.erase(item_it);
            if (isMainContainer){
                if (item->get_id() < (int)itemsVector.size()) {
                    freeIdBuff.push_back(id);
                }
                delete item;
            } else {
                result = item;
            }
            break;
        }
    }
    return result;
}

template <typename IType> 
void Pointers_Container<IType>::erase_itemById(int id){
    pop_itemById(id); 
}

template <typename IType> 
vector<IType> Pointers_Container<IType>::pop_itemsByName(string iName){
    IType item;
    typename vector<IType>::iterator item_it;
    vector<IType> result;
 
    if ( itemsVector.size() > 0){
        for (item_it = itemsVector.end() - 1;
             item_it >= itemsVector.begin();
             item_it--){

            item = *item_it;
            if (iName.compare(item->get_name()) == 0) {
                itemsVector.erase(item_it);
                if (isMainContainer){
                    if (item->get_id() < (int)itemsVector.size()) {
                        freeIdBuff.push_back(item->get_id());
                    }
                    delete item;
                }
                result.push_back(item);
            }
        }
    }
    return result;
}


template <typename IType> 
void Pointers_Container<IType>::erase_itemsByName(string iName){
    pop_itemsByName(iName);
}

/*
template <typename IType> 
void Pointers_Container<IType>::reset_itemTypeById(int id, string iName){
    IType item;
    typename vector<IType>::iterator item_it;
    Particle_props init_props;

    if (iName.size() == 0){
       iName = default_addedItemName;
       cout<<"default added name:"<<default_addedItemName<<endl;
    } 

    for (item_it = itemsVector.begin();
         item_it != itemsVector.end();
         item_it++){

        item = *item_it;
        if (item->id == id) {
            init_props = item->props;
            delete item;
            itemsVector.erase(item_it);
            create_itemByName(iName,init_props);
            itemsVector.back()->id = id;
            break;
        }
    }
}
*/

template <typename IType> 
vector<IType> Pointers_Container<IType>::clear(){
    IType item;
    typename vector<IType>::iterator item_it;
    vector<IType> result;
    result = itemsVector;

    if ( itemsVector.size() > 0){
        if (isMainContainer){
            for (item_it = itemsVector.end() - 1;
                 item_it >= itemsVector.begin();
                 item_it--){

                item = *item_it;
                delete item;
            }
            freeIdBuff.clear();
        }
        itemsVector.clear();
    }
    return result; 
}

template <typename IType> 
void Pointers_Container<IType>::erase_all(){
    clear();
}

class Particles_Container : public Pointers_Container<Particle*>{
    public:
        Particles_Container() : Pointers_Container<Particle*>(){};
        Particles_Container(bool isMainContainer) : Pointers_Container<Particle*>(isMainContainer){};
        //Particle* create_itemByName(string iName);
};

//Particle* Particles_Container::create_itemByName(string iName){
//
//    Items_Fabric nature;
//    if (iName.size() == 0)
//        iName = default_addedItemName;
//    Particle* newParticle = nature.create_particle(iName);
//    add(newParticle);
//
//    return newParticle;
//
//}

class Tags_Container : public Pointers_Container<Tag*> {
    public:
    Tags_Container() : Pointers_Container<Tag*>(){};
    Tags_Container(bool isMainContainer) : Pointers_Container<Tag*>(isMainContainer){};
};


class Actions_Container : public Pointers_Container<Action*>{
    public:
    Actions_Container() : Pointers_Container<Action*>(){};
    Actions_Container(bool isMainContainer) : Pointers_Container<Action*>(isMainContainer){};
};
