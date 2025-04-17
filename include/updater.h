//
// Created by horeb on 25-4-16.
//

#ifndef UPDATER_H
#define UPDATER_H

#include <string>

#include "model.h"

class Updater{
public:
    Updater() = default;
    virtual ~Updater();

    virtual CheckUpdateResult CheckUpdate() = 0;
    virtual std::string GetRemoteVersion() = 0;
    virtual std::string GetLocalVersion() = 0;

    virtual bool Update() = 0;
};

// int max_retries = 3;
// int retry_delay = 1; // 初始延迟1秒
//
// for (int i = 0; i < max_retries; ++i) {
//     try {
//         // 执行网络请求或文件操作
//         perform_operation();
//         break; // 成功则退出循环
//     } catch (const NetworkError& e) {
//         if (is_retryable(e)) {
//             log("重试次数: " + to_string(i+1));
//             this_thread::sleep_for(seconds(retry_delay));
//             retry_delay *= 2; // 指数退避
//         } else {
//             throw; // 不可重试错误，直接抛出
//         }
//     } catch (const FileLockedError& e) {
//         // 处理文件占用，可能等待后重试
//         log("文件被占用，重试中...");
//         this_thread::sleep_for(seconds(retry_delay));
//         retry_delay *= 2;
//     }
// }

#endif //UPDATER_H
