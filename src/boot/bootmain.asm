[org 0x0]
; This is the 'second' stage of the bootloader and our job is to load the final stage into memory
; This final stage may be longer than 1 sector, so we will have to find it in our fat16 file system and then dynamically load it into memory at 0x2000

entry:
    jmp short entry_main
    nop

; begin bpb
; bsOemName db "IBM     "
; bsBytesPerSec dw 512
; bsSecsPerClust db 1
; bsResSecs dw 1
; bsNumFats db 2
; bsRootDirEnts dw 224
; bsTotalSectors dw ; TODO: complete
; bsMediaDesc 0xf0
; bsSecsPerFat 9
; bsSecsPerTrack 18

; begin actual bootloader
entry_main:
    mov al, 'x'
    mov ah, 0x0e
    int 0x10

dynamic_dap:
    dap_size            db 0x10
    dap_unused          db 0x00
    dap_num_sectors     dw 0x01
    dap_load_offset     dw 0x00
    dap_load_segment    dw 0x2000
    dap_sector_loc      dq 0x00000000