#ifndef SIGLETON_NOT_INITIALIZED_H
#define SIGLETON_NOT_INITIALIZED_H


class SingletonNotInitialized
    :   public std::exception
{
public:
    SingletonNotInitialized(const std::string& message);
    virtual ~SingletonNotInitialized();

    virtual const char* what() const noexcept;

private:
    std::string message_;

};


#endif