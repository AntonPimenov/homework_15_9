#include <iostream>
#include "chat.h"

int main() {
    // Chat chat;
    // char login[LOGINLENGTH];
    // char password[100]; // Длина пароля может быть больше, чем длина логина

    // // Пример регистрации
    // std::cout << "Введите логин для регистрации: ";
    // std::cin >> login;
    // std::cout << "Введите пароль для регистрации: ";
    // std::cin >> password;
    // chat.reg(login, password, strlen(password));

    // // Пример логина
    // std::cout << "Введите логин для входа: ";
    // std::cin >> login;
    // std::cout << "Введите пароль для входа: ";
    // std::cin >> password;
    // chat.login(login, password, strlen(password));

    Chat chat;

    // Регистрация пользователей
    char login1[LOGINLENGTH] = "user1";
    char password1[] = "password123";
    chat.reg(login1, password1, strlen(password1));

    char login2[LOGINLENGTH] = "user2";
    char password2[] = "mypassword";
    chat.reg(login2, password2, strlen(password2));

    // Попытка зарегистрировать пользователя с существующим логином
    chat.reg(login1, password1, strlen(password1));

    // Вход в систему
    chat.login(login1, password1, strlen(password1)); // Успешный вход
    chat.login(login2, password2, strlen(password2)); // Успешный вход

    // Попытка входа с неверным паролем
    char wrongPassword[] = "wrongpassword";
    chat.login(login2, wrongPassword, strlen(wrongPassword)); // Неверный пароль

    // Попытка входа с несуществующим логином
    char nonExistentUser [LOGINLENGTH] = "user3";
    chat.login(nonExistentUser , password1, strlen(password1)); // Неверный логин


    return 0;
}
