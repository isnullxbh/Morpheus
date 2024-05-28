/**
 * @file    Cli.cppm
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    28.05.2024
 */

module;

#include <mysql.h>

export module Morpheus.MySql.Cli;

export namespace Morpheus::MySql::Cli
{

using Handle = ::MYSQL*;
using ResultHandle = ::MYSQL_RES*;

using ::mysql_init;
using ::mysql_real_connect;
using ::mysql_error;
using ::mysql_close;
using ::mysql_query;
using ::mysql_store_result;
using ::mysql_free_result;
using ::mysql_num_rows;

} // namespace Morpheus::MySql::Cli
