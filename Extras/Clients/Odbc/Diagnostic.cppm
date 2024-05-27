/**
 * @file    Diagnostic.cppm
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    27.05.2024
 */

export module Morpheus.Odbc.Diagnostic;

export import Std.Array;
import Std.Def;
export import Std.Strings;
export import Morpheus.Sql.Error;
import Morpheus.Odbc.Cli;

namespace Morpheus::Odbc
{

export class Diagnostic
{
public:
    using State = std::array<char, 6>;

    auto message() const noexcept -> const std::string& { return _message; }
    auto state() const noexcept -> const State& { return _state; }
    auto vendorCode() const noexcept -> int { return _vendor_code; }

    static auto retrieve(Cli::HandleType type, Cli::Handle handle, int record_index = 1) -> Diagnostic
    {
        Diagnostic entry {};
        entry._message.resize(max_message_len);

        signed short bytes_written {};
        const auto ec =
            Cli::SQLGetDiagRec(type, handle, record_index, (Cli::Char*)entry._state.data(), &entry._vendor_code,
                (Cli::Char*)entry._message.data(), max_message_len - 1, &bytes_written);

        if (ec != Cli::Ok && ec != Cli::OkWithInfo)
        {
            return {};
        }

        entry._message.resize(static_cast<std::size_t>(bytes_written));
        return entry;
    }

    auto toError() const & -> Sql::Error
    {
        return Sql::Error { _message };
    }

    auto toError() && -> Sql::Error
    {
        return Sql::Error { std::move(_message) };
    }

private:
    Diagnostic() = default;

    State       _state       {};
    std::string _message     {};
    int         _vendor_code {};

    static constexpr std::size_t max_message_len { 1024 };
};

} // namespace Morpheus::Odbc
