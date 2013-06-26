template <typename IType>
class Pointers_Container{
    public:
        string name;
        int id;
        string default_addedItemName;
        vector<IType> itemsVector;
        vector<int> freeIdBuff;

        void set_default_itemName(string iName);
        void add(IType item,bool mainContainer=true);
        //virtual void del(IType item);
        virtual IType add_itemByName(string iName, Particle* _host_particle);
        virtual IType add_itemByName(string iName, World* _world);
        IType pop(u_int index=(u_int)NULL, bool erase=true);
        IType pop(typename vector<IType>::iterator item_it, bool erase=true);
        IType pop_itemById(int id, bool erase=true);
        IType get_itemById(int id);
        void show_items_name_and_id();
        vector <IType> pop_itemByName(string iName, bool erase=true);
        vector <IType> clear(bool erase=true);
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
IType Pointers_Container<IType>::add_itemByName(string iName, World* _world){
    return (int)NULL;
}

template <typename IType> 
IType Pointers_Container<IType>::add_itemByName(string iName,Particle* _host_particle){
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
    typename vector<IType>::iterator item_it;

    for (item_it = itemsVector.begin();
         item_it != itemsVector.end();
         item_it++){

        item = *item_it;
        if (iName.compare(item->name) == 0 || iName.compare("all") == 0){
            //cout<<" I.name:"<<item->name<<" I.id:"<<item->id<<endl;
            result.push_back(item);
        }
    }
    return result;
}

template <typename IType> 
IType Pointers_Container<IType>::pop(typename vector<IType>::iterator item_it, bool erase){
/*
Erase element from "itemsVector" pointers vector after
deallocate the respective memory using the "delete"
function. Also keep "id" value of each erased element
in "freeIdBuff" vector for future added items.
*/
    IType item; 
    if (item_it >= itemsVector.begin() && item_it < itemsVector.end() && itemsVector.size() > 0) {
        if (erase) {
            if ((**item_it).id < (int)(itemsVector.size() - 1)) {
                freeIdBuff.push_back((**item_it).id);
            }
            item = *item_it;
            delete item;
        }
        itemsVector.erase(item_it);
    }
    return *item_it;
}

template <typename IType> 
IType Pointers_Container<IType>::pop(u_int index, bool erase){
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
        if (erase) {
            if (item->id < (int)(itemsVector.size())) {
                freeIdBuff.push_back(item->id);
            }
            delete item;
        }
    }
    return item;
}

template <typename IType> 
void Pointers_Container<IType>::show_items_name_and_id(){
    typename vector<IType>::iterator item_it;

    for (item_it = itemsVector.begin();
         item_it != itemsVector.end();
         item_it++){

        cout<<"name:"<<(*item_it)->name<<" id:"<<(*item_it)->id<<endl;
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
        if (item->id == id){
            result = item;
            //cout<<"got item - name:"<<item->name<<"; id:"<<id<<endl;
            break;
        }
    }
    return result;
}

template <typename IType> 
IType Pointers_Container<IType>::pop_itemById(int id, bool erase){
    IType item;
    IType result = (int)NULL;
    typename vector<IType>::iterator item_it;

    for (item_it = itemsVector.begin();
         item_it != itemsVector.end();
         item_it++){

        item = *item_it;
        if (item->id == id){
            itemsVector.erase(item_it);
            if (erase){
                if (item->id < (int)itemsVector.size()) {
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
vector<IType> Pointers_Container<IType>::pop_itemByName(string iName, bool erase){
    IType item;
    typename vector<IType>::iterator item_it;
    vector<IType> result;
 
    if ( itemsVector.size() > 0){
        for (item_it = itemsVector.end() - 1;
             item_it >= itemsVector.begin();
             item_it--){

            item = *item_it;
            if (iName.compare(item->name) == 0) {
                itemsVector.erase(item_it);
                if (erase){
                    if (item->id < itemsVector.size()) {
                        freeIdBuff.push_back(item->id);
                    }
                    delete item;
                }
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
    typename vector<IType>::iterator item_it;
    vector<IType> result;
    result = itemsVector;

    if ( itemsVector.size() > 0){
        if (erase){
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

