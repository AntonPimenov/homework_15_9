#include "chat.h"
#include "iostream"
#include "string.h"

Chat::Chat() 
{
    data_count = 0;
}

int Chat::hashFunction(const char* key) 
{
    unsigned long hash = 0;
    for (int i = 0; key[i] != '\0'; i++) 
    {
        hash = (hash * 31 + key[i]) % SIZE; // Метод умножения
    }
    return hash;
}

int Chat::quadraticProbing(int hashIndex, int attempt) 
{
    return (hashIndex + attempt * attempt) % SIZE; // Квадратичное пробирование
}

void Chat::reg(char _login[LOGINLENGTH], char _pass[], int pass_length) 
{
    if (data_count >= SIZE) 
    {
        std::cout << "Достигнуто максимальное количество пользователей!" << std::endl;
        return;
    }

    // Проверка на существование логина
    int hashIndex = hashFunction(_login);
    int attempt = 0;
    while (attempt < SIZE) 
    {
        int index = quadraticProbing(hashIndex, attempt);
        if (data[index].pass_sha1_hash == nullptr) 
        {
            // Позиция свободна, сохраняем данные
            uint* hashedPassword = sha1(_pass, pass_length);
            data[index] = AuthData(_login, hashedPassword);
            data_count++;
            std::cout << "Регистрация успешна!" << std::endl;
            return;
        } 
        else if (strcmp(data[index].login, _login) == 0) 
        {
            std::cout << "Логин уже занят!" << std::endl;
            return; // Логин занят, выходим из функции
        }
        attempt++;
    }

    std::cout << "Не удалось зарегистрировать пользователя!" << std::endl;
}

bool Chat::login(char _login[LOGINLENGTH], char _pass[], int pass_length) 
{
    uint* hashedPassword = sha1(_pass, pass_length);
    int hashIndex = hashFunction(_login);
    int attempt = 0;

    while (attempt < SIZE) {
        int index = quadraticProbing(hashIndex, attempt);
        if (data[index].pass_sha1_hash == nullptr) 
        {
            // Позиция пуста, пользователь не найден
            break;
        } 
        else if (strcmp(data[index].login, _login) == 0) 
        {
            // Сравнение хешей паролей
            if (memcmp(data[index].pass_sha1_hash, hashedPassword, SHA1HASHLENGTHBYTES) == 0) 
            {
                std::cout << "Вход успешен!" << std::endl;
                delete[] hashedPassword; // Освобождаем память
                return true; // Успешный вход
            }
            break; // Неверный пароль
        }
        attempt++;
    }

    std::cout << "Неверный логин или пароль!" << std::endl;
    delete[] hashedPassword; // Освобождаем память
    return false; // Неудачный вход
}

// void Chat::reg(char _login[LOGINLENGTH], char _pass[], int pass_length) {
//     // Проверка на существование логина
//     for (int i = 0; i < data_count; ++i) {
//         if (strcmp(data[i].login, _login) == 0) {
//             std::cout << "Логин уже занят!" << std::endl;
//             return; // Логин занят, выходим из функции
//         }
//     }

//     // Проверяем, достаточно ли места для нового пользователя
//     if (data_count >= SIZE) {
//         std::cout << "Достигнуто максимальное количество пользователей!" << std::endl;
//         return;
//     }

//     // Вычисление SHA-1 хеша пароля
//     uint* hashedPassword = sha1(_pass, pass_length);

//     // Сохранение логина и хеша в массиве
//     data[data_count++] = AuthData(_login, hashedPassword);
//     std::cout << "Регистрация успешна!" << std::endl;
// }

// bool Chat::login(char _login[LOGINLENGTH], char _pass[], int pass_length) {
//     // Вычисление SHA-1 хеша пароля
//     uint* hashedPassword = sha1(_pass, pass_length);

//     // Поиск пользователя по логину
//     for (int i = 0; i < data_count; ++i) {
//         if (strcmp(data[i].login, _login) == 0) {
//             // Сравнение хешей паролей
//             if (memcmp(data[i].pass_sha1_hash, hashedPassword, SHA1HASHLENGTHBYTES) == 0) {
//                 std::cout << "Вход успешен!" << std::endl;
//                 delete[] hashedPassword; // Освобождаем память
//                 return true; // Успешный вход
//             }
//         }
//     }

//     std::cout << "Неверный логин или пароль!" << std::endl;
//     delete[] hashedPassword; // Освобождаем память
//     return false; // Неудачный вход
// }
/*
Пояснение кода

    Метод reg:
        Проверяет, существует ли логин уже в массиве data.
        Если логин не занят и есть место для нового пользователя, вычисляет хеш пароля с помощью функции sha1.
        Сохраняет логин и хеш пароля в массиве data и увеличивает счетчик data_count.

    Метод login:
        Вычисляет хеш пароля, который пользователь пытается ввести.
        Проходит по массиву data, ищет логин и сравнивает хеши паролей.
        Если логин и хеш совпадают, вход считается успешным, и метод возвращает true. В противном случае возвращает false.

Указания по использованию

    Убедитесь, что у вас есть реализация функции sha1, которая возвращает указатель на массив, содержащий хеш пароля.
    Не забудьте освободить память, выделенную для хеша пароля, после его использования, чтобы избежать утечек памяти.
    Для тестирования вы можете создать функцию main, где будете использовать методы reg и login для регистрации и входа пользователей в систему.


*/