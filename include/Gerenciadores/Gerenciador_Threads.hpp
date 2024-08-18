#ifndef GERENCIADOR_THREADS_HPP
#define GERENCIADOR_THREADS_HPP

#include "Gerenciadores/Gerenciador_Colisoes.hpp"
#include "Gerenciadores/Gerenciador_Grafico.hpp"
#include <pthread.h>


class Gerenciador_Threads {
public:
    Gerenciador_Threads();
    ~Gerenciador_Threads();
    void iniciarThreadColisoes(Gerenciador_Colisoes* gerenciadorColisoes);
    void pararThreadColisoes();
    void iniciarThreadGrafico(Gerenciador_Grafico* gerenciadorGrafico);
    void pararThreadGrafico();

private:
    static void* threadGerenciadorColisoes(void* arg);
    static void* threadGerenciadorGrafico(void* arg);

    Gerenciador_Colisoes* gerenciadorColisoes;
    Gerenciador_Grafico* gerenciadorGrafico;
    pthread_t threadColisoes;
    pthread_t threadGrafico;
    bool rodandoColisoes;
    bool rodandoGrafico;
};

#endif // GERENCIADOR_THREADS_HPP

