#include "gamegraphics.h"
#include <stdio.h>
#include <shader.h>
#include <glmath.h>
#include <glad/gl.h>



#define RGB(r,g,b) r/255.0, g/255.0, b/255.0
#define WHITE  (vec3){RGB(255, 255, 255)}
#define PINK (vec3){RGB(253, 185, 200)}
#define PURPLE (vec3){RGB(128,0,128)}
#define GREEN (vec3){RGB(0,255,0)};

//implement this
uint32_t load_texture(const char *path){
    return 0;
}



drawer set_up_drawer(int shader, unsigned int vao, int arr[]){
  drawer result;
  result.shader = shader;
  result.vao = vao;

  for(int i =0; i < 9; i++){
    result.gridColors[i] = arr[i];
  }

  return result;
}

//draws the title_screen
void draw_main_screen(drawer draw_tools, unsigned int button, unsigned int title){
  glBindVertexArray(draw_tools.vao);
  use_shader(draw_tools.shader);


  //enable our title text
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, title);

  //move the title to the top of the screen
  mat4 title_model = create_transform_mat4(GLH_SCALE, (vec4){1.5f, 0.25f, 0.0f});
  translate_mat4(&title_model, (vec3){0.0f, 0.75f, 0.0f});
  set_mat4("model", title_model, draw_tools.shader);
  set_vec3("color", PINK, draw_tools.shader);

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);


  glBindTexture(GL_TEXTURE_2D, button);

  //translates play button to the bottom and scales it
  mat4 button_model = create_transform_mat4(GLH_SCALE, (vec4){0.65f, 0.25f, 0.0f});
  translate_mat4(&button_model, (vec3){0.0f, -0.5f, 0.0f});
  set_mat4("model", button_model, draw_tools.shader);


  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);


  free_mat4(title_model);
  free_mat4(button_model);

  glBindTexture(GL_TEXTURE_2D, 0);
}



//draws the tic toc toe board
void draw_game(drawer draw_tools){

  glBindVertexArray(draw_tools.vao);
  use_shader(draw_tools.shader);



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
    set_vec4("isTexture", white, draw_tools.shader);
    glBindTexture(GL_TEXTURE_2D, 0);

    model = create_transform_mat4(GLH_SCALE, (vec4){scale_factor, scale_factor, 0.0f});
    translate_mat4(&model, translate[i]);


    set_mat4("model", model, draw_tools.shader);
    set_vec3("color", (vec3){RGB(0, 0, (100 + i))}, draw_tools.shader);


    //draws either an x or o if there is one there
    if(draw_tools.gridColors[i] < 10){
      set_vec4("isTexture", black, draw_tools.shader);
      if(draw_tools.gridColors[i] == 1){
        glBindTexture(GL_TEXTURE_2D, x_texture);
      }
      else{
        glBindTexture(GL_TEXTURE_2D, o_texture);
      }

    }

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
    free_mat4(model);
  }

  glDeleteTextures(1, &x_texture);
  glDeleteTextures(1, &o_texture);

  //create the board grid lines
  set_vec3("color", PURPLE, draw_tools.shader);
  vec3 scale = Vec3(1.0f, 1.35f, 0.0f);
  mat4 id;


  //draws the vertical grid lines on the screen
  for(int i =0; i < 2; i++){
    id = create_transform_mat4(GLH_TRANSLATE, (vec4){0.28f + (i * 0.45f ), 0.0f});
    scale_mat4(&id, scale);

    set_mat4("model", id, draw_tools.shader);

    glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, NULL);
    free_mat4(id);
  }


  //draws the horizontal grid lines on the screen
  for(int i =0; i < 2; i++){
    id = create_transform_mat4(GLH_SCALE, (vec4){scale.x, scale.y, scale.z, 0});
    rotate_axis_mat4(&id, 180, (vec3){1.0f, 1.0f, 0.0f});
    translate_mat4(&id, (vec3){0.0, 0.27f + (i * 0.45f), 0.0f});
    set_mat4("model", id, draw_tools.shader);
    glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, NULL);
    free_mat4(id);
  }
}

void display_winner(drawer draw_tools, int winner){
  vec4 black = {0,0,0,0};

  const char* textures[] = {"res/images/player.png", "res/images/bot.png", "res/images/draw.png"};
  unsigned int texture = load_texture(textures[winner]);

  use_shader(draw_tools.shader);
  glBindVertexArray(draw_tools.vao);

  mat4 model = create_transform_mat4(GLH_SCALE, (vec4){0.35, 0.15});
  translate_mat4(&model, (vec3){0.0f, 0.8f, 0.0f});

  set_vec3("color", WHITE, draw_tools.shader);
  set_vec4("isTexture", black, draw_tools.shader);
  set_mat4("model", model, draw_tools.shader);
  glBindTexture(GL_TEXTURE_2D, texture);


  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
  free_mat4(model);
  glBindTexture(GL_TEXTURE_2D, 0);

}



void display_end_buttons(drawer draw_tools){
  unsigned int play_again = load_texture("res/images/play_again.png");
  unsigned int quit = load_texture("res/images/quit.png");


  use_shader(draw_tools.shader);
  glBindVertexArray(draw_tools.vao);

  //draws the quit game button
  mat4 model = create_transform_mat4(GLH_SCALE, (vec4){0.45f, 0.15f, 0.0f});
  translate_mat4(&model, (vec3){-0.4f, -0.85f, 0.0f});

  set_vec3("color", WHITE, draw_tools.shader);
  set_mat4("model", model, draw_tools.shader);
  glBindTexture(GL_TEXTURE_2D, quit);

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
  free_mat4(model);


  //draw the play again button
  model = create_transform_mat4(GLH_SCALE, (vec4){0.45f, 0.15f, 0.0f});
  translate_mat4(&model, (vec3){0.4f, -0.85f, 0.0f});

  set_mat4("model", model, draw_tools.shader);
  glBindTexture(GL_TEXTURE_2D, play_again);

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
  free_mat4(model);

  glBindTexture(GL_TEXTURE_2D, 0);
  glDeleteTextures(1, &quit);
  glDeleteTextures(1, &play_again);

}
