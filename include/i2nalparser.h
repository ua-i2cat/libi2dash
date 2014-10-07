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

#include <cstdlib>

#define MAXIGROUP 512
#define MAXMATRIX 267 //255+12
#define MAXCNTCYCLE 255
#define EXTENDESAR 255
#define MAXCPBCNTMINUSONE 31
//PPS FLAGS
#define MAXLENGTHPPS 6
#define FPICPARAMETERSETID 0x80
#define FPPSSEQPARAMETERSETID 0x40
#define FENTROPYCODINGMODEFLAG 0x20
#define FBOTTOMFIELDPICORDERINFRAMEPRESENTFLAG 0x10
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

#define FPICSACALINGLISTPRESENTFLAG0 0x80
#define FPICSACALINGLISTPRESENTFLAG1 0x40
#define FPICSACALINGLISTPRESENTFLAG2 0x20
#define FPICSACALINGLISTPRESENTFLAG3 0x10
#define FPICSACALINGLISTPRESENTFLAG4 0x08
#define FPICSACALINGLISTPRESENTFLAG5 0x04
#define FPICSACALINGLISTPRESENTFLAG6 0x02
#define FPICSACALINGLISTPRESENTFLAG7 0x01

#define FSECONDCHROMAQPINDEXOFFSETH 0x0F
#define FSECONDCHROMAQPINDEXOFFSETL 0x80
#define FRBSPSTOPONEBIT 0x40
#define FRBSPALIGNMENTZEROBIT 0x3F

//SPS FLAGS
#define FCONSTRAINTSET0FLAG 0x80
#define FCONSTRAINTSET1FLAG 0x40
#define FCONSTRAINTSET2FLAG 0x20
#define FCONSTRAINTSET3FLAG 0x10
#define FCONSTRAINTSET4FLAG 0x08
#define FCONSTRAINTSET5FLAG 0x04
#define FRESERVEDZERO2BITS 0x03
#define FSPSSEQPARAMETERSETID 0x80
#define FCHROMAFORMATIDC 0x70
#define FSEPARATECOLOURPLANEFLAG 0x08
#define FBITDEPTHLUMAMINUS8 0x08
#define FBITDEPTHCHROMAMINUS8 0x04
#define FQPPRIMEYZEROTRANSFORMBYPASSFLAG 0x02
#define FSEQSCALINGMATRIXPRESENTLAG 0x01
#define FSEQSCALINGLISTPRESENTFLAGNBIT7 0x80
#define FSEQSCALINGLISTPRESENTFLAGNBIT6 0x40
#define FSEQSCALINGLISTPRESENTFLAGNBIT5 0x20
#define FSEQSCALINGLISTPRESENTFLAGNBIT4 0x10
#define FSEQSCALINGLISTPRESENTFLAGNBIT3 0x08
#define FSEQSCALINGLISTPRESENTFLAGNBIT2 0x04
#define FSEQSCALINGLISTPRESENTFLAGNBIT1 0x02
#define FSEQSCALINGLISTPRESENTFLAGNBIT0 0x01
#define FLOG2MAXFRAMENUMMINUS4 0x80
#define FPICORDERCNTTYPE 0x70
#define FLOG2MAXPICORDERCNTLSBMINUSH 0x0F
#define FLOG2MAXPICORDERCNTLSBMINUSL 0xF0
#define FDELTAPICORDERALWAYSZEROGFLAG 0x80
#define FOFFSETFORNONREFPIC 0x40
#define FOFFSETFORTOPTOBOTTOMFIELD 0x20
#define FNUMREFFRAMESINOICORDERCNTCYCLE 0x01
#define FMAXNUMREFFRAMESH 0x0F
#define FMAXNUMREFFRAMESL 0x80
#define FGAPSINFRAMENUMVALUEALLOWEDFLAG 0x40
#define FPICWIDTHINMBSMINUS1H 0x3F
#define FPICWIDTHINMBSMINUS1L 0xFE
#define FPICHEIGHTINMAPUNITSMINUS1H 0x01
#define FPICHEIGHTINMAPUNITSMINUS1M 0xFF
#define FPICHEIGHTINMAPUNITSMINUS1L 0xC0
#define FFRAMEMBSONLYFLAG 0x20
#define FMBADAPTIVEFRAMEFIELDFLAG 0x10
#define FDIRECT8X8INFERENCEFLAG 0x10
#define FFRAMECROPPINGFLAG 0x08
#define FFRAMECROPLEFTOFFSET 0x06
#define FFRAMECROPRIGHTOFFSETH 0x01
#define FFRAMECROPRIGHTOFFSETL 0x80
#define FFRAMECROPTOPOFFSET 0x60
#define FFRAMECROPBOTTOMOFFSET 0x18
#define FVUIPARAMETERSPRESENTLAG 0x40
//VUI FLAG
#define FASPECTRATIOINFOPRESENTLAG 0x02
#define FASPECTRATIOIDCH 0x01
#define FASPECTRATIOIDCL 0xFE
#define FSARWIDTHH 0x01
#define FSARWIDTHM 0xFF
#define FSARWIDTHL 0xFE
#define FSARHEIGHTH 0x01
#define FSARHEIGHTM 0xFF
#define FSARHEIGHTL 0xFE
#define FOVERSCANINFOPRESENTFLAG 0x01
#define FOVERSCANAPPROPIATEFLAG 0x80
#define FVIDEOSIGNALTYPEPRESENTLAG 0x80 //REDEFINIR
#define FVIDEOFORMAT 0x70
#define FVIDEOFULLRANGEFLAG 0X08
#define FCOLOURDESCRIPTIONPRESENTLAG 0x04
#define FCOLOURPRIMARIESH 0x03
#define FCOLOURPRIMARIESL 0xFC
#define FTRANSFERCHARACTERISTICSH 0x03
#define FTRANSFERCHARACTERISTICSL 0xFC
#define FMATRIXCOEFFICIENTSH 0x03
#define FMATRIXCOEFFICIENTSL 0xFC
#define FCHROMALOCINFOPRESENTFLAG 0x40
#define FCHROMASAMPLELOCTYPETOPFIELD 0x3C //REDEFINIR
#define FCHROMASAMPLELOCTYPEBOTTOMFIELDH 0x03 //REDEFINIR
#define FCHROMASAMPLELOCTYPEBOTTOMFIELDL 0xC0 //REDEFINIR
/* FCHROMASAMPLELOCTYPETOPFIELD - FCHROMASAMPLELOCTYPEBOTTOMFIELD
The value of chroma_sample_loc_type_top_field and chroma_sample_loc_type_bottom_field shall be in the range of 0
to 5, inclusive. When the chroma_sample_loc_type_top_field and chroma_sample_loc_type_bottom_field are not
present, the values of chroma_sample_loc_type_top_field and chroma_sample_loc_type_bottom_field shall be inferred
to be equal to 0.
*/
#define FTIMINGINFOPRESENTLAG 0x20
#define FNUMUNITSINTICKH 0x1F 
#define FNUMUNITSINTICKM 0xFF 
#define FNUMUNITSINTICKL 0xE0 
#define FTIMESCALEH 0x1F 
#define FTIMESCALEM 0xFF 
#define FTIMESCALEL 0xE0
#define FFIXEDFRAMERATEFLAG 0x10
#define FNALHRDPARAMETERSPRESENTLAG 0x08
#define FVCLHRDPARAMETERSPRESENTLAG 0x04

#define FLOWDELAYHRDFLAG 0x02
#define FPICSTRUCTPRESENTLAG 0x02 //REDEFINIR
#define FBITSTREAMRESTRICTIONFLAG 0x01
#define FMONTIONVECTORSOVERPICBOUNDARIESFLAG 0x80
#define FMAXBYTESPERPICDENOM 0x40
#define FMAXBITSPERMBDENOM 0x20
#define FLOG2MAXMVLENGTHHORIZONTALH 0x1F
#define FLOG2MAXMVLENGTHHORIZONTALL 0xC0
#define FLOG2MAXMVLENGTHVERTICALH 0x3F
#define FLOG2MAXMVLENGTHVERTICALL 0x80
#define FMAXNUMREODERFRAMES 0x40
/* FMAXNUMREODERFRAMES
The value of max_num_reorder_frames shall be in the range of 0 to max_dec_frame_buffering, inclusive. When the
max_num_reorder_frames syntax element is not present, the value of max_num_reorder_frames value shall be inferred
as follows:
– If profile_idc is equal to 44, 86, 100, 110, 122, or 244 and constraint_set3_flag is equal to 1, the value of
max_num_reorder_frames shall be inferred to be equal to 0.
– Otherwise (profile_idc is not equal to 44, 86, 100, 110, 122, or 244 or constraint_set3_flag is equal to 0), the value of
max_num_reorder_frames shall be inferred to be equal to MaxDpbFrames. MaxDpbFrames (0-16)
*/
#define FMAXEDCFRAMEBUFFERING 0x3E
/* FMAXEDCFRAMEBUFFERING
The value of max_dec_frame_buffering shall be greater than or equal to max_num_ref_frames. An upper bound for the value of
max_dec_frame_buffering is specified by the level limits in subclauses A.3.1, A.3.2, G.10.2.1, and H.10.2. When the max_dec_frame_buffering syntax element is not present, the value of max_dec_frame_buffering shall be inferred as follows:
– If profile_idc is equal to 44, 86, 100, 110, 122, or 244 and constraint_set3_flag is equal to 1, the value of
max_num_reorder_frames shall be inferred to be equal to 0.
– Otherwise (profile_idc is not equal to 44, 86, 100, 110, 122, or 244 or constraint_set3_flag is equal to 0), the value of
max_num_reorder_frames shall be inferred to be equal to MaxDpbFrames. MaxDpbFrames (0-16)
*/
#define FRBSPSTOPBIT 0X01 //ESTO SE VE EN WIRESHARK PERO NO EN LA ESPECIFICACION
//NAL HDR FLAGS
#define FNALCPBCNTMINUS1H 0x07
#define FNALCPBCNTMINUS1L 0xC0
#define FNALBITRATESCALE 0x3C
#define FNALCPBSIZESCALEH 0x03
#define FNALCPBSIZESCALEL 0xC0
//VCL HDR FLAGS
#define FVCLCPBCNTMINUS1H 0x03
#define FVCLCPBCNTMINUS1L 0xE0
#define FVCLBITRATESCALE 0x1E
#define FVCLCPBSIZESCALEH 0x01
#define FVCLCPBSIZESCALEL 0xE0

#define FBITRATEVALUEMINUS1H0 0xFF
#define FBITRATEVALUEMINUS1M 0xFF
#define FBITRATEVALUEMINUS1L0 0xFF
#define FCPBSIZEVALUEMINUS1H0 0xFF
#define FCPBSIZEVALUEMINUS1M 0xFF
#define FCPBSIZEVALUEMINUS1L0 0xFF
#define FCBRFLAG0 0x80
#define FBITRATEVALUEMINUS1H1 0x7F
#define FBITRATEVALUEMINUS1L1 0x80
#define FCPBSIZEVALUEMINUS1H1 0x7F
#define FCPBSIZEVALUEMINUS1L1 0x80
#define FCBRFLAG1 0x40
#define FBITRATEVALUEMINUS1H2 0x3F
#define FBITRATEVALUEMINUS1L2 0xC0
#define FCPBSIZEVALUEMINUS1H2 0x3F
#define FCPBSIZEVALUEMINUS1L2 0xC0
#define FCBRFLAG2 0x20
#define FBITRATEVALUEMINUS1H3 0x1F
#define FBITRATEVALUEMINUS1L3 0xE0
#define FCPBSIZEVALUEMINUS1H3 0x1F
#define FCPBSIZEVALUEMINUS1L3 0xE0
#define FCBRFLAG3 0x10
#define FBITRATEVALUEMINUS1H4 0x0F
#define FBITRATEVALUEMINUS1L4 0xF0
#define FCPBSIZEVALUEMINUS1H4 0x0F
#define FCPBSIZEVALUEMINUS1L4 0xF0
#define FCBRFLAG4 0x08
#define FBITRATEVALUEMINUS1H5 0x07
#define FBITRATEVALUEMINUS1L5 0xF8
#define FCPBSIZEVALUEMINUS1H5 0x07
#define FCPBSIZEVALUEMINUS1L5 0xF8
#define FCBRFLAG5 0x04
#define FBITRATEVALUEMINUS1H6 0x03
#define FBITRATEVALUEMINUS1L6 0xFC
#define FCPBSIZEVALUEMINUS1H6 0x03
#define FCPBSIZEVALUEMINUS1L6 0xFC
#define FCBRFLAG6 0x02
#define FBITRATEVALUEMINUS1H7 0x01
#define FBITRATEVALUEMINUS1L7 0xFE
#define FCPBSIZEVALUEMINUS1H7 0x01
#define FCPBSIZEVALUEMINUS1L7 0xFE
#define FCBRFLAG7 0x01

#define FINITIALCPBREMOVALDELAYLENGTHMINUS10 0xF8
#define FINITIALCPBREMOVALDELAYLENGTHMINUS11 0x7C
#define FINITIALCPBREMOVALDELAYLENGTHMINUS12 0x3E
#define FINITIALCPBREMOVALDELAYLENGTHMINUS13 0x1F
#define FINITIALCPBREMOVALDELAYLENGTHMINUS14H 0x0F
#define FINITIALCPBREMOVALDELAYLENGTHMINUS14L 0x80
#define FINITIALCPBREMOVALDELAYLENGTHMINUS15H 0x07
#define FINITIALCPBREMOVALDELAYLENGTHMINUS15L 0xC0
#define FINITIALCPBREMOVALDELAYLENGTHMINUS16H 0x03
#define FINITIALCPBREMOVALDELAYLENGTHMINUS16L 0xE0
#define FINITIALCPBREMOVALDELAYLENGTHMINUS17H 0x01
#define FINITIALCPBREMOVALDELAYLENGTHMINUS17L 0xF0
#define FCPBREMOVALDELAYLENGTHMINUS10 0xF8
#define FCPBREMOVALDELAYLENGTHMINUS11 0x7C
#define FCPBREMOVALDELAYLENGTHMINUS12 0x3E
#define FCPBREMOVALDELAYLENGTHMINUS13 0x1F
#define FCPBREMOVALDELAYLENGTHMINUS14H 0x0F
#define FCPBREMOVALDELAYLENGTHMINUS14L 0x80
#define FCPBREMOVALDELAYLENGTHMINUS15H 0x07
#define FCPBREMOVALDELAYLENGTHMINUS15L 0xC0
#define FCPBREMOVALDELAYLENGTHMINUS16H 0x03
#define FCPBREMOVALDELAYLENGTHMINUS16L 0xE0
#define FCPBREMOVALDELAYLENGTHMINUS17H 0x01
#define FCPBREMOVALDELAYLENGTHMINUS17L 0xF0
#define FDPBOUTPUTDEALYLENGTHMINUS10 0xF8
#define FDPBOUTPUTDEALYLENGTHMINUS11 0x7C
#define FDPBOUTPUTDEALYLENGTHMINUS12 0x3E
#define FDPBOUTPUTDEALYLENGTHMINUS13 0x1F
#define FDPBOUTPUTDEALYLENGTHMINUS14H 0x0F
#define FDPBOUTPUTDEALYLENGTHMINUS14L 0x80
#define FDPBOUTPUTDEALYLENGTHMINUS15H 0x07
#define FDPBOUTPUTDEALYLENGTHMINUS15L 0xC0
#define FDPBOUTPUTDEALYLENGTHMINUS16H 0x03
#define FDPBOUTPUTDEALYLENGTHMINUS16L 0xE0
#define FDPBOUTPUTDEALYLENGTHMINUS17H 0x01
#define FDPBOUTPUTDEALYLENGTHMINUS17L 0xF0
#define FTIMEOFFSETLENGTH0 0xF8
#define FTIMEOFFSETLENGTH1 0x7C
#define FTIMEOFFSETLENGTH2 0x3E
#define FTIMEOFFSETLENGTH3 0x1F
#define FTIMEOFFSETLENGTH4H 0x0F
#define FTIMEOFFSETLENGTH4L 0x80
#define FTIMEOFFSETLENGTH5H 0x07
#define FTIMEOFFSETLENGTH5L 0xC0
#define FTIMEOFFSETLENGTH6H 0x03
#define FTIMEOFFSETLENGTH6L 0xE0
#define FTIMEOFFSETLENGTH7H 0x01
#define FTIMEOFFSETLENGTH7L 0xF0


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
	byte rbspStopOneBit; //u(1)
	byte rbspAlignmentZeroBit; //u(6) = 0
} ppsStruct;

typedef struct {
	byte profileIdc; //u(8)
	byte constraintSet0Flag; //u(1)
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
	byte offsetForNonRefPic; //se(v)
	byte offsetForTopToBottomField; //se(v)
	byte numRefFramesInPicOrderCntCycle; //ue(v)
	byte offserForRefFrame[MAXCNTCYCLE]; //se(v)
	byte maxNumRefFrames; //ue(v)
	byte gapsInFrameNumValueAlloweFlag; //u(1)
	int  picWidthInMbsMinus1; //ue(v)
	int  picHeightInMapUnitsMinus1; //ue(v)
	byte framMbsOnlyFlag; //u(1)
	byte mbAdaptiveFrameFieldFlag; //u(1)
	byte direct8x8InferenceFlag; //u(1)
	byte frameCroppinFlag; //u(1)
	byte frameCroppinLeftOffset; //u(1)
	byte frameCroppinRightOffset; //u(1)
	byte frameCroppinTopOffset; //u(1)
	byte frameCroppinBottomOffset; //u(1)
	byte vuiParametersPresentFlag; //u(1)
	//VUI Parameters
	byte aspectRatioInfoPresentFlag; //u(1)
	byte aspectRatioIdc; //u(8)
	uint16_t sarWidth; //u(16)
	uint16_t sarHeight; //u(16)
	byte overscanInfoPresentFlag; //u(1)
	byte overscanAppropriateFlag; //u(1)
	byte videoSignalTypePresentFlag; //u(1)
	byte videoFormat; //u(3)
	byte videoFullRangeFlag; //u(1)
	byte colourDescriptionPresentFlag; //u(1)
	byte colourPrimaries; //u(8)
	byte transferCharacteristics; //u(8)
	byte matrixCoefficients; //u(8)
	byte chromaLocInfoPresentFlag; //u(1)
	byte chromaSampleLocTypeTopField; //ue(v)
	byte chromaSampleLocTypeBottomField; //ue(v)
	byte timingInfoPresentFlag; //u(1)
	uint32_t numUnitsInTick; //u(32)
	uint32_t timeScale; //u(32)
	byte fixedFrameRateFlag; //u(1)
	byte nalHrdParametersPresentFlag; //u(1)
	byte vclHrdParametersPresentFlag; //u(1)
	byte lowDelayHrdFlag; //u(1)
	byte picStructPresentFlag; //u(1)
	byte bitstreamRestrictionFlag; //u(1)
	byte montionVectorsOverPicBoundariesFlag; //u(1)
	byte maxBytesPerPicDenom; //ue(v)
	byte maxBitsPerMbDenom; //ue(v)
	byte log2MaxMvLengthHorizontal; //ue(v)
	byte log2MaxMvLengthVertical; //ue(v)
	byte maxNumReorderFrames; //ue(v)
	byte maxDecFrameBuffering; //ue(v)
	byte rbspStopBit; //u(1)
	//NAL HRD Parameters
	byte nalcpbCntMinus1; //ue(v)
	byte nalbitRateScale; //u(4)
	byte nalcpbSizeScale; //u(4)
	uint32_t nalbitRateValueMinus1[MAXCPBCNTMINUSONE]; //ue(v)
	uint32_t nalcpbSizeValueMinus1[MAXCPBCNTMINUSONE]; //ue(v)
	byte nalcbrFlag; //u(1)
	byte nalinitialCpbRemovalDelayLengthMinus1; //u(5)
	byte nalcpbRemovalDelayLengthMinus1; //u(5)
	byte naldpbOutputDelayLengthMinus1; //u(5)
	byte naltimeOffsetLength; //u(5)
	//VCL HRD Parameters
	byte vclcpbCntMinus1; //ue(v)
	byte vclbitRateScale; //u(4)
	byte vclcpbSizeScale; //u(4)
	uint32_t vclbitRateValueMinus1[MAXCPBCNTMINUSONE]; //ue(v)
	uint32_t vclcpbSizeValueMinus1[MAXCPBCNTMINUSONE]; //ue(v)
	byte vclcbrFlag; //u(1)
	byte vclinitialCpbRemovalDelayLengthMinus1; //u(5)
	byte vclcpbRemovalDelayLengthMinus1; //u(5)
	byte vcldpbOutputDelayLengthMinus1; //u(5)
	byte vcltimeOffsetLength; //u(5)

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
