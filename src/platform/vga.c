volatile int *const VGA_CTRL = (volatile int *) 0x04000100; 
volatile char *const VGA_BUFFER_0 = (volatile char *) 0x08000000; 
volatile char *const VGA_BUFFER_1 = (volatile char *) 0x08000000 + 320*240;
volatile char *CURRENT_BUFFER = VGA_BUFFER_1;

void swap_buffer() {

    *(VGA_CTRL + 1) = (unsigned int) CURRENT_BUFFER;

    *(VGA_CTRL + 0) = 0;

    while (*(VGA_CTRL + 3) & 1) {
        // wait
    }
    if (CURRENT_BUFFER == VGA_BUFFER_0) {
        CURRENT_BUFFER = VGA_BUFFER_1;
    } else {
        CURRENT_BUFFER = VGA_BUFFER_0;
    }
}