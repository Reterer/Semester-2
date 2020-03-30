#pragma once

#define LOG_INFO(MSG) _log("[INFO]",MSG, "", __func__, "")
#define LOG_ERR(MSG) _log("[ERRO]",MSG, "", __func__, "")

#define TEST_SUCCESS() _log("[SUCCESS]","", "", __func__, "")
#define TEST_FAILED() _log("[FAILED]", "", "", __func__, "")
#define TEST(EXP) (EXP)?TEST_SUCCESS():TEST_FAILED()

#define TEST_START() _log("[TEST]\t ", "", "", __func__, "")

void _log(const char* level, const char* message, const char* file, const char* func, const char* line);