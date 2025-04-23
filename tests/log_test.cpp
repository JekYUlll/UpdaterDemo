//
// Created by horeb on 25-4-18.
//
#include"log/Logger.h"

int main(int argc, char* argv[]) {
    LOG_I("Hello World!{}, {}", __FILE__, __LINE__);
    LOG_D("Hello World!{}, {}", __FILE__, __LINE__);
    LOG_E("Hello World!{}, {}", __FILE__, __LINE__);
    LOG_F("Hello World!{}, {}", __FILE__, __LINE__);
    LOG_T("Hello World!{}, {}", __FILE__, __LINE__);
    LOG_W("Hello World!{}, {}", __FILE__, __LINE__);
}
