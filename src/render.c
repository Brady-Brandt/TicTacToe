#include "render.h"
#include "game.h"
#include <stdint.h>
#include <stdio.h>
#include <shader.h>
#include <glmath.h>
#include <glad/gl.h>

#include "assets/x.h"
#include "assets/o.h"
#include "assets/player.h"
#include "assets/bot.h"
#include "assets/draw.h"



#define RGB(r,g,b) r/255.0, g/255.0, b/255.0
#define WHITE  (vec3){RGB(255, 255, 255)}
#define PURPLE (vec3){RGB(128,0,128)}
#define GREEN (vec3){RGB(0,255,0)};



const char* fragment= 
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "\n"
    "uniform vec3 color;\n"
    "in vec2 tex_coords;\n"
    "uniform sampler2D tex;\n"
    "uniform vec4 isTexture;\n"
    "\n"
    "void main(){\n"
    "  FragColor = max(texture(tex, tex_coords), isTexture) * vec4(color, 1.0);\n"
    "}\n";

const char* vertex= 
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec2 texCoords;\n"
    "\n"
    "uniform mat4 model;\n"
    "out vec2 tex_coords;\n"
    "\n"
    "void main(){\n"
    "  gl_Position = model * vec4(aPos,1.0);\n"
    "\n"
    "  tex_coords = vec2(texCoords);\n"
    "}\n";


float vertices[] = {
    //pos                 //texture
    -0.5f, 0.5f, 0.0f,    0.0f, 0.0f, //top left 
    -0.5, -0.5f, 0.0f,    0.0f, 1.0f, //bottom left
    0.5f, 0.5f, 0.0f,     1.0f, 0.0f, //top right
    0.5f, -0.5f, 0.0f,     1.0f, 1.0f //bottom right
};

unsigned int button_indices[] = {
    0,1,2, //first triangle
    2,1,3, //second triangle
};


//implement this
static uint32_t load_texture(const unsigned char* data, int width, int height, int channels){
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    if (data){
        if(channels == 3){
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

        } else{
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
    }
    else{
        printf("Failed to load texture\n");
        return 0;
    }
    return texture;
}


uint32_t render_init(){
    uint32_t shader = create_shader_from_string(vertex, fragment);
    unsigned int VAO, EBO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &VBO);


    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(button_indices), button_indices, GL_STATIC_DRAW);

    //triangle coords
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //texture coords
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    return shader;
}



//draws the tic toc toe board
void draw_game(uint32_t shader, Symbol board[9]){
    use_shader(shader);
    float scale_factor = 0.45f;
    //tic toc toe squares translation vertices
    vec3 translate[] = {
        //first row
        {-scale_factor, scale_factor, 0.0f},
        {0.0f, scale_factor, 0.0f},
        {scale_factor, scale_factor, 0.0f},

        //second row
        {-scale_factor, 0.0f, 0.0f},
        {0.0f, 0.0f, 0.0f},
        {scale_factor, 0.0f, 0.0f},

        //third row
        {-scale_factor, -scale_factor, 0.0f},
        {0.0f, -scale_factor, 0.0f},
        {scale_factor, -scale_factor, 0.0f}
    };

    //texture for x/o
    unsigned int x_texture = load_texture(x, X_WIDTH, X_HEIGHT, 3);
    unsigned int o_texture = load_texture(o, O_WIDTH, O_HEIGHT, 3);


    mat4 model;
    vec4 black = {0,0,0,0};
    vec4 white = {1,1,1,1};

    //draws the game squares
    for(int i =0; i < 9; i++){
        glBindTexture(GL_TEXTURE_2D, 0);
        model = create_transform_mat4(GLH_SCALE, (vec4){scale_factor, scale_factor, 0.0f});
        translate_mat4(&model, translate[i]);
        set_mat4("model", model, shader);
        set_vec3("color", (vec3){RGB(0, 0, (100 + i))}, shader);
        set_vec4("isTexture", white, shader);

        //draws either an x or o if there is one there
        if(board[i] == SYMBOL_X){
            glBindTexture(GL_TEXTURE_2D, x_texture);
            set_vec4("isTexture", black, shader);
        }
        else if(board[i] == SYMBOL_O){
            glBindTexture(GL_TEXTURE_2D, o_texture);
            set_vec4("isTexture", black, shader);
        }
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
        free_mat4(model);
    }

    
    glDeleteTextures(1, &x_texture);
    glDeleteTextures(1, &o_texture);

    //create the board grid lines
    set_vec3("color", PURPLE, shader);
    vec3 scale = Vec3(1.0f, 1.35f, 0.0f);
    mat4 id;


    //draws the vertical grid lines on the screen
    for(int i =0; i < 2; i++){
        id = create_transform_mat4(GLH_TRANSLATE, (vec4){0.28f + (i * 0.45f ), 0.0f});
        scale_mat4(&id, scale);

        set_mat4("model", id, shader);

        glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, NULL);
        free_mat4(id);
    }


    //draws the horizontal grid lines on the screen
    for(int i =0; i < 2; i++){
        id = create_transform_mat4(GLH_SCALE, (vec4){scale.x, scale.y, scale.z, 0});
        rotate_axis_mat4(&id, 180, (vec3){1.0f, 1.0f, 0.0f});
        translate_mat4(&id, (vec3){0.0, 0.27f + (i * 0.45f), 0.0f});
        set_mat4("model", id, shader);
        glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, NULL);
        free_mat4(id);
    }
}

void display_winner(uint32_t shader, int winner){
    vec4 black = {0,0,0,0};
    unsigned int texture = 0;
    switch(winner){
        case 0:
            texture = load_texture(player, PLAYER_WIDTH, PLAYER_HEIGHT, 4);
            break;
        case 1:
            texture = load_texture(bot, BOT_WIDTH, BOT_HEIGHT, 4);
            break;
        default:
            texture = load_texture(draw, DRAW_WIDTH, DRAW_HEIGHT, 4);
            break;
    }
    use_shader(shader);

    mat4 model = create_transform_mat4(GLH_SCALE, (vec4){0.35, 0.15});
    translate_mat4(&model, (vec3){0.0f, 0.8f, 0.0f});

    set_vec3("color", WHITE, shader);
    set_vec4("isTexture", black, shader);
    set_mat4("model", model, shader);
    glBindTexture(GL_TEXTURE_2D, texture);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
    free_mat4(model);
    glBindTexture(GL_TEXTURE_2D, 0);
}
