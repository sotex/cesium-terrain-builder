#include "gdal_priv.h"
#include "cpl_vsi.h"
#include "TerrainTiler.hpp"
#include "TileCoordinate.hpp"
#include "GlobalGeodetic.hpp"

using namespace ctb;

int main(int argc,char** v)
{
	if(argc != 6){
		printf("Usage:%s inputfile outfile zoom x y\n    eg. %s dem.tif tmp.terrain 3 4 5\n",v[0],v[0]);
		return 0;
	}
	GDALAllRegister();

	GlobalGeodetic grid;
	GDALDataset* hDS = NULL;
	hDS = (GDALDataset*) GDALOpen(v[1],GA_ReadOnly);
	if(hDS == NULL){ return -1;}

	TerrainTiler tiler(hDS,grid);

	int z = atoi(v[3]);
	int x = atoi(v[4]);
	int y = atoi(v[5]);

	TileCoordinate c(z,x,y);

	TerrainTile* tile = tiler.createTile(c);
	tile->writeFile(v[2]);
	delete tile;
	return 0;
}
