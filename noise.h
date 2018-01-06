#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/noise.hpp>
#include <vector>
using std::vector;
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

#include "time.h"

struct UniformRNG
{
	// https://en.wikipedia.org/wiki/Linear_congruential_generator
	// MMIX by Donald Knuth
private:
	static const unsigned long _multiplier = 6364136223846793005;
	static const unsigned long _increment = 1442695040888963407;

	unsigned long _state;
	unsigned int _count;

public:
	UniformRNG(unsigned long state)
	{
		struct tm *local;
		time_t t;
		t = time(NULL);
		local = localtime(&t);
		_count = 101;
		if (state == 0)
		{
			//auto time = DateTime.Now;
			auto seed = (unsigned long)(local->tm_mday << 25 | local->tm_hour << 20 | local->tm_min << 14 | local->tm_sec << 8 | clock());
			for (int i = 0; i < 4; ++i)
			{
				seed = seed * _multiplier + _increment;
			}

			_state = seed;
		}
		else
		{
			_state = state;
		}
	}

	int NextInt32()
	{
		return (int)Next();
	}

	unsigned int NextUInt32()
	{
		return Next();
	}

	long NextInt64()
	{
		Next();
		return (long)_state;
	}

	unsigned long NextUInt64()
	{
		Next();
		return _state;
	}

	float NextSingle()
	{
		return Next() * 2.3283064365386962890625e-10f;
	}

	double NextDouble()
	{
		auto t = Next();
		return (((unsigned long)t << 32) | Next()) * 5.4210108624275221700372640043497e-20;
	}

	int Uniform(int a, int b)
	{
		return a == b ? a : (int)(Next() % (b - a) + a);
	}

	unsigned int Uniform(unsigned int a, unsigned int b)
	{
		return a == b ? a : Next() % (b - a) + a;
	}

	long Uniform(long a, long b)
	{
		return a == b ? a : Next() % (b - a) + a;
	}

	unsigned long Uniform(unsigned long a, unsigned long b)
	{
		return a == b ? a : Next() % (b - a) + a;
	}

	float Uniform(float a, float b)
	{
		return NextSingle() * (b - a) + a;
	}

	double Uniform(double a, double b)
	{
		return NextDouble() * (b - a) + a;
	}

private:
	unsigned int Next()
	{
		--_count;
		if (_count == 0)
		{
			for (int i = 0; i < 4; ++i)
			{
				_state = _state * _multiplier + _increment;
			}

			_count = 101;
		}

		_state ^= _state >> 21;
		_state ^= (_state << 13) | 0x73a4b9de9d2c5680;
		_state ^= (_state << 29) & 0x5b3e6da7efc67a5b;
		_state ^= _state >> 33;
		return (unsigned int)_state;
	}
};

class PerlinNoise
{
	/// <summary>
	/// Permutation
	/// </summary>
private:
	int _p[512];

	/// <summary>
	/// Initializes a new instance of the <see cref="PerlinNoise"/> class.
	/// </summary>
	/// <param name="seed">Seed for generating permutaion.</param>
public:
	PerlinNoise(int seed)
	{
		auto random = UniformRNG((unsigned long)seed);
		for (int i = 0; i < 256; i++)
			_p[i + 256] = _p[i] = (int)(random.NextUInt32() % 256);
	}

	float Noise(float x, float y, float z)
	{
		auto xcoord = Split(x);
		auto ycoord = Split(y);
		auto zcoord = Split(z);

		auto u = Fade(xcoord.remainder);
		auto v = Fade(ycoord.remainder);
		auto w = Fade(zcoord.remainder);

		int a = _p[xcoord.integer];
		int b = _p[xcoord.integer + 1];
		int aa = _p[a + ycoord.integer];
		int ab = _p[a + ycoord.integer + 1];
		int ba = _p[b + ycoord.integer];
		int bb = _p[b + ycoord.integer + 1];

		int aaa = _p[aa + zcoord.integer];
		int aba = _p[ab + zcoord.integer];
		int aab = _p[aa + zcoord.integer + 1];
		int abb = _p[ab + zcoord.integer + 1];
		int baa = _p[ba + zcoord.integer];
		int bba = _p[bb + zcoord.integer];
		int bab = _p[ba + zcoord.integer + 1];
		int bbb = _p[bb + zcoord.integer + 1];

		auto xa = glm::vec4(
			Grad(aaa, xcoord.remainder, ycoord.remainder, zcoord.remainder),
			Grad(aba, xcoord.remainder, ycoord.remainder - 1, zcoord.remainder),
			Grad(aab, xcoord.remainder, ycoord.remainder, zcoord.remainder - 1),
			Grad(abb, xcoord.remainder, ycoord.remainder - 1, zcoord.remainder - 1));
		auto xb = glm::vec4(
			Grad(baa, xcoord.remainder - 1, ycoord.remainder, zcoord.remainder),
			Grad(bba, xcoord.remainder - 1, ycoord.remainder - 1, zcoord.remainder),
			Grad(bab, xcoord.remainder - 1, ycoord.remainder, zcoord.remainder - 1),
			Grad(bbb, xcoord.remainder - 1, ycoord.remainder - 1, zcoord.remainder - 1));
		auto xl = glm::mix(xa, xb, u);
		auto ya = glm::vec2(xl.x, xl.z);
		auto yb = glm::vec2(xl.y, xl.w);
		auto yl = glm::mix(ya, yb, v);

		return (Lerp(yl.x, yl.y, w) + 1) / 2;
	}

	void Noise(vector<vector<vector<float>>> & noise, glm::vec3 offset, glm::vec3 scale)
	{
		int xExtent = noise.size(), yExtent = noise[0].size(), zExtent = noise[0][0].size();

		for (int x = 0; x < xExtent; x++)
		{
			auto xOffset = offset.x + x * scale.x;
			auto xcoord = Split(xOffset);
			auto u = Fade(xcoord.remainder);

			int a = _p[xcoord.integer];
			int b = _p[xcoord.integer + 1];
			for (int y = 0; y < yExtent; y++)
			{
				auto yOffset = offset.y + y * scale.y;
				auto ycoord = Split(yOffset);
				auto v = Fade(ycoord.remainder);

				int aa = _p[a + ycoord.integer];
				int ab = _p[a + ycoord.integer + 1];
				int ba = _p[b + ycoord.integer];
				int bb = _p[b + ycoord.integer + 1];
				for (int z = 0; z < zExtent; z++)
				{
					auto zOffset = offset.z + z * scale.z;
					auto zcoord = Split(zOffset);
					auto w = Fade(zcoord.remainder);

					int aaa = _p[aa + zcoord.integer];
					int aba = _p[ab + zcoord.integer];
					int aab = _p[aa + zcoord.integer + 1];
					int abb = _p[ab + zcoord.integer + 1];
					int baa = _p[ba + zcoord.integer];
					int bba = _p[bb + zcoord.integer];
					int bab = _p[ba + zcoord.integer + 1];
					int bbb = _p[bb + zcoord.integer + 1];

					auto xa = glm::vec4(
						Grad(aaa, xcoord.remainder, ycoord.remainder, zcoord.remainder),
						Grad(aba, xcoord.remainder, ycoord.remainder - 1, zcoord.remainder),
						Grad(aab, xcoord.remainder, ycoord.remainder, zcoord.remainder - 1),
						Grad(abb, xcoord.remainder, ycoord.remainder - 1, zcoord.remainder - 1));
					auto xb = glm::vec4(
						Grad(baa, xcoord.remainder - 1, ycoord.remainder, zcoord.remainder),
						Grad(bba, xcoord.remainder - 1, ycoord.remainder - 1, zcoord.remainder),
						Grad(bab, xcoord.remainder - 1, ycoord.remainder, zcoord.remainder - 1),
						Grad(bbb, xcoord.remainder - 1, ycoord.remainder - 1, zcoord.remainder - 1));
					auto xl = glm::mix(xa, xb, u);
					auto ya = glm::vec2(xl.x, xl.z);
					auto yb = glm::vec2(xl.y, xl.w);
					auto yl = glm::mix(ya, yb, v);

					noise[x][y][z] = (Lerp(yl.x, yl.y, w) + 1) / 2;
				}
			}
		}
	}

	void AddNoise(vector<vector<vector<float>>> & noise, glm::vec3 offset, glm::vec3 scale, float noiseScale)
	{
		int xExtent = noise.size(), yExtent = noise[0].size(), zExtent = noise[0][0].size();

		for (int x = 0; x < xExtent; x++)
		{
			auto xOffset = offset.x + x * scale.x;
			auto xcoord = Split(xOffset);
			auto u = Fade(xcoord.remainder);

			int a = _p[xcoord.integer];
			int b = _p[xcoord.integer + 1];
			for (int y = 0; y < yExtent; y++)
			{
				auto yOffset = offset.y + y * scale.y;
				auto ycoord = Split(yOffset);
				auto v = Fade(ycoord.remainder);

				int aa = _p[a + ycoord.integer];
				int ab = _p[a + ycoord.integer + 1];
				int ba = _p[b + ycoord.integer];
				int bb = _p[b + ycoord.integer + 1];
				for (int z = 0; z < zExtent; z++)
				{
					auto zOffset = offset.z + z * scale.z;
					auto zcoord = Split(zOffset);
					auto w = Fade(zcoord.remainder);

					int aaa = _p[aa + zcoord.integer];
					int aba = _p[ab + zcoord.integer];
					int aab = _p[aa + zcoord.integer + 1];
					int abb = _p[ab + zcoord.integer + 1];
					int baa = _p[ba + zcoord.integer];
					int bba = _p[bb + zcoord.integer];
					int bab = _p[ba + zcoord.integer + 1];
					int bbb = _p[bb + zcoord.integer + 1];

					auto xa = glm::vec4(
						Grad(aaa, xcoord.remainder, ycoord.remainder, zcoord.remainder),
						Grad(aba, xcoord.remainder, ycoord.remainder - 1, zcoord.remainder),
						Grad(aab, xcoord.remainder, ycoord.remainder, zcoord.remainder - 1),
						Grad(abb, xcoord.remainder, ycoord.remainder - 1, zcoord.remainder - 1));
					auto xb = glm::vec4(
						Grad(baa, xcoord.remainder - 1, ycoord.remainder, zcoord.remainder),
						Grad(bba, xcoord.remainder - 1, ycoord.remainder - 1, zcoord.remainder),
						Grad(bab, xcoord.remainder - 1, ycoord.remainder, zcoord.remainder - 1),
						Grad(bbb, xcoord.remainder - 1, ycoord.remainder - 1, zcoord.remainder - 1));
					auto xl = glm::mix(xa, xb, u);
					auto ya = glm::vec2(xl.x, xl.z);
					auto yb = glm::vec2(xl.y, xl.w);
					auto yl = glm::mix(ya, yb, v);

					noise[x][y][z] += (Lerp(yl.x, yl.y, w) + 1) / 2 * noiseScale;
				}
			}
		}
	}

	struct sp
	{
		sp(int i, float r) { integer = i; remainder = r; }
		int integer; float remainder;
	};

private:
	static sp Split(float value)
	{
		value = fmod(value, 256);
		if (value < 0) value += 256;
		auto integer = (int)value;
		auto remainder = value - integer;
		return sp(integer, remainder);
	}

	static float Fade(float t)
	{
		// 6t^5 - 15t^4 + 10t^3
		return t * t * t * (t * (t * 6 - 15) + 10);
	}

	// Source: http://riven8192.blogspot.com/2010/08/calculate-perlinnoise-twice-as-fast.html
public:
	static float Grad(int hash, float x, float y, float z)
	{
		switch (hash & 0xF)
		{
		case 0x0: return x + y;
		case 0x1: return -x + y;
		case 0x2: return x - y;
		case 0x3: return -x - y;
		case 0x4: return x + z;
		case 0x5: return -x + z;
		case 0x6: return x - z;
		case 0x7: return -x - z;
		case 0x8: return y + z;
		case 0x9: return -y + z;
		case 0xA: return y - z;
		case 0xB: return -y - z;
		case 0xC: return y + x;
		case 0xD: return -y + z;
		case 0xE: return y - x;
		case 0xF: return -y - z;
		//default: throw new ArgumentException();
		}
	}

		static float Lerp(float a, float b, float x) {
			return a + x * (b - a);
		}
};

class OctavedNoise
{
private:
	PerlinNoise _innerNoise = PerlinNoise(0);
	int _octaves;
	float _persistence;

public:
	OctavedNoise(PerlinNoise innerNoise, int octaves, float persistence)
	{
		_innerNoise = innerNoise;
		_octaves = octaves;
		_persistence = persistence;
	}

	float Noise(float x, float y, float z)
	{
		double total = 0;
		int frequency = 1;
		double amplitude = 1;
		double maxValue = 0;

		for (int i = 0; i < _octaves; i++)
		{
			total += _innerNoise.Noise(x * frequency, y * frequency, z * frequency) * amplitude;
			maxValue += amplitude;
			amplitude *= _persistence;
			frequency *= 2;
		}

		return (float)(total / maxValue);
	}

	void Noise(vector<vector<vector<float>>> & noise, glm::vec3 offset, glm::vec3 scale)
	{
		for (auto i : noise)
			for (auto j : i)
				for (auto k : j)
					k = 0;
				
		int frequency = 1;
		double amplitude = 1;
		double maxValue = 0;

		for (int i = 0; i < _octaves; i++)
		{
			_innerNoise.AddNoise(noise, glm::vec3(offset.x * scale.x * frequency, offset.y * scale.y * frequency, offset.z * scale.z * frequency), glm::vec3( scale.x * frequency,  scale.y * frequency,  scale.z * frequency), (float)amplitude);
			maxValue += amplitude;
			amplitude *= _persistence;
			frequency *= 2;
		}

		int xExtent = noise.size(), yExtent = noise[0].size(), zExtent = noise[0][0].size();
		for (int x = 0; x < xExtent; x++)
		{
			for (int y = 0; y < yExtent; y++)
			{
				for (int z = 0; z < zExtent; z++)
					noise[x][y][z] /= (float)maxValue;
			}
		}
	}
};