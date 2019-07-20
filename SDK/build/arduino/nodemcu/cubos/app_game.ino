void app_game_loop(){
  drawString("Game app", 0, 0);

  if (isPressStart(0) || isPressStart(1) || isPressStart(2)){
    current_app = 0x01;
  }
}
