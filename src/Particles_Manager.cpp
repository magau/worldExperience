#include "testApp.h"

Particles_Container* World_Manager::create_group(string iName){
    //create System systemParticles Particles_Container.
    Particles_Container* newGroup;
    newGroup = new Particles_Container;
    newGroup->name = iName;
    world->groups.add(newGroup);
    return newGroup;
}

Particle* World_Manager::create_particle(string iName, Particle_props init_props){
    //create newParticle add particle to worldParticles and 
    //systemParticles Particles_Container
    Particle* newParticle;
    newParticle = world->particles.add_itemByName(iName,init_props);
    return newParticle;
}

Particles_Container* World_Manager::update(){
    //for(uint i=0;i<world->particles.itemsVector.size();i++){
    for(vector<Particle*>::iterator IterPart = world->particles.itemsVector.begin();
                                    IterPart != world->particles.itemsVector.end();
                                    IterPart++){
        //world->particles.itemsVector[i]->display();
        // cout<<i<<":"<<world.particles.itemsVector[i]->props.locat<<endl;
        (*IterPart)->run();
    }
    return &(world->particles);
}

void World_Manager::draw(){
    for(vector<Particle*>::iterator IterPart = world->particles.itemsVector.begin();
                                    IterPart != world->particles.itemsVector.end();
                                    IterPart++){
        (*IterPart)->display();
    }
}

Particles_Container* World_Manager::create_regularGrid(int particles_distance, float windowRatio){
    //This method ("constructor") builds a 2D regular grid particles system.
    // particles_distance - pixels
    // grid_size - [0 < grid_size <1] Relative to window size.
    Particles_Container* regGrid;
    Particle* newParticle;
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
    grd_w = round(win_w*windowRatio);
    grd_h = round(win_h*windowRatio);
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
    regGrid = create_group();

    for (i=0; i<grid_num.y; i++){
        //init_props.loc.y = i*grid_ds + grid_offset.y;
        init_props.locat.y = i*grid_ds + grid_offset.y;
        for (j=0; j<grid_num.x; j++){
            init_props.locat.x = j * grid_ds + grid_offset.x;
            
            newParticle = create_particle("P_Circle", init_props);
            regGrid->add(newParticle,false);
        }
    }
    return regGrid;
}


void Manager_KeyboardInterface::start(){
    isListening = false;
}

void Manager_KeyboardInterface::listen(int key){
   if(ofGetKeyPressed(17)) { //CTRL + Q
       isListening = true;
       msg.erase();
   } else if(ofGetKeyPressed(23)) { //CTRL + W
       isListening = false;
       cout<<"msg:"<<msg<<endl;
   } else if(isListening){
       msg += key;
   }
}

