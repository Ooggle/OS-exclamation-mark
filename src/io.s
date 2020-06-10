global outb
global inb

; outb - send a byte to an I/O port
;
; stack: [esp + 8] the data byte
;        [esp + 4] the I/O port
;        [esp    ] return address
outb:
mov AL, [esp + 8]
mov DX, [esp + 4]
out DX, AL
ret

;inb - read a byte from a I/O port
;
; stack: [esp + 4] the I/O port
;        [esp    ] the return address
inb:
mov DX, [esp + 4]
in AL, DX
ret
