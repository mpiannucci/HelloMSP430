#ifndef DHT11_H
#define DHT11_H

typedef struct DHT11_Data {
    unsigned int Humidity;
    unsigned int Temperature;
    unsigned int CheckSum;

    unsigned int _humidity;
    unsigned int _temperature;
} DHT11_Data;

void dht11_init(void);

void dht11_set_timer_isr_ptr(void (*isr_ptr)(void));

static void dht11_send_start_signal(void);

static unsigned int dht11_check_response(void);

static unsigned int dht11_read_byte(void);

unsigned int dht11_verify_checksum(void);

DHT11_Data dht11_get_data(void);

#endif // DHT11_H