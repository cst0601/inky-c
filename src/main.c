#include <stdio.h>
#include <unistd.h>

#include "eeprom.h"

int main(int argc, char * argv[]) {
    int device = open_device(1);
    __u8 buf[32];

    read_eeprom(device, buf, 32);

    struct EPDType* data = create_epd_data_from_buffer(buf);
    print_epd_data(data);

    free(data);

    close(device);

    return 0;
}
