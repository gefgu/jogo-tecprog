#include "Listas/ListaEntidades.hpp"
#include "Entidades/Personagens/Personagem.hpp"
#include "Entidades/Personagens/Jogador.hpp"
#include "Entidades/Projetil.hpp"

ListaEntidades::ListaEntidades() {}

ListaEntidades::~ListaEntidades() {}

void ListaEntidades::incluir(Entidade *pE)
{
  LEs.incluir(pE);
}

void ListaEntidades::executar()
{
  Elemento<Entidade> *it;
  for (it = LEs.getPrimeiro(); it != NULL; it = it->getProximo())
  {
    if (it->getInfo()->getAtivo())
      it->getInfo()->executar();
  }
}

void ListaEntidades::desenhar()
{
  Elemento<Entidade> *it;
  for (it = LEs.getPrimeiro(); it != NULL; it = it->getProximo())
  {
    if (it->getInfo()->getAtivo())
      it->getInfo()->desenhar();
  }
}

Entidade *ListaEntidades::getRandom()
{
  Elemento<Entidade> *it;
  for (it = LEs.getPrimeiro(); it != NULL; it = it->getProximo())
  {
    if ((rand() % 100) == 0)
      return it->getInfo();

    if (it->getProximo() == NULL)
      it = LEs.getPrimeiro();
  }
  return LEs.getPrimeiro()->getInfo();
}

void ListaEntidades::remover(Entidade *pE)
{
  LEs.remover(pE);
}

Json::Value ListaEntidades::toJsonArray()
{
  Json::Value jsonArray(Json::arrayValue);
  Elemento<Entidade> *it;
  for (it = LEs.getPrimeiro(); it != NULL; it = it->getProximo())
  {
    jsonArray.append(it->getInfo()->gravar());
  }

  return jsonArray;
}