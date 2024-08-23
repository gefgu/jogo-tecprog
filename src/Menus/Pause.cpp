#include "Menus/Pause.hpp"

#include "Menus/Pause.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

Pause::Pause(estadoJogo ultimoEstado) : Menu(), ultimaFase(ultimoEstado)
{
  int largura = pGG->getWindowSize().x;
  int altura = pGG->getWindowSize().y;
  sf::Texture *texturaBotao = pGG->carregaTextura("./assets/images/botao.png");
  sf::Font *fonte = pGG->carregaFonte("./assets/fonts/BACKTO1982.TTF");

  // Pontuação
  sf::RectangleShape fundo(sf::Vector2f(1000, 100)); // Tamanho dos botões
  fundo.setPosition(sf::Vector2f((largura / 2) - 500, (altura / 8)));
  fundo.setTexture(texturaBotao);
  fundos.push_back(fundo);

  sf::Text texto;
  texto.setFont(*fonte);
  texto.setFillColor(sf::Color::White);
  texto.setCharacterSize(48);
  texto.setString("Pausado");
  centralizaTextoNoBotao(texto, fundo);
  textosDecorativos.push_back(texto);

  // Botões
  for (int i = 0; i < 2; i++)
  {
    sf::RectangleShape botao(sf::Vector2f(425, 75)); // Tamanho dos botões
    botao.setPosition(sf::Vector2f(125 + ((i % 2) * 525), (altura / 2) + 100 + (i >= 2) * 150));
    botao.setTexture(texturaBotao);
    botoes.push_back(botao);

    sf::Text texto;
    texto.setFont(*fonte);
    texto.setFillColor(sf::Color::White);
    texto.setCharacterSize(20);
    centralizaTextoNoBotao(texto, botao);
    textos.push_back(texto);
  }

  setBotaoTexto(0, "Voltar");
  setBotaoTexto(1, "Salvar e Sair");
  prevButton();
}

Pause::~Pause()
{
  // std::cout << "Destruindo menu." << std::endl;
}

void Pause::desenhar()
{
  pGG->centerCamera(sf::Vector2f(pGG->getWindowSize().x / 2, pGG->getWindowSize().y / 2));
  pGG->draw(fundo);
  // textInput.desenhar();
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

void Pause::executar()
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
      else if (event.key.code == sf::Keyboard::Enter)
      {
        if (itemSelecionado == 0)
          gerenciadorEstado.setEstadoJogo(ultimaFase);
        else
          gerenciadorEstado.setEstadoJogo(GAMEOVER);
      }
      else if (event.key.code == sf::Keyboard::Escape)
      {
        gerenciadorEstado.setEstadoJogo(ultimaFase);
      }
    }
    // textInput.receiveEvent(event);
  }
  desenhar();
}
