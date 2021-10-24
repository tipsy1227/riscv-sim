.equ mtime, 0x200bff8
.equ mtimecmp, 0x2004000

.weak get_mtime
.weak get_mtimecmp
.weak set_mtimecmp

get_mtime:
	la t0, mtime
	lw t2, 4(t0)
	lw t1, 0(t0)
	lw t3, 4(t0)
	bne t2, t3, get_mtime # read again if the lower part overflow
	mv a0, t1
	mv a1, t2
	ret

get_mtimecmp:
	la t0, mtimecmp
	csrrci t1, mstatus, 0x8 # disable interrupts
	lw a0, 0(t0)
	lw a1, 4(t0)
	csrw mstatus, t1
	ret

set_mtimecmp:
	la t0, mtimecmp
	csrrci t1, mstatus, 0x8 # disable interrupts
	sw a0, 0(t0)
	sw a1, 4(t0) # New value
	csrw mstatus, t1
	ret

