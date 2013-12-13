#include "SingletonKeep.h"
#include "SingletonKeepVariables.h"

using namespace std;

template <class T>
SingletonKeep<T>::SingletonKeep()
{
    T::getInstance();
}

template <class T>
SingletonKeep<T>::~SingletonKeep()
{
    T::destroyInstance();
}

