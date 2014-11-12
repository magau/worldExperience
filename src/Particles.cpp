#include "testApp.h"

Particle :: Particle () : Item(){

    set_name(get_type_name());
    //cout << get_type_name() << " constructor..." << endl;
    loc = Item_Parameter<ofVec3f>(ofVec3f(0), pair<ofVec3f,ofVec3f> (ofVec3f(0),ofVec3f(0)));
    vel = Item_Parameter<ofVec3f>(ofVec3f(0), pair<ofVec3f,ofVec3f> (ofVec3f(0),ofVec3f(0)));
    acc = Item_Parameter<ofVec3f>(ofVec3f(0), pair<ofVec3f,ofVec3f> (ofVec3f(0),ofVec3f(0)));
    color = Item_Parameter<ofColor>(ofColor(0), pair<ofColor,ofColor> (ofColor(0),ofColor(0)));
    rad = Item_Parameter<int>(10, pair<int,int>(0,100));
    relax = Item_Parameter<float>(0);
    visible = Item_Parameter<bool>(true);
    set_variable("loc",&loc,IP_VEC3F);
    set_variable("vel",&vel,IP_VEC3F);
    set_variable("acc",&acc,IP_VEC3F);
    set_variable("color",&color,IP_COLOR);
    set_variable("rad",&rad,IP_INT);
    set_variable("relax",&relax,IP_FLOAT);
    set_variable("is_visible",&visible,IP_BOOL);
}

Particle :: ~Particle (){
    PointersVector<Tag*>::iterator iter_tag;
    for (iter_tag = tags.begin();
         iter_tag != tags.end();
         iter_tag++){
        (*iter_tag)->remove_particle(this);
    }
}

//bool Particle::is_visible() {
//    return visible.value;    
//};

//void Particle::set_visible(bool visible_val){
//    visible.value = visible_val;
//};

void Particle::setup(){}

void Particle::run(){update();}

// Method to display
void Particle::display() {}

const type_info& Particle::get_typeid() {
    return typeid(this);
}

void Particle :: update() {
    vel.value += acc.value;
    elastic_boundery();
    loc.value += vel.value;
    //Aplly relax_fact
    vel.value *= ofVec3f(relax.value);
    relax.value = 1.0;
    //bound_particles_location();

    // Clear accelaration to allow comulative 
    // interactions and order independency:
    acc.value = ofVec3f(0);
}


/*
void Particle :: bound_particles_location(){
   int offset = rad;

   if (locat.x < offset){
       locat.x = offset;
   } else if (locat.x > ofGetWindowWidth()-offset){
       locat.x = ofGetWindowWidth()-offset;
   }
   if (locat.y < offset){
       locat.y = offset;
   } else if (locat.y > ofGetWindowHeight()-offset){
       locat.y = ofGetWindowHeight()-offset;
   }
}

void Particle :: set_speedLimit(int maxSpeed){
   
   if (veloc.x < -1 * maxSpeed){
       veloc.x = -1 * maxSpeed;
   } else if (veloc.x > maxSpeed){
       veloc.x = maxSpeed;
   }
   if (veloc.y < -1 * maxSpeed){
       veloc.y = -1 * maxSpeed;
   } else if (veloc.y > maxSpeed){
       veloc.y = maxSpeed;
   }
}
*/

void Particle :: elastic_boundery(){
    //int offset = *get_item_parameter<int>("rad");
    int* offset = &get_item_parameter<int>("rad")->value;
    ofVec3f* locat = &loc.value;
    ofVec3f* veloc = &vel.value;

    //Elastic bounds
    if ( (locat->x <= *offset &&  veloc->x < 0) ||
         (locat->x >= ofGetWindowWidth() - *offset &&  veloc->x > 0) ){
        veloc->x *= -1;
    }
    if ( (locat->y <= *offset && veloc->y < 0) ||
         (locat->y >= ofGetWindowHeight() - *offset && veloc->y > 0) ){
        veloc->y *= -1;
    }
}

Circle::Circle() : Particle(){
    set_name(get_type_name());
}

const type_info& Circle::get_typeid() {
    return typeid(this);
}

void Circle :: display() {
    //ofColor(...);
    //ofFill();
    ofSetColor(color.value);
    //ofEllipse(locat.x,locat.y,rad,rad);
    int* rad_val = &rad.value;
    ofVec3f* loc_val = &loc.value;
    ofEllipse(loc_val->x,loc_val->y,*rad_val,*rad_val);
}

Line :: Line() : Particle(){
    set_name(get_type_name());
    color.value = ofColor(100,255,255);
}

const type_info& Line::get_typeid() {
    return typeid(this);
}

void Line :: display() {
    ofSetColor(color.value);
    ofSetLineWidth(3);
    points.draw();
}
