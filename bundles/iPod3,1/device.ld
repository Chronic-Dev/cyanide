SECTIONS {
	. = 0x41000000;
	_begin = .;
	
	.entry : {
		entry.S.o (.text .data);
	}
	
	.text : {
		* (.text);
	}
	
	.rodata : {
		* (.rodata);
	}
	
	.data : {
		* (.data);
	}

	_bss_start = .;
	.bss : {
		* (.bss);
	}
	
	_bss_end = .;
	_bss_size = _bss_end - _bss_start;
	_code_size = _bss_start - _begin;
	
	_end = .;
}
