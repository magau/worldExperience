#include "testApp.h"

Master_Particle::Master_Particle(World* _world) : Particle(_world){
    name = "basePS";
    default_Particle = "P_Circle";
    //default_Particle = "baseP";
    default_Interaction = "baseI";
}

void Master_Particle::setup(){

}

void Master_Particle::run(){

}

void Master_Particle::create_slaveContainer(){
    //create System slaveParticles Particles_Container.
    slaveParticles = new Particles_Container;
    slaveParticles->name = "Generic";
    world->groups.add(slaveParticles); 
}

Particle* Master_Particle::create_slaveParticle(){
    //create newParticle add particle to worldParticles and 
    //slaveParticles Particles_Container
    Particle* newParticle;
    newParticle = world->particles.add_itemByName(default_Particle, world);
    slaveParticles->add(newParticle,false);
    return newParticle;
}

RegularGrid_MP::RegularGrid_MP(World* _world) : Master_Particle(_world){
    name = "MP_RegGrid";
    default_Particle = "P_Circle";
    // provisorio:
    setup(15,4.0/5); 
}

void RegularGrid_MP::setup(int particles_distance, float windowRatio){
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

    create_slaveContainer();

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
