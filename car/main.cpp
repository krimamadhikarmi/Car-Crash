#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include<string>

using namespace std;
using namespace sf;

//initiallize game const
const double screenWidth = 1200;
const double screenHeight = 929;
const double racerHeight=160;
const double borderLeft=200;
const double borderRight=930;
double gamespeed=0.4;
int score=0;
string scorestring="";

RenderWindow window(VideoMode(screenWidth,screenHeight),"Car Crash");
void gamePlay();
void startGame(){
    Texture menuTexture,instrcTexture;
    menuTexture.loadFromFile("image/racee.png");
    instrcTexture.loadFromFile("image/arrow.png");
    Sprite menu(menuTexture), instruction(instrcTexture);
    instruction.setPosition(800,750);

    while(window.isOpen()){
        Event event;
        while(window.pollEvent(event)){
            if(event.type==Event::Closed){
                window.close();
            }
            if (Keyboard::isKeyPressed(Keyboard::Enter)){
                gamePlay();
            }
            if(Keyboard::isKeyPressed(Keyboard::Escape)){
                window.close();
            }
        }
        window.clear();
        window.draw(menu);
        window.draw(instruction);
        window.display();
    }

}

//random number for x cordinate generate
int getRandomNum(int min,int max){
    int num = (rand() % (max - min + 1)) + min;
    return num;
}

void gameOver(){
    SoundBuffer soundBuffer;
    soundBuffer.loadFromFile("sound/crash.wav");

    Sound sound(soundBuffer);
    sound.play();
    Font font;
    font.loadFromFile("font/xirod.ttf");
    scorestring="SCORE-"+ to_string(score);
    Text text(scorestring,font,50);
    text.setPosition(400,700);

    Texture deadtex,overTex;
    deadtex.loadFromFile("image/death.png");
    overTex.loadFromFile("image/game over.jpg");
    Sprite dead(deadtex), over(overTex);

    over.setPosition(400,100);

    while(window.isOpen()){
        Event event;
        while(window.pollEvent(event)){
            if(event.type==Event::Closed){
                window.close();
            }
        }
        window.clear();
        window.draw(over);
        window.draw(dead);
        window.draw(text);
        window.display();
        if (Keyboard::isKeyPressed(Keyboard::BackSpace))
            {
                score=0;
                gamespeed=0.4;
                startGame();
            }
    }
}

void gamePlay(){
    //score text font
    Font font;
    font.loadFromFile("font/xirod.ttf");

    //sound
    SoundBuffer soundBuffer;
    soundBuffer.loadFromFile("sound/alonee.wav");
    Sound sound(soundBuffer);
    sound.play();
    sound.setLoop(true);

    Texture backgroundtex, obs1tex,obs2tex,obs3tex,obs4tex,racertex;

    //load images
    backgroundtex.loadFromFile("image/background1.png");
    obs1tex.loadFromFile("image/bikee.png");
    obs2tex.loadFromFile("image/truck 2.png");
    obs3tex.loadFromFile("image/bus.png");
    obs4tex.loadFromFile("image/carr.png");
    racertex.loadFromFile("image/race.png");

    Sprite background(backgroundtex),background2(backgroundtex),obs1(obs1tex),obs2(obs2tex),obs3(obs3tex),obs4(obs4tex),racer(racertex);

    //position
    double racerX=screenWidth/2;
    double racerY=screenHeight-racerHeight;
    double backgroundY=0;
    double background2Y=-929;
    double obs1X=getRandomNum(borderLeft,borderRight), obs1Y=0;
    double obs2X=getRandomNum(borderLeft,borderRight), obs2Y=-200;
    double obs3X=getRandomNum(borderLeft,borderRight), obs3Y=-400;
    double obs4X=getRandomNum(borderLeft,borderRight), obs4Y=-600;

    while(window.isOpen()){
        racer.setPosition(racerX,racerY);

        //obstacles move and position
        obs1.setPosition(obs1X,obs1Y);
        obs2.setPosition(obs2X,obs2Y);
        obs3.setPosition(obs3X,obs3Y);
        obs4.setPosition(obs4X,obs4Y);

        if(obs1Y>screenHeight){obs1X=getRandomNum(borderLeft,borderRight);obs1Y=-40; score++;}
        else{obs1Y+=gamespeed;}

        if(obs2Y>screenHeight){obs2X=getRandomNum(borderLeft,borderRight);obs2Y=-40; score++;}
        else{obs2Y+=gamespeed;}

        if(obs3Y>screenHeight){obs3X=getRandomNum(borderLeft,borderRight);obs3Y=-40;score++;}
        else{obs3Y+=gamespeed;}

        if(obs4Y>screenHeight){obs4X=getRandomNum(borderLeft,borderRight);obs4Y=-40;score++;}
        else{obs4Y+=gamespeed;}

        //game level
        if(score>10 && score<20){gamespeed=0.6;}
        if(score>20&& score<30){gamespeed=0.8;}
        if(score>30 && score<40){gamespeed=0.9;}
        if (score>40 && score<50){gamespeed=1.0;}
        if(score>50){gamespeed=1.1;}

        //racer move
        if(Keyboard::isKeyPressed(Keyboard::Up)){
                if(racerY>0)
            racerY-=0.5;
        }
        if(Keyboard::isKeyPressed(Keyboard::Down)){
            if(racerY<screenHeight-racerHeight)
            racerY+=0.5;
        }
        if(Keyboard::isKeyPressed(Keyboard::Left)){
                if(racerX>borderLeft)
            racerX-=0.6;
        }
        if(Keyboard::isKeyPressed(Keyboard::Right)){
            if(racerX<borderRight)
            racerX+=0.6;
        }

        //background move
        background.setPosition(0,backgroundY);
        background2.setPosition(0,background2Y);
        if(background2Y>0){
            backgroundY=0;
            background2Y=backgroundY-929;
        }
        backgroundY+=0.3;
        background2Y+=0.3;

        Event event;
        while(window.pollEvent(event)){
            if(event.type==Event::Closed){
                window.close();
            }
        }

        //Accident
        if(racer.getGlobalBounds().intersects(obs1.getGlobalBounds())){sound.stop(); gameOver();}
        if(racer.getGlobalBounds().intersects(obs2.getGlobalBounds())){sound.stop(); gameOver();}
        if(racer.getGlobalBounds().intersects(obs3.getGlobalBounds())){sound.stop(); gameOver();}
        if(racer.getGlobalBounds().intersects(obs4.getGlobalBounds())){sound.stop(); gameOver();}

        //score
        scorestring="Score-"+to_string(score);
         Text text(scorestring,font,30);

        window.clear();
        window.draw(background);
        window.draw(background2);
        window.draw(obs1);
        window.draw(obs2);
        window.draw(obs3);
        window.draw(obs4);
        window.draw(racer);
        window.draw(text);
        window.display();
    }
}

int main(){
    startGame();
}
