#include "../include/i2nalparser.h"

bool ppsToRbsp(unsigned char* ppsHeader, uint32_t ppsLength, nalHeader* headers) {
	int offset = 0;
	if ((ppsLength <=0) || (ppsLength > MAXLENGTHPPS) || (ppsHeader == NULL))
		return false;
	header->pps.picParameterSetId = (ppsHeader[offset] & FPICPARAMETERSETID) >> 7;
	header->pps.seqParameterSetId = (ppsHeader[offset] & FSEQPARAMETERSETID) >> 6;
	header->pps.entropyCondingModeFlag = (ppsHeader[offset] & FENTROPYCODINGMODEFLAG) >> 5;
	header->pps.bottomFieldPicOrderInFramePresentFlag = (ppsHeader[offset] & FBOTTOMFIELDPICORDERINFRAMEPRESENTFLAG) >> 4;
	header->pps.numSliceGroupsMinus1 = (ppsHeader[offset] & FNUMSLICEGROUPMINUS1) >> 3;
	if (header->pps.numSliceGroupsMinus1 > 0) {//TODO check this!
		header->pps.sliceGroupMapType = (ppsHeader[0] & FSLICEGROUPSMAPTYPE);
		offset++;
		if (header->pps.sliceGroupMapType == 0) {
			for (int iGroup = 0; iGroup <= header->pps.numSliceGroupsMinus1; iGroup++) {
				header->pps.runLengthMinus1[iGroup] == ppsHeader[offset];
				offset++;
			}
		} else if (header->pps.sliceGroupMapType == 2) {
			for (int iGroup = 0; iGroup <= header->pps.numSliceGroupsMinus1; iGroup++) {
				header->pps.topLef[iGroup] = (ppsHeader[offset] & FTOPLEFT) >> 4;
				header->pps.bottomRight[iGroup] = (ppsHeader[offset] & FBOTTOMRIGHT);
				offset++;
			} 
		} else if ((header->pps.sliceGroupMapType > 2) && (header->pps.sliceGroupMapType < 6)) {
			header->pps.sliceGroupChangeDirectionFlag = (ppsHeader[offset] & FSLICEGROUPCHANGEDIRECTIONFLAG) >> 7;
			header->pps.sliceGroupChangeRateMinus1 = (ppsHeader[offset] & FSLICEGROUPCHANGERATEMINUS1);
			offset++;			
		} else if (header->pps.sliceGroupMapType == 6) {
			header->pps.picSizeInMapUnitsMinus1 = ppsHeader[offset];
			offset++;
			for (int i = 0; i <= header->pps.picSizeInMapUnitsMinus1; i++) {
				header->pps.sliceGroupId[i] == ppsHeader[offset];
				offset++;
			}
			
		}
		
	}

}
bool spsToRbsp(unsigned char* spsHeader, uint32_t spsLength, nalHeader* headers);
uint32_t getWidth(nalHeader headers);
uint32_t getHeight(nalHeader headers);
