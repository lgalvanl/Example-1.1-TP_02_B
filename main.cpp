#include "mbed.h"
#include "arm_book_lib.h"
#define C_MAS_MAS
//#define C_
#ifdef C_
//manipular gasDetector y alarmLed con funcionalidades de C
void inicializar_pin_sal(gpio_t *obj, PinName pin){
    gpio_init_out(obj, pin);
}

void inicializar_pin_ent(gpio_t *obj, PinName pin){
    gpio_init_in(obj, pin);
}

void inicializar_pin_ent_modo(gpio_t *obj, PinName pin,PinMode modo){
    gpio_init_in_ex(obj, pin,modo);
}

int leer_entrada(gpio_t *obj){
    return gpio_read(obj);
}
 
void escribir_pin(gpio_t *obj, int value){
    gpio_write(obj, value);
} 
int main()
{
    gpio_t gpio_gas;   
    gpio_t led;
    inicializar_pin_ent_modo(&gpio_gas ,D2,PullDown);
    inicializar_pin_sal(&led,LED1);

    int detecto_gas = leer_entrada(&gpio_gas);
    escribir_pin(&led,OFF);

    while (true) {
        if (detecto_gas) {
            printf("%s\n", "Escape de gas detectado.");
            escribir_pin(&led,ON);
        }
        
        else {
            printf("%s\n", "Alarma apagada, escape de gas no detectado.");
            escribir_pin(&led,OFF);
        }
    }
}
#endif

#ifdef C_MAS_MAS
int main()
{
    DigitalIn gasDetector(D2);

    DigitalOut alarmLed(LED1);

    gasDetector.mode(PullDown);

    alarmLed = OFF;

    while (true) {
        if ( gasDetector == ON ) {
            alarmLed = ON;
        }
        
        if ( gasDetector == OFF ) {
            alarmLed = OFF;
        }
    }
}
#endif
