#include "testApp.h"


Particle :: Particle (Particle_props init_props){
    props = init_props;
}

void Particle :: run() {
    behave();
    interact();
    update();
    //display();
}

// Method to display
void Particle :: display() {
    //ofColor(...);
    //ofFill();
    //ofSetColor(props.color);
    //ofEllipse(props.locat.x,props.locat.y,props.rad,props.rad);
}

void Particle :: update() {
    props.veloc += props.accel;
    elastic_boundery();
    props.locat += props.veloc;
    //Aplly relax_fact
    props.veloc *= ofVec3f(props.relax_fact);
    //bound_particles_location();
    //props.vel = ofPoint(0);
    props.accel = ofVec3f(0);
    props.relax_fact = 1.0;
//cout<<"props.vel:"<<props.vel<<" props.loc:"<<props.loc<<endl;
    // Clear accelaration to allow comulative 
    // interactions and order independency:
}

void Particle :: behave() {
        for(vector<Behavior*>::iterator IterBehav = behaviors.itemsVector.begin();
                                        IterBehav != behaviors.itemsVector.end();
                                        IterBehav++){
            (*IterBehav)->run();
        }
}

void Particle :: interact() {
        for(vector<Interaction*>::iterator IterInterac = interactions.itemsVector.begin();
                                        IterInterac != interactions.itemsVector.end();
                                        IterInterac++){
            
            //for(vector<Particle*>::iterator IterPart = actuated_particles.itemsVector.begin();
            //                                IterPart != actuated_particles.itemsVector.end();
            //                                IterPart++){
            (*IterInterac)->run();
        }
}
/*
void Particle :: bound_particles_location(){
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

void Particle :: set_speedLimit(int maxSpeed){
   
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
*/

void Particle :: elastic_boundery(){
   int offset = props.rad;

   //Elastic bounds
   if ( (props.locat.x <= offset &&  props.veloc.x < 0) ||
        (props.locat.x >= ofGetWindowWidth()-offset &&  props.veloc.x > 0) ){
       props.veloc.x *= -1;
   }
   if ( (props.locat.y <= offset && props.veloc.y < 0) ||
        (props.locat.y >= ofGetWindowHeight()-offset && props.veloc.y > 0) ){
       props.veloc.y *= -1;
   }
}

Circle::Circle(Particle_props init_props) :
                     Particle(init_props){
    name="P_Circle";
}

void Circle :: display() {
    //ofColor(...);
    //ofFill();
    ofSetColor(props.color);
    ofEllipse(props.locat.x,props.locat.y,props.rad,props.rad);
}
/*
InteractiveParticle::InteractiveParticle(Particle_props init_props) :
                     Particle(init_props){
    name="IP_1";
}

void InteractiveParticle::run(){
// for interaction in itemsVector
// interaction.run()
}

DerivedParticle::DerivedParticle(Particle_props init_props) :
                 Pointers_Container<Particle*>(init_props){
    name="derivedP";
}
*/

//Particles_Container::Particles_Container(){
//
//}

Particle* Particles_Container::add_itemByName(string iName,Particle_props init_props){

   Particle* newParticle = (int)NULL;

   if (iName.size() == 0){
       iName = default_addedItemName;
   } 

   if (iName.compare("baseP") == 0){
       newParticle = new Particle(init_props);
   } else if (iName.compare("P_Circle") == 0){
       newParticle = new Circle(init_props);
   } else if (iName.compare("MP_RegGrid") == 0){
       newParticle = new RegularGrid_MP(init_props);
   }

   /*
    .
    .
    .
       Add new item types
   */

   add(newParticle);

   return newParticle;

}


void Particles_Container::attachInteraction_one2one(string iName, Particles_Container* actuated_particles){
//    typename vector<Particles*>::iterator particle_it;
//    for (particle_it = itemsVector.begin();
//         particle_it != itemsVector.end();
//         particle_it++){
//        particle = *particle_it;
//        particle->interactions.        
//
//    }
//
}

void Particles_Container::attachInteraction_many2one(string iName, Particles_Container* actuated_particles){

}

//void Particles_Container::set_regularGrig(int particles_distance){
//
//    int win_w = ofGetWindowWidth();
//    int win_h = ofGetWindowHeight();
//    int nParticles = itemsVector.size();
//    //This method ("constructor") builds a 2D regular grid particles system.
//    // particles_distance - pixels
//    // grid_size - [0 < grid_size <1] Relative to window size.
//    u_int i,j,win_w,win_h,grd_w,grd_h;
//    Particle_props init_props;
//    ofPoint grid_offset;
//    int grid_ds;
//    ofPoint grid_num;
//
//    init_props.veloc.set(0,0);
//    init_props.accel.set(0,0);
//    init_props.rad = 6;
//    init_props.relax_fact = 1.0;
//    init_props.color = ofColor(255);
//
//    grid_ds = particles_distance;
//    win_w = ofGetWindowWidth();
//    win_h = ofGetWindowHeight();
//    grd_w = round(win_w*grid_size.x);
//    grd_h = round(win_h*grid_size.y);
//    //grid_offset.x = (win_w - (grd_w-2*grid_ds)/grid_ds * grid_ds)/2;
//    //grid_offset.y = (win_h - (grd_h-2*grid_ds)/grid_ds * grid_ds)/2;
//    //grid_num.set(1+(win_w-2*grid_offset.x)/grid_ds,1+(win_h-2*grid_offset.y)/grid_ds);
//
//    grid_offset.x = (win_w - grd_w)/2;
//    grid_offset.y = (win_h - grd_h)/2;
//    grid_num.set(grd_w/grid_ds , grd_h/grid_ds);
//
//////One particle for testing
////grid_num.set(1);
////init_props.loc.x = win_w/2;//
////init_props.loc.y = win_h/2;//
//    create_systemParticles();
//
//    for (i=0; i<grid_num.y; i++){
//        //init_props.loc.y = i*grid_ds + grid_offset.y;
//        init_props.locat.y = i*grid_ds + grid_offset.y;
//        for (j=0; j<grid_num.x; j++){
//            init_props.locat.x = j * grid_ds + grid_offset.x;
//            create_particle(init_props);
//        }
//    }
//}


