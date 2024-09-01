#include "Menus/MenuEscolhaPlayers.hpp"
#include <cstring>

MenuEscolhaPlayers::MenuEscolhaPlayers(estadoJogo proxFase) : Menu(), fase(proxFase), configuracoes(Configuracoes::getInstance())
{
  int largura = pGG->getWindowSize().x;
  int altura = pGG->getWindowSize().y;

  sf::Texture *texturaBotao = pGG->carregaTextura("./assets/images/botao.png");

  sf::Font *fonte = pGG->carregaFonte("./assets/fonts/BACKTO1982.TTF");

  // Criar botões
  for (int i = 0; i < 2; i++)
  {
    sf::RectangleShape botao(sf::Vector2f(300, 75)); // Tamanho dos botões
    botao.setPosition(sf::Vector2f((largura / 2) - 150, (300 + 150 * i)));
    botao.setTexture(texturaBotao);
    botoes.push_back(botao);

    sf::Text texto;
    texto.setFont(*fonte);
    texto.setFillColor(sf::Color::White);
    texto.setCharacterSize(22);
    textos.push_back(texto);
  }

  // Definir os textos dos botões
  setBotaoTexto(0, "1 Player");
  setBotaoTexto(1, "2 Player");

  if (!botoes.empty())
  {
    textos[itemSelecionado].setCharacterSize(26);
    centralizaTextoNoBotao(textos[itemSelecionado], botoes[itemSelecionado]); // Aumentar o tamanho da fonte do botão selecionado
    std::cout << "Botão " << itemSelecionado << " destacado." << std::endl;
  }
}

MenuEscolhaPlayers::~MenuEscolhaPlayers() {}

void MenuEscolhaPlayers::Update(const char *teclaPressionada)
{
  if (strcmp(teclaPressionada, "Up") == 0)
    prevButton();
  if (strcmp(teclaPressionada, "Down") == 0)
    nextButton();
  if (strcmp(teclaPressionada, "Escape") == 0)
    gerenciadorEstado.setEstadoJogo(MENUINICIO);
  else if (strcmp(teclaPressionada, "Enter") == 0)
  {
    int selectedItem = getSelectedItemIndex();

    configuracoes.setDoisJogadores((bool)selectedItem);

    gerenciadorEstado.setEstadoJogo(fase);
  }
}

void MenuEscolhaPlayers::executar()
{
  desenhar();
}

void MenuEscolhaPlayers::desenhar()
{
  pGG->centerCamera(sf::Vector2f(pGG->getWindowSize().x / 2, pGG->getWindowSize().y / 2));
  pGG->draw(fundo);

  for (size_t i = 0; i < botoes.size(); i++)
  {
    pGG->draw(botoes[i]);
    pGG->draw(textos[i]);
  }
}
