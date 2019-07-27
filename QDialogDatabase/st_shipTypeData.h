#ifndef ST_SHIPTYPEDATA_H
#define ST_SHIPTYPEDATA_H



#define  SHIPMAX 200
#define  SHIPTYPE_NUM 100

//船灯颜色
typedef struct _ST_SHIP_LIGHT_COLOR{
    float r;
    float g;
    float b;
    float a;
}ST_SHIP_LIGHT_COLOR;

//船灯属性
typedef struct _ST_SHIP_LIT{
    long		lType;
    float		dOffset[3];						//the offset position with the center of ship
    long		lColor;							//the value of color
    float		dVect[2][3];					//the vector of light in the different orient
    long		lMode;							//the mode of light  when mode = 2 means the angle of light > 180,
    //Given mode = 3, then angle < 180
}ST_SHIP_LIT, *pST_SHIP_LIT;

typedef struct _ST_SHIP_LINE{
    long		lActive;
    long		lLineId;
    float		dOffset[3];						//the offset position with the center of ship
    float		dDiameter;
    float		dLength;
}ST_SHIP_LINE, *pST_SHIP_LINE;

typedef struct _ST_SHIPTYPE{
    float			dBowOffset;					//ship back wake position
    float			dSternOffset;				//ship before wake position
    float			dLen;					    //ship length
    float			dBreadth;				    //ship breadth
    bool			bLit;					    //whether does ship light flash
    float          dEyeHeight;				    //eye height
    float          dOriginOffset;				//the distance between the center and cab of ship
    long			bLightNumber;
    float			dLightSize;					//the size of light
    char			szOsModelPath[255];
    char			szTargetModelPath[255];
    float			dRollFactor;
    float			dPitchFactor;
    float			dBowSternSmooth;
    float			dPortStarbSmooth;
    ST_SHIP_LIT		stLight[64];			//ship light status
    ST_SHIP_LINE    stLine[26];				//[0]: the head line, [25]: tail line
}ST_SHIPTYPE;

//船舶模型的位置参数，单位：米、弧度
typedef struct _WPOS
{
    double dX,dY,dZ,dH,dP,dR;
}WPOS;

#endif // ST_SHIPTYPEDATA_H
