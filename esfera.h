#ifndef __ESFERA_H_INCLUDED_
#define __ESFERA_H_INCLUDED_

#define RAIO_TERRA 128
#define PERIODO_ROT_TERRA 48
#define PERIODO_TRANS_TERRA PERIODO_ROT_TERRA*365
#define INCLINACAO_TERRA 23.5/180.0*PI
#define GRAVIDADE_TERRA 0.001
#define DIST_TERRA_SOL 1496*RAIO_TERRA

#define RAIO_SOL 7*RAIO_TERRA
#define PERIODO_ROT_SOL PERIODO_ROT_TERRA*28

#define INCLINACAO_MARTE 25.33/180.0*PI
#define PERIODO_ROT_MARTE (int)(PERIODO_ROT_TERRA*1.0275)
#define PERIODO_TRANS_MARTE (int)(PERIODO_TRANS_TERRA*1.88)
#define GRAVIDADE_MARTE GRAVIDADE_TERRA*0.378
#define RAIO_MARTE RAIO_TERRA/2
#define DIST_MARTE_SOL (int)(DIST_TERRA_SOL*1.52)

#define LATITUDES 15
#define LONGITUDES 15

#define PI 3.14159265358979

#endif
