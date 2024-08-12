#include "Jogo.hpp"
#include <iostream>

Jogo::Jogo() 
    : gerenciadorGrafico(), 
      menu(gerenciadorGrafico.getWindowSize().x, gerenciadorGrafico.getWindowSize().y), 
      menuAtivo(true)
{
    Ente::setGerenciadorGrafico(&gerenciadorGrafico);
    jogador = new Jogador(100, 100, 3);
    entidades.incluir(jogador);
}

Jogo::~Jogo()
{
    // Implementar destruição de entidades, se necessário
}

void Jogo::adicionarEntidade(Entidade *e)
{
    // entidades.push_back(e);
}

void Jogo::processarMenu()
{
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

void Jogo::executar()
{
    while (gerenciadorGrafico.isWindowOpen()) {
        if (menuAtivo) {
            processarMenu();
        } else {
            gerenciadorGrafico.clear();

            // execute all
            entidades.executar();
            // render all
            entidades.desenhar();

            gerenciadorGrafico.display();
        }
    }
}
