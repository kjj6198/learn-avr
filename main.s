.include "./m162def.inc"

ldi r16, 0x01
add r16, r15
out DDRB,r16
out PORTB,r16

; expected 0x02 = 0b00000010

Start:
	rjmp Start