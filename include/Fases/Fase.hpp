#ifndef FASE_HPP
#define FASE_HPP

#include "Ente.hpp"
#include <SFML/Graphics.hpp>
#include "Gerenciadores/Gerenciador_Grafico.hpp"
#include "Gerenciadores/Gerenciador_Colisoes.hpp"
#include "Listas/ListaEntidades.hpp"
#include "Entidades/Plataforma.hpp"
#include "Entidades/Personagens/Jogador.hpp"
#include "Entidades/Obstaculos/Espinho.hpp"
#include "Gerenciadores/Gerenciador_Estado.hpp"

class Fase : public Ente
{
protected:
  sf::Sprite fundo;
  Gerenciador_Grafico &gerenciadorGrafico;
  Gerenciador_Colisoes gerenciadorColisoes;
  ListaEntidades plataformas;
  ListaEntidades entidades;
  Jogador *jogador;
  int pontos;
  int finalX;
  sf::Text vidasJogador;
  sf::Text pontosText;
  sf::Clock clock;

  void criarPlataformas(int qty_plt = 20);
  void criarCenario();
  void criaEspinhos();
  void atualizaVidaJogador();
  void atualizaPontos();
  void verificaFim();
  void fimDeJogo();

public:
  Fase();
  ~Fase();
  void desenhar();
  virtual void executar();
};

#endif // FASE_HPP