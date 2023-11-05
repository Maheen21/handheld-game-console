#include <TFT_eSPI.h>
#include <SPI.h>


TFT_eSPI tft = TFT_eSPI();

int playerWidth = 10;

int playerX = 165;
int playerY = 430;
uint16_t playerColor = TFT_PURPLE;

int obstacleWidth = 17;

uint16_t obstacleColor = TFT_RED;

int obstacleX = 30;
int obstacleY = 50;

int obstacle2X = 270;
int obstacle2Y = 50;

int obstacle3X = 90;
int obstacle3Y = 50;

int obstacle4X = 210;
int obstacle4Y = 50;

int button;
int joystickX = 0;
int joystickY = 0;
int game_speed = 0;

int score;
int position = 0;
int move = 15;
bool gameover = false;
#define WHITE 0xFFFF
#define BLACK 0x0000
void setup() {
  tft.begin();

  tft.fillScreen(BLACK);
  beginning_screen();
  tft.fillScreen(BLACK);
  pinMode(7,INPUT);

}

void loop() {
  tft.setRotation(0);
  
  // Read joystick input
  pinMode(7, INPUT);
  joystickX = analogRead(A6);
  joystickY = analogRead(A7);
  

  // Move player based on joystick input
  if (!gameover){
    gamescreen();
    if (joystickX < 7) {
      tft.fillCircle(playerX, playerY, playerWidth, TFT_BLACK);
      tft.drawLine(playerX, playerY, (playerX-30), 430, TFT_BLACK);
      tft.drawLine((playerX-30), 430, (playerX - 40), (playerY - 10), TFT_BLACK);
      tft.drawLine((playerX-30), 430, (playerX - 40), (playerY + 10), TFT_BLACK);
      tft.drawLine((playerX-15), (playerY - 10), (playerX - 15), (playerY + 10), TFT_BLACK);
      playerX -= 60;
    }
    else if (joystickX > 1015) {
      tft.fillCircle(playerX, playerY, playerWidth, TFT_BLACK);
      tft.drawLine(playerX, playerY, (playerX-30), 430, TFT_BLACK);
      tft.drawLine((playerX-30), 430, (playerX - 40), (playerY - 10), TFT_BLACK);
      tft.drawLine((playerX-30), 430, (playerX - 40), (playerY + 10), TFT_BLACK);
      tft.drawLine((playerX-15), (playerY - 10), (playerX - 15), (playerY + 10), TFT_BLACK);
      playerX += 60;
    }
    // Make sure player doesn't go off the screen
    if (playerX < 45) {
      playerX = 45;
    }
    if (playerX > 285) {
      playerX = 285;
    }

    drawPlayer();

    tft.fillCircle(obstacleX, obstacleY, obstacleWidth, TFT_BLACK);
    obstacleY += move;
    if (obstacleY > 480) {
    
    position = random(0,5);
    if (position == 0){
      obstacleX = 30;
    }
    else if (position == 1){
      obstacleX = 90;
    }
    else if (position == 2){
      obstacleX = 150;
    }
    else if (position == 3){
      obstacleX = 210;
    }
    else{
      obstacleX = 270;
    }

    obstacleY = 0;
    score++;
    displayScore();
    displaySpeed();
    tft.setRotation(0);
    }
    if (checkCollision()) {
      gameover = true;
      playagain();
    }
  
  // Move obstacle and check if it collided with player
    tft.fillCircle(obstacleX, obstacleY, obstacleWidth, obstacleColor);

    tft.fillCircle(obstacle2X, obstacle2Y, obstacleWidth, TFT_BLACK);
    obstacle2Y += move;
    if (obstacle2Y > 480) {
    
    position = random(5,10);
    if (position == 5){
      obstacle2X = 30;
    }
    else if (position == 6){
      obstacle2X = 90;
    }
    else if (position == 7){
      obstacle2X = 150;
    }
    else if (position == 8){
      obstacle2X = 210;
    }
    else{
      obstacle2X = 270;
    }
    displayScore();

    tft.setRotation(0);
    obstacle2Y = 0;
  }
    if (checkCollision2()) {
      gameover = true;
      playagain(); // Game over
    //while (true); // Wait forever
  }

    tft.fillCircle(obstacle2X, obstacle2Y, obstacleWidth, obstacleColor);

    tft.fillCircle(obstacle3X, obstacle3Y, obstacleWidth, TFT_BLACK);
    obstacle3Y += move;
    if (obstacle3Y > 480) {
    
    position = random(10,15);
    if (position == 10){
      obstacle3X = 30;
    }
    else if (position == 11){
      obstacle3X = 90;
    }
    else if (position == 12){
      obstacle3X = 150;
    }
    else if (position == 13){
      obstacle3X = 210;
    }
    else{
      obstacle3X = 270;
    }
    displayScore();

    tft.setRotation(0);
    obstacle3Y = 0;
  }
    if (checkCollision3()) {
      gameover = true;
      playagain(); // Game over
    //while (true); // Wait forever
  }

    tft.fillCircle(obstacle3X, obstacle3Y, obstacleWidth, obstacleColor);
    tft.fillCircle(obstacle4X, obstacle4Y, obstacleWidth, TFT_BLACK);
    obstacle4Y += move;
    if (obstacle4Y > 480) {
    
    position = random(15,20);
    if (position == 15){
      obstacle4X = 30;
    }
    else if (position == 16){
      obstacle4X = 90;
    }
    else if (position == 17){
      obstacle4X = 150;
    }
    else if (position == 18){
      obstacle4X = 210;
    }
    else{
      obstacle4X = 270;
    }
    displayScore();

    tft.setRotation(0);

    obstacle4Y = 0;
  }
    if (checkCollision4()) {
      gameover = true;
      playagain(); // Game over
    //while (true); // Wait forever
  }

    tft.fillCircle(obstacle4X, obstacle4Y, obstacleWidth, obstacleColor);

    speed();


  }
   // Game over
  else{
    checkplayagain();
  }
    //while (true); // Wait forever
    

  

  delay(10);
}



void drawPlayer() { 
  //tft.fillCircle(playerX, playerY, playerWidth, TFT_BLACK);
  tft.fillCircle(playerX, playerY, playerWidth, playerColor);
  tft.drawLine(playerX, playerY, (playerX-30), 430, playerColor);
  tft.drawLine((playerX-30), 430, (playerX - 40), (playerY - 10), playerColor);
  tft.drawLine((playerX-30), 430, (playerX - 40), (playerY + 10), playerColor);
  tft.drawLine((playerX-15), (playerY - 10), (playerX - 15), (playerY + 10), playerColor);
}

bool checkCollision() {
  int playerCenterX = playerX + playerWidth/2;
  int playerCenterY = playerY + playerWidth/2;
  int obstacleCenterX = obstacleX +  obstacleWidth/2;
  int obstacleCenterY = obstacleY +  obstacleWidth/2;
  int distance = sqrt(pow(obstacleCenterX - playerCenterX, 2) + pow(obstacleCenterY - playerCenterY, 2));
  if (distance <= (obstacleWidth/2 + playerWidth/2)) {
    return true;
  } else {
    return false;
  }
}

bool checkCollision2() {
  int playerCenterX = playerX + playerWidth/2;
  int playerCenterY = playerY + playerWidth/2;
  int obstacleCenterX = obstacle2X +  obstacleWidth/2;
  int obstacleCenterY = obstacle2Y +  obstacleWidth/2;
  int distance = sqrt(pow(obstacleCenterX - playerCenterX, 2) + pow(obstacleCenterY - playerCenterY, 2));
  if (distance <= (obstacleWidth/2 + playerWidth/2)) {
    return true;
  } else {
    return false;
  }
}
bool checkCollision3() {
  int playerCenterX = playerX + playerWidth/2;
  int playerCenterY = playerY + playerWidth/2;
  int obstacleCenterX = obstacle3X +  obstacleWidth/2;
  int obstacleCenterY = obstacle3Y +  obstacleWidth/2;
  int distance = sqrt(pow(obstacleCenterX - playerCenterX, 2) + pow(obstacleCenterY - playerCenterY, 2));
  if (distance <= (obstacleWidth/2 + playerWidth/2)) {
    return true;
  } else {
    return false;
  }
}
bool checkCollision4() {
  int playerCenterX = playerX + playerWidth/2;
  int playerCenterY = playerY + playerWidth/2;
  int obstacleCenterX = obstacle4X +  obstacleWidth/2;
  int obstacleCenterY = obstacle4Y +  obstacleWidth/2;
  int distance = sqrt(pow(obstacleCenterX - playerCenterX, 2) + pow(obstacleCenterY - playerCenterY, 2));
  if (distance <= (obstacleWidth/2 + playerWidth/2)) {
    return true;
  } else {
    return false;
  }
}

void gamescreen(){

  //Draw the Border for Screen

  tft.drawLine(1, 0, 1, 470, WHITE);

  tft.drawLine(300, 0, 300, 470, WHITE);

  tft.drawLine(1, 470, 300, 470, WHITE);

  tft.drawLine(60, 0, 60, 470, WHITE);

  tft.drawLine(120, 0, 120, 470, WHITE);
  tft.drawLine(180, 0, 180, 470, WHITE);
  tft.drawLine(240, 0, 240, 470, WHITE);

  //Enter Default Texts
  tft.setRotation(1);
  tft.setTextSize(2);

  tft.setTextColor(WHITE);

  tft.setCursor(2,2);

  tft.println("Speed:");

  tft.setCursor(82,2);

  tft.println(game_speed);

  tft.setCursor(150,2);

  tft.println("Score:");

  tft.setCursor(230,2);

  tft.println(score);
  tft.setRotation(0);
}
void beginning_screen(){
  tft.setRotation(1);
  tft.setTextSize(6);

  tft.setTextColor(WHITE);

  tft.setCursor(160,100);

  tft.println("BEKM");
  tft.setCursor(100,200);

  tft.println("PRESENTS");
  delay(2000);
  tft.fillScreen(BLACK);
  tft.setTextSize(50);

  tft.setTextColor(TFT_RED);
  tft.setCursor(140,150);

  tft.println("DODGE");

  delay(2000);
  tft.fillScreen(BLACK);
  tft.setTextSize(6);

  tft.setTextColor(WHITE);
  tft.setCursor(50,80);

  tft.println("Game starts");
  tft.setCursor(160,140);

  tft.println("in");
  delay(1000);
  tft.fillScreen(BLACK);
  tft.setTextSize(20);

  tft.setTextColor(WHITE);
  tft.setCursor(240,140);

  tft.println("3");
  delay(1000);
  tft.fillScreen(BLACK);
  tft.setTextSize(20);

  tft.setTextColor(WHITE);
  tft.setCursor(240,140);

  tft.println("2");
  delay(1000);
  tft.fillScreen(BLACK);
  tft.setTextSize(20);

  tft.setTextColor(WHITE);
  tft.setCursor(240,140);

  tft.println("1");
  delay(1000);
  }
void displayScore() {
  tft.setRotation(1);
  tft.fillRect(230, 2, 50, 20, TFT_BLACK); // Clear previous score
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.setCursor(230,2);
  tft.println(score);
}

void speed(){
  if (score < 5){
    move = 15;
  }
  else if (score>4 && score <10){
    move = 20;
    
  }
  else if (score>9 && score <15) {
    move = 25;
    
  }
  else if (score > 14 && score < 20){
    move = 30;
    
  }
  else if (score > 19 && score < 25){
    move = 30;
  }
  else if (score > 24 && score < 30){
    move = 35;
  }
  else if (score > 29 && score < 35){
    move = 40;
  }
  else if (score > 34 && score < 40){
    move = 50;
  }
  else if (score > 39 && score < 50){
    move = 60;
  }
  else if (score > 49){
    move = 70;
  }

}
void displaySpeed() {
  if (score % 5 == 0 && score != 0){
    game_speed++;
  
  }

  tft.fillRect(82, 2, 50, 20, TFT_BLACK); // Clear previous score
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.setCursor(82,2);

  tft.println(game_speed);
}

void playagain(){
  tft.fillScreen(BLACK);
  tft.setRotation(1);
  tft.setTextSize(5);
  tft.setTextColor(WHITE);
  tft.setCursor(40,50);
  tft.println("Congrats you");
  tft.setCursor(90,100);
  tft.println("died!! :)");
  tft.setCursor(20,150);
  tft.setTextColor(WHITE);
  tft.println("Press button to");
  tft.setCursor(60,200);
  tft.println("play again");
  tft.setTextSize(3);
  tft.setTextColor(TFT_BLUE);
  tft.setCursor(130,260);
  tft.println("Score:");
  tft.setCursor(240,260);
  tft.println(score);


}

void checkplayagain(){
  if (digitalRead(7) == 1){
    tft.fillScreen(BLACK);
    obstacleX = 30;
    obstacleY = 50;
    obstacle2X = 270;
    obstacle2Y = 50;
    obstacle3X = 90;
    obstacle3Y = 50;
    obstacle4X = 210;
    obstacle4Y = 50;
    playerX = 165;
    playerY = 430;
    score = 0;
    game_speed = 0;
    gameover = false;
    
    //tft.fillScreen(BLACK);
  }
}

