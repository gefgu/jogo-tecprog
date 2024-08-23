#include "Menus/MenuFimDeJogo.hpp"
#include <iostream>

MenuFimDeJogo::MenuFimDeJogo(int p) : Menu(), gerenciadorEstado(Gerenciador_Estado::getInstance()), pontos(p)
{
  sf::Font *fonte = pGG->carregaFonte("./assets/fonts/BACKTO1982.TTF");
  textoFinal.setFont(*fonte);
  textoFinal.setFillColor(sf::Color::White);
  textoFinal.setCharacterSize(48);
  textoFinal.setString("Conseguiu" + to_string(pontos) + " Pontos!!");
  sf::Vector2f pos = pGG->getTopLeftPosition();
  textoFinal.setPosition(250, 75);
  cout << "Criando MENU FIM" << endl;
}

MenuFimDeJogo::~MenuFimDeJogo()
{
  std::cout << "Destruindo menu." << std::endl;
}

void MenuFimDeJogo::desenhar()
{
  pGG->centerCamera(sf::Vector2f(pGG->getWindowSize().x / 2, pGG->getWindowSize().y / 2));
  pGG->draw(fundo);
  pGG->draw(textoFinal);
}

void MenuFimDeJogo::executar()
{
  sf::Event event;
  while (pGG->pollEvent(event))
  {
    if (event.type == sf::Event::Closed)
    {
      pGG->fecharJanela();
    }
    else if (event.type == sf::Event::KeyPressed)
    {
      if (event.key.code == sf::Keyboard::Escape)
      {
        gerenciadorEstado.setEstadoJogo(estadoJogo::MENUINICIO);
      }
    }
  }
  desenhar();
}
