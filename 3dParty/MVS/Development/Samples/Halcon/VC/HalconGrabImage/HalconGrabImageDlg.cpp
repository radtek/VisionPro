#include "stdafx.h"
#include "HalconGrabImage.h"
#include "HalconGrabImageDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAboutDlg dialog used for App About
class CAboutDlg : public CDialog
{
public:
    CAboutDlg();

// Dialog Data
    enum { IDD = IDD_ABOUTBOX };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CHalconGrabImageDlg dialog
CHalconGrabImageDlg::CHalconGrabImageDlg(CWnd* pParent /*=NULL*/)
: CDialog(CHalconGrabImageDlg::IDD, pParent)
, m_dExposureEdit(0)
, m_dGainEdit(0)
, m_dFrameRateEdit(0)
, m_bSoftwareTriggerCheck(FALSE)
, m_nDeviceCombo(0)
, m_bOpenDevice(FALSE)
, m_bStartGrabbing(FALSE)
{
    strcpy_s(m_chTriggerMode, 64, "Off");
    for (unsigned int i = 0; i < MV_MAX_DEVICE_NUM; i++)
    {
        m_pDeviceInfo[i] = NULL;
    }

    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHalconGrabImageDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EXPOSURE_EDIT, m_dExposureEdit);
    DDX_Text(pDX, IDC_GAIN_EDIT, m_dGainEdit);
    DDX_Text(pDX, IDC_FRAME_RATE_EDIT, m_dFrameRateEdit);
    DDX_Check(pDX, IDC_SOFTWARE_TRIGGER_CHECK, m_bSoftwareTriggerCheck);
    DDX_CBIndex(pDX, IDC_DEVICE_COMBO, m_nDeviceCombo);
    DDX_Control(pDX, IDC_OPEN_BUTTON, m_ctrlOpenButton);
    DDX_Control(pDX, IDC_CLOSE_BUTTON, m_ctrlCloseButton);
    DDX_Control(pDX, IDC_CONTINUS_MODE_RADIO, m_ctrlContinusModeRadio);
    DDX_Control(pDX, IDC_TRIGGER_MODE_RADIO, m_ctrlTriggerModeRadio);
    DDX_Control(pDX, IDC_START_GRABBING_BUTTON, m_ctrlStartGrabbingButton);
    DDX_Control(pDX, IDC_STOP_GRABBING_BUTTON, m_ctrlGrabImageButton);
    DDX_Control(pDX, IDC_SOFTWARE_TRIGGER_CHECK, m_ctrlSoftwareTriggerCheck);
    DDX_Control(pDX, IDC_SOFTWARE_ONCE_BUTTON, m_ctrlSoftwareOnceButton);
    DDX_Control(pDX, IDC_EXPOSURE_EDIT, m_ctrlExposureEdit);
    DDX_Control(pDX, IDC_GAIN_EDIT, m_ctrlGainEdit);
    DDX_Control(pDX, IDC_FRAME_RATE_EDIT, m_ctrlFrameRateEdit);
    DDX_Control(pDX, IDC_GET_PARAMETER_BUTTON, m_ctrlGetParameterButton);
    DDX_Control(pDX, IDC_SET_PARAMETER_BUTTON, m_ctrlSetParameterButton);
    DDX_Control(pDX, IDC_DEVICE_COMBO, m_ctrlDeviceCombo);
}

BEGIN_MESSAGE_MAP(CHalconGrabImageDlg, CDialog)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    //}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_ENUM_BUTTON, &CHalconGrabImageDlg::OnBnClickedEnumButton)
    ON_BN_CLICKED(IDC_OPEN_BUTTON, &CHalconGrabImageDlg::OnBnClickedOpenButton)
    ON_BN_CLICKED(IDC_CLOSE_BUTTON, &CHalconGrabImageDlg::OnBnClickedCloseButton)
    ON_BN_CLICKED(IDC_CONTINUS_MODE_RADIO, &CHalconGrabImageDlg::OnBnClickedContinusModeRadio)
    ON_BN_CLICKED(IDC_TRIGGER_MODE_RADIO, &CHalconGrabImageDlg::OnBnClickedTriggerModeRadio)
    ON_BN_CLICKED(IDC_START_GRABBING_BUTTON, &CHalconGrabImageDlg::OnBnClickedStartGrabbingButton)
    ON_BN_CLICKED(IDC_STOP_GRABBING_BUTTON, &CHalconGrabImageDlg::OnBnClickedGetOneFrameButton)
    ON_BN_CLICKED(IDC_SOFTWARE_TRIGGER_CHECK, &CHalconGrabImageDlg::OnBnClickedSoftwareTriggerCheck)
    ON_BN_CLICKED(IDC_SOFTWARE_ONCE_BUTTON, &CHalconGrabImageDlg::OnBnClickedSoftwareOnceButton)
    ON_BN_CLICKED(IDC_GET_PARAMETER_BUTTON, &CHalconGrabImageDlg::OnBnClickedGetParameterButton)
    ON_BN_CLICKED(IDC_SET_PARAMETER_BUTTON, &CHalconGrabImageDlg::OnBnClickedSetParameterButton)
    ON_CBN_SELCHANGE(IDC_DEVICE_COMBO, &CHalconGrabImageDlg::OnCbnSelchangeDeviceCombo)
END_MESSAGE_MAP()

void MyHalconExceptionHandler(const Halcon::HException& except)
{
    throw except;	
}

// CHalconGrabImageDlg message handlers

BOOL CHalconGrabImageDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // IDM_ABOUTBOX must be in the system command range.
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != NULL)
    {
        BOOL bNameValid;
        CString strAboutMenu;
        bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
        ASSERT(bNameValid);
        if (!strAboutMenu.IsEmpty())
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    // Set the icon for this dialog.  The framework does this automatically
    //  when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE);			// Set big icon
    SetIcon(m_hIcon, FALSE);		// Set small icon

    DisplayWindowInitial();     // ch:???????????? | en:Display Window Initialization

    HException::InstallHHandler(&MyHalconExceptionHandler);

    return TRUE;  // return TRUE  unless you set the focus to a control
}

void CHalconGrabImageDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX)
    {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    }
    else
    {
        CDialog::OnSysCommand(nID, lParam);
    }
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CHalconGrabImageDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this);

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;
		// Draw the icon
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialog::OnPaint();
    }
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CHalconGrabImageDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

// ch: ???????? || en: work thread
unsigned int    __stdcall   WorkThread(void* pUser)
{
    if (NULL == pUser)
    {
        return -1;
    }

    CHalconGrabImageDlg* pCam = (CHalconGrabImageDlg*)pUser;
    if (NULL == pCam)
    {
        MessageBox(NULL, TEXT("Error In WorkThread, NULL == pCam"), TEXT("warning"), MB_OK | MB_ICONWARNING);
        return -1;
    }

    Hobject Image;
    HTuple * hWindow = (HTuple *)(&(pCam->m_hWindowID));
    while (pCam->m_bStartGrabbing)
    {
        try
        {
            grab_image_async (&Image, pCam->m_htupHalconHandle, 1000);
            // ch: ???? || en: display
            HTuple hImageWidth, hImageHeight;
            get_image_pointer1(Image, NULL, NULL, &hImageWidth, &hImageHeight);// ????????????????????
            set_part(*hWindow, 0, 0, hImageHeight - 1, hImageWidth -1 );// ??????????????????????
            disp_obj((const Halcon::Hobject)Image, *hWindow);
            if(pCam->m_bIsAlwaysGrab == false)
            {
                pCam->m_bStartGrabbing = FALSE;
                break;
            }
        }
        catch(HException &except)
        {
            Herror  error_num = except.err;
        }
    }

    return 0;
}

/*????????????????????*/
void CHalconGrabImageDlg::EnableWindowWhenClose(void)
{
    m_ctrlOpenButton.EnableWindow(FALSE);
    m_ctrlCloseButton.EnableWindow(FALSE);
    m_ctrlStartGrabbingButton.EnableWindow(FALSE);
    m_ctrlGrabImageButton.EnableWindow(FALSE);
    m_ctrlSoftwareTriggerCheck.EnableWindow(FALSE);
    m_ctrlSoftwareOnceButton.EnableWindow(FALSE);
    m_ctrlExposureEdit.EnableWindow(FALSE);
    m_ctrlGainEdit.EnableWindow(FALSE);
    m_ctrlFrameRateEdit.EnableWindow(FALSE);
    m_ctrlGetParameterButton.EnableWindow(FALSE);
    m_ctrlSetParameterButton.EnableWindow(FALSE);
    m_ctrlContinusModeRadio.EnableWindow(FALSE);
    m_ctrlTriggerModeRadio.EnableWindow(FALSE);
}

// ch: ???????????????????? || en: The device is opened but it does not grab image
void CHalconGrabImageDlg::EnableWindowWhenOpenNotStart(void)
{
    m_ctrlOpenButton.EnableWindow(FALSE);
    m_ctrlCloseButton.EnableWindow(TRUE);
    m_ctrlStartGrabbingButton.EnableWindow(TRUE);
    m_ctrlSoftwareTriggerCheck.EnableWindow(TRUE);
    m_ctrlExposureEdit.EnableWindow(TRUE);
    m_ctrlGainEdit.EnableWindow(TRUE);
    m_ctrlFrameRateEdit.EnableWindow(TRUE);
    m_ctrlGetParameterButton.EnableWindow(TRUE);
    m_ctrlSetParameterButton.EnableWindow(TRUE);
    m_ctrlContinusModeRadio.EnableWindow(TRUE);
    m_ctrlTriggerModeRadio.EnableWindow(TRUE);
    m_ctrlGrabImageButton.EnableWindow(TRUE);
}

// ch: ???????????????????????????? || en: color of button when it starts grabbing image
void CHalconGrabImageDlg::EnableWindowWhenStart(void)
{
    m_ctrlGrabImageButton.EnableWindow(TRUE);
    m_ctrlStartGrabbingButton.EnableWindow(TRUE);
    if (TRUE == m_bSoftwareTriggerCheck && (!strcmp("On", m_chTriggerMode)))
    {
        m_ctrlSoftwareOnceButton.EnableWindow(TRUE);
    }
}

// ch: ???????????????????????? || en: color of button when it stops grabbing image
void CHalconGrabImageDlg::EnableWindowWhenStop(void)
{
    m_ctrlGrabImageButton.EnableWindow(FALSE);
    m_ctrlStartGrabbingButton.EnableWindow(TRUE);
    m_ctrlSoftwareOnceButton.EnableWindow(FALSE);
}

// ch: ???????????????????? || en: initialization of window in the beginning
void CHalconGrabImageDlg::DisplayWindowInitial(void)
{
    // ch: ?????????????????????? || en: defined display starting point, height, width, and length
    HTuple hWindowRow, hWindowColumn, hWindowWidth, hWindowHeight;  
    // ch: ????????ID || en: Define window ID
    HTuple hWindowID;

    // ch: ????????CRect???????????????????????????????????? || en: define an object of CRect class to measure the size and position of image window
    CRect mRect;  
    CStatic* pWnd = (CStatic*)GetDlgItem(IDC_DISPLAY_STATIC);  

    CDC *pDC = pWnd->GetDC();  
    pWnd->GetWindowRect(&mRect);  

    // ch: ???????????????????????? || en: set the starting point, width, and height of display window
    hWindowRow = 0;  
    hWindowColumn = 0;  
    hWindowWidth = mRect.Width();  
    hWindowHeight = mRect.Height();
    try  
    {   
        hWindowID = (long)pWnd->m_hWnd;  
        open_window(hWindowRow, hWindowColumn, hWindowWidth, hWindowHeight, hWindowID, "visible", "", &m_hWindowID);  
    }  
    catch (HException& except)  
    {  
        TRACE(except.message);  
    }

    EnableWindowWhenClose();
}

// ch: ???????? || en: open device
int CHalconGrabImageDlg::OpenDevice(void)
{
    if (TRUE == m_bOpenDevice)
    {
        return MV_E_CALLORDER;
    }
    UpdateData(TRUE);
    int nIndex = m_nDeviceCombo;
    if ((nIndex < 0) | (nIndex >= MV_MAX_DEVICE_NUM))
    {
        MessageBox(TEXT("Please select device"), TEXT("warning"), MB_OK | MB_ICONWARNING);
        return MV_E_PARAMETER;
    }

    // ch: ?????????????????????? || en: get and create example from the device information list
    if (NULL == m_pDeviceInfo[nIndex])
    {
        MessageBox(TEXT("Device does not exist"), TEXT("warning"), MB_OK | MB_ICONWARNING);
        return MV_E_PARAMETER;
    }

    char strSerial[64] = {0};
    if (MV_GIGE_DEVICE == m_pDeviceInfo[nIndex]->nTLayerType)
    {
        memcpy(strSerial, m_pDeviceInfo[nIndex]->SpecialInfo.stGigEInfo.chSerialNumber, 
            sizeof(m_pDeviceInfo[nIndex]->SpecialInfo.stGigEInfo.chSerialNumber));
    }
    else if (MV_USB_DEVICE == m_pDeviceInfo[nIndex]->nTLayerType)
    {
        memcpy(strSerial, m_pDeviceInfo[nIndex]->SpecialInfo.stUsb3VInfo.chSerialNumber,
            sizeof(m_pDeviceInfo[nIndex]->SpecialInfo.stUsb3VInfo.chSerialNumber));
    }
    else
    {
        return MV_E_PARAMETER;
    }

    try
    {
        open_framegrabber("MVision", 1, 1, 0, 0, 0, 0, "progressive", 8, "rgb", -1,
            "false", "auto", (char*)strSerial, 0, -1, &m_htupHalconHandle);
    }
    catch(HException &except)
    {
        Herror  error_num = except.err;
        return MV_E_UNKNOW;
    }

    m_bOpenDevice = TRUE;

    return MV_OK;
}

// ch: ???????? || en: close device
int CHalconGrabImageDlg::CloseDevice(void)
{
    if(m_bStartGrabbing == TRUE || m_bOpenDevice == TRUE)
    {
        try
        {
            close_framegrabber(m_htupHalconHandle);
        }
        catch(HException &except)
        {
            Herror  error_num = except.err;
            return MV_E_UNKNOW;
        }
    }

    m_bOpenDevice = FALSE;
    m_bStartGrabbing = FALSE;

    return MV_OK;
}

// ch: ???????????? || en: get trigger mode
int CHalconGrabImageDlg::GetTriggerMode(void)
{
    Halcon::HTuple str;
    try
    {
        get_framegrabber_param(m_htupHalconHandle, "TriggerMode", &str);
    }
    catch(HException &except)
    {
        Herror  error_num = except.err;
        return MV_E_UNKNOW;
    }

    strcpy_s(m_chTriggerMode, 64, str[0].S());
    if (!strcmp("On", str[0].S()))
    {
        OnBnClickedTriggerModeRadio();
    }
    else if (!strcmp("Off", str[0].S()))
    {
        OnBnClickedContinusModeRadio();
    }
    else
    {
        return MV_E_PARAMETER;
    }
    UpdateData(FALSE);

    return MV_OK;
}

// ch: ???????????? || en: set trigger mode
int CHalconGrabImageDlg::SetTriggerMode(void)
{
    try
    {
        set_framegrabber_param(m_htupHalconHandle, "TriggerMode", m_chTriggerMode);
    }
    catch(HException &except)
    {
        Herror  error_num = except.err;
        return MV_E_UNKNOW;
    }

    return MV_OK;
}

// ch: ???????????? ||en: get exposure time
int CHalconGrabImageDlg::GetExposureTime(void)
{
    Halcon::HTuple str;
    try
    {
        get_framegrabber_param(m_htupHalconHandle, "ExposureTime", &str);
    }
    catch(HException &except)
    {
        Herror  error_num = except.err;
        return MV_E_UNKNOW;
    }
    m_dExposureEdit = str[0].D();
    UpdateData(FALSE);

    return MV_OK;
}

// ch: ???????????? || en: set exposure time
int CHalconGrabImageDlg::SetExposureTime(void)
{
    /*??????????????????????????????????????*/
    try
    {
        set_framegrabber_param(m_htupHalconHandle, "ExposureMode", "Timed");
        set_framegrabber_param(m_htupHalconHandle, "ExposureAuto", "Off");
        set_framegrabber_param(m_htupHalconHandle, "ExposureTime", m_dExposureEdit);
    }
    catch(HException &except)
    {
        Herror  error_num = except.err;
        return MV_E_UNKNOW;
    }
    UpdateData(FALSE);

    return MV_OK;
}

// ch: ???????? || en: get gain
int CHalconGrabImageDlg::GetGain(void)
{
    Halcon::HTuple str;
    try
    {
        get_framegrabber_param(m_htupHalconHandle, "Gain", &str);
    }
    catch(HException &except)
    {
        Herror  error_num = except.err;
        return MV_E_UNKNOW;
    }
    m_dGainEdit = (int)str[0].D();
    UpdateData(FALSE);

    return MV_OK;
}

// ch: ???????? || en: set gain
int CHalconGrabImageDlg::SetGain(void)
{
    try
    {
        set_framegrabber_param(m_htupHalconHandle, "GainAuto", "Off");
        set_framegrabber_param(m_htupHalconHandle, "Gain", m_dGainEdit);
    }
    catch(HException &except)
    {
        Herror  error_num = except.err;
        return MV_E_UNKNOW;
    }
    UpdateData(FALSE);

    return MV_OK;
}

// ch: ???????? || en: get frame rate
int CHalconGrabImageDlg::GetFrameRate(void)
{
    Halcon::HTuple str;
    try
    {
        get_framegrabber_param(m_htupHalconHandle, "ResultingFrameRate", &str);
    }
    catch(HException &except)
    {
        Herror  error_num = except.err;
        return MV_E_UNKNOW;
    }
    m_dFrameRateEdit = (int)str[0].D();
    UpdateData(FALSE);

    return MV_OK;
}

// ch: ???????? || en: set frame rate
int CHalconGrabImageDlg::SetFrameRate(void)
{
    Halcon::HTuple str;
    try
    {
        get_framegrabber_param(m_htupHalconHandle, "AcquisitionFrameRateEnable", &str);
        if(str != true)
        {
            set_framegrabber_param(m_htupHalconHandle, "AcquisitionFrameRateEnable", true);
        }
        set_framegrabber_param(m_htupHalconHandle, "AcquisitionFrameRate", m_dFrameRateEdit);
    }
    catch(HException &except)
    {
        Herror  error_num = except.err;
        return MV_E_UNKNOW;
    }
    UpdateData(FALSE);

    return MV_OK;
}

// ch: ?????????? || en: get trigger source
int CHalconGrabImageDlg::GetTriggerSource(void)
{
    Halcon::HTuple str;
    try
    {
        get_framegrabber_param(m_htupHalconHandle, "TriggerSource", &str);
    }
    catch(HException &except)
    {
        Herror  error_num = except.err;
        return MV_E_UNKNOW;
    }

    if (!strcmp("TriggerSource", str[0].S()))
    {
        m_bSoftwareTriggerCheck = TRUE;
    }
    else
    {
        m_bSoftwareTriggerCheck = FALSE;
    }
    UpdateData(FALSE);

    return MV_OK;
}

// ch: ?????????? || en: set trigger source
int CHalconGrabImageDlg::SetTriggerSource(void)
{
    UpdateData(TRUE);

    if (m_bSoftwareTriggerCheck)
    {
        try
        {
            set_framegrabber_param(m_htupHalconHandle, "TriggerSource", "Software");
        }
        catch(HException &except)
        {
            MessageBox(TEXT("Set Software Trigger Fail"), TEXT("warning"), MB_OK | MB_ICONWARNING);
            Herror  error_num = except.err;
            return MV_E_UNKNOW;
        }
        m_ctrlSoftwareOnceButton.EnableWindow(TRUE);
    }
    else
    {
        try
        {
            set_framegrabber_param(m_htupHalconHandle, "TriggerSource", "Line0");
        }
        catch(HException &except)
        {
            MessageBox(TEXT("Set Hardware Trigger Fail"), TEXT("warning"), MB_OK | MB_ICONWARNING);
            Herror  error_num = except.err;
            return MV_E_UNKNOW;
        }
        m_ctrlSoftwareOnceButton.EnableWindow(FALSE);
    }

    try
    {
        set_framegrabber_param(m_htupHalconHandle, "AcquisitionFrameRate", m_dFrameRateEdit);
    }
    catch(HException &except)
    {
        Herror  error_num = except.err;
        return MV_E_UNKNOW;
    }

    return MV_OK;
}

void CHalconGrabImageDlg::OnBnClickedEnumButton()
{
    CString strMsg;

    // ch: 1. ?????????????????????? || en: 1. clear the information in the device list
    m_ctrlDeviceCombo.ResetContent();

    // ch: 2. ?????????????????? || en: 2. initialize information list of device
    MV_CC_DEVICE_INFO_LIST stDevList = {0};

    // ch: 3. ?????????????????? || en: 3. enumerate all of devices in the subnetwork
    int nRet = MV_CC_EnumDevices(MV_GIGE_DEVICE | MV_USB_DEVICE, &stDevList);
    if (MV_OK != nRet)
    {
        // ch: ???????????? || en: fail to enumerate devices
        return;
    }

    // ch: ???????????????????????????????? || en: add value to the information list and display it
    unsigned int i;
    int nIp1, nIp2, nIp3, nIp4;
    for (i = 0; i < stDevList.nDeviceNum; i++)
    {
        MV_CC_DEVICE_INFO* pDeviceInfo = stDevList.pDeviceInfo[i];
        if (NULL == pDeviceInfo)
        {
            continue;
        }

        if (m_pDeviceInfo[i] == NULL)
        {
            m_pDeviceInfo[i] = new MV_CC_DEVICE_INFO;
        }

        if (m_pDeviceInfo[i])
        {
            memcpy(m_pDeviceInfo[i], pDeviceInfo, sizeof(MV_CC_DEVICE_INFO));
        }

        if (pDeviceInfo->nTLayerType == MV_GIGE_DEVICE)
        {
            nIp1 = ((pDeviceInfo->SpecialInfo.stGigEInfo.nCurrentIp & 0xff000000) >> 24);
            nIp2 = ((pDeviceInfo->SpecialInfo.stGigEInfo.nCurrentIp & 0x00ff0000) >> 16);
            nIp3 = ((pDeviceInfo->SpecialInfo.stGigEInfo.nCurrentIp & 0x0000ff00) >> 8);
            nIp4 = (pDeviceInfo->SpecialInfo.stGigEInfo.nCurrentIp & 0x000000ff);

            wchar_t* pUserName = NULL;
            if (strcmp("", (LPCSTR)(pDeviceInfo->SpecialInfo.stGigEInfo.chUserDefinedName)) != 0)
            {
                DWORD dwLenUserName = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)(pDeviceInfo->SpecialInfo.stGigEInfo.chUserDefinedName), -1, NULL, 0);
                pUserName = new wchar_t[dwLenUserName];
                MultiByteToWideChar(CP_ACP, 0, (LPCSTR)(pDeviceInfo->SpecialInfo.stGigEInfo.chUserDefinedName), -1, pUserName, dwLenUserName);
            }
            else
            {
                char strUserName[256] = {0};
                sprintf_s(strUserName, "%s %s (%s)", pDeviceInfo->SpecialInfo.stGigEInfo.chManufacturerName,
                    pDeviceInfo->SpecialInfo.stGigEInfo.chModelName,
                    pDeviceInfo->SpecialInfo.stGigEInfo.chSerialNumber);
                DWORD dwLenUserName = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)(strUserName), -1, NULL, 0);
                pUserName = new wchar_t[dwLenUserName];
                MultiByteToWideChar(CP_ACP, 0, (LPCSTR)(strUserName), -1, pUserName, dwLenUserName);
            }
            strMsg.Format(_T("[%d]GigE:    %s  (%d.%d.%d.%d)"), i, 
                pUserName, nIp1, nIp2, nIp3, nIp4);
            if (NULL != pUserName)
            {
                delete(pUserName);
                pUserName = NULL;
            }
        }
        else if (pDeviceInfo->nTLayerType == MV_USB_DEVICE)
        {
            wchar_t* pUserName = NULL;

            if (strcmp("", (char*)pDeviceInfo->SpecialInfo.stUsb3VInfo.chUserDefinedName) != 0)
            {
                DWORD dwLenUserName = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)(pDeviceInfo->SpecialInfo.stUsb3VInfo.chUserDefinedName), -1, NULL, 0);
                pUserName = new wchar_t[dwLenUserName];
                MultiByteToWideChar(CP_ACP, 0, (LPCSTR)(pDeviceInfo->SpecialInfo.stUsb3VInfo.chUserDefinedName), -1, pUserName, dwLenUserName);
            }
            else
            {
                char strUserName[256];
                sprintf_s(strUserName, "%s %s (%s)", pDeviceInfo->SpecialInfo.stUsb3VInfo.chManufacturerName,
                    pDeviceInfo->SpecialInfo.stUsb3VInfo.chModelName,
                    pDeviceInfo->SpecialInfo.stUsb3VInfo.chSerialNumber);
                DWORD dwLenUserName = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)(strUserName), -1, NULL, 0);
                pUserName = new wchar_t[dwLenUserName];
                MultiByteToWideChar(CP_ACP, 0, (LPCSTR)(strUserName), -1, pUserName, dwLenUserName);
            }
            strMsg.Format(_T("[%d]UsbV3:  %s"), i, pUserName);
            if (NULL != pUserName)
            {
                delete(pUserName);
                pUserName = NULL;
            }
        }
        else
        {
            MessageBox(TEXT("Unknown device enumerated"), TEXT("warning"), MB_OK | MB_ICONWARNING);;
        }
        m_ctrlDeviceCombo.AddString(strMsg);
    }
    m_ctrlDeviceCombo.SetCurSel(CB_ERR);

    // ch: ???????????????????????? || en: display the device after enumeration
    UpdateData(FALSE);

    if (0 == stDevList.nDeviceNum)
    {
        MessageBox(TEXT("No device"));
        return;
    }
    // ch: ???????????????????????? || en:show the button for opening device
    m_ctrlOpenButton.EnableWindow(TRUE);

    return;
}

void CHalconGrabImageDlg::OnBnClickedOpenButton()
{
    int nRet = OpenDevice();
    if (MV_OK != nRet)
    {
        MessageBox(TEXT("Open fail"), TEXT("warning"), MB_OK | MB_ICONWARNING);
        return;
    }

	nRet = GetTriggerMode();
	if (nRet != MV_OK)
	{
	    MessageBox(TEXT("Get Trigger Mode Fail"), TEXT("warning"), MB_OK | MB_ICONWARNING);
	}

	nRet = GetTriggerSource();
	if (nRet != MV_OK)
	{
	    MessageBox(TEXT("Get Trigger Source Fail"), TEXT("warning"), MB_OK | MB_ICONWARNING);
	}

    OnBnClickedGetParameterButton(); // ch: ???????? || en: get parameter
    EnableWindowWhenOpenNotStart();

    return;
}

void CHalconGrabImageDlg::OnBnClickedCloseButton()
{
    CloseDevice();
    EnableWindowWhenClose();
    m_ctrlOpenButton.EnableWindow(TRUE);

    return;
}

void CHalconGrabImageDlg::OnBnClickedContinusModeRadio()
{
    ((CButton *)GetDlgItem(IDC_CONTINUS_MODE_RADIO))->SetCheck(TRUE);
    ((CButton *)GetDlgItem(IDC_TRIGGER_MODE_RADIO))->SetCheck(FALSE);
    ((CButton *)GetDlgItem(IDC_SOFTWARE_TRIGGER_CHECK))->EnableWindow(FALSE);
    strcpy_s(m_chTriggerMode, 64, "Off");
    int nRet = SetTriggerMode();
    if (MV_OK != nRet)
    {
        return;
    }
    m_ctrlSoftwareOnceButton.EnableWindow(FALSE);

    return;
}

void CHalconGrabImageDlg::OnBnClickedTriggerModeRadio()
{
    ((CButton *)GetDlgItem(IDC_CONTINUS_MODE_RADIO))->SetCheck(FALSE);
    ((CButton *)GetDlgItem(IDC_TRIGGER_MODE_RADIO))->SetCheck(TRUE);
    ((CButton *)GetDlgItem(IDC_SOFTWARE_TRIGGER_CHECK))->EnableWindow(TRUE);
    strcpy_s(m_chTriggerMode, 64, "On");
    int nRet = SetTriggerMode();
    if (MV_OK != nRet)
    {
        MessageBox(TEXT("Set Trigger Mode Fail"), TEXT("warning"), MB_OK | MB_ICONWARNING);
        return;
    }

    if (m_bStartGrabbing == TRUE)
    {
        UpdateData(TRUE);
        if (TRUE == m_bSoftwareTriggerCheck)
        {
            m_ctrlSoftwareOnceButton.EnableWindow(TRUE);
        }
    }

    return;
}

void CHalconGrabImageDlg::OnBnClickedStartGrabbingButton()
{
    if (FALSE == m_bOpenDevice || TRUE == m_bStartGrabbing)
    {
        return;
    }

    try
    {
        grab_image_start(m_htupHalconHandle, -1);
    }
    catch(HException &except)
    {
        Herror  error_num = except.err;
        return;
    }

    m_bStartGrabbing = TRUE;
    m_bIsAlwaysGrab = true;
    unsigned int nThreadID = 0;
    m_hGetOneFrameHandle = (void*) _beginthreadex( NULL , 0 , WorkThread , this, 0 , &nThreadID );
    if (NULL == m_hGetOneFrameHandle)
    {
        MessageBox(TEXT("Create thread fail"), TEXT("warning"), MB_OK | MB_ICONWARNING);
    }
    EnableWindowWhenStart();

    return;
}

void CHalconGrabImageDlg::OnBnClickedGetOneFrameButton()
{
    if (FALSE == m_bOpenDevice)
    {
        return;
    }

    if( TRUE == m_bStartGrabbing)
    {
        m_bStartGrabbing = FALSE;
    }
    else
    {
        m_bStartGrabbing = TRUE;
    }
    
    unsigned int nThreadID = 0;
    m_bIsAlwaysGrab = false;
    m_hOnlyGetOneFrameHandle = (void*) _beginthreadex( NULL , 0 , WorkThread, this, 0 , &nThreadID );
    if (NULL == m_hOnlyGetOneFrameHandle)
    {
        MessageBox(TEXT("Create thread fail"), TEXT("warning"), MB_OK | MB_ICONWARNING);
    }

    return;
}

void CHalconGrabImageDlg::OnBnClickedSoftwareTriggerCheck()
{
    int nRet = SetTriggerSource();
    if (nRet != MV_OK)
    {
        return;
    }

    return;
}

void CHalconGrabImageDlg::OnBnClickedSoftwareOnceButton()
{
    if (TRUE != m_bStartGrabbing)
    {
        return;
    }

    try
    {
        set_framegrabber_param(m_htupHalconHandle, "TriggerSoftware", 0);
    }
    catch(HException &except)
    {
        MessageBox(TEXT("TriggerSoftware failed!"), TEXT("warning"), MB_OK | MB_ICONWARNING);
        Herror  error_num = except.err;
    }

    return;
}

void CHalconGrabImageDlg::OnBnClickedGetParameterButton()
{
    int nRet = GetExposureTime();
    if (nRet != MV_OK)
    {
        MessageBox(TEXT("Get Exposure Time Fail"), TEXT("warning"), MB_OK | MB_ICONWARNING);
        return;
    }

    nRet = GetGain();
    if (nRet != MV_OK)
    {
        MessageBox(TEXT("Get Gain Fail"), TEXT("warning"), MB_OK | MB_ICONWARNING);
        return;
    }

    nRet = GetFrameRate();
    if (nRet != MV_OK)
    {
        MessageBox(TEXT("Get Frame Rate Fail"), TEXT("warning"), MB_OK | MB_ICONWARNING);
        return;
    }

    return;
}

void CHalconGrabImageDlg::OnBnClickedSetParameterButton()
{
    UpdateData(TRUE);

    bool bIsSetSucceed = true;
    int nRet = SetExposureTime();
    if (nRet != MV_OK)
    {
        bIsSetSucceed = false;
        MessageBox(TEXT("Set Exposure Time Fail"), TEXT("warning"), MB_OK | MB_ICONWARNING);
    }
    nRet = SetGain();
    if (nRet != MV_OK)
    {
        bIsSetSucceed = false;
        MessageBox(TEXT("Set Gain Fail"), TEXT("warning"), MB_OK | MB_ICONWARNING);
    }
    nRet = SetFrameRate();
    if (nRet != MV_OK)
    {
        bIsSetSucceed = false;
        MessageBox(TEXT("Set Frame Rate Fail"), TEXT("warning"), MB_OK | MB_ICONWARNING);
    }

    if (true == bIsSetSucceed)
    {
        MessageBox(TEXT("Set Parameter Succeed"), TEXT("warning"), MB_OK | MB_ICONWARNING);
    }

    return;
}

void CHalconGrabImageDlg::OnCbnSelchangeDeviceCombo()
{
    // TODO: Add your control notification handler code here
    m_nDeviceCombo = m_ctrlDeviceCombo.GetCurSel();
    return;
}

BOOL CHalconGrabImageDlg::PreTranslateMessage(MSG* pMsg)
{
    if (pMsg->message == WM_KEYDOWN&&pMsg->wParam == VK_ESCAPE)
    {
        // ch:????????????????????????????Esc????????????????????????????????????????????????????????
        // en:If the message is a keyboard press event and a Esc key, execute the following code (nothing is done, you can add the code you want)
        return TRUE;
    }
    if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
    {
        // ch:????????????????????????????Entert????????????????????????????????????????????????????????
        // en:If the message is a keyboard press event and a Esc key, execute the following code (nothing is done, you can add the code you want)
        return TRUE;
    }

    return CDialog::PreTranslateMessage(pMsg);
}
