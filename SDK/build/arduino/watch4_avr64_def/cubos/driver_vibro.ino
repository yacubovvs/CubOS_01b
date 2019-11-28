void driver_vibro_setup(){
    #ifdef device_has_vibro
      pinMode(device_vibro_pin, OUTPUT);
      driver_vibro_vibrate_sync(200);
    #endif
}

void driver_vibro_vibrate_sync(uint16_t time){
    #ifdef device_has_vibro
      digitalWrite(device_vibro_pin, 1);
      delay(time);
      digitalWrite(device_vibro_pin, 0);
    #endif
}
