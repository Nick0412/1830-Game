#ifndef GAME_HPP
#define GAME_HPP

#include <chrono>
#include <cstdint>
#include <format>
#include <fstream>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

constexpr std::string_view LOG_FILE_PREFIX = "1830_Game";
constexpr std::string_view LOG_FILE_SUFFIX = ".log";

constexpr std::string_view PRIVATE_COMPANY_NAME_SCHUYLKILL_VALLEY = "Schuylkill Valley";
constexpr std::string_view PRIVATE_COMPANY_NAME_CHAMPLAIN_ST_LAWRENCE= "Champlain & St. Lawrence";
constexpr std::string_view PRIVATE_COMPANY_NAME_DELAWARE_AND_HUDSON = "Delaware & Hudson";
constexpr std::string_view PRIVATE_COMPANY_NAME_MOHAWK_AND_HUDSON = "Mohawk & Hudson";
constexpr std::string_view PRIVATE_COMPANY_NAME_CAMDEN_AND_AMBOY = "Camden & Amboy";
constexpr std::string_view PRIVATE_COMPANY_NAME_BALTIMORE_AND_OHIO = "Baltimore & Ohio";

enum LogLevel
{
    PLAYER,
    GAME,
    OVERRIDE
};

struct DefaultLogger
{
    DefaultLogger();

    static auto log(LogLevel log_level, const std::string& str) -> void;
    static auto instance() -> DefaultLogger&;
    static auto get_file_name() -> std::string;

    auto log_impl(LogLevel log_level, const std::string& str) -> void;

    std::ofstream log_file_;
};

struct PrivateCompany
{
    PrivateCompany(std::string company_name, std::uint32_t face_value_price, std::uint32_t revenue);

    const std::string company_name_;
    const std::uint32_t face_value_price_;
    const std::uint32_t revenue_;
};

struct Player
{
    Player() = delete;
    Player(const std::string& name, std::uint16_t money_amount,  bool has_priority_deal_card);

    std::string name_;
    std::uint32_t money_amount_;
    bool has_priority_deal_card_;
};

struct Bank
{
    std::uint32_t money_amount_;
};

struct GameState
{
    GameState();
    ~GameState() = default;

    std::vector<std::unique_ptr<Player>> player_list_;
    std::uint32_t player_count_;
    std::unordered_map<std::uint8_t, Player*> player_position_;
    std::vector<std::unique_ptr<PrivateCompany>> private_companies_;
    std::vector<PrivateCompany*> unowned_private_companies_;
    Bank bank_;
};

struct Phase
{
    enum PhaseName
    {
        PHASE_BEGIN,
        PHASE_ONE,
        PHASE_TWO,
        PHASE_THREE,
        PHASE_FOUR,
        PHASE_FIVE,
        PHASE_SIX,
        PHASE_SEVEN,
        PHASE_END
    };

    Phase(PhaseName phase_name); 
    virtual ~Phase() {}
    virtual auto run(GameState* game_state) -> void = 0;

    PhaseName phase_name_;
};

/**
 * PhaseZero begins the setup of the game. This includes calculating the number of players, their names and their position.
 * 
 */
struct PhaseZero : public Phase
{
    PhaseZero() = default;
    auto run(GameState* game) -> void override;
    auto get_player_count(GameState* game) -> void;
    auto get_player_names(GameState* game) -> void;
    auto assign_player_positions(GameState* game) -> void;
};

struct Game
{
    Game() = default;
    auto start() -> void;

    GameState game_state_;
    std::unique_ptr<Phase> phase_;
};

#endif
