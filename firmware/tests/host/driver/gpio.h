#pragma once
#include <cstdint>
using gpio_num_t = int;
constexpr int ESP_OK = 0;
constexpr int GPIO_MODE_INPUT = 1;
constexpr int GPIO_MODE_OUTPUT = 2;
constexpr int GPIO_PULLUP_DISABLE = 0;
constexpr int GPIO_PULLDOWN_DISABLE = 0;
constexpr int GPIO_INTR_DISABLE = 0;
struct gpio_config_t {
    std::uint64_t pin_bit_mask;
    int mode, pull_up_en, pull_down_en, intr_type;
};
int gpio_set_level(gpio_num_t pin, int value);
int gpio_config(const gpio_config_t* config);
