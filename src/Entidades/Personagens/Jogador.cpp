#include "Entidades/Personagens/Jogador.hpp"
#include <cmath> // Para usar std::max

const float GRAVIDADE = 9.8f;          // Aceleração da gravidade (em unidades por segundo^2)
const float TEMPO_FRAME = 0.16f;       // Duração de cada frame (em segundos) - para 60 FPS
const float COOLDOWN_PULO = 800.0f;    // Tempo de espera entre pulos (em milissegundos)
const float VELOCIDADE_CORRIDA = 1.5f; // Velocidade de corrida (em unidades por segundo)

Jogador::Jogador(float px, float py, int vidas) : Personagem(px, py, vidas),
                                                  velocidadeY(0), velocidadeX(25), noChao(false),
                                                  animacao(), direcao(1), state(IDLE), velocidadeCorrida(VELOCIDADE_CORRIDA * velocidadeX),
                                                  tempoDesdeUltimoPulo(0.0f) // Inicializa o tempo desde o último pulo
{
    animacao.addTrilha("idle", new TrilhaAnimacao(5, 15, 128, 79, 40, 3.0, 3.0, "./assets/Gangsters_1/Idle.png"));
    animacao.addTrilha("running", new TrilhaAnimacao(9, 10, 128, 80, 20, 3.0, 3.0, "./assets/Gangsters_1/Run.png"));
    animacao.addTrilha("walking", new TrilhaAnimacao(9, 10, 128, 81, 40, 3.0, 3.0, "./assets/Gangsters_1/Walk.png"));
    animacao.addTrilha("jump", new TrilhaAnimacao(9, 10, 128, 110, 35, 3.0, 3.0, "./assets/Gangsters_1/Jump.png"));
    animacao.setPosition(x, y);
    animacao.setScale(3.f, 3.f);
    setAnimationState();
}

void Jogador::setAnimationState()
{
    if (state == IDLE)
    {
        animacao.setTrilha("idle");
    }
    else if (state == WALK)
    {
        animacao.setTrilha("walking");
    }
    else if (state == RUN)
    {
        animacao.setTrilha("running");
    }
    else if (state == JUMP)
    {
        animacao.setTrilha("jump");
    }

    // Ajusta a escala com base na direção atual
    animacao.setScale(direcao * 3.f, 3.f);
}

void Jogador::atacar()
{
    // Implementação do ataque do jogador
}

void Jogador::setPosition(int px, int py)
{
    animacao.setPosition(px, py);
    Gerenciador_Grafico::getInstance().centerCamera(sf::Vector2f(px, py));
}
void Jogador::executar()
{
    aplicarGravidade();
    estadoJogador newState = IDLE;

    float elapsed_time = pGG->getElapsedTime();
    bool mudouDirecao = false;

    // Atualiza o tempo desde o último pulo
    tempoDesdeUltimoPulo += elapsed_time;

    // Verifica se o Shift está pressionado para correr
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    {
        velocidadeX = velocidadeCorrida; // Velocidade de corrida
        newState = RUN;

        // Executa a corrida na direção atual
        if (direcao == -1) // Esquerda
        {
            x -= velocidadeX * (elapsed_time / 100.0);
        }
        else if (direcao == 1) // Direita
        {
            x += velocidadeX * (elapsed_time / 100.0);
        }
    }
    else
    {
        // Retorna à velocidade normal de caminhada
        velocidadeX = velocidadeCorrida / VELOCIDADE_CORRIDA;
    }

    // Verifica se a tecla A (esquerda) está pressionada
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        if (direcao != -1)
        {
            mudouDirecao = true;
            direcao = -1;
        }
        x -= velocidadeX * (elapsed_time / 100.0);
        newState = (newState == RUN) ? RUN : WALK;
    }
    // Verifica se a tecla D (direita) está pressionada
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        if (direcao != 1)
        {
            mudouDirecao = true;
            direcao = 1;
        }
        x += velocidadeX * (elapsed_time / 100.0);
        newState = (newState == RUN) ? RUN : WALK;
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    {
        velocidadeX = velocidadeCorrida; // Velocidade de corrida
        if (direcao == -1)
        {
            x -= velocidadeX * (elapsed_time / 100.0);
        }
        else if (direcao == 1)
        {
            x += velocidadeX * (elapsed_time / 100.0);
        }
    }

    // Verifica o pulo
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        if (noChao && tempoDesdeUltimoPulo >= COOLDOWN_PULO)
        {
            velocidadeY = -sqrt(2 * GRAVIDADE * 150);
            noChao = false;
            tempoDesdeUltimoPulo = 0.0f; // Reseta o tempo desde o último pulo
        }
    }

    if (!noChao)
    {
        newState = JUMP;
    }

    // Atualiza a animação se a direção ou o estado mudar
    if (mudouDirecao || newState != state)
    {
        state = newState;
        setAnimationState();
    }

    animacao.update();
    setPosition(x, y);
}

void Jogador::aplicarGravidade()
{
    velocidadeY += GRAVIDADE * TEMPO_FRAME; // Aceleração devido à gravidade
    y += velocidadeY * TEMPO_FRAME;
}

void Jogador::desenhar()
{
    animacao.desenhar();
}

sf::Vector2f Jogador::getCenter()
{
    return animacao.getCenter();
}

sf::FloatRect Jogador::getSize()
{
    return animacao.getSize();
}

void Jogador::lidarColisao(sf::Vector2f intersecao, Entidade *other)
{
    sf::FloatRect otherBounds = other->getSize();
    sf::FloatRect jogadorBounds = getSize();

    // Imprimir a interseção para debug
    std::cout << "Colisão: x=" << intersecao.x << ", y=" << intersecao.y << std::endl;

    if (intersecao.y != 0)
    {
        // Ajusta a posição do jogador para evitar sobreposição
        if (other->getCenter().y > getCenter().y)
        {
            y -= intersecao.y; // Ajusta a posição do jogador para cima

            // Corrige a altura para garantir que o jogador fique exatamente na plataforma
            y = otherBounds.top - jogadorBounds.height / 2;

            velocidadeY = 0; // Zera a velocidade Y para simular estar no chão
            noChao = true;   // Marca o jogador como estando no chão
        }
        else
        {
            y += intersecao.y; // Ajusta a posição do jogador para baixo
        }
    }
    setPosition(x, y);
}