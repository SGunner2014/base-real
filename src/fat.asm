%include "src/boot/drive.asm"

; Locates a file on disk in the root directory
; params:
; ax -> pointer to filename
; ax <- sector number where file is stored.
find_file:
    