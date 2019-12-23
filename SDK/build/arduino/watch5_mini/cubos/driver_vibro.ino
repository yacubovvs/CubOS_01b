void driver_vibro_setup(){
    pinMode(device_vibro_pin, OUTPUT);
    driver_vibro_vibrate_sync(200);
}

void driver_vibro_vibrate_sync(uint16_t time){
    digitalWrite(device_vibro_pin, 1);
    delay(time);
    digitalWrite(device_vibro_pin, 0);
}