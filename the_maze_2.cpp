#include "the_maze_2.hpp"

void TheMaze2::initGl() {
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

void TheMaze2::initVao() {
    
    GLuint vert_array;
    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);
}

void TheMaze2::initVbo() {
    
    glGenBuffers(1, &vbo_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    
    // total vbo size is size of all models added together
    int vbo_size = sizeof(WallSegment::verts_);
    
    glBufferData(GL_ARRAY_BUFFER, vbo_size, WallSegment::verts_, GL_STATIC_DRAW);
    
    // load each model's vertex data into the vbo
    // WallSegment
    glBufferSubData(GL_ARRAY_BUFFER, WALL_SEGMENT_VBO_POS, sizeof(WallSegment::verts_), WallSegment::verts_);
    
    // init element array buffer
    glGenBuffers(1, &ebo_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
    
    // total ebo size is size of all models added together
    int ebo_size = sizeof(WallSegment::elems_);
    
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, ebo_size, WallSegment::elems_, GL_STATIC_DRAW);
    
    // load each model's element data into the ebo
    // WallSegment
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, WALL_SEGMENT_EBO_POS, sizeof(WallSegment::elems_), WallSegment::elems_);
    
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

void TheMaze2::initAttributes() {
    
    position_attr_ = glGetAttribLocation(shader_prog_, "position");
    glVertexAttribPointer(position_attr_, 3, GL_FLOAT, GL_FALSE, 11*sizeof(GLfloat), (void*)(0*sizeof(GLfloat)));
    
    normal_attr_ = glGetAttribLocation(shader_prog_, "normal");
    glVertexAttribPointer(normal_attr_, 3, GL_FLOAT, GL_FALSE, 11*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));
    
    color_attr_ = glGetAttribLocation(shader_prog_, "in_color");
    glVertexAttribPointer(color_attr_, 3, GL_FLOAT, GL_FALSE, 11*sizeof(GLfloat), (void*)(8*sizeof(GLfloat)));
    
    proj_uni_ = glGetUniformLocation(shader_prog_, "proj");
    view_uni_ = glGetUniformLocation(shader_prog_, "view");
    vert_model_uni_ = glGetUniformLocation(shader_prog_, "vert_model");
    norm_model_uni_ = glGetUniformLocation(shader_prog_, "norm_model");
    
    proj_matrix_ = glm::perspective(35.0f, 1920.0f / 1080.0f, 0.1f, 100.0f);
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
        return 0;
    }
    
    return shader;
}

void TheMaze2::render() {
    
    glEnableVertexAttribArray(position_attr_);
    glEnableVertexAttribArray(normal_attr_);
    glEnableVertexAttribArray(color_attr_);
    
    player_.updateModelMatrix();
    //player_.model_matrix_ = glm::inverse(player_.model_matrix_);
    glUniformMatrix4fv(view_uni_, 1, GL_FALSE, glm::value_ptr(player_.model_matrix_));
    
    for (WallSegment ws : walls_) {
        ws.updateModelMatrix();
        glUniformMatrix4fv(vert_model_uni_, 1, GL_FALSE, glm::value_ptr(ws.model_matrix_));
        glUniformMatrix4fv(norm_model_uni_, 1, GL_FALSE, glm::value_ptr(ws.model_matrix_));
        glDrawElements(GL_TRIANGLES, ws.ebo_count_, GL_UNSIGNED_SHORT, ws.ebo_pos_);
    }
    
    glDisableVertexAttribArray(position_attr_);
    glDisableVertexAttribArray(normal_attr_);
    glDisableVertexAttribArray(color_attr_);
}

void TheMaze2::handleMovement(double delta) {
    
    player_.move(delta);
    walls_[0].move(delta);
    
}

void TheMaze2::handleKeyInput(int key, int action) {
    
    TheMaze2 &maze = TheMaze2::getInstance();
    
    switch (key) {
        
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
                maze.player_.rot_dir_ = DIR_LEFT;
            } else if (action == GLFW_RELEASE) {
                maze.player_.rot_dir_ = DIR_NONE;
            }
            break;
        case 68: // D
            if (action == GLFW_PRESS) {
                maze.player_.rot_dir_ = DIR_RIGHT;
            } else if (action == GLFW_RELEASE) {
                maze.player_.rot_dir_ = DIR_NONE;
            }
            break;
        /*
        case 87: // W
            if (action == GLFW_PRESS) {
                maze.walls_[0].move_dir_ = DIR_FORWARD;
            } else if (action == GLFW_RELEASE) {
                maze.walls_[0].move_dir_ = DIR_NONE;
            }
            break;
        case 83: // S
            if (action == GLFW_PRESS) {
                maze.walls_[0].move_dir_ = DIR_REVERSE;
            } else if (action == GLFW_RELEASE) {
                maze.walls_[0].move_dir_ = DIR_NONE;
            }
            break;
        case 65: // A
            if (action == GLFW_PRESS) {
                maze.walls_[0].rot_dir_ = DIR_LEFT;
            } else if (action == GLFW_RELEASE) {
                maze.walls_[0].rot_dir_ = DIR_NONE;
            }
            break;
        case 68: // D
            if (action == GLFW_PRESS) {
                maze.walls_[0].rot_dir_ = DIR_RIGHT;
            } else if (action == GLFW_RELEASE) {
                maze.walls_[0].rot_dir_ = DIR_NONE;
            }
            break;
        */
        default:
            break;
    }
}

int main() {
    if (!glfwInit()) {
        std::cout << "Error initializing GLFW\n";
        return -1;
    }
    
    if (!glfwOpenWindow(1920, 1080, 8, 8, 8, 0, 24, 0, GLFW_WINDOW)) {
        std::cout << "Error opening GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwSetWindowTitle("The Maze 2!");
    
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
    
    WallSegment ws;
    ws.yPos_ = -20200;
    ws.xPos_ = 2200;
    
    //maze.player_.xPos_ = 20000;
    //maze.player_.yPos_ = 20000;
    maze.player_.facing_ = (3.0f/2.0f)*M_PI;
    
    maze.walls_.push_back(ws);
    
    glfwSetKeyCallback(TheMaze2::handleKeyInput);
    double prev_time = glfwGetTime();
    while (glfwGetWindowParam(GLFW_OPENED)) {
        double cur_time = glfwGetTime();
        double time_delta = cur_time - prev_time;
        prev_time = cur_time;
        
        // logic
        maze.handleMovement(time_delta);
        
        // drawing
        glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        maze.render();
        
        glfwSwapBuffers();
        
        int error = glGetError();
        if (error != 0) {
            //std::cout << "GL Error " << error << std::endl;
            //return -1;
        }
    }
    
    glfwTerminate();
    return 0;
}










