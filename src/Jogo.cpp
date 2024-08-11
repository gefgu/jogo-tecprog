#include "Jogo.hpp"

Jogo::Jogo() : window(sf::VideoMode(800, 600), "Meu Jogo")
{
    // jogador = new Jogador(100, 100, 3);
    // entidades.push_back(jogador);
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
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        // Desenha o mapa
        // mapa.desenhar(window);

        // for (Entidade *e : entidades)
        // {
        //     e->executar();
        //     e->desenhar(window);
        // }

        window.display();
    }
}
