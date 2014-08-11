#include "testApp.h"

Item::Item(){
    //cout << "item constructor..." << endl;
    is_alive = Item_Parameter<bool>(true);
    is_active = Item_Parameter<bool>(true);
    set_variable("is_alive", &is_alive, IP_BOOL);
    set_variable("is_active", &is_active, IP_BOOL);
    set_name(get_type_name());
}

Item :: ~Item(){
    /* Delete added variables. */
    clear_variables();

    /* Remove this item from the
     * attached_buttons remove listeners
     * and clear buttons. */
    remove_attached_buttons(); 
}

const type_info& Item::get_typeid(){
    return typeid(this);
}

string Item::get_type_name(){
    regex pattern ("^P?[0-9]*(.*)"); 
    return regex_replace(string(get_typeid().name()), pattern, string("$1"));
};

string Item::get_name(){return name;}

void Item::print_shared_var_names(){
    unordered_map<shared_variable_key, shared_variable, shared_variable_hasher>::iterator var_it;
    for(var_it = shared_variables_map.begin();
        var_it != shared_variables_map.end(); var_it++) {
        cout << "var:" << var_it->first.name << "; host item:" << var_it->first.host_item->get_name() << endl;
    }
}

int    Item::get_id(){return id;}

World* Item::get_world(){return world;}

void   Item::set_name(string _name){name=_name;}

void   Item::set_id(int _id){id=_id;}

void   Item::set_world(World* _world){world=_world;}

void   Item::iterate_attribute(string attr_name, bool forward){}

void   Item :: setup(){}

void   Item :: run(){}

void* Item::create_var_ptr(arg_t type_enum){
    void* var_ptr = NULL;
    switch (type_enum) {
        case EVENT_SH_VAR:
            var_ptr = new ofEvent<pair<shared_variable_key,shared_variable>>;
            break;
        case IP_INT:
            var_ptr = new Item_Parameter<int>;
            break;
        case IP_FLOAT:
            var_ptr = new Item_Parameter<float>;
            break;
        case IP_BOOL:
            var_ptr = new Item_Parameter<bool>;
            break;
        case IP_VEC3F:
            var_ptr = new Item_Parameter<ofVec3f>;
            break;
        case IP_COLOR:
            var_ptr = new Item_Parameter<ofColor>;
            break;
        case BUTTON:
            var_ptr = new Button;
            break;
        case T_NULL:
            cout << "Can't create new variable! arg_t not defined for this type!!" << endl;
            break;
        default:
            cout << "Can't create new variable! arg_t not defined for this type!!" << endl;
            break;
    }
    return var_ptr;
}

void Item::erase_var_ptr(void* var_value, arg_t type_enum){
    switch (type_enum) {
        case EVENT_SH_VAR:
            delete static_cast<ofEvent<pair<shared_variable_key,shared_variable>>*>(var_value); 
            break;
        case IP_INT:
            delete static_cast<Item_Parameter<int>*>(var_value); 
            break;
        case IP_FLOAT:
            delete static_cast<Item_Parameter<float>*>(var_value); 
            break;
        case IP_BOOL:
            delete static_cast<Item_Parameter<bool>*>(var_value); 
            break;
        case IP_VEC3F:
            delete static_cast<Item_Parameter<ofVec3f>*>(var_value); 
            break;
        case IP_COLOR:
            delete static_cast<Item_Parameter<ofColor>*>(var_value); 
            break;
        case BUTTON:
            delete static_cast<Button*>(var_value);
            break;
        case T_NULL:
            cout << "arg_t not defined for this type!!" << endl;
            break;
        default:
            cout << "arg_t not defined for this type!!" << endl;
            break;
    }
}

void Item::set_variable(string var_name, void* var_ptr, arg_t type_enum, Item* host_item_ptr,
           unordered_map <shared_variable_key, shared_variable, shared_variable_hasher>* shvar_map_ptr){

    if (host_item_ptr == NULL)
        host_item_ptr = this;

    shared_variable_key key(var_name, host_item_ptr);

    // Add an existent poiter as a new element.
    bool is_new_var = false;

    // The input argument "shvar_map_ptr" can be used if
    // independent containes are required for the base Item.
    // The default container is the "shared_variables_map".
    if (shvar_map_ptr == NULL)
        shvar_map_ptr = &shared_variables_map;

    unordered_map <shared_variable_key, shared_variable, shared_variable_hasher>::iterator shvar_map_it = shvar_map_ptr->find(key);

    if (var_ptr == NULL) {
        // Create a new element.
        is_new_var = true;
        var_ptr = create_var_ptr(type_enum);
    }

    if (shvar_map_it == shvar_map_ptr->end()) {
        // Add element.
        (*shvar_map_ptr)[key] = shared_variable(var_ptr,type_enum,is_new_var);

        //cout << "add new variable:" << key.name << endl;
    } else if(type_enum == T_NULL) {
        // Enumerator arg_t not defined for this type.
        stringstream error_msg;
        error_msg << "Enumerator arg_t not defined for this type." <<
                     "; variable name:" << var_name;
        //throw runtime_error(error_msg.str());
        cout << error_msg.str() << endl;
    } else {
        // Replace element.
        //cout << "overwiting var:" << var_key << " value:" << old_var->value << endl;

        if (shvar_map_it->second.is_new) {
            erase_var_ptr(shvar_map_it->second.value,shvar_map_it->second.type_enum);
        }

        if(shvar_map_it->second.type_enum != type_enum) {
            // Element already exists with diferent arg_t.
            stringstream error_msg;
            error_msg << "Replacing variable of arg_t: " <<
                         shvar_map_it->second.type_enum << " by other of arg_t: " << type_enum <<
                         "; variable name: " << var_name;
            //throw runtime_error(error_msg.str());
            cout << error_msg.str() << endl;
            shvar_map_it->second.type_enum = type_enum;
        } 


        shvar_map_it->second.value = var_ptr;
        shvar_map_it->second.is_new = is_new_var;
    }

    //cout << "variable name:" << key.name << endl;
    //cout << "key.name: " << key.name << "; key.host_item->get_name():" << key.host_item->get_name() << endl;
    //cout << "shared_variables_map[key].type_enum: " << shared_variables_map[key].type_enum << "; shared_variables_map[key].is_new:" << shared_variables_map[key].is_new << endl;

}

shared_variable Item::get_variable(string var_name, Item* host_item_ptr,
           unordered_map <shared_variable_key, shared_variable, shared_variable_hasher>* shvar_map_ptr){

    shared_variable raw_value;

    if (host_item_ptr == NULL)
        host_item_ptr = this;
 
    shared_variable_key key(var_name, host_item_ptr);

    // The input argument "shvar_map_ptr" can be used if
    // independent containes are required for the base Item.
    // The default container is the "shared_variables_map".
    if (shvar_map_ptr == NULL)
        shvar_map_ptr = &shared_variables_map;


    unordered_map <shared_variable_key, shared_variable, shared_variable_hasher>::iterator shvar_map_it = shvar_map_ptr->find(key);

    if(shvar_map_it == shvar_map_ptr->end()) {
        // Element doesn't exists.
        stringstream error_msg;
        error_msg << "get undefined variable: " << var_name;
        cout << error_msg.str() << endl;
        //throw runtime_error(error_msg.str());
    } else {
        raw_value = shvar_map_it->second;
    }
    return raw_value;
}

void Item::erase_variable(string var_name, Item* host_item_ptr,
           unordered_map <shared_variable_key, shared_variable, shared_variable_hasher>* shvar_map_ptr){

    if (host_item_ptr == NULL)
        host_item_ptr = this;
    
    shared_variable_key key(var_name, host_item_ptr);

    // The input argument "shvar_map_ptr" can be used if
    // independent containes are required for the base Item.
    // The default container is the "shared_variables_map".
    if (shvar_map_ptr == NULL)
        shvar_map_ptr = &shared_variables_map;

    unordered_map <shared_variable_key, shared_variable, shared_variable_hasher>::iterator shvar_map_it = shvar_map_ptr->find(key);

    if(shvar_map_it == shvar_map_ptr->end()) {
        // Element doesn't exists.
        stringstream error_msg;
        error_msg << "erase undefined variable " << var_name;
        cout << error_msg.str() << endl;
        //throw runtime_error(error_msg.str());
    } else {

        shared_variable raw_value = shvar_map_it->second;

        if (raw_value.is_new){
            if(raw_value.type_enum == T_NULL) {
                // Enumerator arg_t not defined for this type.
                stringstream error_msg;
                error_msg << "Enumerator arg_t not defined for this type." <<
                             "; can't delete variable:" << var_name;
                //throw runtime_error(error_msg.str());
                cout << error_msg.str() << endl;
            } else { 
                erase_var_ptr(raw_value.value,raw_value.type_enum);
            }
        }
        shvar_map_ptr->erase(shvar_map_it);
    }
}

void Item::erase_item_parameter(string var_name, Item* host_item_ptr){
    erase_variable(var_name, host_item_ptr);
}

void Item::erase_event(string var_name, Item* host_item_ptr) {
    erase_variable(var_name, host_item_ptr);
}

void Item::erase_ctrl(string event_name, Item* host_item_ptr){
    erase_variable(event_name, host_item_ptr);
}

void Item::clear_variables(unordered_map <shared_variable_key, shared_variable, shared_variable_hasher>* shvar_map_ptr){

    // The input argument "shvar_map_ptr" can be used if
    // independent containes are required for the base Item.
    // The default container is the "shared_variables_map".
    if (shvar_map_ptr == NULL)
        shvar_map_ptr = &shared_variables_map;

    unordered_map <shared_variable_key, shared_variable, shared_variable_hasher>::iterator shvar_map_it;

    for (shvar_map_it = shvar_map_ptr->begin();
         shvar_map_it != shvar_map_ptr->end();
         shvar_map_it++) {

        shared_variable raw_value = shvar_map_it->second;

        if (raw_value.is_new){
            if(raw_value.type_enum == T_NULL) {
                // Enumerator arg_t not defined for this type.
                stringstream error_msg;
                error_msg << "Enumerator arg_t not defined for this type." <<
                             "; can't delete variable:" << shvar_map_it->first.name;
                //throw runtime_error(error_msg.str());
                cout << error_msg.str() << endl;
            } else { 
                erase_var_ptr(raw_value.value,raw_value.type_enum);
            }
        }
    }
    shvar_map_ptr->clear();
}
void Item::map_event_parameter(pair<shared_variable_key, shared_variable>& received_var){
    Item* host_item_ptr = received_var.first.host_item;
    if (host_item_ptr == NULL)
        host_item_ptr = this;
    switch (received_var.second.type_enum) {
         case IP_INT:
            map_parameter<int>(received_var.first.name,
                               *static_cast<Item_Parameter<int>*>(received_var.second.value),
                               host_item_ptr);
            break;
        case IP_FLOAT:
            map_parameter<float>(received_var.first.name,
                                 *static_cast<Item_Parameter<float>*>(received_var.second.value),
                                 host_item_ptr);
            break;
        case IP_BOOL:
            map_parameter<bool>(received_var.first.name,
                                *static_cast<Item_Parameter<bool>*>(received_var.second.value),
                                host_item_ptr);
            break;
        case IP_COLOR:
            map_parameter<ofColor>(received_var.first.name,
                                   *static_cast<Item_Parameter<ofColor>*>(received_var.second.value),
                                   host_item_ptr);
            break;
        case IP_VEC3F:
            map_parameter<ofVec3f>(received_var.first.name,
                                   *static_cast<Item_Parameter<ofVec3f>*>(received_var.second.value),
                                   host_item_ptr);
            break;
        case T_NULL:
            cout << "arg_t not defined for this type!" << endl;
            break;
        default:
            cout << "arg_t not defined for this type!" << endl;
            break;
    }

}

void Item::add_listener(ofEvent<pair<shared_variable_key, shared_variable>>* event){
    ofAddListener( *event, this, & Item::map_event_parameter);
}

void Item::add_listener(Item* host_controller, string button_name) {
    Button* button = static_cast<Button*>(host_controller->get_variable(button_name).value);
    if (button != NULL) {
        ofEvent<pair<shared_variable_key, shared_variable>>* event = &(button->event);
        if (event != NULL) {
            // Add button to attached_buttons (vector<Button*>).
            attached_buttons.push_back(button);
            // Add this to the button listeners (vector<Items*>). 
            button->listeners.push_back(this);
            add_listener(event);
        } else {
            cout << "error: Invalid event name for Controller: " << host_controller->get_name() << "." << endl;
        }

    } else {
        cout << "error: Invalid button name for Controller: " << host_controller->get_name() << "." << endl;
    }
}

void Item::remove_listener(ofEvent<pair<shared_variable_key, shared_variable>>* event){
    ofRemoveListener( *event, this, & Item::map_event_parameter);
}

void Item::remove_listener(string button_name, Item* host_controller) {
    cout << "remove button from item..."<<endl;
    Button* button = static_cast<Button*>(host_controller->get_variable(button_name).value);
    if (button != NULL) {
        ofEvent<pair<shared_variable_key, shared_variable>>* event = &(button->event);
        if (event != NULL) {
            // Remove button from attached_buttons (vector<Button*>).
            vector<Button*>::iterator button_it = find(attached_buttons.begin(),attached_buttons.end(),button);
            if(button_it != attached_buttons.end())
                attached_buttons.erase(button_it);
            // Remove this from the button listeners (vector<Items*>). 
            vector<Item*>::iterator listener_it = find(button->listeners.begin(),button->listeners.end(),this);
            if(listener_it != button->listeners.end())
                button->listeners.erase(listener_it);
            remove_listener(event);
        } else {
            cout << "error: Invalid event name for Controller: " << host_controller->get_name() << "." << endl;
        }
    } else {
        cout << "error: Invalid button name for Controller: " << host_controller->get_name() << "." << endl;
    }
}

void Item::remove_attached_buttons() {
    // Remove button from attached_buttons (vector<Button*>).
    vector<Button*>::iterator button_it;
    
    for (button_it = attached_buttons.end()-1;
         button_it >= attached_buttons.begin();
         button_it--){
        // Remove this item from the button listeners (vector<Items*>). 
        vector<Item*>::iterator listener_it = find((*button_it)->listeners.begin(),(*button_it)->listeners.end(),this);
        if(listener_it != (*button_it)->listeners.end())
            (*button_it)->listeners.erase(listener_it);
        ofEvent<pair<shared_variable_key, shared_variable>>* event = &((*button_it)->event);
        if (event != NULL)
            remove_listener(event);
    }
    attached_buttons.clear();
}
