//
// breakout.c
//
// Computer Science 50
// Problem Set 4
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

//height and width of game paddle
#define HEIGHTPADDLE 15
#define WIDTHPADDLE 70

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));
    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);
    
    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);
    //We need to add the ball to the screen ! 
    add(window, ball);
    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);
    //We need to add the paddle to the screen !
    add(window, paddle);
    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);
    //We need to add the score to the screen !
    add(window, label);
    
    // number of bricks initially
    //int bricks = COLS * ROWS;
    int bricks = 100;
    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    //Initialize velocity
    double velocityX = drand48()*5;
    double velocityY = drand48()*5;
    //Velocity can't be too slow or too fast
    while(velocityX <= 4.0 || velocityX >= 9){
        velocityX = drand48()*5;
    }
    while(velocityY <= 4.0 || velocityY >= 9){
        velocityY = drand48()*5;
    }
   
    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        // TODO
        // Keep drawing the paddle at the new mouse position along the x-axis
        GEvent mouseMoved = getNextEvent(MOUSE_EVENT);
        if(mouseMoved != NULL){
            double mouseX = getX(mouseMoved) - getWidth(paddle)/2;
            //if paddle is going over screen
            if(mouseX < 5){
                mouseX = 0;
            }
            else if(mouseX > WIDTH-WIDTHPADDLE){
                mouseX = WIDTH-WIDTHPADDLE;
            }
            setLocation(paddle, mouseX, HEIGHT-50);
        }
        
        //Making the ball bounce
        //velocity is in the header
        //Vertical bounce
        move(ball, velocityX, velocityY);
        if(getY(ball) + getWidth(ball) >= HEIGHT){
            //velocityY = -velocityY;
            //Loose a life
            lives--;
            setLocation(ball, WIDTH/2-12,HEIGHT/2);
            if(lives > 0){
                waitForClick();
            }
            
        }
        else if(getY(ball) <= 0){
            velocityY = -velocityY;
        }
        //Horizontal bounce
        if(getX(ball) + getWidth(ball) >= WIDTH){
            velocityX = -velocityX;
        }
        else if(getX(ball) <= 0){
            velocityX = -velocityX;
        }
        pause(10);
        //Detect collisions
        GObject collision = detectCollision(window, ball);
        //if ball collide paddle
        if(collision == paddle){
            velocityY = -velocityY;
        }
        //if ball collide rect (else if because bug with paddle)
        else if(strcmp(getType(collision), "GRect")==0){
            velocityY = -velocityY;
            points++;
            bricks--;
            removeGWindow(window, collision);
        }
    updateScoreboard(window, label, points);
    }
    if(lives == 0){
        //Show Game over
        setLabel(label, "GAME OVER");
        // center label in window
        double x = (getWidth(window) - getWidth(label)) / 2;
        double y = (getHeight(window) - getHeight(label)) / 2;
        setLocation(label, x, y);
    }
    if(bricks == 0){
        setLabel(label, "Yeeeah ! :-) ");
        // center label in window
        double x = (getWidth(window) - getWidth(label)) / 2;
        double y = (getHeight(window) - getHeight(label)) / 2;
        setLocation(label, x, y);
    }
    
    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    // TODO
    for(int i = 5; i < ROWS*80; i+=40){
        for(int j = 5; j < COLS*20; j+=20){
            GRect rect = newGRect(i, j, 30, 10);
            setFilled(rect, true);
            // Make the color change every column
            if(j <= 5){
            setColor(rect, "CYAN");
            }
            else if(j >= 25 && j <= 44){
            setColor(rect, "YELLOW");
            }
            else if(j >= 45 && j<= 64){
            setColor(rect, "RED");
            }
            else if(j >= 65 && j<= 84){
            setColor(rect, "GREEN");
            }
            else if(j >= 85 && j<= 104){
            setColor(rect, "DARK_GRAY");
            }
            else if(j >= 105 && j<= 124){
            setColor(rect, "PINK");
            }
            else if(j >= 125 && j<= 144){
            setColor(rect, "ORANGE");
            }
            else if(j >= 145 && j<= 164){
            setColor(rect, "LIGHT_GRAY");
            }
            else if(j >= 165 && j <= 184){
            setColor(rect, "GRAY");
            }
            add(window, rect);
        }
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    // TODO
    double x = (WIDTH - 45) / 2;
    double y = (HEIGHT - 45) / 2;
    GOval circle = newGOval(x,y, 25, 25);
    setFilled(circle, true);
    setColor(circle, "BLACK");
    return circle;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    //TODO
    GRect initPaddle = newGRect(WIDTH/2.4,HEIGHT-50, WIDTHPADDLE, HEIGHTPADDLE);
    setFilled(initPaddle,true);
    setColor(initPaddle,"ORANGE");
    
    // initially return NULL
    return initPaddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    // TODO
    GLabel score = newGLabel("hello");
    setFont(score, "SansSerif-24");
    setColor(score, "GRAY");
    setLocation(score, (WIDTH-getWidth(score))/2, (HEIGHT + getFontAscent(score))/2);
    return score;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
