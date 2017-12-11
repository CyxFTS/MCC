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

	// FlatGeneratorInfo FlatGeneratorInfo 

	// OverworldGeneratorInfo OverworldGeneratorInfo 
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

	// 噪声函数
	/*protected static readonly OctavedNoise<PerlinNoise> _temperatureNoise =
		new OctavedNoise<PerlinNoise>(new PerlinNoise(1234), 4, 0.5F);

	protected static readonly OctavedNoise<PerlinNoise> _grassColorNoise =
		new OctavedNoise<PerlinNoise>(new PerlinNoise(2345), 4, 0.5F);*/

//	// 矿物生成器
//private:
//	MinableGenerator _dirtGen; // 你没看错，这些当作矿物生成
//	MinableGenerator _gravelOreGen;
//	MinableGenerator _graniteGen;
//	MinableGenerator _dioriteGen;
//	MinableGenerator _andesiteGen;
//
//	MinableGenerator _coalGen;
//	MinableGenerator _ironGen;
//	MinableGenerator _goldGen;
//	MinableGenerator _redstoneGen;
//	MinableGenerator _diamondGen;
//	MinableGenerator _lapisGen;

	// 植被设置
//protected:
//	int _treesPerChunk;
//	float _extraTreeChance;
//	int _grassPerChunk;
//	int _flowersPerChunk;
//	int _mushroomsPerChunk;
//
//	int _deadBushPerChunk;
//	int _reedsPerChunk;
//	int _cactiPerChunk;
//
//	// 生物种类
//	List<MobType> _passiveMobList;
//	List<MobType> _monsterList;
//
//	int _clayPerChunk;
//	int _waterlilyPerChunk;
//	int _sandPatchesPerChunk;
//	int _gravelPatchesPerChunk;

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

		//_dirtGen = new MinableGenerator(
		//	BlockStates.Dirt(),
		//	genSettings.DirtSize);
		//_gravelOreGen = new MinableGenerator(
		//	BlockStates.Gravel(),
		//	genSettings.GravelSize);
		//_graniteGen = new MinableGenerator(
		//	BlockStates.Stone(StoneType.Granite),
		//	genSettings.GraniteSize);
		//_dioriteGen = new MinableGenerator(
		//	BlockStates.Stone(StoneType.Diorite),
		//	genSettings.DioriteSize);
		//_andesiteGen = new MinableGenerator(
		//	BlockStates.Stone(StoneType.Andesite),
		//	genSettings.AndesiteSize);
		//_coalGen = new MinableGenerator(
		//	BlockStates.CoalOre(),
		//	genSettings.CoalSize);
		//_ironGen = new MinableGenerator(
		//	BlockStates.IronOre(),
		//	genSettings.IronSize);
		//_goldGen = new MinableGenerator(
		//	BlockStates.GoldOre(),
		//	genSettings.GoldSize);
		//_redstoneGen = new MinableGenerator(
		//	BlockStates.RedstoneOre(),
		//	genSettings.RedstoneSize);
		//_diamondGen = new MinableGenerator(
		//	BlockStates.DiamondOre(),
		//	genSettings.DiamondSize);
		//_lapisGen = new MinableGenerator(
		//	BlockStates.LapisLazuliOre(),
		//	genSettings.LapisSize);

		//_treesPerChunk = 0; // mc 0
		//_extraTreeChance = 0.05F; // mc 0.05F
		//_grassPerChunk = 10;
		//_flowersPerChunk = 4;
		//_mushroomsPerChunk = 0;

		//_deadBushPerChunk = 2;
		//_reedsPerChunk = 50;
		//_cactiPerChunk = 10;

		//_passiveMobList = new List<MobType>();
		//_monsterList = new List<MobType>();
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

	

	// 随机获得一个该生物群系可能出现的草
	/*virtual PlantsType GetRandomGrass(Random rand)
	{
		return PlantsType.TallGrass;
	}*/

	// 随机获得一个该生物群系可能出现的花
	/*virtual PlantsType GetRandomFlower(Random rand)
	{
		double n = rand.NextDouble();
		if (n > 0.5)
		{
			return PlantsType.RedFlower;
		}
		else
		{
			return PlantsType.YellowFlower;
		}
	}*/

	// 随机获得一个该生物群系可能出现的树
	/*virtual PlantsType GetRandomTree(Random rand)
	{
		int n = rand.Next(2);
		switch (n)
		{
		case 0:
			return PlantsType.Oak;
		case 1:
			return PlantsType.Birch;
		default:
			return PlantsType.Oak;
		}
	}*/

	/*void GenerateOre(MinableGenerator generator, IWorld world, IGrainFactory grainFactory, ChunkColumnStorage &chunk, Random random, BlockWorldPos position, int count, int minHeight, int maxHeight)
	{
		if (minHeight > maxHeight)
		{
			int tmp = minHeight;
			minHeight = maxHeight;
			maxHeight = tmp;
		}
		else if (maxHeight == minHeight)
		{
			if (minHeight < 255)
				++maxHeight;
			else
				--minHeight;
		}

		for (int j = 0; j < count; ++j)
		{
			BlockWorldPos blockpos = BlockWorldPos.Add(
				position,
				random.Next(16),
				random.Next(maxHeight - minHeight) + minHeight,
				random.Next(16));
			generator.Generate(world, grainFactory, chunk, random, blockpos);
		}
	}*/

	// 后期添加一些方块，Biome基类主要生成矿物
	/*virtual void Decorate(IWorld world, IGrainFactory grainFactory, ChunkColumnStorage &chunk, Random rand, BlockWorldPos pos)
	{
		GenerateOre(_dirtGen, world, grainFactory, chunk, rand, pos, _genSettings.DirtCount, _genSettings.DirtMaxHeight, _genSettings.DirtMinHeight);
		GenerateOre(_gravelOreGen, world, grainFactory, chunk, rand, pos, _genSettings.GravelCount, _genSettings.GravelMaxHeight, _genSettings.GravelMinHeight);
		GenerateOre(_graniteGen, world, grainFactory, chunk, rand, pos, _genSettings.GraniteCount, _genSettings.GraniteMaxHeight, _genSettings.GraniteMinHeight);
		GenerateOre(_dioriteGen, world, grainFactory, chunk, rand, pos, _genSettings.DioriteCount, _genSettings.DioriteMaxHeight, _genSettings.DioriteMinHeight);
		GenerateOre(_andesiteGen, world, grainFactory, chunk, rand, pos, _genSettings.AndesiteCount, _genSettings.AndesiteMaxHeight, _genSettings.AndesiteMinHeight);

		GenerateOre(_coalGen, world, grainFactory, chunk, rand, pos, _genSettings.CoalCount, _genSettings.CoalMaxHeight, _genSettings.CoalMinHeight);
		GenerateOre(_ironGen, world, grainFactory, chunk, rand, pos, _genSettings.IronCount, _genSettings.IronMaxHeight, _genSettings.IronMinHeight);
		GenerateOre(_goldGen, world, grainFactory, chunk, rand, pos, _genSettings.GoldCount, _genSettings.GoldMaxHeight, _genSettings.GoldMinHeight);
		GenerateOre(_redstoneGen, world, grainFactory, chunk, rand, pos, _genSettings.RedstoneCount, _genSettings.RedstoneMaxHeight, _genSettings.RedstoneMinHeight);
		GenerateOre(_diamondGen, world, grainFactory, chunk, rand, pos, _genSettings.DiamondCount, _genSettings.DiamondMaxHeight, _genSettings.DiamondMinHeight);
		GenerateOre(_lapisGen, world, grainFactory, chunk, rand, pos, _genSettings.LapisCount, _genSettings.LapisCenterHeight + _genSettings.LapisSpread, _genSettings.LapisCenterHeight - _genSettings.LapisSpread);
	}*/

	// 添加生物群系特有的生物
	/*virtual void SpawnMob(IWorld world, IGrainFactory grainFactory, ChunkColumnStorage &chunk, Random rand, BlockWorldPos pos)
	{
		ChunkWorldPos chunkPos = pos.ToChunkWorldPos();
		int seed = chunkPos.Z * 16384 + chunkPos.X;
		Random r = new Random(seed);
		foreach(MobType eachType in _passiveMobList)
		{
			if (r.Next(64) == 0)
			{
				PassiveMobSpawner spawner = new PassiveMobSpawner(eachType, 10);
				spawner.Spawn(world, grainFactory, chunk, rand, new BlockWorldPos(pos.X, pos.Y, pos.Z));
			}
		}
	}*/

	// 添加生物群系特有的怪物
	/*virtual void SpawnMonster(IWorld world, IGrainFactory grainFactory, ChunkColumnStorage &chunk, Random rand, BlockWorldPos pos)
	{
		ChunkWorldPos chunkPos = pos.ToChunkWorldPos();
		int seed = chunkPos.Z * 16384 + chunkPos.X;
		Random r = new Random(seed);
		foreach(MobType eachType in _monsterList)
		{
			if (r.Next(64) == 0)
			{
				MonsterSpawner spawner = new MonsterSpawner(eachType, 3);
				spawner.Spawn(world, grainFactory, chunk, rand, new BlockWorldPos(pos.X, pos.Y, pos.Z));
			}
		}
	}
*/
	// 产生生物群系特有的方块
	virtual void GenerateBiomeTerrain(int seaLevel, int randSeed, ChunkColumnStorage &chunk, int chunk_x, int chunk_z, int x_in_chunk, int z_in_chunk, double noiseVal)
	{
		//srand(randSeed);
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
						{
							chunk(x_in_chunk, y, z_in_chunk) = fillerBlockstate;
							auto a = chunk(x_in_chunk, y, z_in_chunk);
							a.Id += 0;
							a.Id += 0;
							
								a.Id += 0;
						}
					}
					else if (surfaceFlag > 0)
					{
						--surfaceFlag;
						chunk(x_in_chunk, y, z_in_chunk) = fillerBlockstate;
					}
				}
			}
			auto a = chunk(x_in_chunk, y, z_in_chunk);
			if (y == 54 && a.Id != 3)
			int A = 1 + 1;
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

		/*_passiveMobList.Add(MobType.Squid);*/
	}

	// 添加生物群系特有的生物
	/*public override void SpawnMob(IWorld world, IGrainFactory grainFactory, ChunkColumnStorage &chunk, Random rand, BlockWorldPos pos)
	{
		ChunkWorldPos chunkPos = pos.ToChunkWorldPos();
		int seed = chunkPos.Z * 16384 + chunkPos.X;
		Random r = new Random(seed);
		foreach(MobType eachType in _passiveMobList)
		{
			if (r.Next(32) == 0)
			{
				PassiveMobSpawner spawner = new PassiveMobSpawner(eachType, 15);
				spawner.Spawn(world, grainFactory, chunk, rand, new BlockWorldPos(pos.X, pos.Y, pos.Z));
			}
		}
	}*/
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

		/*_passiveMobList.Add(MobType.Pig);
		_passiveMobList.Add(MobType.Sheep);
		_passiveMobList.Add(MobType.Cow);
		_passiveMobList.Add(MobType.Chicken);

		_monsterList.Add(MobType.Creeper);
		_monsterList.Add(MobType.Zombie);
		_monsterList.Add(MobType.Skeleton);
		_monsterList.Add(MobType.Spider);*/
	}

	//// 添加其他东西
	//public override void Decorate(IWorld world, IGrainFactory grainFactory, ChunkColumnStorage &chunk, Random rand, BlockWorldPos pos)
	//{
	//	float grassColor = (_grassColorNoise.Noise((pos.X + 8) / 200.0F, 0.0F, (pos.Z + 8) / 200.0F) - 0.5F) * 2;

	//	if (grassColor < -0.8F)
	//	{
	//		_flowersPerChunk = 15;
	//		_grassPerChunk = 5 * 7;
	//		GenDoubleFlowers(world, grainFactory, chunk, rand, pos);
	//	}
	//	else
	//	{
	//		_flowersPerChunk = 4;
	//		_grassPerChunk = 10 * 7;
	//	}

	//	GenGrass(world, grainFactory, chunk, rand, pos);
	//	GenFlowers(world, grainFactory, chunk, rand, pos);
	//	GenDoubleGrass(world, grainFactory, chunk, rand, pos);

	//	int treesPerChunk = _treesPerChunk;

	//	if (rand.NextDouble() < _extraTreeChance)
	//	{
	//		++treesPerChunk;
	//	}

	//	for (int num = 0; num < treesPerChunk; ++num)
	//	{
	//		int x = rand.Next(12) + 2;
	//		int z = rand.Next(12) + 2;

	//		TreeGenerator treeGenerator = new TreeGenerator(5, false, GetRandomTree(rand));

	//		// 获得地表面高度
	//		int h = 0;
	//		for (int y = 255; y >= 0; --y)
	//		{
	//			if (!chunk[x, y, z].IsAir())
	//			{
	//				h = y + 1;
	//				break;
	//			}
	//		}

	//		treeGenerator.Generate(world, grainFactory, chunk, this, rand, new BlockWorldPos(pos.X + x, h, pos.Z + z));
	//	}

	//	base.Decorate(world, grainFactory, chunk, rand, pos);
	//}

	//// 添加生物群系特有的生物
	//public override void SpawnMob(IWorld world, IGrainFactory grainFactory, ChunkColumnStorage &chunk, Random rand, BlockWorldPos pos)
	//{
	//	ChunkWorldPos chunkPos = pos.ToChunkWorldPos();
	//	int seed = chunkPos.Z * 16384 + chunkPos.X;
	//	Random r = new Random(seed);
	//	foreach(MobType eachType in _passiveMobList)
	//	{
	//		if (r.Next(32) == 0)
	//		{
	//			PassiveMobSpawner spawner = new PassiveMobSpawner(eachType, 15);
	//			spawner.Spawn(world, grainFactory, chunk, rand, new BlockWorldPos(pos.X, pos.Y, pos.Z));
	//		}
	//	}
	//}

	//private void GenGrass(IWorld world, IGrainFactory grainFactory, ChunkColumnStorage &chunk, Random random, BlockWorldPos pos)
	//{
	//	int grassMaxNum = random.Next(_grassPerChunk);
	//	GrassGenerator generator = new GrassGenerator();
	//	for (int grassNum = 0; grassNum < grassMaxNum; ++grassNum)
	//	{
	//		int x = random.Next(16);
	//		int z = random.Next(16);
	//		for (int y = 255; y >= 1; --y)
	//		{
	//			if (!chunk[x, y, z].IsAir())
	//			{
	//				generator.Generate(world, grainFactory, chunk, this, random, new BlockWorldPos(pos.X + x, y + 1, pos.Z + z));
	//				break;
	//			}
	//		}
	//	}
	//}

	//private void GenFlowers(IWorld world, IGrainFactory grainFactory, ChunkColumnStorage &chunk, Random random, BlockWorldPos pos)
	//{
	//	int flowersMaxNum = random.Next(_flowersPerChunk);
	//	FlowersGenerator generator = new FlowersGenerator();
	//	for (int flowersNum = 0; flowersNum < flowersMaxNum; ++flowersNum)
	//	{
	//		int x = random.Next(16);
	//		int z = random.Next(16);
	//		for (int y = 255; y >= 1; --y)
	//		{
	//			if (!chunk[x, y, z].IsAir())
	//			{
	//				generator.Generate(world, grainFactory, chunk, this, random, new BlockWorldPos(pos.X + x, y + 1, pos.Z + z));
	//				break;
	//			}
	//		}
	//	}
	//}

	//private void GenDoubleFlowers(IWorld world, IGrainFactory grainFactory, ChunkColumnStorage &chunk, Random random, BlockWorldPos pos)
	//{
	//	DoubleFlowersGenerator generator = new DoubleFlowersGenerator(PlantsType.Sunflower);
	//	for (int flowersNum = 0; flowersNum < 10; ++flowersNum)
	//	{
	//		int x = random.Next(16);
	//		int z = random.Next(16);
	//		for (int y = 255; y >= 1; --y)
	//		{
	//			if (!chunk[x, y, z].IsAir())
	//			{
	//				generator.Generate(world, grainFactory, chunk, this, random, new BlockWorldPos(pos.X + x, y + 1, pos.Z + z));
	//				break;
	//			}
	//		}
	//	}
	//}

	//private void GenDoubleGrass(IWorld world, IGrainFactory grainFactory, ChunkColumnStorage &chunk, Random random, BlockWorldPos pos)
	//{
	//	DoubleGrassGenerator generator = new DoubleGrassGenerator(PlantsType.DoubleTallgrass);
	//	for (int grassNum = 0; grassNum < 2; ++grassNum)
	//	{
	//		int x = random.Next(16);
	//		int z = random.Next(16);
	//		for (int y = 255; y >= 1; --y)
	//		{
	//			if (!chunk[x, y, z].IsAir())
	//			{
	//				generator.Generate(world, grainFactory, chunk, this, random, new BlockWorldPos(pos.X + x, y + 1, pos.Z + z));
	//				break;
	//			}
	//		}
	//	}
	//}
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
		/*_treesPerChunk = -999;
		_deadBushPerChunk = 2;
		_reedsPerChunk = 50;
		_cactiPerChunk = 10;

		_monsterList.Add(MobType.Creeper);
		_monsterList.Add(MobType.Zombie);
		_monsterList.Add(MobType.Skeleton);
		_monsterList.Add(MobType.Spider);*/
	}

	// 添加其他东西
	//public override void Decorate(IWorld world, IGrainFactory grainFactory, ChunkColumnStorage &chunk, Random rand, BlockWorldPos pos)
	//{
	//	GenCacti(world, grainFactory, chunk, rand, pos);

	//	// TODO 生成仙人掌和枯木
	//	base.Decorate(world, grainFactory, chunk, rand, pos);
	//}

	//// 添加生物群系特有的生物
	//public override void SpawnMob(IWorld world, IGrainFactory grainFactory, ChunkColumnStorage &chunk, Random rand, BlockWorldPos pos)
	//{
	//	ChunkWorldPos chunkPos = pos.ToChunkWorldPos();
	//	int seed = chunkPos.Z * 16384 + chunkPos.X;
	//	Random r = new Random(seed);
	//	foreach(MobType eachType in _passiveMobList)
	//	{
	//		if (r.Next(64) == 0)
	//		{
	//			PassiveMobSpawner spawner = new PassiveMobSpawner(eachType, 10);
	//			spawner.Spawn(world, grainFactory, chunk, rand, new BlockWorldPos(pos.X, pos.Y, pos.Z));
	//		}
	//	}
	//}

	//private void GenCacti(IWorld world, IGrainFactory grainFactory, ChunkColumnStorage &chunk, Random random, BlockWorldPos pos)
	//{
	//	int cactiMaxNum = random.Next(_cactiPerChunk);

	//	if (random.Next(64) == 0)
	//	{
	//		CactiGenerator generator = new CactiGenerator();
	//		for (int cactiNum = 0; cactiNum < cactiMaxNum; ++cactiNum)
	//		{
	//			int x = random.Next(14) + 1;
	//			int z = random.Next(14) + 1;
	//			for (int y = 255; y >= 1; --y)
	//			{
	//				if (!chunk[x, y, z].IsAir())
	//				{
	//					generator.Generate(world, grainFactory, chunk, this, random, new BlockWorldPos(pos.X + x, y + 1, pos.Z + z));
	//					break;
	//				}
	//			}
	//		}
	//	}
	//}
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

		/*_passiveMobList.Add(MobType.Pig);
		_passiveMobList.Add(MobType.Sheep);
		_passiveMobList.Add(MobType.Cow);
		_passiveMobList.Add(MobType.Chicken);

		_monsterList.Add(MobType.Creeper);
		_monsterList.Add(MobType.Zombie);
		_monsterList.Add(MobType.Skeleton);
		_monsterList.Add(MobType.Spider);*/
	}

	// 添加其他东西
	/*public override void Decorate(IWorld world, IGrainFactory grainFactory, ChunkColumnStorage &chunk, Random rand, BlockWorldPos pos)
	{
		GenTrees(world, grainFactory, chunk, rand, pos);
	}*/

	// 添加生物群系特有的生物
	/*public override void SpawnMob(IWorld world, IGrainFactory grainFactory, ChunkColumnStorage &chunk, Random rand, BlockWorldPos pos)
	{
		ChunkWorldPos chunkPos = pos.ToChunkWorldPos();
		int seed = chunkPos.Z * 16384 + chunkPos.X;
		Random r = new Random(seed);
		foreach(MobType eachType in _passiveMobList)
		{
			if (r.Next(32) == 0)
			{
				PassiveMobSpawner spawner = new PassiveMobSpawner(eachType, 15);
				spawner.Spawn(world, grainFactory, chunk, rand, new BlockWorldPos(pos.X, pos.Y, pos.Z));
			}
		}
	}*/

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

	//public void GenTrees(IWorld world, IGrainFactory grainFactory, ChunkColumnStorage &chunk, Random random, BlockWorldPos pos)
	//{
	//	int treesPerChunk = _treesPerChunk;

	//	if (random.NextDouble() < _extraTreeChance)
	//	{
	//		++treesPerChunk;
	//	}

	//	for (int num = 0; num < treesPerChunk; ++num)
	//	{
	//		int x = random.Next(12) + 2;
	//		int z = random.Next(12) + 2;

	//		TreeGenerator treeGenerator = new TreeGenerator(5, false, GetRandomTree(random));

	//		// 获得地表面高度
	//		int h = 0;
	//		for (int y = 255; y >= 0; --y)
	//		{
	//			if (!chunk[x, y, z].IsAir())
	//			{
	//				h = y + 1;
	//				break;
	//			}
	//		}

	//		treeGenerator.Generate(world, grainFactory, chunk, this, random, new BlockWorldPos(pos.X + x, h, pos.Z + z));
	//	}
	//}
};

class BiomeForest : public Biome
{
public:
	BiomeForest(BiomeProperties properties, GeneratorSettings genSettings)
		: Biome(properties, genSettings)
	{
		_name = "forest";
		_biomeId = BiomeId::Forest;
		/*_treesPerChunk = 10;
		_grassPerChunk = 2;*/

		_temperature = 0.7F;
		_rainfall = 0.8F;
		_enableRain = true;

		/*_passiveMobList.Add(MobType.Pig);
		_passiveMobList.Add(MobType.Sheep);
		_passiveMobList.Add(MobType.Cow);
		_passiveMobList.Add(MobType.Chicken);

		_monsterList.Add(MobType.Creeper);
		_monsterList.Add(MobType.Zombie);
		_monsterList.Add(MobType.Skeleton);
		_monsterList.Add(MobType.Spider);*/
	}

	// 添加其他东西
	//public override void Decorate(IWorld world, IGrainFactory grainFactory, ChunkColumnStorage &chunk, Random rand, BlockWorldPos pos)
	//{
	//	float grassColor = (_grassColorNoise.Noise((pos.X + 8) / 200.0F, 0.0F, (pos.Z + 8) / 200.0F) - 0.5F) * 2;

	//	if (grassColor < -0.8F)
	//	{
	//		_flowersPerChunk = 15;
	//		_grassPerChunk = 5 * 7;
	//		GenDoubleFlowers(world, grainFactory, chunk, rand, pos);
	//	}
	//	else
	//	{
	//		_flowersPerChunk = 4;
	//		_grassPerChunk = 10 * 7;
	//	}

	//	GenGrass(world, grainFactory, chunk, rand, pos);
	//	GenFlowers(world, grainFactory, chunk, rand, pos);
	//	GenDoubleGrass(world, grainFactory, chunk, rand, pos);

	//	int treesPerChunk = _treesPerChunk;

	//	if (rand.NextDouble() < _extraTreeChance)
	//	{
	//		++treesPerChunk;
	//	}

	//	for (int num = 0; num < treesPerChunk; ++num)
	//	{
	//		int x = rand.Next(12) + 2;
	//		int z = rand.Next(12) + 2;

	//		TreeGenerator treeGenerator = new TreeGenerator(5, false, GetRandomTree(rand));

	//		// 获得地表面高度
	//		int h = 0;
	//		for (int y = 255; y >= 0; --y)
	//		{
	//			if (!chunk[x, y, z].IsAir())
	//			{
	//				h = y + 1;
	//				break;
	//			}
	//		}

	//		treeGenerator.Generate(world, grainFactory, chunk, this, rand, new BlockWorldPos(pos.X + x, h, pos.Z + z));
	//	}

	//	base.Decorate(world, grainFactory, chunk, rand, pos);
	//}

	//// 添加生物群系特有的生物
	//public override void SpawnMob(IWorld world, IGrainFactory grainFactory, ChunkColumnStorage &chunk, Random rand, BlockWorldPos pos)
	//{
	//	ChunkWorldPos chunkPos = pos.ToChunkWorldPos();
	//	int seed = chunkPos.Z * 16384 + chunkPos.X;
	//	Random r = new Random(seed);
	//	foreach(MobType eachType in _passiveMobList)
	//	{
	//		if (r.Next(32) == 0)
	//		{
	//			PassiveMobSpawner spawner = new PassiveMobSpawner(eachType, 15);
	//			spawner.Spawn(world, grainFactory, chunk, rand, new BlockWorldPos(pos.X, pos.Y, pos.Z));
	//		}
	//	}
	//}

	//private void GenGrass(IWorld world, IGrainFactory grainFactory, ChunkColumnStorage &chunk, Random random, BlockWorldPos pos)
	//{
	//	int grassMaxNum = random.Next(_grassPerChunk);
	//	GrassGenerator generator = new GrassGenerator();
	//	for (int grassNum = 0; grassNum < grassMaxNum; ++grassNum)
	//	{
	//		int x = random.Next(16);
	//		int z = random.Next(16);
	//		for (int y = 255; y >= 1; --y)
	//		{
	//			if (!chunk[x, y, z].IsAir())
	//			{
	//				generator.Generate(world, grainFactory, chunk, this, random, new BlockWorldPos(pos.X + x, y + 1, pos.Z + z));
	//				break;
	//			}
	//		}
	//	}
	//}

	//private void GenFlowers(IWorld world, IGrainFactory grainFactory, ChunkColumnStorage &chunk, Random random, BlockWorldPos pos)
	//{
	//	int flowersMaxNum = random.Next(_flowersPerChunk);
	//	FlowersGenerator generator = new FlowersGenerator();
	//	for (int flowersNum = 0; flowersNum < flowersMaxNum; ++flowersNum)
	//	{
	//		int x = random.Next(16);
	//		int z = random.Next(16);
	//		for (int y = 255; y >= 1; --y)
	//		{
	//			if (!chunk[x, y, z].IsAir())
	//			{
	//				generator.Generate(world, grainFactory, chunk, this, random, new BlockWorldPos(pos.X + x, y + 1, pos.Z + z));
	//				break;
	//			}
	//		}
	//	}
	//}

	//private void GenDoubleFlowers(IWorld world, IGrainFactory grainFactory, ChunkColumnStorage &chunk, Random random, BlockWorldPos pos)
	//{
	//	DoubleFlowersGenerator generator = new DoubleFlowersGenerator(PlantsType.Sunflower);
	//	for (int flowersNum = 0; flowersNum < 10; ++flowersNum)
	//	{
	//		int x = random.Next(16);
	//		int z = random.Next(16);
	//		for (int y = 255; y >= 1; --y)
	//		{
	//			if (!chunk[x, y, z].IsAir())
	//			{
	//				generator.Generate(world, grainFactory, chunk, this, random, new BlockWorldPos(pos.X + x, y + 1, pos.Z + z));
	//				break;
	//			}
	//		}
	//	}
	//}

	//private void GenDoubleGrass(IWorld world, IGrainFactory grainFactory, ChunkColumnStorage &chunk, Random random, BlockWorldPos pos)
	//{
	//	DoubleGrassGenerator generator = new DoubleGrassGenerator(PlantsType.DoubleTallgrass);
	//	for (int grassNum = 0; grassNum < 2; ++grassNum)
	//	{
	//		int x = random.Next(16);
	//		int z = random.Next(16);
	//		for (int y = 255; y >= 1; --y)
	//		{
	//			if (!chunk[x, y, z].IsAir())
	//			{
	//				generator.Generate(world, grainFactory, chunk, this, random, new BlockWorldPos(pos.X + x, y + 1, pos.Z + z));
	//				break;
	//			}
	//		}
	//	}
	//}
};

namespace BiomeTaigaType
{
	int Normal = 1;
	int Mega = 2;
	int MegaSpruce = 3;
};

class BiomeTaiga : public Biome
{
private:
	//BiomeTaigaType _type;

public:
	BiomeTaiga(/*BiomeTaigaType type, */BiomeProperties properties, GeneratorSettings genSettings)
		: Biome(properties, genSettings)
	{
		_name = "taiga";
		_biomeId = BiomeId::Taiga;

		_baseHeight = 0.2F;
		_heightVariation = 0.2F;
		_temperature = 0.25F;

		/*_treesPerChunk = 10;
		_grassPerChunk = 2;*/

		_temperature = 0.7F;
		_rainfall = 0.8F;
		_enableRain = true;

		//_type = type;

		/*if (type != BiomeTaigaType.Mega && type != BiomeTaigaType.MegaSpruce)
		{
			_grassPerChunk = 1;
			_mushroomsPerChunk = 1;
		}
		else
		{
			_grassPerChunk = 7;
			_deadBushPerChunk = 1;
			_mushroomsPerChunk = 3;
		}

		_passiveMobList.Add(MobType.Pig);
		_passiveMobList.Add(MobType.Sheep);
		_passiveMobList.Add(MobType.Cow);
		_passiveMobList.Add(MobType.Chicken);

		_monsterList.Add(MobType.Creeper);
		_monsterList.Add(MobType.Zombie);
		_monsterList.Add(MobType.Skeleton);
		_monsterList.Add(MobType.Spider);*/
	}

	// 生物群中可能的树
	// 随机获得一个该生物群系可能出现的树
	//public override PlantsType GetRandomTree(Random rand)
	//{
	//	return PlantsType.Spruce;
	//}

	//// 添加其他东西
	//public override void Decorate(IWorld world, IGrainFactory grainFactory, ChunkColumnStorage &chunk, Random rand, BlockWorldPos pos)
	//{
	//	float grassColor = (_grassColorNoise.Noise((pos.X + 8) / 200.0F, 0.0F, (pos.Z + 8) / 200.0F) - 0.5F) * 2;

	//	if (grassColor < -0.8F)
	//	{
	//		_flowersPerChunk = 15;
	//		_grassPerChunk = 5 * 7;
	//		GenDoubleFlowers(world, grainFactory, chunk, rand, pos);
	//	}
	//	else
	//	{
	//		_flowersPerChunk = 4;
	//		_grassPerChunk = 10 * 7;
	//	}

	//	GenGrass(world, grainFactory, chunk, rand, pos);
	//	GenFlowers(world, grainFactory, chunk, rand, pos);
	//	GenDoubleGrass(world, grainFactory, chunk, rand, pos);

	//	int treesPerChunk = _treesPerChunk;

	//	if (rand.NextDouble() < _extraTreeChance)
	//	{
	//		++treesPerChunk;
	//	}

	//	for (int num = 0; num < treesPerChunk; ++num)
	//	{
	//		int x = rand.Next(10) + 3;
	//		int z = rand.Next(10) + 3;

	//		AbstractTreeGenerator treeGenerator;
	//		PlantsType type = GetRandomTree(rand);

	//		if (type == PlantsType.Spruce)
	//		{
	//			if (x % 2 == 0)
	//				treeGenerator = new Taiga2Generator(5, false, type);
	//			else
	//				treeGenerator = new TaigaGenerator(5, false, type);
	//		}
	//		else
	//		{
	//			treeGenerator = new TreeGenerator(5, false, type);
	//		}

	//		// 获得地表面高度
	//		int h = 0;
	//		for (int y = 255; y >= 0; --y)
	//		{
	//			if (!chunk[x, y, z].IsAir())
	//			{
	//				h = y + 1;
	//				break;
	//			}
	//		}

	//		treeGenerator.Generate(world, grainFactory, chunk, this, rand, new BlockWorldPos(pos.X + x, h, pos.Z + z));
	//	}

	//	base.Decorate(world, grainFactory, chunk, rand, pos);
	//}

	//// 添加生物群系特有的生物
	//public override void SpawnMob(IWorld world, IGrainFactory grainFactory, ChunkColumnStorage &chunk, Random rand, BlockWorldPos pos)
	//{
	//	ChunkWorldPos chunkPos = pos.ToChunkWorldPos();
	//	int seed = chunkPos.Z * 16384 + chunkPos.X;
	//	Random r = new Random(seed);
	//	foreach(MobType eachType in _passiveMobList)
	//	{
	//		if (r.Next(32) == 0)
	//		{
	//			PassiveMobSpawner spawner = new PassiveMobSpawner(eachType, 15);
	//			spawner.Spawn(world, grainFactory, chunk, rand, new BlockWorldPos(pos.X, pos.Y, pos.Z));
	//		}
	//	}
	//}

	//private void GenGrass(IWorld world, IGrainFactory grainFactory, ChunkColumnStorage &chunk, Random random, BlockWorldPos pos)
	//{
	//	int grassMaxNum = random.Next(_grassPerChunk);
	//	GrassGenerator generator = new GrassGenerator();
	//	for (int grassNum = 0; grassNum < grassMaxNum; ++grassNum)
	//	{
	//		int x = random.Next(16);
	//		int z = random.Next(16);
	//		for (int y = 255; y >= 1; --y)
	//		{
	//			if (!chunk[x, y, z].IsAir())
	//			{
	//				generator.Generate(world, grainFactory, chunk, this, random, new BlockWorldPos(pos.X + x, y + 1, pos.Z + z));
	//				break;
	//			}
	//		}
	//	}
	//}

	//private void GenFlowers(IWorld world, IGrainFactory grainFactory, ChunkColumnStorage &chunk, Random random, BlockWorldPos pos)
	//{
	//	int flowersMaxNum = random.Next(_flowersPerChunk);
	//	FlowersGenerator generator = new FlowersGenerator();
	//	for (int flowersNum = 0; flowersNum < flowersMaxNum; ++flowersNum)
	//	{
	//		int x = random.Next(16);
	//		int z = random.Next(16);
	//		for (int y = 255; y >= 1; --y)
	//		{
	//			if (!chunk[x, y, z].IsAir())
	//			{
	//				generator.Generate(world, grainFactory, chunk, this, random, new BlockWorldPos(pos.X + x, y + 1, pos.Z + z));
	//				break;
	//			}
	//		}
	//	}
	//}

	//private void GenDoubleFlowers(IWorld world, IGrainFactory grainFactory, ChunkColumnStorage &chunk, Random random, BlockWorldPos pos)
	//{
	//	DoubleFlowersGenerator generator = new DoubleFlowersGenerator(PlantsType.Sunflower);
	//	for (int flowersNum = 0; flowersNum < 10; ++flowersNum)
	//	{
	//		int x = random.Next(16);
	//		int z = random.Next(16);
	//		for (int y = 255; y >= 1; --y)
	//		{
	//			if (!chunk[x, y, z].IsAir())
	//			{
	//				generator.Generate(world, grainFactory, chunk, this, random, new BlockWorldPos(pos.X + x, y + 1, pos.Z + z));
	//				break;
	//			}
	//		}
	//	}
	//}

	//private void GenDoubleGrass(IWorld world, IGrainFactory grainFactory, ChunkColumnStorage &chunk, Random random, BlockWorldPos pos)
	//{
	//	DoubleGrassGenerator generator = new DoubleGrassGenerator(PlantsType.DoubleTallgrass);
	//	for (int grassNum = 0; grassNum < 2; ++grassNum)
	//	{
	//		int x = random.Next(16);
	//		int z = random.Next(16);
	//		for (int y = 255; y >= 1; --y)
	//		{
	//			if (!chunk[x, y, z].IsAir())
	//			{
	//				generator.Generate(world, grainFactory, chunk, this, random, new BlockWorldPos(pos.X + x, y + 1, pos.Z + z));
	//				break;
	//			}
	//		}
	//	}
	//}
};

class BiomeSwamp : public Biome
{
public:
	BiomeSwamp(BiomeProperties properties, GeneratorSettings genSettings)
		: Biome(properties, genSettings)
	{
		_name = "swampland";
		_biomeId = BiomeId::Swampland;

		/*_treesPerChunk = 2;
		_flowersPerChunk = 1;
		_deadBushPerChunk = 1;
		_mushroomsPerChunk = 8;
		_reedsPerChunk = 10;
		_clayPerChunk = 1;
		_waterlilyPerChunk = 4;
		_sandPatchesPerChunk = 0;
		_gravelPatchesPerChunk = 0;
		_grassPerChunk = 5;*/

		_baseHeight = -0.2F;
		_heightVariation = 0.1F;
		_temperature = 0.8F;
		_rainfall = 0.9F;
		_enableRain = true;
		_waterColor = 14745518;
	}

	//// 添加其他东西
	//public override void Decorate(IWorld world, IGrainFactory grainFactory, ChunkColumnStorage &chunk, Random rand, BlockWorldPos pos)
	//{
	//	float grassColor = (_grassColorNoise.Noise((pos.X + 8) / 200.0F, 0.0F, (pos.Z + 8) / 200.0F) - 0.5F) * 2;

	//	if (grassColor < -0.8F)
	//	{
	//		_flowersPerChunk = 15;
	//		_grassPerChunk = 5 * 7;
	//		GenDoubleFlowers(world, grainFactory, chunk, rand, pos);
	//	}
	//	else
	//	{
	//		_flowersPerChunk = 4;
	//		_grassPerChunk = 10 * 7;
	//	}

	//	GenGrass(world, grainFactory, chunk, rand, pos);
	//	GenFlowers(world, grainFactory, chunk, rand, pos);
	//	GenDoubleGrass(world, grainFactory, chunk, rand, pos);

	//	int treesPerChunk = _treesPerChunk;

	//	if (rand.NextDouble() < _extraTreeChance)
	//	{
	//		++treesPerChunk;
	//	}

	//	for (int num = 0; num < treesPerChunk; ++num)
	//	{
	//		int x = rand.Next(10) + 3;
	//		int z = rand.Next(10) + 3;

	//		TreeGenerator treeGenerator = new TreeGenerator(5, true, GetRandomTree(rand));

	//		// 获得地表面高度
	//		int h = 0;
	//		for (int y = 255; y >= 0; --y)
	//		{
	//			if (!chunk[x, y, z].IsAir())
	//			{
	//				h = y + 1;
	//				break;
	//			}
	//		}

	//		treeGenerator.Generate(world, grainFactory, chunk, this, rand, new BlockWorldPos(pos.X + x, h, pos.Z + z));
	//	}

	//	base.Decorate(world, grainFactory, chunk, rand, pos);
	//}

	//// 添加生物群系特有的生物
	//public override void SpawnMob(IWorld world, IGrainFactory grainFactory, ChunkColumnStorage &chunk, Random rand, BlockWorldPos pos)
	//{
	//	ChunkWorldPos chunkPos = pos.ToChunkWorldPos();
	//	int seed = chunkPos.Z * 16384 + chunkPos.X;
	//	Random r = new Random(seed);
	//	foreach(MobType eachType in _passiveMobList)
	//	{
	//		if (r.Next(32) == 0)
	//		{
	//			PassiveMobSpawner spawner = new PassiveMobSpawner(eachType, 10);
	//			spawner.Spawn(world, grainFactory, chunk, rand, new BlockWorldPos(pos.X, pos.Y, pos.Z));
	//		}
	//	}
	//}

	//private void GenGrass(IWorld world, IGrainFactory grainFactory, ChunkColumnStorage &chunk, Random random, BlockWorldPos pos)
	//{
	//	int grassMaxNum = random.Next(_grassPerChunk);
	//	GrassGenerator generator = new GrassGenerator();
	//	for (int grassNum = 0; grassNum < grassMaxNum; ++grassNum)
	//	{
	//		int x = random.Next(16);
	//		int z = random.Next(16);
	//		for (int y = 255; y >= 1; --y)
	//		{
	//			if (!chunk[x, y, z].IsAir())
	//			{
	//				generator.Generate(world, grainFactory, chunk, this, random, new BlockWorldPos(pos.X + x, y + 1, pos.Z + z));
	//				break;
	//			}
	//		}
	//	}
	//}

	//private void GenFlowers(IWorld world, IGrainFactory grainFactory, ChunkColumnStorage &chunk, Random random, BlockWorldPos pos)
	//{
	//	int flowersMaxNum = random.Next(_flowersPerChunk);
	//	FlowersGenerator generator = new FlowersGenerator();
	//	for (int flowersNum = 0; flowersNum < flowersMaxNum; ++flowersNum)
	//	{
	//		int x = random.Next(16);
	//		int z = random.Next(16);
	//		for (int y = 255; y >= 1; --y)
	//		{
	//			if (!chunk[x, y, z].IsAir())
	//			{
	//				generator.Generate(world, grainFactory, chunk, this, random, new BlockWorldPos(pos.X + x, y + 1, pos.Z + z));
	//				break;
	//			}
	//		}
	//	}
	//}

	//private void GenDoubleFlowers(IWorld world, IGrainFactory grainFactory, ChunkColumnStorage &chunk, Random random, BlockWorldPos pos)
	//{
	//	DoubleFlowersGenerator generator = new DoubleFlowersGenerator(PlantsType.Sunflower);
	//	for (int flowersNum = 0; flowersNum < 10; ++flowersNum)
	//	{
	//		int x = random.Next(16);
	//		int z = random.Next(16);
	//		for (int y = 255; y >= 1; --y)
	//		{
	//			if (!chunk[x, y, z].IsAir())
	//			{
	//				generator.Generate(world, grainFactory, chunk, this, random, new BlockWorldPos(pos.X + x, y + 1, pos.Z + z));
	//				break;
	//			}
	//		}
	//	}
	//}

	//private void GenDoubleGrass(IWorld world, IGrainFactory grainFactory, ChunkColumnStorage &chunk, Random random, BlockWorldPos pos)
	//{
	//	DoubleGrassGenerator generator = new DoubleGrassGenerator(PlantsType.DoubleTallgrass);
	//	for (int grassNum = 0; grassNum < 2; ++grassNum)
	//	{
	//		int x = random.Next(16);
	//		int z = random.Next(16);
	//		for (int y = 255; y >= 1; --y)
	//		{
	//			if (!chunk[x, y, z].IsAir())
	//			{
	//				generator.Generate(world, grainFactory, chunk, this, random, new BlockWorldPos(pos.X + x, y + 1, pos.Z + z));
	//				break;
	//			}
	//		}
	//	}
	//}
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

		/*_treesPerChunk = -999;
		_deadBushPerChunk = 0;
		_reedsPerChunk = 0;
		_cactiPerChunk = 0;*/
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
		return BiomeTaiga(/*BiomeTaigaType::Normal, */BiomeProperties(), settings);
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