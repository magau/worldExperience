#include "testApp.h"

//Master_Particle::Master_Particle(World* _world) : Particle(_world){
Master_Particle::Master_Particle() : Particle(){
    set_name("MP_Base");
    default_Particle = "P_Base";
    set_world((World*)NULL);
    //default_Particle = "P_Circle";
    //default_Interaction = "I";
}

void Master_Particle::setup(){}

void Master_Particle::run(){}

//Particles_Container* Master_Particle::create_slaveContainer(){
//    //create System slaveParticles Particles_Container.
//    //slaveParticles = new Particles_Container;
//    //slaveParticles->name = "C_" + name;
//    //world->groups.add(slaveParticles); 
//    slaveParticles = world->create_group("C_" + name);
//    return slaveParticles;
//}

Particle* Master_Particle::create_slaveParticle(){
    //create newParticle add particle to worldParticles 
    Particle* newParticle = get_world()->create_particle(default_Particle);//, world);
    //Particle* newParticle = world->particles.create_itemByName(default_Particle);//, world);
    //newParticle->set_world(world);
    
    //slaveParticles->add(newParticle,false);
    return newParticle;
}

//RegularGrid_MP::RegularGrid_MP(World* _world) : Master_Particle(_world){
RegularGrid_MP::RegularGrid_MP() : Master_Particle(){
    set_name("MP_RegGrid");
    default_Particle = "P_Circle";
    particles_distance = 15;
    windowRatio = 4.0/5;
}

void RegularGrid_MP::setup(){
    //This method ("constructor") builds a 2D regular grid particles system.
    // particles_distance - pixels
    // grid_size - [0 < grid_size <1] Relative to window size.
    u_int i,j,win_w,win_h,grd_w,grd_h;
    ofPoint grid_offset;
    ofVec3f temp_locat;
    int grid_ds;
    ofPoint grid_num;
    Particle* slave_particle;

    grid_ds = particles_distance;
    win_w = ofGetWindowWidth();
    win_h = ofGetWindowHeight();
    grd_w = round(win_w*windowRatio);
    grd_h = round(win_h*windowRatio);

    grid_offset.x = (win_w - grd_w)/2;
    grid_offset.y = (win_h - grd_h)/2;
    grid_num.set(grd_w/grid_ds , grd_h/grid_ds);

    //create_slaveContainer();

//grid_num.x = 2;
//grid_num.y = 2;

    for (i=0; i<grid_num.y; i++){

        temp_locat.y = i*grid_ds + grid_offset.y;

        for (j=0; j<grid_num.x; j++){

            temp_locat.x = j * grid_ds + grid_offset.x;

            slave_particle = create_slaveParticle();

            slave_particle->locat = temp_locat;
            slave_particle->veloc.set(0);
            slave_particle->accel.set(0);
            slave_particle->rad = 6;
            slave_particle->relax_fact = 1.0;
            slave_particle->color = ofColor(255);
        }
    }
}
