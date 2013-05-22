#include "testApp.h"

Master_Particle::Master_Particle(Particle_props init_props) :
                 Particle(init_props){
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
    props.world->groups.add(slaveParticles); 
}

void Master_Particle::create_slaveParticle(Particle_props init_props){
    //create newParticle add particle to worldParticles and 
    //slaveParticles Particles_Container
    Particle* newParticle;
    newParticle = props.world->particles.add_itemByName(default_Particle,init_props);
    slaveParticles->add(newParticle,false);
}

RegularGrid_MP::RegularGrid_MP(Particle_props init_props) :
                             Master_Particle(init_props){
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
    Particle_props init_props;
    ofPoint grid_offset;
    int grid_ds;
    ofPoint grid_num;

    init_props.veloc.set(0);
    init_props.accel.set(0);
    init_props.rad = 6;
    init_props.relax_fact = 1.0;
    init_props.color = ofColor(255);
    init_props.world = props.world;

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
        init_props.locat.y = i*grid_ds + grid_offset.y;
        for (j=0; j<grid_num.x; j++){
            init_props.locat.x = j * grid_ds + grid_offset.x;
            create_slaveParticle(init_props);
        }
    }
}
