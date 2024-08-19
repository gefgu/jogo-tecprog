#include "Menus/MenuFimDeJogo.hpp"
#include <iostream>

MenuFimDeJogo::MenuFimDeJogo(int p) : gerenciadorGrafico(Gerenciador_Grafico::getInstance()), gerenciadorEstado(Gerenciador_Estado::getInstance()), pontos(p)
{
  int largura = gerenciadorGrafico.getWindowSize().x;
  int altura = gerenciadorGrafico.getWindowSize().y;
  gerenciadorGrafico.centerCamera(sf::Vector2f(largura / 2, altura));
  sf::Texture *texturaFundo = gerenciadorGrafico.carregaTextura("./assets/images/fundo_fase_1.png");
  fundo.setTexture(*texturaFundo);
  fundo.setPosition(0, 0);
  fundo.setScale(largura / fundo.getTexture()->getSize().x, altura / fundo.getTexture()->getSize().y);

  // sf::Texture *texturaBotao = gerenciadorGrafico.carregaTextura("./assets/images/botao.png");
  // if (!texturaBotao)
  // {
  //   std::cerr << "Erro ao carregar a textura dos botões!" << std::endl;
  // }

  sf::Font *fonte = gerenciadorGrafico.carregaFonte("./assets/fonts/BACKTO1982.TTF");
  textoFinal.setFont(*fonte);
  textoFinal.setFillColor(sf::Color::White);
  textoFinal.setCharacterSize(48);
  textoFinal.setString("Vc fez " + to_string(pontos) + " Pontos!!");
  sf::Vector2f pos = gerenciadorGrafico.getTopLeftPosition();
  textoFinal.setPosition(pos.x + largura / 2, pos.y + 75);
  cout << "Criando MENU FIM" << endl;
}

MenuFimDeJogo::~MenuFimDeJogo()
{
  std::cout << "Destruindo menu." << std::endl;
}

void MenuFimDeJogo::desenhar()
{
  gerenciadorGrafico.centerCamera(sf::Vector2f(gerenciadorGrafico.getWindowSize().x / 2, gerenciadorGrafico.getWindowSize().y / 2));
  gerenciadorGrafico.drawSprite(fundo);
  gerenciadorGrafico.drawText(textoFinal);
}

void MenuFimDeJogo::executar()
{
  sf::Event event;
  while (gerenciadorGrafico.pollEvent(event))
  {
    if (event.type == sf::Event::Closed)
    {
      gerenciadorGrafico.fecharJanela();
    }
    else if (event.type == sf::Event::KeyPressed)
    {
      if (event.key.code == sf::Keyboard::Escape)
      {
        gerenciadorEstado.setEstadoJogo(estadoJogo::MENU);
      }
    }
  }
  desenhar();
}
