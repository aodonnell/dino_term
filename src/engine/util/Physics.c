#include "Physics.h"

// up down left right
enum direction{
    U,
    D,
    L,
    R,
};

void tickPhysicsi(Physics2i * physics){
    vacci(&physics->s, &physics->ds);
    vacci(&physics->ds, &physics->d2s);
}

void tickPhysicsf(Physics2f * physics){
    vaccf(&physics->s, &physics->ds);
    vaccf(&physics->ds, &physics->d2s);
}