#include <mbed.h>


using namespace std::chrono;


volatile bool sample = true;
volatile int8_t cycles = 0;
volatile int16_t datasample[40][3];
bool start_Count = false;
int range_Start = -100; // We find from experiments that when at rest, the value sampled (of angular velocities) fluctuate anywhere between -100 to 100
int range_End = 100;
static int step_count = 0; // we wish to find the no of steps taken by the person in observation
static float leg_length = 1.84 / 2 ; // height of my project partner, average height of an american male is 175.26 cms
static float linear_velocity = 0.0; // linear velocity of a man's trunk (essentially that of a person's center of mass/ gravity)
float angular_velocity[100]; // sampling values of angular velocity
static int counter = 0;


Timer first;
Timer velocity_Timer;

void setSampleFlag() {
    sample = true;
}

void calc_angular_velocity(float sum_angular_velocity, float angular_velocity[100]){
  for (int i = 0 ; i < counter ; i ++) {
    sum_angular_velocity = sum_angular_velocity + angular_velocity[i]; // physics behind this has been explained in the report. essentially, omega = d thetha / dt, integrating omega.dt gives change in angle.
  }

}

float calc_angle(float average_angular_velocity, float timeinterval_cycle){
  return average_angular_velocity * timeinterval_cycle;
} // time interval cycle is essential time interval that spans the duration of one step. For that step, we sample multiple values of omega (angular velocity)


int main() {

  // put your setup code here, to run once:
  SPI gyroscope(PF_9, PF_8, PF_7); // MOSI, MISO, SCLK (Pins are for the inbuilt Gyroscope)
  DigitalOut cs(PC_1);

  Ticker ticker;

  
  static float distance = 0; // initialising distance travelled.

  cs = 1; // chipselect equals 1

  gyroscope.format(8,3);
  gyroscope.frequency(1000000);

  // Setting L3GD20 to 'Normal' mode
  cs = 0;
  gyroscope.write(0x20);
  gyroscope.write(0xF);
  cs = 1;

  ticker.attach(&setSampleFlag, 500ms); //sampling every 0.5 sec
  
  while(1) {
    

      cs = 0;

      gyroscope.write(0xA8);
      
      int8_t out_x_l = gyroscope.write(0x00);

      cs = 1;
      cs = 0;

      gyroscope.write(0xA9);
      int8_t out_x_h = gyroscope.write(0x00);
      datasample[cycles][0] = (out_x_h << 8 | out_x_l); // we see change only in x axis of rotation. Other changes are insignificant and cannot deduce distance travelled.

    if(start_Count) {
      angular_velocity[counter] = datasample[cycles][0] * 0.00875 * 0.0175; // 0.00875 multiplication factor converts into degree per second, 0.0175 changes into radian per second, which is the SI unit of measurement.
      counter = counter + 1;
    }


    if((datasample[cycles][0] > range_Start && datasample[cycles][0] < range_End) && start_Count) { 
        // we see (from multiple experiments) that once we get low values of omega,it marks the conclusion of one step.
          step_count = step_count + 1; // hence incrementing, we have observed the conclusion of one step
          start_Count = false;
          first.stop();
          //
          float timeinterval_cycle = (duration_cast<milliseconds>(first.elapsed_time()).count()) / 1000;
          
          float sum_angular_velocity = 0;
          
          calc_angular_velocity(sum_angular_velocity, angular_velocity);

          float average_angular_velocity = (float) sum_angular_velocity / (float) counter;
          counter = 0;

          float angle = calc_angle(average_angular_velocity, timeinterval_cycle);

          float current_Distance = abs(leg_length * cos(angle));
          float current_Velocity = 0;

          if(timeinterval_cycle > 0) {
          distance = distance + current_Distance;
          current_Velocity = current_Distance / timeinterval_cycle;
          
          } else {
            printf("here");
            current_Velocity = 0;
          }

        linear_velocity =  current_Velocity;
    } 
    if(datasample[cycles][0] > 2000) {
      start_Count = true;
      first.start();
    }


    printf("Distance : %f \n", distance);
    printf("Steps : %d \n", step_count);
    printf("Velocity : %f \n", linear_velocity);
    printf("\n\n");
    
    
    linear_velocity = 0;
    
    cycles++;

    if(cycles >= 40) {
      cycles = 0;
    }

}
}