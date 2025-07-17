add_executable(example_eeprom example_eeprom.c)

target_include_directories(example_eeprom PUBLIC ../includes)

target_link_libraries(example_eeprom PUBLIC i2c)