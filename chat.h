#pragma once

#include "sha1.h"
#include "string.h"

#define SIZE 10
#define LOGINLENGTH 10

class Chat {
    public:
        Chat();
        void reg(char _login[LOGINLENGTH], char _pass[], int pass_length);
        bool login(char _login[LOGINLENGTH], char _pass[], int pass_length);
        
        
    private:
        struct AuthData {
            AuthData() : pass_sha1_hash(nullptr) {
                strcpy(login, "");
            }
    
            ~AuthData() {
                delete[] pass_sha1_hash;
            }
            AuthData(char _login[LOGINLENGTH], uint* sh1) {
                strcpy(login, _login);
                pass_sha1_hash = sh1;
            }
            AuthData& operator = (const AuthData& other) {
                strcpy(login, other.login);
                
                if(pass_sha1_hash != 0)
                    delete [] pass_sha1_hash;
                pass_sha1_hash = new uint[SHA1HASHLENGTHUINTS];
                
                memcpy(pass_sha1_hash, other.pass_sha1_hash, SHA1HASHLENGTHBYTES);
                
                return *this;
            }           
            char login[LOGINLENGTH];
            uint* pass_sha1_hash;
        };
    AuthData data[SIZE];
    int data_count;
    int hashFunction(const char* key);
    int quadraticProbing(int hashIndex, int attempt);
};