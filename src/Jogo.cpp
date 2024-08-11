#include "Jogo.hpp"

Jogo::Jogo() : gerenciadorGrafico()
{
    Ente::setGerenciadorGrafico(&gerenciadorGrafico);
    jogador = new Jogador(100, 100, 3);
    entidades.incluir(jogador);
    // entidades.push_back(new Inimigo(400, 300, 1, 5.0f));
    // entidades.push_back(new Obstaculo(200, 150, true));
}

Jogo::~Jogo()
{
    // for (Entidade *e : entidades)
    // {
    //     delete e;
    // }
}

void Jogo::adicionarEntidade(Entidade *e)
{
    // entidades.push_back(e);
}

void Jogo::executar()
{
    while (gerenciadorGrafico.isWindowOpen())
    {
        gerenciadorGrafico.clear();

        // execute all
        entidades.executar();
        // render all
        entidades.desenhar();

        gerenciadorGrafico.display();
        }
}
