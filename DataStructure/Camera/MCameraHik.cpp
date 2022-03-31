#include "MCameraHik.h"

MCameraHik::MCameraHik() 
    : MCameraBase(){

}

MCameraHik::~MCameraHik(){	
	if (handle != NULL){
		MV_CC_DestroyHandle(handle);
		handle = NULL;
	}
}

MCameraHik::MCameraHik(MCameraHik &&rhs)
	:stDeviceList{ rhs.stDeviceList }, handle{ rhs.handle },image_mode_{ rhs.image_mode_ }
{
	rhs.stDeviceList = { 0, nullptr };
	rhs.handle = nullptr;
    rhs.image_mode_ = 0;
}

MCameraHik& MCameraHik::operator=(MCameraHik &&rhs){
	if (this == &rhs)
		return *this;
	stDeviceList = rhs.stDeviceList;
	rhs.stDeviceList = { 0, nullptr };
	delete handle;
	handle = rhs.handle;
	rhs.handle = nullptr;
	image_mode_ = rhs.image_mode_;
	rhs.image_mode_ = 0;
    return *this;
}

void MCameraHik::init (){
    int nRet = MV_OK;
    handle = nullptr;
    // ch:枚举设备 | en:Enum device
    memset(&stDeviceList, 0, sizeof(MV_CC_DEVICE_INFO_LIST));
    nRet = MV_CC_EnumDevices(MV_GIGE_DEVICE | MV_USB_DEVICE, &stDeviceList);
    if (MV_OK != nRet)
    {
		//printf("Enum Devices fail! nRet [0x%x]\n", nRet);
		//break;
    }

    if (stDeviceList.nDeviceNum > 0)
    {
        for (unsigned int i = 0; i < stDeviceList.nDeviceNum; i++)
        {
            //printf("[device %d]:\n", i);
            //MV_CC_DEVICE_INFO* pDeviceInfo = stDeviceList.pDeviceInfo[i];
            //if (NULL == pDeviceInfo)
            //{
            //    break;
            //}
            //PrintDeviceInfo(pDeviceInfo);
        }
    }
    else
    {
        //printf("Find No Devices!\n");
        //break;
    }

    //printf("Please Input camera index(0-%d):", stDeviceList.nDeviceNum-1);
    //unsigned int nIndex = 0;
    //scanf_s("%d", &nIndex);

    //if (nIndex >= stDeviceList.nDeviceNum)
    //{
    //    printf("Input error!\n");
    //    break;
    //}

    // ch:选择设备并创建句柄 | en:Select device and create handle
    nRet = MV_CC_CreateHandle(&handle, stDeviceList.pDeviceInfo[0]);
    if (MV_OK != nRet)
    {
        //printf("Create Handle fail! nRet [0x%x]\n", nRet);
        //break;
    }
}

void MCameraHik::open(){
	// ch:打开设备 | en:Open device
	int nRet = MV_CC_OpenDevice(handle);
	if (MV_OK != nRet)
	{
		//printf("Open Device fail! nRet [0x%x]\n", nRet);
		//break;
	}

	// ch:探测网络最佳包大小(只对GigE相机有效) | en:Detection network optimal package size(It only works for the GigE camera)
	if (stDeviceList.pDeviceInfo[0]->nTLayerType == MV_GIGE_DEVICE)
	{
		int nPacketSize = MV_CC_GetOptimalPacketSize(handle);
		if (nPacketSize > 0)
		{
			nRet = MV_CC_SetIntValue(handle, "GevSCPSPacketSize", nPacketSize);
			if (nRet != MV_OK)
			{
				//printf("Warning: Set Packet Size fail nRet [0x%x]!", nRet);
			}
		}
		else
		{
			//printf("Warning: Get Packet Size fail nRet [0x%x]!", nPacketSize);
		}
	}
}

bool MCameraHik::is_open() {
	return true;
}

bool MCameraHik::snap(HalconCpp::HObject& h_object_) {
	try {
		int nRet = MV_OK;
		MV_FRAME_OUT stOutFrame = { 0 };
		// ch:开始取流 | en:Start grab image
		nRet = MV_CC_StartGrabbing(handle);
		if (MV_OK != nRet)
		{
			//printf("Start Grabbing fail! nRet [0x%x]\n", nRet);
			//break;
			return false;
		}

		nRet = MV_CC_GetImageBuffer(handle, &stOutFrame, 1000);
		if (nRet == MV_OK)
		{
			//printf("Get Image Buffer: Width[%d], Height[%d], FrameNum[%d]\n",
			//	stOutFrame.stFrameInfo.nWidth, stOutFrame.stFrameInfo.nHeight, stOutFrame.stFrameInfo.nFrameNum);
			unsigned short img_width = stOutFrame.stFrameInfo.nWidth;
			unsigned short img_height = stOutFrame.stFrameInfo.nHeight;
			unsigned char* p_buf = stOutFrame.pBufAddr;
			//img_ = QImage((const uchar*)p_buf, img_width, img_height, QImage::Format_Grayscale8);
			HalconCpp::GenImage1(&h_object_, "byte", img_width, img_height, (Hlong)p_buf);
            switch(image_mode_){
                case 0:
                    HalconCpp::RotateImage(h_object_, &h_object_, 0, "constant");
                break;
                case 1:
                    HalconCpp::RotateImage(h_object_, &h_object_, 90, "constant");
                break;
                case 2:
                    HalconCpp::RotateImage(h_object_, &h_object_, 180, "constant");
                break;
                case 3:
                    HalconCpp::RotateImage(h_object_, &h_object_, 270, "constant");
                break;
                case 4:
                    HalconCpp::MirrorImage(h_object_, &h_object_, "row");
                break;
                case 5:
                    HalconCpp::MirrorImage(h_object_, &h_object_, "column");
                break;
                default:
                break;

            }
			nRet = MV_CC_FreeImageBuffer(handle, &stOutFrame);
			if (nRet != MV_OK)
			{
				//printf("Free Image Buffer fail! nRet [0x%x]\n", nRet);
				return false;
			}
		}
		else
		{
			//printf("Get Image fail! nRet [0x%x]\n", nRet);
			return false;
		}

		// ch:停止取流 | en:Stop grab image
		nRet = MV_CC_StopGrabbing(handle);
		if (MV_OK != nRet)
		{
			//printf("Stop Grabbing fail! nRet [0x%x]\n", nRet);
			//break;
			return false;
		}
		return true;
	}
	catch (...) {
		return false;
	}
}

void MCameraHik::close() {
	// ch:关闭设备 | Close device
	int nRet = MV_CC_CloseDevice(handle);
	if (MV_OK != nRet)
	{
		//printf("ClosDevice fail! nRet [0x%x]\n", nRet);
		//break;
	}

	// ch:销毁句柄 | Destroy handle
	nRet = MV_CC_DestroyHandle(handle);
	if (MV_OK != nRet)
	{
		//printf("Destroy Handle fail! nRet [0x%x]\n", nRet);
		//break;
	}
}

void MCameraHik::set_trigger_mode(bool trigger_mode) {
	// ch:设置触发模式为off | en:Set trigger mode as off
	int nRet = MV_CC_SetEnumValue(handle, "TriggerMode", trigger_mode);
	if (MV_OK != nRet)
	{
		//printf("Set Trigger Mode fail! nRet [0x%x]\n", nRet);
		//break;
	}
}

void MCameraHik::set_exposure(double exposure){
	int nRet = MV_CC_SetEnumValue(handle, "ExposureMode", MV_EXPOSURE_MODE_TIMED);
	if (MV_OK != nRet)
	{
		//return nRet;
	}
	MV_CC_SetEnumValue(handle, "ExposureAuto", MV_EXPOSURE_AUTO_MODE_OFF);
	MV_CC_SetFloatValue(handle, "ExposureTime", static_cast<float>(exposure));
}

void MCameraHik::set_image_mode(const int &image_mode){
    image_mode_ = image_mode;
}
