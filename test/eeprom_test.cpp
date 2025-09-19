#include <gtest/gtest.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include "../src/eeprom.h"

namespace 
{
    // EEPROM data from Spectra 6 7.3" model
    const char eeprom_data[] = 
        "\x20\x03\xe0\x01\x06\x64\x16\x15\x32\x30\x32\x35\x2d\x30\x35\x2d"
        "\x30\x37\x20\x31\x33\x3a\x35\x32\x3a\x30\x39\x2e\x33";

    // Since gTest does not allow mock for c-style function, we need the actual
    // device (for now) to test read_eeprom().
    // See https://github.com/google/googletest/blob/main/docs/gmock_cook_book.md#mocking-free-functions
    TEST(Eeprom, TestReadEeprom) 
    {
        const int device = open_device(1);
        char buf[32];

        read_eeprom(device, buf, 32);

        for (size_t i = 0; i < (size_t)EEP_READ_LENGTH; i++) {
            ASSERT_EQ(eeprom_data[i], buf[i]);
        }

        close(device);
    }

    TEST(Eeprom, TestCreateEpdDataFromBuffer)
    {
        struct EPDType* epd_data = NULL;
        create_epd_data_from_buffer(&epd_data, eeprom_data);
        
        ASSERT_EQ(epd_data->width, 800);
        ASSERT_EQ(epd_data->height, 480);
        ASSERT_EQ(epd_data->color, 6);
        ASSERT_EQ(epd_data->pcb_variant, 100);
        ASSERT_EQ(epd_data->display_variant, 22);

        delete epd_data;
    }
}
