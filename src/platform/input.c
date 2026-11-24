volatile int *btn_pointer = (volatile int*)0x040000d0;
volatile int btn_pressed = 0;

int get_sw(void){
  volatile int* switch_values = (volatile int*) 0x04000010;
  return (*switch_values & 0x3FF);
 }

void enable_input() {
    *(btn_pointer + 3) = 1;
    *(btn_pointer + 2) = 1;
}

int get_input() {
    //Wait for input
    while(btn_pressed == 0){}

    int confirm = get_sw() & 1;

    for (volatile int i = 0; i < 500000; i++) {}

    btn_pressed = 0;

    return confirm;
}

//Choice function for choosing between any number of options 
int get_choice(int num_choice){
    volatile int *leds = (volatile int*)0x04000000;

    int choice = 0;
    int response = 0;

    *leds = 1; // LED 0 on = choice 0

    while(response == 0){
        //Get input
        response = get_input();

        //Confirm
        if(response == 1)
            return choice;

        choice = (choice + 1) % num_choice;

        *leds = (1 << choice); // LED 0 = choice 0, LED 1 = choice 1

        //Also update screen to indicate that choice changed
    }
    return choice;
}

void handle_interrupt(unsigned cause){
    switch(cause){
        //Button Interrupt
        case 18:
            *(btn_pointer + 3) = 1;
            btn_pressed = 1;
    }
}