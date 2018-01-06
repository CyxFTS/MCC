#pragma once
#include <string>
#include <genLayer.h>
#include <block.h>
#include <chunk.h>
#include <vector>
using namespace std;
class BiomeOcean;
class BiomeProperties
{
public: 
	string BiomeName;

	BiomeId BiomeId;

	float BaseHeight = 0.1F;

	float HeightVariation = 0.2F;

	float Temperature = 0.5F;

	float Rainfall = 0.5F;

	int WaterColor = 16777215;

	bool EnableSnow = false;

	bool EnableRain = true;
};

class GeneratorSettings
{
public:
	bool GenerateStructure = true;

	bool UseCaves = true;

	bool UseRavines = true;

	bool UseMineShafts = true;

	bool UseVillages = true;

	bool UseStrongholds = true;

	bool UseTemples = true;

	bool UseMonuments = true;

	bool UseMansions = true;

	int SeaLevel = 63;

	float DepthNoiseScaleX = 200.0F;

	float DepthNoiseScaleY = 200.0F;

	float DepthNoiseScaleZ = 200.0F;

	float CoordinateScale = 0.006F; // mc = 684.412F;0.05

	float HeightScale = 0.006F; // mc = 684.412F;0.05

	float MainNoiseScaleX = 80.0F;

	float MainNoiseScaleY = 160.0F;

	float MainNoiseScaleZ = 80.0F;

	float BiomeDepthOffSet;

	float BiomeDepthWeight = 1.0F;

	float BiomeScaleOffset;

	float BiomeScaleWeight = 1.0F;

	float BaseSize = 8.5F;

	float StretchY = 12.0F;

	float LowerLimitScale = 512.0F;

	float UpperLimitScale = 512.0F;

	int BiomeSize = 4;

	int RiverSize = 4;

	// ores like
	int DirtSize = 33;

	int DirtCount = 10;

	int DirtMinHeight = 0;

	int DirtMaxHeight = 256;

	int GravelSize = 33;

	int GravelCount = 8;

	int GravelMinHeight = 0;

	int GravelMaxHeight = 256;

	int GraniteSize = 33;

	int GraniteCount = 10;

	int GraniteMinHeight = 0;

	int GraniteMaxHeight = 80;

	int DioriteSize = 33;

	int DioriteCount = 10;

	int DioriteMinHeight = 0;

	int DioriteMaxHeight = 80;

	int AndesiteSize = 33;

	int AndesiteCount = 10;

	int AndesiteMinHeight = 0;

	int AndesiteMaxHeight = 80;

	// ores
	int CoalSize = 17;

	int CoalCount = 20;

	int CoalMinHeight = 0;

	int CoalMaxHeight = 128;

	int IronSize = 9;

	int IronCount = 20;

	int IronMinHeight = 0;

	int IronMaxHeight = 64;

	int GoldSize = 9;

	int GoldCount = 2;

	int GoldMinHeight = 0;

	int GoldMaxHeight = 32;

	int RedstoneSize = 8;

	int RedstoneCount = 8;

	int RedstoneMinHeight = 0;

	int RedstoneMaxHeight = 16;

	int DiamondSize = 8;

	int DiamondCount = 1;

	int DiamondMinHeight = 0;

	int DiamondMaxHeight = 16;

	int LapisSize = 7;

	int LapisCount = 1;

	int LapisCenterHeight = 16;

	int LapisSpread = 16;

	vector<BlockState> FlatBlockId = { BlockState(Bedrock, 0), BlockState(BlockId::Stone, StoneType::Stone), BlockState(BlockId::Dirt, DirtType::Dirt), BlockState(BlockId::Grass, GrassType::Shrub)};

};

class Biome
{
	// Biome有关的生成器的设置
protected:
	GeneratorSettings _genSettings;

	string _name;

	BiomeId _biomeId;
	/** The base height of this biome. Default 0.1. */
	float _baseHeight;
	/** The variation from the base height of the biome. Default 0.3. */
	float _heightVariation;
	/** The temperature of this biome. */
	float _temperature;
	/** The rainfall in this biome. */
	float _rainfall;
	/** Color tint applied to water depending on biome */
	int _waterColor;
	/** Set to true if snow is enabled for this biome. */
	bool _enableSnow;
	/** Is true (default) if the biome support rain (desert and nether can't have rain) */
	bool _enableRain;
	/** The block expected to be on the top of this biome */
public:
	BlockState _topBlock = BlockState(BlockId::GrassBlock, 0);
	/** The block to fill spots in when not on the top */
	BlockState _fillerBlock = BlockState(BlockId::Dirt, DirtType::Dirt);


public:
	Biome() = default;
	Biome(BiomeProperties properties, GeneratorSettings genSettings)
	{
		_genSettings = genSettings;

		_name = properties.BiomeName;
		_biomeId = properties.BiomeId;
		_baseHeight = properties.BaseHeight;
		_heightVariation = properties.HeightVariation;
		_temperature = properties.Temperature;
		_rainfall = properties.Rainfall;
		_waterColor = properties.WaterColor;
		_enableSnow = properties.EnableSnow;
		_enableRain = properties.EnableRain;

	}

	BiomeId GetBiomeId()
	{
		return _biomeId;
	}

	string GetBiomeName()
	{
		return _name;
	}

	float GetBaseHeight()
	{
		return _baseHeight;
	}

	float GetHeightVariation()
	{
		return _heightVariation;
	}

	// 产生生物群系特有的方块
	virtual void GenerateBiomeTerrain(int seaLevel, int randSeed, ChunkColumnStorage &chunk, int chunk_x, int chunk_z, int x_in_chunk, int z_in_chunk, double noiseVal)
	{
		BlockState topBlockstate = _topBlock;
		BlockState fillerBlockstate = _fillerBlock;
		int surfaceFlag = -1;
		double t = rand() / (double)(RAND_MAX);
		int surfaceDepth = (int)(noiseVal / 3.0f + 3.0f + (t) * 0.25f);

		for (int y = 255; y >= 0; --y)
		{
			if (y <= rand()%(5))
			{
				chunk(x_in_chunk, y, z_in_chunk) = BlockState(Bedrock, 0);
			}
			else
			{
				BlockState iblockstate = chunk(x_in_chunk, y, z_in_chunk);

				if (iblockstate.Id == BlockId::Air)
				{
					surfaceFlag = -1;
				}
				else if (iblockstate.Equals(BlockState(BlockId::Stone, StoneType::Stone)))
				{
					// 将地面石头进行生物群系替换
					if (surfaceFlag == -1)
					{
						if (surfaceDepth <= 0)
						{
							topBlockstate = BlockState(BlockId::Air, 0);
							fillerBlockstate = BlockState(BlockId::Stone, StoneType::Stone);
						}
						else if (y >= seaLevel - 4 && y <= seaLevel + 1)
						{
							topBlockstate = _topBlock;
							fillerBlockstate = _fillerBlock;
						}

						// TODO 根据温度变化决定水的状态
						surfaceFlag = surfaceDepth;

						if (y >= seaLevel - 1)
						{
							chunk(x_in_chunk, y, z_in_chunk) = topBlockstate;
						}
						else if (y < seaLevel - 7 - surfaceDepth)
						{
							topBlockstate = BlockState(BlockId::Air, 0);
							fillerBlockstate = BlockState(BlockId::Stone, StoneType::Stone);
							chunk(x_in_chunk, y, z_in_chunk) = BlockState(BlockId::Gravel, 0);
						}
						else
							chunk(x_in_chunk, y, z_in_chunk) = fillerBlockstate;
					}
					else if (surfaceFlag > 0)
					{
						--surfaceFlag;
						chunk(x_in_chunk, y, z_in_chunk) = fillerBlockstate;
					}
				}
			}
		}
	}
};

class BiomeOcean : public Biome
{
public:
	BiomeOcean(BiomeProperties properties, GeneratorSettings genSettings)
		: Biome(properties, genSettings)
	{
		
		_name = "ocean";
		_biomeId = BiomeId::Ocean;
		_baseHeight = -1.0F;
		_heightVariation = 0.1F;

	}

};

class BiomePlains : public Biome
{
public:
	BiomePlains(BiomeProperties properties, GeneratorSettings genSettings)
		: Biome(properties, genSettings)
	{
		_name = "plains";
		_biomeId = BiomeId::Plains;
		_baseHeight = 0.125F;
		_heightVariation = 0.05F;
		_temperature = 0.8F;
		_rainfall = 0.4F;
		_enableRain = true;

	}
};

class BiomeDesert : public Biome
{
public:
	BiomeDesert(BiomeProperties properties, GeneratorSettings genSettings)
		: Biome(properties, genSettings)
	{
		_name = "desert";
		_biomeId = BiomeId::Desert;
		_baseHeight = 0.125F;
		_heightVariation = 0.05F;
		_temperature = 2.0F;
		_rainfall = 0.0F;
		_enableRain = false;

		_topBlock = BlockState(BlockId::Sand, SandType::Sand);
		_fillerBlock = BlockState(BlockId::Sand, SandType::Sand);
	}
};

enum BiomeHillType
{
	Normal,
	ExtraTrees,
	Mutated
};

class BiomeHill : public Biome
{
protected:
	int _type;

public:
	BiomeHill(int type, BiomeProperties properties, GeneratorSettings genSettings)
		: Biome(properties, genSettings)
	{
		_type = type;
		if (type == BiomeHillType::Normal)
		{
			_name = "extreme_hills";
			_biomeId = BiomeId::ExtremeHills;

			_baseHeight = 1.0F;
			_heightVariation = 0.5F;
			_temperature = 0.2F;
			_rainfall = 0.3F;
			_enableRain = true;
		}
		else
		{
			_name = "extreme_hills";
			_biomeId = BiomeId::ExtremeHills;

			_baseHeight = 1.0F;
			_heightVariation = 0.5F;
			_temperature = 0.2F;
			_rainfall = 0.3F;
			_enableRain = true;
		}
	}

	void GenerateBiomeTerrain(int seaLevel, int randSeed, ChunkColumnStorage &chunk, int chunk_x, int chunk_z, int x_in_chunk, int z_in_chunk, double noiseVal)
	{
		_topBlock = BlockState(BlockId::GrassBlock, 0);
		_fillerBlock = BlockState(BlockId::Dirt, DirtType::Dirt);

		if ((noiseVal < -1.0f || noiseVal > 2.0f) && _type == BiomeHillType::Mutated)
		{
			_topBlock = BlockState(BlockId::Gravel, 0);
			_fillerBlock = BlockState(BlockId::Gravel, 0);
		}
		else if (noiseVal > 0.0f && _type != BiomeHillType::ExtraTrees)
		{
			_topBlock = BlockState(BlockId::Stone, StoneType::Stone);
			_fillerBlock = BlockState(BlockId::Stone, StoneType::Stone);
		}

		Biome::GenerateBiomeTerrain(seaLevel, randSeed, chunk, chunk_x, chunk_z, x_in_chunk, z_in_chunk, noiseVal);
	}
};

class BiomeForest : public Biome
{
public:
	BiomeForest(BiomeProperties properties, GeneratorSettings genSettings)
		: Biome(properties, genSettings)
	{
		_name = "forest";
		_biomeId = BiomeId::Forest;
	
		_temperature = 0.7F;
		_rainfall = 0.8F;
		_enableRain = true;

	}
};

class BiomeTaiga : public Biome
{
public:
	BiomeTaiga(BiomeProperties properties, GeneratorSettings genSettings)
		: Biome(properties, genSettings)
	{
		_name = "taiga";
		_biomeId = BiomeId::Taiga;

		_baseHeight = 0.2F;
		_heightVariation = 0.2F;
		_temperature = 0.25F;
		_temperature = 0.7F;
		_rainfall = 0.8F;
		_enableRain = true;

	}
};

class BiomeSwamp : public Biome
{
public:
	BiomeSwamp(BiomeProperties properties, GeneratorSettings genSettings)
		: Biome(properties, genSettings)
	{
		_name = "swampland";
		_biomeId = BiomeId::Swampland;

		_baseHeight = -0.2F;
		_heightVariation = 0.1F;
		_temperature = 0.8F;
		_rainfall = 0.9F;
		_enableRain = true;
		_waterColor = 14745518;
	}
};

class BiomeRiver : public Biome
{
public:
	BiomeRiver(BiomeProperties properties, GeneratorSettings genSettings)
		: Biome(properties, genSettings)
	{
		_name = "river";
		_biomeId = BiomeId::River;

		_baseHeight = -0.5F;
		_heightVariation = 0.0F;
	}
};

class BiomeBeach : public Biome
{
public:
	BiomeBeach(BiomeProperties properties, GeneratorSettings genSettings)
		: Biome(properties, genSettings)
	{
		_name = "beach";
		_biomeId = BiomeId::Beach;

		_baseHeight = -0.1F;
		_heightVariation = 0.0025F;
		_temperature = 0.8F;
		_rainfall = 0.4F;

		_topBlock = BlockState(BlockId::Sand, SandType::Sand);
		_fillerBlock = BlockState(BlockId::Sand, SandType::Sand);
	}
};

static Biome GetBiome(int id, GeneratorSettings settings)
{
	BiomeId biomeId = (BiomeId)id;
	switch (biomeId)
	{
	case BiomeId::Ocean:
		return BiomeOcean(BiomeProperties(), settings);
	case BiomeId::Plains:
		return BiomePlains(BiomeProperties(), settings);
	case BiomeId::Desert:
		return BiomeDesert(BiomeProperties(), settings);
	case BiomeId::ExtremeHills:
		return BiomeHill(BiomeHillType::Normal, BiomeProperties(), settings);
	case BiomeId::Forest:
		return BiomeForest(BiomeProperties(), settings);
	case BiomeId::Taiga:
		return BiomeTaiga(BiomeProperties(), settings);
	case BiomeId::Swampland:
		return BiomeSwamp(BiomeProperties(), settings);
	case BiomeId::River:
		return BiomeRiver(BiomeProperties(), settings);
	case BiomeId::Beach:
		return BiomeBeach(BiomeProperties(), settings);
	default:
		return Biome();
	}
}