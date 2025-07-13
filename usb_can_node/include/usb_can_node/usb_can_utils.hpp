#pragma once

#include <string>

void send_motor_command(const std::string& motor_l_counts_per_loop,
                        const std::string& motor_r_counts_per_loop);
