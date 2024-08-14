#include "Menu.hpp"
#include <iostream>

Menu::Menu(float largura, float altura) : itemSelecionado(0), gerenciadorGrafico(Gerenciador_Grafico::getInstance())
{
    sf::Texture *texturaFundo = gerenciadorGrafico.carregaTextura("./assets/images/fundo_menu.png");
    if (!texturaFundo)
    {
        std::cerr << "Erro ao carregar a textura de fundo!" << std::endl;
        // Handle error accordingly, possibly return or use a fallback
    }
    fundo.setTexture(*texturaFundo);
    fundo.setPosition(0, 0);
    fundo.setScale(largura / fundo.getTexture()->getSize().x, altura / fundo.getTexture()->getSize().y);

    sf::Texture *texturaBotao = gerenciadorGrafico.carregaTextura("./assets/images/botoes.png");
    if (!texturaBotao)
    {
        std::cerr << "Erro ao carregar a textura dos botões!" << std::endl;
    }

    if (!fonte.loadFromFile("./assets/fonts/BACKTO1982.TTF"))
    {
        std::cerr << "Erro ao carregar a fonte!" << std::endl;
    }
    else
    {
        std::cout << "Fonte carregada com sucesso." << std::endl;
    }

    // Criar botões
    for (int i = 0; i < 4; i++)
    {
        sf::RectangleShape botao(sf::Vector2f(300, 100)); // Tamanho dos botões
        botao.setPosition(sf::Vector2f((largura / 2) - 150, (altura / (5 + 1) * (i + 1))));
        botao.setTexture(texturaBotao);
        botoes.push_back(botao);

        sf::Text texto;
        texto.setFont(fonte);
        texto.setFillColor(sf::Color::White);
        texto.setCharacterSize(24);
        texto.setPosition(botao.getPosition().x + 50, botao.getPosition().y + 25);
        textos.push_back(texto);
    }

    // Definir os textos dos botões
    setBotaoTexto(0, "Stage 1", fonte);
    setBotaoTexto(1, "Stage 2", fonte);
    setBotaoTexto(2, "Load Games", fonte);
    setBotaoTexto(3, "Settings", fonte);

    if (!botoes.empty())
    {
        botoes[itemSelecionado].setFillColor(sf::Color::Red); // Destacar o botão selecionado
        std::cout << "Botão " << itemSelecionado << " destacado." << std::endl;
    }
}

Menu::~Menu()
{
    std::cout << "Destruindo menu." << std::endl;
}

void Menu::draw(sf::RenderWindow &window)
{
    // Verifique se a textura do fundo está carregada corretamente antes de desenhar
    if (fundo.getTexture() != NULL)
    {
        window.draw(fundo);
    }
    else
    {
        std::cerr << "Erro: Textura de fundo não carregada." << std::endl;
    }

    for (size_t i = 0; i < botoes.size(); i++)
    {
        window.draw(botoes[i]);
        window.draw(textos[i]);
    }
}

void Menu::moveUp()
{
    std::cout << "Movendo para cima: itemSelecionado antes = " << itemSelecionado << std::endl;
    if (itemSelecionado - 1 >= 0)
    {
        botoes[itemSelecionado].setFillColor(sf::Color::White);
        itemSelecionado--;
        botoes[itemSelecionado].setFillColor(sf::Color::Red);
    }
    std::cout << "itemSelecionado depois = " << itemSelecionado << std::endl;
}

void Menu::moveDown()
{
    std::cout << "Movendo para baixo: itemSelecionado antes = " << itemSelecionado << std::endl;
    if (itemSelecionado + 1 < botoes.size())
    {
        botoes[itemSelecionado].setFillColor(sf::Color::White);
        itemSelecionado++;
        botoes[itemSelecionado].setFillColor(sf::Color::Red);
    }
    std::cout << "itemSelecionado depois = " << itemSelecionado << std::endl;
}

int Menu::getSelectedItemIndex() const
{
    return itemSelecionado;
}

void Menu::setBotaoTexto(int index, const std::string &texto, const sf::Font &fonte)
{
    if (index >= 0 && index < textos.size())
    {
        textos[index].setFont(fonte);
        textos[index].setString(texto);
    }
}

const sf::Font &Menu::getFonte() const
{
    return fonte;
}
