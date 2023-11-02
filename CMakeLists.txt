# Run cmake with WIFI options : cmake ../. -DWIFI_SSID="MY-SSID" -DWIFI_PASSWORD="MY-PASSWORD" -DCYW43_COUNTRY_LOCAL=CYW43_COUNTRY_FRANCE

cmake_minimum_required(VERSION 3.12)

set(PICO_BOARD pico_w)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project (wifi)

pico_sdk_init()

add_executable (${CMAKE_PROJECT_NAME}
    wifi.c
)

pico_enable_stdio_usb(${CMAKE_PROJECT_NAME} 0)
pico_enable_stdio_uart(${CMAKE_PROJECT_NAME} 1)

target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
            WIFI_SSID=\"${WIFI_SSID}\"
            WIFI_PASSWORD=\"${WIFI_PASSWORD}\"
            CYW43_COUNTRY_LOCAL=\"${CYW43_COUNTRY_LOCAL}\"
)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
            ${CMAKE_CURRENT_LIST_DIR}
)
 

target_link_libraries(${CMAKE_PROJECT_NAME} 
	pico_stdlib
	pico_cyw43_arch_lwip_threadsafe_background
)


pico_add_extra_outputs(${CMAKE_PROJECT_NAME})


set_directory_properties(PROPERTIES
   ADDITIONAL_MAKE_CLEAN_FILES
   "${CMAKE_PROJECT_NAME}.bin;${CMAKE_PROJECT_NAME}.dis;\
    ${CMAKE_PROJECT_NAME}.elf.map;${CMAKE_PROJECT_NAME}.hex;\
    ${CMAKE_PROJECT_NAME}.uf2"
)
