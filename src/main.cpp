#include "main.h"
#include "timer.h"
#include "boat.h"
#include "sea.h"
#include "rock.h"
#include "cannonball.h"
#include "monster.h"
#include "barrel.h"
#include "gift.h"
#include "boss.h"
#include "spike.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Boat boat;
Sea sea;
Rock rocks[4];
Barrel barrels[4];
Gift gifts[4];
Cannonball ball;
Monster m[2];
Gift drops[2];
Boss ganon;
Spike attack;
Spike boundary[108];

int in_the_air = 0;
int view_flag = 0;
int hp = 100;
int boss_hp = 8000;
int invincibility = 0;
int pow_count = 0;
int temp = 4;
int no_dead = 0;
int boss_made = 0;
int boss_attack_count = 0;
int boss_attack_started = 0;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_anglexz = -90.0f;
float camera_rotation_angley = 30.0f;
float camera_magnitude = 3.0f;
double xpos, ypos;
double old_xpos, old_ypos;

glm::vec3 wind(0, 0, 0);

enum views{BOAT_V, TOP_V, TOWER_V, FOLL_V, HELI_V};
enum views view = TOWER_V;

Timer t60(1.0 / 60);

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    if (yoffset > 0) {
        camera_magnitude -= 0.5;
    }
    else if (yoffset < 0) {
        camera_magnitude += 0.5;
    }
    if (camera_magnitude > 5) {
        camera_magnitude = 5;
    }
    if (camera_magnitude < 2.5) {
        camera_magnitude = 2.5;
    }
}

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    //glm::vec3 eye( 3*cos(camera_rotation_anglexz*M_PI/180.0f) - boat.speed*cos(boat.rotation * M_PI / 180.0f), 3*sin(camera_rotation_angley*M_PI/180.0f), 3*sin(camera_rotation_anglexz*M_PI/180.0f) - boat.speed*cos(boat.rotation * M_PI / 180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    //glm::vec3 target(boat.position.x, boat.position.y, boat.position.z);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    //glm::vec3 up (0, 1, 0);

    glm::vec3 eye(10, 10, 0);
    glm::vec3 target(0, 0, 0);
    glm::vec3 up (0, 1, 0);

    if (view == BOAT_V) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        eye = boat.position + glm::vec3(0, 1.5f, 0) + 1.5f * boat.front;
        target = eye + 10.0f*boat.front - glm::vec3(0, 9*boat.front.y, 0);
    }

    else if (view == TOP_V) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        eye = boat.position + glm::vec3(0, 10, 0);
        target = boat.position;
        up = boat.front;
    }

    else if (view == TOWER_V) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        eye = glm::vec3( 10, 10, 0 );
        target = glm::vec3(0, 0, 0);
    }

    else if (view == FOLL_V) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        eye = boat.position + glm::vec3(-3*boat.front.x, 3*sin(30.0f*M_PI/180.0f), -3*boat.front.z);
        target = boat.position;
    }

    else if (view == HELI_V) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        eye = boat.position + glm::vec3(camera_magnitude*cos(camera_rotation_anglexz*M_PI/180.0f), camera_magnitude*sin(camera_rotation_angley*M_PI/180.0f), camera_magnitude*sin(camera_rotation_anglexz*M_PI/180.0f));
        target = boat.position;
    }


    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    if ((invincibility/10)%2 == 0) {
        boat.draw(VP);
    }

    sea.draw(VP);

    for (int i=0 ; i<4 ; i++) {
        rocks[i].draw(VP);
        barrels[i].draw(VP);
        gifts[i].draw(VP);
    }

    attack.draw(VP);

    if (in_the_air) {
        ball.draw(VP);
    }

    for (int i=0 ; i<2 ; i++) {
        m[i].draw(VP);
        drops[i].draw(VP);
    }

    ganon.draw(VP);
}

void tick_input(GLFWwindow *window) {
    int a  = glfwGetKey(window, GLFW_KEY_LEFT);
    int d  = glfwGetKey(window, GLFW_KEY_RIGHT);
    int w = glfwGetKey(window, GLFW_KEY_UP);
    int s = glfwGetKey(window, GLFW_KEY_DOWN);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    int f = glfwGetKey(window, GLFW_KEY_F);

    int o = glfwGetKey(window, GLFW_KEY_O);
    int p = glfwGetKey(window, GLFW_KEY_P);

    int bv = glfwGetKey(window, GLFW_KEY_1);
    int tv = glfwGetKey(window, GLFW_KEY_2);
    int tov = glfwGetKey(window, GLFW_KEY_3);
    int fv = glfwGetKey(window, GLFW_KEY_4);
    int hv = glfwGetKey(window, GLFW_KEY_5);

    if (w) {
        boat.speed = -0.2;
    }
    if (a) {
        boat.rotation += 2;
    }
    if (s) {
        boat.speed = 0.2;
    }
    if (d) {
        boat.rotation -= 2;
    }
    if (space) {
        if (boat.position.y == 0) {
            boat.speedy = 0.3;
        }
    }
    if (f) {
        if (!in_the_air) {
            glm::vec3 vec = boat.position + glm::vec3(0, 1.5f, 0) + 2.5f * boat.front;
            if (pow_count > 0) {
                ball = Cannonball(vec.x, vec.y, vec.z, COLOR_YELLOW, -1.5f * boat.front.x, -1.5f * boat.front.z, 0);
            }
            else {
                ball = Cannonball(vec.x, vec.y, vec.z, COLOR_ORANGE, -0.2f * boat.front.x, -0.2f * boat.front.z, 0.2);
            }
            in_the_air = 1;
        }
    }

    if (o) {
        view_flag = 1;
        reset_screen();
    }
    if (p) {
        view_flag = 0;
        reset_screen();
    }

    if (bv) {
        view = BOAT_V;
    }
    if (tv) {
        view = TOP_V;
    }
    if (tov) {
        view = TOWER_V;
    }
    if (fv) {
        view = FOLL_V;
    }
    if (hv) {
        camera_magnitude = 3;
        view = HELI_V;
    }
}

void tick_elements() {
    if (hp <= 0) {
        boat = boat = Boat(0, 0, 0, COLOR_RED);
        boat.speedx = wind.x;
        boat.speedz = wind.z;
        hp = 100;
    }
    stringstream convert;
    convert << hp;
    string str = "Boat life = " + convert.str();

    if (no_dead >= 2) {
        if (!boss_made) {
            ganon = Boss(-15, 0, 0, COLOR_BOSS);
            boss_made = 1;
        }

        if (boss_hp <= 0) {
            ganon = Boss(1000, -60, 1000, COLOR_BOSS);
            string str2 = str + "    Boss defeated";
            glfwSetWindowTitle(window, str2.c_str());
        }
        else {
            stringstream convert1;
            convert1 << boss_hp;
            string str1 = str + "    Boss life = " + convert1.str();
            glfwSetWindowTitle(window, str1.c_str());
        }

        ganon.tick();
        glm::vec3 follow = boat.position - ganon.position;
        follow.y = 0;

        if (boss_attack_count <= 600 && !boss_attack_started) {
            ganon = Boss(ganon.position.x, ganon.position.y, ganon.position.z, COLOR_BOSS);
            ganon.speedx = -0.01f * follow.x;
            ganon.speedz = -0.01f * follow.z;
            boss_attack_count++;
            if (boss_attack_count == 600) {
                boss_attack_started = 1;
                boss_attack_count = 120;
            }
        }
        else if (boss_attack_count <= 120 && boss_attack_started) {
            ganon = Boss(ganon.position.x, ganon.position.y, ganon.position.z, COLOR_AOE);
            ganon.speedx = -0.01f * follow.x;
            ganon.speedz = -0.01f * follow.z;
            if (abs(ganon.position.x - boat.position.x) < ganon.range.x && abs(ganon.position.z - boat.position.z) < ganon.range.z) {
                if (boss_attack_count >= 60 && boss_attack_count < 61) {
                    attack.set_position(boat.position.x, 0, boat.position.z);
                }
                else if (boss_attack_count == 1) {
                    attack.set_position(-1000, 0, 1000);
                }
            }
            boss_attack_count--;
            if (boss_attack_count == 0) {
                boss_attack_started = 0;
            }
        }

        follow = (1/sqrt(pow(follow.x, 2) + pow(follow.y, 2) + pow(follow.z, 2))) * follow;
        double angle = acos(dot(follow, ganon.front)) * 180.0f / M_PI;
        if (follow.x >= 0) {
            ganon.rotation += angle;
        }
        else {
            ganon.rotation -= angle;
        }

        if (detect_collision(boat.bounding_box(), ganon.bounding_box())) {
            boat.speed = 0;
            glm::vec3 pos = boat.position + 0.25f * (boat.position - ganon.position);
            boat.set_position(pos.x, pos.y, pos.z);
            if (pow_count <= 0) {
                if (invincibility <= 0) {
                    hp -= 4;
                    invincibility = 120;
                }
            }
        }

        if (detect_collision(ball.bounding_box(), ganon.bounding_box())) {
            in_the_air = 0;
            ball.set_position(1000, 0, 1000);
            if (pow_count > 0) {
                boss_hp -= 20;
            }
            else {
                boss_hp -= 10;
            }
        }
    }
    else {
        glfwSetWindowTitle(window, str.c_str());
    }
    reset_screen();

    boat.tick();
    if (boat.position.y < 0) {
        boat.set_position(boat.position.x, 0, boat.position.z);
    }
    for (int i=0 ; i<4 ; i++) {
        if (detect_collision(boat.bounding_box(), rocks[i].bounding_box()) && boat.position.y <= rocks[i].position.y) {
            boat.speed = 0;
            glm::vec3 pos = boat.position + 0.25f * (boat.position - rocks[i].position);
            boat.set_position(pos.x, pos.y, pos.z);
            if (pow_count <= 0) {
                if (invincibility <= 0) {
                    hp--;
                    invincibility = 120;
                }
            }
        }
        barrels[i].tick();
        gifts[i].tick();
        if (pow_count > 0 && temp < 4) {
            gifts[temp].set_position(boat.position.x, boat.position.y + 3, boat.position.z);
            pow_count--;
        }
        else if (pow_count <= 0 && temp < 4) {
            gifts[temp].set_position(1000, -40, 1000);
            temp = 4;
        }
        if (detect_collision(boat.bounding_box(), barrels[i].bounding_box())) {
            if (boat.position.y > gifts[i].position.y) {
                //hp += 10;
                if (pow_count <= 0) {
                    barrels[i].set_position(1000, -40, 1000);
                    gifts[i].set_position(boat.position.x, boat.position.y + 3, boat.position.z);
                    temp = i;
                    pow_count = 3600;
                }
            }
            else {
                boat.speed = 0;
                glm::vec3 pos = boat.position + 0.25f * (boat.position - barrels[i].position);
                boat.set_position(pos.x, pos.y, pos.z);
            }
        }
    }

    if (detect_collision(boat.bounding_box(), attack.bounding_box()) && boat.position.y <= attack.position.y + attack.h-0.5f) {
        boat.speed = 0;
        glm::vec3 pos = boat.position + 0.25f * (boat.position - attack.position);
        boat.set_position(pos.x, pos.y, pos.z);
        if (pow_count <= 0) {
            if (invincibility <= 0) {
                hp -= 10;
                invincibility = 120;
            }
        }
    }

    ball.tick();
    //cout << ball.position.y << "\n";
    if (ball.position.y < 0) {
        in_the_air = 0;
        ball.set_position(1000, 0, 1000);
    }

    for (int i=0 ; i<2 ; i++) {
        m[i].tick();
        drops[i].tick();
        if (detect_collision(boat.bounding_box(), m[i].bounding_box()) && boat.position.y <= m[i].position.y) {
            boat.speed = 0;
            glm::vec3 pos = boat.position + 0.25f * (boat.position - m[i].position);
            boat.set_position(pos.x, pos.y, pos.z);
            if (pow_count <= 0) {
                if (invincibility <= 0) {
                    hp -= 2;
                    invincibility = 120;
                }
            }
        }
        if (detect_collision(boat.bounding_box(), drops[i].bounding_box())) {
            hp += 100;
            drops[i].set_position(1000, -40, 1000);
            no_dead++;
        }
        if (detect_collision(ball.bounding_box(), m[i].bounding_box()) && abs(ball.position.y - m[i].position.y) <= 0.75) {
            in_the_air = 0;
            drops[i].set_position(m[i].position.x, 0.25, m[i].position.z);
            m[i].set_position(1000, -60, 1000);
        }
        for (int j=0 ; j<4 ; j++) {
            if (detect_collision(m[i].bounding_box(), rocks[j].bounding_box())) {
                glm::vec3 pos = m[i].position + 0.25f * (m[i].position - rocks[j].position);
                m[i].set_position(pos.x, pos.y, pos.z);
            }
            if (detect_collision(m[i].bounding_box(), barrels[j].bounding_box())) {
                glm::vec3 pos = m[i].position + 0.25f * (m[i].position - barrels[j].position);
                m[i].set_position(pos.x, pos.y, pos.z);
            }
        }
        for (int j=i+1 ; j<2 ; j++) {
            if (detect_collision(m[i].bounding_box(), m[j].bounding_box())) {
                glm::vec3 pos1 = m[i].position + 0.25f * (m[i].position - m[j].position);
                m[i].set_position(pos1.x, pos1.y, pos1.z);
                glm::vec3 pos2 = m[j].position + 0.25f * (m[j].position - m[i].position);
                m[j].set_position(pos2.x, pos2.y, pos2.z);
            }
        }

        if (abs(m[i].position.x - boat.position.x) < m[i].range.x && abs(m[i].position.z - boat.position.z) < m[i].range.z) {
            glm::vec3 follow = boat.position - m[i].position;
            follow.y = 0;
            follow = (1/sqrt(pow(follow.x, 2) + pow(follow.y, 2) + pow(follow.z, 2))) * follow;
            m[i].speedx = -0.03f * follow.x;
            m[i].speedz = -0.03f * follow.z;
            double angle = acos(dot(follow, m[i].front)) * 180.0f / M_PI;
            if (angle >= 90) {
                m[i].rotation += 0.6f*angle;
            }
            else if (angle >= 60) {
                m[i].rotation += 0.45f*angle;
            }
            else if (angle >= 30) {
                m[i].rotation += 0.33f*angle;
            }
            else if (angle >= 10) {
                m[i].rotation += 0.2f*angle;
            }
            else if (angle >= 0) {
                m[i].rotation += 0.015f*angle;
            }
        }
        else {
            m[i].speedx = 0;
            m[i].speedz = 0;
        }
    }

    if (invincibility > 0) {
        invincibility--;
    }

    glfwGetCursorPos(window, &xpos, &ypos);
    if (xpos - old_xpos > 0) {
        camera_rotation_anglexz -= 2;
    }
    else if (xpos - old_xpos < 0) {
        camera_rotation_anglexz += 2;
    }
    if (ypos - old_ypos > 0) {
        camera_rotation_angley += 2;
    }
    else if (ypos - old_ypos < 0) {
        camera_rotation_angley -= 2;
    }
    old_xpos = xpos;
    old_ypos = ypos;

    if (view == HELI_V) {
        glfwSetScrollCallback(window, scroll_callback);
    }
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    boat = Boat(0, 0, 0, COLOR_RED);
    boat.speedx = wind.x;
    boat.speedz = wind.z;

    sea = Sea(COLOR_OCEAN_BLUE);

    rocks[0] = Rock(9, 0, 9, 1, COLOR_ROCK);
    rocks[1] = Rock(-9, 0, 9, 1, COLOR_ROCK);
    rocks[2] = Rock(9, 0, -9, 1, COLOR_ROCK);
    rocks[3] = Rock(-9, 0, -9, 1, COLOR_ROCK);

    barrels[0] = Barrel(6, -0.5, 0, COLOR_BARREL);
    barrels[1] = Barrel(-6, -0.5, 0, COLOR_BARREL);
    barrels[2] = Barrel(0, -0.5, 6, COLOR_BARREL);
    barrels[3] = Barrel(0, -0.5, -6, COLOR_BARREL);

    gifts[0] = Gift(6, 0.25, 0, COLOR_YELLOW);
    gifts[1] = Gift(-6, 0.25, 0, COLOR_YELLOW);
    gifts[2] = Gift(0, 0.25, 6, COLOR_YELLOW);
    gifts[3] = Gift(0, 0.25, -6, COLOR_YELLOW);

    m[0] = Monster(11, 0, 11, COLOR_PURPLE);
    m[1] = Monster(-11, 0, -11, COLOR_PURPLE);
    drops[0] = Gift(1000, 0.25, 1000, COLOR_HEALTH);
    drops[1] = Gift(1000, 0.25, 1000, COLOR_HEALTH);
    ball = Cannonball(1000, 0, 1000, COLOR_ORANGE, 0, 0, 0);

    ganon = Boss(1000, 0, 1000, COLOR_BOSS);
    attack = Spike(-1000, 0, -1000, COLOR_YELLOW, 3.5f);

    glfwGetCursorPos(window, &xpos, &ypos);
    old_xpos = xpos;
    old_ypos = ypos;

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 1920;
    int height = 1000;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    float top    = screen_center_y + 18 / screen_zoom;
    float bottom = screen_center_y - 18 / screen_zoom;
    float left   = screen_center_x - 32 / screen_zoom;
    float right  = screen_center_x + 32 / screen_zoom;
    if (view_flag) {
        Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
    }
    else {
        Matrices.projection = glm::perspective(90.0f, 16.0f/9, 0.1f, 500.0f);
    }
}
