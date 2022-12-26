#pragma once

#include "src/goopylib/debug/Log.h"

#define GP_TYPE_CHECKING true
#define GP_VALUE_CHECKING true
#define GP_ERROR_CHECKING true

/*
 0 - No Logging
 1 - Fatals Enabled
 2 - Errors Enabled
 3 - Warnings Enabled
 4 - Info Enabled
 5 - Debug Enabled
 6 - Trace Enabled
 7 - All Enabled
 */
#define GP_PY_LOGGING_LEVEL 3

// Python Extension Logging

#if (GP_PY_LOGGING_LEVEL >= 3)
#define GP_PY_WARN(...)     gp::Log::getPythonLogger()->warn(__VA_ARGS__)
#else
#define GP_PY_WARN(...) nullptr
#endif

#if (GP_PY_LOGGING_LEVEL >= 4)
#define GP_PY_INFO(...)     gp::Log::getPythonLogger()->info(__VA_ARGS__)
#else
#define GP_PY_INFO(...) nullptr
#endif

#if (GP_PY_LOGGING_LEVEL >= 5)
#define GP_PY_DEBUG(...)    gp::Log::getPythonLogger()->debug(__VA_ARGS__)
#else
#define GP_PY_DEBUG(...) nullptr
#endif

#if (GP_PY_LOGGING_LEVEL >= 6)
#define GP_PY_TRACE(...)    gp::Log::getPythonLogger()->trace(__VA_ARGS__)
#else
#define GP_PY_TRACE(...) nullptr
#endif

// Value Checking

#if GP_VALUE_CHECKING
#define GP_CHECK_EQUALS(variable, val, rtype, error) if ((variable) != (val)) { RAISE_VALUE_ERROR(rtype, error); }
#define GP_CHECK_NOT_EQUALS(variable, val, rtype, error) if ((variable) == (val)) { RAISE_VALUE_ERROR(rtype, error); }

#define GP_CHECK_GT(variable, val, rtype, error) if ((variable) <= (val)) { RAISE_VALUE_ERROR(rtype, error); }
#define GP_CHECK_GE(variable, val, rtype, error) if ((variable) < (val)) { RAISE_VALUE_ERROR(rtype, error); }

#define GP_CHECK_LT(variable, val, rtype, error) if ((variable) >= (val)) { RAISE_VALUE_ERROR(rtype, error); }
#define GP_CHECK_LE(variable, val, rtype, error) if ((variable) > (val)) { RAISE_VALUE_ERROR(rtype, error); }

#define GP_CHECK_INCLUSIVE_RANGE(variable, min, max, rtype, error) if ((variable) < (min) or (variable) > (max)) { RAISE_VALUE_ERROR(rtype, error); }
#define GP_CHECK_EXCLUSIVE_RANGE(variable, min, max, rtype, error) if ((variable) <= (min) or (variable) >= (max)) { RAISE_VALUE_ERROR(rtype, error); }
#else
#define GP_CHECK_EQUALS(variable, val, rtype, error)
#define GP_CHECK_NOT_EQUALS(variable, val, rtype, error)

#define GP_CHECK_GT(variable, val, rtype, error)
#define GP_CHECK_GE(variable, val, rtype, error)

#define GP_CHECK_LT(variable, val, rtype, error)
#define GP_CHECK_LE(variable, val, rtype, error)

#define GP_CHECK_INCLUSIVE_RANGE_INCLUSIVE(variable, min, max, rtype, error)
#define GP_CHECK_EXCLUSIVE_RANGE(variable, min, max, rtype, error)
#endif
