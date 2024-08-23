#include "Menus/Leaderboard.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

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
    texto.setCharacterSize(24);
    texto.setString("-------------");
    centralizaTextoNoBotao(texto, fundo);
    textosDecorativos.push_back(texto);
  }

  readLeaderboard();

  sf::RectangleShape botao(sf::Vector2f(300, 75)); // Tamanho dos botões
  botao.setPosition(sf::Vector2f((largura / 2) + 150, altura / 2 - 75 / 2));
  botao.setTexture(texturaBotao);
  botoes.push_back(botao);

  sf::Text texto;
  texto.setFont(*fonte);
  texto.setFillColor(sf::Color::White);
  texto.setCharacterSize(22);
  textos.push_back(texto);

  setBotaoTexto(0, "Voltar");

  if (!botoes.empty())
  {
    textos[itemSelecionado].setCharacterSize(26);
    centralizaTextoNoBotao(textos[itemSelecionado], botoes[itemSelecionado]);
  }
}

Leaderboard::~Leaderboard() {}

void Leaderboard::readLeaderboard()
{
  const char *filename = "leaderboard.txt";
  std::ifstream file(filename);

  if (file.is_open())
  {
    std::string line;
    int i = 0;
    while (std::getline(file, line))
    {
      std::stringstream ss(line);
      std::string name;
      int points;

      // Parse the line assuming it's in "name,points" format
      if (std::getline(ss, name, ',') && ss >> points)
      {
        setFundoTexto(i, name + ": " + to_string(points));
        std::cout
            << "Name: " << name << ", Points: " << points << std::endl;
      }
      else
      {
        std::cerr << "Error parsing line: " << line << std::endl;
      }
      i++;
      if (i > textosDecorativos.size())
        break;
    }

    file.close();
  }
  else
  {
    std::cerr << "Unable to open the file " << filename << std::endl;
  }
}

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
      if (event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Escape)
      {
        gerenciadorEstado.setEstadoJogo(estadoJogo::MENUINICIO);
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