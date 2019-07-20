void loop_os_splashscreen(){
  drawString("CubOS v0.1a", 0, 0);
  updatescreen_displayDriver();
  delay(1000);

  // Switch to the menu app
  current_app = 0x01;
  // current_app = 0x02; // Clock
  // current_app = 0x03; // Settings
}
