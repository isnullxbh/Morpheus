/**
 * @file    Cli.cppm
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    26.05.2024
 */

module;

#include <sqlite3.h>

export module Morpheus.SQLite.Cli;

export namespace Morpheus::SQLite::Cli
{

using ::sqlite3;
using ::sqlite3_stmt;

using StatementHandle = ::sqlite3_stmt*;

enum StatusCode : decltype(SQLITE_OK)
{
    Ok = SQLITE_OK,
    Row = SQLITE_ROW,
    Done = SQLITE_DONE
};

enum Flags : decltype(SQLITE_OPEN_READONLY)
{
    ReadOnly = SQLITE_OPEN_READONLY,
    ReadWrite = SQLITE_OPEN_READWRITE,
    Create = SQLITE_OPEN_CREATE,
    DeleteOnClose = SQLITE_OPEN_DELETEONCLOSE,
    Exclusive = SQLITE_OPEN_EXCLUSIVE,
    AutoProxy = SQLITE_OPEN_AUTOPROXY,
    Uri = SQLITE_OPEN_URI,
    Memory = SQLITE_OPEN_MEMORY
};

using ::sqlite3_open_v2;
using ::sqlite3_errmsg;
using ::sqlite3_close;
using ::sqlite3_finalize;
using ::sqlite3_step;
using ::sqlite3_reset;
using ::sqlite3_prepare;
using ::sqlite3_column_text;

} // namespace Morpheus::SQLite::Cli
