#include "Menus/Menu.hpp"
#include <iostream>

Menu::Menu() : gerenciadorEstado(Gerenciador_Estado::getInstance())
{
    int largura = pGG->getWindowSize().x;
    int altura = pGG->getWindowSize().y;
    sf::Texture *texturaFundo = pGG->carregaTextura("./assets/images/fundo_menu.png");
    fundo.setTexture(*texturaFundo);
    fundo.setPosition(0, 0);
    float scaleX = static_cast<float>(largura) / fundo.getTexture()->getSize().x;
    float scaleY = static_cast<float>(altura) / fundo.getTexture()->getSize().y;
    fundo.setScale(scaleX, scaleY);
}

Menu::~Menu()
{
    std::cout << "Destruindo menu." << std::endl;
}

void Menu::desenhar()
{
}