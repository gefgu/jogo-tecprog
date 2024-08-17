#include "Jogo.hpp"
#include <iostream>

Jogo::Jogo() : gerenciadorGrafico(Gerenciador_Grafico::getInstance()), menu(gerenciadorGrafico.getWindowSize().x, gerenciadorGrafico.getWindowSize().y),
               gerenciadorEstado(Gerenciador_Estado::getInstance())
{
    Ente::setGerenciadorGrafico(&gerenciadorGrafico);
}

Jogo::~Jogo()
{
    // Implementar destruição de entidades, se necessário
}

void Jogo::executar()
{
    while (gerenciadorGrafico.isWindowOpen())
    {
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
    }
}
