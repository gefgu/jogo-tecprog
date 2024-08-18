#include "Jogo.hpp"
#include <unistd.h>
#include <iostream>

Jogo::Jogo() : gerenciadorGrafico(Gerenciador_Grafico::getInstance()), menu(gerenciadorGrafico.getWindowSize().x, gerenciadorGrafico.getWindowSize().y),
               gerenciadorEstado(Gerenciador_Estado::getInstance())
{
    Ente::setGerenciadorGrafico(&gerenciadorGrafico);
    gerenciadorThreads.iniciarThreadColisoes(&gerenciadorColisoes);
}

Jogo::~Jogo()
{
    gerenciadorThreads.pararThreadColisoes();
    // Implementar destruição de entidades, se necessário
}

void Jogo::executar()
{
    while (gerenciadorGrafico.isWindowOpen())
    {
        performanceMonitor.startFrame();
        gerenciadorGrafico.clear();
        estadoJogo estado = gerenciadorEstado.getEstadoJogo();
        if (estado == estadoJogo::MENU)
        {
            menu.executar();
        }
        else if (estado == estadoJogo::FASE1)
        {
            fase1.executar();
        }
        gerenciadorGrafico.display();
        performanceMonitor.endFrame(); // Finaliza a medição do tempo do quadro
        performanceMonitor.printFPS();
    }
}