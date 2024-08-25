#include "Menus/Menu.hpp"
#include <iostream>

Menu::Menu() : gerenciadorEstado(Gerenciador_Estado::getInstance()), _gerenciadorInput(Gerenciador_Input::getInstance()), itemSelecionado(0)
{
    fundos.clear();
    botoes.clear();
    textos.clear();
    textosDecorativos.clear();
    int largura = pGG->getWindowSize().x;
    int altura = pGG->getWindowSize().y;
    sf::Texture *texturaFundo = pGG->carregaTextura("./assets/images/fundo_menu.png");
    fundo.setTexture(*texturaFundo);
    fundo.setPosition(0, 0);
    float scaleX = static_cast<float>(largura) / fundo.getTexture()->getSize().x;
    float scaleY = static_cast<float>(altura) / fundo.getTexture()->getSize().y;
    fundo.setScale(scaleX, scaleY);

    // observer
    _gerenciadorInput.Attach(this);
}

Menu::~Menu()
{
    botoes.clear();
    textos.clear();
    fundos.clear();
    textosDecorativos.clear();

    // observer
    _gerenciadorInput.Detach(this);
}

void Menu::prevButton()
{
    std::cout << "Movendo para cima: itemSelecionado antes = " << itemSelecionado << std::endl;
    if (itemSelecionado - 1 >= 0)
    {
        textos[itemSelecionado].setCharacterSize(22);                             // Redefine o tamanho da fonte para o padrão
        centralizaTextoNoBotao(textos[itemSelecionado], botoes[itemSelecionado]); // Recentraliza o texto

        itemSelecionado--;
        textos[itemSelecionado].setCharacterSize(26);                             // Aumenta o tamanho da fonte do texto selecionado
        centralizaTextoNoBotao(textos[itemSelecionado], botoes[itemSelecionado]); // Recentraliza o texto
    }
    std::cout << "itemSelecionado depois = " << itemSelecionado << std::endl;
}

void Menu::nextButton()
{
    std::cout << "Movendo para baixo: itemSelecionado antes = " << itemSelecionado << std::endl;
    if (itemSelecionado + 1 < botoes.size())
    {
        textos[itemSelecionado].setCharacterSize(22);                             // Redefine o tamanho da fonte para o padrão
        centralizaTextoNoBotao(textos[itemSelecionado], botoes[itemSelecionado]); // Recentraliza o texto

        itemSelecionado++;
        textos[itemSelecionado].setCharacterSize(26);                             // Aumenta o tamanho da fonte do texto selecionado
        centralizaTextoNoBotao(textos[itemSelecionado], botoes[itemSelecionado]); // Recentraliza o texto
    }
    std::cout << "itemSelecionado depois = " << itemSelecionado << std::endl;
}

int Menu::getSelectedItemIndex() const
{
    return itemSelecionado;
}

void Menu::centralizaTextoNoBotao(sf::Text &texto, const sf::RectangleShape &botao)
{
    float posX = botao.getPosition().x + (botao.getSize().x / 2.f) - (texto.getLocalBounds().width / 2.f);

    float posY = botao.getPosition().y + (botao.getSize().y / 2.f) - (texto.getLocalBounds().height / 2.f) - texto.getLocalBounds().top;

    texto.setPosition(posX, posY);
}

void Menu::setBotaoTexto(int index, const std::string &texto)
{
    if (index >= 0 && index < textos.size())
    {
        textos[index].setString(texto);
        centralizaTextoNoBotao(textos[index], botoes[index]);
    }
}

void Menu::setFundoTexto(int index, const std::string &texto)
{
    if (index >= 0 && index < textosDecorativos.size())
    {
        textosDecorativos[index].setString(texto);
        centralizaTextoNoBotao(textosDecorativos[index], fundos[index]);
    }
}