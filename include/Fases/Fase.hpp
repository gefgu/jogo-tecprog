#ifndef FASE_HPP
#define FASE_HPP

#include "Ente.hpp"
#include <SFML/Graphics.hpp>
#include "Gerenciadores/Gerenciador_Grafico.hpp"
#include "Gerenciadores/Gerenciador_Colisoes.hpp"
#include "Gerenciadores/Gerenciador_Estado.hpp"
#include "Listas/ListaEntidades.hpp"
#include "Entidades/Plataforma.hpp"
#include "Entidades/Personagens/Jogador.hpp"
#include "Entidades/Obstaculos/Espinho.hpp"
#include "Entidades/Obstaculos/Lixo.hpp"
#include "Entidades/Personagens/Fighter.hpp"

class Fase : public Ente
{
protected:
  sf::Sprite fundo;
  Gerenciador_Colisoes gerenciadorColisoes;
  ListaEntidades plataformas;
  ListaEntidades entidades;
  Jogador *jogador;
  int pontos;
  int finalX;
  sf::Text vidasJogador;
  sf::Text pontosText;
  sf::Clock clock;
  ObjetoEstatico caixaDeCorreio;

  void criarPlataformas(int qty_plt);
  virtual void criarCenario() = 0;
  void criaEspinhos();
  void criaLixos();
  void criaFighters();
  void atualizaVidaJogador();
  void atualizaPontos();
  void verificaFim();
  void fimDeJogo();

public:
  Fase(int qty_plt);
  ~Fase();
  void desenhar();
  virtual void executar();
  int getPontos();
};

#endif // FASE_HPP