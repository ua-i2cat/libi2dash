#include "../include/i2nalparser.h"

//PPS
bool ppsToRbsp(unsigned char* ppsHeader, uint32_t ppsLength, nalHeader* headers) {
	int offset = 0;
	if ((ppsLength <=0) || (ppsLength > MAXLENGTHPPS) || (ppsHeader == NULL))
		return false;
	headers->pps.picParameterSetId = (ppsHeader[offset] & FPICPARAMETERSETID) >> 7;
	headers->pps.seqParameterSetId = (ppsHeader[offset] & FPPSSEQPARAMETERSETID) >> 6;
	headers->pps.entropyCondingModeFlag = (ppsHeader[offset] & FENTROPYCODINGMODEFLAG) >> 5;
	headers->pps.bottomFieldPicOrderInFramePresentFlag = (ppsHeader[offset] & FBOTTOMFIELDPICORDERINFRAMEPRESENTFLAG) >> 4;
	headers->pps.numSliceGroupsMinus1 = (ppsHeader[offset] & FNUMSLICEGROUPMINUS1) >> 3;
	if (headers->pps.numSliceGroupsMinus1 > 0) {//TODO check this!
		headers->pps.sliceGroupMapType = (ppsHeader[0] & FSLICEGROUPSMAPTYPE);
		offset++;
		if (headers->pps.sliceGroupMapType == 0) {
			for (int iGroup = 0; iGroup <= headers->pps.numSliceGroupsMinus1; iGroup++) {
				headers->pps.runLengthMinus1[iGroup] = ppsHeader[offset];
				offset++;
			}
		} else if (headers->pps.sliceGroupMapType == 2) {
			for (int iGroup = 0; iGroup <= headers->pps.numSliceGroupsMinus1; iGroup++) {
				headers->pps.topLef[iGroup] = (ppsHeader[offset] & FTOPLEFT) >> 4;
				headers->pps.bottomRight[iGroup] = (ppsHeader[offset] & FBOTTOMRIGHT);
				offset++;
			} 
		} else if ((headers->pps.sliceGroupMapType > 2) && (headers->pps.sliceGroupMapType < 6)) {
			headers->pps.sliceGroupChangeDirectionFlag = (ppsHeader[offset] & FSLICEGROUPCHANGEDIRECTIONFLAG) >> 7;
			headers->pps.sliceGroupChangeRateMinus1 = (ppsHeader[offset] & FSLICEGROUPCHANGERATEMINUS1);
			offset++;			
		} else if (headers->pps.sliceGroupMapType == 6) {
			headers->pps.picSizeInMapUnitsMinus1 = ppsHeader[offset];
			offset++;
			for (int i = 0; i <= headers->pps.picSizeInMapUnitsMinus1; i++) {
				headers->pps.sliceGroupId[i] = ppsHeader[offset];
				offset++;
			}
			
		}
	}
	headers->pps.numRefIdx10DefaultActiveMinus1 = (ppsHeader[offset] & FNUMREFIDX10DEFAULTACTIVEMINUS1) - 1;
	offset++;
	headers->pps.numRefIdx11DefaultActiveMinus1 = (ppsHeader[offset] & FNUMREFIDX11DEFAULTACTIVEMINUS1) - 1;
	headers->pps.weightedPredFlag = (ppsHeader[offset] & FWEIGHTEDPREDFLAG);
	headers->pps.weightedBipredIdc = (ppsHeader[offset] & FWEIGHTEDBIPREDIDC);
	headers->pps.picInitQpMinus26 = ((((ppsHeader[offset] & FPICINITQPMINUS26H) << 1) | ((ppsHeader[offset+1] & FPICINITQPMINUS26L) >> 7)) - 26) & FSIGNOQP26; //TODO check this
	offset++;
	headers->pps.picInitQsMinus26 = (((ppsHeader[offset] & FPICINITQSMINUS26) >> 6) - 26)  & FSIGNOQS26; //TODO check this
	headers->pps.chromaQpIndexOffset = (ppsHeader[offset] & FCHROMAQPINDEXOFFSET) >> 1; //Mirar esto
	headers->pps.deblockingFilterControlPresentFlag = (ppsHeader[offset] & FDEBLOCKINGFILTERTCONTROLPRESENTFLAG);
	offset++;
	headers->pps.constrainedIntraPredFlag = (ppsHeader[offset] & FCONSTRAINEDINTRAPREDFLAG) >> 7;
	headers->pps.redundantPicCntPresentFlag = (ppsHeader[offset] & FREDUNDANTPICCNTPRESENTLAG) >> 6;
	if (true) {//TODO more_rbsp_data()
		headers->pps.transform8x8ModeFlag = (ppsHeader[offset] & FTRANSFORM8X8MODEFLAG) >> 5;
		headers->pps.picScalingMatrixPresentFlag = (ppsHeader[offset] & FPICSACALINGMATRIXPRESENTFLAG) >> 4;
		if (headers->pps.picScalingMatrixPresentFlag) {
			int index = 0;
			for (int i=0; i < 6 + (((headers->sps.chromaFormatIdc != 3) ? 2 : 6) * headers->pps.transform8x8ModeFlag); i++) {
				index = (i + 4) % 8;
				switch (index) {
				case 0:
					headers->pps.picScalingListPresentFlag[i] = (ppsHeader[offset] & FPICSACALINGLISTPRESENTFLAG0) >> 7;
					break;
				case 1:
					headers->pps.picScalingListPresentFlag[i] = (ppsHeader[offset] & FPICSACALINGLISTPRESENTFLAG1) >> 6;
					break;
				case 2:
					headers->pps.picScalingListPresentFlag[i] = (ppsHeader[offset] & FPICSACALINGLISTPRESENTFLAG2) >> 5;
					break;
				case 3:
					headers->pps.picScalingListPresentFlag[i] = (ppsHeader[offset] & FPICSACALINGLISTPRESENTFLAG3) >> 4;
					break;
				case 4:
					headers->pps.picScalingListPresentFlag[i] = (ppsHeader[offset] & FPICSACALINGLISTPRESENTFLAG4) >> 3;
					break;
				case 5:
					headers->pps.picScalingListPresentFlag[i] = (ppsHeader[offset] & FPICSACALINGLISTPRESENTFLAG5) >> 2;
					break;
				case 6:
					headers->pps.picScalingListPresentFlag[i] = (ppsHeader[offset] & FPICSACALINGLISTPRESENTFLAG6) >> 1;
					break;
				case 7:
					headers->pps.picScalingListPresentFlag[i] = (ppsHeader[offset] & FPICSACALINGLISTPRESENTFLAG7) >> 0;
					offset++;
					break;
				}
			}
		}
		headers->pps.secondChromaQpIndexOffset = ((ppsHeader[offset] & FSECONDCHROMAQPINDEXOFFSETH) << 1) | ((ppsHeader[offset+1] & FSECONDCHROMAQPINDEXOFFSETL) >> 7);
		offset++;
	}
	headers->pps.rbspStopOneBit = (ppsHeader[offset] & FRBSPSTOPONEBIT) >> 6;
	//TODO While(byte_aligned())
	headers->pps.rbspAlignmentZeroBit = (ppsHeader[offset] & FRBSPALIGNMENTZEROBIT);
	return true;
}

//SPS
bool spsToRbsp(unsigned char* spsHeader, uint32_t spsLength, nalHeader* headers) {
	int offset = 0;
	headers->sps.profileIdc = spsHeader[offset];
	offset++;
	headers->sps.constraintSet0Flag = (spsHeader[offset] & FCONSTRAINTSET0FLAG) >> 7;
	headers->sps.constraintSet1Flag = (spsHeader[offset] & FCONSTRAINTSET1FLAG) >> 6;
	headers->sps.constraintSet2Flag = (spsHeader[offset] & FCONSTRAINTSET2FLAG) >> 5;
	headers->sps.constraintSet3Flag = (spsHeader[offset] & FCONSTRAINTSET3FLAG) >> 4;
	headers->sps.constraintSet4Flag = (spsHeader[offset] & FCONSTRAINTSET4FLAG) >> 3;
	headers->sps.constraintSet5Flag = (spsHeader[offset] & FCONSTRAINTSET5FLAG) >> 2;
	headers->sps.reservedZero2bits = (spsHeader[offset] & FRESERVEDZERO2BITS);
	offset++;
	headers->sps.levelIdc = spsHeader[offset];
	offset++;
	headers->sps.seqParameterSetId = (spsHeader[offset] & FSPSSEQPARAMETERSETID);
	if ((headers->sps.profileIdc == 100) || (headers->sps.profileIdc == 110) || (headers->sps.profileIdc == 122) || (headers->sps.profileIdc == 244) || (headers->sps.profileIdc == 44) || (headers->sps.profileIdc == 83) || (headers->sps.profileIdc == 86) || (headers->sps.profileIdc == 118) || (headers->sps.profileIdc == 128)) {
		headers->sps.chromaFormatIdc = (spsHeader[offset] &FCHROMAFORMATIDC) >> 4;
		if (headers->sps.chromaFormatIdc == 3) {
			headers->sps.separateColourPlaneFlag = (spsHeader[offset] & FSEPARATECOLOURPLANEFLAG) >> 3;
		}
		headers->sps.bitDepthLumaMinus8 = (spsHeader[offset] & FBITDEPTHLUMAMINUS8) >> 3;
		headers->sps.bitDepthChromaMinus8 = (spsHeader[offset] & FBITDEPTHCHROMAMINUS8) >> 2;
		headers->sps.qpprimeYZeroTransformBypassFlag = (spsHeader[offset] & FQPPRIMEYZEROTRANSFORMBYPASSFLAG) >> 1;
		headers->sps.seqScalingMatrixPresentFlag = (spsHeader[offset] & FSEQSCALINGMATRIXPRESENTLAG);
		if (headers->sps.seqScalingMatrixPresentFlag) {
			for (int i = 0; i < ((headers->sps.chromaFormatIdc != 3)?8:12); i++) {//TODO: check
				switch (i) {
				case 0:
					headers->sps.seqScalingListPresentFlag[i] = (spsHeader[offset] & FSEQSCALINGLISTPRESENTFLAGNBIT7) >> 7;
					break;
				case 1:
					headers->sps.seqScalingListPresentFlag[i] = (spsHeader[offset] & FSEQSCALINGLISTPRESENTFLAGNBIT6) >> 6;
					break;
				case 2:
					headers->sps.seqScalingListPresentFlag[i] = (spsHeader[offset] & FSEQSCALINGLISTPRESENTFLAGNBIT5) >> 5;
					break;
				case 3:
					headers->sps.seqScalingListPresentFlag[i] = (spsHeader[offset] & FSEQSCALINGLISTPRESENTFLAGNBIT4) >> 4;
					break;
				case 4:
					headers->sps.seqScalingListPresentFlag[i] = (spsHeader[offset] & FSEQSCALINGLISTPRESENTFLAGNBIT3) >> 3;
					break;
				case 5:
					headers->sps.seqScalingListPresentFlag[i] = (spsHeader[offset] & FSEQSCALINGLISTPRESENTFLAGNBIT2) >> 2;
					break;
				case 6:
					headers->sps.seqScalingListPresentFlag[i] = (spsHeader[offset] & FSEQSCALINGLISTPRESENTFLAGNBIT1) >> 1;
					break;
				case 7:
					headers->sps.seqScalingListPresentFlag[i] = (spsHeader[offset] & FSEQSCALINGLISTPRESENTFLAGNBIT0);
					offset++;
					break;
				case 8:
					headers->sps.seqScalingListPresentFlag[i] = (spsHeader[offset] & FSEQSCALINGLISTPRESENTFLAGNBIT7) >> 7;
					break;
				case 9:
					headers->sps.seqScalingListPresentFlag[i] = (spsHeader[offset] & FSEQSCALINGLISTPRESENTFLAGNBIT6) >> 6;
					break;
				case 10:
					headers->sps.seqScalingListPresentFlag[i] = (spsHeader[offset] & FSEQSCALINGLISTPRESENTFLAGNBIT5) >> 5;
					break;
				case 11:
					headers->sps.seqScalingListPresentFlag[i] = (spsHeader[offset] & FSEQSCALINGLISTPRESENTFLAGNBIT4) >> 4;
					offset++;
					break;
				}
				/*TODO
				if( seq_scaling_list_present_flag[ i ] )
				if( i < 6 )
				scaling_list( ScalingList4x4[ i ], 16,
				UseDefaultScalingMatrix4x4Flag[ i ])
				else
				scaling_list( ScalingList8x8[ i − 6 ], 64,
				UseDefaultScalingMatrix8x8Flag[ i − 6 ] )*/
			}
		}
	}
	headers->sps.log2MaxFrameNumMinus4 = (spsHeader[offset] & FLOG2MAXFRAMENUMMINUS4) >> 7;
	headers->sps.picOrderCntType = (spsHeader[offset] & FPICORDERCNTTYPE) >> 4;
	if (headers->sps.picOrderCntType == 0) {
		headers->sps.log2MaxPicOrderCntLsbMinus4 = ((spsHeader[offset] & FLOG2MAXPICORDERCNTLSBMINUSH) << 4) | ((spsHeader[offset+1] & FLOG2MAXPICORDERCNTLSBMINUSL) >> 4);
		offset++;
	} else if (headers->sps.picOrderCntType == 1) {
		headers->sps.DeltaPicOrderAlwaysZeroFlag = (spsHeader[offset] & FDELTAPICORDERALWAYSZEROGFLAG) >> 3;
		headers->sps.offsetForNonRefPic = (spsHeader[offset] & FOFFSETFORNONREFPIC) >> 2;
		headers->sps.offsetForTopToBottomField = (spsHeader[offset] & FOFFSETFORTOPTOBOTTOMFIELD) >> 1;
		headers->sps.numRefFramesInPicOrderCntCycle = (spsHeader[offset] & FNUMREFFRAMESINOICORDERCNTCYCLE); //TODO: check this
		offset++;
		for (int i = 0; i < headers->sps.numRefFramesInPicOrderCntCycle; i++) {//TODO: check this
			headers->sps.offserForRefFrame[i] = spsHeader[offset];
			offset++;
		}
	}
	headers->sps.maxNumRefFrames = ((spsHeader[offset] & FMAXNUMREFFRAMESH) << 1) | (spsHeader[offset+1] & FMAXNUMREFFRAMESL);
	offset++;
	headers->sps.gapsInFrameNumValueAlloweFlag = (spsHeader[offset] & FGAPSINFRAMENUMVALUEALLOWEDFLAG) >> 6;
	headers->sps.picWidthInMbsMinus1 = ((spsHeader[offset] & FPICWIDTHINMBSMINUS1H) * 128) + (spsHeader[offset] & FPICWIDTHINMBSMINUS1L) - 1;
	offset++;
	headers->sps.picHeightInMapUnitsMinus1 = ((spsHeader[offset] & FPICHEIGHTINMAPUNITSMINUS1H) * 1024) + ((spsHeader[offset+1] & FPICHEIGHTINMAPUNITSMINUS1M) * 4) + ((spsHeader[offset+2] & FPICHEIGHTINMAPUNITSMINUS1L) >> 6) - 1;
	offset += 2;
	headers->sps.framMbsOnlyFlag = (spsHeader[offset] & FFRAMEMBSONLYFLAG) >> 5;
	if (!headers->sps.framMbsOnlyFlag) {
		headers->sps.mbAdaptiveFrameFieldFlag = (spsHeader[offset] & FMBADAPTIVEFRAMEFIELDFLAG) >> 4;
	}
	headers->sps.direct8x8InferenceFlag = (spsHeader[offset] & FDIRECT8X8INFERENCEFLAG) >> 4;
	headers->sps.frameCroppinFlag = (spsHeader[offset] & FFRAMECROPPINGFLAG) >> 3;
	if (headers->sps.frameCroppinFlag) {//TODO: check this
		headers->sps.frameCroppinLeftOffset = (spsHeader[offset] & FFRAMECROPLEFTOFFSET) >> 1;
		headers->sps.frameCroppinRightOffset = ((spsHeader[offset] & FFRAMECROPRIGHTOFFSETH) << 1) | ((spsHeader[offset] & FFRAMECROPRIGHTOFFSETL) >> 7);
		offset++;
		headers->sps.frameCroppinTopOffset = (spsHeader[offset] & FFRAMECROPTOPOFFSET) >> 5;
		headers->sps.frameCroppinBottomOffset = ((spsHeader[offset] & FFRAMECROPBOTTOMOFFSET) >> 3);
	} else {
		headers->sps.frameCroppinLeftOffset = 0;
		headers->sps.frameCroppinRightOffset = 0;
		headers->sps.frameCroppinTopOffset = 0;
		headers->sps.frameCroppinBottomOffset = 0;
	}
	headers->sps.vuiParametersPresentFlag = (spsHeader[offset] & FVUIPARAMETERSPRESENTLAG) >> 2;
	if (headers->sps.vuiParametersPresentFlag) {
		headers->sps.aspectRatioInfoPresentFlag = (spsHeader[offset] & FASPECTRATIOINFOPRESENTLAG) >> 1;
		if (headers->sps.aspectRatioInfoPresentFlag) {
			headers->sps.aspectRatioIdc = ((spsHeader[offset] & FASPECTRATIOIDCH) << 7) | ((spsHeader[offset+1] & FASPECTRATIOIDCL) >> 1);
			offset++;
			if (headers->sps.aspectRatioIdc == EXTENDESAR) {
				headers->sps.sarWidth = ((spsHeader[offset] & FSARWIDTHH) * 32768) + ((spsHeader[offset+1] & FSARWIDTHM) * 128) + ((spsHeader[offset+2] & FSARWIDTHL) >> 1);
				offset+= 2;
				headers->sps.sarHeight = ((spsHeader[offset] & FSARHEIGHTH) * 32768) + ((spsHeader[offset+1] & FSARHEIGHTM) * 128) + ((spsHeader[offset+2] & FSARHEIGHTL) >> 1);
				offset+= 2;
			}
		}
		headers->sps.overscanInfoPresentFlag = (spsHeader[offset] & FOVERSCANINFOPRESENTFLAG);
		offset++;
		if (headers->sps.overscanInfoPresentFlag) {
			headers->sps.overscanAppropriateFlag = (spsHeader[offset] & FOVERSCANAPPROPIATEFLAG) >> 7;
		}
		headers->sps.videoSignalTypePresentFlag = (spsHeader[offset] & FVIDEOSIGNALTYPEPRESENTLAG) >> 7;
		if (headers->sps.videoSignalTypePresentFlag) {
			headers->sps.videoFormat = (spsHeader[offset] & FVIDEOFORMAT) >> 4;
			headers->sps.videoFullRangeFlag = (spsHeader[offset] & FVIDEOFULLRANGEFLAG) >> 3;
			headers->sps.colourDescriptionPresentFlag = (spsHeader[offset] & FCOLOURDESCRIPTIONPRESENTLAG) >> 2;
			if (headers->sps.colourDescriptionPresentFlag) {
				headers->sps.colourPrimaries = ((spsHeader[offset] & FCOLOURPRIMARIESH) << 6) | ((spsHeader[offset+1] & FCOLOURPRIMARIESL) >> 2);
				offset++;
				headers->sps.transferCharacteristics = ((spsHeader[offset] & FTRANSFERCHARACTERISTICSH) << 6) | ((spsHeader[offset+1] & FTRANSFERCHARACTERISTICSL) >> 2);
				offset++;
				headers->sps.matrixCoefficients = ((spsHeader[offset] & FMATRIXCOEFFICIENTSH) << 6) | ((spsHeader[offset+1] & FMATRIXCOEFFICIENTSL) >> 2);
				offset++;
			}
		}
		headers->sps.chromaLocInfoPresentFlag = (spsHeader[offset] & FCHROMALOCINFOPRESENTFLAG) >> 6;
		if (headers->sps.chromaLocInfoPresentFlag) {
			headers->sps.chromaSampleLocTypeTopField = (spsHeader[offset] & FCHROMASAMPLELOCTYPETOPFIELD) >> 2;
			headers->sps.chromaSampleLocTypeBottomField = ((spsHeader[offset] & FCHROMASAMPLELOCTYPEBOTTOMFIELDH) << 2) | ((spsHeader[offset+1] & FCHROMASAMPLELOCTYPEBOTTOMFIELDL) >> 6);
			offset++;
		}
		headers->sps.timingInfoPresentFlag = (spsHeader[offset] & FTIMINGINFOPRESENTLAG) >> 5;
		if (headers->sps.timingInfoPresentFlag) {
			headers->sps.numUnitsInTick = ((spsHeader[offset] & FNUMUNITSINTICKH) * 134217728) + ((spsHeader[offset+1] & FNUMUNITSINTICKM) * 524288) + ((spsHeader[offset+2] & FNUMUNITSINTICKM) * 2048) + ((spsHeader[offset+3] & FNUMUNITSINTICKM) * 8) + ((spsHeader[offset+4] & FNUMUNITSINTICKL) >> 5);
			offset+= 4;
			headers->sps.timeScale = ((spsHeader[offset] & FTIMESCALEH) * 134217728) + ((spsHeader[offset+1] & FTIMESCALEM) * 524288) + ((spsHeader[offset+2] & FTIMESCALEM) * 2048) + ((spsHeader[offset+3] & FTIMESCALEM) * 8) + ((spsHeader[offset+4] & FTIMESCALEL) >> 5);
			offset+= 4;
			headers->sps.fixedFrameRateFlag = (spsHeader[offset] & FFIXEDFRAMERATEFLAG) >> 4;
		}
		headers->sps.nalHrdParametersPresentFlag = (spsHeader[offset] & FNALHRDPARAMETERSPRESENTLAG) >> 3;
		if (headers->sps.nalHrdParametersPresentFlag) {
			int index = 0;
			headers->sps.nalcpbCntMinus1 = ((spsHeader[offset] & FNALCPBCNTMINUS1H) << 2) | ((spsHeader[offset+1] & FNALCPBCNTMINUS1L) >> 6);
			offset++;
			headers->sps.nalbitRateScale = (spsHeader[offset] & FNALBITRATESCALE) >> 2;
			headers->sps.nalcpbSizeScale = ((spsHeader[offset] & FNALCPBSIZESCALEH) << 2) | ((spsHeader[offset+1] & FNALCPBSIZESCALEL) >> 6);
			offset++;
			for (int i = 0; i < headers->sps.nalcpbCntMinus1; i++) {
				index = ((i+2) % 8);
				switch (index) {
				case 0:
					headers->sps.nalbitRateValueMinus1[i] = ((spsHeader[offset] & FBITRATEVALUEMINUS1H0) * 16777216) + ((spsHeader[offset+1] & FBITRATEVALUEMINUS1M) * 65536) + ((spsHeader[offset+2] & FBITRATEVALUEMINUS1M) * 256) + ((spsHeader[offset+3] & FBITRATEVALUEMINUS1L0));
					offset+=4;
					headers->sps.nalcpbSizeValueMinus1[i] = ((spsHeader[offset] & FCPBSIZEVALUEMINUS1H0) * 16777216) + ((spsHeader[offset+1] & FCPBSIZEVALUEMINUS1M) * 65536) + ((spsHeader[offset+2] & FCPBSIZEVALUEMINUS1M) * 256) + ((spsHeader[offset+3] & FCPBSIZEVALUEMINUS1L0));
					offset+=4;
					headers->sps.nalcbrFlag = (spsHeader[offset] & FCBRFLAG0) >> 7;
					break;
				case 1:
					headers->sps.nalbitRateValueMinus1[i] = ((spsHeader[offset] & FBITRATEVALUEMINUS1H1) * 33554432) + ((spsHeader[offset+1] & FBITRATEVALUEMINUS1M) * 131072) + ((spsHeader[offset+2] & FBITRATEVALUEMINUS1M) * 512) + ((spsHeader[offset+3] & FBITRATEVALUEMINUS1M) * 2) + ((spsHeader[offset+4] & FBITRATEVALUEMINUS1L1) >> 7);
					offset+=4;
					headers->sps.nalcpbSizeValueMinus1[i] = ((spsHeader[offset] & FCPBSIZEVALUEMINUS1H1) * 33554432) + ((spsHeader[offset+1] & FCPBSIZEVALUEMINUS1M) * 131072) + ((spsHeader[offset+2] & FCPBSIZEVALUEMINUS1M) * 512) + ((spsHeader[offset+3] & FCPBSIZEVALUEMINUS1M) * 2) + ((spsHeader[offset+4] & FCPBSIZEVALUEMINUS1L1) >> 7);
					offset+=4;
					headers->sps.nalcbrFlag = (spsHeader[offset] & FCBRFLAG1) >> 6;
					break;
				case 2:
					headers->sps.nalbitRateValueMinus1[i] = ((spsHeader[offset] & FBITRATEVALUEMINUS1H2) * 67108864) + ((spsHeader[offset+1] & FBITRATEVALUEMINUS1M) * 262144) + ((spsHeader[offset+2] & FBITRATEVALUEMINUS1M) * 1024) + ((spsHeader[offset+3] & FBITRATEVALUEMINUS1M) * 4) + ((spsHeader[offset+4] & FBITRATEVALUEMINUS1L2) >> 6);
					offset+=4;
					headers->sps.nalcpbSizeValueMinus1[i] = ((spsHeader[offset] & FCPBSIZEVALUEMINUS1H2) * 67108864) + ((spsHeader[offset+1] & FCPBSIZEVALUEMINUS1M) * 262144) + ((spsHeader[offset+2] & FCPBSIZEVALUEMINUS1M) * 1024) + ((spsHeader[offset+3] & FCPBSIZEVALUEMINUS1M) * 4) + ((spsHeader[offset+4] & FCPBSIZEVALUEMINUS1L2) >> 6);
					offset+=4;
					headers->sps.nalcbrFlag = (spsHeader[offset] & FCBRFLAG2) >> 5;
					break;
				case 3:
					headers->sps.nalbitRateValueMinus1[i] = ((spsHeader[offset] & FBITRATEVALUEMINUS1H3) * 134217728) + ((spsHeader[offset+1] & FBITRATEVALUEMINUS1M) * 524288) + ((spsHeader[offset+2] & FBITRATEVALUEMINUS1M) * 2048) + ((spsHeader[offset+3] & FBITRATEVALUEMINUS1M) * 8) + ((spsHeader[offset+4] & FBITRATEVALUEMINUS1L3) >> 5);
					offset+=4;
					headers->sps.nalcpbSizeValueMinus1[i] = ((spsHeader[offset] & FCPBSIZEVALUEMINUS1H3) * 134217728) + ((spsHeader[offset+1] & FCPBSIZEVALUEMINUS1M) * 524288) + ((spsHeader[offset+2] & FCPBSIZEVALUEMINUS1M) * 2048) + ((spsHeader[offset+3] & FCPBSIZEVALUEMINUS1M) * 8) + ((spsHeader[offset+4] & FCPBSIZEVALUEMINUS1L3) >> 5);
					offset+=4;
					headers->sps.nalcbrFlag = (spsHeader[offset] & FCBRFLAG3) >> 4;
					break;
				case 4:
					headers->sps.nalbitRateValueMinus1[i] = ((spsHeader[offset] & FBITRATEVALUEMINUS1H4) * 268435456) + ((spsHeader[offset+1] & FBITRATEVALUEMINUS1M) * 1048576) + ((spsHeader[offset+2] & FBITRATEVALUEMINUS1M) * 4096) + ((spsHeader[offset+3] & FBITRATEVALUEMINUS1M) * 16) + ((spsHeader[offset+4] & FBITRATEVALUEMINUS1L4) >> 4);
					offset+=4;
					headers->sps.nalcpbSizeValueMinus1[i] = ((spsHeader[offset] & FCPBSIZEVALUEMINUS1H4) * 268435456) + ((spsHeader[offset+1] & FCPBSIZEVALUEMINUS1M) * 1048576) + ((spsHeader[offset+2] & FCPBSIZEVALUEMINUS1M) * 4096) + ((spsHeader[offset+3] & FCPBSIZEVALUEMINUS1M) * 16) + ((spsHeader[offset+4] & FCPBSIZEVALUEMINUS1L4) >> 4);
					offset+=4;
					headers->sps.nalcbrFlag = (spsHeader[offset] & FCBRFLAG4) >> 3;
					break;
				case 5:
					headers->sps.nalbitRateValueMinus1[i] = ((spsHeader[offset] & FBITRATEVALUEMINUS1H5) * 536870912) + ((spsHeader[offset+1] & FBITRATEVALUEMINUS1M) * 2097152) + ((spsHeader[offset+2] & FBITRATEVALUEMINUS1M) * 8192) + ((spsHeader[offset+3] & FBITRATEVALUEMINUS1M) * 32) + ((spsHeader[offset+4] & FBITRATEVALUEMINUS1L5) >> 3);
					offset+=4;
					headers->sps.nalcpbSizeValueMinus1[i] = ((spsHeader[offset] & FCPBSIZEVALUEMINUS1H5) * 536870912) + ((spsHeader[offset+1] & FCPBSIZEVALUEMINUS1M) * 2097152) + ((spsHeader[offset+2] & FCPBSIZEVALUEMINUS1M) * 8192) + ((spsHeader[offset+3] & FCPBSIZEVALUEMINUS1M) * 32) + ((spsHeader[offset+4] & FCPBSIZEVALUEMINUS1L5) >> 3);
					offset+=4;
					headers->sps.nalcbrFlag = (spsHeader[offset] & FCBRFLAG5) >> 2;
					break;
				case 6:
					headers->sps.nalbitRateValueMinus1[i] = ((spsHeader[offset] & FBITRATEVALUEMINUS1H5) * 1073741824) + ((spsHeader[offset+1] & FBITRATEVALUEMINUS1M) * 2097152) + ((spsHeader[offset+2] & FBITRATEVALUEMINUS1M) * 16384) + ((spsHeader[offset+3] & FBITRATEVALUEMINUS1M) * 64) + ((spsHeader[offset+4] & FBITRATEVALUEMINUS1L5) >> 2);
					offset+=4;
					headers->sps.nalcpbSizeValueMinus1[i] = ((spsHeader[offset] & FCPBSIZEVALUEMINUS1H5) * 1073741824) + ((spsHeader[offset+1] & FCPBSIZEVALUEMINUS1M) * 2097152) + ((spsHeader[offset+2] & FCPBSIZEVALUEMINUS1M) * 16384) + ((spsHeader[offset+3] & FCPBSIZEVALUEMINUS1M) * 64) + ((spsHeader[offset+4] & FCPBSIZEVALUEMINUS1L5) >> 2);
					offset+=4;
					headers->sps.nalcbrFlag = (spsHeader[offset] & FCBRFLAG6) >> 1;
					break;
				case 7:
					headers->sps.nalbitRateValueMinus1[i] = ((spsHeader[offset] & FBITRATEVALUEMINUS1H5) * 2147483648) + ((spsHeader[offset+1] & FBITRATEVALUEMINUS1M) * 4194304) + ((spsHeader[offset+2] & FBITRATEVALUEMINUS1M) * 32768) + ((spsHeader[offset+3] & FBITRATEVALUEMINUS1M) * 128) + ((spsHeader[offset+4] & FBITRATEVALUEMINUS1L5) >> 1);
					offset+=4;
					headers->sps.nalcpbSizeValueMinus1[i] = ((spsHeader[offset] & FCPBSIZEVALUEMINUS1H5) * 2147483648) + ((spsHeader[offset+1] & FCPBSIZEVALUEMINUS1M) * 4194304) + ((spsHeader[offset+2] & FCPBSIZEVALUEMINUS1M) * 32768) + ((spsHeader[offset+3] & FCPBSIZEVALUEMINUS1M) * 128) + ((spsHeader[offset+4] & FCPBSIZEVALUEMINUS1L5) >> 1);
					offset+=4;
					headers->sps.nalcbrFlag = (spsHeader[offset] & FCBRFLAG7);
					offset++;
					break;
				}
			}

			switch (index) {
			case 0:
				headers->sps.nalinitialCpbRemovalDelayLengthMinus1 = (spsHeader[offset] & FINITIALCPBREMOVALDELAYLENGTHMINUS10) >> 3; //u(5)
				headers->sps.nalcpbRemovalDelayLengthMinus1 = ((spsHeader[offset] & FCPBREMOVALDELAYLENGTHMINUS15H) << 2) | ((spsHeader[offset+1] & FCPBREMOVALDELAYLENGTHMINUS15L) >> 6); //u(5)
				offset++;
				headers->sps.naldpbOutputDelayLengthMinus1 = (spsHeader[offset] & FDPBOUTPUTDEALYLENGTHMINUS12) >> 1; //u(5)
				headers->sps.naltimeOffsetLength = ((spsHeader[offset] & FTIMEOFFSETLENGTH7H) << 4) | ((spsHeader[offset+1] & FTIMEOFFSETLENGTH7L) >> 4); //u(5)
				offset++;
				break;
			case 1:
				headers->sps.nalinitialCpbRemovalDelayLengthMinus1 = (spsHeader[offset] & FINITIALCPBREMOVALDELAYLENGTHMINUS11) >> 2; //u(5)
				headers->sps.nalcpbRemovalDelayLengthMinus1 = ((spsHeader[offset] & FCPBREMOVALDELAYLENGTHMINUS16H) << 3) | ((spsHeader[offset+1] & FCPBREMOVALDELAYLENGTHMINUS16L) >> 5); //u(5)
				offset++;
				headers->sps.naldpbOutputDelayLengthMinus1 = (spsHeader[offset] & FDPBOUTPUTDEALYLENGTHMINUS13); //u(5)
				offset++;
				headers->sps.naltimeOffsetLength = (spsHeader[offset] & FTIMEOFFSETLENGTH0) >> 3; //u(5)
				break;
			case 2:
				headers->sps.nalinitialCpbRemovalDelayLengthMinus1 = (spsHeader[offset] & FINITIALCPBREMOVALDELAYLENGTHMINUS12) >> 1; //u(5)
				headers->sps.nalcpbRemovalDelayLengthMinus1 = ((spsHeader[offset] & FCPBREMOVALDELAYLENGTHMINUS17H) << 4) | ((spsHeader[offset+1] & FCPBREMOVALDELAYLENGTHMINUS17L) >> 4); //u(5)
				offset++;
				headers->sps.naldpbOutputDelayLengthMinus1 = ((spsHeader[offset] & FDPBOUTPUTDEALYLENGTHMINUS14H) << 1) | ((spsHeader[offset+1] & FDPBOUTPUTDEALYLENGTHMINUS14L) >> 7); //u(5)
				offset++;
				headers->sps.naltimeOffsetLength = (spsHeader[offset] & FTIMEOFFSETLENGTH1) >> 2; //u(5)
				break;
			case 3:
				headers->sps.nalinitialCpbRemovalDelayLengthMinus1 = (spsHeader[offset] & FINITIALCPBREMOVALDELAYLENGTHMINUS13); //u(5)
				offset++;
				headers->sps.nalcpbRemovalDelayLengthMinus1 = ((spsHeader[offset] & FCPBREMOVALDELAYLENGTHMINUS10) >> 3); //u(5)
				headers->sps.naldpbOutputDelayLengthMinus1 = ((spsHeader[offset] & FDPBOUTPUTDEALYLENGTHMINUS15H) << 2) | ((spsHeader[offset+1] & FDPBOUTPUTDEALYLENGTHMINUS15L) >> 6); //u(5)
				offset++;
				headers->sps.naltimeOffsetLength = (spsHeader[offset] & FTIMEOFFSETLENGTH2) >> 1; //u(5)
				break;
			case 4:
				headers->sps.nalinitialCpbRemovalDelayLengthMinus1 = ((spsHeader[offset] & FINITIALCPBREMOVALDELAYLENGTHMINUS14H) << 1 ) | ((spsHeader[offset] & FINITIALCPBREMOVALDELAYLENGTHMINUS14L) >> 7); //u(5)
				offset++;
				headers->sps.nalcpbRemovalDelayLengthMinus1 = ((spsHeader[offset] & FCPBREMOVALDELAYLENGTHMINUS11) >> 2); //u(5)
				headers->sps.naldpbOutputDelayLengthMinus1 = ((spsHeader[offset] & FDPBOUTPUTDEALYLENGTHMINUS16H) << 3) | ((spsHeader[offset+1] & FDPBOUTPUTDEALYLENGTHMINUS16L) >> 5); //u(5)
				offset++;
				headers->sps.naltimeOffsetLength = (spsHeader[offset] & FTIMEOFFSETLENGTH3); //u(5)
				break;
			case 5:
				headers->sps.nalinitialCpbRemovalDelayLengthMinus1 = ((spsHeader[offset] & FINITIALCPBREMOVALDELAYLENGTHMINUS15H) << 2 ) | ((spsHeader[offset] & FINITIALCPBREMOVALDELAYLENGTHMINUS15L) >> 6); //u(5)
				offset++;
				headers->sps.nalcpbRemovalDelayLengthMinus1 = ((spsHeader[offset] & FCPBREMOVALDELAYLENGTHMINUS12) >> 1); //u(5)
				headers->sps.naldpbOutputDelayLengthMinus1 = ((spsHeader[offset] & FDPBOUTPUTDEALYLENGTHMINUS17H) << 4) | ((spsHeader[offset+1] & FDPBOUTPUTDEALYLENGTHMINUS17L) >> 4); //u(5)
				offset++;
				headers->sps.naltimeOffsetLength = ((spsHeader[offset] & FTIMEOFFSETLENGTH4H) << 1) | ((spsHeader[offset+1] & FTIMEOFFSETLENGTH4L) >> 7); //u(5)
				offset++;
				break;
			case 6:
				headers->sps.nalinitialCpbRemovalDelayLengthMinus1 = ((spsHeader[offset] & FINITIALCPBREMOVALDELAYLENGTHMINUS16H) << 3 ) | ((spsHeader[offset] & FINITIALCPBREMOVALDELAYLENGTHMINUS16L) >> 5); //u(5)
				offset++;
				headers->sps.nalcpbRemovalDelayLengthMinus1 = (spsHeader[offset] & FCPBREMOVALDELAYLENGTHMINUS13); //u(5)
				offset++;
				headers->sps.naldpbOutputDelayLengthMinus1 = ((spsHeader[offset] & FDPBOUTPUTDEALYLENGTHMINUS10) >> 3); //u(5)
				headers->sps.naltimeOffsetLength = ((spsHeader[offset] & FTIMEOFFSETLENGTH5H) << 2) | ((spsHeader[offset+1] & FTIMEOFFSETLENGTH5L) >> 6); //u(5)
				offset++;
				break;
			case 7:
				headers->sps.nalinitialCpbRemovalDelayLengthMinus1 = ((spsHeader[offset] & FINITIALCPBREMOVALDELAYLENGTHMINUS17H) << 4) | ((spsHeader[offset] & FINITIALCPBREMOVALDELAYLENGTHMINUS17L) >> 4); //u(5)
				offset++;
				headers->sps.nalcpbRemovalDelayLengthMinus1 = ((spsHeader[offset] & FCPBREMOVALDELAYLENGTHMINUS14H) << 1) | ((spsHeader[offset+1] & FCPBREMOVALDELAYLENGTHMINUS14L) >> 7); //u(5)
				offset++;
				headers->sps.naldpbOutputDelayLengthMinus1 = ((spsHeader[offset] & FDPBOUTPUTDEALYLENGTHMINUS11) >> 2); //u(5)
				headers->sps.naltimeOffsetLength = ((spsHeader[offset] & FTIMEOFFSETLENGTH6H) << 3) | ((spsHeader[offset+1] & FTIMEOFFSETLENGTH6L) >> 5); //u(5)
				offset++;
				break;
			}
		}
		headers->sps.vclHrdParametersPresentFlag = (spsHeader[offset] & FVCLHRDPARAMETERSPRESENTLAG) >> 2;
		if (headers->sps.vclHrdParametersPresentFlag) {
			int index = 0;
			headers->sps.vclcpbCntMinus1 = ((spsHeader[offset] & FVCLCPBCNTMINUS1H) << 3) | ((spsHeader[offset+1] & FVCLCPBCNTMINUS1L) >> 5);
			offset++;
			headers->sps.vclbitRateScale = (spsHeader[offset] & FVCLBITRATESCALE) >> 1;
			headers->sps.vclcpbSizeScale = ((spsHeader[offset] & FVCLCPBSIZESCALEH) << 3) | ((spsHeader[offset+1] & FVCLCPBSIZESCALEL) >> 5);
			offset++;
			for (int i = 0; i < headers->sps.nalcpbCntMinus1; i++) {
				index = ((i+3) % 8);
				switch (index) {
				case 0:
					headers->sps.vclbitRateValueMinus1[i] = ((spsHeader[offset] & FBITRATEVALUEMINUS1H0) * 16777216) + ((spsHeader[offset+1] & FBITRATEVALUEMINUS1M) * 65536) + ((spsHeader[offset+2] & FBITRATEVALUEMINUS1M) * 256) + ((spsHeader[offset+3] & FBITRATEVALUEMINUS1L0));
					offset+=4;
					headers->sps.vclcpbSizeValueMinus1[i] = ((spsHeader[offset] & FCPBSIZEVALUEMINUS1H0) * 16777216) + ((spsHeader[offset+1] & FCPBSIZEVALUEMINUS1M) * 65536) + ((spsHeader[offset+2] & FCPBSIZEVALUEMINUS1M) * 256) + ((spsHeader[offset+3] & FCPBSIZEVALUEMINUS1L0));
					offset+=4;
					headers->sps.vclcbrFlag = (spsHeader[offset] & FCBRFLAG0) >> 7;
					break;
				case 1:
					headers->sps.vclbitRateValueMinus1[i] = ((spsHeader[offset] & FBITRATEVALUEMINUS1H1) * 33554432) + ((spsHeader[offset+1] & FBITRATEVALUEMINUS1M) * 131072) + ((spsHeader[offset+2] & FBITRATEVALUEMINUS1M) * 512) + ((spsHeader[offset+3] & FBITRATEVALUEMINUS1M) * 2) + ((spsHeader[offset+4] & FBITRATEVALUEMINUS1L1) >> 7);
					offset+=4;
					headers->sps.vclcpbSizeValueMinus1[i] = ((spsHeader[offset] & FCPBSIZEVALUEMINUS1H1) * 33554432) + ((spsHeader[offset+1] & FCPBSIZEVALUEMINUS1M) * 131072) + ((spsHeader[offset+2] & FCPBSIZEVALUEMINUS1M) * 512) + ((spsHeader[offset+3] & FCPBSIZEVALUEMINUS1M) * 2) + ((spsHeader[offset+4] & FCPBSIZEVALUEMINUS1L1) >> 7);
					offset+=4;
					headers->sps.vclcbrFlag = (spsHeader[offset] & FCBRFLAG1) >> 6;
					break;
				case 2:
					headers->sps.vclbitRateValueMinus1[i] = ((spsHeader[offset] & FBITRATEVALUEMINUS1H2) * 67108864) + ((spsHeader[offset+1] & FBITRATEVALUEMINUS1M) * 262144) + ((spsHeader[offset+2] & FBITRATEVALUEMINUS1M) * 1024) + ((spsHeader[offset+3] & FBITRATEVALUEMINUS1M) * 4) + ((spsHeader[offset+4] & FBITRATEVALUEMINUS1L2) >> 6);
					offset+=4;
					headers->sps.vclcpbSizeValueMinus1[i] = ((spsHeader[offset] & FCPBSIZEVALUEMINUS1H2) * 67108864) + ((spsHeader[offset+1] & FCPBSIZEVALUEMINUS1M) * 262144) + ((spsHeader[offset+2] & FCPBSIZEVALUEMINUS1M) * 1024) + ((spsHeader[offset+3] & FCPBSIZEVALUEMINUS1M) * 4) + ((spsHeader[offset+4] & FCPBSIZEVALUEMINUS1L2) >> 6);
					offset+=4;
					headers->sps.vclcbrFlag = (spsHeader[offset] & FCBRFLAG2) >> 5;
					break;
				case 3:
					headers->sps.vclbitRateValueMinus1[i] = ((spsHeader[offset] & FBITRATEVALUEMINUS1H3) * 134217728) + ((spsHeader[offset+1] & FBITRATEVALUEMINUS1M) * 524288) + ((spsHeader[offset+2] & FBITRATEVALUEMINUS1M) * 2048) + ((spsHeader[offset+3] & FBITRATEVALUEMINUS1M) * 8) + ((spsHeader[offset+4] & FBITRATEVALUEMINUS1L3) >> 5);
					offset+=4;
					headers->sps.vclcpbSizeValueMinus1[i] = ((spsHeader[offset] & FCPBSIZEVALUEMINUS1H3) * 134217728) + ((spsHeader[offset+1] & FCPBSIZEVALUEMINUS1M) * 524288) + ((spsHeader[offset+2] & FCPBSIZEVALUEMINUS1M) * 2048) + ((spsHeader[offset+3] & FCPBSIZEVALUEMINUS1M) * 8) + ((spsHeader[offset+4] & FCPBSIZEVALUEMINUS1L3) >> 5);
					offset+=4;
					headers->sps.vclcbrFlag = (spsHeader[offset] & FCBRFLAG3) >> 4;
					break;
				case 4:
					headers->sps.vclbitRateValueMinus1[i] = ((spsHeader[offset] & FBITRATEVALUEMINUS1H4) * 268435456) + ((spsHeader[offset+1] & FBITRATEVALUEMINUS1M) * 1048576) + ((spsHeader[offset+2] & FBITRATEVALUEMINUS1M) * 4096) + ((spsHeader[offset+3] & FBITRATEVALUEMINUS1M) * 16) + ((spsHeader[offset+4] & FBITRATEVALUEMINUS1L4) >> 4);
					offset+=4;
					headers->sps.vclcpbSizeValueMinus1[i] = ((spsHeader[offset] & FCPBSIZEVALUEMINUS1H4) * 268435456) + ((spsHeader[offset+1] & FCPBSIZEVALUEMINUS1M) * 1048576) + ((spsHeader[offset+2] & FCPBSIZEVALUEMINUS1M) * 4096) + ((spsHeader[offset+3] & FCPBSIZEVALUEMINUS1M) * 16) + ((spsHeader[offset+4] & FCPBSIZEVALUEMINUS1L4) >> 4);
					offset+=4;
					headers->sps.vclcbrFlag = (spsHeader[offset] & FCBRFLAG4) >> 3;
					break;
				case 5:
					headers->sps.vclbitRateValueMinus1[i] = ((spsHeader[offset] & FBITRATEVALUEMINUS1H5) * 536870912) + ((spsHeader[offset+1] & FBITRATEVALUEMINUS1M) * 2097152) + ((spsHeader[offset+2] & FBITRATEVALUEMINUS1M) * 8192) + ((spsHeader[offset+3] & FBITRATEVALUEMINUS1M) * 32) + ((spsHeader[offset+4] & FBITRATEVALUEMINUS1L5) >> 3);
					offset+=4;
					headers->sps.vclcpbSizeValueMinus1[i] = ((spsHeader[offset] & FCPBSIZEVALUEMINUS1H5) * 536870912) + ((spsHeader[offset+1] & FCPBSIZEVALUEMINUS1M) * 2097152) + ((spsHeader[offset+2] & FCPBSIZEVALUEMINUS1M) * 8192) + ((spsHeader[offset+3] & FCPBSIZEVALUEMINUS1M) * 32) + ((spsHeader[offset+4] & FCPBSIZEVALUEMINUS1L5) >> 3);
					offset+=4;
					headers->sps.vclcbrFlag = (spsHeader[offset] & FCBRFLAG5) >> 2;
					break;
				case 6:
					headers->sps.vclbitRateValueMinus1[i] = ((spsHeader[offset] & FBITRATEVALUEMINUS1H5) * 1073741824) + ((spsHeader[offset+1] & FBITRATEVALUEMINUS1M) * 2097152) + ((spsHeader[offset+2] & FBITRATEVALUEMINUS1M) * 16384) + ((spsHeader[offset+3] & FBITRATEVALUEMINUS1M) * 64) + ((spsHeader[offset+4] & FBITRATEVALUEMINUS1L5) >> 2);
					offset+=4;
					headers->sps.vclcpbSizeValueMinus1[i] = ((spsHeader[offset] & FCPBSIZEVALUEMINUS1H5) * 1073741824) + ((spsHeader[offset+1] & FCPBSIZEVALUEMINUS1M) * 2097152) + ((spsHeader[offset+2] & FCPBSIZEVALUEMINUS1M) * 16384) + ((spsHeader[offset+3] & FCPBSIZEVALUEMINUS1M) * 64) + ((spsHeader[offset+4] & FCPBSIZEVALUEMINUS1L5) >> 2);
					offset+=4;
					headers->sps.vclcbrFlag = (spsHeader[offset] & FCBRFLAG6) >> 1;
					break;
				case 7:
					headers->sps.vclbitRateValueMinus1[i] = ((spsHeader[offset] & FBITRATEVALUEMINUS1H5) * 2147483648) + ((spsHeader[offset+1] & FBITRATEVALUEMINUS1M) * 4194304) + ((spsHeader[offset+2] & FBITRATEVALUEMINUS1M) * 32768) + ((spsHeader[offset+3] & FBITRATEVALUEMINUS1M) * 128) + ((spsHeader[offset+4] & FBITRATEVALUEMINUS1L5) >> 1);
					offset+=4;
					headers->sps.vclcpbSizeValueMinus1[i] = ((spsHeader[offset] & FCPBSIZEVALUEMINUS1H5) * 2147483648) + ((spsHeader[offset+1] & FCPBSIZEVALUEMINUS1M) * 4194304) + ((spsHeader[offset+2] & FCPBSIZEVALUEMINUS1M) * 32768) + ((spsHeader[offset+3] & FCPBSIZEVALUEMINUS1M) * 128) + ((spsHeader[offset+4] & FCPBSIZEVALUEMINUS1L5) >> 1);
					offset+=4;
					headers->sps.vclcbrFlag = (spsHeader[offset] & FCBRFLAG7);
					offset++;
					break;
				}
			}

			switch (index) {
			case 0:
				headers->sps.vclinitialCpbRemovalDelayLengthMinus1 = (spsHeader[offset] & FINITIALCPBREMOVALDELAYLENGTHMINUS10) >> 3; //u(5)
				headers->sps.vclcpbRemovalDelayLengthMinus1 = ((spsHeader[offset] & FCPBREMOVALDELAYLENGTHMINUS15H) << 2) | ((spsHeader[offset+1] & FCPBREMOVALDELAYLENGTHMINUS15L) >> 6); //u(5)
				offset++;
				headers->sps.vcldpbOutputDelayLengthMinus1 = (spsHeader[offset] & FDPBOUTPUTDEALYLENGTHMINUS12) >> 1; //u(5)
				headers->sps.vcltimeOffsetLength = ((spsHeader[offset] & FTIMEOFFSETLENGTH7H) << 4) | ((spsHeader[offset+1] & FTIMEOFFSETLENGTH7L) >> 4); //u(5)
				offset++;
				break;
			case 1:
				headers->sps.vclinitialCpbRemovalDelayLengthMinus1 = (spsHeader[offset] & FINITIALCPBREMOVALDELAYLENGTHMINUS11) >> 2; //u(5)
				headers->sps.vclcpbRemovalDelayLengthMinus1 = ((spsHeader[offset] & FCPBREMOVALDELAYLENGTHMINUS16H) << 3) | ((spsHeader[offset+1] & FCPBREMOVALDELAYLENGTHMINUS16L) >> 5); //u(5)
				offset++;
				headers->sps.vcldpbOutputDelayLengthMinus1 = (spsHeader[offset] & FDPBOUTPUTDEALYLENGTHMINUS13); //u(5)
				offset++;
				headers->sps.vcltimeOffsetLength = (spsHeader[offset] & FTIMEOFFSETLENGTH0) >> 3; //u(5)
				break;
			case 2:
				headers->sps.vclinitialCpbRemovalDelayLengthMinus1 = (spsHeader[offset] & FINITIALCPBREMOVALDELAYLENGTHMINUS12) >> 1; //u(5)
				headers->sps.vclcpbRemovalDelayLengthMinus1 = ((spsHeader[offset] & FCPBREMOVALDELAYLENGTHMINUS17H) << 4) | ((spsHeader[offset+1] & FCPBREMOVALDELAYLENGTHMINUS17L) >> 4); //u(5)
				offset++;
				headers->sps.vcldpbOutputDelayLengthMinus1 = ((spsHeader[offset] & FDPBOUTPUTDEALYLENGTHMINUS14H) << 1) | ((spsHeader[offset+1] & FDPBOUTPUTDEALYLENGTHMINUS14L) >> 7); //u(5)
				offset++;
				headers->sps.vcltimeOffsetLength = (spsHeader[offset] & FTIMEOFFSETLENGTH1) >> 2; //u(5)
				break;
			case 3:
				headers->sps.vclinitialCpbRemovalDelayLengthMinus1 = (spsHeader[offset] & FINITIALCPBREMOVALDELAYLENGTHMINUS13); //u(5)
				offset++;
				headers->sps.vclcpbRemovalDelayLengthMinus1 = ((spsHeader[offset] & FCPBREMOVALDELAYLENGTHMINUS10) >> 3); //u(5)
				headers->sps.vcldpbOutputDelayLengthMinus1 = ((spsHeader[offset] & FDPBOUTPUTDEALYLENGTHMINUS15H) << 2) | ((spsHeader[offset+1] & FDPBOUTPUTDEALYLENGTHMINUS15L) >> 6); //u(5)
				offset++;
				headers->sps.vcltimeOffsetLength = (spsHeader[offset] & FTIMEOFFSETLENGTH2) >> 1; //u(5)
				break;
			case 4:
				headers->sps.vclinitialCpbRemovalDelayLengthMinus1 = ((spsHeader[offset] & FINITIALCPBREMOVALDELAYLENGTHMINUS14H) << 1 ) | ((spsHeader[offset] & FINITIALCPBREMOVALDELAYLENGTHMINUS14L) >> 7); //u(5)
				offset++;
				headers->sps.vclcpbRemovalDelayLengthMinus1 = ((spsHeader[offset] & FCPBREMOVALDELAYLENGTHMINUS11) >> 2); //u(5)
				headers->sps.vcldpbOutputDelayLengthMinus1 = ((spsHeader[offset] & FDPBOUTPUTDEALYLENGTHMINUS16H) << 3) | ((spsHeader[offset+1] & FDPBOUTPUTDEALYLENGTHMINUS16L) >> 5); //u(5)
				offset++;
				headers->sps.vcltimeOffsetLength = (spsHeader[offset] & FTIMEOFFSETLENGTH3); //u(5)
				break;
			case 5:
				headers->sps.vclinitialCpbRemovalDelayLengthMinus1 = ((spsHeader[offset] & FINITIALCPBREMOVALDELAYLENGTHMINUS15H) << 2 ) | ((spsHeader[offset] & FINITIALCPBREMOVALDELAYLENGTHMINUS15L) >> 6); //u(5)
				offset++;
				headers->sps.vclcpbRemovalDelayLengthMinus1 = ((spsHeader[offset] & FCPBREMOVALDELAYLENGTHMINUS12) >> 1); //u(5)
				headers->sps.vcldpbOutputDelayLengthMinus1 = ((spsHeader[offset] & FDPBOUTPUTDEALYLENGTHMINUS17H) << 4) | ((spsHeader[offset+1] & FDPBOUTPUTDEALYLENGTHMINUS17L) >> 4); //u(5)
				offset++;
				headers->sps.vcltimeOffsetLength = ((spsHeader[offset] & FTIMEOFFSETLENGTH4H) << 1) | ((spsHeader[offset+1] & FTIMEOFFSETLENGTH4L) >> 7); //u(5)
				offset++;
				break;
			case 6:
				headers->sps.vclinitialCpbRemovalDelayLengthMinus1 = ((spsHeader[offset] & FINITIALCPBREMOVALDELAYLENGTHMINUS16H) << 3 ) | ((spsHeader[offset] & FINITIALCPBREMOVALDELAYLENGTHMINUS16L) >> 5); //u(5)
				offset++;
				headers->sps.vclcpbRemovalDelayLengthMinus1 = (spsHeader[offset] & FCPBREMOVALDELAYLENGTHMINUS13); //u(5)
				offset++;
				headers->sps.vcldpbOutputDelayLengthMinus1 = ((spsHeader[offset] & FDPBOUTPUTDEALYLENGTHMINUS10) >> 3); //u(5)
				headers->sps.vcltimeOffsetLength = ((spsHeader[offset] & FTIMEOFFSETLENGTH5H) << 2) | ((spsHeader[offset+1] & FTIMEOFFSETLENGTH5L) >> 6); //u(5)
				offset++;
				break;
			case 7:
				headers->sps.vclinitialCpbRemovalDelayLengthMinus1 = ((spsHeader[offset] & FINITIALCPBREMOVALDELAYLENGTHMINUS17H) << 4) | ((spsHeader[offset] & FINITIALCPBREMOVALDELAYLENGTHMINUS17L) >> 4); //u(5)
				offset++;
				headers->sps.vclcpbRemovalDelayLengthMinus1 = ((spsHeader[offset] & FCPBREMOVALDELAYLENGTHMINUS14H) << 1) | ((spsHeader[offset+1] & FCPBREMOVALDELAYLENGTHMINUS14L) >> 7); //u(5)
				offset++;
				headers->sps.vcldpbOutputDelayLengthMinus1 = ((spsHeader[offset] & FDPBOUTPUTDEALYLENGTHMINUS11) >> 2); //u(5)
				headers->sps.vcltimeOffsetLength = ((spsHeader[offset] & FTIMEOFFSETLENGTH6H) << 3) | ((spsHeader[offset+1] & FTIMEOFFSETLENGTH6L) >> 5); //u(5)
				offset++;
				break;
			}
		}		
		if (headers->sps.nalHrdParametersPresentFlag || headers->sps.vclHrdParametersPresentFlag) {
			headers->sps.lowDelayHrdFlag = (spsHeader[offset] & FLOWDELAYHRDFLAG) >> 1;
		}
		headers->sps.picStructPresentFlag = (spsHeader[offset] & FPICSTRUCTPRESENTLAG) >> 1;
		headers->sps.bitstreamRestrictionFlag = (spsHeader[offset] & FBITSTREAMRESTRICTIONFLAG);
		offset++;
		if (headers->sps.bitstreamRestrictionFlag) {
			headers->sps.montionVectorsOverPicBoundariesFlag = (spsHeader[offset] & FMONTIONVECTORSOVERPICBOUNDARIESFLAG) >> 7;
			headers->sps.maxBytesPerPicDenom = (spsHeader[offset] & FMAXBYTESPERPICDENOM) >> 6;
			headers->sps.maxBitsPerMbDenom = (spsHeader[offset] & FMAXBITSPERMBDENOM) >> 5;
			headers->sps.log2MaxMvLengthHorizontal = ((spsHeader[offset] & FLOG2MAXMVLENGTHHORIZONTALH) << 2) | ((spsHeader[offset+1] & FLOG2MAXMVLENGTHHORIZONTALL) >> 6);
			offset++;
			headers->sps.log2MaxMvLengthVertical = ((spsHeader[offset] & FLOG2MAXMVLENGTHVERTICALH) << 1) | ((spsHeader[offset+1] & FLOG2MAXMVLENGTHVERTICALL) >> 7);
			offset++;
			headers->sps.maxNumReorderFrames = (spsHeader[offset] & FMAXNUMREODERFRAMES) >> 6;
			headers->sps.maxDecFrameBuffering = (spsHeader[offset] & FMAXEDCFRAMEBUFFERING) >> 1;
			headers->sps.rbspStopBit = (spsHeader[offset] & FRBSPSTOPBIT) >> 1;
		}
	}

	return true;
}
uint32_t getWidth(nalHeader headers) {
	uint32_t width = ((headers.sps.picWidthInMbsMinus1+1)*16) - (headers.sps.frameCroppinRightOffset*2) - (headers.sps.frameCroppinLeftOffset*2);
	return width;
}
uint32_t getHeight(nalHeader headers) {
	uint32_t height = (((2 - headers.sps.framMbsOnlyFlag) * (headers.sps.picHeightInMapUnitsMinus1+1)*16)) - (headers.sps.frameCroppinBottomOffset*2) - (headers.sps.frameCroppinTopOffset*2);
	return height;
}
