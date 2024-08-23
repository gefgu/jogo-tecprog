#include "Menus/MenuFimDeJogo.hpp"
#include <iostream>

MenuFimDeJogo::MenuFimDeJogo(int p) : Menu(), gerenciadorEstado(Gerenciador_Estado::getInstance()), pontos(p), textInput(pGG->getWindowSize().x / 2 - 300, 400, 600, 75)
{
  int largura = pGG->getWindowSize().x;
  int altura = pGG->getWindowSize().y;
  sf::Texture *texturaBotao = pGG->carregaTextura("./assets/images/botao.png");
  sf::Font *fonte = pGG->carregaFonte("./assets/fonts/BACKTO1982.TTF");

  // Pontuação
  sf::RectangleShape botao(sf::Vector2f(1000, 100)); // Tamanho dos botões
  botao.setPosition(sf::Vector2f((largura / 2) - 500, (altura / 8)));
  botao.setTexture(texturaBotao);
  botoes.push_back(botao);

  sf::Text textoFinal;
  textoFinal.setFont(*fonte);
  textoFinal.setFillColor(sf::Color::White);
  textoFinal.setCharacterSize(48);
  textoFinal.setString("Conseguiu " + to_string(pontos) + " Pontos!!");
  centralizaTextoNoBotao(textoFinal, botao);
  textos.push_back(textoFinal);

  // Botões
  for (int i = 0; i < 4; i++)
  {
    sf::RectangleShape botao(sf::Vector2f(400, 75)); // Tamanho dos botões
    botao.setPosition(sf::Vector2f(150 + ((i % 2) * 500), (altura / 2) + 100 + (i >= 2) * 150));
    botao.setTexture(texturaBotao);
    botoes.push_back(botao);

    sf::Text texto;
    texto.setFont(*fonte);
    texto.setFillColor(sf::Color::White);
    texto.setCharacterSize(20);
    centralizaTextoNoBotao(texto, botao);
    textos.push_back(texto);
  }

  setBotaoTexto(1, "Continuar", fonte);
  setBotaoTexto(2, "Salvar e Continuar", fonte);
  setBotaoTexto(3, "Salvar e Voltar", fonte);
  setBotaoTexto(4, "Voltar Menu", fonte);
  if (itemSelecionado < 1)
  { // just to take advantage of existing code
    nextButton();
    textos[0].setCharacterSize(48);
    centralizaTextoNoBotao(textos[0], botoes[0]);
  }
}

MenuFimDeJogo::~MenuFimDeJogo()
{
  // std::cout << "Destruindo menu." << std::endl;
}

void MenuFimDeJogo::desenhar()
{
  pGG->centerCamera(sf::Vector2f(pGG->getWindowSize().x / 2, pGG->getWindowSize().y / 2));
  pGG->draw(fundo);
  textInput.desenhar();
  int i;
  for (i = 0; i < botoes.size(); i++)
  {
    pGG->draw(botoes[i]);
  }
  for (i = 0; i < textos.size(); i++)
  {
    pGG->draw(textos[i]);
  }
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
      if (event.key.code == sf::Keyboard::Right)
      {
        nextButton();
      }
      else if (event.key.code == sf::Keyboard::Left)
      {
        prevButton();
      }
      else if (event.key.code == sf::Keyboard::Escape)
      {
        gerenciadorEstado.setEstadoJogo(estadoJogo::MENUINICIO);
      }
    }
    textInput.receiveEvent(event);
  }
  if (itemSelecionado < 1)
  { // just to take advantage of existing code
    nextButton();
    textos[0].setCharacterSize(48);
    centralizaTextoNoBotao(textos[0], botoes[0]);
  }
  desenhar();
}
