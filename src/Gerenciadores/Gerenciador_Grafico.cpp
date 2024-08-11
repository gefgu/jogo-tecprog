#include "Gerenciadores/Gerenciador_Grafico.hpp"

Gerenciador_Grafico::Gerenciador_Grafico() : window(sf::VideoMode(1600, 900), "Meu Jogo")
{
  clock.restart();
}

Gerenciador_Grafico::~Gerenciador_Grafico()
{
}

void Gerenciador_Grafico::desenharEnte(Ente *pE)
{
  window.draw(pE->getSprite());
}

void Gerenciador_Grafico::clear()
{
  window.clear();
}

void Gerenciador_Grafico::display()
{
  sf::Event event;
  while (window.pollEvent(event))
  {
    if (event.type == sf::Event::Closed)
      window.close();
  }

  window.display();
  updateElapsedTime();
  // sf::sleep(sf::milliseconds(100));
}

bool Gerenciador_Grafico::isWindowOpen()
{
  return window.isOpen();
}

void Gerenciador_Grafico::updateElapsedTime()
{
  elapsed_time = clock.getElapsedTime().asMilliseconds();
  clock.restart();
}