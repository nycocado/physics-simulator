#include "particle.h"
#include "collection.h"
#include "simulation/dynamic_sim.h"



Particle_Cinematic particle_cinematic_new(
    double x,
    double y,
    double vx,
    double vy,
    double ax,
    double ay
)
{
    Particle_Cinematic particle = g_new(struct _Particle_Cinematic, 1);

    particle->position_i.x = x; particle->position_i.y = y;
    particle->position.x = x; particle->position.y = y;
    particle->velocity_i.x = vx; particle->velocity_i.y = vy;
    particle->velocity.x = vx; particle->velocity.y = vy;
    particle->acceleration.x = ax; particle->acceleration.y = ay;
    return particle;
}

void particle_cinematic_free(Particle_Cinematic particle)
{

    g_free(particle);
}

Particle_Dynamic particle_dynamic_new(
    double x,
    double y,
    double vx,
    double vy,
    double ax,
    double ay,
    double mass
)
{
    Particle_Dynamic particle = g_new(struct _Particle_Dynamic, 1);

    particle->position_i.x = x; particle->position_i.y = y;
    particle->position.x = x; particle->position.y = y;
    particle->velocity_i.x = vx; particle->velocity_i.y = vy;
    particle->acceleration_i.x = ax; particle->acceleration_i.y = ay;
    particle->acceleration.x = ax; particle->acceleration.y = ay;
    particle->force_resultant.x = 0; particle->force_resultant.y = 0;
    particle->mass = mass;
    particle->forces = NULL;
    return particle;
}

void particle_dynamic_free(Particle_Dynamic particle)
{

    if (particle->forces != NULL)
    {
        g_list_free_full(particle->forces, g_free);
    }
    g_free(particle);
}

Particle_Cinematic_Collection
particle_cinematic_collection_new(int num_particles)
{
    Particle_Cinematic_Collection collection =
        g_new(struct _Particle_Cinematic_Collection, 1);
    collection->particles = g_new(Particle_Cinematic, num_particles);
    collection->num_particles = num_particles;
    return collection;
}

void particle_cinematic_collection_free(
    Particle_Cinematic_Collection collection
)
{
    for (int i = 0; i < collection->num_particles; i++)
        particle_cinematic_free(collection->particles[i]);
    g_free(collection->particles);
    g_free(collection);
}

Particle_Dynamic_Collection particle_dynamic_collection_new(int num_particles)
{
    Particle_Dynamic_Collection collection =
        g_new(struct _Particle_Dynamic_Collection, 1);
    collection->particles = g_new(Particle_Dynamic, num_particles);
    collection->num_particles = num_particles;
    return collection;
}

void particle_dynamic_collection_free(Particle_Dynamic_Collection collection)
{
    for (int i = 0; i < collection->num_particles; i++)
        particle_dynamic_free(collection->particles[i]);
    g_free(collection->particles);
    g_free(collection);
}
