#pragma once
struct BlockState
{
public:
	BlockState() = default;
	BlockState(unsigned int id, unsigned int value)
	{
		Id = id;
		MetaValue = value;
	}

	unsigned int Id;

	unsigned int MetaValue;

	bool IsSameId(BlockState other)
	{
		return Id == other.Id;
	}

	bool Equals(BlockState other)
	{
		return Id == other.Id &&
			MetaValue == other.MetaValue;
	}

	bool operator ==(BlockState state2)
	{
		return this->Equals(state2);
	}

	bool operator !=(BlockState state2)
	{
		return !(*this == state2);
	}
};

enum BlockId
{
	Air = 0,
	Stone = 1,
	GrassBlock = 2,
	Dirt = 3,
	Cobblestone = 4,
	WoodPlanks = 5,
	Sapling = 6,
	Bedrock = 7,
	Water = 8,
	StationaryWater = 9,
	Lava = 10,
	StationaryLava = 11,
	Sand = 12,
	Gravel = 13,
	GoldOre = 14,
	IronOre = 15,
	CoalOre = 16,
	Wood = 17,
	Leaves = 18,
	Sponge = 19,
	Glass = 20,
	LapisLazuliOre = 21,
	LapisLazuliBlock = 22,
	Dispenser = 23,
	Sandstone = 24,
	NoteBlock = 25,
	Bed = 26,
	PoweredRail = 27,
	DetectorRail = 28,
	StickyPiston = 29,
	Cobweb = 30,
	Grass = 31,
	
};

enum WoodPlankType
{
	Oak = 0
};

namespace StoneType
{
	int Stone = 0;
};

namespace DirtType
{
	int Dirt = 0;
};

enum FluidType
{
	Level1 = 0,
	FallingFlag = 0x8
};

namespace SandType
{
	int Sand = 0;
};

////[Flags]
namespace WoodType
{
	int Oak = 0;
};


namespace LeaveType
{
	int Oak = 0;
};



namespace GrassType
{
int Shrub = 0;
int TallGrass = 1;
int Fern = 2
;};
