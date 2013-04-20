#include "the_maze_2.hpp"

TheMaze2::TheMaze2() {
    window_width_ = DEFAULT_WINDOW_WIDTH;
    window_height_ = DEFAULT_WINDOW_HEIGHT;
}

void TheMaze2::initGl() {
    
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
}

void TheMaze2::initVao() {
    
    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);
}

void TheMaze2::initVbo() {
    
    /*
    for (int i = 0; i < SURFACE_EBO_COUNT; i++) {
        Surface::elems_[i] += WALL_SEGMENT_VERT_COUNT;
    }
    */
    for (int i = 0; i < WALL_SEGMENT_EBO_COUNT; i++) {
        WallSegment::elems_[i] += SURFACE_VERT_COUNT;
    }
    
    for (int i = 0; i < PROJECTILE_EBO_COUNT; i++) {
        Projectile::elems_[i] += SURFACE_VERT_COUNT + WALL_SEGMENT_VERT_COUNT;
    }
    
    glGenBuffers(1, &vbo_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    
    // total vbo size is size of all models added together
    int vbo_size = sizeof(Surface::verts_);
    vbo_size += sizeof(WallSegment::verts_);
    vbo_size += sizeof(Projectile::verts_);
    
    // allocate space for verticies
    glBufferData(GL_ARRAY_BUFFER, vbo_size, NULL, GL_STATIC_DRAW);
    
    // load each model's vertex data into the vbo
    glBufferSubData(GL_ARRAY_BUFFER, SURFACE_VBO_POS, sizeof(Surface::verts_), Surface::verts_);
    glBufferSubData(GL_ARRAY_BUFFER, WALL_SEGMENT_VBO_POS, sizeof(WallSegment::verts_), WallSegment::verts_);
    glBufferSubData(GL_ARRAY_BUFFER, PROJECTILE_VBO_POS, sizeof(Projectile::verts_), Projectile::verts_);
    
    // init element array buffer
    glGenBuffers(1, &ebo_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
    
    // total ebo size is size of all models added together
    int ebo_size = sizeof(Surface::elems_);
    ebo_size += sizeof(WallSegment::elems_);
    ebo_size += sizeof(Projectile::elems_);
    
    // allocate space for elements
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, ebo_size, NULL, GL_STATIC_DRAW);
    
    // load each model's element data into the ebo
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, SURFACE_EBO_POS, sizeof(Surface::elems_), Surface::elems_);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, WALL_SEGMENT_EBO_POS, sizeof(WallSegment::elems_), WallSegment::elems_);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, PROJECTILE_EBO_POS, sizeof(Projectile::elems_), Projectile::elems_);
    
}

void TheMaze2::initShaders() {
    
    GLuint vertex_shader = shaderFromFile("shaders/vertex.glsl", GL_VERTEX_SHADER);
    GLuint frag_shader = shaderFromFile("shaders/fragment.glsl", GL_FRAGMENT_SHADER);
    if (vertex_shader == 0 || frag_shader == 0) {
        // TODO: thow something meaningful
        throw "shader error";
    }
    
    shader_prog_ = glCreateProgram();
    glAttachShader(shader_prog_, vertex_shader);
    glAttachShader(shader_prog_, frag_shader);
    glBindFragDataLocation(shader_prog_, 0, "out_color");
    glLinkProgram(shader_prog_);
    glUseProgram(shader_prog_);
    
}

void TheMaze2::initTextures() {
    
    wall_text_ = gli::createTexture2D("textures/test_texture.dds");
    //wall_text_ = gli::createTexture2D("textures/ice_wall.dds");
    //wall_text_ = gli::createTexture2D("textures/stone_wall.dds");
    //wall_text_ = gli::createTexture2D("textures/rough_stone_wall.dds");
    
    glGenerateMipmap(GL_TEXTURE_2D);
}

void TheMaze2::initAttributes() {
    
    position_attr_ = glGetAttribLocation(shader_prog_, "position_ms");
    glVertexAttribPointer(position_attr_, 3, GL_FLOAT, GL_FALSE, 11*sizeof(GLfloat), (void*)(0*sizeof(GLfloat)));
    
    normal_attr_ = glGetAttribLocation(shader_prog_, "normal_ms");
    glVertexAttribPointer(normal_attr_, 3, GL_FLOAT, GL_FALSE, 11*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));
    
    text_coord_attr_ = glGetAttribLocation(shader_prog_, "in_text");
    glVertexAttribPointer(text_coord_attr_, 2, GL_FLOAT, GL_FALSE, 11*sizeof(GLfloat), (void*)(6*sizeof(GLfloat)));
    
    color_attr_ = glGetAttribLocation(shader_prog_, "in_color");
    glVertexAttribPointer(color_attr_, 3, GL_FLOAT, GL_FALSE, 11*sizeof(GLfloat), (void*)(8*sizeof(GLfloat)));
    
    proj_uni_ = glGetUniformLocation(shader_prog_, "proj");
    view_uni_ = glGetUniformLocation(shader_prog_, "view");
    vert_model_uni_ = glGetUniformLocation(shader_prog_, "vert_model");
    norm_model_uni_ = glGetUniformLocation(shader_prog_, "norm_model");
    light_pos_cs_uni_ = glGetUniformLocation(shader_prog_, "light_pos_cs");
    text_samp_uni_ = glGetUniformLocation(shader_prog_, "texture_sampler");
    
    proj_matrix_ = glm::perspective(35.0f, 1920.0f / 1080.0f, 0.1f, 200.0f);
    glUniformMatrix4fv(proj_uni_, 1, GL_FALSE, glm::value_ptr(proj_matrix_));
    
}

GLuint TheMaze2::shaderFromFile(std::string filename, GLenum type) {
    std::ifstream in_stream(filename.c_str());
    std::string source_str((std::istreambuf_iterator<char>(in_stream)),
                           std::istreambuf_iterator<char>());
    const char *source_ca = source_str.c_str();
    
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source_ca, NULL);
    glCompileShader(shader);
    
    GLint isCompiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) {
        GLint max_len = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &max_len);
        std::vector<GLchar> info_log(max_len);
        glGetShaderInfoLog(shader, max_len, &max_len, &info_log[0]);
        
        std::cout << "Error compiling shader " << filename << std::endl;
        for (GLchar c : info_log) {
            std::cout << c;
        }
        std::cout << std::endl;
        return 0;
    }
    
    return shader;
}

void TheMaze2::render() {
    
    glEnableVertexAttribArray(position_attr_);
    glEnableVertexAttribArray(normal_attr_);
    glEnableVertexAttribArray(text_coord_attr_);
    glEnableVertexAttribArray(color_attr_);
    
    player_.updateModelMatrix();
    //player_.model_matrix_ = glm::inverse(player_.model_matrix_);
    glUniformMatrix4fv(view_uni_, 1, GL_FALSE, glm::value_ptr(player_.model_matrix_));
    
    // convert light position to camera space
    glm::vec3 light_pos_cs = (glm::vec3)(player_.model_matrix_ * glm::vec4(light_pos_ws_, 1.0));
    glUniform3fv(light_pos_cs_uni_, 1, glm::value_ptr(light_pos_cs));
    
    for (Surface *sf : surfaces_) {
        sf->updateModelMatrix();
        glUniformMatrix4fv(vert_model_uni_, 1, GL_FALSE, glm::value_ptr(sf->model_matrix_));
        glUniformMatrix4fv(norm_model_uni_, 1, GL_FALSE, glm::value_ptr(sf->model_matrix_));
        glUniform1i(text_samp_uni_, 0);
        
        glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, wall_text_);
        
        glDrawElements(GL_TRIANGLES, sf->ebo_count_, GL_UNSIGNED_SHORT, sf->ebo_pos_);
    }
    
    for (Model *ws : walls_) {
        ws->updateModelMatrix();
        glUniformMatrix4fv(vert_model_uni_, 1, GL_FALSE, glm::value_ptr(ws->model_matrix_));
        glUniformMatrix4fv(norm_model_uni_, 1, GL_FALSE, glm::value_ptr(ws->model_matrix_));
        glUniform1i(text_samp_uni_, 0);
        
        glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, wall_text_);
        
        glDrawElements(GL_TRIANGLES, ws->ebo_count_, GL_UNSIGNED_SHORT, ws->ebo_pos_);
    }
    
    for (Projectile *proj : projectiles_) {
        proj->updateModelMatrix();
        glUniformMatrix4fv(vert_model_uni_, 1, GL_FALSE, glm::value_ptr(proj->model_matrix_));
        glUniformMatrix4fv(norm_model_uni_, 1, GL_FALSE, glm::value_ptr(proj->model_matrix_));
        glUniform1i(text_samp_uni_, 0);
        
        glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, wall_text_);
        
        glDrawElements(GL_TRIANGLES, proj->ebo_count_, GL_UNSIGNED_SHORT, proj->ebo_pos_);
    }
    
    glDisableVertexAttribArray(position_attr_);
    glDisableVertexAttribArray(normal_attr_);
    glDisableVertexAttribArray(text_coord_attr_);
    glDisableVertexAttribArray(color_attr_);
}

void TheMaze2::handleMovement(double delta) {
    
    player_.move(delta, walls_);
    player_.update(delta);
    
    walls_[0]->move(delta, walls_);
    
    // move and update each projectile
    for (Projectile *proj : projectiles_) {
        proj->move(delta, walls_);
        proj->update(delta);
    }
    
}

void TheMaze2::addWall(int xPos, int yPos, int zPos) {
    
    WallSegment *ws = new WallSegment();
    ws->pos_.x_ = xPos;
    ws->pos_.y_ = yPos;
    ws->pos_.z_ = zPos;
    walls_.push_back(ws);
}

void TheMaze2::addWalls(int xPos, int yPos, int zPos, int xOff, int yOff) {
    if (xOff != 0) {
        int abs_off = abs(xOff);
        int delta = xOff / abs_off;
        for (int i = 0; i != abs_off*delta; i += delta) {
            addWall(xPos + i*1000, yPos, zPos);
        }
    }
    if (yOff != 0) {
        int abs_off = abs(yOff);
        int delta = yOff / abs_off;
        for (int i = 0; i != abs_off*delta; i += delta) {
            addWall(xPos, yPos + i*1000, zPos);
        }
    }
}

void TheMaze2::addSurface(int xPos, int yPos, int zPos) {
    
    Surface *sf = new Surface();
    sf->pos_.x_ = xPos;
    sf->pos_.y_ = yPos;
    sf->pos_.z_ = zPos;
    surfaces_.push_back(sf);
}

void TheMaze2::addProjectile(int xPos, int yPos, int zPos, float xFacing, float yFacing) {
    
    Projectile *proj = new Projectile(xPos, yPos, zPos, xFacing, yFacing);
    projectiles_.push_back(proj);
}

int main() {
    if (!glfwInit()) {
        std::cout << "Error initializing GLFW\n";
        return -1;
    }
    
    glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);
    if (!glfwOpenWindow(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, 
                        8, 8, 8, 0, 24, 0, GLFW_WINDOW)) {
        std::cout << "Error opening GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwSetWindowTitle("The Maze 2!");
    glfwDisable(GLFW_MOUSE_CURSOR);
    
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cout << "Error initing GLEW\n";
        glfwTerminate();
        return -1;
    }
    
    TheMaze2 &maze = TheMaze2::getInstance();
    
    maze.initGl();
    maze.initVao();
    maze.initVbo();
    maze.initShaders();
    maze.initAttributes();
    maze.initTextures();
    
    maze.light_pos_ws_ = glm::vec3(0.0, 4.0, -6.0);
    maze.addSurface(0, 0, -5000);
    maze.addSurface(0, 0, 5000); // need to flip this
    
    maze.addWall(0, 0, 0);
    maze.addWall(0, 1000, 0);
    maze.addWall(0, 2000, 0);
    maze.addWall(2000, -20000, 0);
    
    maze.walls_[3]->setScale(3.0f);
    maze.walls_[3]->pos_.z_ = 10000;
    
    maze.addWalls(-70000, -70000, 0, 140, 140);
    maze.addWalls(70000, 70000, 0, -140, -140);
    
    maze.player_.pos_.x_ = 20000;
    maze.player_.pos_.y_ = 20000;
    
    double fps_timer = 0;
    glfwSetKeyCallback(TheMaze2::handleKeyInput);
    glfwSetMouseButtonCallback(TheMaze2::handleMouseButtonInput);
    glfwSetWindowSizeCallback(TheMaze2::handleWindowResize);
    double prev_time = glfwGetTime();
    while (glfwGetWindowParam(GLFW_OPENED)) {
        double cur_time = glfwGetTime();
        double time_delta = cur_time - prev_time;
        prev_time = cur_time;
        
        // print framerate
        fps_timer += time_delta;
        if (fps_timer > 1) {
            int fps = 1 / time_delta;
            std::cout << fps << "\r" << std::flush;
            fps_timer = 0;
        }
        // logic
        maze.handleMouseInput(time_delta);
        maze.handleMovement(time_delta);
        
        //maze.cleanupObjects();
        
        // drawing
        glClearColor(0.8f, 0.8f, 0.85f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        maze.render();
        
        glfwSwapBuffers();
        
        int error = glGetError();
        if (error != 0) {
            std::cout << "GL Error " << error << std::endl;
            //return -1;
        }
    }
    
    glfwTerminate();
    return 0;
}

void TheMaze2::handleMouseInput(double time_delta) {
    int xPos, yPos;
    glfwGetMousePos(&xPos, &yPos);
    player_.xFacing_ -= player_.look_speed_ * time_delta * float(window_width_/2 - xPos);
    player_.yFacing_ += player_.look_speed_ * time_delta * float(window_height_/2 - yPos);
    glfwSetMousePos(window_width_/2, window_height_/2);
}

void TheMaze2::handleMouseButtonInput(int button, int action) {
    
    TheMaze2 &maze = TheMaze2::getInstance();
    
    switch (button) {
        // move the camera/player
        case GLFW_MOUSE_BUTTON_LEFT:
            if (action == GLFW_RELEASE) {
                maze.addProjectile(maze.player_.pos_.x_, maze.player_.pos_.y_, maze.player_.pos_.z_, 
                                   maze.player_.xFacing_, maze.player_.yFacing_);
            }
        default:
            break;
    }
}

void TheMaze2::handleKeyInput(int key, int action) {
    
    TheMaze2 &maze = TheMaze2::getInstance();
    
    switch (key) {
        // move the camera/player
        case 87: // W
            if (action == GLFW_PRESS) {
                maze.player_.move_dir_ = DIR_FORWARD;
            } else if (action == GLFW_RELEASE) {
                maze.player_.move_dir_ = DIR_NONE;
            }
            break;
        case 83: // S
            if (action == GLFW_PRESS) {
                maze.player_.move_dir_ = DIR_REVERSE;
            } else if (action == GLFW_RELEASE) {
                maze.player_.move_dir_ = DIR_NONE;
            }
            break;
        case 65: // A
            if (action == GLFW_PRESS) {
                maze.player_.strafe_dir_ = DIR_LEFT;
            } else if (action == GLFW_RELEASE) {
                maze.player_.strafe_dir_ = DIR_NONE;
            }
            break;
        case 68: // D
            if (action == GLFW_PRESS) {
                maze.player_.strafe_dir_ = DIR_RIGHT;
            } else if (action == GLFW_RELEASE) {
                maze.player_.strafe_dir_ = DIR_NONE;
            }
            break;
        case 81: // Q
            if (action == GLFW_PRESS) {
                maze.player_.rot_dir_ = DIR_LEFT;
            } else if (action == GLFW_RELEASE) {
                maze.player_.rot_dir_ = DIR_NONE;
            }
            break;
        case 69: // E
            if (action == GLFW_PRESS) {
                maze.player_.rot_dir_ = DIR_RIGHT;
            } else if (action == GLFW_RELEASE) {
                maze.player_.rot_dir_ = DIR_NONE;
            }
            break;
        // move the wall
        case 73: // I
            if (action == GLFW_PRESS) {
                maze.walls_[0]->move_dir_ = DIR_FORWARD;
            } else if (action == GLFW_RELEASE) {
                maze.walls_[0]->move_dir_ = DIR_NONE;
            }
            break;
        case 75: // K
            if (action == GLFW_PRESS) {
                maze.walls_[0]->move_dir_ = DIR_REVERSE;
            } else if (action == GLFW_RELEASE) {
                maze.walls_[0]->move_dir_ = DIR_NONE;
            }
            break;
        case 74: // J
            if (action == GLFW_PRESS) {
                maze.walls_[0]->rot_dir_ = DIR_LEFT;
            } else if (action == GLFW_RELEASE) {
                maze.walls_[0]->rot_dir_ = DIR_NONE;
            }
            break;
        case 76: // L
            if (action == GLFW_PRESS) {
                maze.walls_[0]->rot_dir_ = DIR_RIGHT;
            } else if (action == GLFW_RELEASE) {
                maze.walls_[0]->rot_dir_ = DIR_NONE;
            }
            break;
        
        default:
            break;
    }
}

void TheMaze2::handleWindowResize(int width, int height) {
    
    TheMaze2 &maze = TheMaze2::getInstance();
    
    maze.window_width_ = width;
    maze.window_height_ = height;
}


