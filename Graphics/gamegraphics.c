#include "gamegraphics.h"
#include <stdio.h>
#include <glhf.h>
#include <glad/glad.h>


//draws the title_screen
void draw_main_screen(shader shad, unsigned int vao, unsigned int button, unsigned int title){
  glBindVertexArray(vao);
  use_shader(shad);


  //enable our title text
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, title);

  //move the title to the top of the screen
  mat4 title_model = create_transform_mat4(SCALE, (vec3){1.5f, 0.25f, 0.0f});
  translate_mat4(&title_model, (vec3){0.0f, 0.75f, 0.0f});
  set_mat4("model", title_model, shad);
  set_vec3("color", PINK, shad);

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);


  glBindTexture(GL_TEXTURE_2D, button);

  //translates play button to the bottom and scales it
  mat4 button_model = create_transform_mat4(SCALE, (vec3){0.65f, 0.25f, 0.0f});
  translate_mat4(&button_model, (vec3){0.0f, -0.5f, 0.0f});
  set_mat4("model", button_model, shad);


  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);


  free_mat4(title_model);
  free_mat4(button_model);

  glBindTexture(GL_TEXTURE_2D, 0);
}



//draws the tic toc toe board
void draw_game(shader shad, unsigned vao, int grid_colors[]){

  glBindVertexArray(vao);
  use_shader(shad);

  mat4 model;
  set_vec3("color", YELLOW, shad);

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



  for(int i =0; i < 9; i++){
    set_vec3("isTexture", WHITE, shad);
    glBindTexture(GL_TEXTURE_2D, 0);

    model = create_transform_mat4(SCALE, (vec3){scale_factor, scale_factor, 0.0f});
    translate_mat4(&model, translate[i]);


    set_mat4("model", model, shad);
    set_vec3("color", rgb((vec3){0, 0, 100 + i}), shad);


    //draws either an x or o if there is one there
    if(grid_colors[i] == -1){
      //texture for x/o
      unsigned int x_texture = glhf_load_texture("res/images/x.png");
      unsigned int o_texture = glhf_load_texture("res/images/o.png");

      set_vec3("isTexture", BLACK, shad);
      glBindTexture(GL_TEXTURE_2D, x_texture);
    }


    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
    free_mat4(model);
  }

  //create the board grid lines
  set_vec3("color", PURPLE, shad);
  vec3 scale = Vec3(1.0f, 1.35f, 0.0f);
  mat4 id;


  //draws the vertical grid lines on the screen
  for(int i =0; i < 2; i++){
    id = create_transform_mat4(TRANSLATE, (vec3){0.28f + (i * 0.45f ), 0.0f, 0.0f});
    scale_mat4(&id, scale);

    set_mat4("model", id, shad);

    glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, NULL);
    free_mat4(id);
  }


  //draws the horizontal grid lines on the screen
  for(int i =0; i < 2; i++){
    id = create_transform_mat4(SCALE, scale);
    rotate_axis_mat4(&id, 180, (vec3){1.0f, 1.0f, 0.0f});
    translate_mat4(&id, (vec3){0.0, 0.27f + (i * 0.45f), 0.0f});
    set_mat4("model", id, shad);
    glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, NULL);
    free_mat4(id);
  }


}
