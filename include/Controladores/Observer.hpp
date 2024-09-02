#pragma once
// using namespace Controladores;

// class Subject;

namespace Controladores
{
  class Observer
  {
  public:
    Observer();
    virtual ~Observer();
    virtual void Update(const char *teclaPressionada) = 0;
  };
};