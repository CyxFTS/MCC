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

	/*bool Equals(object obj)
	{
		return obj is BlockState && Equals((BlockState)obj);
	}*/

	bool Equals(BlockState other)
	{
		return Id == other.Id &&
			MetaValue == other.MetaValue;
	}

	/*int GetHashCode()
	{
		auto hashCode = -81208087;
		hashCode = hashCode * -1521134295 + base.GetHashCode();
		hashCode = hashCode * -1521134295 + Id.GetHashCode();
		hashCode = hashCode * -1521134295 + MetaValue.GetHashCode();
		return hashCode;
	}*/

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
	DeadBush = 32,
	Piston = 33,
	PistonHead = 34,
	Wool = 35,
	BlockMovedByPiston = 36,
	Dandelion = 37,
	Poppy = 38,
	BrownMushroom = 39,
	RedMushroom = 40,
	BlockOfGold = 41,
	BlockOfIron = 42,
	DoubleStoneSlab = 43,
	StoneSlab = 44,
	Bricks = 45,
	TNT = 46,
	Bookshelf = 47,
	MossStone = 48,
	Obsidian = 49,
	Torch = 50,
	Fire = 51,
	MonsterSpawner = 52,
	OakWoodStairs = 53,
	Chest = 54,
	RedstoneWire = 55,
	DiamondOre = 56,
	BlockOfDiamond = 57,
	CraftingTable = 58,
	Wheat = 59,
	Farmland = 60,
	Furnace = 61,
	BurningFurnace = 62,
	StandingSign = 63,
	OakDoor = 64,
	Ladder = 65,
	Rail = 66,
	CobblestoneStairs = 67,
	WallSign = 68,
	Lever = 69,
	StonePressurePlate = 70,
	IronDoor = 71,
	WoodenPressurePlate = 72,
	RedstoneOre = 73,
	GlowingRedstoneOre = 74,
	RedstoneTorchInactive = 75,
	RedstoneTorchActive = 76,
	StoneButton = 77,
	SnowLayer = 78,
	Ice = 79,
	Snow = 80,
	Cactus = 81,
	Clay = 82,
	SugarCane = 83,
	Jukebox = 84,
	OakFence = 85,
	Pumpkin = 86,
	Netherrack = 87,
	SoulSand = 88,
	Glowstone = 89,
	NetherPortal = 90,
	JackLantern = 91,
	Cake = 92,
	RedstoneRepeaterInactive = 93,
	RedstoneRepeaterActive = 94,
	StainedGlass = 95,
	Trapdoor = 96,
	MonsterEgg = 97,
	StoneBricks = 98,
	BrownMushroomBlock = 99,
	RedMushroomBlock = 100,
	IronBars = 101,
	GlassPane = 102,
	Melon = 103,
	PumpkinStem = 104,
	MelonStem = 105,
	Vines = 106,
	FenceGate = 107,
	BrickStairs = 108,
	StoneBrickStairs = 109,
	Mycelium = 110,
	LilyPad = 111,
	NetherBrick = 112,
	NetherBrickFence = 113,
	NetherBrickStairs = 114,
	NetherWart = 115,
	EnchantmentTable = 116,
	BrewingStand = 117,
	Cauldron = 118,
	EndPortal = 119,
	EndPortalFrame = 120,
	EndStone = 121,
	DragonEgg = 122,
	RedstoneLampInactive = 123,
	RedstoneLampActive = 124,
	DoubleWoodenSlab = 125,
	WoodenSlab = 126,
	Cocoa = 127,
	SandstoneStairs = 128,
	EmeraldOre = 129,
	EnderChest = 130,
	TripwireHook = 131,
	Tripwire = 132,
	BlockOfEmerald = 133,
	SpruceWoodStairs = 134,
	BirchWoodStairs = 135,
	JungleWoodStairs = 136,
	CommandBlock = 137,
	Beacon = 138,
	CobblestoneWall = 139,
	FlowerPot = 140,
	Carrot = 141,
	Potato = 142,
	WoodenButton = 143,
	Mobhead = 144,
	Anvil = 145,
	TrappedChest = 146,
	WeightedPressurePlateLight = 147,
	WeightedPressurePlateHeavy = 148,
	RedstoneComparator = 149,
	RedstoneComparatorDeprecated = 150,
	DaylightSensor = 151,
	BlockOfRedstone = 152,
	NetherQuartzOre = 153,
	Hopper = 154,
	BlockOfQuartz = 155,
	QuartzStairs = 156,
	ActivatorRail = 157,
	Dropper = 158,
	StainedClay = 159,
	StainedGlassPane = 160,
	Leaves2 = 161,
	Wood2 = 162,
	AcaciaWoodStairs = 163,
	DarkOakWoodStairs = 164,
	SlimeBlock = 165,
	Barrier = 166,
	IronTrapdoor = 167,
	Prismarine = 168,
	SeaLantern = 169,
	HayBale = 170,
	Carpet = 171,
	HardenedClay = 172,
	BlockOfCoal = 173,
	PackedIce = 174,
	LargeFlowers = 175,
	StandingBanner = 176,
	WallBanner = 177,
	InvertedDaylightSensor = 178,
	RedSandstone = 179,
	RedSandstoneStairs = 180,
	DoubleRedSandstoneSlab = 181,
	RedSandstoneSlab = 182,
	SpruceFenceGate = 183,
	BirchFenceGate = 184,
	JungleFenceGate = 185,
	DarkOakFenceGate = 186,
	AcaciaFenceGate = 187,
	SpruceFence = 188,
	BirchFence = 189,
	JungleFence = 190,
	DarkOakFence = 191,
	AcaciaFence = 192,
	SpruceDoor = 193,
	BirchDoor = 194,
	JungleDoor = 195,
	AcaciaDoor = 196,
	DarkOakDoor = 197,
	EndRod = 198,
	ChorusPlant = 199,
	ChorusFlower = 200,
	PurpurBlock = 201,
	PurpurPillar = 202,
	PurpurStairs = 203,
	PurpurDoubleSlab = 204,
	PurpurSlab = 205,
	EndStoneBricks = 206,
	BeetrootSeeds = 207,
	GrassPath = 208,
	EndGateway = 209,
	RepeatingCommandBlock = 210,
	ChainCommandBlock = 211,
	FrostedIce = 212,
	MagmaBlock = 213,
	NetherWartBlock = 214,
	RedNetherBrick = 215,
	BoneBlock = 216,
	StructureVoid = 217,
	Observer = 218,
	WhiteShulkerBox = 219,
	OrangeShulkerBox = 220,
	MagentaShulkerBox = 221,
	LightBlueShulkerBox = 222,
	YellowShulkerBox = 223,
	LimeShulkerBox = 224,
	PinkShulkerBox = 225,
	GrayShulkerBox = 226,
	LightGrayShulkerBox = 227,
	CyanShulkerBox = 228,
	PurpleShulkerBox = 229,
	BlueShulkerBox = 230,
	BrownShulkerBox = 231,
	GreenShulkerBox = 232,
	RedShulkerBox = 233,
	BlackShulkerBox = 234,
	WhiteGlazedTerracotta = 235,
	OrangeGlazedTerracotta = 236,
	MagentaGlazedTerracotta = 237,
	LightBlueGlazedTerracotta = 238,
	YellowGlazedTerracotta = 239,
	LimeGlazedTerracotta = 240,
	PinkGlazedTerracotta = 241,
	GrayGlazedTerracotta = 242,
	LightGrayGlazedTerracotta = 243,
	CyanGlazedTerracotta = 244,
	PurpleGlazedTerracotta = 245,
	BlueGlazedTerracotta = 246,
	BrownGlazedTerracotta = 247,
	GreenGlazedTerracotta = 248,
	RedGlazedTerracotta = 249,
	BlackGlazedTerracotta = 250,
	Concrete = 251,
	ConcretePowder = 252,
	StructureBlock = 255
};

enum WoodPlankType
{
	Oak = 0,
	Spruce = 1,
	Birch = 2,
	Jungle = 3,
	Acacia = 4,
	DarkOak = 5
};

namespace StoneType
{
	int Stone = 0;
	int Granite = 1;
	int PolishedGranite = 2;
	int Diorite = 3;
	int PolishedDiorite = 4;
	int Andesite = 5;
	int PolishedAndesite = 6;
};

namespace DirtType
{
	int Dirt = 0;
	int CoarseDirt = 1;
	int Podzol = 2;
};

////[Flags]
namespace SaplingsType
{
	int Oak = 0;
	int Spruce = 1;
	int Birch = 2;
	int Jungle = 3;
	int Acacia = 4;
	int DarkOak = 5;

	// 0x8 bit field : Set if sapling is ready to grow into a tree
	int ReadyForTreeFlag = 0x8;
};

/// <summary>
/// Attributes of water and lava.
///
/// If FallingFlag is set, the lower bits are essentially ignored,
/// since this block is then at its highest fluid level.
/// Level1 is the highest fluid level(not necessarily filling the block -
/// this depends on the neighboring fluid blocks above each upper corner of the block)
/// </summary>
////[Flags]
enum FluidType
{
	Level1 = 0,
	Level2 = 1,
	Level3 = 2,
	Level4 = 3,
	Level5 = 4,
	Level6 = 5,
	Level7 = 6,
	Level8 = 7,

	// 0x8 bit field : If set, this liquid is "falling" and only spreads downward
	FallingFlag = 0x8
};

namespace SandType
{
	int Sand = 0;
	int RedSand = 1;
};

////[Flags]
namespace WoodType
{
	int Oak = 0;
	int Spruce = 1;
	int Birch = 2;
	int Jungle = 3;

	// 0x4 ~ 0x8 bits field specifying the orientation of the wood
	int FacingUpFlag = 0x0;
	int FacingEastFlag = 0x4;
	int FacingNorthFlag = 0x8;
	int OnlybarkFlag = 0xC;
};

////[Flags]
namespace Wood2Type
{
	int Acacia = 0;
	int DarkOak = 1;

	// 0x4 ~ 0x8 bits field specifying the orientation of the wood
	int FacingUpFlag = 0x0;
	int FacingEastFlag = 0x4;
	int FacingNorthFlag = 0x8;
	int OnlybarkFlag = 0xC;
};

namespace LeaveType
{
	int Oak = 0;
	int Spruce = 1;
	int Birch = 2;
	int Jungle = 3;
	int OakLeaves = 4;
	int SpruceNoDecay = 5;
	int BirchNoDecay = 6;
	int JungleNoDecay = 7;
	int OakCheckDecay = 8;
	int SpruceCheckDecay = 9;
	int BirchCheckDecay = 10;
	int JungleCheckDecay = 11;
	int OakNoDecayAndCheckDecay = 12;
	int SpruceNoDecayAndCheckDecay = 13;
	int BirchNoDecayAndCheckDecay = 14;
	int JungleNoDecayAndCheckDecay = 15;
};

namespace Leave2Type
{
	int Acacia = 0;
	int DarkOak = 1;
	int AcaciaNoDecay = 4;
	int DarkOakNoDecay = 5;
	int AcaciaCheckDecay = 8;
	int DarkOakCheckDecay = 9;
	int AcaciaNoDecayAndCheckDecay = 12;
	int DarkOakNoDecayAndCheckDecay = 13;
};

/// <summary>
/// Specifies the color of the wool, stained terracotta, stained glass and carpet.
/// </summary>
namespace BlockColorType
{
	int White = 0;
	int Orange = 1;
	int Magenta = 2;
	int LightBlue = 3;
	int Yellow = 4;
	int Lime = 5;
	int Pink = 6;
	int Gray = 7;
	int LightGray = 8;
	int Cyan = 9;
	int Purple = 10;
	int Blue = 11;
	int Brown = 12;
	int Green = 13;
	int Red = 14;
	int Black = 15;
};

namespace TorchesType
{
	int FacingEast = 1;
	int FacingWest = 2;
	int FacingSouth = 3;
	int FacingNorth = 4;
	int FacingUp = 5;
};

namespace DoubleStoneSlabType
{
	int Stone = 0;
	int Sandstone = 1;
	int Wooden = 2;
	int Cobblestone = 3;
	int Bricks = 4;
	int StoneBrick = 5;
	int NetherBrick = 6;
	int Quartz = 7;
	int SmoothStone = 8;
	int SmoothSandstone = 9;
	int TileQuartz = 15;
};

namespace DoubleRedSandstoneSlabType
{
	int Normal = 0;
	int Smooth = 8;
};

namespace StoneSlabType
{
	int Stone = 0;
	int Sandstone = 1;
	int Wooden = 2;
	int Cobblestone = 3;
	int Bricks = 4;
	int StoneBrick = 5;
	int NetherBrick = 6;
	int Quartz = 7;
	int UpperStone = 8;
	int UpperSandstone = 9;
	int UpperWooden = 10;
	int UpperCobblestone = 11;
	int UpperBricks = 12;
	int UpperStoneBrick = 13;
	int UpperNetherBrick = 14;
	int UpperQuartz = 15;
};

namespace RedSandstoneSlabType
{
	int Normal = 0;
	int Upper = 1;
};

namespace DoubleWoodenSlabType
{
	int Oak = 0;
	int Spruce = 1;
	int Birch = 2;
	int Jungle = 3;
	int Acacia = 4;
	int DarkOak = 5;
};

namespace WoodenSlabType
{
int Oak = 0;
int Spruce = 1;
int Birch = 2;
int Jungle = 3;
int Acacia = 4;
int DarkOak = 5;
int UpperOak = 8;
int UpperSpruce = 9;
int UpperBirch = 10;
int UpperJungle = 11;
int UpperAcacia = 12;
int UpperDarkOak = 13;
};

namespace FireType
{
int Placed = 0x0;
int Eternal = 0xF
;};

namespace SandstoneType
{
int Normal = 0;
int Chiseled = 1;
int Smooth = 2
;};

namespace RedSandstoneType
{
int Normal = 0;
int Chiseled = 1;
int Smooth = 2
;};

//[Flags]
namespace BedType
{
int HeadFacingSouth = 0;
int HeadFacingWest = 1;
int HeadFacingNorth = 2;
int HeadFacingEast = 3;

// 0x4 bit field : When 0; the bed is empty; otherwise; the bed is occupied
int OccupiedFlag = 0x4;

// 0x8 bit field : When 0; the foot of the bed; otherwise; the head of the bed
int HeadFlag = 0x8
;};

namespace GrassType
{
int Shrub = 0;
int TallGrass = 1;
int Fern = 2
;};

namespace FlowerType
{
int Poppy = 0;
int BlueOrchid = 1;
int Allium = 2;
int AzureBluet = 3;
int RedTulip = 4;
int OrangeTulip = 5;
int WhiteTulip = 6;
int PinkTulip = 7;
int OxeyeDaisy = 8
;};

//[Flags]
namespace LargeFlowerType
{
int Sunflower = 0;
int Lilac = 1;
int DoubleTallgrass = 2;
int LargeFern = 3;
int RoseBush = 4;
int Peony = 5;

// 0x8 bit field : Top Half of any Large Plant; low three bits 0x7 are derived from the block below
int TopHalfFlag = 0x8
;};

//[Flags]
namespace PistionType
{
int Down = 0;
int Up = 1;
int North = 2;
int South = 3;
int West = 4;
int East = 5;

// 0x8 bit field : Determines whether the piston is pushed out or not. 1 for pushed out; 0 for retracted
int PushedOutFlag = 0x8
;};

//[Flags]
namespace PistionExType
{
int Down = 0;
int Up = 1;
int North = 2;
int South = 3;
int West = 4;
int East = 5;

// 0x8 bit field : Determines whether the head is sticky or not(note that the Piston Body actually
// has completely different block types for Sticky and Regular). 1 is sticky; 0 is regular
int StickyFlag = 0x8
;};

//[Flags]
namespace StairsType
{
int East = 0;
int West = 1;
int South = 2;
int North = 3;

// 0x4 bit field : Set if stairs are upside-down
int UpsideDownFlag = 0x4
;};

/// <summary>
/// Specifies the redstone dust's current redstone power level.
/// </summary>
namespace RedstoneWireType
{
int Level1 = 0;
int Level2 = 1;
int Level3 = 2;
int Level4 = 3;
int Level5 = 4;
int Level6 = 5;
int Level7 = 6;
int Level8 = 7;
int Level9 = 8;
int Level10 = 9;
int Level11 = 10;
int Level12 = 11;
int Level13 = 12;
int Level14 = 13;
int Level15 = 14;
int Level16 = 15;
;};

/// <summary>
/// Represents the daylight sensor's current redstone power level.
/// </summary>
namespace DaylightSensorType
{
int Level1 = 0;
int Level2 = 1;
int Level3 = 2;
int Level4 = 3;
int Level5 = 4;
int Level6 = 5;
int Level7 = 6;
int Level8 = 7;
int Level9 = 8;
int Level10 = 9;
int Level11 = 10;
int Level12 = 11;
int Level13 = 12;
int Level14 = 13;
int Level15 = 14;
int Level16 = 15;
;};

/// <summary>
/// Crops grow from 0x0 to 0x7. Carrots; beetroot and potatoes appear to have 4 stages;
/// but actually grow identically to wheat; merely using the same texture for multiple stages.
/// </summary>
namespace CropsType
{
int GrowStage1 = 0;
int GrowStage2 = 1;
int GrowStage3 = 2;
int GrowStage4 = 3;
int GrowStage5 = 4;
int GrowStage6 = 5;
int GrowStage7 = 6;
int GrowStage8 = 7;
;};

namespace FarmlandType
{
int DryLand = 0;
int WetnessLevel1 = 1;
int WetnessLevel2 = 2;
int WetnessLevel3 = 3;
int WetnessLevel4 = 4;
int WetnessLevel5 = 5;
int WetnessLevel6 = 6;
int WetnessLevel7 = 7;
;};

namespace StandingBannerType
{
int South = 0;
int SouthToSouthwest = 1;
int Southwest = 2;
int WestToSouthwest = 3;
int West = 4;
int WestToNorthwest = 5;
int Northwest = 6;
int NorthToNorthwest = 7;
int North = 8;
int NorthToNortheast = 9;
int Northeast = 10;
int EastToNortheast = 11;
int East = 12;
int EastToSoutheast = 13;
int Southeast = 14;
int SouthToSoutheast = 15
;};

namespace WallBannerType
{
int North = 2;
int South = 3;
int West = 4;
int East = 5
;};

//[Flags]
namespace DoorType
{
int NorthwestCorner = 0;
int NortheastCorner = 1;
int SoutheastCorner = 2;
int SouthwestCorner = 3;

// 0x4 bit field : If set; the door has swung counterclockwise around its hinge
int HasSwungCounterclockwiseFlag = 0x4;

// 0x8 bit field : If set; this is the top half of a door (else the bottom half of the door)
int TopHalfOfTheDoorFlag = 0x8
;};

namespace RailType
{
int StraightRailConnectNS = 0;
int StraightRailConnectEW = 1;
int SlopedRailAscendEast = 2;
int SlopedRailAscendWest = 3;
int SlopedRailAscendNorth = 4;
int SlopedRailAscendSouth = 5;
int CurvedRailConnectSE = 6;
int CurvedRailConnectSW = 7;
int CurvedRailConnectNW = 8;
int CurvedRailConnectNE = 9
;};

/// <summary>
/// For Activator Rails; Detector Rails; and Powered Rails
/// </summary>
namespace RailExType
{
int FlatTrackGoingNS = 0;
int FlatTrackGoingWE = 1;
int SlopedTrackAscendEast = 2;
int SlopedTrackAscendWest = 3;
int SlopedTrackAscendNorth = 4;
int SlopedTrackAscendSouth = 5;
;};

/// <summary>
/// For Ladders; Furnaces; Chests; Trapped Chests
/// </summary>
namespace FacingDirectionType
{
int FacingNorth = 2;
int FacingSouth = 3;
int FacingWest = 4;
int FacingEast = 5;
;};

namespace StandingSignType
{
int South = 0;
int SouthToSouthwest = 1;
int Southwest = 2;
int WestToSouthwest = 3;
int West = 4;
int WestToNorthwest = 5;
int Northwest = 6;
int NorthToNorthwest = 7;
int North = 8;
int NorthToNortheast = 9;
int Northeast = 10;
int EastToNortheast = 11;
int East = 12;
int EastToSoutheast = 13;
int Southeast = 14;
int SouthToSoutheast = 15
;};

namespace WallSignType
{
int North = 2;
int South = 3;
int West = 4;
int East = 5
;};

/// <summary>
/// 0x1 ~ 0x4 bits specifying which direction the dispenser is facing
/// </summary>
//[Flags]
namespace DispenserType
{
int FacingDown = 0;
int FacingUp = 1;
int FacingNorth = 2;
int FacingSouth = 3;
int FacingWest = 4;
int FacingEast = 5;

// 0x8 bit field : If set; the dispenser is activated
int ActivatedFlag = 0x8
;};

/// <summary>
/// 0x1 ~ 0x4 bits specifying which direction the dropper is facing
/// </summary>
//[Flags]
namespace DropperType
{
int FacingDown = 0;
int FacingUp = 1;
int FacingNorth = 2;
int FacingSouth = 3;
int FacingWest = 4;
int FacingEast = 5;

// 0x8 bit field : If set; the dropper is activated
int ActivatedFlag = 0x8
;};

//[Flags]
namespace HopperType
{
int FacingDown = 0;
int FacingNorth = 2;
int FacingSouth = 3;
int FacingWest = 4;
int FacingEast = 5;

// 0x8 bit field : Set if activated/disabled
int ActivatedFlag = 0x8
;};

//[Flags]
namespace LeverType
{
int BottomPointsEastWhenOff = 0;
int SideFacingEast = 1;
int SideFacingWest = 2;
int SideFacingSouth = 3;
int SideFacingNorth = 4;
int TopPointsSouthWhenOff = 5;
int TopPointsEastWhenOff = 6;
int BottomPointsSouthWhenOff = 7;

// 0x8 bit field : If set; the lever is active
int ActivatedFlag = 0x8
;};

namespace PressurePlatesType
{
int None = 0;
int Active = 1
;};

/// <summary>
/// Represents the weighted pressure plate's current redstone power level.
/// </summary>
namespace WeightedPressurePlateType
{
int Level1 = 0;
int Level2 = 1;
int Level3 = 2;
int Level4 = 3;
int Level5 = 4;
int Level6 = 5;
int Level7 = 6;
int Level8 = 7;
int Level9 = 8;
int Level10 = 9;
int Level11 = 10;
int Level12 = 11;
int Level13 = 12;
int Level14 = 13;
int Level15 = 14;
int Level16 = 15;
;};

//[Flags]
namespace ButtonType
{
int BottomFacingDown = 0;
int SideFacingEast = 1;
int SideFacingWest = 2;
int SideFacingSouth = 3;
int SideFacingNorth = 4;
int TopFacingUp = 5;

// 0x8 bit field : If set; the button is currently active
int ActivatedFlag = 0x8
;};

namespace SnowType
{
int OneLayer = 0;
int TwoLayers = 1;
int ThreeLayers = 2;
int FourLayers = 3;
int FiveLayers = 4;
int SixLayers = 5;
int SevenLayers = 6;
int EightLayers = 7
;};

namespace CactusType
{
int FreshlyPlanted = 0;
int Interval1 = 1;
int Interval2 = 2;
int Interval3 = 3;
int Interval4 = 4;
int Interval5 = 5;
int Interval6 = 6;
int Interval7 = 7;
int Interval8 = 8;
int Interval9 = 9;
int Interval10 = 10;
int Interval11 = 11;
int Interval12 = 12;
int Interval13 = 13;
int Interval14 = 14;
int Interval15 = 15
;};

namespace SugarCaneType
{
int FreshlyPlanted = 0;
int Interval1 = 1;
int Interval2 = 2;
int Interval3 = 3;
int Interval4 = 4;
int Interval5 = 5;
int Interval6 = 6;
int Interval7 = 7;
int Interval8 = 8;
int Interval9 = 9;
int Interval10 = 10;
int Interval11 = 11;
int Interval12 = 12;
int Interval13 = 13;
int Interval14 = 14;
int Interval15 = 15
;};

namespace JuckboxType
{
int NoDiscInserted = 0;
int ContainsADisc = 1
;};

namespace PumpkinType
{
int FacingSouth = 0;
int FacingWest = 1;
int FacingNorth = 2;
int FacingEast = 3;
int WithoutFace = 4
;};

namespace JackLanternType
{
int FacingSouth = 0;
int FacingWest = 1;
int FacingNorth = 2;
int FacingEast = 3;
int WithoutFace = 4
;};

namespace CakeType
{
int Eat0Pieces = 0;
int Eat1Piece = 1;
int Eat2Pieces = 2;
int Eat3Pieces = 3;
int Eat4Pieces = 4;
int Eat5Pieces = 5;
int Eat6Pieces = 6;
;};

//[Flags]
namespace RedstoneRepeaterType
{
int FacingNorth = 0;
int FacingEast = 1;
int FacingSouth = 2;
int FacingWest = 3;

// 0x4 ~ 0x8 bit field specifying the redstone repeater's delay
int Tick1Flag = 0x0;
int Tick2Flag = 0x4;
int Tick3Flag = 0x8;
int Tick4Flag = 0xC
;};

//[Flags]
namespace RedstoneComparatorType
{
int FacingNorth = 0;
int FacingEast = 1;
int FacingSouth = 2;
int FacingWest = 3;

// 0x4 bit field Set if in subtraction mode (front torch up and powered)
int SubtractionModeFlag = 0x4;

// 0x8 bit field Set if powered (at any power level)
int PoweredFlag = 0x8
;};

//[Flags]
namespace TrapdoorType
{
int SouthSide = 0;
int NorthSide = 1;
int EastSide = 2;
int WestSide = 3;

// 0x4 bit field : If set; the trapdoor is open
int OpenFlag = 0x4;

// 0x8 bit field : If set; the trapdoor is on the top half of a block. Otherwise; it is on the bottom half
int TopHalfFlag = 0x8
;};

namespace MonsterEggType
{
int Stone = 0;
int Cobblestone = 1;
int StoneBrick = 2;
int MossyStoneBrick = 3;
int CrackedStoneBrick = 4;
int ChiseledStoneBrick = 5
;};

namespace StoneBrickType
{
int Normal = 0;
int Mossy = 1;
int Cracked = 2;
int Chiseled = 3
;};

namespace PrismarineType
{
int Prismarine = 0;
int PrismarineBricks = 1;
int DarkPrismarine = 2
;};

namespace SpongeType
{
int Sponge = 0;
int WetSponge = 1
;};

namespace MushroomBlockType
{
int PoresOnAllSides = 0;
int CapTextureOnTopWestNorth = 1;
int CapTextureOnTopNorth = 2;
int CapTextureOnTopNorthEast = 3;
int CapTextureOnTopWest = 4;
int CapTextureOnTop = 5;
int CapTextureOnTopEast = 6;
int CapTextureOnTopSouthWest = 7;
int CapTextureOnTopSouth = 8;
int CapTextureOnTopEastSouth = 9;
int StemTextureOnAllFourSidesPoresOnTopBottom = 10;
int CapTextureOnAllSixSides = 11;
int StemTextureOnAllSixSides = 12
;};

namespace PumpkinMelonStemType
{
int FreshlyPlantedStem = 0;
int FirstStageOfGrowth = 1;
int SecondStageOfGrowth = 2;
int ThirdStageOfGrowth = 3;
int FourthStageOfGrowth = 4;
int FifthStageOfGrowth = 5;
int SixthStageOfGrowth = 6;
int SeventhStageOfGrowth = 7
;};

/// <summary>
/// Determines the face against which the vine is anchored.
/// </summary>
namespace VineType
{
int South = 1;
int West = 2;
int North = 4;
int East = 8
;};

//[Flags]
namespace FenceGateType
{
int FacingSouth = 0;
int FacingWest = 1;
int FacingNorth = 2;
int FacingEast = 3;

// 0x4 bit field : 0 if the gate is closed; 1 if open
int OpenFlag = 0x4
;};

namespace NetherWartType
{
int GrowthStage1 = 0;
int GrowthStage2 = 1;
int GrowthStage3 = 2;
int GrowthStage4 = 3;
;};

namespace BrewingStandType
{
int TheSlotPointingSast = 0x1;
int TheSlotPointingSouthwest = 0x2;
int TheSlotPointingNorthwest = 0x4
;};

namespace CauldronType
{
int Empty = 0;
int LittleFilled = 1;
int ManyFilled = 2;
int FullFilled = 3
;};

//[Flags]
namespace EndPortalFrameType
{
int South = 0;
int West = 1;
int North = 2;
int East = 3;

// 0x4 bit field : 0 is an "empty" frame block; 1 is a block with an Eye of Ender inserted
int EyeOfEnderFlag = 0x4
;};

//[Flags]
namespace CocoaType
{
int North = 0;
int East = 1;
int South = 2;
int West = 3;

// 0x4 ~ 0x8 bit field specifying the stage of growth of the plant
int FirstStageFlag = 0x0;
int SecondStageFlag = 0x4;
int FinalStageFlag = 0x8
;};

//[Flags]
namespace TripwireHookType
{
int FacingSouth = 0;
int FacingWest = 1;
int FacingNorth = 2;
int FacingEast = 3;

// 0x4 bit field : If set; the tripwire hook is connected and ready to trip ("middle" position)
int ConnectedFlag = 0x4;

// 0x8 bit field : If set; the tripwire hook is currently activated ("down" position)
int ActivatedFlag = 0x8
;};

//[Flags]
namespace TripwireType
{
int None = 0;

// 0x1 bit field : Set if tripwire is activated (an entity is intersecting its collision mask)
int ActivatedFlag = 0x1;

// 0x4 bit field : Set if tripwire is attached to a valid tripwire circuit
int AttachedFlag = 0x4;

// 0x8 bit field : Set if tripwire is disarmed
int DisarmedFlag = 0x8
;};

namespace CobblestoneWallType
{
int CobblestoneWall = 0;
int MossyCobblestoneWall = 1
;};

namespace FlowerPotType
{
int Empty = 0;
int Poppy = 1;
int Dandelion = 2;
int OakSapling = 3;
int SpruceSapling = 4;
int BirchSapling = 5;
int JungleSapling = 6;
int RedMushroom = 7;
int BrownMushroom = 8;
int Cactus = 9;
int DeadBush = 10;
int Fern = 11;
int AcaciaSapling = 12;
int DarkOakSapling = 13
;};

namespace HeadForBlockType
{
int OnTheFloor = 1;
int OnWallFacingNorth = 2;
int OnWallFacingSouth = 3;
int OnWallFacingEast = 4;
int OnWallFacingWest = 5
;};

namespace BlockOfQuartzType
{
int Normal = 0;
int Chiseled = 1;
int Vertical = 2;
int NorthSouth = 3;
int EastWest = 4
;};

namespace AnvilForBlockType
{
int NorthSouth = 0;
int EastWest = 1;
int SouthNorth = 2;
int WestEast = 3;
int SlightlyDamagedNS = 4;
int SlightlyDamagedEW = 5;
int SlightlyDamagedWE = 6;
int SlightlyDamagedSN = 7;
int VeryDamagedNS = 8;
int VeryDamagedEW = 9;
int VeryDamagedWE = 10;
int VeryDamagedSN = 11
;};