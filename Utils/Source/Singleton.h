
template<typename T>
class Singleton
{
    static T& Get();

private:
    Singleton();
    virtual ~Singleton();
};

template<typename T>
T& Singleton<T>::Get()
{
    static T instance;

    return T;
}