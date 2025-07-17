#ifndef EEPROM_H
#define EEPROM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <i2c/smbus.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <error_handlers.h>

__u8 EEP_ADDRESS = 0x50;
__u8 EEP_WP = 12;
__u8 EEP_READ_COMMAND = 0;
__u8 EEP_READ_LENGTH = 29;

const char *VALID_COLORS[] = {
    NULL, "black", "red", "yellow", NULL, "7colour", "spectra6"
};

const char* DISPLAY_VARIANT[] = { 
    NULL,
    "Red pHAT (High-Temp)",
    "Yellow wHAT",
    "Black wHAT",
    "Black pHAT",
    "Yellow pHAT",
    "Red wHAT",
    "Red wHAT (High-Temp)",
    "Red wHAT",
    NULL,
    "Black pHAT (SSD1608)",
    "Red pHAT (SSD1608)",
    "Yellow pHAT (SSD1608)",
    NULL,
    "7-Colour (UC8159)",
    "7-Colour 640x400 (UC8159)",
    "7-Colour 640x400 (UC8159)",
    "Black wHAT (SSD1683)",
    "Red wHAT (SSD1683)",
    "Yellow wHAT (SSD1683)",
    "7-Colour 800x480 (AC073TC1A)",
    "Spectra 6 13.3 1600 x 1200 (EL133UF1)",
    "Spectra 6 7.3 800 x 480 (E673)"
};

/**
 * u16 width 
 * u16 height
 * u8  color
 * u8  pcb_variant
 * u8  display_variant
 * char* eeprom_write_time, size = 22
 */
struct EPDType {
    __u16 width;
    __u16 height;
    __u8 color;
    __u8 pcb_variant;
    __u8 display_variant;
    char eeprom_write_time[22];
};

struct EPDType* create_epd_data_from_buffer(const char* buf)  {
    struct EPDType* data = (struct EPDType*)malloc(sizeof(struct EPDType));

    memcpy(&data->width, buf, sizeof(__u16));
    memcpy(&data->height, buf+2, sizeof(__u16));
    memcpy(&data->color, buf+4, sizeof(__u8));
    memcpy(&data->pcb_variant, buf+5, sizeof(__u8));
    memcpy(&data->display_variant, buf+6, sizeof(__u8));
    memcpy(&data->eeprom_write_time, buf+7, sizeof(char) * 22);

    return data;
}

void print_epd_data(const struct EPDType* data) {
    printf(
        "Display: %ux%u\n"
        "Color: %s\n"
        "PCB Variant: %.1f\n"
        "Display Variant: %s\n"
        "Time: %s\n",
        data->width,
        data->height,
        VALID_COLORS[data->color],
        data->pcb_variant / 10.0,
        DISPLAY_VARIANT[data->display_variant],
        data->eeprom_write_time
    );
}

/**
 * Open i2c device on adapter_nr. Returns open file, exits the program if
 * fails.
 */
int open_device(int adapter_nr) {
    int file;
    char filename[20];

    snprintf(filename, 19, "/dev/i2c-%d", adapter_nr);
    file = open(filename, O_RDWR);
    if (file < 0) {
        fprintf(stderr, "Error opening device /dev/i2c-%d.\n", adapter_nr);
        exit(1);
    }
    return file;
}

/* buf max 32 bytes */
void read_eeprom(int file, char* buf, size_t buf_size) {
    __u8 reg = 0x10;
    __u8 write_data[1] = {0x00};
    __s32 res = 0;

    if (ioctl(file, I2C_SLAVE, EEP_ADDRESS) < 0) {
        fprintf(stderr, "Error calling ioctl.\n");
        close(file);
        exit(1);
    }

    HANDLE_ERROR(
        i2c_smbus_write_i2c_block_data(file, 0x00, 1, write_data),
        "Error writing block data to i2c."
    );

    res = HANDLE_ERROR(
        i2c_smbus_read_i2c_block_data(file, EEP_READ_COMMAND, EEP_READ_LENGTH, (__u8*)buf),
        "Error reading from device."
    );
}

#ifdef __cplusplus
}
#endif
#endif
