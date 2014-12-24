class Particle;
class Action;
class Tag;

/*
 * BaseTypePtr is the Base class pointer of the contained objects.
 * The purpose of this container is to hold all the derived
 * classes pointer objects.
 * If the value of the "isMainContainer" member is set true,
 * the container becomes a "main container" and the manage of
 * the "id" member of the contained objects is assumed by the 
 * container and every erased object will be deleted from memory
 * (as the added pointer objects are suposed to be instanciated
 * by the "new" operator).
 * Also a set of "get_by" id, typeid, and name are available.
 */
template <typename BaseTypePtr>
class PointersVector : public vector<BaseTypePtr>{
    public:
        bool isMainContainer;

        PointersVector();
        PointersVector(bool _isMainContainer);
        PointersVector(const PointersVector& ptr_container);
        PointersVector<BaseTypePtr>& operator=(const PointersVector& ptr_container);
        void pop_back();
        typename vector<BaseTypePtr>::iterator erase(typename vector<BaseTypePtr>::iterator position);
        typename vector<BaseTypePtr>::iterator erase(typename vector<BaseTypePtr>::iterator first, typename vector<BaseTypePtr>::iterator last);
        void clear();
        void set_main_container(bool _isMainContainer);
        bool is_main_container() const;
        typename vector<BaseTypePtr>::iterator erase_item_by_id(BaseTypePtr item);
        void erase_items_by_typeid(const type_info& type_id);
        BaseTypePtr get_item_by_id(BaseTypePtr item);
        PointersVector<BaseTypePtr> get_items_by_typeid(const type_info& type_id);

        // This function is suposed to be used only for purpouse of debug.
        void show_items_name_and_id();

        /*
         "reset_itemTypeById" should be implemented in order to replace
         old items by newers of diferent types, passing the properties
         you plane to keep with from one to the other.
         virtual void reset_itemTypeById(Item* item_ptr, string iName="");
        */
};

template <typename BaseTypePtr> 
PointersVector<BaseTypePtr>::PointersVector() : vector<BaseTypePtr>() {
    isMainContainer = false;
}

template <typename BaseTypePtr> 
PointersVector<BaseTypePtr>::PointersVector(bool _isMainContainer) : vector<BaseTypePtr>() {
    isMainContainer = _isMainContainer;
}

template <typename BaseTypePtr> 
PointersVector<BaseTypePtr>::PointersVector(const PointersVector& ptr_container) {
    // Can't use the copy constructor between two "Main Containers".
    if( !(ptr_container.is_main_container() && isMainContainer) ) {
        typename PointersVector<BaseTypePtr>::const_iterator item_it; 
        for (item_it = ptr_container.begin(); item_it != ptr_container.end(); item_it++){
            vector<BaseTypePtr>::push_back(*item_it);
        }
    }
}

template <typename BaseTypePtr> 
PointersVector<BaseTypePtr>& PointersVector<BaseTypePtr>::operator=(const PointersVector<BaseTypePtr>& ptr_container){
    // Can't use the assign operator between two "Main Containers".
    if( !(ptr_container.is_main_container() && isMainContainer) ) {
        typename PointersVector<BaseTypePtr>::const_iterator item_it; 
        for (item_it = ptr_container.begin(); item_it != ptr_container.end(); item_it++){
            vector<BaseTypePtr>::push_back(*item_it);
        }
    }
    return *this;
}

template <typename BaseTypePtr>
typename vector<BaseTypePtr>::iterator PointersVector<BaseTypePtr>::erase(typename vector<BaseTypePtr>::iterator position){
/*
 * Erase element from "PointersVector" after deallocate
 * the respective memory using the "delete" function.
 */
    if (isMainContainer) {
        delete *position;
    }
    return vector<BaseTypePtr>::erase(position);
}

template <typename BaseTypePtr>
void PointersVector<BaseTypePtr>::pop_back() {
    if (isMainContainer) {
        delete vector<BaseTypePtr>::back();
    }
    vector<BaseTypePtr>::pop_back();
}

template <typename BaseTypePtr>
typename vector<BaseTypePtr>::iterator PointersVector<BaseTypePtr>::erase( typename vector<BaseTypePtr>::iterator first,
                                                               typename vector<BaseTypePtr>::iterator last ) {
/*
 * Call the "erase" method of the "PointersVector" class
 * for the elementes in the range between "first" and 
 * "last", including the element pointed by "first" but not
 * the one pointed by "last".
 */
    typename vector<BaseTypePtr>::iterator item_it; 
    if (isMainContainer) {
        for (item_it = last-1; item_it >= first; item_it--) {
            delete *item_it;
        }
    }
    vector<BaseTypePtr>::erase(first,last);
    return item_it+1;
}

template <typename BaseTypePtr>
void PointersVector<BaseTypePtr>::clear(){
    if (isMainContainer){
        typename vector<BaseTypePtr>::iterator item_it; 
        for (item_it = vector<BaseTypePtr>::begin();
             item_it < vector<BaseTypePtr>::end();
             item_it++){
            delete *item_it;
        }
    }
    vector<BaseTypePtr>::clear();
}

template <typename BaseTypePtr>
BaseTypePtr PointersVector<BaseTypePtr>::get_item_by_id(BaseTypePtr item) {
    typename vector<BaseTypePtr>::iterator item_it; 
    for (item_it = vector<BaseTypePtr>::begin(); item_it != vector<BaseTypePtr>::end(); item_it++) {
        if ((*item_it) == item)
            return *item_it;
    }
    return (BaseTypePtr)NULL;
}

template <typename BaseTypePtr>
typename vector<BaseTypePtr>::iterator PointersVector<BaseTypePtr>::erase_item_by_id(BaseTypePtr item) {
    typename vector<BaseTypePtr>::iterator item_it; 
    for (item_it = vector<BaseTypePtr>::begin(); item_it != vector<BaseTypePtr>::end(); item_it++) {
        if (*item_it == item)
            return erase(item_it);
    }
    return vector<BaseTypePtr>::end();
}

template <typename BaseTypePtr>
PointersVector<BaseTypePtr> PointersVector<BaseTypePtr>::get_items_by_typeid(const type_info& type_id) {
    PointersVector<BaseTypePtr> result;
    typename vector<BaseTypePtr>::iterator item_it; 
    for (item_it = vector<BaseTypePtr>::begin(); item_it != vector<BaseTypePtr>::end(); item_it++) {
        if ((*item_it)->get_typeid() == type_id)
            result.push_back(*item_it);
    }
    return result;
}

template <typename BaseTypePtr>
void PointersVector<BaseTypePtr>::erase_items_by_typeid(const type_info& type_id) {
    typename vector<BaseTypePtr>::iterator item_it; 
    for (item_it = vector<BaseTypePtr>::end()-1; item_it >= vector<BaseTypePtr>::begin(); item_it--) {
        if ((*item_it)->get_typeid() == type_id)
            erase(item_it);
    }
}

template <typename BaseTypePtr>
void PointersVector<BaseTypePtr>::set_main_container(bool _isMainContainer) {
    isMainContainer = _isMainContainer;
}

template <typename BaseTypePtr>
bool PointersVector<BaseTypePtr>::is_main_container() const {
    return isMainContainer;
}

template <typename BaseTypePtr> 
void PointersVector<BaseTypePtr>::show_items_name_and_id(){
    typename vector<BaseTypePtr>::iterator item_it;
    for (item_it = vector<BaseTypePtr>::begin(); item_it != vector<BaseTypePtr>::end(); item_it++) {
        cout<<"name:"<<(*item_it)->get_name()<<" id:"<<(long long)(*item_it)<<endl;
    }
}
