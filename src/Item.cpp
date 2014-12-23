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
            var_ptr = new ofEvent<pair<vector<shared_variable_key>,shared_variable>>;
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
        case IP_VECTOR_OF_VEC3F:
            var_ptr = new Item_Parameter_VectorOfofVect3f;
            break;
        case BUTTON:
            var_ptr = new Button;
            break;
        case INT:
            var_ptr = new int;
            break;
        case FLOAT:
            var_ptr = new float;
            break;
        case STRING:
            var_ptr = new string;
            break;
        case PARTICLE:
            var_ptr = new Particle;
            break;
        case T_NULL:
            var_ptr = NULL;
            cout << "Can't create new variable! arg_t not defined for this type!!" << endl;
            break;
        default:
            var_ptr = NULL;
            cout << "Can't create new variable! arg_t not defined for this type!!" << endl;
            break;
    }
    return var_ptr;
}

void Item::erase_var_ptr(void* var_value, arg_t type_enum){
    if (var_value != NULL) {
        switch (type_enum) {
            case EVENT_SH_VAR:
                delete static_cast<ofEvent<pair<vector<shared_variable_key>,shared_variable>>*>(var_value); 
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
            case IP_VECTOR_OF_VEC3F:
                delete static_cast<Item_Parameter_VectorOfofVect3f*>(var_value); 
                break;
            case BUTTON:
                delete static_cast<Button*>(var_value);
                break;
            case INT:
                delete static_cast<int*>(var_value);
                break;
            case FLOAT:
                delete static_cast<float*>(var_value);
                break;
            case STRING:
                delete static_cast<string*>(var_value); 
                break;
            case PARTICLE:
                delete static_cast<Particle*>(var_value);
                break;
            case T_NULL:
                cout << "arg_t not defined for this type!!" << endl;
                break;
            default:
                cout << "arg_t not defined for this type!!" << endl;
                break;
        }
    }
}

void Item::set_variable(string var_name, void* var_ptr, arg_t type_enum, Item* host_item_ptr,
           unordered_map <shared_variable_key, shared_variable, shared_variable_hasher>* shvar_map_ptr){

    if (host_item_ptr == NULL)
        host_item_ptr = this;

    shared_variable_key key(var_name, host_item_ptr);

    // Add an existent poiter as a new element.
    bool is_new_var = false;

    /*
     * The input argument "shvar_map_ptr" can be used if
     * independent containes are required for the base Item.
     * The default container is the "shared_variables_map".
     */ 
    if (shvar_map_ptr == NULL)
        shvar_map_ptr = &shared_variables_map;

    unordered_map <shared_variable_key, shared_variable, shared_variable_hasher>::iterator shvar_map_it;
    shvar_map_it = shvar_map_ptr->find(key);

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

        if (shvar_map_it->second.is_new)
            erase_var_ptr(shvar_map_it->second.value,shvar_map_it->second.type_enum);

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
        shvar_map_it->second.callback = NULL;
        shvar_map_it->second.is_new = is_new_var;
    }

}

void Item::set_callback(string var_name, void (Item::*item_callback)(shared_variable*),
           Item* host_item_ptr,
           unordered_map <shared_variable_key, shared_variable, shared_variable_hasher>* shvar_map_ptr){

    arg_t type_enum = CALLBACK;

    if (host_item_ptr == NULL)
        host_item_ptr = this;
    shared_variable_key key(var_name, host_item_ptr);

    /*
     * The input argument "shvar_map_ptr" can be used if
     * independent containes are required for the base Item.
     * The default container is the "shared_variables_map".
     */ 
    if (shvar_map_ptr == NULL)
        shvar_map_ptr = &shared_variables_map;

    unordered_map <shared_variable_key, shared_variable, shared_variable_hasher>::iterator shvar_map_it;
    shvar_map_it = shvar_map_ptr->find(key);

    if (shvar_map_it == shvar_map_ptr->end()) {
        // Add element.
        (*shvar_map_ptr)[key] = shared_variable(item_callback);

        //cout << "add new variable:" << key.name << endl;
    } else {
        // Replace element.
        //cout << "overwiting var:" << var_key << " value:" << old_var->value << endl;

        if (shvar_map_it->second.is_new)
            erase_var_ptr(shvar_map_it->second.value,shvar_map_it->second.type_enum);

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

        shvar_map_it->second.value = NULL;
        shvar_map_it->second.callback = item_callback;
        shvar_map_it->second.is_new = false;
    }

}

shared_variable Item::get_variable(string var_name, Item* host_item_ptr,
           unordered_map <shared_variable_key, shared_variable, shared_variable_hasher>* shvar_map_ptr){

    shared_variable raw_value;

    if (host_item_ptr == NULL)
        host_item_ptr = this;
 
    shared_variable_key key(var_name, host_item_ptr);

    /*
     * The input argument "shvar_map_ptr" can be used if
     * independent containes are required for the base Item.
     * The default container is the "shared_variables_map".
     */ 
    if (shvar_map_ptr == NULL)
        shvar_map_ptr = &shared_variables_map;


    unordered_map <shared_variable_key, shared_variable, shared_variable_hasher>::iterator shvar_map_it;
    shvar_map_it = shvar_map_ptr->find(key);

    if(shvar_map_it != shvar_map_ptr->end()) {
        raw_value = shvar_map_it->second;
         
    }//else {
    //    // Element doesn't exists.
    //    stringstream error_msg;
    //    error_msg << "get undefined variable: " << var_name;
    //    cout << error_msg.str() << endl;
    //    //throw runtime_error(error_msg.str());
    //}
    return raw_value;
}

void Item::erase_variable(string var_name, Item* host_item_ptr,
           unordered_map <shared_variable_key, shared_variable, shared_variable_hasher>* shvar_map_ptr){

    if (host_item_ptr == NULL)
        host_item_ptr = this;
    
    shared_variable_key key(var_name, host_item_ptr);

    /*
     * The input argument "shvar_map_ptr" can be used if
     * independent containes are required for the base Item.
     * The default container is the "shared_variables_map".
     */ 
    if (shvar_map_ptr == NULL)
        shvar_map_ptr = &shared_variables_map;

    unordered_map <shared_variable_key, shared_variable, shared_variable_hasher>::iterator shvar_map_it;
    shvar_map_it = shvar_map_ptr->find(key);

    if(shvar_map_it != shvar_map_ptr->end()) {
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
    } else {
        // Element doesn't exists.
        stringstream error_msg;
        error_msg << "erase undefined variable " << var_name;
        cout << error_msg.str() << endl;
        //throw runtime_error(error_msg.str());
    }
}

void Item::clear_variables(unordered_map <shared_variable_key, shared_variable, shared_variable_hasher>* shvar_map_ptr){

    /*
     * The input argument "shvar_map_ptr" can be used if
     * independent containes are required for the base Item.
     * The default container is the "shared_variables_map".
     */  
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

void Item::map_shv_parameter(shared_variable* current_var, shared_variable* input_var) {
    switch (input_var->type_enum) {

        case IP_INT:
        {

            Item_Parameter<int> input_ip = *static_cast<Item_Parameter<int>*>(input_var->value);

            switch (current_var->type_enum) {

                case IP_INT:
                {
                    Item_Parameter<int>* current_ip = static_cast<Item_Parameter<int>*>(current_var->value);
                    current_ip->value = map_parameter<int>(*current_ip, input_ip);
                    break;
                }
                case IP_FLOAT:
                {
                    Item_Parameter<float>* current_ip = static_cast<Item_Parameter<float>*>(current_var->value);
                    Item_Parameter<float> cast_input_ip = cast_item_parameter<int,float>(input_ip);
                    current_ip->value = map_parameter<float>(*current_ip, cast_input_ip);
                    break;
                }
                case T_NULL:
                    cout << "arg_t not defined for this type!" << endl;
                    break;
                default:
                    cout << "arg_t not defined for this type!" << endl;
                    break;
            }
            break;
        }
        case IP_VECTOR_OF_VEC3F:
        {

            Item_Parameter_VectorOfofVect3f input_ip = *static_cast<Item_Parameter_VectorOfofVect3f*>(input_var->value);

            switch (current_var->type_enum) {

                case IP_VECTOR_OF_VEC3F:
                {
                    Item_Parameter_VectorOfofVect3f* current_ip = static_cast<Item_Parameter_VectorOfofVect3f*>(current_var->value);
                    current_ip->set_value(input_ip.value); 
                    //vector<ofVec3f>::iterator track_it;
                    //for(track_it = particles_tracker.value.begin();
                    //    track_it != particles_tracker.value.end();
                    //    track_it++){
                    //    cout << *track_it << endl;
                    //    
                    //}
 
                    //current_ip->value = map_parameter<vector<ofVec3f>>(*current_ip, input_ip);
                    break;
                }
                default:
                    cout << "IP_VECTOR_OF_VEC3F can't be maped for different types!" << endl;
                    break;
            }
            break;
        }
        case IP_FLOAT:
        {

            Item_Parameter<float> input_ip = *static_cast<Item_Parameter<float>*>(input_var->value);

            switch (current_var->type_enum) {
                case IP_INT:
                {
                    Item_Parameter<int>* current_ip = static_cast<Item_Parameter<int>*>(current_var->value);
                    Item_Parameter<int> cast_input_ip = cast_item_parameter<float,int>(input_ip);
                    current_ip->value = map_parameter<int>(*current_ip, cast_input_ip);;
                    break;
                }
                case IP_FLOAT:
                {
                    Item_Parameter<float>* current_ip = static_cast<Item_Parameter<float>*>(current_var->value);
                    current_ip->value = map_parameter<float>(*current_ip, input_ip);;
                    break;
                }
                case T_NULL:
                    cout << "arg_t not defined for this type!" << endl;
                    break;
                default:
                    cout << "arg_t not defined for this type!" << endl;
                    break;
            }
            break;
        }
        case T_NULL:
            cout << "arg_t not defined for this type!" << endl;
            break;
        default:
            cout << "arg_t not defined for this type!" << endl;
            break;
    }
}

void Item::map_event_contents(pair<vector<shared_variable_key>, shared_variable>& received_var){

    vector<shared_variable_key>::iterator key_it;

    for(key_it = received_var.first.begin(); key_it != received_var.first.end(); key_it++){

        Item* host_item_ptr = key_it->host_item;
        if (host_item_ptr == NULL)
            host_item_ptr = this;

        shared_variable current_var = get_variable(key_it->name,host_item_ptr);

        if(current_var.value != NULL) {
            shared_variable input_var = received_var.second;
            map_shv_parameter(&current_var, &input_var);
        } else if (current_var.callback != NULL) {
            shared_variable input_var = received_var.second;
            void (Item::*item_callback)(shared_variable*) = current_var.callback;
            (this->*item_callback)(&input_var);
        }
    }
}


void Item::add_listener(ofEvent<pair<vector<shared_variable_key>, shared_variable>>* event){
    ofAddListener( *event, this, & Item::map_event_contents);
}

void Item::set_listener(Button* button, ofEvent<pair<vector<shared_variable_key>, shared_variable>>* event) {

    if (event != NULL) {
 
        // Add button to attached_buttons (vector<Button*>).
        attached_buttons.push_back(button);
        add_listener(event);
    } else {
        cout << "error: Missing button's event." << endl;
    }
}

void Item::remove_listener(Button* button, ofEvent<pair<vector<shared_variable_key>, shared_variable>>* event) {
    // Detache it self from the listeners of
    // the respective event and remove the
    // button of the attached buttons.

    // Find the button on this item attached buttons:
    vector<Button*>::iterator button_it = find(attached_buttons.begin(),attached_buttons.end(),button);
    if(button_it != attached_buttons.end())
        // Remove the button from this item attached buttons:
        attached_buttons.erase(button_it);

    if (event != NULL) {
        remove_listener(event);
    } else {
        cout << "error: Missing button's event." << endl;
    }
}

void Item::remove_listener(ofEvent<pair<vector<shared_variable_key>,shared_variable>>* event){
    ofRemoveListener( *event, this, & Item::map_event_contents);
}

void Item::remove_attached_buttons() {
    // Remove button from attached_buttons (vector<Button*>).
    vector<Button*>::iterator button_it=attached_buttons.end()-1;
    for (button_it = attached_buttons.begin();
         button_it != attached_buttons.end();
         button_it++){
        // Remove this item from the button listeners (vector<Items*>). 
//        vector<Button::Button_Item>::iterator b_item_it;
//        for (b_item_it = (*button_it)->attached_listeners.begin();
//             b_item_it != (*button_it)->attached_listeners.end();
//             b_item_it++) { 
//            if (b_item_it->listener == this)
//                break;
//        }

        unordered_map <Item*,Button::Button_Item>::iterator b_item_map_it = (*button_it)->listeners_map.find(this);
        if (b_item_map_it != (*button_it)->listeners_map.end()){
            ofEvent<pair<vector<shared_variable_key>,shared_variable>>* event = &(b_item_map_it->second.event);
            if (event != NULL)
                remove_listener(event);
            (*button_it)->listeners_map.erase(b_item_map_it);
        }
    }
    attached_buttons.clear();
}
