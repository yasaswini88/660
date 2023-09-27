#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define DIR_1_ST "/sys/class/gpio/gpio67/direction"
#define DIR_2_ST "/sys/class/gpio/gpio44/direction"
#define DIR_3_ST "/sys/class/gpio/gpio68/direction"
#define DIR_1_OP "/sys/class/gpio/gpio45/direction"
#define DIR_2_OP "/sys/class/gpio/gpio69/direction"
#define DIR_3_OP "/sys/class/gpio/gpio66/direction"

#define VAL_1_ST "/sys/class/gpio/gpio67/value"
#define VAL_2_ST "/sys/class/gpio/gpio44/value"
#define VAL_3_ST "/sys/class/gpio/gpio68/value"
#define VAL_1_OP "/sys/class/gpio/gpio45/value"
#define VAL_2_OP "/sys/class/gpio/gpio69/value"
#define VAL_3_OP "/sys/class/gpio/gpio66/value"

#define OUT "out"

#define ON 1
#define OFF 0

int write_val(char *light, int val);
int open_dir(int f, char *dir);
int init_gpios();

int main(void)
{
    if (init_gpios() == -1)
    {
        printf("Error with GPIO initialisation \n");
        return -1;
    }

    while (1)
    {
        write_val(VAL_1_ST, ON);
        write_val(VAL_2_ST, OFF);
        write_val(VAL_3_ST, OFF);
        write_val(VAL_1_OP, OFF);
        write_val(VAL_2_OP, OFF);
        write_val(VAL_3_OP, ON);
        sleep(120);
        write_val(VAL_1_ST, ON);
        write_val(VAL_2_ST, OFF);
        write_val(VAL_3_ST, OFF);
        write_val(VAL_1_OP, OFF);
        write_val(VAL_2_OP, ON);
        write_val(VAL_3_OP, OFF);
        sleep(5);
        write_val(VAL_1_ST, OFF);
        write_val(VAL_2_ST, ON);
        write_val(VAL_3_ST, OFF);
        write_val(VAL_1_OP, ON);
        write_val(VAL_2_OP, OFF);
        write_val(VAL_3_OP, OFF);
        sleep(120);
        write_val(VAL_1_ST, OFF);
        write_val(VAL_2_ST, OFF);
        write_val(VAL_3_ST, ON);
        write_val(VAL_1_OP, ON);
        write_val(VAL_2_OP, OFF);
        write_val(VAL_3_OP, OFF);
        sleep(5);
    }
}

int write_val(char *light, int val)
{
    int f = 0;

    f = open(light, O_RDWR);

    if (f < 0)
    {
        fprintf(stderr, "Error opening \"%s\" Value", light);
        return -1;
    }

    val == ON ? write(f, "1", 1) : write(f, "0", 1);

    close(f);
}

int open_dir(int f, char *dir)
{
    f = open(dir, O_RDWR);

    if (f < 0)
    {
        fprintf(stderr, "Error opening \"%s\" Direction", dir);
        return -1;
    }

    write(f, OUT, 3);
    close(f);

    return 0;
}

int init_gpios()
{
    int f = 0;

    f = open_dir(f, DIR_1_ST);
    f = open_dir(f, DIR_2_ST);
    f = open_dir(f, DIR_3_ST);

    f = open_dir(f, DIR_1_OP);
    f = open_dir(f, DIR_2_OP);
    f = open_dir(f, DIR_3_OP);

    return f;
}
