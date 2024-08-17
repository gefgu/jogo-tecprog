#include "Jogo.hpp"
#include <unistd.h>
#include <iostream>

Jogo::Jogo() : gerenciadorGrafico(Gerenciador_Grafico::getInstance()), 
               menu(gerenciadorGrafico.getWindowSize().x, gerenciadorGrafico.getWindowSize().y),
               menuAtivo(true), fase_primeira_ativa(false) {
    Ente::setGerenciadorGrafico(&gerenciadorGrafico);
    gerenciadorThreads.iniciarThreadColisoes(&gerenciadorColisoes);
}

Jogo::~Jogo() {
    gerenciadorThreads.pararThreadColisoes();
    // Implementar destruição de entidades, se necessário
}

void Jogo::processarMenu() {
    sf::Event event;
    while (gerenciadorGrafico.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            gerenciadorGrafico.fecharJanela();
        } else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Up) {
                menu.moveUp();
            } else if (event.key.code == sf::Keyboard::Down) {
                menu.moveDown();
            } else if (event.key.code == sf::Keyboard::Enter) {
                int selectedItem = menu.getSelectedItemIndex();
                if (selectedItem == 0) {
                    // Começar Fase 1
                    menuAtivo = false;
                } else if (selectedItem == 1) {
                    // Começar Fase 2
                    menuAtivo = false;
                } else if (selectedItem == 2) {
                    // Configurações
                } else if (selectedItem == 3) {
                    // Carregar jogo salvo
                }
            }
        }
    }

    gerenciadorGrafico.clear();
    menu.draw(gerenciadorGrafico.getWindow());
    gerenciadorGrafico.display();
}

void Jogo::executar() {
    while (gerenciadorGrafico.isWindowOpen()) {
        performanceMonitor.startFrame(); 
        if (menuAtivo) {
            processarMenu();
        } else {
            gerenciadorGrafico.clear();
            fase1.executar();
            fase1.desenhar();
            gerenciadorGrafico.display();
        }
        performanceMonitor.endFrame(); // Finaliza a medição do tempo do quadro
        performanceMonitor.printFPS();
    }
}