#include "Menus/MenuCarregamento.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <dirent.h>    // Include for directory handling
#include <cstring>     // Include for strcmp
#include <json/json.h> // JSON library that supports C++03

MenuCarregamento::MenuCarregamento() : Menu()
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
    botoes.push_back(fundo);

    sf::Text texto;
    texto.setFont(*fonte);
    texto.setFillColor(sf::Color::White);
    texto.setCharacterSize(24);
    texto.setString("-------------");
    centralizaTextoNoBotao(texto, fundo);
    textos.push_back(texto);
  }

  readMenuCarregamento();

  sf::RectangleShape botao(sf::Vector2f(300, 75)); // Tamanho dos botões
  botao.setPosition(sf::Vector2f((largura / 2) + 150, altura / 2 - 75 / 2));
  botao.setTexture(texturaBotao);
  botoes.push_back(botao);

  sf::Text texto;
  texto.setFont(*fonte);
  texto.setFillColor(sf::Color::White);
  texto.setCharacterSize(22);
  textos.push_back(texto);

  setBotaoTexto(7, "Voltar");

  if (!botoes.empty())
  {
    textos[itemSelecionado].setCharacterSize(26);
    centralizaTextoNoBotao(textos[itemSelecionado], botoes[itemSelecionado]);
  }
}

MenuCarregamento::~MenuCarregamento() {}

void MenuCarregamento::Update(const char *teclaPressionada)
{
  if (!acceptingCommands)
    return;
  if (strcmp(teclaPressionada, "Up") == 0)
    prevButton();
  if (strcmp(teclaPressionada, "Down") == 0)
    nextButton();
  if(strcmp(teclaPressionada, "Escape") == 0)
  {
    gerenciadorEstado.setEstadoJogo(estadoJogo::MENUINICIO);
  }
  else if (strcmp(teclaPressionada, "Enter") == 0)
  {
    acceptingCommands = false;
    int selectedItem = getSelectedItemIndex();
    if (selectedItem == 7)
    {
      gerenciadorEstado.setEstadoJogo(estadoJogo::MENUINICIO);
    }
    else
    {
      int fase = getFaseFromJson(filenames[selectedItem]);
      cout << fase << endl;
      if (fase == -1)
      {
        gerenciadorEstado.setEstadoJogo(estadoJogo::MENUINICIO);
      }
      else if (fase == 1)
      {
        gerenciadorEstado.setEstadoJogo(estadoJogo::FASE1);
      }
      else if (fase == 9) // fase2
      {
        gerenciadorEstado.setEstadoJogo(estadoJogo::FASE2);
      }
    }
  }
}

void MenuCarregamento::readMenuCarregamento()
{
  {
    DIR *dir;
    struct dirent *ent;
    int i = 0;
    std::string datetime;

    if ((dir = opendir(".")) != NULL) // Open current directory
    {
      while ((ent = readdir(dir)) != NULL)
      {
        std::string filename(ent->d_name);
        if (filename.size() >= 20 && filename.substr(0, 6) == "salvo_" && filename.substr(21) == ".json")
        {
          // Extract date and time components
          std::string year = filename.substr(6, 4);
          std::string month = filename.substr(10, 2);
          std::string day = filename.substr(12, 2);
          std::string hour = filename.substr(15, 2);
          std::string minute = filename.substr(17, 2);

          // Format as DD/MM/YY HH:MM
          datetime = day + "/" + month + "/" + year.substr(2) + " " + hour + ":" + minute;
          filenames.push_back(filename);
          setBotaoTexto(i, datetime);
          i++;
          cout << "Save found: " << filename << endl;
        }
        else
        {
          std::cerr << "Invalid filename format: " << filename << std::endl;
        }
      }
      closedir(dir);
    }
    else
    {
      std::cerr << "Unable to open the current directory" << std::endl;
    }
  }
}

void MenuCarregamento::executar()
{
  desenhar();
}

void MenuCarregamento::desenhar()
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

int MenuCarregamento::getFaseFromJson(string filename)
{
  std::ifstream file(filename);
  if (!file.is_open())
  {
    std::cerr << "Error: Unable to open the file " << filename << std::endl;
    return -1; // Return an error code
  }

  Json::Value root;
  file >> root;
  file.close();

  if (root.isMember("fase"))
  {
    int fase = root["fase"].asInt();
    return fase;
  }
  else
  {
    std::cerr << "Error: 'fase' attribute not found in " << filename << std::endl;
    return -1; // Return an error code if 'fase' is not found
  }
}

string MenuCarregamento::getSelectedSalve()
{
  return filenames[getSelectedItemIndex()];
}