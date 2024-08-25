#include "Menus/MenuInicio.hpp"
#include <cstring>

MenuInicio::MenuInicio() : Menu()
{
  int largura = pGG->getWindowSize().x;
  int altura = pGG->getWindowSize().y;

  sf::Texture *texturaBotao = pGG->carregaTextura("./assets/images/botao.png");

  sf::Font *fonte = pGG->carregaFonte("./assets/fonts/BACKTO1982.TTF");

  // Criar botões
  for (int i = 0; i < 4; i++)
  {
    sf::RectangleShape botao(sf::Vector2f(300, 75)); // Tamanho dos botões
    botao.setPosition(sf::Vector2f((largura / 2) - 150, (150 + 150 * i)));
    botao.setTexture(texturaBotao);
    botoes.push_back(botao);

    sf::Text texto;
    texto.setFont(*fonte);
    texto.setFillColor(sf::Color::White);
    texto.setCharacterSize(22);
    textos.push_back(texto);
  }

  // Definir os textos dos botões
  setBotaoTexto(0, "Stage 1");
  setBotaoTexto(1, "Stage 2");
  setBotaoTexto(2, "Load Games");
  setBotaoTexto(3, "Leaderboard");

  if (!botoes.empty())
  {
    textos[itemSelecionado].setCharacterSize(26);
    centralizaTextoNoBotao(textos[itemSelecionado], botoes[itemSelecionado]); // Aumentar o tamanho da fonte do botão selecionado
    std::cout << "Botão " << itemSelecionado << " destacado." << std::endl;
  }
}

MenuInicio::~MenuInicio() {}

void MenuInicio::Update(const char *teclaPressionada)
{
  cout << teclaPressionada << endl;
  if (strcmp(teclaPressionada, "Up") == 0)
  {
    prevButton();
  }
  if (strcmp(teclaPressionada, "Down") == 0)
  {
    nextButton();
  }
  else if (strcmp(teclaPressionada, "Enter") == 0)
  {
    int selectedItem = getSelectedItemIndex();
    if (selectedItem == 0)
    {
      gerenciadorEstado.setEstadoJogo(estadoJogo::FASE1);
    }
    else if (selectedItem == 1)
    {
      // Começar Fase 2
      gerenciadorEstado.setEstadoJogo(estadoJogo::FASE2);
    }
    else if (selectedItem == 2)
    {
      // Configurações
    }
    else if (selectedItem == 3)
    {
      gerenciadorEstado.setEstadoJogo(estadoJogo::LEADERBOARD);
    }
  }
}

void MenuInicio::executar()
{
  desenhar();
}

void MenuInicio::desenhar()
{
  pGG->centerCamera(sf::Vector2f(pGG->getWindowSize().x / 2, pGG->getWindowSize().y / 2));
  pGG->draw(fundo);

  for (size_t i = 0; i < botoes.size(); i++)
  {
    pGG->draw(botoes[i]);
    pGG->draw(textos[i]);
  }
}