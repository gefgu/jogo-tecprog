#include "Gerenciadores/Gerenciador_Grafico.hpp"
#include <cstring>

Gerenciador_Grafico::Gerenciador_Grafico() : window(sf::VideoMode(1200, 900), "Meu Jogo"), texturesMap(), fontMap()
{
  fontMap.clear();
  texturesMap.clear();
  clock.restart();

  sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

  int posX = (desktop.width / 2) - (window.getSize().x / 2);
  int posY = (desktop.height / 2) - (window.getSize().y / 2);

  window.setPosition(sf::Vector2i(posX, posY));
  sf::View view = sf::View(sf::Vector2f(1200 / 2, 900 / 2), sf::Vector2f(1200.f, 900.f));
  window.setView(view);
}

Gerenciador_Grafico::~Gerenciador_Grafico()
{
  destroyTextures();
  destroyFonts();
}

void Gerenciador_Grafico::destroyTextures()
{
  map<const char *, sf::Texture *>::iterator it = texturesMap.begin();
  for (it = texturesMap.begin(); it != texturesMap.end(); it++)
  {
    delete (it->second);
  }
  texturesMap.clear();
}

void Gerenciador_Grafico::destroyFonts()
{
  map<const char *, sf::Font *>::iterator it = fontMap.begin();
  for (it = fontMap.begin(); it != fontMap.end(); it++)
  {
    delete (it->second);
  }
  fontMap.clear();
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
    if (event.type == sf::Event::Resized)
      handleResize(event);
  }

  window.display();
  updateElapsedTime();
  sf::sleep(sf::milliseconds(1000 / 120)); // 120 FPS max
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

sf::Font *Gerenciador_Grafico::carregaFonte(const char *font_path)
{
  map<const char *, sf::Font *>::iterator it = fontMap.begin();
  for (it = fontMap.begin(); it != fontMap.end(); it++)
  {
    if (!strcmp(it->first, font_path))
      return (it->second);
  }

  // If not found, then load it.
  sf::Font *font = new sf::Font();

  if (!font->loadFromFile(font_path))
  {
    cout << "Error loading file" << font_path << endl;
    exit(1);
  }

  fontMap.insert(pair<const char *, sf::Font *>(font_path, font));
  return font;
}

void Gerenciador_Grafico::drawSprite(sf::Sprite s)
{
  window.draw(s);
}

void Gerenciador_Grafico::renderizar()
{
  // Adicione a lógica de renderização aqui
  std::cout << "Renderizando..." << std::endl;
}

void Gerenciador_Grafico::handleResize(sf::Event event)
{
  sf::Vector2f center = window.getView().getCenter();
  window.setView(sf::View(center, sf::Vector2f(event.size.width, event.size.height)));
}

void Gerenciador_Grafico::centerCamera(sf::Vector2f center)
{
  window.setView(sf::View(center, window.getView().getSize()));
}