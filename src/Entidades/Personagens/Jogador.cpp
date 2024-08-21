#include "Entidades/Personagens/Jogador.hpp"
#include "Fases/Fase.hpp" // Full definition
#include <cmath>          // Para usar std::max

const float VELOCIDADEINICIAL = 25;
const float GRAVIDADE = 9.8f; // Aceleração da gravidade (em unidades por segundo^2)

const float COOLDOWN_PULO = 800.0f;    // Tempo de espera entre pulos (em milissegundos)
const float VELOCIDADE_CORRIDA = 1.5f; // Velocidade de corrida (em unidades por segundo)
const float COOLDOWN_ESPINHO = 500.0f;
const float COOLDOWN_LIXO = 250.0f;
const float COOLDOWN_TIRO = 500.0f;

const float SCALING_FACTOR = 3.f;

const float HURT_ANIMATION_TIME = 250.0f;
const float DEATH_ANIMATION_TIME = 1200.0f;

Jogador::Jogador(int px, int py, int vidas) : Personagem(px, py, VELOCIDADEINICIAL, 0, vidas, tipoDeEntidade::JOGADOR),

                                              tempoDesdeUltimoPulo(0.0f),
                                              tempoDesdeUltimoEspinho(COOLDOWN_ESPINHO),
                                              tempoDesdeUltimoLixo(COOLDOWN_LIXO),
                                              tempoDesdeUltimoTiro(COOLDOWN_TIRO),
                                              slowness(1)

{
    animacao.addTrilha("idle", new TrilhaAnimacao(5, 15, 128, 128, 3.0, 3.0, "./assets/Gangsters_1/Idle.png"));
    animacao.addTrilha("running", new TrilhaAnimacao(9, 10, 128, 128, 3.0, 3.0, "./assets/Gangsters_1/Run.png"));
    animacao.addTrilha("walking", new TrilhaAnimacao(9, 10, 128, 128, 3.0, 3.0, "./assets/Gangsters_1/Walk.png"));
    animacao.addTrilha("jump", new TrilhaAnimacao(9, 10, 128, 128, 3.0, 3.0, "./assets/Gangsters_1/Jump.png"));
    animacao.addTrilha("hurt", new TrilhaAnimacao(4, 5, 128, 128, 3.0, 3.0, "./assets/Gangsters_1/Hurt.png"));
    animacao.addTrilha("dead", new TrilhaAnimacao(4, 20, 128, 128, 3.0, 3.0, "./assets/Gangsters_1/Dead.png", false));
    animacao.setPosition(px, py);
    animacao.setScale(SCALING_FACTOR, SCALING_FACTOR);
    setColisionBoxSize(sf::Vector2f(30 * SCALING_FACTOR, 128 * SCALING_FACTOR));
    setAnimationState();
}

void Jogador::atacar()
{
    if (tempoDesdeUltimoTiro >= COOLDOWN_TIRO)
    {
        pFase->addProjetil(x + 40, y + getSize().height / 6, direcao);
        tempoDesdeUltimoTiro = 0;
    }
}

void Jogador::mover()
{
    newState = IDLE;
    mudouDirecao = false;
    float elapsed_time = pGG->getElapsedTime();
    float velocidadeCorrida = VELOCIDADEINICIAL * VELOCIDADE_CORRIDA;
    // Verifica se o Shift está pressionado para correr
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    {
        velocidadeX = velocidadeCorrida / slowness; // Velocidade de corrida
        newState = RUN;

        // Executa a corrida na direção atual

        x += direcao * velocidadeX * (elapsed_time / 100.0);
    }
    else
    {
        // Retorna à velocidade normal de caminhada
        velocidadeX = (velocidadeCorrida / slowness) / VELOCIDADE_CORRIDA;
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
        velocidadeX = velocidadeCorrida / slowness; // Velocidade de corrida
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

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
    {
        atacar();
    }
}

void Jogador::executar()
{
    // Reset noChao at the start of each frame
    noChao = tempoDesdeUltimoPiso <= COOLDOWN_PISO;
    if (tempoDesdeUltimoLixo >= COOLDOWN_LIXO)
        slowness = 1;

    aplicarGravidade();
    float elapsed_time = pGG->getElapsedTime();

    // Atualiza o tempo desde o último pulo
    tempoDesdeUltimoPulo += elapsed_time;
    tempoDesdeUltimoEspinho += elapsed_time;
    tempoDesdeUltimoPiso += elapsed_time;
    tempoDesdeUltimoLixo += elapsed_time;
    tempoDesdeUltimoTiro += elapsed_time;
    tempoDesdeUltimoDano += elapsed_time;
    if (getVidas() <= 0)
    {
        tempoDesdeMorte += elapsed_time;
    }

    mover();

    if (y > 2000)
    {
        recebeDano(1);
        y = 0;
        x = 0;
        velocidadeY = 0;
    }

    if (!noChao)
    {
        newState = JUMP;
    }

    if (tempoDesdeUltimoDano < HURT_ANIMATION_TIME)
    {
        newState = HURT;
    }

    if (tempoDesdeMorte > 0.0f && tempoDesdeMorte <= DEATH_ANIMATION_TIME)
    {
        newState = DEAD;
    }
    else if (tempoDesdeMorte > DEATH_ANIMATION_TIME)
    {
        morto = true;
    }

    if (mudouDirecao || newState != state)
    {
        state = newState;
        setAnimationState();
    }

    animacao.update();
    setPosition(x, y);
}

void Jogador::lidarColisao(sf::Vector2f intersecao, Entidade *other)
{
    sf::FloatRect pisoBounds = other->getSize();
    sf::FloatRect jogadorBounds = getSize();

    // Imprimir a interseção para debug
    // std::cout << "Colisão com " << other->getTipo() << ": x = " << intersecao.x << ", y = " << (intersecao.y) << std::endl;

    if (other->getTipo() == tipoDeEntidade::PLATAFORMA)
    {
        if (intersecao.y > 0)
        {
            y -= intersecao.y - 1;
            tempoDesdeUltimoPiso = 0.0f;
            velocidadeY = 0;
        }
    }
    if (other->getTipo() == tipoDeEntidade::FIGHTER && !static_cast<Fighter *>(other)->getMorto())
    {
        if (intersecao.x > 0)
        {
            x -= intersecao.x - 1;
            tempoDesdeUltimoPiso = 0.0f;
            velocidadeY = 0;
        }
    }
    else if (other->getTipo() == tipoDeEntidade::ESPINHO && tempoDesdeUltimoEspinho >= COOLDOWN_ESPINHO)
    {
        recebeDano(1);
        tempoDesdeUltimoEspinho = 0;
    }

    setPosition(x, y);
}

void Jogador::reduzirVelocidade(float fator)
{
    tempoDesdeUltimoLixo = 0.0f;
    slowness = fator;
}
