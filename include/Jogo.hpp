#ifndef JOGO_HPP
#define JOGO_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <cstring>
#include "Entidades/Entidade.hpp"
#include "Entidades/Personagens/Personagem.hpp"
#include "Entidades/Personagens/Jogador.hpp"
#include "Entidades/Personagens/Inimigo.hpp"
#include "Entidades/Obstaculos/Obstaculo.hpp"
#include "Listas/ListaEntidades.hpp"
#include "Gerenciadores/Gerenciador_Grafico.hpp"
#include "Gerenciadores/Gerenciador_Estado.hpp"
#include "Gerenciadores/Gerenciador_Threads.hpp"
#include "Gerenciadores/Configuracoes.hpp"
#include "Ente.hpp"
#include "PerformanceMonitor.hpp"
#include "Menus/MenuInicio.hpp"
#include "Menus/MenuFimDeJogo.hpp"
#include "Menus/Leaderboard.hpp"
#include "Menus/Pause.hpp"
#include "Menus/MenuEscolhaPlayers.hpp"
#include "Menus/MenuCarregamento.hpp"
#include "Fases/Fase_Primeira.hpp"
#include "Fases/Fase_Segunda.hpp"

class Jogo
{
private:
    Gerenciador_Grafico &gerenciadorGrafico;
    Gerenciador_Estado &gerenciadorEstado;
    Gerenciador_Input &gerenciadorInput;
    Configuracoes &configuracoes;
    Gerenciador_Colisoes gerenciadorColisoes;
    Gerenciador_Threads gerenciadorThreads;
    PerformanceMonitor performanceMonitor;

    MenuInicio *menuInicio;
    Fase_Primeira *fase1;
    Fase_Segunda *fase2;
    MenuFimDeJogo *menuFimDeJogo;
    Leaderboard *leaderboard;
    Pause *pauseMenu;
    MenuEscolhaPlayers *menuEscolhaPlayers;
    MenuCarregamento *menuCarregamento;

public:
    Jogo();
    ~Jogo();
    void executar();
};

#endif // JOGO_HPP
