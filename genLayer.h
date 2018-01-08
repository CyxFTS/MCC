#pragma once
#include <vector>
#include <cstdlib>
using namespace std;

enum BiomeId
{
	Ocean = 0,
	Plains = 1,
	Desert = 2,
	ExtremeHills = 3,
	Forest = 4,
	Taiga = 5,
	Swampland = 6,
	River = 7,
	Beach = 16
};

class GenLayer
{
protected:
	int _baseSeed;
	GenLayer *_parent;

public:
	GenLayer() {  }
	GenLayer(int seed, GenLayer *parent)
	{
		_baseSeed = seed;
		_parent = parent;
	}

	virtual vector<vector<int>> GetInts(int areaX, int areaY, int areaWidth, int areaHeight)
	{
		return _parent->GetInts(areaX, areaY, areaWidth, areaHeight);
	}

	static GenLayer* GenLayerZoomMagnify(int seed, GenLayer* layer, int times);

	static GenLayer* InitAllLayer(int seed);

	static int SelectRandom(int seed, vector<int> arrys)
	{
		//srand(seed);
		return arrys[rand() % arrys.size()];
	}

	static int SelectModeOrRandom(int seed, int a, int b, int c, int d)
	{
		if (a == b || a == c || a == d)
		{
			return a;
		}
		else if (b == c || b == d)
		{
			return b;
		}
		else if (c == d)
		{
			return c;
		}
		else
		{
			return SelectRandom(seed, { a, b, c, d });
		}
	}
	int GetChunkSeed(int x, int z)
	{
		return z * _baseSeed + x;
	}
};

class GenLayerIsland: public GenLayer
{
public:

	GenLayerIsland(int seed, GenLayer* parent)
	{
		_baseSeed = seed;
		_parent = parent;
	}

	vector<vector<int>> GetInts(int areaX, int areaY, int areaWidth, int areaHeight)
	{
		vector<vector<int>> result(areaHeight, vector<int>(areaWidth));

		for (int i = 0; i < areaHeight; ++i)
		{
			for (int j = 0; j < areaWidth; ++j)
			{
				srand(GetChunkSeed(areaX + j, areaY + i));
				result[i][j] = rand()%3 == 0 ? 1 : 0;
			}
		}

		if (-areaWidth < areaX && areaX <= 0 && -areaHeight < areaY && areaY <= 0)
		{
			result[-areaY][ -areaX] = (int)Plains;
		}

		return result;
	}
};

class GenLayerZoom : public GenLayer
{
public:
	GenLayerZoom(int seed, GenLayer* parent)
	{
		_baseSeed = seed;
		_parent = parent;
	}

	vector<vector<int>> GetInts(int areaX, int areaY, int areaWidth, int areaHeight)
	{
		// parent�߶��Ǳ����1/2
		int parentAreaX = areaX > 0 ? areaX / 2 : (areaX - 1) / 2;
		int parentAreaY = areaY > 0 ? areaY / 2 : (areaY - 1) / 2;

		// +2��ӱ߽�
		int parentWidth = areaWidth / 2 + 2;
		int parentHeight = areaHeight / 2 + 2;

		// parentRes�Ǳ����1/4
		vector<vector<int>> parentRes = _parent->GetInts(parentAreaX, parentAreaY, parentWidth, parentHeight);
		int tmpWidth = (parentWidth - 1) * 2;
		int tmpHeight = (parentHeight - 1) * 2;

		// ��ʱ���
		vector<vector<int>> tmp(tmpHeight, vector<int>(tmpWidth));

		for (int parentY = 0; parentY < parentHeight - 1; ++parentY)
		{
			// parent��ǰ���ֵ
			int parentValue = parentRes[parentY][ 0];

			// parent��ǰ��y+1���ֵ
			int parentValueY1 = parentRes[parentY + 1][0];

			for (int parentX = 0; parentX < parentWidth - 1; ++parentX)
			{
				int randomSeed = GetChunkSeed((parentX + parentAreaX) * 2, (parentY + parentAreaY) * 2);
				srand(randomSeed);
				// parent��ǰ��x+1���ֵ
				int parentValueX1 = parentRes[parentY][parentX + 1];

				// parent��ǰ��x+1, y+1���ֵ
				int parentValueX1Y1 = parentRes[parentY + 1][parentX + 1];

				// ��ǰ��ֵ = parent��ֵ
				tmp[parentY * 2][parentX * 2] = parentValue;

				// ��ǰ��y+1ֵ = �� parent�㡢parent��y+1 �����ѡ
				tmp[parentY * 2 + 1][parentX * 2] = SelectRandom(randomSeed, { parentValue, parentValueY1 });

				// ��ǰ��ֵ = �� parent�㡢parent��x+1 �����ѡ
				tmp[parentY * 2][parentX * 2 + 1] = SelectRandom(randomSeed, { parentValue, parentValueX1 });

				// ��ǰ��y+1ֵ = parent�ĸ���ֵ�е����������ѡ
				tmp[parentY * 2 + 1][parentX * 2 + 1] = SelectModeOrRandom(randomSeed, parentValue, parentValueX1, parentValueY1, parentValueX1Y1);

				// parent��ǰ���ƶ�x+1
				parentValue = parentValueX1;
				parentValueY1 = parentValueX1Y1;
			}
		}

		vector<vector<int>> result(areaHeight, vector<int>(areaWidth));

		// tmp��result�ߴ���ܲ�ͬ�������tmp�м䲿�ָ��Ƶ�result
		int areaOffsetX = abs(areaX % 2);
		int areaOffsetY = abs(areaY % 2);
		for (int resultY = 0; resultY < areaHeight; ++resultY)
		{
			for (int resultX = 0; resultX < areaWidth; ++resultX)
			{
				result[resultY][resultX] = tmp[resultY + areaOffsetY][resultX + areaOffsetX];
			}
		}

		return result;
	}
	
	
};
static bool allDesert = false;
static bool allHills = false;
class GenLayerBiome : public GenLayer
{
public:
	GenLayerBiome(int seed, GenLayer* parent)
	{
		_baseSeed = seed;
		_parent = parent;
	}

	vector<vector<int>> GetInts(int areaX, int areaY, int areaWidth, int areaHeight)
	{
		vector<vector<int>> parentResult = _parent->GetInts(areaX, areaY, areaWidth, areaHeight);
		for (int i = 0; i < areaHeight; ++i)
		{
			for (int j = 0; j < areaWidth; ++j)
			{
				srand(GetChunkSeed(areaX + j, areaY + i));
				if (parentResult[i][j] == (int)Plains)
				{
					int r = rand() % 10;// random.Next(10);
					if (r >= 0 && r < 1)
					{
						parentResult[i][j] = allHills ? (int)ExtremeHills : (allDesert ? (int)Desert : (int)Plains);
					}
					else if (r >= 1 && r < 2)
					{
						parentResult[i][j] = (int)Desert;// = allHills ? (int)ExtremeHills : (allDesert ? (int)Desert : (int)Plains);
					}
					else if (r >= 2 && r < 3)
					{
						parentResult[i][j] = (int)ExtremeHills;
					}
					else if (r >= 3 && r < 6)
					{
						parentResult[i][j] = (int)Desert;
					}
					else if (r >= 6 && r < 8)
					{
						parentResult[i][j] = (int)Desert;
					}
				}
			}
		}

		return parentResult;
	}
};

class GenLayerAddIsland : public GenLayer
{
public:
	GenLayerAddIsland(int seed, GenLayer* parent)
	{
		_baseSeed = seed;
		_parent = parent;
	}

	vector<vector<int>> GetInts(int areaX, int areaY, int areaWidth, int areaHeight)
	{
		int parentAreaX = areaX - 1;
		int parentAreaY = areaY - 1;
		int parentWidth = areaWidth + 2;
		int parentHeight = areaHeight + 2;
		vector<vector<int>> parentRes = _parent->GetInts(parentAreaX, parentAreaY, parentWidth, parentHeight);
		vector<vector<int>> result(areaHeight, vector<int>(areaWidth)); //new int[areaHeight, areaWidth];

		for (int y = 0; y < areaHeight; ++y)
		{
			for (int x = 0; x < areaWidth; ++x)
			{
				// ��x+1 y+1Ϊ���ģ�X�Ͳ���5����
				int parentValue = parentRes[y][x];
				int parentValueX2 = parentRes[y][ x + 2];
				int parentValueY2 = parentRes[y + 2][x];
				int parentValueX2Y2 = parentRes[y + 2][x + 2];
				int parentValueX1Y1 = parentRes[y + 1][x + 1];
				int randomSeed = GetChunkSeed(x + areaX, y + areaY);
				srand(randomSeed);

				// ���Ĳ�Ϊ0 �� ��Χȫ��0
				if (parentValueX1Y1 != 0 || (parentValue == 0 && parentValueX2 == 0 && parentValueY2 == 0 && parentValueX2Y2 == 0))
				{
					// ����>0 �� ��Χ������0
					if (parentValueX1Y1 > 0 && (parentValue == 0 || parentValueX2 == 0 || parentValueY2 == 0 || parentValueX2Y2 == 0))
					{
						// 1/5���ʱ�Ϊ����
						if (rand()%5 == 0)
						{
							// ������ɭ���򲻱�Ϊ����
							if (parentValueX1Y1 == 4)
							{
								result[y][x] = 4;
							}
							else
							{
								result[y][x] = 0;
							}
						}
						else
						{
							result[y][x] = parentValueX1Y1;
						}
					}
					else
					{
						result[y][x] = parentValueX1Y1;
					}
				}
				else
				{
					// �����еķ�ĸ
					int deno = 1;
					int value = 1;

					// ѡ��һ����Ϊ0��ֵ��Խ��������ѡ�ĸ���ԽС
					if (parentValue != 0 && rand()%(deno++) == 0)
					{
						value = parentValue;
					}

					if (parentValueX2 != 0 && rand()%(deno++) == 0)
					{
						value = parentValueX2;
					}

					if (parentValueY2 != 0 && rand()%(deno++) == 0)
					{
						value = parentValueY2;
					}

					if (parentValueX2Y2 != 0 && rand()%(deno++) == 0)
					{
						value = parentValueX2Y2;
					}

					// 1/3�ĸ�������Ϊ�ղ�ѡ��ֵ
					if (rand()%(3) == 0)
					{
						result[y][x] = value;
					}
					else if (value == 4)
					{
						// ɭ��
						result[y][x] = 4;
					}
					else
					{
						result[y][x] = 0;
					}
				}
			}
		}

		return result;
	}
};

class GenLayerAddBeach : public GenLayer
{
public:
	GenLayerAddBeach(int seed, GenLayer* parent)
	{
		_baseSeed = seed;
		_parent = parent;
	}

	vector<vector<int>> GetInts(int areaX, int areaY, int areaWidth, int areaHeight)
	{
		int parentAreaX = areaX - 1;
		int parentAreaY = areaY - 1;
		int parentWidth = areaWidth + 2;
		int parentHeight = areaHeight + 2;
		vector<vector<int>> parentRes = _parent->GetInts(parentAreaX, parentAreaY, parentWidth, parentHeight);
		vector<vector<int>> result(areaHeight, vector<int>(areaWidth));// = new int[areaHeight, areaWidth];

		for (int y = 0; y < areaHeight; ++y)
		{
			for (int x = 0; x < areaWidth; ++x)
			{
				// ��x+1 y+1Ϊ���ģ�X�Ͳ���5����
				int parentValue = parentRes[y][x];
				int parentValueX2 = parentRes[y][x + 2];
				int parentValueY2 = parentRes[y + 2][x];
				int parentValueX2Y2 = parentRes[y + 2][x + 2];
				int parentValueX1Y1 = parentRes[y + 1][x + 1];
				int randomSeed = GetChunkSeed(x + areaX, y + areaY);

				// Random random = new Random(randomSeed);

				// ���Ĳ�Ϊ0 �� ��Χ��0
				if (parentValueX1Y1 != 0 && (parentValue == 0 || parentValueX2 == 0 || parentValueY2 == 0 || parentValueX2Y2 == 0))
				{
					if (parentValueX1Y1 != (int)ExtremeHills)
						result[y][x] = (int)Beach;
				}
				else
				{
					result[y][x] = parentValueX1Y1;
				}
			}
		}

		return result;
	}
};

class GenLayerAddRiver : public GenLayer
{
public:
	GenLayerAddRiver(int seed, GenLayer* parent)
	{
		_baseSeed = seed;
		_parent = parent;
	}

	vector<vector<int>> GetInts(int areaX, int areaY, int areaWidth, int areaHeight)
	{
		int parentAreaX = areaX - 1;
		int parentAreaY = areaY - 1;
		int parentWidth = areaWidth + 2;
		int parentHeight = areaHeight + 2;

		// parent�Ǿ����Ŵ��GenLayerRiverInit
		vector<vector<int>> parentRes = _parent->GetInts(parentAreaX, parentAreaY, parentWidth, parentHeight);
		vector<vector<int>> result(areaHeight, vector<int>(areaWidth));// = new int[areaHeight, areaWidth];

		for (int y = 0; y < areaHeight; ++y)
		{
			for (int x = 0; x < areaWidth; ++x)
			{
				// ���ϲ������0��2��3�����
				int randomValueY1 = parentRes[y + 1][x];
				int randomValueX2Y1 = parentRes[y + 1][x + 2];
				int randomValueX1 = parentRes[y][x + 1];
				int randomValueX1Y2 = parentRes[y + 2][x + 1];
				int randomValueX1Y1 = parentRes[y + 1][x + 1];

				int tmpx, tmpy;
				if (x + areaX >= 0) tmpx = (x + areaX) / 64;
				else tmpx = (x + areaX) / 64 - 1;
				if (y + areaY >= 0) tmpy = (y + areaY) / 64;
				else tmpy = (y + areaY) / 64 - 1;

				int seed = GetChunkSeed(tmpx, tmpy);
				srand(seed);

				if (randomValueX1Y1 == randomValueY1
					&& randomValueX1Y1 == randomValueX1
					&& randomValueX1Y1 == randomValueX2Y1
					&& randomValueX1Y1 == randomValueX1Y2)
				{
					// ���ĺ���Χ���
					result[y][x] = randomValueX1Y1;
				}
				else if (rand()%(5) == 0)
				{
					// ����
					if (randomValueX1Y1 != (int)Ocean &&
						randomValueX1Y1 != (int)Beach)
						result[y][x] = (int)River;
				}
				else
				{
					result[y][x] = randomValueX1Y1;
				}
			}
		}

		return result;
	}

	// value >= 2�򷵻�2~3������������򷵻�value
private :
	int RandomValue(int value)
	{
		return value >= 2 ? 2 + value % 2 : value;
	}
};

GenLayer* GenLayer::GenLayerZoomMagnify(int seed, GenLayer* layer, int times)
{
	GenLayer* genlayer = layer;

	for (int i = 0; i < times; ++i)
	{
		genlayer = new GenLayerZoom(seed + 1, genlayer);
	}

	return genlayer;
}

GenLayer* GenLayer::InitAllLayer(int seed)
{
	GenLayer *addIsland0 = new GenLayerIsland(seed, nullptr);
	GenLayer *zoomed0 = new GenLayerZoom(seed, addIsland0);

	GenLayer *biomesAdded = new GenLayerBiome(seed, zoomed0);
	GenLayer *addIsland1 = new GenLayerAddIsland(2, biomesAdded);
	GenLayer *zoomed1 = new GenLayerZoom(seed, addIsland1);
	GenLayer *addIsland2 = new GenLayerAddIsland(50, zoomed1);

	// GenLayer zoomed2 = new GenLayerZoom(seed, zoomed0);
	GenLayer *zoomed2 = GenLayerZoomMagnify(seed, addIsland2, 4);

	GenLayer *addBeach = new GenLayerAddBeach(50, zoomed2);
	GenLayer *addBeach2 = new GenLayerAddBeach(50, addBeach);
	GenLayer *zoomed3 = new GenLayerZoom(seed, addBeach2);
	GenLayer *addRiver = new GenLayerAddRiver(1000, zoomed3);

	GenLayer *result = GenLayerZoomMagnify(seed, addRiver, 2);
	return result;
}