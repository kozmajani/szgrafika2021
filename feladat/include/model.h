/*
[SZÁMÍTÓGÉPI GRAFIKA BEADANDÓ FELADAT]
[----------LOW-BUDGET SIMCITY-------]
[-------------Kozma János-----------]
[---------------SVOXGH--------------]
*/

#ifndef INCLUDE_MODEL_H
#define INCLUDE_MODEL_H
#include <stdio.h>
#include <GL/glut.h>
#include "SOIL/SOIL.h"
#define TRUE 1
#define FALSE 0
#define INVALID_VERTEX_INDEX 0

typedef GLubyte Pixel;

struct TokenArray
{
	char** tokens;
	int n_tokens;
};

struct Vertex
{
    double x;
    double y;
    double z;
};

struct TextureVertex
{
    double u;
    double v;
};

struct FacePoint
{
    int vertex_index;
    int texture_index;
    int normal_index;
};

struct Triangle
{
    struct FacePoint points[3];
};

struct Quad
{
    struct FacePoint points[4];
};

typedef struct Model
{
    int n_vertices;
    int n_texture_vertices;
    int n_normals;
    int n_triangles;
    int n_quads;
    struct Vertex* vertices;
    struct TextureVertex* texture_vertices;
    struct Vertex* normals;
    struct Triangle* triangles;
    struct Quad* quads;
}Model;

typedef struct {
    Model model;
    float material_ambient[4];
    int texture;
    struct Vertex position;
}Object;

typedef struct {
    int ground, top, front, right,back,left;
}City;

typedef struct {
	City city;
	Object skyscraper;
	Object house1;
	Object house2;
	int helpPanel;
	Object border_b1;
	Object border_b2;
}World;

World world;

int count_tokens(const char* text);

int calc_token_length(const char* text, int start_index);

char* copy_token(const char* text, int offset, int length);

void insert_token(const char* token, struct TokenArray* token_array);

void extract_tokens(const char* text, struct TokenArray* token_array);

void free_tokens(struct TokenArray* token_array);

int load_model(const char* filename, struct Model* model);

void print_model_info(const struct Model* model);

void free_model(struct Model* model);

void read_vertex(const struct TokenArray* token_array, struct Vertex* vertex);

void count_elements(FILE* file, struct Model* model);

void count_element_in_line(const char* line, struct Model* model);

void init_model_counters(struct Model* model);

void clear_comment(char* line);

void read_face_point(const char* text, struct FacePoint* face_point);

void read_element_from_line(const char* line, struct Model* model);

void create_arrays(struct Model* model);

void read_elements(FILE* file, struct Model* model);

void read_texture_vertex(const struct TokenArray* token_array, struct TextureVertex* texture_vertex);

void read_normal(const struct TokenArray* token_array, struct Vertex* normal);

void read_triangle(const struct TokenArray* token_array, struct Triangle* triangle);

void read_quad(const struct TokenArray* token_array, struct Quad* quad);

int read_next_index(const char* text, int* length);

int count_face_delimiters(const char* text);

void print_bounding_box(const struct Model* model);

int is_digit(char c);

int is_valid_triangle(const struct Triangle* triangle, const struct Model* model);

int is_valid_quad(const struct Quad* quad, const struct Model* model);

void scale_model(struct Model* model, double sx, double sy, double sz);

GLuint load_texture(const char* filename);

void init_entities(World* world);

#endif
