#ifndef JOGO_HPP
#define JOGO_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Entidades/Entidade.hpp"
#include "Entidades/Personagens/Personagem.hpp"
#include "Entidades/Personagens/Jogador.hpp"
#include "Entidades/Personagens/Inimigo.hpp"
#include "Entidades/Obstaculos/Obstaculo.hpp"
#include "Listas/ListaEntidades.hpp"
#include "Gerenciadores/Gerenciador_Grafico.hpp"
#include "Gerenciadores/Gerenciador_Estado.hpp"
#include "Ente.hpp"
#include "Menu.hpp" // Incluí o Menu
#include "Fases/Fase_Primeira.hpp"

class Jogo
{
private:
    Gerenciador_Grafico &gerenciadorGrafico;
    Gerenciador_Estado &gerenciadorEstado;
    Menu menu;
    sf::Font fonte;
    Fase_Primeira fase1;

public:
    Jogo();
    ~Jogo();
    void executar();
    void processarMenu(); // Função para processar o menu
};

#endif // JOGO_HPP
