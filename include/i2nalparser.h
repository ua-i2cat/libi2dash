/*
 *  Libi2dash - is an ANSI C DASH library in development of ISO/IEC 23009-1
 *  Copyright (C) 2014  Fundació i2CAT, Internet i Innovació digital a Catalunya
 *
 *  This file is part of libi2dash.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Authors:		Martin German <martin.german@i2cat.net>
 *
 */

#ifndef __I2NALPARSER_H__
#define __I2NALPARSER_H__

#define MAXIGROUP 512
#define MAXMATRIX 267 //255+12
#define MAXCNTCYCLE 255
#define MAXLENGTHPPS 6
#define FPICPARAMETERSETID 0x80
#define FSEQPARAMETERSETID 0x40
#define FENTROPYCODINGMODEFLAG 0x20
#define FNUMSLICEGROUPMINUS1 0x08
#define FSLICEGROUPSMAPTYPE 0x07
#define FTOPLEFT 0xF0
#define FBOTTOMRIGHT 0x0F
#define FSLICEGROUPCHANGEDIRECTIONFLAG 0x80
#define FSLICEGROUPCHANGERATEMINUS1 0x7F
#define FNUMREFIDX10DEFAULTACTIVEMINUS1 0x07
#define FNUMREFIDX11DEFAULTACTIVEMINUS1 0x80
#define FWEIGHTEDPREDFLAG 0x40
#define FWEIGHTEDBIPREDIDC 0x30
#define FPICINITQPMINUS26H 0x0F
#define FPICINITQPMINUS26L 0x80
#define FSIGNOQP26 0x0F
#define FPICINITQSMINUS26 0x40
#define FSIGNOQS26 0x0F
#define FCHROMAQPINDEXOFFSET 0x3E
#define FDEBLOCKINGFILTERTCONTROLPRESENTFLAG 0x01
#define FCONSTRAINEDINTRAPREDFLAG 0x80
#define FREDUNDANTPICCNTPRESENTLAG 0x40
#define FTRANSFORM8X8MODEFLAG 0x20
#define FPICSACALINGMATRIXPRESENTFLAG 0x10

#define FPICINITQPMINUS26H 0x0F
#define FPICINITQPMINUS26L 0x80


typedef unsigned char byte;



#include <netinet/in.h>

typedef struct {
	byte picParameterSetId; //ue(v)
	byte seqParameterSetId; //ue(v)
	byte entropyCondingModeFlag; //u(1)
	byte bottomFieldPicOrderInFramePresentFlag; //u(1)
	byte numSliceGroupsMinus1; //ue(v)
	byte sliceGroupMapType; //ue(v)
	byte runLengthMinus1[MAXIGROUP]; //ue(v)
	byte topLef[MAXIGROUP]; //ue(v)
	byte bottomRight[MAXIGROUP]; //ue(v)
	byte sliceGroupChangeDirectionFlag; //u(1)
	byte sliceGroupChangeRateMinus1; //ue(v)
	byte picSizeInMapUnitsMinus1; //ue(v)
	byte sliceGroupId[MAXIGROUP]; //u(v)
	byte numRefIdx10DefaultActiveMinus1; //ue(v)
	byte numRefIdx11DefaultActiveMinus1; //ue(v)
	byte weightedPredFlag; //u(1)
	byte weightedBipredIdc; //u(2)
	byte picInitQpMinus26; //se(v)
	byte picInitQsMinus26; //se(v)
	byte chromaQpIndexOffset; //se(v)
	byte deblockingFilterControlPresentFlag; //u(1)
	byte constrainedIntraPredFlag; //u(1)
	byte redundantPicCntPresentFlag; //u(1)
	byte transform8x8ModeFlag; //u(1)
	byte picScalingMatrixPresentFlag; //u(1)
	byte picScalingListPresentFlag[12]; //u(1)
	byte secondChromaQpIndexOffset; //se(v)
} ppsStruct;

typedef struct {
	byte profileIdc;
	byte constraintSet0Flag; //u(8)
	byte constraintSet1Flag; //u(1)
	byte constraintSet2Flag; //u(1)
	byte constraintSet3Flag; //u(1)
	byte constraintSet4Flag; //u(1)
	byte constraintSet5Flag; //u(1)
	byte reservedZero2bits; //u(2)
	byte levelIdc; //u(8)
	byte seqParameterSetId; //ue(v)
	byte chromaFormatIdc; //ue(v)
	byte separateColourPlaneFlag; //u(1)
	byte bitDepthLumaMinus8; //ue(v)
	byte bitDepthChromaMinus8; //ue(v)
	byte qpprimeYZeroTransformBypassFlag; //u(1)
	byte seqScalingMatrixPresentFlag; //u(1)
	byte seqScalingListPresentFlag[MAXMATRIX]; //u(1)
	byte log2MaxFrameNumMinus4; //ue(v)
	byte picOrderCntType; //ue(v)
	byte log2MaxPicOrderCntLsbMinus4; //ue(v)
	byte DeltaPicOrderAlwaysZeroFlag; //u(1)
	int offsetForNonRefPic; //se(v)
	int offsetForTopToBottomField; //se(v)
	byte numRefFramesInPicOrderCntCycle; //ue(v)
	int offserForRefFrame[MAXCNTCYCLE]; //se(v)
	byte maxNumRefFrames; //ue(v)
	byte gapsInFrameNumValueAlloweFlag; //u(1)
	byte picWidthInMbsMinus1; //ue(v)
	byte picHeightInMapUnitsMinus1; //ue(v)
	byte framMbsOnlyFlag; //u(1)
	byte mbAdaptiveFrameFieldFlag; //u(1)
	byte direct8x8InferenceFlag; //u(1)
	byte frameCroppinFlag; //u(1)
	byte frameCroppinLeftOffset; //u(1)
	byte frameCroppinRightOffset; //u(1)
	byte frameCroppinTopOffset; //u(1)
	byte frameCroppinBottomOffset; //u(1)
	byte vuiParametersPresentFlag; //u(1)

} spsStruct;

typedef struct {
	ppsStruct pps;
	spsStruct sps;
} nalHeader;

bool ppsToRbsp(unsigned char* ppsHeader, uint32_t ppsLength, nalHeader* headers);
bool spsToRbsp(unsigned char* spsHeader, uint32_t spsLength, nalHeader* headers);
uint32_t getWidth(nalHeader headers);
uint32_t getHeight(nalHeader headers);

#endif
