; Paging for address spaces for the Spectrum 128
;
; We've named address spaces after the banks for clarity
;
; Based on https://github.com/z88dk/z88dk/blob/master/examples/named-address-spaces/page.asm

SECTION code_user

PUBLIC _setb0, _setb1, _setb3, _setb4, _setb6
EXTERN l_push_di, l_pop_ei

_setb0:
    ld    a,0
    jr    page 

_setb1:
    ld    a,1
    jr    page 

_setb3:
    ld    a,3
    jr    page 

_setb4:
    ld    a,4
    jr    page      

_setb6:
    ld    a,6
    jr    page    
;we didn't actually need a jr instruction on the last one because it flows right into that anyway, but I left it in
;just in case you add _setb7 afterwards

page:
    di
    or    16
    ld    bc,32765
    out   (c),a
    ld    (23388),a
    ei
    ret