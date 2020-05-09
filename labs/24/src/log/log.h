#pragma once

#define LOG_INFO(MSG) _log("[INFO]\t   ",MSG, "", __func__, -1)
#define LOG_ERR(MSG) _log("[ERRO]\t   ",MSG, "", __func__, -1)

#define TEST_SUCCESS() _log("[SUCCESS]","", "", __func__, __LINE__)
#define TEST_FAILED() _log("[FAILED]", "", "", __func__, __LINE__)
#define TEST(EXP) (EXP)?TEST_SUCCESS():TEST_FAILED()

#define TEST_START() _log("[TEST]\t ", "", "", __func__, -1)

void _log(const char* level, const char* message, const char* file, const char* func, const int line);