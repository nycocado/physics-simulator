#pragma once

// Definição dos ponteiros das estruturas
typedef struct _Vector *Vector;
typedef struct _Particle_Cinematic *Particle_Cinematic;
typedef struct _Particle_Dynamic *Particle_Dynamic;
typedef struct _Particle_Cinematic_Collection *Particle_Cinematic_Collection;
typedef struct _Particle_Dynamic_Collection *Particle_Dynamic_Collection;

struct _Vector // Estrutura do vetor
{
    float x;
    float y;
};

struct _Particle_Cinematic // Estrutura da partícula cinemática
{
    Vector position_i;
    Vector position;
    Vector velocity_i;
    Vector velocity;
    Vector acceleration; // Aceleração é constante na cinemática
};

struct _Particle_Dynamic // Estrutura da partícula dinâmica
{
    Vector position_i;
    Vector position;
    Vector velocity_i; // Velocidade inicial, pois não precisamos calcular a velocidade instantânea na simulação dinâmica
    Vector acceleration_i;
    Vector acceleration; // Aceleração é variável na dinâmica, por conta das forças
    Vector force_resultant;
    float mass;
    GList *forces;
};

struct _Particle_Cinematic_Collection // Estrutura da coleção de partículas cinemáticas
{
    Particle_Cinematic *particles;
};

struct _Particle_Dynamic_Collection // Estrutura da coleção de partículas dinâmicas
{
    Particle_Dynamic *particles;
};

Vector create_vector(float x, float y);                                                                      // Função de criação de um vetor
Particle_Cinematic particle_cinematic_new(float x, float y, float vx, float vy, float ax, float ay);         // Função de criação de uma partícula cinemática
void particle_cinematic_free(Particle_Cinematic particle_cinematic);                                         // Função de liberação de uma partícula cinemática
Particle_Dynamic particle_dynamic_new(float x, float y, float vx, float vy, float ax, float ay, float mass); // Função de criação de uma partícula dinâmica
void particle_dynamic_free(Particle_Dynamic particle);                                                       // Função de liberação de uma partícula dinâmica
Particle_Cinematic_Collection particle_cinematic_collection_new(int num_particle_cinematics);                // Função de criação de uma coleção de partículas cinemáticas
void particle_cinematic_collection_free(Particle_Cinematic_Collection collection);                           // Função de liberação de uma coleção de partículas cinemáticas
Particle_Dynamic_Collection particle_dynamic_collection_new(int num_particles);                              // Função de criação de uma coleção de partículas dinâmicas
void particle_dynamic_collection_free(Particle_Dynamic_Collection collection);                               // Função de liberação de uma coleção de partículas dinâmicas