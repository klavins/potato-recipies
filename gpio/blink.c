/*
 * blink.c
 *
 * Eric Klavins
 * 
 * Minimal GPIO example. Hook an LED with a resistor up to
 * pin 5 and stand back! Compile with
 *
 *    gcc blink.c -c blink
 *
 * and then do something like
 *
 *    sudo ./blink /dev/gpiochip0 0
 *
 * to see blinkiness. With gpiochip0 and offet 0 you should see a square wave
 * on GPIOH_4, which is the middle pin of the three pin header next to the
 * HDMI port.
 */

#include <linux/gpio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
//#include <sys/poll.h>
#include <assert.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    int offset = atoi(argv[2]);

    struct gpiohandle_request rq;
    struct gpiohandle_data data;
    int fd;

    fd = open(argv[1], O_RDONLY);
    assert(fd>=0);

    rq.lineoffsets[0] = offset;
    rq.flags = GPIOHANDLE_REQUEST_OUTPUT;
    rq.lines = 1;
    assert ( ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &rq) != -1 );
    close(fd);

    data.values[0] = 0;

    for ( int i=0; i<1000; i++ ) {

      data.values[0] = !data.values[0];
      assert ( ioctl(rq.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data) != -1 );
      usleep(200000);

    }

    close(rq.fd);

    return 0;

}