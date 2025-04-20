#include "Game.hpp"

#include <iostream>
#include <sstream>

DefaultLogger::DefaultLogger()
: log_file_{get_file_name()}
{
}

auto DefaultLogger::get_file_name() -> std::string
{
    auto time_now_from_epoch = std::chrono::system_clock::now().time_since_epoch();
    auto seconds_from_epoch = std::chrono::duration_cast<std::chrono::seconds>(time_now_from_epoch).count();
    std::string file_name = std::format("{}_{}{}", LOG_FILE_PREFIX, seconds_from_epoch, LOG_FILE_SUFFIX);
    return file_name;
}

auto DefaultLogger::log(LogLevel log_level, const std::string& str) -> void
{
    instance().log_impl(log_level, str);
}

auto DefaultLogger::log_impl(LogLevel log_level, const std::string& str) -> void
{
    std::ostringstream log_stream;

    switch (log_level)
    {
        case LogLevel::GAME:
            log_stream << "[GAME] ";
            break;
        case LogLevel::PLAYER:
            log_stream << "[PLAYER] ";
            break;
        case LogLevel::OVERRIDE:
            log_stream << "[OVERRIDE] ";
            break;
        default:
            log_stream << "[UNKNOWN] ";
    }

    log_stream << str << "\n";
    log_file_ << log_stream.str();
    log_file_.flush();
}

auto DefaultLogger::instance() -> DefaultLogger&
{
    static DefaultLogger logger;
    return logger;
}

Phase::Phase(PhaseName phase_name)
: phase_name_{phase_name}
{

}

auto PhaseZero::run(GameState* game) -> void
{
    get_player_count(game);
    get_player_names(game);
    assign_player_positions(game);
}

auto PhaseZero::get_player_count(GameState* game) -> void
{
    uint8_t count;
    std::cin >> count;

    game->player_count_ = count;
}

auto PhaseZero::get_player_names(GameState* game) -> void
{
    for(std::uint8_t i = 0; i < game->player_count_; i++)
    {
        std::string player_name;
        std::cin >> player_name;
    }
}

// auto PhaseZero::assign_player_positions(GameState* game) -> void;
