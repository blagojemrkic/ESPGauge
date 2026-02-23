/*
ESP Gauge Init no.01 - ESP32 board init. 
-----------------------------------------------------

Initilaze ESP32 board with basic Serial communication. 

*/

/*Using LVGL with Arduino requires some extra steps:
 *Be sure to read the docs here: https://docs.lvgl.io/master/get-started/platforms/arduino.html  */

#include <lvgl.h>
#include <TFT_eSPI.h>
#include "ui.h"

extern lv_obj_t * ui_Screen1;
extern lv_obj_t * ui_RMPgauge;
extern lv_obj_t * ui_SpeedGauge;
extern lv_obj_t * ui_SpeedLable;
extern lv_obj_t * ui_RPMLable;
extern lv_obj_t * ui_RPMunit;
extern lv_obj_t * ui_SpeedUnit;

extern lv_obj_t * ui_yellowBatWarrinig;
extern lv_obj_t * ui_redBatWarring;
extern lv_obj_t * ui_yellowOilWarrning;
extern lv_obj_t * ui_redOilWarring;
extern lv_obj_t * ui_yellowEngineWarrning;
extern lv_obj_t * ui_redEngineWarrning;

/*To use the built-in examples and demos of LVGL uncomment the includes below respectively.
 *You also need to copy `lvgl/examples` to `lvgl/src/examples`. Similarly for the demos `lvgl/demos` to `lvgl/src/demos`.
 Note that the `lv_examples` library is for LVGL v7 and you shouldn't install it for this version (since LVGL v8)
 as the examples and demos are now part of the main LVGL library. */

const unsigned long update_interval = 25; 
const unsigned long update_rpm_interval = 25; 
const unsigned long update_warrning_interval = 2000; 
unsigned long previous_tick_speed = 0; 
unsigned long previous_tick_rpm = 0; 
unsigned long previous_tick_warrning = 0; 

/*Change to your screen resolution*/
static const uint16_t screenWidth  = 240;
static const uint16_t screenHeight = 240;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[ screenWidth * screenHeight / 10 ];

TFT_eSPI tft = TFT_eSPI(screenWidth, screenHeight); /* TFT instance */

#if LV_USE_LOG != 0
/* Serial debugging */
void my_print(const char * buf)
{
    Serial.printf(buf);
    Serial.flush();
}
#endif

/* Display flushing */
void my_disp_flush( lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p )
{
    uint32_t w = ( area->x2 - area->x1 + 1 );
    uint32_t h = ( area->y2 - area->y1 + 1 );

    tft.startWrite();
    tft.setAddrWindow( area->x1, area->y1, w, h );
    tft.pushColors( ( uint16_t * )&color_p->full, w * h, true );
    tft.endWrite();

    lv_disp_flush_ready( disp_drv );
}

// /*Read the touchpad*/
// void my_touchpad_read( lv_indev_drv_t * indev_drv, lv_indev_data_t * data )
// {
//     uint16_t touchX, touchY;

//     bool touched = tft.getTouch( &touchX, &touchY, 600 );

//     if( !touched )
//     {
//         data->state = LV_INDEV_STATE_REL;
//     }
//     else
//     {
//         data->state = LV_INDEV_STATE_PR;

//         /*Set the coordinates*/
//         data->point.x = touchX;
//         data->point.y = touchY;

//         Serial.print( "Data x " );
//         Serial.println( touchX );

//         Serial.print( "Data y " );
//         Serial.println( touchY );
//     }
// }

void setup()
{
    Serial.begin( 115200 ); /* prepare for possible serial debug */

    String LVGL_Arduino = "Hello Arduino! ";
    LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();

    Serial.println( LVGL_Arduino );
    Serial.println( "I am LVGL_Arduino" );

    lv_init();

#if LV_USE_LOG != 0
    lv_log_register_print_cb( my_print ); /* register print function for debugging */
#endif

    tft.begin();          /* TFT init */
    tft.setRotation( 3 ); /* Landscape orientation, flipped */

    /*Set the touchscreen calibration data,
     the actual data for your display can be acquired using
     the Generic -> Touch_calibrate example from the TFT_eSPI library*/
    // uint16_t calData[5] = { 275, 3620, 264, 3532, 1 };
    // tft.setTouch( calData );

    lv_disp_draw_buf_init( &draw_buf, buf, NULL, screenWidth * screenHeight / 10 );

    /*Initialize the display*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init( &disp_drv );
    /*Change the following line to your display resolution*/
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register( &disp_drv );

    // /*Initialize the (dummy) input device driver*/
    // static lv_indev_drv_t indev_drv;
    // lv_indev_drv_init( &indev_drv );
    // indev_drv.type = LV_INDEV_TYPE_POINTER;
    // indev_drv.read_cb = my_touchpad_read;
    // lv_indev_drv_register( &indev_drv );
  
    // /* Create simple label */
    // lv_obj_t *label = lv_label_create( lv_scr_act() );
    // lv_label_set_text( label, "Hello Ardino and LVGL!");
    // lv_obj_align( label, LV_ALIGN_CENTER, 0, 0 );
 
    /* Try an example. See all the examples 
     * online: https://docs.lvgl.io/master/examples.html
     * source codes: https://github.com/lvgl/lvgl/tree/e7f88efa5853128bf871dde335c0ca8da9eb7731/examples */
     //lv_example_btn_1();
   
     /*Or try out a demo. Don't forget to enable the demos in lv_conf.h. E.g. LV_USE_DEMOS_WIDGETS*/
    //lv_demo_widgets();               
    // lv_demo_benchmark();          
    // lv_demo_keypad_encoder();     
    // lv_demo_music();              
    // lv_demo_printer();
    // lv_demo_stress();

    ui_init();
    
    Serial.println( "Setup done" );
}


// lv_arc_set_value(ui_RMPgauge, 5000);
// lv_arc_set_value(ui_SpeedGauge, 100);
// lv_label_set_text(ui_SpeedUnit, "km/h");
// lv_label_set_text(ui_SpeedUnit, "km/h");

void update_speed_value(int * current_speed){

  int max_speed = 160; 
  int min_speed = 0; 
  int delta_speed = 1;

  static bool direction_up = true;

  if (direction_up){
    // Increase speed 
    if (*current_speed + delta_speed >= max_speed){
      // Change direction 
      // limit current speed to max
      *current_speed = max_speed; 
      direction_up = false; 
    }
    else {
      *current_speed += delta_speed; 
    }
 }
  else{
    // Decrease speed 
    if (*current_speed - delta_speed <= min_speed){ 
      // Change direction 
      //  limit current speed to min
      *current_speed = min_speed; 
      direction_up = true;
    }
    else {
      *current_speed -= delta_speed;
    }
  }
  lv_arc_set_value(ui_SpeedGauge, *current_speed);
}

void update_speed_text (const int *current_speed){
  // update ui_SpeedLable with text 
  char cstr[10]; // Ensure the array is large enough for the number, sign, and null terminator

  // Convert the integer to a string in base 10 (decimal)
  itoa(*current_speed, cstr, 10);

  lv_label_set_text(ui_SpeedLable, cstr);

}

void update_speed(unsigned long tick){
  // Update Speed Gauge 
  // Check elapse time
  // demo function for speed data
  static int main_speed = 0;   

  if ((tick - previous_tick_speed) > update_interval) {
    // time elapsed - update Speed gauge 
    update_speed_value(&main_speed);
    update_speed_text(&main_speed);
    previous_tick_speed = tick;
  }
}

void update_rpm_value(int * current_rmp){

  int max_rpm = 8000; 
  int min_rpm = 0; 
  int delta_rpm = 100;

  static bool direction_up = true;

  if (direction_up){
    // Increase speed 
    if (*current_rmp + delta_rpm >= max_rpm){
      // Change direction 
      // limit current speed to max
      *current_rmp = max_rpm; 
      direction_up = false; 
    }
    else {
      *current_rmp += delta_rpm; 
    }
 }
  else{
    // Decrease speed 
    if (*current_rmp - delta_rpm <= min_rpm){ 
      // Change direction 
      //  limit current speed to min
      *current_rmp = min_rpm; 
      direction_up = true;
    }
    else {
      *current_rmp -= delta_rpm;
    }
  }
  lv_arc_set_value(ui_RMPgauge, *current_rmp);
}

void update_rpm_text (const int *current_rpm){
  // update ui_RPMLable with text 
  char cstr[10]; // Ensure the array is large enough for the number, sign, and null terminator

  // Convert the integer to a string in base 10 (decimal)
  itoa(*current_rpm, cstr, 10);

  lv_label_set_text(ui_RPMLable, cstr);
}


void update_rpm(unsigned long tick){
  // Update RPM Gauge 
  // Check elapse time 
  // Demo fuction for RPM data
  static int main_rmp = 0;   

  if ((tick - previous_tick_rpm) > update_rpm_interval) {
    // time elapsed - update RPM gauge 
    update_rpm_value(&main_rmp);
    update_rpm_text(&main_rmp);
    previous_tick_rpm = tick;
  }
}

/*
extern lv_obj_t * ui_yellowBatWarrinig;
extern lv_obj_t * ui_redBatWarring;
extern lv_obj_t * ui_yellowOilWarrning;
extern lv_obj_t * ui_redOilWarring;
extern lv_obj_t * ui_yellowEngineWarrning;
extern lv_obj_t * ui_redEngineWarrning;
*/

void update_warrning(unsigned long tick){

  static int warrning_selection = 0; // 0 - no warrning, 1 - yellow, 2 - red 

  if ((tick - previous_tick_warrning) > update_warrning_interval) {
    switch (warrning_selection) {
      case 1:
        warrning_selection = 2; 
        lv_obj_clear_flag(ui_yellowBatWarrinig, LV_OBJ_FLAG_HIDDEN); 
        lv_obj_clear_flag(ui_yellowOilWarrning, LV_OBJ_FLAG_HIDDEN); 
        lv_obj_clear_flag(ui_yellowEngineWarrning, LV_OBJ_FLAG_HIDDEN); 
        lv_obj_add_flag(ui_redBatWarring, LV_OBJ_FLAG_HIDDEN); 
        lv_obj_add_flag(ui_redOilWarring, LV_OBJ_FLAG_HIDDEN); 
        lv_obj_add_flag(ui_redEngineWarrning, LV_OBJ_FLAG_HIDDEN); 
        break; 
      case 2:
        warrning_selection = 0;
        lv_obj_clear_flag(ui_redBatWarring, LV_OBJ_FLAG_HIDDEN); 
        lv_obj_clear_flag(ui_redOilWarring, LV_OBJ_FLAG_HIDDEN); 
        lv_obj_clear_flag(ui_redEngineWarrning, LV_OBJ_FLAG_HIDDEN); 
        lv_obj_add_flag(ui_yellowBatWarrinig, LV_OBJ_FLAG_HIDDEN); 
        lv_obj_add_flag(ui_yellowOilWarrning, LV_OBJ_FLAG_HIDDEN); 
        lv_obj_add_flag(ui_yellowEngineWarrning, LV_OBJ_FLAG_HIDDEN); 
        break;
      default: 
        warrning_selection = 1;
        lv_obj_add_flag(ui_redBatWarring, LV_OBJ_FLAG_HIDDEN); 
        lv_obj_add_flag(ui_redOilWarring, LV_OBJ_FLAG_HIDDEN); 
        lv_obj_add_flag(ui_redEngineWarrning, LV_OBJ_FLAG_HIDDEN); 
        lv_obj_add_flag(ui_yellowBatWarrinig, LV_OBJ_FLAG_HIDDEN); 
        lv_obj_add_flag(ui_yellowOilWarrning, LV_OBJ_FLAG_HIDDEN); 
        lv_obj_add_flag(ui_yellowEngineWarrning, LV_OBJ_FLAG_HIDDEN); 

    }
    previous_tick_warrning= tick;
  }
}

void loop()
{

    unsigned long current_tick = millis(); 
    unsigned long old_tick = 0;

    update_speed(current_tick);
    update_rpm(current_tick);
    update_warrning(current_tick);

    lv_timer_handler(); /* let the GUI do its work */
    lv_tick_inc(current_tick - old_tick);
    
    old_tick = current_tick;
    delay(5);

}