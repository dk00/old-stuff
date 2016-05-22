.386
.model flat
option casemap :none

.data
    sum DWORD 0
.code
_crc32 PROC PUBLIC
    push ebp
    mov ebp, esp ; build stack frame

    ; variables in stack
    ; [ebp+12]  data length (the second argument)
    ; [ebp+8]	pointer to string data (the first argument)
    ; [ebp+4]	return address
    ; [ebp]	previous ebp

    ; begin CRC32 calculation
    ; WRITE YOUR OWN CODE HERE
    
    ; end CRC32 calculation
    mov eax, sum
    leave
    ret
_crc32 ENDP
END ; file ends here
