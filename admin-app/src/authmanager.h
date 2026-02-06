#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H

#include <QString>


class AuthManager
{
public:
    static AuthManager* instance();

    void setToken(const QString &token);
    QString getToken() const;

private:
    explicit AuthManager();
    QString token;
};

#endif // AUTHMANAGER_H
