#pragma once
#ifndef SYNC_START_SYNCSTART_HPP_
#define SYNC_START_SYNCSTART_HPP_

#include "core/core.hpp"

#include "game_modes/GameMode.hpp"

#include "game_modes/HasTimer.hpp"

#include "game_modes/sync_start/Options.hpp"

#include "game_modes/ISyncable.hpp"

class SyncStart : public GameMode, public HasTimer, public ISyncable
{
public:
    SyncStart() = default;
    ~SyncStart() = default;

public:
    void start() override;
    void update() override;

    static void onPress();
    static void onRelease();

    void confirmReady();
    void setReady();
    void updateButtonTimer();

    void startButtonTimer();

    ISyncable::Data onSend() override;
    void onRecive(const ISyncable::Data& data) override;

public:
    GameModeOptions* getOptions() { return &options; };

public:
    SyncStartOptions options;
    std::vector<uint8_t> m_sendBuffer;

private:
    bool is_this_side_ready;
    bool is_other_side_ready;
};

#endif  // SYNC_START_SYNCSTART_HPP_
