#ifndef FASE_HPP
#define FASE_HPP

#include "Ente.hpp"
#include <SFML/Graphics.hpp>
#include "Gerenciadores/Gerenciador_Grafico.hpp"
#include "Gerenciadores/Gerenciador_Colisoes.hpp"

class Fase : public Ente
{
private:
  sf::Sprite fundo;
  Gerenciador_Grafico &gerenciadorGrafico;
  Gerenciador_Colisoes gerenciadorColisoes;

public:
  Fase();
  ~Fase();
  void desenhar();
  virtual void executar() = 0;
  void gerenciar_colisoes();
  void criarCenario();
};

#endif // FASE_HPP