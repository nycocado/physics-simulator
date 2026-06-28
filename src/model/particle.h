#pragma once

typedef struct _Vector* Vector;
typedef struct _Particle_Cinematic* Particle_Cinematic;
typedef struct _Particle_Dynamic* Particle_Dynamic;
typedef struct _Particle_Cinematic_Collection* Particle_Cinematic_Collection;
typedef struct _Particle_Dynamic_Collection* Particle_Dynamic_Collection;

struct _Vector
{
        float x;
        float y;
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
        float mass;
        GList* forces;
};

struct _Particle_Cinematic_Collection
{
        Particle_Cinematic* particles;
};

struct _Particle_Dynamic_Collection
{
        Particle_Dynamic* particles;
};

Vector create_vector(float x, float y);
Particle_Cinematic particle_cinematic_new(
    float x,
    float y,
    float vx,
    float vy,
    float ax,
    float ay
);
void particle_cinematic_free(Particle_Cinematic particle_cinematic);
Particle_Dynamic particle_dynamic_new(
    float x,
    float y,
    float vx,
    float vy,
    float ax,
    float ay,
    float mass
);
void particle_dynamic_free(Particle_Dynamic particle);
Particle_Cinematic_Collection
particle_cinematic_collection_new(int num_particle_cinematics);
void particle_cinematic_collection_free(
    Particle_Cinematic_Collection collection
);
Particle_Dynamic_Collection particle_dynamic_collection_new(int num_particles);
void particle_dynamic_collection_free(Particle_Dynamic_Collection collection);