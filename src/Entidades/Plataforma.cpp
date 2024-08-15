#include "Plataforma.hpp"

const PLATAFORMA_PATH = "./assets/tiles/Tiles.png";

Plataforma::Plataforma(int px, int py) : visual(PLATAFORMA_PATH)
{
  visual.setPosition(px, py);
  visual.setScale(3, 3);
}

Plataforma::~Plataforma()
{
}

void Plataforma::desenhar()
{
  visual.desenhar();
}