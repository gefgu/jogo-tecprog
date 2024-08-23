#include "Menus/Leaderboard.hpp"

Leaderboard::Leaderboard() : Menu()
{
  int largura = pGG->getWindowSize().x;
  int altura = pGG->getWindowSize().y;

  sf::Texture *texturaBotao = pGG->carregaTextura("./assets/images/botao.png");
  sf::Font *fonte = pGG->carregaFonte("./assets/fonts/BACKTO1982.TTF");

  for (int i = 0; i < 7; i++)
  {
    sf::RectangleShape fundo(sf::Vector2f(400, 75)); // Tamanho dos botões
    fundo.setPosition(sf::Vector2f((largura / 2) - 400, 100 * (i + 1)));
    fundo.setTexture(texturaBotao);
    fundos.push_back(fundo);

    sf::Text texto;
    texto.setFont(*fonte);
    texto.setFillColor(sf::Color::White);
    texto.setCharacterSize(22);
    texto.setString("-------------");
    centralizaTextoNoBotao(texto, fundo);
    textosDecorativos.push_back(texto);
  }
}

Leaderboard::~Leaderboard() {}

void Leaderboard::executar()
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
      if (event.key.code == sf::Keyboard::Up)
      {
        prevButton();
      }
      else if (event.key.code == sf::Keyboard::Down)
      {
        nextButton();
      }
      else if (event.key.code == sf::Keyboard::Enter)
      {
        int selectedItem = getSelectedItemIndex();
        if (selectedItem == 0)
        {
          // gerenciadorEstado.setEstadoJogo(estadoJogo::FASE1);
        }
        else if (selectedItem == 1)
        {
          // Começar Fase 2
          // gerenciadorEstado.setEstadoJogo(estadoJogo::FASE2);
        }
        else if (selectedItem == 2)
        {
          // Configurações
        }
        else if (selectedItem == 3)
        {
          // Carregar jogo salvo
        }
      }
    }
  }
  desenhar();
}

void Leaderboard::desenhar()
{
  pGG->centerCamera(sf::Vector2f(pGG->getWindowSize().x / 2, pGG->getWindowSize().y / 2));
  pGG->draw(fundo);

  int i;
  for (i = 0; i < botoes.size(); i++)
    pGG->draw(botoes[i]);
  for (i = 0; i < fundos.size(); i++)
    pGG->draw(fundos[i]);
  for (i = 0; i < textos.size(); i++)
    pGG->draw(textos[i]);
  for (i = 0; i < textosDecorativos.size(); i++)
    pGG->draw(textosDecorativos[i]);
}