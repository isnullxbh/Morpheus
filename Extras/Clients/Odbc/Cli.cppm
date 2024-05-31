/**
 * @file    Cli.cppm
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    27.05.2024
 */

module;

#include <sqlext.h>

export module Morpheus.Odbc.Cli;

export namespace Morpheus::Odbc::Cli
{

using Char = SQLCHAR;
using Handle = SQLHANDLE;
using Pointer = SQLPOINTER;
using USmallInt = ::SQLUSMALLINT;

enum class DataType : decltype(SQL_C_CHAR)
{
    Char = SQL_C_CHAR,
};

using ::SQLAllocHandle;
using ::SQLFreeHandle;
using ::SQLSetEnvAttr;
using ::SQLGetDiagRec;
using ::SQLExecDirect;
using ::SQLConnect;
using ::SQLDisconnect;
using ::SQLDriverConnect;
using ::SQLFetch;
using ::SQLGetData;

enum EnvironmentAttribute : decltype(SQL_ATTR_ODBC_VERSION)
{
    OdbcVersion = SQL_ATTR_ODBC_VERSION,
};

enum Version : decltype(SQL_OV_ODBC2)
{
    v2 = SQL_OV_ODBC2,
    v3 = SQL_OV_ODBC3,
};

enum StatusCode : decltype(SQL_SUCCESS)
{
    Ok = SQL_SUCCESS,
    OkWithInfo = SQL_SUCCESS_WITH_INFO,
    InvalidHandle = SQL_INVALID_HANDLE,
    Error = SQL_ERROR,
    NoData = SQL_NO_DATA
};

enum HandleType : decltype(SQL_HANDLE_ENV)
{
    Environment = SQL_HANDLE_ENV,
    Connection = SQL_HANDLE_DBC,
    Statement = SQL_HANDLE_STMT,
    Invalid = SQL_INVALID_HANDLE
};

enum DriverCompletion : decltype(SQL_DRIVER_COMPLETE)
{
    Complete = SQL_DRIVER_COMPLETE,
    CompleteRequired = SQL_DRIVER_COMPLETE_REQUIRED,
    NoPrompt = SQL_DRIVER_NOPROMPT,
    Prompt = SQL_DRIVER_PROMPT,
};

inline const auto null_handle = reinterpret_cast<Handle>(SQL_NULL_HANDLE);
inline const SQLSMALLINT nts = SQL_NTS;

} // namespace Morpheus::Odbc::Cli
