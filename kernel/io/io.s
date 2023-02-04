.text

// outb - send a byte to an I/O port
// stack: [esp + 8] the data byte
//        [esp + 4] the I/O port
//        [esp    ] return address
.global outb
outb:
    mov 8(%esp), %al
    mov 4(%esp), %dx
    out %al, %dx
    ret

// inb - returns a byte from the given I/O port
// stack: [esp + 4] The address of the I/O port
//    
.global inb
inb:
    mov 4(%esp), %dx
    in %dx, %al
    ret
