#include "Menu.hpp"
#include <iostream>

Menu::Menu(float largura, float altura) : itemSelecionado(0), gerenciadorGrafico(Gerenciador_Grafico::getInstance()), gerenciadorEstado(Gerenciador_Estado::getInstance())
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

    sf::Texture *texturaBotao = gerenciadorGrafico.carregaTextura("./assets/images/botao.png");
    if (!texturaBotao)
    {
        std::cerr << "Erro ao carregar a textura dos botões!" << std::endl;
    }

    sf::Font *fonte = gerenciadorGrafico.carregaFonte("./assets/fonts/BACKTO1982.TTF");

    // Criar botões
    for (int i = 0; i < 4; i++)
    {
        sf::RectangleShape botao(sf::Vector2f(300, 50)); // Tamanho dos botões
        botao.setPosition(sf::Vector2f((largura / 2) - 150, (altura / (5 + 1) * (i + 1))));
        botao.setTexture(texturaBotao);
        botoes.push_back(botao);

        sf::Text texto;
        texto.setFont(*fonte);
        texto.setFillColor(sf::Color::White);
        texto.setCharacterSize(22);
        centralizaTextoNoBotao(texto, botao);
        textos.push_back(texto);
    }

    // Definir os textos dos botões
    setBotaoTexto(0, "Stage 1", fonte);
    setBotaoTexto(1, "Stage 2", fonte);
    setBotaoTexto(2, "Load Games", fonte);
    setBotaoTexto(3, "Leaderboard", fonte);

    if (!botoes.empty())
    {
        textos[itemSelecionado].setCharacterSize(26);
        centralizaTextoNoBotao(textos[itemSelecionado], botoes[itemSelecionado]); // Aumentar o tamanho da fonte do botão selecionado
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
        textos[itemSelecionado].setCharacterSize(22);                             // Redefine o tamanho da fonte para o padrão
        centralizaTextoNoBotao(textos[itemSelecionado], botoes[itemSelecionado]); // Recentraliza o texto

        itemSelecionado--;
        textos[itemSelecionado].setCharacterSize(26);                             // Aumenta o tamanho da fonte do texto selecionado
        centralizaTextoNoBotao(textos[itemSelecionado], botoes[itemSelecionado]); // Recentraliza o texto
    }
    std::cout << "itemSelecionado depois = " << itemSelecionado << std::endl;
}

void Menu::moveDown()
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

void Menu::setBotaoTexto(int index, const std::string &texto, sf::Font *fonte)
{
    if (index >= 0 && index < textos.size())
    {
        textos[index].setFont(*fonte);
        textos[index].setString(texto);
        centralizaTextoNoBotao(textos[index], botoes[index]); // Recentraliza o texto após a atualização
    }
}

void Menu::executar()
{
    sf::Event event;
    while (gerenciadorGrafico.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            gerenciadorGrafico.fecharJanela();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Up)
            {
                moveUp();
            }
            else if (event.key.code == sf::Keyboard::Down)
            {
                moveDown();
            }
            else if (event.key.code == sf::Keyboard::Enter)
            {
                int selectedItem = getSelectedItemIndex();
                if (selectedItem == 0)
                {
                    gerenciadorEstado.setEstadoJogo(estadoJogo::FASE1);
                }
                else if (selectedItem == 1)
                {
                    // Começar Fase 2
                    // menuAtivo = false;
                }
                else if (selectedItem == 2)
                {
                    // Configurações
                }
                else if (selectedItem == 3)
                {
                    // Carregar jogo salvo
                }
            }
        }
    }

    draw(gerenciadorGrafico.getWindow());
}