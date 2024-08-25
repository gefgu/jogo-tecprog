#include "Menus/MenuFimDeJogo.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cstring>

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

void MenuFimDeJogo::Update(const char *teclaPressionada)
{
  if (strcmp(teclaPressionada, "Right") == 0)
    nextButton();
  else if (strcmp(teclaPressionada, "Left") == 0)
    prevButton();
  else if (strcmp(teclaPressionada, "Enter") == 0)
    encerrar();
  else if (strcmp(teclaPressionada, "Escape") == 0)
    gerenciadorEstado.setEstadoJogo(estadoJogo::MENUINICIO);
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
  if (!acceptingCommands)
    return;
  acceptingCommands = false;
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

  desenhar();
}

int MenuFimDeJogo::getPontos()
{
  return pontos;
}

struct LeaderboardEntry
{
  std::string name;
  int pontos;

  // Comparator to sort by points in descending order
  bool operator<(const LeaderboardEntry &other) const
  {
    return pontos > other.pontos;
  }
};

void MenuFimDeJogo::salvar()
{
  std::vector<LeaderboardEntry> entries;
  std::ifstream infile("leaderboard.txt");
  std::string line;

  // Read the existing entries from the file
  while (std::getline(infile, line))
  {
    std::stringstream ss(line);
    std::string name;
    int pontos;

    if (std::getline(ss, name, ',') && ss >> pontos)
    {
      entries.push_back({name, pontos});
    }
  }
  infile.close();

  // Add the new entry
  const char *name = textInput.getTexto();
  entries.push_back({name, pontos});

  // Sort the entries by points in descending order
  std::sort(entries.begin(), entries.end());

  // Write the sorted entries back to the file
  std::ofstream outfile("leaderboard.txt", std::ios::trunc);
  for (const auto &entry : entries)
  {
    outfile << entry.name << "," << entry.pontos << "\n";
  }
  outfile.close();

  std::cout << "Entry added to leaderboard: " << name << ", " << pontos << " points\n";
}