#include "authmanager.h"
#include <qdebug.h>

AuthManager *AuthManager::instance()
{
    static AuthManager instance;
    return &instance;
}

AuthManager::AuthManager()
{

}

void AuthManager::setToken(const QString &token)
{
    this->token = token;
}

QString AuthManager::getToken() const
{
    return token;
}

