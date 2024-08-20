#include "Entidades/Personagens/Jogador.hpp"
#include <cmath> // Para usar std::max

const float GRAVIDADE = 9.8f;          // Aceleração da gravidade (em unidades por segundo^2)
const float TEMPO_FRAME = 0.16f;       // Duração de cada frame (em segundos) - para 60 FPS
const float COOLDOWN_PULO = 800.0f;    // Tempo de espera entre pulos (em milissegundos)
const float VELOCIDADE_CORRIDA = 1.5f; // Velocidade de corrida (em unidades por segundo)

const float COOLDOWN_ESPINHO = 500.0f;

const float COOLDOWN_PISO = 75.f;

const float SCALING_FACTOR = 3.f;

Jogador::Jogador(int px, int py, int vidas) : Personagem(px, py, 25, 0, vidas),
                                              noChao(false),
                                              animacao(), direcao(1), state(IDLE), velocidadeCorrida(VELOCIDADE_CORRIDA * velocidadeX),
                                              tempoDesdeUltimoPulo(0.0f),
                                              tempoDesdeUltimoEspinho(COOLDOWN_ESPINHO),
                                              tempoDesdeUltimoPiso(COOLDOWN_PISO)

{
    animacao.addTrilha("idle", new TrilhaAnimacao(5, 15, 128, 128, 3.0, 3.0, "./assets/Gangsters_1/Idle.png"));
    animacao.addTrilha("running", new TrilhaAnimacao(9, 10, 128, 128, 3.0, 3.0, "./assets/Gangsters_1/Run.png"));
    animacao.addTrilha("walking", new TrilhaAnimacao(9, 10, 128, 128, 3.0, 3.0, "./assets/Gangsters_1/Walk.png"));
    animacao.addTrilha("jump", new TrilhaAnimacao(9, 10, 128, 128, 3.0, 3.0, "./assets/Gangsters_1/Jump.png"));
    animacao.setPosition(px, py);
    animacao.setScale(SCALING_FACTOR, SCALING_FACTOR);
    setColisionBoxSize(sf::Vector2f(40 * SCALING_FACTOR, 128 * SCALING_FACTOR));
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
    animacao.setScale(direcao * SCALING_FACTOR, SCALING_FACTOR);
}

void Jogador::atacar()
{
    // Implementação do ataque do jogador
}

void Jogador::setPosition(int px, int py)
{
    animacao.setPosition(px, py);
    colisionBox.setPosition(px, py);
    pGG->centerCamera(sf::Vector2f(px, py));
}

void Jogador::mover()
{
    estadoJogador newState = IDLE;
    bool mudouDirecao = false;
    float elapsed_time = pGG->getElapsedTime();
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
            y -= 10;
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
}

void Jogador::executar()
{
    // Reset noChao at the start of each frame
    noChao = tempoDesdeUltimoPiso <= COOLDOWN_PISO;

    aplicarGravidade();
    float elapsed_time = pGG->getElapsedTime();

    // Atualiza o tempo desde o último pulo
    tempoDesdeUltimoPulo += elapsed_time;
    tempoDesdeUltimoEspinho += elapsed_time;
    tempoDesdeUltimoPiso += elapsed_time;

    mover();

    if (y > 2000)
    {
        recebeDano(1);
        y = 0;
        x = 0;
        velocidadeY = 0;
    }

    animacao.update();
    setPosition(x, y);
}

void Jogador::aplicarGravidade()
{
    if (!noChao)
    {
        velocidadeY += GRAVIDADE * TEMPO_FRAME; // Aceleração devido à gravidade
        y += velocidadeY * TEMPO_FRAME;
    }
}

void Jogador::desenhar()
{
    animacao.desenhar();
    // pGG->draw(colisionBox);
}

sf::Vector2f Jogador::getCenter()
{
    sf::FloatRect size = getSize();
    return sf::Vector2f(size.left + size.width / 2.0f, size.top + size.height / 2.0f);
}

sf::FloatRect Jogador::getSize()
{
    return colisionBox.getGlobalBounds();
}

void Jogador::lidarColisao(sf::Vector2f intersecao, Entidade *other)
{
    sf::FloatRect pisoBounds = other->getSize();
    sf::FloatRect jogadorBounds = getSize();

    // Imprimir a interseção para debug
    std::cout << "Colisão com " << other->getTipo() << ": x = " << intersecao.x << ", y = " << (intersecao.y) << std::endl;

    if (other->getTipo() == tipoDeEntidade::PLATAFORMA)
    {
        if (intersecao.y > 0)
        {
            y -= intersecao.y - 1;
            // y = pisoBounds.top - (jogadorBounds.height / 2); // Position the player on top of the platform
            tempoDesdeUltimoPiso = 0.0f;
            velocidadeY = 0;
        }
    }
    else if (other->getTipo() == tipoDeEntidade::ESPINHO)
    {
        bool isCloseEnough = abs(getCenter().x - other->getCenter().x) <= 16 * SCALING_FACTOR;
        if (isCloseEnough && tempoDesdeUltimoEspinho >= COOLDOWN_ESPINHO)
        {
            recebeDano(1);
            tempoDesdeUltimoEspinho = 0;
        }
    }

    setPosition(x, y);
}
