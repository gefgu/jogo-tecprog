#include "Entidades/Personagens/Jogador.hpp"
#include "Fases/Fase.hpp" // Full definition
#include <unistd.h>       // Para usar sleep
#include <cmath>          // Para usar std::max
#include <cstring>

const float WALK_VELOCIDADE_MAXIMA = 4;
const float RUN_VELOCIDADE_MAXIMA = 8;

const float GRAVIDADE = 9.8f; // Aceleração da gravidade (em unidades por segundo^2)

const float COOLDOWN_PULO = 800.0f; // Tempo de espera entre pulos (em milissegundos)

const float COOLDOWN_ESPINHO = 1500.0f;
const float COOLDOWN_LIXO = 250.0f;
const float COOLDOWN_TIRO = 500.0f;
const float COOLDOWN_MINA = 1250.0f;
const float COOLDOWN_ACAO = 25.0f;

const float SCALING_FACTOR = 3.f;

const float SHOT_ANIMATION_TIME = 150.0f;
const float HURT_ANIMATION_TIME = 250.0f;
const float DEATH_ANIMATION_TIME = 1200.0f;

const char *p1_idle = "./assets/Gangsters_1/Idle.png";
const char *p1_run = "./assets/Gangsters_1/Run.png";
const char *p1_walk = "./assets/Gangsters_1/Walk.png";
const char *p1_jump = "./assets/Gangsters_1/Jump.png";
const char *p1_hurt = "./assets/Gangsters_1/Hurt.png";
const char *p1_dead = "./assets/Gangsters_1/Dead.png";
const char *p1_shot = "./assets/Gangsters_1/Shot.png";
const char *p2_idle = "./assets/Gangsters_1_p2/Idle.png";
const char *p2_run = "./assets/Gangsters_1_p2/Run.png";
const char *p2_walk = "./assets/Gangsters_1_p2/Walk.png";
const char *p2_jump = "./assets/Gangsters_1_p2/Jump.png";
const char *p2_hurt = "./assets/Gangsters_1_p2/Hurt.png";
const char *p2_dead = "./assets/Gangsters_1_p2/Dead.png";
const char *p2_shot = "./assets/Gangsters_1_p2/Shot.png";

Jogador::Jogador(int px, int py, int vidas, bool player1) : Personagem(px, py, 0, 0, vidas, tipoDeEntidade::JOGADOR),

                                                            tempoDesdeUltimoPulo(0.0f),
                                                            tempoDesdeUltimoEspinho(COOLDOWN_ESPINHO),
                                                            tempoDesdeUltimoLixo(COOLDOWN_LIXO),
                                                            tempoDesdeUltimoTiro(COOLDOWN_TIRO),
                                                            tempoDesdeUltimaMina(COOLDOWN_MINA),
                                                            tempoDesdeUltimaAcao(COOLDOWN_ACAO),
                                                            slowness(1),
                                                            _gerenciadorInput(Gerenciador_Input::getInstance()),
                                                            teclaEsquerda(player1 ? "A" : "Left"),
                                                            teclaDireita(player1 ? "D" : "Right"),
                                                            teclaPulo(player1 ? "W" : "Up"),
                                                            teclaCorrida(player1 ? "Shift" : "RShift"),
                                                            teclaTiro(player1 ? "F" : "RControl"), isP1(player1)

{
    _gerenciadorInput.AttachContinuous(this);
    animacao.addTrilha("idle", new TrilhaAnimacao(5, 15, 128, 128, 3.0, 3.0, isP1 ? p1_idle : p2_idle));
    animacao.addTrilha("running", new TrilhaAnimacao(9, 10, 128, 128, 3.0, 3.0, isP1 ? p1_run : p2_run));
    animacao.addTrilha("walking", new TrilhaAnimacao(9, 10, 128, 128, 3.0, 3.0, isP1 ? p1_walk : p2_walk));
    animacao.addTrilha("jump", new TrilhaAnimacao(9, 10, 128, 128, 3.0, 3.0, isP1 ? p1_jump : p2_jump));
    animacao.addTrilha("hurt", new TrilhaAnimacao(4, 5, 128, 128, 3.0, 3.0, isP1 ? p1_hurt : p2_hurt));
    animacao.addTrilha("dead", new TrilhaAnimacao(4, 20, 128, 128, 3.0, 3.0, isP1 ? p1_dead : p2_dead, false));
    animacao.addTrilha("shot", new TrilhaAnimacao(3, 5, 128, 128, 3.0, 3.0, isP1 ? p1_shot : p2_shot, false));
    animacao.setPosition(px, py);
    animacao.setScale(SCALING_FACTOR, SCALING_FACTOR);
    setColisionBoxSize(sf::Vector2f(30 * SCALING_FACTOR, 128 * SCALING_FACTOR));
    setAnimationState();
}

Jogador::~Jogador()
{
    _gerenciadorInput.DetachContinuous(this);
}

void Jogador::Update(const char *teclaPressionada)
{
    // cout << "Update: " << teclaPressionada << endl;
    tempoDesdeUltimaAcao = 0.0f;
    if (strcmp(teclaPressionada, teclaEsquerda) == 0)
        andar(-1);
    if (strcmp(teclaPressionada, teclaDireita) == 0)
        andar(1);
    if (strcmp(teclaPressionada, teclaPulo) == 0)
        pular();
    if (strcmp(teclaPressionada, teclaTiro) == 0)
        atacar();
    if (strcmp(teclaPressionada, teclaCorrida) == 0)
        correr();
}

void Jogador::atacar()
{
    if (tempoDesdeUltimoTiro >= COOLDOWN_TIRO)
    {
        pFase->addProjetil(x + direcao * 60, y + (getSize().height / 5), direcao, JOGADOR);
        tempoDesdeUltimoTiro = 0;
    }
}

void Jogador::pular()
{
    if (noChao && tempoDesdeUltimoPulo >= COOLDOWN_PULO)
    {
        velocidadeY = -sqrt(2 * GRAVIDADE) * 1.25;
        y -= 10;
        noChao = false;
        tempoDesdeUltimoPulo = 0.0f; // Reseta o tempo desde o último pulo
    }
}

void Jogador::correr()
{
    float elapsed_time = pGG->getElapsedTime();
    newState = RUN;
    velocidadeX += (elapsed_time / 100.0f) / slowness; // taking up speed
    velocidadeX = min(RUN_VELOCIDADE_MAXIMA / slowness, velocidadeX);
}

void Jogador::andar(int newDirection)
{
    float elapsed_time = pGG->getElapsedTime();
    if (newDirection != direcao && tempoDesdeUltimaMina >= COOLDOWN_MINA)
    {
        mudouDirecao = true;
        direcao = newDirection;
    }
    velocidadeX += (elapsed_time / 50.0f) / slowness; // taking up speed
    newState = (newState == RUN) ? RUN : WALK;
    if (state == RUN)
        velocidadeX = min(velocidadeX, RUN_VELOCIDADE_MAXIMA / slowness);
    else
        velocidadeX = min(velocidadeX, WALK_VELOCIDADE_MAXIMA / slowness);
    // velocidadeX = WALK_VELOCIDADE_MAXIMA;
}

void Update()
{
}

void Jogador::mover()
{
    if (state == DEAD)
    {
        return; // Bloqueia qualquer movimento se o jogador estiver morto.
    }

    // newState = IDLE;

    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    // {
    //     Gerenciador_Estado::getInstance().setEstadoJogo(PAUSE);
    // }

    x += direcao * velocidadeX;
    y += velocidadeY;
    limitMovementByCamera();
}

void Jogador::executar()
{
    if (morto)
        return;

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
    tempoDesdeUltimaMina += elapsed_time;
    tempoDesdeUltimaAcao += elapsed_time;

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
        velocidadeX = 0;
        velocidadeY = 0;
    }

    if (tempoDesdeUltimaAcao >= COOLDOWN_ACAO)
    {
        newState = IDLE;
    }

    if (!noChao)
    {
        newState = JUMP;
    }

    if (tempoDesdeUltimoTiro <= SHOT_ANIMATION_TIME)
    {
        newState = SHOT;
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

    if (newState == IDLE)
        velocidadeX = 0;

    if (state != DEAD && (mudouDirecao || newState != state))
    {
        mudouDirecao = false;
        state = newState;
        setAnimationState();
    }

    animacao.update();
    setPosition(x, y);
}

void Jogador::lidarColisao(sf::Vector2f intersecao, Entidade *other)
{
    sf::FloatRect otherBounds = other->getSize();
    sf::FloatRect jogadorBounds = getSize();

    // Imprimir a interseção para debug
    // std::cout << "Colisão com " << other->getTipo() << ": x = " << intersecao.x << ", y = " << (intersecao.y) << std::endl;

    if (other->getTipo() == tipoDeEntidade::PLATAFORMA)
    {
        if (intersecao.y > 0 && jogadorBounds.top + (jogadorBounds.height / 1.5) <= otherBounds.top)
        {
            y -= intersecao.y - 1;
            tempoDesdeUltimoPiso = 0.0f;
            if (tempoDesdeUltimoPulo > 50.0f)
            {
                velocidadeY = 0;
            }
        }
        else if (intersecao.x >= 0)
        {
            x -= intersecao.x - 1;
        }
        else if (intersecao.x < 0)
        {
            x += intersecao.x + 1;
        }
    }

    if (morto)
        return;

    if (other->getTipo() == tipoDeEntidade::FIGHTER && !static_cast<Fighter *>(other)->getMorto())
    {
        if (other->getCenter().x >= getCenter().x)
        {
            x -= intersecao.x - 1;
        }
        else
        {
            x += intersecao.x + 1;
        }
    }
    else if (other->getTipo() == tipoDeEntidade::ATIRADOR && !static_cast<Atirador *>(other)->getMorto())
    {
        if (other->getCenter().x >= getCenter().x)
        {
            x -= intersecao.x - 2;
        }
        else
        {
            x += intersecao.x + 2;
        }
    }
    else if (other->getTipo() == tipoDeEntidade::SOLDADO && !static_cast<Atirador *>(other)->getMorto())
    {
        if (other->getCenter().x >= getCenter().x)
        {
            x -= intersecao.x - 2;
        }
        else
        {
            x += intersecao.x + 2;
        }
    }

    else if (other->getTipo() == tipoDeEntidade::LIXO && tempoDesdeUltimoLixo >= COOLDOWN_LIXO)
    {
        slowness = 0.5;
        tempoDesdeUltimoLixo = 0;
    }
    else if (other->getTipo() == tipoDeEntidade::ESPINHO && tempoDesdeUltimoEspinho >= COOLDOWN_ESPINHO)
    {
        recebeDano(static_cast<Espinho *>(other)->getDano());
        tempoDesdeUltimoEspinho = 0;
    }

    setPosition(x, y);
}

void Jogador::reduzirVelocidade(float fator)
{
    tempoDesdeUltimoLixo = 0.0f;
    slowness = fator;
}

Jogador &Jogador::operator++()
{
    this->num_vidas = std::max(0, num_vidas + 1);
    return *this;
}

void Jogador::aplicarForcaRepulsao(float forcaX, float forcaY)
{
    tempoDesdeUltimaMina = 0.0f;
    velocidadeX = forcaX;
    velocidadeY = forcaY;
}

void Jogador::limitMovementByCamera()
{
    sf::Vector2f size = pGG->getViewSize();
    sf::Vector2f center = pGG->getViewCenter();

    if (x >= center.x + size.x / 2)
    {
        x = center.x + size.x / 2;
    }
    else if (x <= center.x - size.x / 2)
    {
        x = center.x - size.x / 2;
    }
}

bool Jogador::getP1()
{
    return isP1;
}

Json::Value Jogador::gravar()
{
    Json::Value entityJson;

    entityJson["type"] = getTipo();
    entityJson["x"] = getPosition().x;
    entityJson["y"] = getPosition().y;
    entityJson["vidas"] = getVidas();
    entityJson["is_p1"] = getP1();
    return entityJson;
}