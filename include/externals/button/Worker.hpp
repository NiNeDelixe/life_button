#ifndef BUTTON_WORKER_HPP_
#define BUTTON_WORKER_HPP_

#include "core/core.hpp"

#include "externals/IWorker.hpp"

#ifdef USE_STL_CODE
#include <functional>
using callback_t = std::function<void()>;
#else
using callback_t = void (*)();
#endif



namespace button
{
    class Worker;
}

class button::Worker : public IWorker
{
public:
    Worker(callback_t on_press, callback_t on_release);
    Worker();
    ~Worker() = default;

public:
    void setOnPress(callback_t callback) { on_press = callback; }
    void setOnRelease(callback_t callback) { on_release = callback; }

    bool isPressed() const { return is_pressed; }

public:
    void update() override;

private:
    callback_t on_press;
    callback_t on_release;
    bool last_state;
    bool is_pressed = false;
};

extern button::Worker _button;

#endif  // BUTTON_WORKER_HPP_
