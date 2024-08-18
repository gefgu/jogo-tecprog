#ifndef FASE_HPP
#define FASE_HPP

#include "Ente.hpp"
#include <SFML/Graphics.hpp>
#include "Gerenciadores/Gerenciador_Grafico.hpp"
#include "Gerenciadores/Gerenciador_Colisoes.hpp"
#include "Listas/ListaEntidades.hpp"
#include "Entidades/Plataforma.hpp"
#include "Entidades/Personagens/Jogador.hpp"

class Fase : public Ente
{
protected:
  sf::Sprite fundo;
  Gerenciador_Grafico &gerenciadorGrafico;
  Gerenciador_Colisoes gerenciadorColisoes;
  ListaEntidades plataformas;
  ListaEntidades entidades;
  Jogador *jogador;
  void criarPlataformas(int qty_plt = 100);
  void criarCenario();

public:
  Fase();
  ~Fase();
  void desenhar();
  virtual void executar();
};

#endif // FASE_HPP