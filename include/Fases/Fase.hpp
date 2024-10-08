#ifndef FASE_HPP
#define FASE_HPP

#include "Ente.hpp"
#include <SFML/Graphics.hpp>
#include "Gerenciadores/Gerenciador_Grafico.hpp"
#include "Gerenciadores/Gerenciador_Colisoes.hpp"
#include "Gerenciadores/Gerenciador_Estado.hpp"
#include "Listas/ListaEntidades.hpp"
#include "Entidades/Obstaculos/Plataforma.hpp"
#include "Entidades/Personagens/Jogador.hpp"
#include "Entidades/Obstaculos/Espinho.hpp"
#include "Entidades/Obstaculos/Lixo.hpp"
#include "Entidades/Obstaculos/Mina.hpp"
#include "Entidades/Personagens/Fighter.hpp"
#include "Entidades/Projetil.hpp"
#include "Entidades/Granada.hpp"
#include "Entidades/Personagens/SoldadoChefe.hpp"
#include "Controladores/Observer.hpp"

class Fase : public Ente, Observer
{
protected:
  sf::Sprite fundo;
  Gerenciador_Colisoes gerenciadorColisoes;
  Gerenciador_Input &_gerenciadorInput;
  ListaEntidades plataformas;
  ListaEntidades entidades;
  Jogador *jogador;
  Jogador *jogador2;
  int pontos;
  int finalX;
  sf::Text vidasJogador;
  sf::Text vidasJogador2;
  sf::Text pontosText;
  sf::Clock clock;
  int segundosDesdeInicio;
  ObjetoEstatico caixaDeCorreio;
  bool temPlayerDois;

  void criarPlataformas(int qty_plt);
  virtual void criarCenario() = 0;
  void criaEspinhos();
  void criaLixos();
  void criaFighters();
  void atualizaVidaJogador();
  void atualizaPontos();
  void verificaFim();
  void fimDeJogo();
  void centralizaCamera();
  void loadFromJson(string filename);

public:
  Fase(string filename = "", int pontos_iniciais = 1000, int qty_plt = 50, bool temP2 = false);
  ~Fase();
  void desenhar();
  virtual void executar();
  int getPontos();
  Projetil *addProjetil(int px, int py, int direcao, tipoDeEntidade atirador);
  Granada *addGranada(int px, int py, int direcao, tipoDeEntidade atirador);
  void alteraPontos(int soma);
  void Update(const char *teclaPressionada);
  void saveEntitiesToJson();
};

#endif // FASE_HPP