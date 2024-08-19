#include "Jogo.hpp"
#include <unistd.h>
#include <iostream>

Jogo::Jogo() : gerenciadorGrafico(Gerenciador_Grafico::getInstance()), menu(gerenciadorGrafico.getWindowSize().x, gerenciadorGrafico.getWindowSize().y),
               gerenciadorEstado(Gerenciador_Estado::getInstance()), fase1(NULL), fase2(NULL), menuFimDeJogo(NULL)
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
        estadoJogo ultimoEstado = gerenciadorEstado.getUltimoEstadoJogo();
        if (estado == estadoJogo::MENU)
        {
            menu.executar();
        }
        else if (estado == estadoJogo::FASE1)
        {
            if (fase1 == NULL)
                fase1 = new Fase_Primeira();
            fase1->executar();
        }
        else if (estado == estadoJogo::FASE2)
        {
            if (fase2 == NULL)
                fase2 = new Fase_Segunda();
            fase2->executar();
        }
        else if (estado == estadoJogo::GAMEOVER)
        {
            if (ultimoEstado == estadoJogo::FASE1 || ultimoEstado == estadoJogo::FASE2)
            {
                int pontos;
                if (ultimoEstado == estadoJogo::FASE1)
                    pontos = fase1->getPontos();
                else if (ultimoEstado == estadoJogo::FASE2)
                    pontos = fase2->getPontos();
                menuFimDeJogo = new MenuFimDeJogo(pontos);
                gerenciadorEstado.setEstadoJogo(estadoJogo::MENUGAMEOVER);
            }

            if (fase1)
                delete fase1;
            fase1 = NULL;
            if (fase2)
                delete fase2;
            fase2 = NULL;
        }
        else if (estado == estadoJogo::MENUGAMEOVER)
        {
            if (menuFimDeJogo == NULL)
                gerenciadorEstado.setEstadoJogo(estadoJogo::MENU);
            else
                menuFimDeJogo->executar();
        }

        if (ultimoEstado == estadoJogo::MENUGAMEOVER)
        {
            delete menuFimDeJogo;
            menuFimDeJogo = NULL;
        }

        gerenciadorGrafico.display();
        performanceMonitor.endFrame(); // Finaliza a medição do tempo do quadro
        performanceMonitor.printFPS();
    }
}