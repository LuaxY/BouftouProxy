#ifndef SIGNLETON_H
#define SIGNLETON_H

#include <memory>
#include <cassert>

/*template<class T>
class Singleton {
private:
    static T * _instance;

protected:
    Singleton (){}

public:
    static T & instance() {
        if (_instance) {
          return *_instance;
        }

        _instance = new T();
        return *_instance;
    }
};

template<class T> T* Singleton<T>::_instance = 0;*/

template<class T>
class Singleton
{
protected:
    Singleton() = default;
    ~Singleton() = default;

public:
    template<class ... Args>
    static T& create(Args &&... args)
    {
        assert(!_singleton);
        _singleton.reset(new T{std::forward<Args>(args)...});
        return *_singleton;
    }

    static void kill()
    {
        _singleton.reset(nullptr);
    }

    static T& instance()
    {
        assert(_singleton);
        return *_singleton;
    }

private:
    static std::unique_ptr<T> _singleton;
};

template<class T>
std::unique_ptr<T> Singleton<T>::_singleton;

#endif // SIGNLETON_H
