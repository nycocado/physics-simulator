#include "../include/gtk_include_all.h"

Vector create_vector(float x, float y)
{
    Vector vector = malloc(sizeof(struct _Vector));

    vector->x = x;
    vector->y = y;
    return vector;
}

Particle_Cinematic
particle_cinematic_new(float x, float y, float vx, float vy, float ax, float ay)
{
    Particle_Cinematic particle = malloc(sizeof(struct _Particle_Cinematic));

    particle->position_i = create_vector(x, y);
    particle->position = create_vector(x, y);
    particle->velocity_i = create_vector(vx, vy);
    particle->velocity = create_vector(vx, vy);
    particle->acceleration = create_vector(ax, ay);
    return particle;
}

void particle_cinematic_free(Particle_Cinematic particle)
{
    free(particle->position_i);
    free(particle->position);
    free(particle->velocity);
    free(particle->velocity_i);
    free(particle->acceleration);
    free(particle);
}

Particle_Dynamic particle_dynamic_new(
    float x,
    float y,
    float vx,
    float vy,
    float ax,
    float ay,
    float mass
)
{
    Particle_Dynamic particle = malloc(sizeof(struct _Particle_Dynamic));

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
    free(particle->position_i);
    free(particle->position);
    free(particle->velocity_i);
    free(particle->acceleration_i);
    free(particle->acceleration);
    free(particle->force_resultant);
    if (particle->forces != NULL)
    {
        g_list_free_full(particle->forces, free);
    }
    free(particle);
}

Particle_Cinematic_Collection
particle_cinematic_collection_new(int num_particles)
{
    Particle_Cinematic_Collection collection =
        malloc(sizeof(struct _Particle_Cinematic_Collection));
    collection->particles = malloc(num_particles * sizeof(Particle_Cinematic));
    return collection;
}

void particle_cinematic_collection_free(
    Particle_Cinematic_Collection collection
)
{
    for (int i = 0; i < app->variables->simulation->num_particles_use; i++)
    {
        particle_cinematic_free(collection->particles[i]);
    }
    free(collection->particles);
    free(collection);
}

Particle_Dynamic_Collection particle_dynamic_collection_new(int num_particles)
{
    Particle_Dynamic_Collection collection =
        malloc(sizeof(struct _Particle_Dynamic_Collection));
    collection->particles = malloc(num_particles * sizeof(Particle_Dynamic));
    return collection;
}

void particle_dynamic_collection_free(Particle_Dynamic_Collection collection)
{
    for (int i = 0; i < app->variables->simulation->num_particles_use; i++)
    {
        particle_dynamic_free(collection->particles[i]);
    }
    free(collection->particles);
    free(collection);
}