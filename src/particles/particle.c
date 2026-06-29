#include "particle.h"
#include "collection.h"
#include "simulation/dynamic_sim.h"

Vector create_vector(double x, double y)
{
    Vector vector = g_new(struct _Vector, 1);

    vector->x = x;
    vector->y = y;
    return vector;
}

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

    particle->position_i = create_vector(x, y);
    particle->position = create_vector(x, y);
    particle->velocity_i = create_vector(vx, vy);
    particle->velocity = create_vector(vx, vy);
    particle->acceleration = create_vector(ax, ay);
    return particle;
}

void particle_cinematic_free(Particle_Cinematic particle)
{
    g_free(particle->position_i);
    g_free(particle->position);
    g_free(particle->velocity);
    g_free(particle->velocity_i);
    g_free(particle->acceleration);
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

    particle->position_i = create_vector(x, y);
    particle->position = create_vector(x, y);
    particle->velocity_i = create_vector(vx, vy);
    particle->acceleration_i = create_vector(ax, ay);
    particle->acceleration = create_vector(ax, ay);
    particle->force_resultant = create_vector(0, 0);
    particle->mass = mass;
    particle->forces = NULL;
    return particle;
}

void particle_dynamic_free(Particle_Dynamic particle)
{
    g_free(particle->position_i);
    g_free(particle->position);
    g_free(particle->velocity_i);
    g_free(particle->acceleration_i);
    g_free(particle->acceleration);
    g_free(particle->force_resultant);
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
