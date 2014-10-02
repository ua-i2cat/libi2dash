#include "../include/i2nalparser.h"

bool ppsToRbsp(unsigned char* ppsHeader, uint32_t ppsLength, nalHeader* headers) {
	int offset = 0;
	if ((ppsLength <=0) || (ppsLength > MAXLENGTHPPS) || (ppsHeader == NULL))
		return false;
	headers->pps.picParameterSetId = (ppsHeader[offset] & FPICPARAMETERSETID) >> 7;
	headers->pps.seqParameterSetId = (ppsHeader[offset] & FSEQPARAMETERSETID) >> 6;
	headers->pps.entropyCondingModeFlag = (ppsHeader[offset] & FENTROPYCODINGMODEFLAG) >> 5;
	headers->pps.bottomFieldPicOrderInFramePresentFlag = (ppsHeader[offset] & FBOTTOMFIELDPICORDERINFRAMEPRESENTFLAG) >> 4;
	headers->pps.numSliceGroupsMinus1 = (ppsHeader[offset] & FNUMSLICEGROUPMINUS1) >> 3;
	if (headers->pps.numSliceGroupsMinus1 > 0) {//TODO check this!
		headers->pps.sliceGroupMapType = (ppsHeader[0] & FSLICEGROUPSMAPTYPE);
		offset++;
		if (headers->pps.sliceGroupMapType == 0) {
			for (int iGroup = 0; iGroup <= headers->pps.numSliceGroupsMinus1; iGroup++) {
				headers->pps.runLengthMinus1[iGroup] == ppsHeader[offset];
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
				headers->pps.sliceGroupId[i] == ppsHeader[offset];
				offset++;
			}
			
		}
	}
	headers->pps.numRefIdx10DefaultActiveMinus1 = (ppsHeader[offset] & FNUMREFIDX10DEFAULTACTIVEMINUS1) - 1;
	offset++;
	headers->pps.numRefIdx11DefaultActiveMinus1 = (ppsHeader[offset] & FNUMREFIDX11DEFAULTACTIVEMINUS1) - 1;
	headers->pps.weightedPredFlag = (ppsHeader[offset] & FWEIGHTEDPREDFLAG);
	headers->pps.weightedBipredIdc = (ppsHeader[offset] & FWEIGHTEDBIPREDIDC);
	headers->pps.picInitQpMinus26 = (((ppsHeader[offset] & FPICINITQPMINUS26H) << 1) | ((ppsHeader[offset+1] & FPICINITQPMINUS26L) >> 7) - 26) & FSIGNOQP26; //TODO check this
	offset++;
	headers->pps.picInitQsMinus26 = (((ppsHeader[offset] & FPICINITQSMINUS26) >> 6) - 26)  & FSIGNOQS26; //TODO check this
	headers->pps.chromaQpIndexOffset = (ppsHeader[offset] & FCHROMAQPINDEXOFFSET) >> 1; //Mirar esto
	headers->pps.deblockingFilterControlPresentFlag = (ppsHeader[offset] & FDEBLOCKINGFILTERTCONTROLPRESENTFLAG);
	offset++;
	headers->pps.constrainedIntraPredFlag = (ppsHeader[offset] & FCONSTRAINEDINTRAPREDFLAG) >> 7;
	headers->pps.redundantPicCntPresentFlag = (ppsHeader[offset] & FCONSTRAINEDINTRAPREDFLAG) >> 6;
	if (true) {//TODO more_rbsp_data()
		headers->pps.transform8x8ModeFlag = (ppsHeader[offset] & FCONSTRAINEDINTRAPREDFLAG) >> 5;
		headers->pps.picScalingMatrixPresentFlag = (ppsHeader[offset] & FCONSTRAINEDINTRAPREDFLAG) >> 4;
		if (headers->pps.picScalingMatrixPresentFlag) {
			for (int i=0; i < 6 + (((headers->sps.chromaFormatIdc != 3) ? 2 : 6) * headers->pps.transform8x8ModeFlag); i++) {
				picScalingListPresentFlag[i] = ;
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
	headers->sps.seqParameterSetId = (spsHeader[offset] & FSEQPARAMETERSETID);
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
		heaedrs->sps.log2MaxPicOrderCntLsbMinus4 = ((spsHeader[offset] & FLOG2MAXPICORDERCNTLSBMINUSH) << 4) | ((spsHeader[offset+1] & FLOG2MAXPICORDERCNTLSBMINUSL) >> 4);
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
		headers->sps.frameCroppinBottomOffset = ((spsHeader[offset] & FFRAMECROPBOTTOMOFFSETH) >> 3) | ((spsHeader[offset] & FFRAMECROPBOTTOMOFFSETL) >> 3);
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
			eaders->sps.chromaSampleLocTypeBottomField = ((spsHeader[offset] & FCHROMASAMPLELOCTYPEBOTTOMFIELDH) << 2) | ((spsHeader[offset+1] & FCHROMASAMPLELOCTYPEBOTTOMFIELDL) >> 6);
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
			byte nalcpbCntMinus1; //ue(v)
			byte nalbitRateScale; //u(4)
			byte nalcpbSizeScale; //u(4)
			byte nalbitRateValueMinus1[MAXCNTMINUSONE]; //ue(v)
			byte nalcpbSizeValueMinus1[MAXCNTMINUSONE]; //ue(v)
			byte nalcbrFlag; //u(1)
			byte nalinitialCpbRemovalDelayLengthMinus1; //u(5)
			byte nalcpbRemovalDelayLengthMinus1; //u(5)
			byte naldpbOutputDelayLengthMinus1; //u(5)
			byte naltimeOffsetLength; //u(5)
		}
		headers->sps.vclHrdParametersPresentFlag = (spsHeader[offset] & FVCLHRDPARAMETERSPRESENTLAG) >> 2;
		if (headers->sps.vclHrdParametersPresentFlag) {
			byte vclcpbCntMinus1; //ue(v)
			byte vclbitRateScale; //u(4)
			byte vclcpbSizeScale; //u(4)
			byte vclbitRateValueMinus1[MAXCNTMINUSONE]; //ue(v)
			byte vclcpbSizeValueMinus1[MAXCNTMINUSONE]; //ue(v)
			byte vclcbrFlag; //u(1)
			byte vclinitialCpbRemovalDelayLengthMinus1; //u(5)
			byte vclcpbRemovalDelayLengthMinus1; //u(5)
			byte vcldpbOutputDelayLengthMinus1; //u(5)
			byte vcltimeOffsetLength; //u(5)
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
uint32_t getWidth(nalHeader headers);
uint32_t getHeight(nalHeader headers);
