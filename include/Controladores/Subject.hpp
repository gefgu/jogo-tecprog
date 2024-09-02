#pragma once

#include <list>
#include "Controladores/Observer.hpp"

using namespace std;

namespace Controladores
{
  class Subject
  {
  public:
    virtual ~Subject();
    virtual void Attach(Observer *o);
    virtual void Detach(Observer *o);
    virtual void AttachContinuous(Observer *o);
    virtual void DetachContinuous(Observer *o);
    virtual void Notify(const char *teclaPressionada) = 0;
    virtual void NotifyContinuous(const char *teclaPressionada) = 0;

  protected:
    Subject();
    list<Observer *> _observers;
    list<Observer *> _observersContinuous;
  };
};