#include "render.h"
#include "game.h"
#include <stdint.h>
#include <stdio.h>
#include <shader.h>
#include <glmath.h>
#include <glad/gl.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>



#define RGB(r,g,b) r/255.0, g/255.0, b/255.0
#define WHITE  (vec3){RGB(255, 255, 255)}
#define PINK (vec3){RGB(253, 185, 200)}
#define PURPLE (vec3){RGB(128,0,128)}
#define GREEN (vec3){RGB(0,255,0)};

float vertices[] = {
    //play button pos     play button texture
    -0.5f, 0.5f, 0.0f,    0.0f, 1.0f,
    -0.5, -0.5f, 0.0f,    0.0f, 0.0f,
    0.5f, 0.5f, 0.0f,     1.0f, 1.0f,
    0.5f, -0.5f, 0.0f,     1.0f, 0.0f
};

unsigned int button_indices[] = {
    //play button
    0,1,2, //first triangle
    2,1,3, //second triangle
};



//implement this
uint32_t load_texture(const char *path){
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the texture
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (data){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else{
        printf("Failed to load texture\n");
        return 0;
    }
    stbi_image_free(data); 
    return texture;
}


uint32_t render_init(){
    uint32_t shader = create_shader("shaders/vertex.c", "shaders/fragment.c");
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

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return shader;
}

void draw_main_screen(uint32_t shader, uint32_t button, uint32_t title){
    use_shader(shader);
    //enable our title text
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, title);

    //move the title to the top of the screen
    mat4 title_model = create_transform_mat4(GLH_SCALE, (vec4){1.5f, 0.25f, 0.0f});
    mat4 projection = ortho(0.0, 800.0, 0.0, 800.0, 0.1, 0.2);
    translate_mat4(&title_model, (vec3){0.0f, 0.75f, 0.0f});
    set_mat4("model", title_model, shader);
    set_vec3("color", PINK, shader);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
    glBindTexture(GL_TEXTURE_2D, button);

    //translates play button to the bottom and scales it
    mat4 button_model = create_transform_mat4(GLH_SCALE, (vec4){0.65f, 0.25f, 0.0f});
    translate_mat4(&button_model, (vec3){0.0f, -0.5f, 0.0f});
    set_mat4("model", button_model, shader);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
    free_mat4(title_model);
    free_mat4(button_model);

    glBindTexture(GL_TEXTURE_2D, 0);
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
    unsigned int x_texture = load_texture("res/images/x.png");
    unsigned int o_texture = load_texture("res/images/o.png");

    mat4 model;

    vec4 black = {0,0,0,0};
    vec4 white = {1,1,1,1};

    //draws the game squares
    for(int i =0; i < 9; i++){
        glBindTexture(GL_TEXTURE_2D, 0);
        model = create_transform_mat4(GLH_SCALE, (vec4){scale_factor, scale_factor, 0.0f});
        translate_mat4(&model, translate[i]);


        set_mat4("model", model, shader);
        set_vec3("color", (vec3){RGB(0, 0, 0)}, shader);

        //draws either an x or o if there is one there
        if(board[i] == SYMBOL_X){
            glBindTexture(GL_TEXTURE_2D, x_texture);
        }
        else if(board[i] == SYMBOL_O){
            glBindTexture(GL_TEXTURE_2D, o_texture);
        }else{
            set_vec3("color", (vec3){RGB(0, 0, 100)}, shader);
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

    const char* textures[] = {"res/images/player.png", "res/images/bot.png", "res/images/draw.png"};
    unsigned int texture = load_texture(textures[winner]);
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



void display_end_buttons(uint32_t shader){
    unsigned int play_again = load_texture("res/images/play_again.png");
    unsigned int quit = load_texture("res/images/quit.png");

    //draws the quit game button
    mat4 model = create_transform_mat4(GLH_SCALE, (vec4){0.45f, 0.15f, 0.0f});
    translate_mat4(&model, (vec3){-0.4f, -0.85f, 0.0f});

    set_vec3("color", WHITE, shader);
    set_mat4("model", model, shader);
    glBindTexture(GL_TEXTURE_2D, quit);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
    free_mat4(model);


    //draw the play again button
    model = create_transform_mat4(GLH_SCALE, (vec4){0.45f, 0.15f, 0.0f});
    translate_mat4(&model, (vec3){0.4f, -0.85f, 0.0f});

    set_mat4("model", model, shader);
    glBindTexture(GL_TEXTURE_2D, play_again);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
    free_mat4(model);

    glBindTexture(GL_TEXTURE_2D, 0);
    glDeleteTextures(1, &quit);
    glDeleteTextures(1, &play_again);

}
