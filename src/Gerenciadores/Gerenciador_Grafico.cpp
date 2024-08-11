#include "Gerenciadores/Gerenciador_Grafico.hpp"

Gerenciador_Grafico::Gerenciador_Grafico() : window(sf::VideoMode(1600, 900), "Meu Jogo")
{
}

Gerenciador_Grafico::~Gerenciador_Grafico()
{
}

void Gerenciador_Grafico::desenharEnte(Ente *pE)
{
  // window.draw(pE->getSprite());
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
}

bool Gerenciador_Grafico::isWindowOpen()
{
  return window.isOpen();
}

sf::Texture Gerenciador_Grafico::carregaTextura(string textura_path)
{
  sf::Texture tex;
  if (!tex.loadFromFile(textura_path, sf::IntRect(0, 0, 32, 32)))
  {
    cout << "Erro carregando textura: " << textura_path << endl;
    tex.create(32, 32);
  }
  return tex;
}