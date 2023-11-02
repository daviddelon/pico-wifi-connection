/*
 * David Delon 2023
 * GNU General Public License v3.0
 */

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"


int main()
{

    stdio_init_all(); 
    
    if (cyw43_arch_init_with_country(CYW43_COUNTRY_LOCAL))
    {
        printf("failed to initialise\n");
        return 1;
    }

    cyw43_arch_enable_sta_mode();

    if (cyw43_arch_wifi_connect_blocking(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_MIXED_PSK))
    {
        printf("failed to connect\n");
        return 2;
    }

    sleep_ms(500);

    if (netif_is_link_up(netif_default) && !ip4_addr_isany_val(*netif_ip4_addr(netif_default)))
    {
        printf("IPV4: Host at %s ", ip4addr_ntoa(netif_ip4_addr(netif_default)));
        printf("mask %s ", ip4addr_ntoa(netif_ip4_netmask(netif_default)));
        printf("gateway %s\n", ip4addr_ntoa(netif_ip4_gw(netif_default)));

        uint8_t mac[6];

        if (!cyw43_wifi_get_mac(&cyw43_state, CYW43_ITF_STA, mac))
        {
            printf("MAC Address: %02X:%02X:%02X:%02X:%02X:%02X\n",
                   mac[0], mac[1], mac[2],
                   mac[3], mac[4], mac[5]);
        }
#if LWIP_NETIF_HOSTNAME
        printf("Hostname : %s\n", netif_get_hostname(netif_default));
#endif 
}
        cyw43_arch_deinit();
}