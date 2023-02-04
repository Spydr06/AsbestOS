section .text

; outb - send a byte to an I/O port
; stack: [esp + 8] the data byte
;        [esp + 4] the I/O port
;        [esp    ] return address
global outb
outb:
    mov al, [esp + 8]
    mov dx, [esp + 4]
    out dx, al
    ret

; inb - returns a byte from the given I/O port
; stack: [esp + 4] The address of the I/O port
;    
global inb
inb:
    mov dx, [esp + 4]
    in al, dx
    ret
