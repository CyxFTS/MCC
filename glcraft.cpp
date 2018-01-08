#include <glad\glad.h>
#include <glfw/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb\stb_image.h>

#include <camera.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/noise.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include <generator.h>
#include <light.h>
#include <sky.h>
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

ChunkGeneratorOverWorldGrain *c = new ChunkGeneratorOverWorldGrain();
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
#define flowerRX 0.685f
#define flowerLX 0.63f
#define flowerTY 0.002f
#define flowerBY 0.062f
#define itemXoff 0.0625f


//item

float Flowervertices[] = {
	// positions                   // texture coords

	0.5f,  0.5f + 0.45, 0.0f,     0.685f , 0.002f, // top right
	0.5f, -0.5f + 0.45 , 0.0f,     0.685f , 0.062f, // bottom right
	-0.5f, -0.5f + 0.45, 0.0f,      0.63f , 0.062f, // bottom left
	-0.5f,  0.5f + 0.45, 0.0f,      0.63f , 0.002f,  // top left 
	0.0f, 0.5f + 0.45, -0.5f,	   0.685f , 0.002f, // top right
	0.0f, -0.5f + 0.45, -0.5f,   0.685f , 0.062f, // top right
	0.0f, -0.5f + 0.45, 0.5f,	   0.63f , 0.062f, // top right
	0.0f, 0.5f + 0.45, 0.5f,	   0.63f , 0.002f  // top right
};

float Grassvertices[] = {
	0.5f,  0.5f + 0.45, 0.0f,     0.685f + 0.0625, 0.002f, // top right
	0.5f, -0.5f + 0.45, 0.0f,      0.685f + 0.0625, 0.062f, // bottom right
	-0.5f, -0.5f + 0.45, 0.0f,      0.63f + 0.0625, 0.062f, // bottom left
	-0.5f,  0.5f + 0.45, 0.0f,      0.63f + 0.0625, 0.002f,  // top left 
	0.0f, 0.5f + 0.45, -0.5f,	   0.685f + 0.0625, 0.002f, // top right
	0.0f, -0.5f + 0.45, -0.5f,    0.685f + 0.0625, 0.062f, // top right
	0.0f, -0.5f + 0.45, 0.5f,	   0.63f + 0.0625, 0.062f, // top right
	0.0f, 0.5f + 0.45, 0.5f,	   0.63f + 0.0625, 0.002f  // top right
};

float Othervertices[] = {
	0.5f,  0.5f + 0.45, 0.0f,     0.685f + 0.0625 + itemXoff, 0.002f, // top right
	0.5f, -0.5f + 0.45, 0.0f,      0.685f + 0.0625 + itemXoff, 0.062f, // bottom right
	-0.5f, -0.5f + 0.45, 0.0f,      0.63f + 0.0625 + itemXoff, 0.062f, // bottom left
	-0.5f,  0.5f + 0.45, 0.0f,      0.63f + 0.0625 + itemXoff, 0.002f,  // top left 
	0.0f, 0.5f + 0.45, -0.5f,	   0.685f + 0.0625 + itemXoff, 0.002f, // top right
	0.0f, -0.5f + 0.45, -0.5f,    0.685f + 0.0625 + itemXoff, 0.062f, // top right
	0.0f, -0.5f + 0.45, 0.5f,	   0.63f + 0.0625 + itemXoff, 0.062f, // top right
	0.0f, 0.5f + 0.45, 0.5f,	   0.63f + 0.0625 + itemXoff, 0.002f  // top right
};
unsigned int indices[] = {
	0, 1, 3, // first triangle
	1, 2, 3,  // second triangle
	4, 5, 7, // first triangle
	5, 6, 7,  // second triangle
};

static GLuint itemProgram;
static GLuint item_mvp;


// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;
bool firstRender = true;
GLdouble firstRenderTime;

static GLuint program;
static GLuint water_program;
static GLuint depthProgram;
static GLuint depthTestProgram;
const static GLint attribute_coord = 0;
const static GLint normal_coord = 1;
const static GLint tangent_coord = 2;
const static GLint bitangent_coord = 3;
static GLint uniform_mvp;
static GLint uniform_model;
static GLint uniform_view;
static GLint uniform_projection;
static GLuint texture;
static GLint uniform_texture;
static GLuint cursor_vbo;
static GLint uniform_viewpos;
static DirlightUniform uniform_dirlight, uniform_dirlight2;
static GLint uniform_lightspacematrix_normal;
static GLint uniform_lightspacematrix_depth;
static GLint uniform_shadow;

static DirectLight dirlight;

static glm::vec3 position;
static glm::vec3 fforward;
static glm::vec3 rright;
static glm::vec3 up;
static glm::vec3 lookat;
static glm::vec3 angle;

static int ww, wh;
static int mx, my, mz;
static int face;
static uint8_t buildtype = 1;

static time_t now;
static unsigned int keys;
static bool select_using_depthbuffer = true;

// Size of one chunk in blocks
#define CX 16
#define CY 16
#define CZ 16

// Number of chunks in the world
//#define SCX 32
//#define SCY 16
//#define SCZ 32
#define SCX 32
#define SCY 16
#define SCZ 32

int blocks[CX*SCX][CY*SCY][CZ*SCZ];
int isGround[CX*SCX][CZ*SCZ] = { 0 };
int itemType[CX*SCX][CZ*SCZ] = { 0 };

// Sea level
#define SEALEVEL 4

// Number of VBO slots for chunks
#define CHUNKSLOTS (SCX * SCY * SCZ)

GLuint create_program(const char *vertexfile, const char *fragmentfile);

static const int transparent[16] = { 2, 0, 0, 0, 1, 0, 0, 0, 3, 4, 0, 0, 0, 0, 0, 0 };
static const char *blocknames[16] = {
	"air", "dirt", "topsoil", "grass", "leaves", "wood", "stone", "sand",
	"water", "glass", "brick", "ore", "woodrings", "white", "black", "x-y"
};

struct byte4 {
	uint8_t x, y, z, w;
	byte4() {}
	byte4(const uint8_t &x, const uint8_t &y, const uint8_t &z, const uint8_t &w) : x(x), y(y), z(z), w(w) {}
};

struct vertexFormat {
	float x, y, z, nx, ny, nz, ux, uy;
	vertexFormat() {}
	vertexFormat(float tx, float ty, float tz, float tnx, float tny, float tnz, float tux, float tuy) :
		x(tx), y(ty), z(tz), nx(tnx), ny(tny), nz(tnz), ux(tux), uy(tuy) {}
};
#define WAVE_AMPLITUDE 0.01f
#define WAVE_LENGTH 0.02f
#define WAVE_SPEED 0.01f
#define DAMPING 0.0f
#define STEEPNESS 1.f

#define SPLIT 2

struct Wave {
	GLfloat A = WAVE_AMPLITUDE;
	glm::vec2 D;
	glm::vec2 C;
	GLfloat w = 2.f * glm::pi<GLfloat>() / WAVE_LENGTH;
	GLfloat phi = WAVE_SPEED * w;
};
Wave w1, w2, w3;

GLint get_uniform(GLuint program, const char *name) {
	GLint uniform = glGetUniformLocation(program, name);
	if (uniform == -1)
		fprintf(stderr, "Could not bind uniform %s\n", name);
	return uniform;
}
void set_uniform(GLuint program, const GLchar* name, GLint v0) {
	glUniform1i(get_uniform(program, name), v0);
}
void set_uniform(GLuint program, const GLchar* name, GLfloat v0) {
	glUniform1f(get_uniform(program, name), v0);
}
void set_uniform(GLuint program, const GLchar* name, GLfloat v0, GLfloat v1) {
	glUniform2f(get_uniform(program, name), v0, v1);
}
void set_uniform(GLuint program, const GLchar* name, GLfloat v0, GLfloat v1, GLfloat v2) {
	glUniform3f(get_uniform(program, name), v0, v1, v2);
}
void set_uniform(GLuint program, const GLchar* name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) {
	glUniform4f(get_uniform(program, name), v0, v1, v2, v3);
}
void set_uniform(GLuint program, const GLchar* name, const glm::vec2& value, GLsizei count = 1) {
	glUniform2fv(get_uniform(program, name), count, glm::value_ptr(value));
}
void set_uniform(GLuint program, const GLchar* name, const glm::vec3& value, GLsizei count = 1) {
	glUniform3fv(get_uniform(program, name), count, glm::value_ptr(value));
}
void set_uniform(GLuint program, const GLchar* name, const glm::vec4& value, GLsizei count = 1) {
	glUniform4fv(get_uniform(program, name), count, glm::value_ptr(value));
}
void set_uniform(GLuint program, const GLchar* name, const glm::mat2& value, GLboolean transpose = GL_FALSE, GLsizei count = 1) {
	glUniformMatrix2fv(get_uniform(program, name), count, transpose, glm::value_ptr(value));
}
void set_uniform(GLuint program, const GLchar* name, const glm::mat3& value, GLboolean transpose = GL_FALSE, GLsizei count = 1) {
	glUniformMatrix3fv(get_uniform(program, name), count, transpose, glm::value_ptr(value));
}
void set_uniform(GLuint program, const GLchar* name, const glm::mat4& value, GLboolean transpose = GL_FALSE, GLsizei count = 1) {
	glUniformMatrix4fv(get_uniform(program, name), count, transpose, glm::value_ptr(value));
}

static struct chunk *chunk_slot[CHUNKSLOTS] = { 0 };

struct chunk {
	int blk[CX][CY][CZ];
	struct chunk *left, *right, *below, *above, *front, *back;
	int slot;
	GLuint vbo, vbo_normal,vbo_tangent,vbo_bitangent;
	int elements;
	time_t lastused;
	bool changed;
	bool noised;
	bool initialized;
	int ax;
	int ay;
	int az;

	chunk() : ax(0), ay(0), az(0) {
		memset(blk, 0, sizeof blk);
		left = right = below = above = front = back = 0;
		lastused = now;
		slot = 0;
		changed = true;
		initialized = false;
		noised = false;
	}

	chunk(int x, int y, int z) : ax(x), ay(y), az(z) {
		memset(blk, 0, sizeof blk);
		left = right = below = above = front = back = 0;
		lastused = now;
		slot = 0;
		changed = true;
		initialized = false;
		noised = false;
	}

	uint8_t get(int x, int y, int z) const {
		if (x < 0)
			return left ? left->blk[x + CX][y][z] : 0;
		if (x >= CX)
			return right ? right->blk[x - CX][y][z] : 0;
		if (y < 0)
			return below ? below->blk[x][y + CY][z] : 0;
		if (y >= CY)
			return above ? above->blk[x][y - CY][z] : 0;
		if (z < 0)
			return front ? front->blk[x][y][z + CZ] : 0;
		if (z >= CZ)
			return back ? back->blk[x][y][z - CZ] : 0;
		return blk[x][y][z];
	}

	bool isblocked(int x1, int y1, int z1, int x2, int y2, int z2) {
		// Invisible blocks are always "blocked"
		if (!blk[x1][y1][z1])
			return true;

		// Leaves do not block any other block, including themselves
		if (transparent[get(x2, y2, z2)] == 1)
			return false;

		// Non-transparent blocks always block line of sight
		if (!transparent[get(x2, y2, z2)])
			return true;

		// Otherwise, LOS is only blocked by blocks if the same transparency type
		if (x1 > 16 || x2 > 16 || y1 > 16 || y2 > 16 || z1 > 16 || z2 > 16)
			return true;
		return transparent[get(x2, y2, z2)] == transparent[blk[x1][y1][z1]];
	}

	void set(int x, int y, int z, uint8_t type) {
		// If coordinates are outside this chunk, find the right one.
		if (x < 0) {
			if (left)
				left->set(x + CX, y, z, type);
			return;
		}
		if (x >= CX) {
			if (right)
				right->set(x - CX, y, z, type);
			return;
		}
		if (y < 0) {
			if (below)
				below->set(x, y + CY, z, type);
			return;
		}
		if (y >= CY) {
			if (above)
				above->set(x, y - CY, z, type);
			return;
		}
		if (z < 0) {
			if (front)
				front->set(x, y, z + CZ, type);
			return;
		}
		if (z >= CZ) {
			if (back)
				back->set(x, y, z - CZ, type);
			return;
		}

		// Change the block
		blk[x][y][z] = type;
		changed = true;

		// When updating blocks at the edge of this chunk,
		// visibility of blocks in the neighbouring chunk might change.
		if (x == 0 && left)
			left->changed = true;
		if (x == CX - 1 && right)
			right->changed = true;
		if (y == 0 && below)
			below->changed = true;
		if (y == CY - 1 && above)
			above->changed = true;
		if (z == 0 && front)
			front->changed = true;
		if (z == CZ - 1 && back)
			back->changed = true;
	}

	static float noise2d(float x, float y, int seed, int octaves, float persistence) {
		float sum = 0;
		float strength = 1.0;
		float scale = 1.0;

		for (int i = 0; i < octaves; i++) {
			sum += strength * glm::simplex(glm::vec2(x, y) * scale);
			scale *= 2.0;
			strength *= persistence;
		}

		return sum;
	}

	static float noise3d_abs(float x, float y, float z, int seed, int octaves, float persistence) {
		float sum = 0;
		float strength = 1.0;
		float scale = 1.0;

		for (int i = 0; i < octaves; i++) {
			sum += strength * fabs(glm::simplex(glm::vec3(x, y, z) * scale));
			scale *= 2.0;
			strength *= persistence;
		}

		return sum;
	}

	void noise()
	{
		if (noised)
			return;
		else
			noised = true;
		//ChunkColumnStorage chunk1 = c->Generate(ax, ay, GeneratorSettings());
		for (int x = 0; x < CX; x++)
		{
			for (int y = 0; y < CY; y++)
			{
				for (int z = 0; z < CZ; z++)
				{
					blk[x][y][z] = blocks[(ax + SCX / 2)*CX + x][(ay + SCY / 2)*CY + y][(az + SCZ / 2)*CZ + z];
				}
			}
		}
		//delete c;
		changed = true;
	}

	void noise(int seed) {
		if (noised)
			return;
		else
			noised = true;

		for (int x = 0; x < CX; x++) {
			for (int z = 0; z < CZ; z++) {
				// Land height
				float n = noise2d((x + ax * CX) / 256.0, (z + az * CZ) / 256.0, seed, 5, 0.8) * 4;
				int h = n * 2;
				int y = 0;

				// Land blocks
				for (y = 0; y < CY; y++) {
					// Are we above "ground" level?
					if (y + ay * CY >= h) {
						// If we are not yet up to sea level, fill with water blocks
						if (y + ay * CY < SEALEVEL) {
							blk[x][y][z] = 8;
							continue;
							// Otherwise, we are in the air
						}
						else
							break;
					}

					// Random value used to determine land type
					float r = noise3d_abs((x + ax * CX) / 16.0, (y + ay * CY) / 16.0, (z + az * CZ) / 16.0, -seed, 2, 1);

					// Sand layer
					if (n + r * 5 < 4)
						blk[x][y][z] = 7;
					// Dirt layer, but use grass blocks for the top
					else if (n + r * 5 < 8)
						blk[x][y][z] = (h < SEALEVEL || y + ay * CY < h - 1) ? 1 : 3;
					// Rock layer
					else if (r < 1.25)
						blk[x][y][z] = 6;
					// Sometimes, ores!
					else
						blk[x][y][z] = 11;
				}
			}
		}
		changed = true;
	}

	void update() {
		byte4 vertex[CX * CY * CZ * 18];
		//1 represent (1, 0, 0), 2 represent (0, 1, 0), 3 represent (0, 0, 1)
		//-1 represent (-1, 0, 0), -2 represent (0, -1, 0), -3 represent (0, 0, -1)
		GLfloat normal[CX * CY * CZ * 18];
		glm::vec3 tangent[CX * CY * CZ * 18];
		glm::vec3 bitangent[CX * CY * CZ * 18];
		int i = 0;
		int merged = 0;
		bool vis = false;

		// View from negative x
		
		for (int x = CX - 1; x >= 0; x--) {
			for (int y = 0; y < CY; y++) {
				for (int z = 0; z < CZ; z++) {
					// Line of sight blocked?
					if (isblocked(x, y, z, x - 1, y, z)) {
						vis = false;
						continue;
					}
					if (blk[x][y][z] == 8)
						continue;
					uint8_t top = blk[x][y][z];
					uint8_t bottom = blk[x][y][z];
					uint8_t side = blk[x][y][z];

					// Grass block has dirt sides and bottom
					if (top == 2) {
						bottom = 3;
						side = 9;
						// Wood blocks have rings on top and bottom
					}
					else if (top == 5) {
						top = bottom = 12;
					}

					// Same block as previous one? Extend it.
					if (vis && z != 0 && blk[x][y][z] == blk[x][y][z - 1]) {
						vertex[i - 5] = byte4(x, y, z + 1, side);
						vertex[i - 2] = byte4(x, y, z + 1, side);
						vertex[i - 1] = byte4(x, y + 1, z + 1, side);
						merged++;
						// Otherwise, add a new quad.
					}
					else {
						glm::vec3 pos1(x, y, z + 1);
						glm::vec3 pos2(x, y, z);
						glm::vec3 pos3(x, y + 1, z);
						glm::vec3 pos4(x, y + 1, z + 1);

						glm::vec2 uv1((0 + side) / 16.0, 1);
						glm::vec2 uv2((0 + side) / 16.0, 0);
						glm::vec2 uv3((1 + side) / 16.0, 0);
						glm::vec2 uv4((1 + side) / 16.0, 1);
						glm::vec3 nm(-1.0f, 0.0f, 0.0f);

						// calculate tangent/bitangent vectors of both triangles
						glm::vec3 tangent1, bitangent1;
						glm::vec3 tangent2, bitangent2;
						// triangle 1
						// ----------
						glm::vec3 edge1 = pos2 - pos1;
						glm::vec3 edge2 = pos3 - pos1;
						glm::vec2 deltaUV1 = uv2 - uv1;
						glm::vec2 deltaUV2 = uv3 - uv1;

						GLfloat f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

						tangent1.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
						tangent1.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
						tangent1.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
						tangent1 = glm::normalize(tangent1);

						bitangent1.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
						bitangent1.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
						bitangent1.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
						bitangent1 = glm::normalize(bitangent1);

						// triangle 2
						// ----------
						edge1 = pos3 - pos1;
						edge2 = pos4 - pos1;
						deltaUV1 = uv3 - uv1;
						deltaUV2 = uv4 - uv1;

						f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

						tangent2.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
						tangent2.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
						tangent2.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
						tangent2 = glm::normalize(tangent2);


						bitangent2.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
						bitangent2.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
						bitangent2.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
						bitangent2 = glm::normalize(bitangent2);

						normal[i] = -1;
						tangent[i] = tangent1;
						vertex[i++] = byte4(x, y, z, side);
						normal[i] = -1;
						tangent[i] = tangent1;
						vertex[i++] = byte4(x, y, z + 1, side);
						normal[i] = -1;
						tangent[i] = tangent1;
						vertex[i++] = byte4(x, y + 1, z, side);
						normal[i] = -1;
						tangent[i] = tangent2;
						vertex[i++] = byte4(x, y + 1, z, side);
						normal[i] = -1;
						tangent[i] = tangent2;
						vertex[i++] = byte4(x, y, z + 1, side);
						normal[i] = -1;
						tangent[i] = tangent2;
						vertex[i++] = byte4(x, y + 1, z + 1, side);
						
					}

					vis = true;
				}
			}
		}

		// View from positive x

		for (int x = 0; x < CX; x++) {
			for (int y = 0; y < CY; y++) {
				for (int z = 0; z < CZ; z++) {
					if (isblocked(x, y, z, x + 1, y, z)) {
						vis = false;
						continue;
					}
					if (blk[x][y][z] == 8)
						continue;
					uint8_t top = blk[x][y][z];
					uint8_t bottom = blk[x][y][z];
					uint8_t side = blk[x][y][z];

					// Grass block has dirt sides and bottom
					if (top == 2) {
						bottom = 3;
						side = 9;
						// Wood blocks have rings on top and bottom
					}
					else if (top == 5) {
						top = bottom = 12;
					}

					if (vis && z != 0 && blk[x][y][z] == blk[x][y][z - 1]) {
						vertex[i - 4] = byte4(x + 1, y, z + 1, side);
						vertex[i - 2] = byte4(x + 1, y + 1, z + 1, side);
						vertex[i - 1] = byte4(x + 1, y, z + 1, side);
						merged++;
					}
					else {
						glm::vec3 pos1(x+1, y, z + 1);
						glm::vec3 pos2(x+1, y, z);
						glm::vec3 pos3(x+1, y + 1, z);
						glm::vec3 pos4(x+1, y + 1, z + 1);

						glm::vec2 uv1((0 + side) / 16.0, 1);
						glm::vec2 uv2((0 + side) / 16.0, 0);
						glm::vec2 uv3((1 + side) / 16.0, 0);
						glm::vec2 uv4((1 + side) / 16.0, 1);
						glm::vec3 nm(1.0f, 0.0f, 0.0f);

						// calculate tangent/bitangent vectors of both triangles
						glm::vec3 tangent1, bitangent1;
						glm::vec3 tangent2, bitangent2;
						// triangle 1
						// ----------
						glm::vec3 edge1 = pos2 - pos1;
						glm::vec3 edge2 = pos3 - pos1;
						glm::vec2 deltaUV1 = uv2 - uv1;
						glm::vec2 deltaUV2 = uv3 - uv1;

						GLfloat f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

						tangent1.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
						tangent1.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
						tangent1.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
						tangent1 = glm::normalize(tangent1);

						bitangent1.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
						bitangent1.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
						bitangent1.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
						bitangent1 = glm::normalize(bitangent1);

						// triangle 2
						// ----------
						edge1 = pos3 - pos1;
						edge2 = pos4 - pos1;
						deltaUV1 = uv3 - uv1;
						deltaUV2 = uv4 - uv1;

						f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

						tangent2.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
						tangent2.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
						tangent2.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
						tangent2 = glm::normalize(tangent2);


						bitangent2.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
						bitangent2.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
						bitangent2.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
						bitangent2 = glm::normalize(bitangent2);

						normal[i] = 1;
						tangent[i] = tangent1;
						vertex[i++] = byte4(x + 1, y, z, side);
						normal[i] = 1;
						tangent[i] = tangent1;
						vertex[i++] = byte4(x + 1, y + 1, z, side);
						normal[i] = 1;
						tangent[i] = tangent1;
						vertex[i++] = byte4(x + 1, y, z + 1, side);
						normal[i] = 1;
						tangent[i] = tangent2;
						vertex[i++] = byte4(x + 1, y + 1, z, side);
						normal[i] = 1;
						tangent[i] = tangent2;
						vertex[i++] = byte4(x + 1, y + 1, z + 1, side);
						normal[i] = 1;
						tangent[i] = tangent2;
						vertex[i++] = byte4(x + 1, y, z + 1, side);
					}
					vis = true;
				}
			}
		}

		// View from negative y

		for (int x = 0; x < CX; x++) {
			for (int y = CY - 1; y >= 0; y--) {
				for (int z = 0; z < CZ; z++) {
					if (isblocked(x, y, z, x, y - 1, z)) {
						vis = false;
						continue;
					}
					if (blk[x][y][z] == 8)
						continue;
					uint8_t top = blk[x][y][z];
					uint8_t bottom = blk[x][y][z];

					// Grass block has dirt sides and bottom
					if (top == 2) {
						bottom = 3;
						//side = 9;
						// Wood blocks have rings on top and bottom
					}
					else if (top == 5) {
						top = bottom = 12;
					}

					if (vis && z != 0 && blk[x][y][z] == blk[x][y][z - 1]) {
						vertex[i - 4] = byte4(x, y, z + 1, bottom + 128);
						vertex[i - 2] = byte4(x + 1, y, z + 1, bottom + 128);
						vertex[i - 1] = byte4(x, y, z + 1, bottom + 128);
						merged++;
					}
					else {
						glm::vec3 pos1(x + 1, y, z);
						glm::vec3 pos2(x, y, z);
						glm::vec3 pos3(x, y, z + 1);
						glm::vec3 pos4(x + 1, y, z + 1);

						glm::vec2 uv1((1 + bottom) / 16.0, 0);
						glm::vec2 uv2((0 + bottom) / 16.0, 0);
						glm::vec2 uv3((0 + bottom) / 16.0, 1);
						glm::vec2 uv4((1 + bottom) / 16.0, 1);
						glm::vec3 nm(0.0f ,-1.0f, 0.0f);

						// calculate tangent/bitangent vectors of both triangles
						glm::vec3 tangent1, bitangent1;
						glm::vec3 tangent2, bitangent2;
						// triangle 1
						// ----------
						glm::vec3 edge1 = pos2 - pos1;
						glm::vec3 edge2 = pos3 - pos1;
						glm::vec2 deltaUV1 = uv2 - uv1;
						glm::vec2 deltaUV2 = uv3 - uv1;

						GLfloat f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

						tangent1.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
						tangent1.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
						tangent1.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
						tangent1 = glm::normalize(tangent1);

						bitangent1.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
						bitangent1.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
						bitangent1.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
						bitangent1 = glm::normalize(bitangent1);

						// triangle 2
						// ----------
						edge1 = pos3 - pos1;
						edge2 = pos4 - pos1;
						deltaUV1 = uv3 - uv1;
						deltaUV2 = uv4 - uv1;

						f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

						tangent2.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
						tangent2.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
						tangent2.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
						tangent2 = glm::normalize(tangent2);


						bitangent2.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
						bitangent2.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
						bitangent2.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
						bitangent2 = glm::normalize(bitangent2);
						normal[i] = -2;
						tangent[i] = tangent1;
						vertex[i++] = byte4(x, y, z, bottom + 128);
						normal[i] = -2;
						tangent[i] = tangent1;
						vertex[i++] = byte4(x + 1, y, z, bottom + 128);
						normal[i] = -2;
						tangent[i] = tangent1;
						vertex[i++] = byte4(x, y, z + 1, bottom + 128);
						normal[i] = -2;
						tangent[i] = tangent2;
						vertex[i++] = byte4(x + 1, y, z, bottom + 128);
						normal[i] = -2;
						tangent[i] = tangent2;
						vertex[i++] = byte4(x + 1, y, z + 1, bottom + 128);
						normal[i] = -2;
						tangent[i] = tangent2;
						vertex[i++] = byte4(x, y, z + 1, bottom + 128);
					}
					vis = true;
				}
			}
		}

		// View from positive y

		for (int x = 0; x < CX; x++) {
			for (int y = 0; y < CY; y++) {
				for (int z = 0; z < CZ; z++) {
					if (isblocked(x, y, z, x, y + 1, z)) {
						vis = false;
						continue;
					}
					if (blk[x][y][z] == 8)
						continue;
					uint8_t top = blk[x][y][z];
					uint8_t bottom = blk[x][y][z];

					// Grass block has dirt sides and bottom
					if (top == 2) {
						bottom = 3;
						//side = 9;
						// Wood blocks have rings on top and bottom
					}
					else if (top == 5) {
						top = bottom = 12;
					}

					if (vis && z != 0 && blk[x][y][z] == blk[x][y][z - 1]) {
						vertex[i - 5] = byte4(x, y + 1, z + 1, top + 128);
						vertex[i - 2] = byte4(x, y + 1, z + 1, top + 128);
						vertex[i - 1] = byte4(x + 1, y + 1, z + 1, top + 128);
						merged++;
					}
					else {
						glm::vec3 pos1(x, y + 1, z + 1);
						glm::vec3 pos2(x, y + 1, z);
						glm::vec3 pos3(x + 1, y + 1, z);
						glm::vec3 pos4(x + 1, y + 1, z + 1);

						glm::vec2 uv1((0 + top) / 16.0, 1);
						glm::vec2 uv2((0 + top) / 16.0, 0);
						glm::vec2 uv3((1 + top) / 16.0, 0);
						glm::vec2 uv4((1 + top) / 16.0, 1);
						glm::vec3 nm(0.0f, 1.0f, 0.0f);

						// calculate tangent/bitangent vectors of both triangles
						glm::vec3 tangent1, bitangent1;
						glm::vec3 tangent2, bitangent2;
						// triangle 1
						// ----------
						glm::vec3 edge1 = pos2 - pos1;
						glm::vec3 edge2 = pos3 - pos1;
						glm::vec2 deltaUV1 = uv2 - uv1;
						glm::vec2 deltaUV2 = uv3 - uv1;

						GLfloat f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

						tangent1.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
						tangent1.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
						tangent1.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
						tangent1 = glm::normalize(tangent1);

						bitangent1.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
						bitangent1.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
						bitangent1.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
						bitangent1 = glm::normalize(bitangent1);

						// triangle 2
						// ----------
						edge1 = pos3 - pos1;
						edge2 = pos4 - pos1;
						deltaUV1 = uv3 - uv1;
						deltaUV2 = uv4 - uv1;

						f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

						tangent2.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
						tangent2.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
						tangent2.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
						tangent2 = glm::normalize(tangent2);


						bitangent2.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
						bitangent2.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
						bitangent2.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
						bitangent2 = glm::normalize(bitangent2);
						normal[i] = 2;
						tangent[i] = tangent1;
						vertex[i++] = byte4(x, y + 1, z, top + 128);
						normal[i] = 2;
						tangent[i] = tangent1;
						vertex[i++] = byte4(x, y + 1, z + 1, top + 128);
						normal[i] = 2;
						tangent[i] = tangent1;
						vertex[i++] = byte4(x + 1, y + 1, z, top + 128);
						normal[i] = 2;
						tangent[i] = tangent2;
						vertex[i++] = byte4(x + 1, y + 1, z, top + 128);
						normal[i] = 2;
						tangent[i] = tangent2;
						vertex[i++] = byte4(x, y + 1, z + 1, top + 128);
						normal[i] = 2;
						tangent[i] = tangent2;
						vertex[i++] = byte4(x + 1, y + 1, z + 1, top + 128);
					}
					vis = true;
				}
			}
		}

		// View from negative z

		for (int x = 0; x < CX; x++) {
			for (int z = CZ - 1; z >= 0; z--) {
				for (int y = 0; y < CY; y++) {
					if (isblocked(x, y, z, x, y, z - 1)) {
						vis = false;
						continue;
					}
					if (blk[x][y][z] == 8)
						continue;
					uint8_t top = blk[x][y][z];
					uint8_t bottom = blk[x][y][z];
					uint8_t side = blk[x][y][z];

					// Grass block has dirt sides and bottom
					if (top == 2) {
						bottom = 3;
						side = 9;
						// Wood blocks have rings on top and bottom
					}
					else if (top == 5) {
						top = bottom = 12;
					}

					if (vis && y != 0 && blk[x][y][z] == blk[x][y - 1][z]) {
						vertex[i - 5] = byte4(x, y + 1, z, side);
						vertex[i - 3] = byte4(x, y + 1, z, side);
						vertex[i - 2] = byte4(x + 1, y + 1, z, side);
						merged++;
					}
					else {
						glm::vec3 pos1(x, y + 1, z);
						glm::vec3 pos2(x, y, z);
						glm::vec3 pos3(x + 1, y, z);
						glm::vec3 pos4(x + 1, y + 1, z);

						glm::vec2 uv1((0 + side) / 16.0, 1);
						glm::vec2 uv2((0 + side) / 16.0, 0);
						glm::vec2 uv3((1 + side) / 16.0, 0);
						glm::vec2 uv4((1 + side) / 16.0, 1);
						glm::vec3 nm(0.0f, 0.0f ,-1.0f);

						// calculate tangent/bitangent vectors of both triangles
						glm::vec3 tangent1, bitangent1;
						glm::vec3 tangent2, bitangent2;
						// triangle 1
						// ----------
						glm::vec3 edge1 = pos2 - pos1;
						glm::vec3 edge2 = pos3 - pos1;
						glm::vec2 deltaUV1 = uv2 - uv1;
						glm::vec2 deltaUV2 = uv3 - uv1;

						GLfloat f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

						tangent1.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
						tangent1.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
						tangent1.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
						tangent1 = glm::normalize(tangent1);

						bitangent1.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
						bitangent1.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
						bitangent1.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
						bitangent1 = glm::normalize(bitangent1);

						// triangle 2
						// ----------
						edge1 = pos3 - pos1;
						edge2 = pos4 - pos1;
						deltaUV1 = uv3 - uv1;
						deltaUV2 = uv4 - uv1;

						f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

						tangent2.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
						tangent2.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
						tangent2.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
						tangent2 = glm::normalize(tangent2);


						bitangent2.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
						bitangent2.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
						bitangent2.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
						bitangent2 = glm::normalize(bitangent2);
						normal[i] = -3;
						tangent[i] = tangent1;
						vertex[i++] = byte4(x, y, z, side);
						normal[i] = -3;
						tangent[i] = tangent1;
						vertex[i++] = byte4(x, y + 1, z, side);
						normal[i] = -3;
						tangent[i] = tangent1;
						vertex[i++] = byte4(x + 1, y, z, side);
						normal[i] = -3;
						tangent[i] = tangent2;
						vertex[i++] = byte4(x, y + 1, z, side);
						normal[i] = -3;
						tangent[i] = tangent2;
						vertex[i++] = byte4(x + 1, y + 1, z, side);
						normal[i] = -3;
						tangent[i] = tangent2;
						vertex[i++] = byte4(x + 1, y, z, side);
					}
					vis = true;
				}
			}
		}

		// View from positive z

		for (int x = 0; x < CX; x++) {
			for (int z = 0; z < CZ; z++) {
				for (int y = 0; y < CY; y++) {
					if (isblocked(x, y, z, x, y, z + 1)) {
						vis = false;
						continue;
					}
					if (blk[x][y][z] == 8)
						continue;
					uint8_t top = blk[x][y][z];
					uint8_t bottom = blk[x][y][z];
					uint8_t side = blk[x][y][z];

					// Grass block has dirt sides and bottom
					if (top == 2) {
						bottom = 3;
						side = 9;
						// Wood blocks have rings on top and bottom
					}
					else if (top == 5) {
						top = bottom = 12;
					}

					if (vis && y != 0 && blk[x][y][z] == blk[x][y - 1][z]) {
						vertex[i - 4] = byte4(x, y + 1, z + 1, side);
						vertex[i - 3] = byte4(x, y + 1, z + 1, side);
						vertex[i - 1] = byte4(x + 1, y + 1, z + 1, side);
						merged++;
					}
					else {
						glm::vec3 pos1(x + 1, y, z + 1);
						glm::vec3 pos2(x, y, z + 1);
						glm::vec3 pos3(x, y + 1, z + 1);
						glm::vec3 pos4(x + 1, y + 1, z + 1);

						glm::vec2 uv1((1 + side) / 16.0, 0);
						glm::vec2 uv2((0 + side) / 16.0, 0);
						glm::vec2 uv3((0 + side) / 16.0, 1);
						glm::vec2 uv4((1 + side) / 16.0, 1);
						glm::vec3 nm(0.0f, 0.0f, 1.0f);

						// calculate tangent/bitangent vectors of both triangles
						glm::vec3 tangent1, bitangent1;
						glm::vec3 tangent2, bitangent2;
						// triangle 1
						// ----------
						glm::vec3 edge1 = pos2 - pos1;
						glm::vec3 edge2 = pos3 - pos1;
						glm::vec2 deltaUV1 = uv2 - uv1;
						glm::vec2 deltaUV2 = uv3 - uv1;

						GLfloat f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

						tangent1.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
						tangent1.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
						tangent1.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
						tangent1 = glm::normalize(tangent1);

						bitangent1.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
						bitangent1.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
						bitangent1.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
						bitangent1 = glm::normalize(bitangent1);

						// triangle 2
						// ----------
						edge1 = pos3 - pos1;
						edge2 = pos4 - pos1;
						deltaUV1 = uv3 - uv1;
						deltaUV2 = uv4 - uv1;

						f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

						tangent2.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
						tangent2.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
						tangent2.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
						tangent2 = glm::normalize(tangent2);


						bitangent2.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
						bitangent2.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
						bitangent2.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
						bitangent2 = glm::normalize(bitangent2);
						normal[i] = 3;
						tangent[i] = tangent1;
						vertex[i++] = byte4(x, y, z + 1, side);
						normal[i] = 3;
						tangent[i] = tangent1;
						vertex[i++] = byte4(x + 1, y, z + 1, side);
						normal[i] = 3;
						tangent[i] = tangent1;
						vertex[i++] = byte4(x, y + 1, z + 1, side);
						normal[i] = 3;
						tangent[i] = tangent2;
						vertex[i++] = byte4(x, y + 1, z + 1, side);
						normal[i] = 3;
						tangent[i] = tangent2;
						vertex[i++] = byte4(x + 1, y, z + 1, side);
						normal[i] = 3;
						tangent[i] = tangent2;
						vertex[i++] = byte4(x + 1, y + 1, z + 1, side);
					}
					vis = true;
				}
			}
		}

		changed = false;
		elements = i;

		// If this chunk is empty, no need to allocate a chunk slot.
		if (!elements)
			return;

		// If we don't have an active slot, find one
		if (chunk_slot[slot] != this) {
			int lru = 0;
			for (int i = 0; i < CHUNKSLOTS; i++) {
				// If there is an empty slot, use it
				if (!chunk_slot[i]) {
					lru = i;
					break;
				}
				// Otherwise try to find the least recently used slot
				if (chunk_slot[i]->lastused < chunk_slot[lru]->lastused)
					lru = i;
			}

			// If the slot is empty, create a new VBO
			if (!chunk_slot[lru]) {
				glGenBuffers(1, &vbo);
				glGenBuffers(1, &vbo_normal);
				glGenBuffers(1, &vbo_tangent);
				glGenBuffers(1, &vbo_bitangent);
				// Otherwise, steal it from the previous slot owner
			}
			else {
				vbo = chunk_slot[lru]->vbo;
				vbo_normal = chunk_slot[lru]->vbo_normal;
				vbo_tangent = chunk_slot[lru]->vbo_tangent;
				vbo_bitangent = chunk_slot[lru]->vbo_bitangent;
				chunk_slot[lru]->changed = true;
			}

			slot = lru;
			chunk_slot[slot] = this;
		}

		// Upload vertices

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, i * sizeof *vertex, vertex, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_normal);
		glBufferData(GL_ARRAY_BUFFER, i * sizeof *normal, normal, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_tangent);
		glBufferData(GL_ARRAY_BUFFER, i * sizeof *tangent, tangent, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_bitangent);
		glBufferData(GL_ARRAY_BUFFER, i * sizeof *bitangent, bitangent, GL_STATIC_DRAW);
	}

	void render() {
		if (changed)
			update();

		lastused = now;

		if (!elements)
			return;

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glEnableVertexAttribArray(attribute_coord);
		glVertexAttribPointer(attribute_coord, 4, GL_BYTE, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_normal);
		glEnableVertexAttribArray(normal_coord);
		glVertexAttribPointer(normal_coord, 1, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_tangent);
		glEnableVertexAttribArray(tangent_coord);
		glVertexAttribPointer(tangent_coord, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_bitangent);
		glEnableVertexAttribArray(bitangent_coord);
		glVertexAttribPointer(bitangent_coord, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, elements);
	}
};

struct superchunk {
	chunk *c[SCX][SCY][SCZ];
	time_t seed;

	GLuint water_vao, water_vbo, water_ibo, water_texture;

	superchunk() {
		seed = time(NULL);
		for (int x = 0; x < SCX; x++)
			for (int y = 0; y < SCY; y++)
				for (int z = 0; z < SCZ; z++)
					c[x][y][z] = new chunk(x - SCX / 2, y - SCY / 2, z - SCZ / 2);

		for (int x = 0; x < SCX; x++)
			for (int y = 0; y < SCY; y++)
				for (int z = 0; z < SCZ; z++) {
					if (x > 0)
						c[x][y][z]->left = c[x - 1][y][z];
					if (x < SCX - 1)
						c[x][y][z]->right = c[x + 1][y][z];
					if (y > 0)
						c[x][y][z]->below = c[x][y - 1][z];
					if (y < SCY - 1)
						c[x][y][z]->above = c[x][y + 1][z];
					if (z > 0)
						c[x][y][z]->front = c[x][y][z - 1];
					if (z < SCZ - 1)
						c[x][y][z]->back = c[x][y][z + 1];
				}
	}

	uint8_t get(int x, int y, int z) const {
		int cx = (x + CX * (SCX / 2)) / CX;
		int cy = (y + CY * (SCY / 2)) / CY;
		int cz = (z + CZ * (SCZ / 2)) / CZ;

		if (cx < 0 || cx >= SCX || cy < 0 || cy >= SCY || cz <= 0 || cz >= SCZ)
			return 0;

		return c[cx][cy][cz]->get(x & (CX - 1), y & (CY - 1), z & (CZ - 1));
	}

	void set(int x, int y, int z, uint8_t type) {
		int cx = (x + CX * (SCX / 2)) / CX;
		int cy = (y + CY * (SCY / 2)) / CY;
		int cz = (z + CZ * (SCZ / 2)) / CZ;

		if (cx < 0 || cx >= SCX || cy < 0 || cy >= SCY || cz <= 0 || cz >= SCZ)
			return;

		c[cx][cy][cz]->set(x & (CX - 1), y & (CY - 1), z & (CZ - 1), type);
	}

	void water_render(const glm::mat4 &pv, const int &whichprogram) {
		glBindVertexArray(water_vao);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawElements(GL_TRIANGLES, SCZ * CZ * SPLIT * SCX * CX * SPLIT * 2 * 3, GL_UNSIGNED_INT, (GLvoid*)0);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBindVertexArray(0);
	}

	void water_init() {
		glGenVertexArrays(1, &water_vao);
		glGenBuffers(1, &water_vbo);
		glGenBuffers(1, &water_ibo);

		water_program = create_program("glcraft_water.vert", "glcraft_water.frag");
		glUseProgram(water_program);
		uniform_model = get_uniform(water_program, "model");
		uniform_view = get_uniform(water_program, "view");
		uniform_projection = get_uniform(water_program, "projection");

		glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		// Set up waves
		// Directional
		//w1.A *= 120; // 120
		//w1.w *= 1.f / 150.f;
		//w1.phi = 50.f * WAVE_SPEED * w1.w;
		//w1.D = glm::normalize(glm::vec2(.5f, .5f));
		w1.A *= 1.1f;
		w1.w *= 0.8f;
		w1.phi = WAVE_SPEED * w1.w;
		w1.D = glm::normalize(glm::vec2(.5f, .5f));
		//w1.A *= 6; // 120
		//w1.w *= 10.f / 600.f;
		//w1.phi = 50.f * WAVE_SPEED * w1.w;
		//w1.D = glm::normalize(glm::vec2(.5f, .5f));
		// Circular 1

		//w2.A *= 11; // 110
		//w2.w = 1.f / 13.5f;
		//w2.phi = 500 * WAVE_SPEED * w2.w;
		//w2.C = glm::vec2(40.f, 40.f);
		w2.A *= 0.6f;
		w2.w *= 0.8f;
		w2.phi = WAVE_SPEED * w2.w;
		w2.D = glm::normalize(glm::vec2(.2f, .4f));
		// Circular 2
		//w3.A *= 13; // 130
		//w3.w = 1.f / 20.f;
		//w3.phi = 300 * WAVE_SPEED * w3.w;
		//w3.C = glm::vec2(-40.f, -40.f);
		w3.D = glm::normalize(glm::vec2(.1f, .9f));
		sendWaves();
	}

	void sendWaves() {
		set_uniform(water_program, "w1.A", w1.A);
		set_uniform(water_program, "w1.C", w1.C);
		set_uniform(water_program, "w1.D", w1.D);
		set_uniform(water_program, "w1.w", w1.w);
		set_uniform(water_program, "w1.phi", w1.phi);

		set_uniform(water_program, "w2.A", w2.A);
		set_uniform(water_program, "w2.C", w2.C);
		set_uniform(water_program, "w2.D", w2.D);
		set_uniform(water_program, "w2.w", w2.w);
		set_uniform(water_program, "w2.phi", w2.phi);

		set_uniform(water_program, "w3.A", w3.A);
		set_uniform(water_program, "w3.C", w3.C);
		set_uniform(water_program, "w3.D", w3.D);
		set_uniform(water_program, "w3.w", w3.w);
		set_uniform(water_program, "w3.phi", w3.phi);
	}

	void water_generate() {
		const int points_x_n = SCX * CX * SPLIT + 1;
		const int points_z_n = SCZ * CZ * SPLIT + 1;
		vertexFormat vertex[points_x_n][points_z_n];
		GLuint index[points_x_n - 1][points_z_n - 1][2][3];

		int vertex_size = points_x_n * points_z_n;
		int index_size = (points_x_n - 1)*(points_z_n - 1) * 2 * 3;

		//double lx = -0.5f, rx = 0.5f;
		//double lz = -0.5f, rz = 0.5f;
		int lx = (-SCX / 2) * CX;
		int lz = (-SCZ / 2) * CZ;
		double dx = 1.0f / SPLIT;
		double dz = 1.0f / SPLIT;

		double cz = lz;
		double cy = -65.5f;
		for (int gz = 0; gz < points_z_n; gz++) {
			double cx = lx;
			for (int gx = 0; gx < points_x_n; gx++) {
				vertex[gz][gx] = vertexFormat(cx, cy, cz, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
				cx += dx;
			}
			cz += dz;
		}

		//row points - n = CX * 16
		for (int tz = 0; tz < points_z_n - 1; tz++) {
			for (int tx = 0; tx < points_x_n - 1; tx++) {
				index[tz][tx][0][0] = tz * points_x_n + tx;
				index[tz][tx][0][1] = tz * points_x_n + tx + 1;
				index[tz][tx][0][2] = (tz + 1) * points_x_n + tx;

				index[tz][tx][1][0] = tz * points_x_n + tx + 1;
				index[tz][tx][1][1] = (tz + 1) * points_x_n + tx;
				index[tz][tx][1][2] = (tz + 1) * points_x_n + tx + 1;
			}
		}

		// Create buffers to hold the mesh data

		glBindVertexArray(water_vao);
		glBindBuffer(GL_ARRAY_BUFFER, water_vao);
		glBufferData(GL_ARRAY_BUFFER, vertex_size * sizeof(vertexFormat), &vertex[0], GL_STATIC_DRAW);

		// Configure the vertex attribute pointers
		// Send vertex positions to attrib pointer 0
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertexFormat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		// Send vertex normals to attrib pointer 1
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertexFormat), (GLvoid*)(sizeof(GLfloat) * 3));
		glEnableVertexAttribArray(1);
		// Send vertex uv texcoords to attrib pointer 2
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertexFormat), (GLvoid*)(sizeof(GLfloat) * 6));
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, water_ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_size * sizeof(GLuint), &index[0], GL_STATIC_DRAW);

		// Clean up
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}


	void render(const glm::mat4 &pv, const glm::mat4 &lightSpaceMatrix, const int &whichprogram) {
		float ud = 1 >> 32;
		int ux = -1;
		int uy = -1;
		int uz = -1;

		for (int x = 0; x < SCX; x++) {
			for (int y = 0; y < SCY; y++) {
				for (int z = 0; z < SCZ; z++) {
					glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(c[x][y][z]->ax * CX, c[x][y][z]->ay * CY, c[x][y][z]->az * CZ));
					glm::mat4 mvp = pv * model;
					glm::mat4 LSM = lightSpaceMatrix * model;

					// Is this chunk on the screen?
					glm::vec4 center = mvp * glm::vec4(CX / 2, CY / 2, CZ / 2, 1);

					float d = glm::length(center);
					center.x /= center.w;
					center.y /= center.w;

					// If it is behind the camera, don't bother drawing it
					if (center.z < -CY / 2)
						continue;

					// If it is outside the screen, don't bother drawing it
					if (fabsf(center.x) > 1 + fabsf(CY * 2 / center.w) || fabsf(center.y) > 1 + fabsf(CY * 2 / center.w))
						continue;

					// If this chunk is not initialized, skip it
					if (!c[x][y][z]->initialized) {
						// But if it is the closest to the camera, mark it for initialization
						if (ux < 0 || d < ud) {
							ud = d;
							ux = x;
							uy = y;
							uz = z;
						}
						continue;
					}
					GLint uniform_model = glGetUniformLocation(program, "model");
					glUniformMatrix4fv(uniform_model, 1, GL_FALSE, glm::value_ptr(model));
					if (whichprogram == 0) {
						glUniformMatrix4fv(uniform_mvp, 1, GL_FALSE, glm::value_ptr(mvp));
						glUniformMatrix4fv(uniform_lightspacematrix_normal, 1, GL_FALSE, glm::value_ptr(LSM));
					}else
					if (whichprogram == 1)
						glUniformMatrix4fv(uniform_lightspacematrix_depth, 1, GL_FALSE, glm::value_ptr(LSM));

					c[x][y][z]->render();
				}
			}
		}

		if (ux >= 0) {
			c[ux][uy][uz]->noise();
			if (c[ux][uy][uz]->left)
				c[ux][uy][uz]->left->noise();
			if (c[ux][uy][uz]->right)
				c[ux][uy][uz]->right->noise();
			if (c[ux][uy][uz]->below)
				c[ux][uy][uz]->below->noise();
			if (c[ux][uy][uz]->above)
				c[ux][uy][uz]->above->noise();
			if (c[ux][uy][uz]->front)
				c[ux][uy][uz]->front->noise();
			if (c[ux][uy][uz]->back)
				c[ux][uy][uz]->back->noise();
			c[ux][uy][uz]->initialized = true;
		}
	}
};

static superchunk *world;

static void update_vectors() {
	fforward.x = sinf(angle.x);
	fforward.y = 0;
	fforward.z = cosf(angle.x);

	rright.x = -cosf(angle.x);
	rright.y = 0;
	rright.z = sinf(angle.x);

	lookat.x = sinf(angle.x) * cosf(angle.y);
	lookat.y = sinf(angle.y);
	lookat.z = cosf(angle.x) * cosf(angle.y);

	up = glm::cross(rright, lookat);
}

static float fract(float value) {
	float f = value - floorf(value);
	if (f > 0.5)
		return 1 - f;
	else
		return f;
}



void checkError(unsigned int shader, const bool type) {
	int success;
	char infoLog[512];
	if (type == false) {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::cout << infoLog << std::endl;
		}
	}
	else
		if (type == true) {
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(shader, 512, NULL, infoLog);
				std::cout << infoLog << std::endl;
			}
		}
}

GLuint create_program(const char *vertexfile, const char *fragmentfile) {
	std::string vertexCode, fragmentCode;
	std::ifstream vertexFile, fragmentFile;
	vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		vertexFile.open(vertexfile);
		fragmentFile.open(fragmentfile);

		std::stringstream vertexStream, fragmentStream;
		vertexStream << vertexFile.rdbuf();
		fragmentStream << fragmentFile.rdbuf();
		vertexFile.close();
		fragmentFile.close();
		vertexCode = vertexStream.str();
		fragmentCode = fragmentStream.str();
	}
	catch (std::ifstream::failure) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULY_READ" << std::endl;
		return 0;
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vShaderCode, NULL);
	glCompileShader(vertexShader);
	checkError(vertexShader, false);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
	glCompileShader(fragmentShader);
	checkError(fragmentShader, false);
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	checkError(shaderProgram, true);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	vertexShader = -1;
	fragmentShader = -1;

	return shaderProgram;
}

unsigned int loadTexture(char const * path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT); // for this tutorial: use GL_CLAMP_TO_EDGE to prevent semi-transparent borders. Due to interpolation it takes texels from next repeat 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

int main()
{
	cout << "Desert? (1/0)" << endl;
	cin >> allDesert;
	cout << "Hills? (1/0)" << endl;
	cin >> allHills;
	int posx, posy;
	cout << "position (x z) recomand: (-10, 10) (40, 10)" << endl;
	cin >> posx >> posy;
	for (int x = 0; x < SCX; x++)
		for (int z = 0; z < SCZ; z++)
		{
			ChunkColumnStorage chunk1 = c->Generate(x + posx, z + posy, GeneratorSettings());
			for (int i = 0; i < 16; i++)
				for (int j = 0; j < 16; j++)
					for (int y = 0; y < CY*SCY; y++)
						blocks[x*CX + i][y][z*CZ + j] = chunk1(i, y, j).Id;
		}
	delete c;
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

														 // glfw window creation
														 // --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "GLCraft", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	// sky
	Sky sky;
	sky.getReadySky();
	// build and compile our shader zprogram
	// ------------------------------------
	program = create_program("glcraft.vert", "glcraft.frag");
	depthProgram = create_program("simple.vert", "simple.frag");
	depthTestProgram = create_program("simpleTexture.vert", "simpleTexture.frag");
//itemProgram
	itemProgram = create_program("item.vs", "item.fs");

	if (program == 0 || depthProgram == 0)
		return 0;
//item
	srand(time(0));
	glUseProgram(itemProgram);
	unsigned int item_VBO, item_VAO, item_EBO, item_VAO2, item_VBO2, item_EBO2, item_VAO3, item_VBO3, item_EBO3;
	glGenVertexArrays(1, &item_VAO);
	glGenBuffers(1, &item_VBO);
	glGenBuffers(1, &item_EBO);


	unsigned int item_texture;
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &item_texture);

	glBindTexture(GL_TEXTURE_2D, item_texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
												// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // Use GL_NEAREST_MIPMAP_LINEAR if you want to use mipmaps
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// load image, create texture and generate mipmaps
	stbi_set_flip_vertically_on_load(false);
	int item_width, item_height, item_nrChannels;
	// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
	unsigned char *item_data = stbi_load("test2.png", &item_width, &item_height, &item_nrChannels, 0);
	if (item_data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, item_width, item_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, item_data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(item_data);

	item_mvp = get_uniform(itemProgram, "itemmvp");
	glBindVertexArray(item_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, item_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Flowervertices), Flowervertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, item_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glGenVertexArrays(1, &item_VAO2);
	glGenBuffers(1, &item_VBO2);
	glGenBuffers(1, &item_EBO2);

	glBindVertexArray(item_VAO2);

	glBindBuffer(GL_ARRAY_BUFFER, item_VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Grassvertices), Grassvertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, item_EBO2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glGenVertexArrays(1, &item_VAO3);
	glGenBuffers(1, &item_VBO3);
	glGenBuffers(1, &item_EBO3);

	glBindVertexArray(item_VAO3);

	glBindBuffer(GL_ARRAY_BUFFER, item_VBO3);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Othervertices), Othervertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, item_EBO3);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
//item end

	glUseProgram(depthProgram);
	uniform_lightspacematrix_depth = get_uniform(depthProgram, "lightSpaceMatrix");

	glUseProgram(program);
	uniform_mvp = get_uniform(program, "mvp");
	uniform_viewpos = get_uniform(program, "viewPos");
	uniform_lightspacematrix_normal = get_uniform(program, "lightSpaceMatrix");
	uniform_texture = get_uniform(program, "texture");
	uniform_shadow = get_uniform(program, "shadow");
	uniform_dirlight.direction = get_uniform(program, "dirlight.direction");
	uniform_dirlight.ambient = get_uniform(program, "dirlight.ambient");
	uniform_dirlight.diffuse = get_uniform(program, "dirlight.diffuse");
	uniform_dirlight.specular = get_uniform(program, "dirlight.specular");

	uniform_dirlight2.direction = get_uniform(itemProgram, "dirlight.direction");
	uniform_dirlight2.ambient = get_uniform(itemProgram, "dirlight.ambient");
	uniform_dirlight2.diffuse = get_uniform(itemProgram, "dirlight.diffuse");
	uniform_dirlight2.specular = get_uniform(itemProgram, "dirlight.specular");

	dirlight.ambient = glm::vec3(0.1f);
	dirlight.diffuse = glm::vec3(0.8f);
	dirlight.specular = glm::vec3(.1f);

	//if (uniform_mvp == -1 || uniform_viewpos == -1 ||
	//	uniform_dirlight.direction == -1 || uniform_dirlight.ambient == -1 ||
	//	uniform_dirlight.diffuse == -1 || uniform_dirlight.specular == -1)
	//	return 0;

	/* Create and upload the texture */

	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	/*glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textures.width, textures.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textures.pixel_data);
	glGenerateMipmap(GL_TEXTURE_2D);*/
	int width, height, nrChannels;
	// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
	unsigned char *data = stbi_load("texture.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	//glActiveTexture(GL_TEXTURE2);
	/*glGenTextures(1, &normalMap);
	glBindTexture(GL_TEXTURE_2D, normalMap);
	int width2, height2, nrChannels2;
	data = stbi_load("normaltextures.png", &width2, &height2, &nrChannels2, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width2, height2, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);*/

	/* Create the world */

	world = new superchunk;

	world->water_init();
	world->water_generate();

	position = glm::vec3(0, CY + 1, 0);
	angle = glm::vec3(0, -0.5, 0);
	update_vectors();

	/* Create a VBO for the cursor */

	glGenBuffers(1, &cursor_vbo);

	/* OpenGL settings that do not change while running this program */

	glUseProgram(program);
	glUniform1i(uniform_texture, 0);
	glUniform1i(uniform_shadow, 1);
	glClearColor(0.6, 0.8, 1.0, 0.0);
	glEnable(GL_CULL_FACE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // Use GL_NEAREST_MIPMAP_LINEAR if you want to use mipmaps
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glPolygonOffset(1, 1);

	glEnableVertexAttribArray(attribute_coord);
	glEnableVertexAttribArray(normal_coord);
	glEnableVertexAttribArray(tangent_coord);
	glEnableVertexAttribArray(bitangent_coord);

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	glEnableVertexAttribArray(0);

	//create depth texture
	GLuint depthMapFBO;
	glGenFramebuffers(1, &depthMapFBO);
	const GLuint SHADOW_WIDTH = 9000, SHADOW_HEIGHT = 9000;
	GLuint depthMap;
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	GLfloat borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
//item begin
	
	for (int x = 0; x < SCX * CX; x++) {
		for (int z = 0; z < SCZ * CZ; z++) {
			int maxHeight = 0;
			for (int y = 1; y < SCY *CY; y++) {
				if (blocks[x][y][z] == 0) {
					if (blocks[x][y - 1][z] != 8) {
						maxHeight = y;
					}
				break;
			}
		}
			int select = rand() % 800;
			if (select <= 5 && select >= 0) {
				isGround[x][z] = maxHeight;
				itemType[x][z] = rand() % 3;
			}
		}
	}
	/*
	for (int x = 127; x < 128; x++) {
		for (int z = 127; z < 128; z++) {
			int maxHeight = 0;
			for (int y = 1; y < SCY *CY; y++) {
				if (blocks[x][y][z] == 0) {
					//if (blocks[x][y - 1][z] != 8) {
					maxHeight = y;
					//}
					break;
				}
			}
			//int select = rand() % 100;
			//if (select <= 5 && select >= 0) {
			isGround[x][z] = maxHeight;
			itemType[x][z] = rand() % 3;
			//}
			//if (flag) break;
		}
		//if (flag) break;
	}
	*/
//item end

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// input
		// -----
		processInput(window);

		// pass projection matrix to shader (note that in this case it could change every frame)
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 model = glm::mat4(1.0f);
		// camera/view transformation
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 pv = projection * view;
		// render sky
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		glm::mat4 matrix = projection * glm::mat4(glm::mat3(view));
		sky.renderSky(matrix);

		glBindVertexArray(VAO);
		glUseProgram(program);
		glUniform3f(uniform_viewpos, camera.Position.x, camera.Position.y, camera.Position.z);

		float now_time = sky.get_time_of_day();
		if (now_time >= 0.25f && now_time <= 0.91f)		// day
		{
			float tmp_angle = ((now_time - 0.25f) / 0.66f) * 3.1415926535898f;
			dirlight.direction = glm::vec3(-cos(tmp_angle) / sqrt(2.0f), -sin(tmp_angle), -cos(tmp_angle) / sqrt(2.0f));
			if (now_time >= 0.85f && now_time <= 0.91f)
			{
				dirlight.diffuse = glm::vec3(0.8f * ((0.91f - now_time) / 0.06f));
				dirlight.specular = glm::vec3(0.1f * ((0.91f - now_time) / 0.06f));
			}
			else if (now_time >= 0.25f && now_time <= 0.31f)
			{
				dirlight.diffuse = glm::vec3(0.8f * ((now_time - 0.25f) / 0.06f));
				dirlight.specular = glm::vec3(0.1f * ((now_time - 0.25f) / 0.06f));
			}
		}
		else											// night
		{
			dirlight.direction = glm::vec3(0.0f, 0.0f, 0.0f);
		}
		dirlight.UniformSet(uniform_dirlight);
		glm::mat4 lightProjection = glm::ortho(-100.0f, 100.0f, -100.0f, 100.0f, 0.1f, 80.0f);
		glm::vec3 lightPos = glm::normalize(-dirlight.direction);
		lightPos *= 50;
		glm::vec3 lookAtCenter = camera.Front;
		lookAtCenter *= 50;
		lookAtCenter += camera.Position;
		lightPos += lookAtCenter;
		glm::mat4 lightView = glm::lookAt(lightPos, lookAtCenter, glm::vec3(0, 1, 0));
		glm::mat4 lightSpaceMatrix = lightProjection * lightView;
		set_uniform(program, "lightDir", dirlight.direction);
		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
		glClear(GL_DEPTH_BUFFER_BIT);
		glUseProgram(depthProgram);
		glEnable(GL_DEPTH_TEST);
		//glEnable(GL_CULL_FACE);
		glDisable(GL_BLEND);
		glDisable(GL_POLYGON_OFFSET_FILL);
		//glCullFace(GL_FRONT);

		world->render(lightSpaceMatrix, lightSpaceMatrix, 1);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
		glClear(GL_DEPTH_BUFFER_BIT);
		glUseProgram(program);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_POLYGON_OFFSET_FILL);
		glDisable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		//depth texture test
		/*glUseProgram(depthTestProgram);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, depthMap);
		GLuint VAO, VBO, EBO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		GLfloat vertices[] = {
		-1, -1,  0,  0,  0,
		1, -1,  0,  1,  0,
		-1,  1,  0,  0,  1,
		1,  1,  0,  1,  1
		};
		GLuint indices[] = {
		0, 1, 2, 1, 2, 3
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
		glBindVertexArray(0);*/

		/* Then draw chunks */

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, depthMap);
		
		world->render(pv, lightSpaceMatrix, 0);

		

		/* Draw a cross in the center of the screen */

		float cross[4][4] = {
			{ -0.02, 0, 0, 13 },
			{ +0.02, 0, 0, 13 },
			{ 0, -0.025, 0, 13 },
			{ 0, +0.025, 0, 13 },
		};
		glBindBuffer(GL_ARRAY_BUFFER, cursor_vbo);
		glDisable(GL_DEPTH_TEST);
		glm::mat4 one(1);
		glUniformMatrix4fv(uniform_mvp, 1, GL_FALSE, glm::value_ptr(one));
		glBufferData(GL_ARRAY_BUFFER, sizeof cross, cross, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(attribute_coord, 4, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_LINES, 0, 4);

		glUseProgram(water_program);
		glUniformMatrix4fv(uniform_projection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniform_view, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(uniform_model, 1, GL_FALSE, glm::value_ptr(model));
		if (firstRender)
		{
			firstRender = false;
			firstRenderTime = glfwGetTime();
		}
		GLfloat dt = (GLfloat)glfwGetTime() - (GLfloat)firstRenderTime;
		set_uniform(water_program, "lightPos", lightPos);
		set_uniform(water_program, "eyePos", camera.Position);
		set_uniform(water_program, "dt", dt);
		set_uniform(water_program, "damp", DAMPING);
		set_uniform(water_program, "Q", STEEPNESS);
		set_uniform(water_program, "E", 3.1415926535898f);
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_POLYGON_OFFSET_FILL);

		world->water_render(pv, water_program);
//item begin
		glm::mat4 mvp;
		int tmpx = camera.Position.x;
		int tmpz = camera.Position.z;
		int tmpy = camera.Position.y;
		//glm::mat4 tmodel = glm::translate(glm::mat4(1.0f), glm::vec3(camera.Position.x, camera.Position.y, camera.Position.z));
		//glm::mat4 tmvp = pv * tmodel;
		//std::cout << tmpx << "   " << tmpy << "  " << tmpz << std::endl;
		int beginX = tmpx + 74 < 0 ? 0 : tmpx + 74;
		int beginZ = tmpz + 74 < 0 ? 0 : tmpz + 74;
		int endX = tmpx + 180 >= SCX * CX ? SCX * CX : tmpx + 180;
		int endZ = tmpz + 180 >= SCZ * CZ ? SCZ * CZ : tmpz + 180;
		for (int x = 0; x < 512; x++) {
			for (int z = 0; z < 512; z++) {
				if (isGround[x][z] != 0) {
					glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(x - 256, isGround[x][z] - 128, z - 256));
					mvp = pv * model;
					glUseProgram(itemProgram);
					dirlight.UniformSet(uniform_dirlight2);
					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, item_texture);
					if (itemType[x][z] == 0)
						glBindVertexArray(item_VAO);
					else if (itemType[x][z] == 1)
						glBindVertexArray(item_VAO2);
					else if(itemType[x][z] == 2)
						glBindVertexArray(item_VAO3);
					//std::cout << itemType[x][z] << std::endl;
					glUniformMatrix4fv(item_mvp, 1, GL_FALSE, glm::value_ptr(mvp));
					glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
					glBindVertexArray(0);
					//std::cout << "true" << std::endl;
					//std::cout << x << " " << isGround[x][z] << " " << z << std::endl;
					//glClear(GL_DEPTH_BUFFER_BIT);
				}

				//if (flag) break;
			}
			//if (flag) break;
		}
		//glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

		//mvp = pv * glm::translate(glm::mat4(1.0f), glm::vec3(10, -63, 0));
		//std::cout << flag << std::endl;
		//glUniformMatrix4fv(item_mvp, 1, GL_FALSE, glm::value_ptr(one)); 

		//glDrawArrays(GL_TRIANGLES, 0, sizeof(itemvertex));
		//std::cout << sizeof(itemvertex) << std::endl;

		glBindTexture(GL_TEXTURE_2D, texture);
//item end


		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}