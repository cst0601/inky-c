/*
 * Example for reading EEPROM.
 */
#include <stdio.h>
#include <unistd.h>

#include "../src/eeprom.h"

int main(int argc, char * argv[]) {
    int device = open_device(1);
    struct EPDType* data = NULL;
    __u8 buf[32];

    read_eeprom(device, buf, 32);

    create_epd_data_from_buffer(&data, buf);
    print_epd_data(data);

    free(data);
    close(device);

    return 0;
}
