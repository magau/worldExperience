#include "worldExperience.h"

Particle_props :: Particle_props(){
    locat = ofVec3f(float(NULL));
    veloc = ofVec3f(float(NULL));
    accel = ofVec3f(float(NULL));
    color = ofColor(float(NULL));
    rad = int(NULL);
    relax_fact = float(NULL);
    isAlive = true;
}


template <typename IType> 
//IType handles the "BaseParticle" class and all their derived classes.
Base_ItemsSystem<IType>::Base_ItemsSystem(Particle_props init_props){
    //name = "baseIS";
    props = init_props;
    //default_addedItemName = "baseI";
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
void Base_ItemsSystem<IType>::add_itemByName(string iName,Particle_props init_props){

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
void Base_ItemsSystem<IType>::pop(int index, bool erase){
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
        if (erase) delete item;
        itemsVector.erase(itemsVector.begin() + index);
    }
}

template <typename IType> 
void Base_ItemsSystem<IType>::pop_itemById(int id, bool erase){
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
            if (erase) delete item;
            itemsVector.erase(particle_it);
            break;
        }
    }
}

template <typename IType> 
void Base_ItemsSystem<IType>::pop_itemByName(string iName, bool erase){
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
                if (erase) delete item;
                itemsVector.erase(particle_it);
            }
        }
    }
}

/*
template <typename IType> 
void Base_ItemsSystem<IType>::reset_itemTypeById(int id, string iName){
    IType item;
    typename vector<IType>::iterator particle_it;
    Particle_props init_props;

    if (iName.size() == 0){
       iName = default_addedItemName;
       cout<<"default added Item name:"<<default_addedItemName<<endl;
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
void Base_ItemsSystem<IType>::clear(bool erase){
    IType item;
    typename vector<IType>::iterator particle_it;

    if ( itemsVector.size() > 0){
        if (erase){
            for (particle_it = itemsVector.end() - 1;
                 particle_it >= itemsVector.begin();
                 particle_it--){

                item = *particle_it;
                delete item;
            }
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

Interaction::Interaction(Particle_props init_props){
    props = init_props;
}

void Interaction::run(Particle_props* actuatedParticle_props, Particle_props* p_props){

}

void Interaction::update(Particle_props* p_props){

}

Interaction_I::Interaction_I(Particle_props init_props) :
Interaction(init_props){
    //props = init_props;
    name = "I_1";
    max_dist = ofDist(0,0,ofGetWindowWidth(),ofGetWindowHeight());
}

void Interaction_I::run(Particle_props* actuatedParticle_props, Particle_props* p_props){
    float dist,dx,dy,weight,weight_fact,acc;
    //Particle* actuated_particle;

    weight_fact = 0.25;

    weight = max_dist*weight_fact;

    dist = p_props->locat.distance(actuatedParticle_props->locat);
    dx = actuatedParticle_props->locat.x - p_props->locat.x;
    dy = actuatedParticle_props->locat.y - p_props->locat.y;
    acc = weight / pow(dist,2);
    actuatedParticle_props->accel.x += dx * acc;
    actuatedParticle_props->accel.y += dy * acc;
    //Do not aplly relaxation at the bounthery wall  
    int offset = actuatedParticle_props->rad;
    if (actuatedParticle_props->locat.x > offset &&
        actuatedParticle_props->locat.x < ofGetWindowWidth() - offset &&
        actuatedParticle_props->locat.y > offset &&
        actuatedParticle_props->locat.y < ofGetWindowHeight() - offset ){

        actuatedParticle_props->relax_fact = 0.7;
    }
} 

Interaction_II::Interaction_II(Particle_props init_props) :
Interaction(init_props){
    name = "I_2";
    max_dist = ofDist(0,0,ofGetWindowWidth(),ofGetWindowHeight());
}

void Interaction_II::run(Particle_props* actuatedParticle_props, Particle_props* p_props){
    float dist,dx,dy,weight,weight_fact,acc;
    //Particle* actuated_particle;

    weight_fact = 0.1;
    min_dist = 40;

    weight = max_dist*weight_fact;

    dist = p_props->locat.distance(actuatedParticle_props->locat);
    dx = actuatedParticle_props->locat.x - p_props->locat.x;
    dy = actuatedParticle_props->locat.y - p_props->locat.y;

    if (dist < min_dist) dist = min_dist;
    acc = weight / pow(dist,2);

    actuatedParticle_props->accel.x += - dx * acc;
    actuatedParticle_props->accel.y += - dy * acc;

    // //Over relaxation
    // if (dist == min_dist) {
    //     actuated_particle->props.relax_fact *= 0.95;
    //     //actuated_particle->props.relax_fact *= 0.7;
    // }
}

BaseParticle::BaseParticle(Particle_props init_props) :
              Base_ItemsSystem<Interaction*>(init_props){
    name = "baseP";
}

void BaseParticle::add_itemByName(string iName,Particle_props init_props){
   if (iName.size() == 0){
       iName = default_addedItemName;
       cout<<"default name:"<<default_addedItemName<<endl;
   } 

   if (iName.compare("I_1") == 0){
       add(new Interaction_I(init_props));
       //cout<<"add item, iName:"<<iName<<endl;
   } else if (iName.compare("I_2") == 0){
       add(new Interaction_II(init_props));
       //add(new DerivedParticle());
       //cout<<"add item, iName:"<<iName<<endl;
   }
   /*
    .
    .
    .
       Add new item types
   */
}

void BaseParticle :: run() {
    update();
    display();
}

// Method to display
void BaseParticle :: display() {
    //ofColor(...);
    //ofFill();
    ofSetColor(props.color);
    ofEllipse(props.locat.x,props.locat.y,props.rad,props.rad);
}

void BaseParticle :: update() {
    props.veloc += props.accel;
    enable_screenElasticBoundery();
    props.locat += props.veloc;
    //Aplly relax_fact
    props.veloc *= ofVec3f(props.relax_fact);
    bound_particles_location();
    //props.vel = ofPoint(0);
    props.accel = ofVec3f(0);
    props.relax_fact = 1.0;
//cout<<"props.vel:"<<props.vel<<" props.loc:"<<props.loc<<endl;
    // Clear accelaration to allow comulative 
    // interactions and order independency:
}

void BaseParticle :: bound_particles_location(){
   int offset = props.rad;

   if (props.locat.x < offset){
       props.locat.x = offset;
   } else if (props.locat.x > ofGetWindowWidth()-offset){
       props.locat.x = ofGetWindowWidth()-offset;
   }
   if (props.locat.y < offset){
       props.locat.y = offset;
   } else if (props.locat.y > ofGetWindowHeight()-offset){
       props.locat.y = ofGetWindowHeight()-offset;
   }

}

void BaseParticle :: set_speedLimit(int maxSpeed){
   
   if (props.veloc.x < -1 * maxSpeed){
       props.veloc.x = -1 * maxSpeed;
   } else if (props.veloc.x > maxSpeed){
       props.veloc.x = maxSpeed;
   }
   if (props.veloc.y < -1 * maxSpeed){
       props.veloc.y = -1 * maxSpeed;
   } else if (props.veloc.y > maxSpeed){
       props.veloc.y = maxSpeed;
   }
}

void BaseParticle :: enable_screenElasticBoundery(){
   int offset = props.rad;

   //Elastic bounds
   if ( props.locat.x <= offset || props.locat.x >= ofGetWindowWidth()-offset ){
       props.veloc.x *= -1;
   }
   if ( props.locat.y <= offset || props.locat.y >= ofGetWindowHeight()-offset ){
       props.veloc.y *= -1;
   }
}

InteractiveParticle::InteractiveParticle(Particle_props init_props) :
                     BaseParticle(init_props){
    name="IP_1";
}

void InteractiveParticle::run(){
// for interaction in itemsVector
// interaction.run()
}

/*
DerivedParticle::DerivedParticle(Particle_props init_props) :
                 Base_ItemsSystem<BaseParticle*>(init_props){
    name="derivedP";
}
*/

Base_ParticlesSystem::Base_ParticlesSystem(Particle_props init_props) :
                      Base_ItemsSystem<BaseParticle*>(init_props){
    name = "basePS";
    default_addedItemName = "baseP";
}

void Base_ParticlesSystem::add_itemByName(string iName,Particle_props init_props){
   if (iName.size() == 0){
       iName = default_addedItemName;
   } 

   if (iName.compare("baseP") == 0){
       add(new BaseParticle(init_props));
   } else if (iName.compare("IP_1") == 0){
       add(new InteractiveParticle(init_props));
   }
   /*
    .
    .
    .
       Add new item types
   */
}

void Base_ParticlesSystem::setup(){
//    for (int i=0;i<10;i++){
//        if (i<5){
//            add(new BaseParticle());
//        } else {
//            add(new DerivedParticle());
//        }
//    }
}

//void Base_ParticlesSystem::interact(Base_ParticlesSystem* actuated_PS){
////    for (u_int i=0; i<itemsVector.size(); i++){
////        itemsVector[i].interact( &(actuated_PS->itemsVector) );
////    }
//}
//
void Base_ParticlesSystem::run(){

}

/*
Derived_ParticlesSystem::Derived_ParticlesSystem() :
                         Base_ItemsSystem<BaseParticle*>(init_props){
    name = "derivedPS";
    default_addedItemName = "baseP";
}
*/

RegularGrid_ParticlesSystem::RegularGrid_ParticlesSystem(Particle_props init_props) :
                             Base_ParticlesSystem(init_props){
    name = "regGidPS";
    default_addedItemName = "baseP";
}

void RegularGrid_ParticlesSystem::setup(int particles_distance, ofPoint grid_size){
    //This method ("constructor") builds a 2D regular grid particles system.
    // particles_distance - pixels
    // grid_size - [0 < grid_size <1] Relative to window size.
    u_int i,j,win_w,win_h,grd_w,grd_h;
    Particle_props init_props;
    ofPoint grid_offset;
    int grid_ds;
    ofPoint grid_num;

    init_props.veloc.set(0,0);
    init_props.accel.set(0,0);
    init_props.rad = 6;
    init_props.relax_fact = 1.0;
    init_props.color = ofColor(255);

    grid_ds = particles_distance;
    win_w = ofGetWindowWidth();
    win_h = ofGetWindowHeight();
    grd_w = round(win_w*grid_size.x);
    grd_h = round(win_h*grid_size.y);
    //grid_offset.x = (win_w - (grd_w-2*grid_ds)/grid_ds * grid_ds)/2;
    //grid_offset.y = (win_h - (grd_h-2*grid_ds)/grid_ds * grid_ds)/2;
    //grid_num.set(1+(win_w-2*grid_offset.x)/grid_ds,1+(win_h-2*grid_offset.y)/grid_ds);

    grid_offset.x = (win_w - grd_w)/2;
    grid_offset.y = (win_h - grd_h)/2;
    grid_num.set(grd_w/grid_ds , grd_h/grid_ds);

////One particle for testing
//grid_num.set(1);
//init_props.loc.x = win_w/2;//
//init_props.loc.y = win_h/2;//
    for (i=0; i<grid_num.y; i++){
        //init_props.loc.y = i*grid_ds + grid_offset.y;
        init_props.locat.y = i*grid_ds + grid_offset.y;
        for (j=0; j<grid_num.x; j++){
            //init_props.loc.x = j * grid_ds + grid_offset.x;
            init_props.locat.x = j * grid_ds + grid_offset.x;
            add(new BaseParticle(init_props));
        }
    }
}

Base_World::Base_World(){
    name = "baseW";
    default_addedItemName = "basePS";
}

void Base_World::add_itemByName(string iName, Particle_props init_props){
   if (iName.size() == 0){
       iName = default_addedItemName;
       cout<<"default name:"<<default_addedItemName<<endl;
   } 

   if (iName.compare("basePS") == 0){
       add(new Base_ParticlesSystem(init_props));
       //cout<<"add item, iName:"<<iName<<endl;
   } else if (iName.compare("derivedPS") == 0){
       add(new RegularGrid_ParticlesSystem(init_props));
       //cout<<"add item, iName:"<<iName<<endl;
   }
   /*
    .
    .
    .
       Add new item types
   */
}
//
////main(){
////    
////    Base_ParticlesSystem sys;
////    sys.setup();
////    sys.pop_itemById(8);
////    sys.get_itemsByName();
////    sys.add(new BaseParticle());
////    sys.get_itemsByName();
////    sys.pop_itemByName("baseP");
////    sys.get_itemsByName();
////    sys.add(new DerivedParticle());
////    sys.get_itemsByName();
////    sys.pop_itemById(2);
////    sys.get_itemsByName();
////    sys.add_itemByName("derivedP");
////    sys.set_default_itemName("derivedP");
////    sys.add_itemByName();
////    sys.get_itemsByName();
////    sys.clear();
////    sys.get_itemsByName();
////    sys.add_itemByName();
////    sys.add_itemByName();
////    sys.add_itemByName();
////    sys.get_itemsByName();
////    sys.reset_itemTypeById(2,"baseP");
////    sys.set_default_itemName("baseP");
////    sys.reset_itemTypeById(0);
////    sys.get_itemsByName();
////
////    cout<<"world..."<<endl;
////    Base_World myWorld;
////    myWorld.add(&sys);
////    myWorld.get_itemsByName()[0]->get_itemsByName();
////    cout<<"done"<<endl;
////    
////    //World world;
////    //world.add("basePS","baseP");
////    //cout<<"size world:"<<world.base_particles_sys.size()<<endl;
////    //world.base_particles_sys.back().setup();
////    //world.get_info();
////}
