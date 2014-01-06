#ifndef _SINGLETONKEEP_H
#define _SINGLETONKEEP_H
/*!
 * \filename SingletonKeep.h
 * \author Daniel Sundfeld
 */

/*!
 * \brief Class that grants the singletons are created before main
 * starts and destroy when the program ends.
 *
 * The Singleton class must implement two static methods: getInstance,
 * that creates the instance if does not exist and destroyInstance,
 * that destroy and frees the memory. This is guaranteed by creating
 * static variables from this class, maintained on a variables header
 * file. See file SingletonKeepVariables.h
 */
template <class T>
class SingletonKeep
{
    public:
        SingletonKeep();
        ~SingletonKeep();
};
#endif
