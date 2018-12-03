#include "Physics.h"

void ticki(Physics2i * physics){
    if(physics->s.y - 12<0){
        physics->ds.y = -0.9*physics->ds.y;
    }
    vacci(&physics->s, &physics->ds);
    vacci(&physics->ds, &physics->d2s);
}

void tickf(Physics2f * physics){
    if(physics->s.y -12 <0){
        physics->ds.y = -0.9*physics->ds.y;
    }
    vaccf(&physics->s, &physics->ds);
    vaccf(&physics->ds, &physics->d2s);
}