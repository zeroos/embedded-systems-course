// częstotliwość taktowania Arduino
// do kalibracji pętli opóźniających
#define F_CPU 16000000

// operacje wejścia/wyjścia
#include <avr/io.h>
// pętle opóźniające
#include <util/delay.h>

int
main()
{
    DDRB |= _BV(PB5);  // pin B5 jest wyjściem
    PORTD |= _BV(PD2); // włączamy rezystor pull-up dla pinu D2
    while (1) {
        if (!(PIND & _BV(PD2))) {  // jeśli przycisk jest wciśnięty (pin D2)
            PORTB |= _BV(PB5);     // zapalamy diodę
            _delay_ms(500);        // czekamy 500 ms
            PORTB &= ~_BV(PB5);    // gasimy diodę
            _delay_ms(500);        // czekamy 500 ms
        } else PORTB &= ~_BV(PB5); // gasimy diodę
    }
}
