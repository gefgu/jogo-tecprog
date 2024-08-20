#include "Menus/Menu.hpp"
#include <iostream>

Menu::Menu() : gerenciadorEstado(Gerenciador_Estado::getInstance())
{
    int largura = pGG->getWindowSize().x;
    int altura = pGG->getWindowSize().y;
    sf::Texture *texturaFundo = pGG->carregaTextura("./assets/images/fundo_menu.png");
    fundo.setTexture(*texturaFundo);
    fundo.setPosition(0, 0);
    fundo.setScale(largura / fundo.getTexture()->getSize().x, altura / fundo.getTexture()->getSize().y);
}

Menu::~Menu()
{
    std::cout << "Destruindo menu." << std::endl;
}

void Menu::desenhar()
{
}