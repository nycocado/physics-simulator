#include "../include/gtk_include_all.h"

Vector create_vector(float x, float y) // Função de criação de um vetor
{
    Vector vector = malloc(sizeof(struct _Vector)); // Aloca memória para o vetor
    // Inicializa as coordenadas do vetor
    vector->x = x;
    vector->y = y;
    return vector;
}

Particle_Cinematic particle_cinematic_new(float x, float y, float vx, float vy, float ax, float ay) // Função de criação de uma partícula cinemática
{
    Particle_Cinematic particle = malloc(sizeof(struct _Particle_Cinematic)); // Aloca memória para a partícula
    // Inicializa as propriedades da partícula
    particle->position_i = create_vector(x, y);
    particle->position = create_vector(x, y);
    particle->velocity_i = create_vector(vx, vy);
    particle->velocity = create_vector(vx, vy);
    particle->acceleration = create_vector(ax, ay);
    return particle;
}

void particle_cinematic_free(Particle_Cinematic particle) // Função de liberação de uma partícula cinemática
{
    free(particle->position_i);
    free(particle->position);
    free(particle->velocity);
    free(particle->velocity_i);
    free(particle->acceleration);
    free(particle);
}

Particle_Dynamic particle_dynamic_new(float x, float y, float vx, float vy, float ax, float ay, float mass) // Função de criação de uma partícula dinâmica
{
    Particle_Dynamic particle = malloc(sizeof(struct _Particle_Dynamic)); // Aloca memória para a partícula
    // Inicializa as propriedades da partícula
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

void particle_dynamic_free(Particle_Dynamic particle) // Função de liberação de uma partícula dinâmica
{
    free(particle->position_i);
    free(particle->position);
    free(particle->velocity_i);
    free(particle->acceleration_i);
    free(particle->acceleration);
    free(particle->force_resultant);
    if (particle->forces != NULL) // Verifica se a lista de forças não é nula
    {
        g_list_free_full(particle->forces, free); // Libera a lista de forças
    }
    free(particle);
}

Particle_Cinematic_Collection particle_cinematic_collection_new(int num_particles) // Função de criação de uma coleção de partículas cinemáticas
{
    Particle_Cinematic_Collection collection = malloc(sizeof(struct _Particle_Cinematic_Collection)); // Aloca memória para a coleção de partículas cinemáticas
    collection->particles = malloc(num_particles * sizeof(Particle_Cinematic));                       // Aloca memória para as partículas
    return collection;
}

void particle_cinematic_collection_free(Particle_Cinematic_Collection collection) // Função de liberação de uma coleção de partículas cinemáticas
{
    for (int i = 0; i < app->variables->simulation->num_particles_use; i++) // Para cada partícula
    {
        particle_cinematic_free(collection->particles[i]); // Libera a partícula
    }
    free(collection->particles);
    free(collection);
}

Particle_Dynamic_Collection particle_dynamic_collection_new(int num_particles) // Função de criação de uma coleção de partículas dinâmicas
{
    Particle_Dynamic_Collection collection = malloc(sizeof(struct _Particle_Dynamic_Collection)); // Aloca memória para a coleção de partículas dinâmicas
    collection->particles = malloc(num_particles * sizeof(Particle_Dynamic));                     // Aloca memória para as partículas
    return collection;
}

void particle_dynamic_collection_free(Particle_Dynamic_Collection collection) // Função de liberação de uma coleção de partículas dinâmicas
{
    for (int i = 0; i < app->variables->simulation->num_particles_use; i++) // Para cada partícula
    {
        particle_dynamic_free(collection->particles[i]); // Libera a partícula
    }
    free(collection->particles);
    free(collection);
}