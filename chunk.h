#pragma once
#include <vector>
#include <block.h>
using namespace std;

enum ChunkConstants
{
	SectionsPerChunk = 16,

	BlockEdgeWidthInSection = 16,
	
	BlocksInSection = BlockEdgeWidthInSection * BlockEdgeWidthInSection * BlockEdgeWidthInSection
};

class ChunkSectionStorage
{
public:
	ChunkSectionStorage() {};
	BlockState Data[ChunkConstants::BlockEdgeWidthInSection][ChunkConstants::BlockEdgeWidthInSection][ChunkConstants::BlockEdgeWidthInSection];

	ChunkSectionStorage(bool hasSkylight)
	{
		/*if (hasSkylight)
			SkyLight = new byte[ChunkConstants.BlockEdgeWidthInSection, ChunkConstants.BlockEdgeWidthInSection, ChunkConstants.BlockEdgeWidthInSection];*/
	}
};

class ChunkColumnStorage
{
public:
	ChunkColumnStorage() {};
	ChunkSectionStorage Sections[ChunkConstants::SectionsPerChunk];

	int Biomes[256];

	BlockState& operator ()(int x, int y, int z)
	{
		return Sections[y / 16].Data[x][y % 16][z];
	}
};