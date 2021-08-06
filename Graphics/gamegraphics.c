#include "gamegraphics.h"
#include <stdio.h>
#include <glhf.h>
#include <glad/glad.h>




drawer set_up_drawer(shader shad, unsigned int vao, int arr[]){
  drawer result;
  result.shad = shad;
  result.vao = vao;

  for(int i =0; i < 9; i++){
    result.gridColors[i] = arr[i];
  }

  return result;
}

//draws the title_screen
void draw_main_screen(drawer draw_tools, unsigned int button, unsigned int title){
  glBindVertexArray(draw_tools.vao);
  use_shader(draw_tools.shad);


  //enable our title text
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, title);

  //move the title to the top of the screen
  mat4 title_model = create_transform_mat4(SCALE, (vec3){1.5f, 0.25f, 0.0f});
  translate_mat4(&title_model, (vec3){0.0f, 0.75f, 0.0f});
  set_mat4("model", title_model, draw_tools.shad);
  set_vec3("color", PINK, draw_tools.shad);

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);


  glBindTexture(GL_TEXTURE_2D, button);

  //translates play button to the bottom and scales it
  mat4 button_model = create_transform_mat4(SCALE, (vec3){0.65f, 0.25f, 0.0f});
  translate_mat4(&button_model, (vec3){0.0f, -0.5f, 0.0f});
  set_mat4("model", button_model, draw_tools.shad);


  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);


  free_mat4(title_model);
  free_mat4(button_model);

  glBindTexture(GL_TEXTURE_2D, 0);
}



//draws the tic toc toe board
void draw_game(drawer draw_tools){

  glBindVertexArray(draw_tools.vao);
  use_shader(draw_tools.shad);



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
  unsigned int x_texture = glhf_load_texture("res/images/x.png");
  unsigned int o_texture = glhf_load_texture("res/images/o.png");

  mat4 model;

  //draws the game squares
  for(int i =0; i < 9; i++){
    set_vec3("isTexture", WHITE, draw_tools.shad);
    glBindTexture(GL_TEXTURE_2D, 0);

    model = create_transform_mat4(SCALE, (vec3){scale_factor, scale_factor, 0.0f});
    translate_mat4(&model, translate[i]);


    set_mat4("model", model, draw_tools.shad);
    set_vec3("color", rgb((vec3){0, 0, 100 + i}), draw_tools.shad);


    //draws either an x or o if there is one there
    if(draw_tools.gridColors[i] < 10){
      set_vec3("isTexture", BLACK, draw_tools.shad);
      if(draw_tools.gridColors[i] == 0){
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
  set_vec3("color", PURPLE, draw_tools.shad);
  vec3 scale = Vec3(1.0f, 1.35f, 0.0f);
  mat4 id;


  //draws the vertical grid lines on the screen
  for(int i =0; i < 2; i++){
    id = create_transform_mat4(TRANSLATE, (vec3){0.28f + (i * 0.45f ), 0.0f, 0.0f});
    scale_mat4(&id, scale);

    set_mat4("model", id, draw_tools.shad);

    glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, NULL);
    free_mat4(id);
  }


  //draws the horizontal grid lines on the screen
  for(int i =0; i < 2; i++){
    id = create_transform_mat4(SCALE, scale);
    rotate_axis_mat4(&id, 180, (vec3){1.0f, 1.0f, 0.0f});
    translate_mat4(&id, (vec3){0.0, 0.27f + (i * 0.45f), 0.0f});
    set_mat4("model", id, draw_tools.shad);
    glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, NULL);
    free_mat4(id);
  }
}

void display_winner(drawer draw_tools, int winner){

  const char* textures[] = {"res/images/player.png", "res/images/bot.png", "res/images/draw.png"};
  unsigned int texture = glhf_load_texture(textures[winner]);

  use_shader(draw_tools.shad);
  glBindVertexArray(draw_tools.vao);

  mat4 model = create_transform_mat4(SCALE, (vec3){0.35, 0.15});
  translate_mat4(&model, (vec3){0.0f, 0.8f, 0.0f});

  set_vec3("color", ORANGE, draw_tools.shad);
  set_vec3("isTexture", BLACK, draw_tools.shad);
  set_mat4("model", model, draw_tools.shad);
  glBindTexture(GL_TEXTURE_2D, texture);


  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
  free_mat4(model);
  glBindTexture(GL_TEXTURE_2D, 0);

}



void display_end_buttons(drawer draw_tools){
  unsigned int play_again = glhf_load_texture("res/images/play_again.png");
  unsigned int quit = glhf_load_texture("res/images/quit.png");


  use_shader(draw_tools.shad);
  glBindVertexArray(draw_tools.vao);

  //draws the quit game button
  mat4 model = create_transform_mat4(SCALE, (vec3){0.45f, 0.15f, 0.0f});
  translate_mat4(&model, (vec3){-0.4f, -0.85f, 0.0f});

  set_vec3("color", PINK, draw_tools.shad);
  set_mat4("model", model, draw_tools.shad);
  glBindTexture(GL_TEXTURE_2D, quit);

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
  free_mat4(model);


  //draw the play again button
  model = create_transform_mat4(SCALE, (vec3){0.45f, 0.15f, 0.0f});
  translate_mat4(&model, (vec3){0.4f, -0.85f, 0.0f});

  set_mat4("model", model, draw_tools.shad);
  glBindTexture(GL_TEXTURE_2D, play_again);

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
  free_mat4(model);

  glBindTexture(GL_TEXTURE_2D, 0);
  glDeleteTextures(1, &quit);
  glDeleteTextures(1, &play_again);

}
