#include <stdio.h>
#include <time.h> 
#include "E101.h"
extern "C" int init(int d_lev);
extern "C" int Sleep (int sec, int usec);
extern "C" int set_motor(int motor, int speed);
extern "C" int write_digital(int chan, char level);
extern "C" int read_digital(int chan, int direct);
extern "C" int select_IO(int chan, int direct);
extern "C" int read_analog(int ch_adc);
extern "C" int take_picture();
extern "C" char get_pixel(int row, int col, int color);

    // Bunch of code, need to divide for individual work. Does not include line
    // following code and does not include wall detectors, yet.

int Average(); //to calculate
int turnLeft();
int turnRight();
int driveStraight();
int reverse();
int wallDetector();
int defaultSpeed (20);
void lineRunner();

    // sets up everything to ensure it is working.

int main()
    {
    init();
    printf("ADC mean: %d/n", Average);
    turnLeft(1);
    turnRight(1);
    driveStraight();
    wallDetector();
    stop();
    return 0;
    }

    //kill program. Only needs to be used to test we actually have something.

int Average()
    {
    int track();
    int Average;

    // read analog input
    for(int c = 0; c<10; c++)
        {
        track += read_analog(0);
        sleep(0,5);
        return Average;
        }
    }

    // line following code - maybe?
    // Basically we need a control loop to maintain an error value (eVal) to follow a line.
    // Outcome - we need to constantly calculate error values and apply the scaled error to our motors (turns based on what it sees)
    // threshhold is always the middle value (1-3 = 2) whic is what must be maintained.
    // Must have error, proprotional term (KP) kDer (KD) kInt (KI) scaled value
    // (Speed with Error) and the applied value (Scale value to motor.)
    // For this the actual line followed would be the edges of the white line, not the centre.

void lineRunner()
    {
    int eVal();   //determines the current error of what is shown.
    int previousVal();  //tracks the previous error of what was shown.
    int difference();   // calculates the difference between previous and current.
    int error(); // tracks the total error (averages are cool) Sensor readings are key for errors.
    int pixelTot(); // pretty much the foundation, differentiates colours.

    double period = (0);
    clock_t start;
    clock_t now;

    float kDer = 0; // constant derivative.
    int derSig = 0; // used to scale motors.

    float kInt = 0; // constant integral.
    int intSig = 0; // used to scale motors.

    float kp = 0.1; // probably have to test this out, this changes based on a lot of factors.
    int pSig = 0; //scales using proportional constant and motors.

    int defaultSpeed = 30;

        // This part actually follows the line (hopefully) based on all the previously set things.

    while(true)
        { // will have to eventually break this to turn it off once the quadrant has been completed and the sensors detect walls.
            start = clock();
            take_picture();
            eVal = 0; // keep this 0
            pSig = 0; // it's a constant, keep it 0.
            pixelTot = 0;

            for(int count = 0; count < 320; count++)
            {
            int noise = get_pixel(count, 120, 3); // Gives pixel brightness, handles the noise.

            if(noise < 120)
                {
                    noise = 0; // Always reset, it's a loop.
                }
                else
                {
                    noise = 1; // To follow the line.
                    pixelTot += 1;
                }

                eVal += (count - 160) * noise; // Equates to 0, ensuring the edges of the line are followed. I hope.
            }
            // if there is no walls, only lines - aka quadrant whatever.

            if (eVal < 500 && eval > -500 && pixelTot > 300)
            {
                return; // we out boiz.
            }

            now = clock();
            ePeriod = ((double)(now - start)) / CLOCKS_PER_SEC;

            difference = eVal - previousVal;
            derSig = (difference/ePeriod) * kDer; // constant

            previousVal = eVal;
            error += eVal; //Sums error.

            pSig = eVal*kp;
            intSig = (error * kInt);

            //change the speeds, based on the scaling of everything prior.

            set_motor(2, defaultSpeed - pSig - intSig + derSig);
            set_motor(1, defaultSpeed + pSig - intSig -derSig);
            }
    }
