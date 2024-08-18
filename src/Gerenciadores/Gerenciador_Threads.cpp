#include "Gerenciadores/Gerenciador_Threads.hpp"
#include <unistd.h> // Para usleep


Gerenciador_Threads::Gerenciador_Threads() : rodandoColisoes(true), rodandoGrafico(true) {}

Gerenciador_Threads::~Gerenciador_Threads() {
    pararThreadColisoes();
    pararThreadGrafico();
}

void* Gerenciador_Threads::threadGerenciadorColisoes(void* arg) {
    Gerenciador_Threads* gerenciador = static_cast<Gerenciador_Threads*>(arg);
    Gerenciador_Colisoes* colisoes = gerenciador->gerenciadorColisoes;

    while (gerenciador->rodandoColisoes) {
        colisoes->executar();
        usleep(16000); // Verificar colisões a cada 16ms
    }

    return nullptr;
}

void Gerenciador_Threads::iniciarThreadColisoes(Gerenciador_Colisoes* gerenciadorColisoes) {
    this->gerenciadorColisoes = gerenciadorColisoes;
    pthread_create(&threadColisoes, nullptr, threadGerenciadorColisoes, this);
}

void Gerenciador_Threads::pararThreadColisoes() {
    rodandoColisoes = false;
    pthread_join(threadColisoes, nullptr);
}

void* Gerenciador_Threads::threadGerenciadorGrafico(void* arg) {
    Gerenciador_Threads* gerenciador = static_cast<Gerenciador_Threads*>(arg);
    Gerenciador_Grafico* grafico = gerenciador->gerenciadorGrafico;

    while (gerenciador->rodandoGrafico) {
        grafico->renderizar(); // Substitua por seu método de renderização
        usleep(16000); // Renderizar a cada 16ms, ajuste conforme necessário
    }

    return nullptr;
}

void Gerenciador_Threads::iniciarThreadGrafico(Gerenciador_Grafico* gerenciadorGrafico) {
    this->gerenciadorGrafico = gerenciadorGrafico;
    pthread_create(&threadGrafico, nullptr, threadGerenciadorGrafico, this);
}

void Gerenciador_Threads::pararThreadGrafico() {
    rodandoGrafico = false;
    pthread_join(threadGrafico, nullptr);
}