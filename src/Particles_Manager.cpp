#include "testApp.h"

World :: World() {}

Tag* World::create_tag(string iName){
    //create a new tag in the tags container of the world.
    Tag* newTag;
    newTag = new Tag(this);
    tags.add(newTag);

    if (iName.size() != 0) {
        newTag->set_name(iName) ;
    } else {
        char tmp[7];
        sprintf(tmp,"T_%04d",newTag->get_id());
        newTag->set_name(tmp);
    }
    return newTag;
}

//Particles_Container* World::create_group(string iName){
//    //create System systemParticles Particles_Container.
//    Particles_Container* newGroup;
//    newGroup = new Particles_Container;
//    newGroup->name = iName;
//    groups.add(newGroup);
//    return newGroup;
//}

Particle* World::create_particle(string iName){
    //create newParticle add particle to worldParticles
    Particle* newParticle = particles.create_itemByName(iName);//, this);
    newParticle->set_world(this);
    //If the particle acts over the world since its creation, it only
    //can be done after seting up the world. this is the purpose for setup function
    if(newParticle->is_active())
        newParticle->setup(); 
    return newParticle;
}

void World::add_particle(Particle* particle){
    // At the moment the particles instantiated at the "world.create_particle" are
    // already added. (change in future...)
    if(particle->get_world()==(World*)NULL){// for future usase...
        particle->set_world(this);
        particles.add(particle);
    }
    //If the particle constructor sets false the default value of the "isAlive" variable.
    //Used to preset the particle members.
    if(!particle->is_active()){
        particle->set_live_state(true);
        particle->setup(); 
    }
}


Particles_Container* World :: update(){

    for(vector<Tag*>::iterator iter_tag = tags.itemsVector.begin();
                                    iter_tag != tags.itemsVector.end();
                                    iter_tag++){
        //(*iter_tag)->particles.show_items_name_and_id();
        (*iter_tag)->run();
    }

    // This "for" statement is iterated in reverse mode to avoid core 
    // dump in case of the "remove_particle" function is called.
    for(vector<Particle*>::iterator iter_particle = particles.itemsVector.end() - 1;
                                    iter_particle >= particles.itemsVector.begin();
                                    iter_particle--) {
        if(!(*iter_particle)->is_alive()) {
            remove_particle(*iter_particle);
        } else if ((*iter_particle)->is_active()) {
            (*iter_particle)->run();
        }
    }
    return &(particles);
}

void World :: remove_tag(Tag* tag){
    tags.erase_itemById(tag->get_id());
}

void World :: remove_particle(Particle* particle){
    // Remove the particle from the world particles container.
    particles.erase_itemById(particle->get_id());
}

void World::draw(){
    for(vector<Particle*>::iterator iter_particle = particles.itemsVector.begin();
                                    iter_particle != particles.itemsVector.end();
                                    iter_particle++){
        (*iter_particle)->display();
    }
}

Manager_KeyboardInterface::Manager_KeyboardInterface(){
    particle_name["1"] = "P_Base";
    particle_name["2"] = "P_Circle";
    particle_name["3"] = "MP_RegGrid";

    interaction_name["1"] = "I_ElectRepulsion";
    interaction_name["2"] = "I_ElectAttraction";
    interaction_name["3"] = "I_WaveSource";
 
    behavior_name["1"] = "B_GravityGlue";
    behavior_name["2"] = "B_MouseTracking";

    buffer_particle    = (int)NULL;
    buffer_interaction = (int)NULL;
    buffer_behavior    = (int)NULL;
    buffer_particles_group    = (int)NULL;
    buffer_interactions_group = (int)NULL;
    buffer_behaviors_group    = (int)NULL;

    isListening = false;
    msg.erase();
    reset_objects();
    reset_actions(); 
} 

void Manager_KeyboardInterface::get_availableItems_names(unordered_map<string,string> names_map){
    unordered_map<string,string>::const_iterator item_name;
    
    for(item_name = names_map.begin();
         item_name != names_map.end();
         item_name++){
        cout<<item_name->first<<" - "<<item_name->second<<endl;
    }
}

void Manager_KeyboardInterface::reset_objects(){

    particle     = false;
    particles    = false;
    group        = false;
    groups       = false;
    behavior     = false;
    behaviors    = false;
    interaction  = false;
    interactions = false;
}

void Manager_KeyboardInterface::reset_actions(){

    create = false;
    remove = false;
    get    = false;
    set    = false;
    add    = false;
}

void Manager_KeyboardInterface::start(World* _world){
    //Can't add 'world' inside constructor because
    //this class is instantiated at the testApp.h file.
    world = _world;
}

void Manager_KeyboardInterface::decode_kb_msg(string encoded_msg){

    if (by_name){

        if(particle){
            
            obj_name = particle_name[encoded_msg];

        } else if(interaction){

            obj_name = interaction_name[encoded_msg];

        } else if(behavior){

            obj_name = behavior_name[encoded_msg];

        } else if(group){

            obj_name = encoded_msg;

        }

        msg += "/" + obj_name;

        cout<<"aqui by_name"<<endl;

    } else if (by_id) {

        obj_id = atoi(encoded_msg.c_str());

        msg += "/" + encoded_msg;

    }

    isListening = false;
    cout<<"END"<<endl;
    cout<<"msg:"<<msg<<endl;
}

void Manager_KeyboardInterface::stateFabric_update(string _msg){
    // This method decodes OSC like messages with purpose of
    // update state variables.
    int pos;
    string _action, _obj, _id;

    pos = _msg.find("/");
    _action = _msg.substr(0,pos);
    _msg.replace(0,pos+1,"");
    pos = _msg.find("/");
    _obj = _msg.substr(0,pos);
    _msg.replace(0,pos+1,"");
    _id = _msg;


    if (_action.compare("CREATE") == 0){
        reset_actions();
        create = true;
    } else if (_action.compare("REMOVE") == 0) {
        reset_actions();
        remove = true;
    } else if (_action.compare("GET") == 0) {
        reset_actions();
        get    = true;
    } else if (_action.compare("SET") == 0) {
        reset_actions();
        set    = true;
    } else if (_action.compare("ADD") == 0) {
        reset_actions();
        add    = true;
    }

    if (_obj.compare("PARTICLE") == 0) {
        reset_objects();
        if (by_name){
            particles    = true;
        } else if (by_id){
            particle     = true;
        }
    } else if (_obj.compare("GROUP") == 0) {
        reset_objects();
        if (by_name){
            groups       = true;
        } else if (by_id){
            group        = true;
        }
    } else if (_obj.compare("BEHAVIOR") == 0) {
        reset_objects();
        if (by_name){
            behaviors    = true;
        } else if (by_id){
            behavior     = true;
        }
    } else if (_obj.compare("INTERACTION") == 0) {
        reset_objects();
        if (by_name){
            interactions = true;
        } else if (by_id){
            interaction  = true;
        }
    }

    
    cout<<"action:"<<_action<<" obj:"<<_obj<<" id:"<<_id<<endl;
}

void Manager_KeyboardInterface::update_availableItems_names(unordered_map<string,string>* names_map, string new_entry){
    unordered_map<string,string>::const_iterator item_name;
    bool found_entry = false;
    ostringstream new_key;

    for(item_name = names_map->begin();
         item_name != names_map->end();
         item_name++){
        if(item_name->second.compare(new_entry)==0) {
            found_entry = true;
            break;
        }
    }

    if(!found_entry){
        new_key<<names_map->size()+1;
        (*names_map)[new_key.str()] = new_entry;
        get_availableItems_names(*names_map);
    }
}

void Manager_KeyboardInterface::stateFabric_decode(){
   vector<Particle*>::iterator iterPart;

    if (create) {

        if (behavior) {

            cout<<"create buffer_behavior "<<obj_name<<" at ";

            //if (buffer_particle != (int)NULL) {

            //    cout<<buffer_particle->name<<": "<<buffer_particle->id<<endl;
            //    buffer_behavior = buffer_particle->behaviors.create_itemByName(obj_name,buffer_particle);
            //    buffer_interaction = (int)NULL;

            //} else if (buffer_particles_group != (int)NULL) {

            //    cout<<buffer_particles_group->name<<": "<<buffer_particles_group->id<<endl;
            //    buffer_behaviors_group->clear();

            //    for(iterPart = buffer_particles_group->itemsVector.begin();
            //         iterPart != buffer_particles_group->itemsVector.end();
            //         iterPart++){
            //        cout<<"iter name:"<<(*iterPart)->name<<" iter id:"<<(*iterPart)->id<<endl;
            //        buffer_behaviors_group->add((*iterPart)->behaviors.create_itemByName(obj_name,*iterPart),false);
            //    }

            //    buffer_interactions_group->clear();

            //}

        } else if (interaction) {

            if (buffer_particle != (int)NULL) {
//
//                buffer_interaction = buffer_particle->interactions.create_itemByName(obj_name,buffer_particle);
//                buffer_behavior = (int)NULL;

            } else if (buffer_particles_group != (int)NULL) {

                buffer_interactions_group->clear();

                //for(iterPart = buffer_particles_group->itemsVector.begin();
                //     iterPart != buffer_particles_group->itemsVector.end();
                //     iterPart++){
                //    buffer_interactions_group->add((*iterPart)->interactions.create_itemByName(obj_name,*iterPart),false);
                //}

                buffer_behaviors_group->clear();

            }

        } else if (particle) {

            buffer_particle = world->create_particle(obj_name);
            if(strncmp(obj_name.c_str(),"MP_",3) == 0){
                update_availableItems_names(&group_name,obj_name);
            }

            if (buffer_particles_group != int(NULL) && buffer_particles_group != &(world->particles)){

                buffer_particles_group->add(buffer_particle, false);
 
            }

            //provisorio...
            *(buffer_particle->ofColorPtr_map["color"]) = ofColor(255,0,0);
            *(buffer_particle->ofVec3fPtr_map["loc"]) = ofVec3f(ofGetMouseX(),ofGetMouseY());
            *(buffer_particle->intPtr_map["rad"]) = 10;

            buffer_particles_group = (int)NULL;

        } else if (group) {

            //buffer_particles_group = world->create_group(obj_name);
            //update_availableItems_names(&group_name,obj_name);
            //buffer_particle = (int)NULL;
            
        }

    } else if (get) {

        if (behavior) {


            if (buffer_particle != (int)NULL) {

                buffer_behavior = buffer_particle->behaviors.get_itemById(obj_id);

            } else if (buffer_particles_group != (int)NULL) {

                get_behaviors_by_name(obj_name,&(buffer_particles_group->itemsVector));

            } else if (buffer_particles_vector.size() != 0) {

                get_behaviors_by_name(obj_name,&buffer_particles_vector);

            }

                buffer_interactions_group->clear();
                buffer_interactions_vector.clear();
                buffer_interaction = (int)NULL;

        } else if (interaction) {

            if (buffer_particle != (int)NULL) {

                buffer_interaction = buffer_particle->interactions.get_itemById(obj_id);

            } else if (buffer_particles_group != (int)NULL) {

                get_interactions_by_name(obj_name,&(buffer_particles_group->itemsVector));

            } else if (buffer_particles_vector.size() != 0) {

                get_interactions_by_name(obj_name,&buffer_particles_vector);

            }

                buffer_behaviors_group->clear();
                buffer_behaviors_vector.clear();
                buffer_behavior = (int)NULL;

        } else if (particle) {

            if (buffer_particles_group != (int)NULL){

                if (by_id) {
                    buffer_particle = buffer_particles_group->get_itemById(obj_id);
                    buffer_particles_group = (int)NULL;
                } else if (by_name) {
                    buffer_particles_vector = buffer_particles_group->get_itemsByName(obj_name);

                    for (u_int i = 0; i < buffer_particles_vector.size(); i++ ){
                        cout<<buffer_particles_vector[i]->get_name()<<" id:"<<buffer_particles_vector[i]->get_id()<<endl;
                    }

                    buffer_particle = (int)NULL;
                    buffer_particles_group = (int)NULL;
                } 

            } else {

                cout<<"ERROR - group not in buffer";

            }

        } else if (group) {

            //if (by_id) {
            //    buffer_particles_group = world->groups.get_itemById(obj_id);
            //} else if (by_name) {
            //    buffer_groups_vector = world->groups.get_itemsByName(obj_name);
            //}
            buffer_particle = (int)NULL;

        }

    
    } else if (add) {

        if (particle) {

            if (buffer_particles_group != (int)NULL && buffer_particle != (int)NULL) {

                buffer_particles_group->add(buffer_particle,false);

            }

        } else if (group) {
            
            //if (buffer_interaction != (int)NULL) {
            //    
            //    buffer_interaction->actuated_particles = world->groups.get_itemById(obj_id);
            //}

        }

    } else if (remove) {

        if (behavior) {

            if (buffer_particle != (int)NULL){

               if (by_id) {

                   buffer_particle->behaviors.erase_itemById(obj_id);

               } else if (by_name) {

                   buffer_particle->behaviors.erase_itemsByName(obj_name);

               }

            } else if (buffer_particles_group != (int)NULL) {

                for(iterPart = buffer_particles_group->itemsVector.begin();
                     iterPart != buffer_particles_group->itemsVector.end();
                     iterPart++){

                    (*iterPart)->behaviors.erase_itemsByName(obj_name);

                }

            }

        } else if (interaction) {

            if (buffer_particle != (int)NULL){

               if (by_id) {

                   buffer_particle->interactions.erase_itemById(obj_id);

               } else if (by_name) {

                   buffer_particle->interactions.erase_itemsByName(obj_name);

               }

            } else if ( buffer_particles_group != (int)NULL) {

                for(iterPart = buffer_particles_group->itemsVector.begin();
                     iterPart != buffer_particles_group->itemsVector.end();
                     iterPart++){

                    (*iterPart)->interactions.erase_itemsByName(obj_name);

                }


            }

        } else if (particle){

            //cout<<"group id:"<<buffer_particles_group->id<<endl;
            buffer_particles_group->erase_itemById(buffer_particle->get_id());

        }

    }

    msg.erase();

}

void Manager_KeyboardInterface::get_behaviors_by_name(string& obj_name, vector<Particle*>* source_items){
    buffer_behaviors_vector.clear();
    for(vector<Particle*>::iterator item_it = source_items->begin();
        item_it != source_items->end();
        item_it++){
        vector<Behavior*> temp_behaviors = (*item_it)->behaviors.get_itemsByName(obj_name);
        for(vector<Behavior*>::iterator behavior_it = temp_behaviors.begin();
        behavior_it != temp_behaviors.end();
        behavior_it++){
            buffer_behaviors_vector.push_back(*behavior_it);
        }
    }
}

void Manager_KeyboardInterface::get_interactions_by_name(string& obj_name, vector<Particle*>* source_items){
    buffer_behaviors_vector.clear();
    for(vector<Particle*>::iterator item_it = source_items->begin();
        item_it != source_items->end();
        item_it++){
        vector<Interaction*> temp_interactions = (*item_it)->interactions.get_itemsByName(obj_name);
        for(vector<Interaction*>::iterator interaction_it = temp_interactions.begin();
        interaction_it != temp_interactions.end();
        interaction_it++){
            buffer_interactions_vector.push_back(*interaction_it);
        }
    }
}

void Manager_KeyboardInterface::listen(int key){

   if(ofGetKeyPressed(13)) {
       //RETURN

       if(isListening){
           decode_kb_msg(temp_msg);
       } 

       //stateFabric_update(msg);

       stateFabric_decode();

   } else if(ofGetKeyPressed(9)) {
       //CTRL + i

       isListening = !isListening;
       temp_msg.erase();
       cout<<(isListening?"INSERT MODE:":"EXIT INSERT")<<endl;

   } else if(ofGetKeyPressed(5)) {
       //CTRL + e

       msg += "/" + temp_msg;
       isListening = false;
       cout<<"END"<<endl;
       cout<<"temp_msg:"<<temp_msg<<endl;

   } else if(isListening){

       if( key != 8 ){
           temp_msg += key;
       } else if (!temp_msg.empty()){
           temp_msg.erase(temp_msg.end() - 1);
       }
       cout<<key<<endl;
       cout<<temp_msg<<endl;

   } else if(ofGetKeyPressed(3)){
       //CTRL + c

       reset_actions();
       create = true;
       msg = "CREATE";
       cout<<msg<<endl;

   } else if(ofGetKeyPressed(18)){
       //CTRL + r

       reset_actions();
       remove = true;
       msg ="REMOVE";
       cout<<msg<<endl;

   } else if(ofGetKeyPressed(7)){
       //CTRL + g

       reset_actions();
       get    = true;
       msg ="GET";
       cout<<msg<<endl;

   } else if(ofGetKeyPressed(19)){
       //CTRL + s
 
       reset_actions();
       set    = true;
       msg ="SET";
       cout<<msg<<endl;

   } else if(ofGetKeyPressed(1)){
       //CTRL + a

       reset_actions();
       add    = true;
       msg ="ADD";
       cout<<msg<<endl;

   } else if(ofGetKeyPressed(112)){
       // p

       reset_objects();
       particle    = true;
       msg += "/PARTICLE/BY_ID";

       by_name = false;
       by_id   = true;


       if (buffer_particles_group == (int)NULL) {

           cout<<"ERROR - group not in buffer";

       } else {

           buffer_particles_group->show_items_name_and_id();
           //cout<<"group:"<<(buffer_particles_group->name)<<" size:"<<(buffer_particles_group->itemsVector.size())<<endl;

       }

       temp_msg.erase();
       isListening = true;
       cout<<"INSERT MODE:"<<endl;

   } else if(ofGetKeyPressed(80)){
       // P

       reset_objects();
       particle    = true;
       msg += "/PARTICLE/BY_NAME";

       by_name = true;
       by_id   = false;

       get_availableItems_names(particle_name);

       temp_msg.erase();
       isListening = true;
       cout<<"INSERT MODE:"<<endl;

   } else if(ofGetKeyPressed(103)){
       // g

       reset_objects();
       group       = true;
       msg += "/GROUP/BY_ID";

       by_name = false;
       by_id   = true;

       //world->groups.show_items_name_and_id();
       //cout<<"group:"<<(world->groups.name)<<" size:"<<(world->groups.itemsVector.size())<<endl;

       temp_msg.erase();
       isListening = true;
       cout<<"INSERT MODE:"<<endl;

   } else if(ofGetKeyPressed(71)){
       // G

       reset_objects();
       group       = true;
       msg += "/GROUP/BY_NAME";

       by_name = true;
       by_id   = false;

       //world->groups.show_items_name_and_id();
       //cout<<"group:"<<(world->groups.name)<<" size:"<<(world->groups.itemsVector.size())<<endl;

       temp_msg.erase();
       isListening = true;
       cout<<"INSERT MODE:"<<endl;

   } else if(ofGetKeyPressed(98)){
       // b

       reset_objects();
       behavior    = true;
       msg += "/BEHAVIOR/BY_ID";

       by_name = false;
       by_id   = true;

       if (buffer_particle == (int)NULL){

           cout<<"ERROR - particle not in buffer";

       } else {

           buffer_particle->behaviors.show_items_name_and_id();
           cout<<"particle:"<<(buffer_particle->get_name())<<" size:"<<(buffer_particle->behaviors.itemsVector.size())<<endl;

       }

       temp_msg.erase();
       isListening = true;
       cout<<"INSERT MODE:"<<endl;

   } else if(ofGetKeyPressed(66)){
       // B

       reset_objects();
       behavior    = true;
       msg += "/BEHAVIOR/BY_NAME";

       by_name = true;
       by_id   = false;

       get_availableItems_names(behavior_name);

       temp_msg.erase();
       isListening = true;
       cout<<"INSERT MODE:"<<endl;

   } else if(ofGetKeyPressed(105)){
       // i

       by_name = false;
       by_id   = true;

       reset_objects();
       interaction = true;
       msg += "/INTERACTION/BY_ID";

       if (buffer_particle == (int)NULL){

           cout<<"ERROR - particle not in buffer";

       } else {

           buffer_particle->interactions.show_items_name_and_id();
           cout<<"particle:"<<(buffer_particle->get_name())<<" size:"<<(buffer_particle->interactions.itemsVector.size())<<endl;

       }

       temp_msg.erase();
       isListening = true;
       cout<<"INSERT MODE:"<<endl;

   } else if(ofGetKeyPressed(73)){
       // I

       by_name = true;
       by_id   = false;

       reset_objects();
       interaction = true;
       msg += "/INTERACTION/BY_NAME";

       get_availableItems_names(interaction_name);

       temp_msg.erase();
       isListening = true;
       cout<<"INSERT MODE:"<<endl;
   }

}

