#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string> // Para usar std::string
#include "Gerenciadores/Gerenciador_Grafico.hpp"
#include "Gerenciadores/Gerenciador_Estado.hpp"
#include "Ente.hpp"

class Menu : public Ente
{
protected:
    sf::Sprite fundo; // Fundo do menu
    Gerenciador_Estado &gerenciadorEstado;

    void setBotaoTexto(int index, const std::string &texto, sf::Font *fonte);

public:
    Menu();
    ~Menu();

    virtual void desenhar() = 0;
    virtual void executar() = 0;
};

#endif // MENU_HPP
