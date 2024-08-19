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
#include "Gerenciadores/Gerenciador_Threads.hpp"
#include "Ente.hpp"
#include "PerformanceMonitor.hpp"
#include "Menus/Menu.hpp"
#include "Menus/MenuFimDeJogo.hpp"
#include "Fases/Fase_Primeira.hpp"
#include "Fases/Fase_Segunda.hpp"

class Jogo
{
private:
    Gerenciador_Grafico &gerenciadorGrafico;
    Gerenciador_Estado &gerenciadorEstado;
    Gerenciador_Colisoes gerenciadorColisoes;
    Gerenciador_Threads gerenciadorThreads;
    PerformanceMonitor performanceMonitor;

    Menu menu;
    sf::Font fonte;
    Fase_Primeira *fase1;
    Fase_Segunda *fase2;
    MenuFimDeJogo *menuFimDeJogo;

public:
    Jogo();
    ~Jogo();
    void executar();
    void processarMenu(); // Função para processar o menu
};

#endif // JOGO_HPP
