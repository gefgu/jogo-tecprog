#include "Menus/MenuInicio.hpp"

MenuInicio::MenuInicio() : Menu()
{
  int largura = pGG->getWindowSize().x;
  int altura = pGG->getWindowSize().y;

  sf::Texture *texturaBotao = pGG->carregaTextura("./assets/images/botao.png");

  sf::Font *fonte = pGG->carregaFonte("./assets/fonts/BACKTO1982.TTF");

  // Criar botões
  for (int i = 0; i < 4; i++)
  {
    sf::RectangleShape botao(sf::Vector2f(300, 50)); // Tamanho dos botões
    botao.setPosition(sf::Vector2f((largura / 2) - 150, (altura / (5 + 1) * (i + 1))));
    botao.setTexture(texturaBotao);
    botoes.push_back(botao);

    sf::Text texto;
    texto.setFont(*fonte);
    texto.setFillColor(sf::Color::White);
    texto.setCharacterSize(22);
    centralizaTextoNoBotao(texto, botao);
    textos.push_back(texto);
  }

  // Definir os textos dos botões
  setBotaoTexto(0, "Stage 1", fonte);
  setBotaoTexto(1, "Stage 2", fonte);
  setBotaoTexto(2, "Load Games", fonte);
  setBotaoTexto(3, "Leaderboard", fonte);

  if (!botoes.empty())
  {
    textos[itemSelecionado].setCharacterSize(26);
    centralizaTextoNoBotao(textos[itemSelecionado], botoes[itemSelecionado]); // Aumentar o tamanho da fonte do botão selecionado
    std::cout << "Botão " << itemSelecionado << " destacado." << std::endl;
  }
}

MenuInicio::~MenuInicio() {}

void MenuInicio::executar()
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
        nextButton();
      }
      else if (event.key.code == sf::Keyboard::Down)
      {
        prevButton();
      }
      else if (event.key.code == sf::Keyboard::Enter)
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
          // Carregar jogo salvo
        }
      }
    }
  }
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