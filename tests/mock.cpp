/**
 * @file main.cpp
 * @brief
 * @author 张祝玙
 * @date 2025-04-17
 */

#include <string>

#include "core/UpdateManager.h"

const std::string REPO_URL = "http://127.0.0.1:8090/repo/";

using namespace udc;

int main() {

    UpdateManager::MockContext context;
    auto mock = context.createManager();

    auto result = mock->installAll(
        mock->checkAndDownload("1.0.1-beta1", REPO_URL), "./mock");

    return 0;
}
