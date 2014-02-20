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
        virtual IType create_itemByName(string iName);
        IType pop(u_int index=(u_int)NULL, bool erase=false);
        void erase(u_int index=(u_int)NULL);
        IType pop(typename vector<IType>::iterator item_it, bool erase=false);
        void erase(typename vector<IType>::iterator item_it);
        IType pop_itemById(int id, bool erase=false);
        void erase_itemById(int id);
        IType get_itemById(int id);
        vector <IType> get_items();
        void show_items_name_and_id();
        vector <IType> pop_itemsByName(string iName, bool erase=false);
        void erase_itemsByName(string iName);
        vector <IType> clear(bool erase=false);
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
void Pointers_Container<IType>::add(IType item,bool mainContainer){
    itemsVector.push_back(item);
    // If 'mainContainer' is setted true we give an id number to the added item.
    // The mainContainer is setted true wen a particle is added to 'world.groups'.
    if (mainContainer) {
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
IType Pointers_Container<IType>::pop_itemById(int id, bool erase){
    IType item;
    IType result = (int)NULL;
    typename vector<IType>::iterator item_it;

    for (item_it = itemsVector.begin();
         item_it != itemsVector.end();
         item_it++){

        item = *item_it;
        if (item->get_id() == id){
            itemsVector.erase(item_it);
            if (erase){
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
    pop_itemById(id, true); 
}

template <typename IType> 
vector<IType> Pointers_Container<IType>::pop_itemsByName(string iName, bool erase){
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
                if (erase){
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
    pop_itemsByName(iName,true);
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

template <typename IType> 
void Pointers_Container<IType>::erase_all(){
    clear(true);
}
