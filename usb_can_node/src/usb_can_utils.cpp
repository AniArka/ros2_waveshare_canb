#include "usb_can_node/usb_can_utils.hpp"
#include "usb_can_node/controlcan.h"

#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <unistd.h>
#include <pthread.h>

namespace {
bool can_initialized = false;

void init_can_if_needed()
{
    if (can_initialized) return;

    if (VCI_OpenDevice(VCI_USBCAN2, 0, 0) != 1)
    {
        std::cerr << ">> Failed to open USB-CAN device\n";
        exit(-1);
    }

    VCI_INIT_CONFIG config = {};
    config.AccCode = 0;
    config.AccMask = 0xFFFFFFFF;
    config.Filter = 1;
    config.Timing0 = 0x00;
    config.Timing1 = 0x1C;
    config.Mode = 0;

    if (VCI_InitCAN(VCI_USBCAN2, 0, 1, &config) != 1 || VCI_StartCAN(VCI_USBCAN2, 0, 1) != 1)
    {
        std::cerr << ">> Init/start CAN2 failed\n";
        VCI_CloseDevice(VCI_USBCAN2, 0);
        exit(-1);
    }

    can_initialized = true;
}

void sendIsoTp(uint8_t* payload, int len)
{
    VCI_CAN_OBJ frame;
    frame.ID = 0x123;
    frame.SendType = 0;
    frame.RemoteFlag = 0;
    frame.ExternFlag = 0;

    if (len <= 7)
    {
        frame.Data[0] = 0x00 | len;  // Single Frame
        memcpy(&frame.Data[1], payload, len);
        frame.DataLen = len + 1;
        VCI_Transmit(VCI_USBCAN2, 0, 1, &frame, 1);
    }
    else
    {
        // First Frame
        frame.Data[0] = 0x10 | ((len >> 8) & 0x0F);
        frame.Data[1] = len & 0xFF;
        memcpy(&frame.Data[2], payload, 6);
        frame.DataLen = 8;
        VCI_Transmit(VCI_USBCAN2, 0, 1, &frame, 1);
        usleep(5000);

        // Consecutive Frames
        int index = 6;
        int seq = 1;
        while (index < len)
        {
            frame.Data[0] = 0x20 | (seq & 0x0F);
            int chunk = std::min(7, len - index);
            memcpy(&frame.Data[1], &payload[index], chunk);
            frame.DataLen = chunk + 1;
            VCI_Transmit(VCI_USBCAN2, 0, 1, &frame, 1);
            usleep(5000);
            index += chunk;
            seq++;
        }
    }
}
} // namespace

void send_motor_command(const std::string& motor_l_counts_per_loop, const std::string& motor_r_counts_per_loop)
{
    init_can_if_needed();  // Ensure CAN2 is initialized

    std::string command = "m" + motor_l_counts_per_loop + "," + motor_r_counts_per_loop;
    std::vector<uint8_t> payload(command.begin(), command.end());

    sendIsoTp(payload.data(), payload.size());

    std::cout << ">> Message sent via ISO-TP over CAN2: " << command << "\n";
}
