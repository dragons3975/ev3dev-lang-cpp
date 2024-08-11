#include <chrono>
#include <thread>
#include <stdexcept>

#include <ev3dev.h>

namespace ev3 = ev3dev;

void precondition(bool cond, const std::string &msg) {
    if (!cond) throw std::runtime_error(msg);
}

template <class Motor, class Leds>
std::function<void(bool)> roll(Motor &motor, Leds &leds, int dir) {
    return [&motor, &leds, dir](bool state) {
        if (state) {
            motor.set_speed_sp(900 * dir).run_forever();
            ev3::led::set_color(leds, dir > 0 ? ev3::led::green : ev3::led::red);
        } else {
            motor.set_stop_action("brake").stop();
            for(auto led : leds) led->off();
        }
    };
}

int main() {
    
    ev3::sound::speak("Hello");

    /*ev3::large_motor lmotor(ev3::OUTPUT_B);
    ev3::large_motor rmotor(ev3::OUTPUT_C);
    ev3::remote_control rc;
    ev3::touch_sensor   ts;

    precondition(lmotor.connected(), "Motor on outB is not connected");
    precondition(rmotor.connected(), "Motor on outC is not connected");
    precondition(rc.connected(),     "Infrared sensor is not connected");
    precondition(ts.connected(),     "Touch sensor is not connected");

    rc.on_red_up    = roll(lmotor, ev3::led::left,   1);
    rc.on_red_down  = roll(lmotor, ev3::led::left,  -1);
    rc.on_blue_up   = roll(rmotor, ev3::led::right,  1);
    rc.on_blue_down = roll(rmotor, ev3::led::right, -1);

    // Enter event processing loop
    while (!ev3::button::enter.pressed()) {
        rc.process();

        // Backup when an obstacle is bumped
        if (ts.is_pressed()) {
            ev3::sound::speak("Oops, excuse me!");

            lmotor.set_stop_action("brake").stop();
            rmotor.set_stop_action("brake").stop();

            // Turn red lights on
            ev3::led::set_color(ev3::led::left,  ev3::led::red);
            ev3::led::set_color(ev3::led::right, ev3::led::red);

            // Run both motors backwards for 0.5 seconds
            lmotor.set_time_sp(500).set_speed_sp(-900).run_timed();
            rmotor.set_time_sp(500).set_speed_sp(-900).run_timed();

            // Wait 0.5 seconds while motors are rolling
            std::this_thread::sleep_for(std::chrono::milliseconds(500));

            ev3::led::all_off();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }*/
}
