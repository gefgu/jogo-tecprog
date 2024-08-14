#ifndef FASE_HPP
#define FASE_HPP

#include "Ente.hpp"
#include <SFML/Graphics.hpp>
#include "Gerenciadores/Gerenciador_Grafico.hpp"

class Fase : public Ente
{
private:
  sf::Sprite fundo;
  Gerenciador_Grafico &gerenciadorGrafico;

public:
  Fase();
  ~Fase();
  void desenhar();
  virtual void executar() = 0;
  void gerenciar_colisoes();
  void criarInimMedios();
  void criarObstaculosMedios();
};

#endif // FASE_HPP