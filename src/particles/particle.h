#pragma once

#include <glib.h>

typedef struct _Vector* Vector;
typedef struct _Particle_Cinematic* Particle_Cinematic;
typedef struct _Particle_Dynamic* Particle_Dynamic;
typedef struct _Particle_Cinematic_Collection* Particle_Cinematic_Collection;
typedef struct _Particle_Dynamic_Collection* Particle_Dynamic_Collection;

struct _Vector
{
        double x;
        double y;
};

struct _Particle_Cinematic
{
        Vector position_i;
        Vector position;
        Vector velocity_i;
        Vector velocity;
        Vector acceleration;
};

struct _Particle_Dynamic
{
        Vector position_i;
        Vector position;
        Vector velocity_i;
        Vector acceleration_i;
        Vector acceleration;
        Vector force_resultant;
        double mass;
        GList* forces;
};

struct _Particle_Cinematic_Collection
{
        Particle_Cinematic* particles;
        int num_particles;
};

struct _Particle_Dynamic_Collection
{
        Particle_Dynamic* particles;
        int num_particles;
};

Vector create_vector(double x, double y);
Particle_Cinematic particle_cinematic_new(
    double x,
    double y,
    double vx,
    double vy,
    double ax,
    double ay
);
void particle_cinematic_free(Particle_Cinematic particle_cinematic);
Particle_Dynamic particle_dynamic_new(
    double x,
    double y,
    double vx,
    double vy,
    double ax,
    double ay,
    double mass
);
void particle_dynamic_free(Particle_Dynamic particle);
Particle_Cinematic_Collection
particle_cinematic_collection_new(int num_particle_cinematics);
void particle_cinematic_collection_free(
    Particle_Cinematic_Collection collection
);
Particle_Dynamic_Collection particle_dynamic_collection_new(int num_particles);
void particle_dynamic_collection_free(Particle_Dynamic_Collection collection);