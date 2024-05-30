/**
 * @file    Cli.cppm
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    25.05.2024
 */

module;

#include <libpq-fe.h>

export module Morpheus.PostgreSql.Cli;

export namespace Morpheus::PostgreSql::Cli
{

using ::pg_conn;
using ::pg_result;
using ::ConnStatusType;
using ::ExecStatusType;
using ::PQconnectdb;
using ::PQstatus;
using ::PQfinish;
using ::PQerrorMessage;
using ::PQexec;
using ::PQresultStatus;
using ::PQresultErrorMessage;
using ::PQclear;
using ::PQntuples;

} // namespace Morpheus::PostgreSql::Cli
