#include "Menus/CampoDeTexto.hpp"

CampoDeTexto::CampoDeTexto(int px, int py, int width, int height) : playerText(), playerInput(""), fundo(sf::Vector2f(width, height))
{
  sf::Font *fonte = pGG->carregaFonte("./assets/fonts/BACKTO1982.TTF");
  fundo.setFillColor(sf::Color::White);
  fundo.setPosition(px, py);

  playerText.setCharacterSize(30);
  playerText.setFont(*fonte);
  playerText.setFillColor(sf::Color::Black);
  centralizaTexto();
}

CampoDeTexto::~CampoDeTexto() {}

void CampoDeTexto::desenhar()
{
  pGG->draw(fundo);
  pGG->draw(playerText);
}

void CampoDeTexto::executar()
{
}

const char *CampoDeTexto::getTexto()
{
  playerInputStr = playerInput.toAnsiString(); // Convert and store
  return playerInputStr.c_str();
}

void CampoDeTexto::receiveEvent(sf::Event event)
{
  if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::BackSpace)
  {
    playerInput = playerInput.substring(0, playerInput.getSize() - 1);
  }
  else if (event.type == sf::Event::TextEntered)
  {
    if (event.text.unicode > 60 && event.text.unicode < 128)
      playerInput = playerInput + event.text.unicode;
  }
  playerText.setString(playerInput);
  centralizaTexto();
}

void CampoDeTexto::centralizaTexto()
{
  float posX = fundo.getPosition().x + (fundo.getSize().x / 2.f) - (playerText.getLocalBounds().width / 2.f);
  float posY = fundo.getPosition().y + (fundo.getSize().y / 2.f) - (playerText.getLocalBounds().height / 2.f) - playerText.getLocalBounds().top;
  playerText.setPosition(posX, posY);
}