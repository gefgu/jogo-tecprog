#include "Gerenciadores/Gerenciador_Grafico.hpp"
#include <cstring>

Gerenciador_Grafico::Gerenciador_Grafico() : window(sf::VideoMode(1200, 900), "Meu Jogo"), texturesMap()
{
  texturesMap.clear();
  clock.restart();

  sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

  int posX = (desktop.width / 2) - (window.getSize().x / 2);
  int posY = (desktop.height / 2) - (window.getSize().y / 2);

  window.setPosition(sf::Vector2i(posX, posY));
}

Gerenciador_Grafico::~Gerenciador_Grafico()
{
  map<const char *, sf::Texture *>::iterator it = texturesMap.begin();
  for (it = texturesMap.begin(); it != texturesMap.end(); it++)
  {
    delete (it->second);
  }
  texturesMap.clear();
}

// void Gerenciador_Grafico::desenharEnte(Ente *pE)
// {
//   window.draw(pE->getSprite());
// }

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
  sf::sleep(sf::milliseconds(1000 / 20)); // 120 FPS max
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

float Gerenciador_Grafico::getElapsedTime()
{
  return elapsed_time;
}

sf::Vector2u Gerenciador_Grafico::getWindowSize() const
{
  return window.getSize();
}

bool Gerenciador_Grafico::pollEvent(sf::Event &event)
{
  return window.pollEvent(event);
}

void Gerenciador_Grafico::fecharJanela()
{
  window.close();
}

sf::RenderWindow &Gerenciador_Grafico::getWindow()
{
  return window;
}

// Fonte: https://github.com/MatheusBurda/Desert/blob/master/src/Managers/Graphics.cpp
sf::Texture *Gerenciador_Grafico::carregaTextura(const char *path)
{
  map<const char *, sf::Texture *>::iterator it = texturesMap.begin();
  for (it = texturesMap.begin(); it != texturesMap.end(); it++)
  {
    if (!strcmp(it->first, path))
      return (it->second);
  }

  // If not found, then load it.
  sf::Texture *tex = new sf::Texture();

  if (!tex->loadFromFile(path))
  {
    cout << "Error loading file" << path << endl;
    exit(1);
  }

  texturesMap.insert(pair<const char *, sf::Texture *>(path, tex));
  return tex;
}

void Gerenciador_Grafico::drawSprite(sf::Sprite s)
{
  window.draw(s);
}
