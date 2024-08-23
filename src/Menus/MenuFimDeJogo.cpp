#include "Menus/MenuFimDeJogo.hpp"
#include <iostream>
#include <fstream>

MenuFimDeJogo::MenuFimDeJogo(int p, estadoJogo ultimoEstado) : Menu(), pontos(p), textInput(pGG->getWindowSize().x / 2 - 300, 400, 600, 75), ultimaFase(ultimoEstado)
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

  sf::Text textoFinal;
  textoFinal.setFont(*fonte);
  textoFinal.setFillColor(sf::Color::White);
  textoFinal.setCharacterSize(48);
  textoFinal.setString("Conseguiu " + to_string(pontos) + " Pontos!!");
  centralizaTextoNoBotao(textoFinal, fundo);
  textosDecorativos.push_back(textoFinal);

  // Botões
  for (int i = 0; i < 4; i++)
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

  setBotaoTexto(0, "Continuar");
  setBotaoTexto(1, "Salvar e Continuar");
  setBotaoTexto(2, "Salvar e Voltar");
  setBotaoTexto(3, "Voltar Menu");
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
    pGG->draw(botoes[i]);
  for (i = 0; i < fundos.size(); i++)
    pGG->draw(fundos[i]);
  for (i = 0; i < textos.size(); i++)
    pGG->draw(textos[i]);
  for (i = 0; i < textosDecorativos.size(); i++)
    pGG->draw(textosDecorativos[i]);
}

void MenuFimDeJogo::encerrar()
{

  if (itemSelecionado == 1 || itemSelecionado == 2)
  {
    salvar();
  }
  if (itemSelecionado <= 1)
  { // continuar
    if (ultimaFase == FASE1)
      gerenciadorEstado.setEstadoJogo(FASE2);
    else if (ultimaFase == FASE2)
      gerenciadorEstado.setEstadoJogo(FASE1);
  }
  else if (itemSelecionado >= 2)
  {
    gerenciadorEstado.setEstadoJogo(MENUINICIO);
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
      else if (event.key.code == sf::Keyboard::Enter)
      {
        encerrar();
      }
      else if (event.key.code == sf::Keyboard::Escape)
      {
        gerenciadorEstado.setEstadoJogo(estadoJogo::MENUINICIO);
      }
    }
    textInput.receiveEvent(event);
  }
  desenhar();
}

int MenuFimDeJogo::getPontos()
{
  return pontos;
}

void MenuFimDeJogo::salvar()
{
  std::ofstream file;
  const char *filename = "leaderboard.txt";

  // Open the file in append mode to add new entries
  file.open(filename, std::ios::app);
  const char *name = textInput.getTexto();

  if (file.is_open())
  {
    // Write the name and points in CSV format
    file << name << "," << to_string(pontos) << "\n";
    file.close();
    std::cout << "Entry added to leaderboard: " << name << ", " << to_string(pontos) << " points\n";
  }
  else
  {
    std::cerr << "Unable to open the file " << filename << "\n";
  }
}