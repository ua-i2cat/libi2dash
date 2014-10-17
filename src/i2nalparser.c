#include "../include/i2nalparser.h"

//PPS

void getValue (byte* buffer, byte* output, unsigned int bytePos, int bitPos, int lenghtBits) {
	//lenghtBits <= 32
	byte auxValue;
	int valueBytePos = 0, valueBitPos = 0, bufferBytePos = 0;
	int bitCopy = bitPos;
	byte value[4];
	//printf ("bytePos %u; bitPos %u; len %d\n", bytePos, bitPos, lenghtBits);
	value[0] = 0;
	value[1] = 0;
	value[2] = 0;
	value[3] = 0;

	for (int i = bitPos; i < (lenghtBits + bitPos); i++) {
		switch (bitCopy) {
			case 0:
				auxValue = buffer[bytePos + bufferBytePos] & 0x01;
				value[3-valueBytePos] <<= (valueBitPos ? 1 : 0);
				bufferBytePos++;
				valueBitPos++;
				value[3-valueBytePos] |= auxValue;
				break;
			case 1:
				auxValue = (buffer[bytePos + bufferBytePos] & 0x02) >> 1;
				value[3-valueBytePos] <<= (valueBitPos ? 1 : 0);
				valueBitPos++;
				value[3-valueBytePos] |= auxValue;
				break;
			case 2:
				auxValue = (buffer[bytePos + bufferBytePos] & 0x04) >> 2;
				value[3-valueBytePos] <<= (valueBitPos ? 1 : 0);
				valueBitPos++;
				value[3-valueBytePos] |= auxValue;
				break;
			case 3:
				auxValue = (buffer[bytePos + bufferBytePos] & 0x08) >> 3;
				value[3-valueBytePos] <<= (valueBitPos ? 1 : 0);
				valueBitPos++;
				value[3-valueBytePos] |= auxValue;
				break;
			case 4:
				auxValue = (buffer[bytePos + bufferBytePos] & 0x10) >> 4;
				value[3-valueBytePos] <<= (valueBitPos ? 1 : 0);
				valueBitPos++;
				value[3-valueBytePos] |= auxValue;
				break;
			case 5:
				auxValue = (buffer[bytePos + bufferBytePos] & 0x20) >> 5;
				value[3-valueBytePos] <<= (valueBitPos ? 1 : 0);
				valueBitPos++;
				value[3-valueBytePos] |= auxValue;
				break;
			case 6:
				auxValue = (buffer[bytePos + bufferBytePos] & 0x40) >> 6;
				value[3-valueBytePos] <<= (valueBitPos ? 1 : 0);
				valueBitPos++;
				value[3-valueBytePos] |= auxValue;
				break;
			case 7:
				auxValue = (buffer[bytePos + bufferBytePos] & 0x80) >> 7;
				value[3-valueBytePos] <<= (valueBitPos ? 1 : 0);
				value[3-valueBytePos] |= auxValue;
				valueBitPos++;
				break;
			default:
				break;
		}
		bitCopy--;
		if (bitCopy == -1) {
			bitCopy= 7;
		}
		if ((valueBitPos % 8) == 0) {
			valueBytePos++;
		}
	}
	output[0] = value[3];
	if (lenghtBits > 8)
		output[1] = value[2];
	if (lenghtBits > 16)
		output[2] = value[1];
	if (lenghtBits > 24)
		output[3] = value[0];
}

void getValueInt16 (byte* buffer, int* output, unsigned int bytePos, int bitPos, int lenghtBits) {
	//lenghtBits <= 16
	byte auxValue;
	int valueBytePos = 0, valueBitPos = 0, bufferBytePos = 0;
	int bitCopy = bitPos;
	byte value[4];
	//printf ("bytePos %u; bitPos %u; len %d\n", bytePos, bitPos, lenghtBits);
	value[0] = 0;
	value[1] = 0;
	value[2] = 0;
	value[3] = 0;

	for (int i = bitPos; i < (lenghtBits + bitPos); i++) {
		switch (bitCopy) {
			case 0:
				auxValue = buffer[bytePos + bufferBytePos] & 0x01;
				value[3-valueBytePos] <<= (valueBitPos ? 1 : 0);
				bufferBytePos++;
				valueBitPos++;
				value[3-valueBytePos] |= auxValue;
				break;
			case 1:
				auxValue = (buffer[bytePos + bufferBytePos] & 0x02) >> 1;
				value[3-valueBytePos] <<= (valueBitPos ? 1 : 0);
				valueBitPos++;
				value[3-valueBytePos] |= auxValue;
				break;
			case 2:
				auxValue = (buffer[bytePos + bufferBytePos] & 0x04) >> 2;
				value[3-valueBytePos] <<= (valueBitPos ? 1 : 0);
				valueBitPos++;
				value[3-valueBytePos] |= auxValue;
				break;
			case 3:
				auxValue = (buffer[bytePos + bufferBytePos] & 0x08) >> 3;
				value[3-valueBytePos] <<= (valueBitPos ? 1 : 0);
				valueBitPos++;
				value[3-valueBytePos] |= auxValue;
				break;
			case 4:
				auxValue = (buffer[bytePos + bufferBytePos] & 0x10) >> 4;
				value[3-valueBytePos] <<= (valueBitPos ? 1 : 0);
				valueBitPos++;
				value[3-valueBytePos] |= auxValue;
				break;
			case 5:
				auxValue = (buffer[bytePos + bufferBytePos] & 0x20) >> 5;
				value[3-valueBytePos] <<= (valueBitPos ? 1 : 0);
				valueBitPos++;
				value[3-valueBytePos] |= auxValue;
				break;
			case 6:
				auxValue = (buffer[bytePos + bufferBytePos] & 0x40) >> 6;
				value[3-valueBytePos] <<= (valueBitPos ? 1 : 0);
				valueBitPos++;
				value[3-valueBytePos] |= auxValue;
				break;
			case 7:
				auxValue = (buffer[bytePos + bufferBytePos] & 0x80) >> 7;
				value[3-valueBytePos] <<= (valueBitPos ? 1 : 0);
				value[3-valueBytePos] |= auxValue;
				valueBitPos++;
				break;
			default:
				break;
		}
		bitCopy--;
		if (bitCopy == -1) {
			bitCopy= 7;
		}
		if ((valueBitPos % 8) == 0) {
			valueBytePos++;
		}
	}
	(*output) = 0;
	memcpy(output, value+3, 1);
	memcpy(output+1, value+2, 1);
	//printf("value[2] %u; value[3] %u; output %d\n", value[2], value[3], (*output));
}

bool ppsToRbsp(unsigned char* ppsHeader, uint32_t ppsLength, nalHeader* headers) {
	uint32_t offset = 1;
	int pos = 7;
	printf ("\n\n ppsLength %u\n\n", ppsLength);
	if ((ppsLength <=0) || (ppsLength > MAXLENGTHPPS) || (ppsHeader == NULL))
		return false;
	getValue(ppsHeader, &(headers->pps.picParameterSetId), offset, pos, FLENGTHPICPARAMETERSETID);
	pos-= FLENGTHPICPARAMETERSETID;
	getValue(ppsHeader, &(headers->pps.seqParameterSetId), offset, pos, FLENGTHPPSSEQPARAMETERSETID);
	pos-= FLENGTHPPSSEQPARAMETERSETID;
	getValue(ppsHeader, &(headers->pps.entropyCondingModeFlag), offset, pos, FLENGTHENTROPYCODINGMODEFLAG);
	pos-= FLENGTHENTROPYCODINGMODEFLAG;
	getValue(ppsHeader, &(headers->pps.bottomFieldPicOrderInFramePresentFlag), offset, pos, FLENGTHBOTTOMFIELDPICORDERINFRAMEPRESENTFLAG);
	pos-= FLENGTHBOTTOMFIELDPICORDERINFRAMEPRESENTFLAG;
	getValue(ppsHeader, &(headers->pps.numSliceGroupsMinus1), offset, pos, FLENGTHNUMSLICEGROUPMINUS1);
	headers->pps.numSliceGroupsMinus1--;
	pos-= FLENGTHNUMSLICEGROUPMINUS1;
	printf ("PPS\n");
	printf ("picParameterSetId %u\nseqParameterSetId %u\nentropyCondingModeFlag %u\nbottomFieldPicOrderInFramePresentFlag %u\nnumSliceGroupsMinus1 %u\n", headers->pps.picParameterSetId, headers->pps.seqParameterSetId, headers->pps.entropyCondingModeFlag, headers->pps.bottomFieldPicOrderInFramePresentFlag, headers->pps.numSliceGroupsMinus1);
	if (headers->pps.numSliceGroupsMinus1 > 0) {//TODO check this!
		getValue(ppsHeader, &(headers->pps.sliceGroupMapType), offset, pos, FLENGTHSLICEGROUPSMAPTYPE);
		pos-= FLENGTHSLICEGROUPSMAPTYPE;
		pos+= 8;
		offset++;
		if (headers->pps.sliceGroupMapType == 0) {
			for (int iGroup = 0; iGroup <= headers->pps.numSliceGroupsMinus1; iGroup++) {
				headers->pps.runLengthMinus1[iGroup] = ppsHeader[offset];
				offset++;
			}
		} else if (headers->pps.sliceGroupMapType == 2) {
			for (int iGroup = 0; iGroup <= headers->pps.numSliceGroupsMinus1; iGroup++) {
				getValue(ppsHeader, &(headers->pps.topLef[iGroup]), offset, pos, FLENGTHTOPLEFT);
				pos-= FLENGTHTOPLEFT;
				getValue(ppsHeader, &(headers->pps.bottomRight[iGroup]), offset, pos, FLENGTHBOTTOMRIGHT);
				pos-= FLENGTHBOTTOMRIGHT;
				pos+= 8;
				offset++;
			} 
		} else if ((headers->pps.sliceGroupMapType > 2) && (headers->pps.sliceGroupMapType < 6)) {
			getValue(ppsHeader, &(headers->pps.sliceGroupChangeDirectionFlag), offset, pos, FLENGTHSLICEGROUPCHANGEDIRECTIONFLAG);
			pos-= FLENGTHSLICEGROUPCHANGEDIRECTIONFLAG;
			getValue(ppsHeader, &(headers->pps.sliceGroupChangeRateMinus1), offset, pos, FLENGTHSLICEGROUPCHANGERATEMINUS1);
			pos-= FLENGTHSLICEGROUPCHANGERATEMINUS1;
			pos+= 8;
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
	getValue(ppsHeader, &(headers->pps.numRefIdxl0DefaultActiveMinus1), offset, pos, FLENGTHNUMREFIDXl0DEFAULTACTIVEMINUS1);
	headers->pps.numRefIdxl0DefaultActiveMinus1--;
	pos-= FLENGTHNUMREFIDXl0DEFAULTACTIVEMINUS1;
	pos+= 8;
	offset++;
	getValue(ppsHeader, &(headers->pps.numRefIdxl1DefaultActiveMinus1), offset, pos, FLENGTHNUMREFIDXl1DEFAULTACTIVEMINUS1);
	headers->pps.numRefIdxl1DefaultActiveMinus1--;
	pos-= FLENGTHNUMREFIDXl1DEFAULTACTIVEMINUS1;
	getValue(ppsHeader, &(headers->pps.weightedPredFlag), offset, pos, FLENGTHWEIGHTEDPREDFLAG);
	pos-= FLENGTHWEIGHTEDPREDFLAG;
	getValue(ppsHeader, &(headers->pps.weightedBipredIdc), offset, pos, FLENGTHWEIGHTEDBIPREDIDC);
	pos-= FLENGTHWEIGHTEDBIPREDIDC;
	getValueInt16(ppsHeader, &(headers->pps.picInitQpMinus26), offset, pos, FLENGTHPICINITQPMINUS26); //TODO check this!
	pos-= FLENGTHPICINITQPMINUS26;
	printf ("numRefIdx10DefaultActiveMinus1 %u\nnumRefIdx11DefaultActiveMinus1 %u\nweightedPredFlag %u\nweightedBipredIdc %u\npicInitQpMinus26 %d\n", headers->pps.numRefIdxl0DefaultActiveMinus1, headers->pps.numRefIdxl1DefaultActiveMinus1, headers->pps.weightedPredFlag, headers->pps.weightedBipredIdc, headers->pps.picInitQpMinus26);
	pos+= 8;
	offset++;
	getValueInt16(ppsHeader, &(headers->pps.picInitQsMinus26), offset, pos, FLENGTHPICINITQSMINUS26);
	pos-= FLENGTHPICINITQSMINUS26;
	getValueInt16(ppsHeader, &(headers->pps.chromaQpIndexOffset), offset, pos, FLENGTHCHROMAQPINDEXOFFSET);
	pos-= FLENGTHCHROMAQPINDEXOFFSET;
	getValue(ppsHeader, &(headers->pps.deblockingFilterControlPresentFlag), offset, pos, FLENGTHDEBLOCKINGFILTERTCONTROLPRESENTFLAG);
	pos-= FLENGTHDEBLOCKINGFILTERTCONTROLPRESENTFLAG;
	pos+= 8;
	offset++;
	getValue(ppsHeader, &(headers->pps.constrainedIntraPredFlag), offset, pos, FLENGTHCONSTRAINEDINTRAPREDFLAG);
	pos-= FLENGTHCONSTRAINEDINTRAPREDFLAG;
	getValue(ppsHeader, &(headers->pps.redundantPicCntPresentFlag), offset, pos, FLENGTHREDUNDANTPICCNTPRESENTLAG);
	pos-= FLENGTHREDUNDANTPICCNTPRESENTLAG;

	printf ("picInitQsMinus26 %d\nchromaQpIndexOffset %d\ndeblockingFilterControlPresentFlag %u\nconstrainedIntraPredFlag %u\nredundantPicCntPresentFlag %u\n", headers->pps.picInitQsMinus26, headers->pps.chromaQpIndexOffset, headers->pps.deblockingFilterControlPresentFlag, headers->pps.constrainedIntraPredFlag, headers->pps.redundantPicCntPresentFlag);

	if (true) {//TODO more_rbsp_data()
		getValue(ppsHeader, &(headers->pps.transform8x8ModeFlag), offset, pos, FLENGTHTRANSFORM8X8MODEFLAG);
		pos-= FLENGTHTRANSFORM8X8MODEFLAG;
		getValue(ppsHeader, &(headers->pps.picScalingMatrixPresentFlag), offset, pos, FLENGTHPICSACALINGMATRIXPRESENTFLAG);
		pos-= FLENGTHPICSACALINGMATRIXPRESENTFLAG;
		printf ("transform8x8ModeFlag %u\npicScalingMatrixPresentFlag %u\n", headers->pps.transform8x8ModeFlag, headers->pps.picScalingMatrixPresentFlag);
		if (headers->pps.picScalingMatrixPresentFlag) {
			int index = 0;
			for (int i=0; i < 6 + (((headers->sps.chromaFormatIdc != 3) ? 2 : 6) * headers->pps.transform8x8ModeFlag); i++) {
				index = (i + 4) % 8;
				switch (index) {
				case 0:
					getValue(ppsHeader, &(headers->pps.picScalingListPresentFlag[i]), offset, pos, FLENGTHPICSACALINGLISTPRESENTFLAG0);
					pos-= FLENGTHPICSACALINGLISTPRESENTFLAG0;
					break;
				case 1:
					getValue(ppsHeader, &(headers->pps.picScalingListPresentFlag[i]), offset, pos, FLENGTHPICSACALINGLISTPRESENTFLAG1);
					pos-= FLENGTHPICSACALINGLISTPRESENTFLAG1;
					break;
				case 2:
					getValue(ppsHeader, &(headers->pps.picScalingListPresentFlag[i]), offset, pos, FLENGTHPICSACALINGLISTPRESENTFLAG2);
					pos-= FLENGTHPICSACALINGLISTPRESENTFLAG2;
					break;
				case 3:
					getValue(ppsHeader, &(headers->pps.picScalingListPresentFlag[i]), offset, pos, FLENGTHPICSACALINGLISTPRESENTFLAG3);
					pos-= FLENGTHPICSACALINGLISTPRESENTFLAG3;
					break;
				case 4:
					getValue(ppsHeader, &(headers->pps.picScalingListPresentFlag[i]), offset, pos, FLENGTHPICSACALINGLISTPRESENTFLAG4);
					pos-= FLENGTHPICSACALINGLISTPRESENTFLAG4;
					break;
				case 5:
					getValue(ppsHeader, &(headers->pps.picScalingListPresentFlag[i]), offset, pos, FLENGTHPICSACALINGLISTPRESENTFLAG5);
					pos-= FLENGTHPICSACALINGLISTPRESENTFLAG5;
					break;
				case 6:
					getValue(ppsHeader, &(headers->pps.picScalingListPresentFlag[i]), offset, pos, FLENGTHPICSACALINGLISTPRESENTFLAG6);
					pos-= FLENGTHPICSACALINGLISTPRESENTFLAG6;
					break;
				case 7:
					getValue(ppsHeader, &(headers->pps.picScalingListPresentFlag[i]), offset, pos, FLENGTHPICSACALINGLISTPRESENTFLAG7);
					pos-= FLENGTHPICSACALINGLISTPRESENTFLAG7;
					pos+= 8;
					offset++;
					break;
				}
			}
		}
		getValueInt16(ppsHeader, &(headers->pps.secondChromaQpIndexOffset), offset, pos, FLENGTHSECONDCHROMAQPINDEXOFFSET);
		pos-= FLENGTHSECONDCHROMAQPINDEXOFFSET;
		printf ("secondChromaQpIndexOffset %u\n", headers->pps.secondChromaQpIndexOffset);
		pos+= 8;
		offset++;
	}
	getValue(ppsHeader, &(headers->pps.rbspStopOneBit), offset, pos, FLENGTHRBSPSTOPONEBIT);
	pos-= FLENGTHRBSPSTOPONEBIT;	
	//TODO While(byte_aligned())
	getValue(ppsHeader, &(headers->pps.rbspAlignmentZeroBit), offset, pos, FLENGTHRBSPALIGNMENTZEROBIT);
	pos-= FLENGTHRBSPALIGNMENTZEROBIT;
	pos+= 8;
	offset++;
	if (offset != ppsLength)
		return false;
	printf ("rbspStopOneBit %u\nrbspAlignmentZeroBit %u\n", headers->pps.rbspStopOneBit, headers->pps.rbspAlignmentZeroBit);
	return true;
}

//SPS
bool spsToRbsp(unsigned char* spsHeader, uint32_t spsLength, nalHeader* headers) {
	uint32_t offset = 1;
	int pos = 7;
	//unsigned int picWidthLenght = 0;
	printf ("\n\n spsLength %u\n\n", spsLength);
	printf ("SPS \n");
	if ((spsLength <=0) || (spsLength > MAXLENGTHSPS) || (spsHeader == NULL))
		return false;
	printf ("SPS\n");
	getValue(spsHeader, &(headers->sps.profileIdc), offset, pos, FLENGTHPROFILEIDC);
	offset++;
	getValue(spsHeader, &(headers->sps.constraintSet0Flag), offset, pos, FLENGTHCONSTRAINTSET0FLAG);
	pos-=FLENGTHCONSTRAINTSET0FLAG;
	getValue(spsHeader, &(headers->sps.constraintSet1Flag), offset, pos, FLENGTHCONSTRAINTSET1FLAG);
	pos-=FLENGTHCONSTRAINTSET1FLAG;
	getValue(spsHeader, &(headers->sps.constraintSet2Flag), offset, pos, FLENGTHCONSTRAINTSET2FLAG);
	pos-=FLENGTHCONSTRAINTSET2FLAG;
	getValue(spsHeader, &(headers->sps.constraintSet3Flag), offset, pos, FLENGTHCONSTRAINTSET3FLAG);
	pos-=FLENGTHCONSTRAINTSET3FLAG;
	getValue(spsHeader, &(headers->sps.constraintSet4Flag), offset, pos, FLENGTHCONSTRAINTSET4FLAG);
	pos-=FLENGTHCONSTRAINTSET4FLAG;
	getValue(spsHeader, &(headers->sps.constraintSet5Flag), offset, pos, FLENGTHCONSTRAINTSET5FLAG);
	pos-=FLENGTHCONSTRAINTSET5FLAG;
	getValue(spsHeader, &(headers->sps.reservedZero2bits), offset, pos, FLENGTHRESERVEDZERO2BITS);
	pos-=FLENGTHRESERVEDZERO2BITS;
	pos+= 8;
	offset++;
	printf("profileIdc %u\nconstraintSet0Flag %u\nconstraintSet1Flag %u\nconstraintSet2Flag %u\nconstraintSet3Flag %u\nconstraintSet4Flag %u\nconstraintSet5Flag %u\nreservedZero2bits %u\n", headers->sps.profileIdc, headers->sps.constraintSet0Flag, headers->sps.constraintSet1Flag, headers->sps.constraintSet2Flag, headers->sps.constraintSet3Flag, headers->sps.constraintSet4Flag, headers->sps.constraintSet5Flag, headers->sps.reservedZero2bits);
	getValue(spsHeader, &(headers->sps.levelIdc), offset, pos, FLENGTHLEVELIDC);
	offset++;
	getValue(spsHeader, &(headers->sps.seqParameterSetId), offset, pos, FLENGTHSPSSEQPARAMETERSETID);
	pos-=FLENGTHSPSSEQPARAMETERSETID;
	if ((headers->sps.profileIdc == 100) || (headers->sps.profileIdc == 110) || (headers->sps.profileIdc == 122) || (headers->sps.profileIdc == 244) || (headers->sps.profileIdc == 44) || (headers->sps.profileIdc == 83) || (headers->sps.profileIdc == 86) || (headers->sps.profileIdc == 118) || (headers->sps.profileIdc == 128)) {
		getValue(spsHeader, &(headers->sps.chromaFormatIdc), offset, pos, FLENGTHCHROMAFORMATIDC);
		pos-=FLENGTHCHROMAFORMATIDC;		
		printf ("levelIdc %u\nseqParameterSetId %u\nchromaFormatIdc %u\n", headers->sps.levelIdc, headers->sps.seqParameterSetId, headers->sps.chromaFormatIdc);
		if (headers->sps.chromaFormatIdc == 3) {
			getValue(spsHeader, &(headers->sps.separateColourPlaneFlag), offset, pos, FLENGTHSEPARATECOLOURPLANEFLAG);
			pos-=FLENGTHSEPARATECOLOURPLANEFLAG;
		} else {
			headers->sps.separateColourPlaneFlag = 0;
		}
		getValue(spsHeader, &(headers->sps.bitDepthLumaMinus8), offset, pos, FLENGTHBITDEPTHLUMAMINUS8);
		pos-=FLENGTHBITDEPTHLUMAMINUS8;
		getValue(spsHeader, &(headers->sps.bitDepthChromaMinus8), offset, pos, FLENGTHBITDEPTHCHROMAMINUS8);
		pos-=FLENGTHBITDEPTHCHROMAMINUS8;
		getValue(spsHeader, &(headers->sps.qpprimeYZeroTransformBypassFlag), offset, pos, FLENGTHQPPRIMEYZEROTRANSFORMBYPASSFLAG);
		pos-=FLENGTHQPPRIMEYZEROTRANSFORMBYPASSFLAG;
		getValue(spsHeader, &(headers->sps.seqScalingMatrixPresentFlag), offset, pos, FLENGTHSEQSCALINGMATRIXPRESENTLAG);
		pos-=FLENGTHSEQSCALINGMATRIXPRESENTLAG;
		pos+=8;
		offset++;
		printf ("separateColourPlaneFlag %u\nbitDepthLumaMinus8 %u\nbitDepthChromaMinus8 %u\nqpprimeYZeroTransformBypassFlag %u\nseqScalingMatrixPresentFlag %u\n", headers->sps.separateColourPlaneFlag, headers->sps.bitDepthLumaMinus8, headers->sps.bitDepthChromaMinus8, headers->sps.qpprimeYZeroTransformBypassFlag, headers->sps.seqScalingMatrixPresentFlag);
		if (headers->sps.seqScalingMatrixPresentFlag) {
			printf ("Matrix\n");
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
		} else {
			printf ("no matrix\n");
		}
	}
	headers->sps.log2MaxFrameNumMinus4 = (spsHeader[offset] & FLOG2MAXFRAMENUMMINUS4) >> 7;
	headers->sps.picOrderCntType = (spsHeader[offset] & FPICORDERCNTTYPE) >> 4;
	printf ("log2MaxFrameNumMinus4 %u\npicOrderCntType %u\noffset %u\n", headers->sps.log2MaxFrameNumMinus4, headers->sps.picOrderCntType, offset);
	if (headers->sps.picOrderCntType == 0) {
		headers->sps.log2MaxPicOrderCntLsbMinus4 = ((spsHeader[offset] & FLOG2MAXPICORDERCNTLSBMINUSH) << 4) | ((spsHeader[offset+1] & FLOG2MAXPICORDERCNTLSBMINUSL) >> 4);
		printf ("log2MaxPicOrderCntLsbMinus4 %u\n", headers->sps.log2MaxPicOrderCntLsbMinus4);
		offset++;
	} else if (headers->sps.picOrderCntType == 1) {
		headers->sps.DeltaPicOrderAlwaysZeroFlag = (spsHeader[offset] & FDELTAPICORDERALWAYSZEROGFLAG) >> 3;
		headers->sps.offsetForNonRefPic = (spsHeader[offset] & FOFFSETFORNONREFPIC) >> 2;
		headers->sps.offsetForTopToBottomField = (spsHeader[offset] & FOFFSETFORTOPTOBOTTOMFIELD) >> 1;
		headers->sps.numRefFramesInPicOrderCntCycle = (spsHeader[offset] & FNUMREFFRAMESINOICORDERCNTCYCLE); //TODO: check this modif
		printf ("DeltaPicOrderAlwaysZeroFlag %u\noffsetForNonRefPic %u\noffsetForTopToBottomField %u\nnumRefFramesInPicOrderCntCycle %u\n", headers->sps.DeltaPicOrderAlwaysZeroFlag, headers->sps.offsetForNonRefPic, headers->sps.offsetForTopToBottomField, headers->sps.numRefFramesInPicOrderCntCycle);
		offset++;
		for (int i = 0; i < headers->sps.numRefFramesInPicOrderCntCycle; i++) {//TODO: check this modif
			headers->sps.offserForRefFrame[i] = spsHeader[offset];
			printf ("offserForRefFrame[%i] %u\n", i, headers->sps.offserForRefFrame[i]);
			offset++;
		}
	}

	headers->sps.maxNumRefFrames = ((spsHeader[offset] & FMAXNUMREFFRAMESH) << 1) | (spsHeader[offset+1] & FMAXNUMREFFRAMESL);
	offset++;
	headers->sps.gapsInFrameNumValueAlloweFlag = (spsHeader[offset] & FGAPSINFRAMENUMVALUEALLOWEDFLAG) >> 6;
	headers->sps.picWidthInMbsMinus1 = ((spsHeader[offset] & FPICWIDTHINMBSMINUS1H) * 128) + ((spsHeader[offset+1] & FPICWIDTHINMBSMINUS1L) >> 1) - 1;
	offset++;
	/*if ((spsHeader[offset+2] & FFRAMEMBSONLYFLAG) == 1) {*/
		headers->sps.picHeightInMapUnitsMinus1 = ((spsHeader[offset] & FPICHEIGHTINMAPUNITSMINUS1H) * 1024) + ((spsHeader[offset+1] & FPICHEIGHTINMAPUNITSMINUS1M) * 4) + ((spsHeader[offset+2] & FPICHEIGHTINMAPUNITSMINUS1L) >> 6) - 1;
		/*picWidthLenght = 11;
	} else { 
		headers->sps.picHeightInMapUnitsMinus1 = ((spsHeader[offset] & FPICHEIGHTINMAPUNITSMINUS1H) * 4096) + ((spsHeader[offset+1] & FPICHEIGHTINMAPUNITSMINUS1M) * 16) + ((spsHeader[offset+2] & FPICHEIGHTINMAPUNITSMINUS1L) >> 4) - 1;
		picWidthLenght = 13;
	}*/
	offset += 2;
	headers->sps.framMbsOnlyFlag = (spsHeader[offset] & FFRAMEMBSONLYFLAG) >> 5;
	printf ("maxNumRefFrames %u\ngapsInFrameNumValueAlloweFlag %u\npicWidthInMbsMinus1 %u\npicHeightInMapUnitsMinus1 %u\nframMbsOnlyFlag %u\n", headers->sps.maxNumRefFrames, headers->sps.gapsInFrameNumValueAlloweFlag, headers->sps.picWidthInMbsMinus1, headers->sps.picHeightInMapUnitsMinus1, headers->sps.framMbsOnlyFlag);
	if (!headers->sps.framMbsOnlyFlag) {
		headers->sps.mbAdaptiveFrameFieldFlag = (spsHeader[offset] & FMBADAPTIVEFRAMEFIELDFLAG) >> 4;
		printf ("mbAdaptiveFrameFieldFlag %u\n", headers->sps.mbAdaptiveFrameFieldFlag);
	}
	headers->sps.direct8x8InferenceFlag = (spsHeader[offset] & FDIRECT8X8INFERENCEFLAG) >> 4;
	headers->sps.frameCroppinFlag = (spsHeader[offset] & FFRAMECROPPINGFLAG) >> 3;
	printf ("direct8x8InferenceFlag %u\nframeCroppinFlag %u\n", headers->sps.direct8x8InferenceFlag, headers->sps.frameCroppinFlag);
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
	headers->sps.vuiParametersPresentFlag = (spsHeader[offset] & FVUIPARAMETERSPRESENTLAG) >> 6;
	printf ("frameCroppinLeftOffset %u\nframeCroppinRightOffset %u\nframeCroppinTopOffset %u\nframeCroppinBottomOffset %u\nvuiParametersPresentFlag %u\n", headers->sps.frameCroppinLeftOffset, headers->sps.frameCroppinRightOffset, headers->sps.frameCroppinTopOffset, headers->sps.frameCroppinBottomOffset, headers->sps.vuiParametersPresentFlag);
	if (headers->sps.vuiParametersPresentFlag) {
		headers->sps.aspectRatioInfoPresentFlag = (spsHeader[offset] & FASPECTRATIOINFOPRESENTLAG) >> 1;
		printf ("aspectRatioInfoPresentFlag %u\n", headers->sps.aspectRatioInfoPresentFlag);
		if (headers->sps.aspectRatioInfoPresentFlag) {
			headers->sps.aspectRatioIdc = ((spsHeader[offset] & FASPECTRATIOIDCH) << 7) | ((spsHeader[offset+1] & FASPECTRATIOIDCL) >> 1);
			printf ("aspectRatioIdc %u\n", headers->sps.aspectRatioIdc);
			offset++;
			if (headers->sps.aspectRatioIdc == EXTENDESAR) {
				headers->sps.sarWidth = ((spsHeader[offset] & FSARWIDTHH) * 32768) + ((spsHeader[offset+1] & FSARWIDTHM) * 128) + ((spsHeader[offset+2] & FSARWIDTHL) >> 1);
				offset+= 2;
				headers->sps.sarHeight = ((spsHeader[offset] & FSARHEIGHTH) * 32768) + ((spsHeader[offset+1] & FSARHEIGHTM) * 128) + ((spsHeader[offset+2] & FSARHEIGHTL) >> 1);
				printf ("sarWidth %u\nsarHeight %u\n", headers->sps.sarWidth, headers->sps.sarHeight);
				offset+= 2;
			}
		}
		headers->sps.overscanInfoPresentFlag = (spsHeader[offset] & FOVERSCANINFOPRESENTFLAG);
		printf ("overscanInfoPresentFlag %u\n", headers->sps.overscanInfoPresentFlag);
		offset++;
		if (headers->sps.overscanInfoPresentFlag) {
			headers->sps.overscanAppropriateFlag = (spsHeader[offset] & FOVERSCANAPPROPIATEFLAG) >> 7;
			printf ("overscanAppropriateFlag %u\n", headers->sps.overscanAppropriateFlag);
		}
		headers->sps.videoSignalTypePresentFlag = (spsHeader[offset] & FVIDEOSIGNALTYPEPRESENTLAG) >> 7;
		printf ("videoSignalTypePresentFlag %u\n", headers->sps.videoSignalTypePresentFlag);
		if (headers->sps.videoSignalTypePresentFlag) {
			headers->sps.videoFormat = (spsHeader[offset] & FVIDEOFORMAT) >> 4;
			headers->sps.videoFullRangeFlag = (spsHeader[offset] & FVIDEOFULLRANGEFLAG) >> 3;
			headers->sps.colourDescriptionPresentFlag = (spsHeader[offset] & FCOLOURDESCRIPTIONPRESENTLAG) >> 2;
			printf ("videoFormat %u\nvideoFullRangeFlag %u\ncolourDescriptionPresentFlag %u\n", headers->sps.videoFormat, headers->sps.videoFullRangeFlag, headers->sps.colourDescriptionPresentFlag);
			if (headers->sps.colourDescriptionPresentFlag) {
				headers->sps.colourPrimaries = ((spsHeader[offset] & FCOLOURPRIMARIESH) << 6) | ((spsHeader[offset+1] & FCOLOURPRIMARIESL) >> 2);
				offset++;
				headers->sps.transferCharacteristics = ((spsHeader[offset] & FTRANSFERCHARACTERISTICSH) << 6) | ((spsHeader[offset+1] & FTRANSFERCHARACTERISTICSL) >> 2);
				offset++;
				headers->sps.matrixCoefficients = ((spsHeader[offset] & FMATRIXCOEFFICIENTSH) << 6) | ((spsHeader[offset+1] & FMATRIXCOEFFICIENTSL) >> 2);
				printf ("colourPrimaries %u\ntransferCharacteristics %u\nmatrixCoefficients %u\n", headers->sps.colourPrimaries, headers->sps.transferCharacteristics, headers->sps.matrixCoefficients);
				offset++;
			}
		}
		headers->sps.chromaLocInfoPresentFlag = (spsHeader[offset] & FCHROMALOCINFOPRESENTFLAG) >> 6;
		printf ("chromaLocInfoPresentFlag %u\n", headers->sps.chromaLocInfoPresentFlag);
		if (headers->sps.chromaLocInfoPresentFlag) {
			headers->sps.chromaSampleLocTypeTopField = (spsHeader[offset] & FCHROMASAMPLELOCTYPETOPFIELD) >> 2;
			headers->sps.chromaSampleLocTypeBottomField = ((spsHeader[offset] & FCHROMASAMPLELOCTYPEBOTTOMFIELDH) << 2) | ((spsHeader[offset+1] & FCHROMASAMPLELOCTYPEBOTTOMFIELDL) >> 6);
			printf ("chromaSampleLocTypeTopField %u\nchromaSampleLocTypeBottomField %u\n", headers->sps.chromaSampleLocTypeTopField, headers->sps.chromaSampleLocTypeBottomField);
			offset++;
		}
		headers->sps.timingInfoPresentFlag = (spsHeader[offset] & FTIMINGINFOPRESENTLAG) >> 5;
		printf ("timingInfoPresentFlag %u\n", headers->sps.timingInfoPresentFlag);
		if (headers->sps.timingInfoPresentFlag) {
			headers->sps.numUnitsInTick = ((spsHeader[offset] & FNUMUNITSINTICKH) * 134217728) + ((spsHeader[offset+1] & FNUMUNITSINTICKM) * 524288) + ((spsHeader[offset+2] & FNUMUNITSINTICKM) * 2048) + ((spsHeader[offset+3] & FNUMUNITSINTICKM) * 8) + ((spsHeader[offset+4] & FNUMUNITSINTICKL) >> 5);
			offset+= 4;
			headers->sps.timeScale = ((spsHeader[offset] & FTIMESCALEH) * 134217728) + ((spsHeader[offset+1] & FTIMESCALEM) * 524288) + ((spsHeader[offset+2] & FTIMESCALEM) * 2048) + ((spsHeader[offset+3] & FTIMESCALEM) * 8) + ((spsHeader[offset+4] & FTIMESCALEL) >> 5);
			offset+= 4;
			headers->sps.fixedFrameRateFlag = (spsHeader[offset] & FFIXEDFRAMERATEFLAG) >> 4;
			printf ("numUnitsInTick %u\ntimeScale %u\nfixedFrameRateFlag %u\n", headers->sps.numUnitsInTick, headers->sps.timeScale, headers->sps.fixedFrameRateFlag);
		}
		headers->sps.nalHrdParametersPresentFlag = (spsHeader[offset] & FNALHRDPARAMETERSPRESENTLAG) >> 3;
		printf ("nalHrdParametersPresentFlag %u\n", headers->sps.nalHrdParametersPresentFlag);
		if (headers->sps.nalHrdParametersPresentFlag) {
			int index = 0;
			headers->sps.nalcpbCntMinus1 = (((spsHeader[offset] & FNALCPBCNTMINUS1H) << 2) | ((spsHeader[offset+1] & FNALCPBCNTMINUS1L) >> 6)) - 1;
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
		printf ("vclHrdParametersPresentFlag %u\n", headers->sps.vclHrdParametersPresentFlag);
		if (headers->sps.vclHrdParametersPresentFlag) {
			int index = 0, indexOffset = 0;
			bool condition = false;//TODO leer la documentacion
			if (condition) {
				headers->sps.vclcpbCntMinus1 = (((spsHeader[offset] & FVCLCPBCNTMINUS1H) << 3) | ((spsHeader[offset+1] & FVCLCPBCNTMINUS1L) >> 5)) - 1;
			offset++;
			headers->sps.vclbitRateScale = (spsHeader[offset] & FVCLBITRATESCALE) >> 1;
			headers->sps.vclcpbSizeScale = ((spsHeader[offset] & FVCLCPBSIZESCALEH) << 3) | ((spsHeader[offset+1] & FVCLCPBSIZESCALEL) >> 5);
			offset++;
			indexOffset = 3;
			} else {
				headers->sps.vclcpbCntMinus1 = ((spsHeader[offset] & FVCLCPBCNTMINUS1) >> 1)  - 1;
				headers->sps.vclbitRateScale = ((spsHeader[offset] & FVCLBITRATESCALEH) << 3) | ((spsHeader[offset + 1] & FVCLBITRATESCALEL) >> 5);
				offset++;
				headers->sps.vclcpbSizeScale = ((spsHeader[offset] & FVCLCPBSIZESCALE) >> 1);	
				indexOffset = 7;			
			}			
			printf ("vclcpbCntMinus1 %u\nvclbitRateScale %u\nvclcpbSizeScale %u\n", headers->sps.vclcpbCntMinus1, headers->sps.vclbitRateScale, headers->sps.vclcpbSizeScale);
			
			for (int i = 0; i < headers->sps.vclcpbCntMinus1; i++) {
				index = ((i+indexOffset) % 8);
				switch (index) {
				case 0:
					headers->sps.vclbitRateValueMinus1[i] = ((spsHeader[offset] & FBITRATEVALUEMINUS1H0) * 16777216) + ((spsHeader[offset+1] & FBITRATEVALUEMINUS1M) * 65536) + ((spsHeader[offset+2] & FBITRATEVALUEMINUS1M) * 256) + ((spsHeader[offset+3] & FBITRATEVALUEMINUS1L0)) - 1;
					offset+=4;
					headers->sps.vclcpbSizeValueMinus1[i] = ((spsHeader[offset] & FCPBSIZEVALUEMINUS1H0) * 16777216) + ((spsHeader[offset+1] & FCPBSIZEVALUEMINUS1M) * 65536) + ((spsHeader[offset+2] & FCPBSIZEVALUEMINUS1M) * 256) + ((spsHeader[offset+3] & FCPBSIZEVALUEMINUS1L0)) - 1;
					offset+=4;
					headers->sps.vclcbrFlag = (spsHeader[offset] & FCBRFLAG0) >> 7;
					break;
				case 1:
					headers->sps.vclbitRateValueMinus1[i] = ((spsHeader[offset] & FBITRATEVALUEMINUS1H1) * 33554432) + ((spsHeader[offset+1] & FBITRATEVALUEMINUS1M) * 131072) + ((spsHeader[offset+2] & FBITRATEVALUEMINUS1M) * 512) + ((spsHeader[offset+3] & FBITRATEVALUEMINUS1M) * 2) + ((spsHeader[offset+4] & FBITRATEVALUEMINUS1L1) >> 7) - 1;
					offset+=4;
					headers->sps.vclcpbSizeValueMinus1[i] = ((spsHeader[offset] & FCPBSIZEVALUEMINUS1H1) * 33554432) + ((spsHeader[offset+1] & FCPBSIZEVALUEMINUS1M) * 131072) + ((spsHeader[offset+2] & FCPBSIZEVALUEMINUS1M) * 512) + ((spsHeader[offset+3] & FCPBSIZEVALUEMINUS1M) * 2) + ((spsHeader[offset+4] & FCPBSIZEVALUEMINUS1L1) >> 7) - 1;
					offset+=4;
					headers->sps.vclcbrFlag = (spsHeader[offset] & FCBRFLAG1) >> 6;
					break;
				case 2:
					headers->sps.vclbitRateValueMinus1[i] = ((spsHeader[offset] & FBITRATEVALUEMINUS1H2) * 67108864) + ((spsHeader[offset+1] & FBITRATEVALUEMINUS1M) * 262144) + ((spsHeader[offset+2] & FBITRATEVALUEMINUS1M) * 1024) + ((spsHeader[offset+3] & FBITRATEVALUEMINUS1M) * 4) + ((spsHeader[offset+4] & FBITRATEVALUEMINUS1L2) >> 6) - 1;
					offset+=4;
					headers->sps.vclcpbSizeValueMinus1[i] = ((spsHeader[offset] & FCPBSIZEVALUEMINUS1H2) * 67108864) + ((spsHeader[offset+1] & FCPBSIZEVALUEMINUS1M) * 262144) + ((spsHeader[offset+2] & FCPBSIZEVALUEMINUS1M) * 1024) + ((spsHeader[offset+3] & FCPBSIZEVALUEMINUS1M) * 4) + ((spsHeader[offset+4] & FCPBSIZEVALUEMINUS1L2) >> 6) - 1;
					offset+=4;
					headers->sps.vclcbrFlag = (spsHeader[offset] & FCBRFLAG2) >> 5;
					break;
				case 3:
					headers->sps.vclbitRateValueMinus1[i] = ((spsHeader[offset] & FBITRATEVALUEMINUS1H3) * 134217728) + ((spsHeader[offset+1] & FBITRATEVALUEMINUS1M) * 524288) + ((spsHeader[offset+2] & FBITRATEVALUEMINUS1M) * 2048) + ((spsHeader[offset+3] & FBITRATEVALUEMINUS1M) * 8) + ((spsHeader[offset+4] & FBITRATEVALUEMINUS1L3) >> 5) - 1;
					offset+=4;
					headers->sps.vclcpbSizeValueMinus1[i] = ((spsHeader[offset] & FCPBSIZEVALUEMINUS1H3) * 134217728) + ((spsHeader[offset+1] & FCPBSIZEVALUEMINUS1M) * 524288) + ((spsHeader[offset+2] & FCPBSIZEVALUEMINUS1M) * 2048) + ((spsHeader[offset+3] & FCPBSIZEVALUEMINUS1M) * 8) + ((spsHeader[offset+4] & FCPBSIZEVALUEMINUS1L3) >> 5) - 1;
					offset+=4;
					headers->sps.vclcbrFlag = (spsHeader[offset] & FCBRFLAG3) >> 4;
					break;
				case 4:
					headers->sps.vclbitRateValueMinus1[i] = ((spsHeader[offset] & FBITRATEVALUEMINUS1H4) * 268435456) + ((spsHeader[offset+1] & FBITRATEVALUEMINUS1M) * 1048576) + ((spsHeader[offset+2] & FBITRATEVALUEMINUS1M) * 4096) + ((spsHeader[offset+3] & FBITRATEVALUEMINUS1M) * 16) + ((spsHeader[offset+4] & FBITRATEVALUEMINUS1L4) >> 4) - 1;
					offset+=4;
					headers->sps.vclcpbSizeValueMinus1[i] = ((spsHeader[offset] & FCPBSIZEVALUEMINUS1H4) * 268435456) + ((spsHeader[offset+1] & FCPBSIZEVALUEMINUS1M) * 1048576) + ((spsHeader[offset+2] & FCPBSIZEVALUEMINUS1M) * 4096) + ((spsHeader[offset+3] & FCPBSIZEVALUEMINUS1M) * 16) + ((spsHeader[offset+4] & FCPBSIZEVALUEMINUS1L4) >> 4) - 1;
					offset+=4;
					headers->sps.vclcbrFlag = (spsHeader[offset] & FCBRFLAG4) >> 3;
					break;
				case 5:
					headers->sps.vclbitRateValueMinus1[i] = ((spsHeader[offset] & FBITRATEVALUEMINUS1H5) * 536870912) + ((spsHeader[offset+1] & FBITRATEVALUEMINUS1M) * 2097152) + ((spsHeader[offset+2] & FBITRATEVALUEMINUS1M) * 8192) + ((spsHeader[offset+3] & FBITRATEVALUEMINUS1M) * 32) + ((spsHeader[offset+4] & FBITRATEVALUEMINUS1L5) >> 3) - 1;
					offset+=4;
					headers->sps.vclcpbSizeValueMinus1[i] = ((spsHeader[offset] & FCPBSIZEVALUEMINUS1H5) * 536870912) + ((spsHeader[offset+1] & FCPBSIZEVALUEMINUS1M) * 2097152) + ((spsHeader[offset+2] & FCPBSIZEVALUEMINUS1M) * 8192) + ((spsHeader[offset+3] & FCPBSIZEVALUEMINUS1M) * 32) + ((spsHeader[offset+4] & FCPBSIZEVALUEMINUS1L5) >> 3) - 1;
					offset+=4;
					headers->sps.vclcbrFlag = (spsHeader[offset] & FCBRFLAG5) >> 2;
					break;
				case 6:
					headers->sps.vclbitRateValueMinus1[i] = ((spsHeader[offset] & FBITRATEVALUEMINUS1H5) * 1073741824) + ((spsHeader[offset+1] & FBITRATEVALUEMINUS1M) * 2097152) + ((spsHeader[offset+2] & FBITRATEVALUEMINUS1M) * 16384) + ((spsHeader[offset+3] & FBITRATEVALUEMINUS1M) * 64) + ((spsHeader[offset+4] & FBITRATEVALUEMINUS1L5) >> 2) - 1;
					offset+=4;
					headers->sps.vclcpbSizeValueMinus1[i] = ((spsHeader[offset] & FCPBSIZEVALUEMINUS1H5) * 1073741824) + ((spsHeader[offset+1] & FCPBSIZEVALUEMINUS1M) * 2097152) + ((spsHeader[offset+2] & FCPBSIZEVALUEMINUS1M) * 16384) + ((spsHeader[offset+3] & FCPBSIZEVALUEMINUS1M) * 64) + ((spsHeader[offset+4] & FCPBSIZEVALUEMINUS1L5) >> 2) - 1;
					offset+=4;
					headers->sps.vclcbrFlag = (spsHeader[offset] & FCBRFLAG6) >> 1;
					break;
				case 7:
					headers->sps.vclbitRateValueMinus1[i] = ((spsHeader[offset] & FBITRATEVALUEMINUS1H5) * 2147483648) + ((spsHeader[offset+1] & FBITRATEVALUEMINUS1M) * 4194304) + ((spsHeader[offset+2] & FBITRATEVALUEMINUS1M) * 32768) + ((spsHeader[offset+3] & FBITRATEVALUEMINUS1M) * 128) + ((spsHeader[offset+4] & FBITRATEVALUEMINUS1L5) >> 1) - 1;
					offset+=4;
					headers->sps.vclcpbSizeValueMinus1[i] = ((spsHeader[offset] & FCPBSIZEVALUEMINUS1H5) * 2147483648) + ((spsHeader[offset+1] & FCPBSIZEVALUEMINUS1M) * 4194304) + ((spsHeader[offset+2] & FCPBSIZEVALUEMINUS1M) * 32768) + ((spsHeader[offset+3] & FCPBSIZEVALUEMINUS1M) * 128) + ((spsHeader[offset+4] & FCPBSIZEVALUEMINUS1L5) >> 1) - 1;
					offset+=4;
					headers->sps.vclcbrFlag = (spsHeader[offset] & FCBRFLAG7);
					offset++;
					break;
				}
			}
			if (headers->sps.vclcpbCntMinus1 == 0) {
					headers->sps.vclbitRateValueMinus1[0] = (spsHeader[offset] & FBITRATEVALUEMINUS1H7) - 1;
					offset++;
					headers->sps.vclcpbSizeValueMinus1[0] = ((spsHeader[offset] & FCPBSIZEVALUEMINUS1L1) >> 7) - 1;
					headers->sps.vclcbrFlag = (spsHeader[offset] & FCBRFLAG1) >> 6;
					index = 2;
					printf ("vclbitRateValueMinus1 %u\nvclcpbSizeValueMinus1 %u\nvclcbrFlag %u\n", headers->sps.vclbitRateValueMinus1[0], headers->sps.vclcpbSizeValueMinus1[0], headers->sps.vclcbrFlag);
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
			printf("vclinitialCpbRemovalDelayLengthMinus1 %u\nvclcpbRemovalDelayLengthMinus1 %u\nvcldpbOutputDelayLengthMinus1 %u\nvcltimeOffsetLength %u\n", headers->sps.vclinitialCpbRemovalDelayLengthMinus1, headers->sps.vclcpbRemovalDelayLengthMinus1, headers->sps.vcldpbOutputDelayLengthMinus1, headers->sps.vcltimeOffsetLength);
			
		}		
		if (headers->sps.nalHrdParametersPresentFlag || headers->sps.vclHrdParametersPresentFlag) {
			headers->sps.lowDelayHrdFlag = (spsHeader[offset] & FLOWDELAYHRDFLAG) >> 1;
			headers->sps.picStructPresentFlag = (spsHeader[offset] & FPICSTRUCTPRESENTLAG0);
			printf ("lowDelayHrdFlag %u\n", headers->sps.lowDelayHrdFlag);
			offset++;
			if (offset == spsLength)
				headers->sps.bitstreamRestrictionFlag = 0;
			else {
				headers->sps.bitstreamRestrictionFlag = (spsHeader[offset] & FBITSTREAMRESTRICTIONFLAG7) >> 7;
				if (headers->sps.bitstreamRestrictionFlag) {
					headers->sps.montionVectorsOverPicBoundariesFlag = (spsHeader[offset] & FMONTIONVECTORSOVERPICBOUNDARIESFLAG6) >> 6;
					headers->sps.maxBytesPerPicDenom = (spsHeader[offset] & FMAXBYTESPERPICDENOM5) >> 5;
					headers->sps.maxBitsPerMbDenom = (spsHeader[offset] & FMAXBITSPERMBDENOM4) >> 4;
					headers->sps.log2MaxMvLengthHorizontal = ((spsHeader[offset] & FLOG2MAXMVLENGTHHORIZONTALH3) << 3) | ((spsHeader[offset+1] & FLOG2MAXMVLENGTHHORIZONTALL75) >> 5);
					offset++;
					headers->sps.log2MaxMvLengthVertical = ((spsHeader[offset] & FLOG2MAXMVLENGTHVERTICALH4) << 2) | ((spsHeader[offset+1] & FLOG2MAXMVLENGTHVERTICALL76) >> 6);
					offset++;
					headers->sps.maxNumReorderFrames = (spsHeader[offset] & FMAXNUMREODERFRAMES5) >> 5;
					headers->sps.maxDecFrameBuffering = (spsHeader[offset] & FMAXEDCFRAMEBUFFERING4);
					offset++;
					headers->sps.rbspStopBit = (spsHeader[offset] & FRBSPSTOPBIT7) >> 7;
				}
			}
		} else {
			headers->sps.picStructPresentFlag = (spsHeader[offset] & FPICSTRUCTPRESENTLAG1) >> 1;
			headers->sps.bitstreamRestrictionFlag = (spsHeader[offset] & FBITSTREAMRESTRICTIONFLAG0);
			offset++;
			printf ("picStructPresentFlag %u\noffset %u\nspsLength %u\n", headers->sps.picStructPresentFlag, offset, spsLength);
			if (headers->sps.bitstreamRestrictionFlag) {
				headers->sps.montionVectorsOverPicBoundariesFlag = (spsHeader[offset] & FMONTIONVECTORSOVERPICBOUNDARIESFLAG7) >> 7;
				headers->sps.maxBytesPerPicDenom = (spsHeader[offset] & FMAXBYTESPERPICDENOM6) >> 6;
				headers->sps.maxBitsPerMbDenom = (spsHeader[offset] & FMAXBITSPERMBDENOM5) >> 5;
				headers->sps.log2MaxMvLengthHorizontal = ((spsHeader[offset] & FLOG2MAXMVLENGTHHORIZONTALH4) << 2) | ((spsHeader[offset+1] & FLOG2MAXMVLENGTHHORIZONTALL7) >> 6);
				offset++;
				headers->sps.log2MaxMvLengthVertical = ((spsHeader[offset] & FLOG2MAXMVLENGTHVERTICALH5) << 1) | ((spsHeader[offset+1] & FLOG2MAXMVLENGTHVERTICALL7) >> 7);
				offset++;
				headers->sps.maxNumReorderFrames = (spsHeader[offset] & FMAXNUMREODERFRAMES6) >> 6;
				headers->sps.maxDecFrameBuffering = (spsHeader[offset] & FMAXEDCFRAMEBUFFERING5) >> 1;
				headers->sps.rbspStopBit = (spsHeader[offset] & FRBSPSTOPBIT0);
			}
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
