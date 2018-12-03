#include "Physics.h"

void ticki(Physics2i * physics){
    vacci(&physics->s, &physics->ds);
    vacci(&physics->ds, &physics->d2s);
}

void tickf(Physics2f * physics){
    vaccf(&physics->s, &physics->ds);
    vaccf(&physics->ds, &physics->d2s);
}