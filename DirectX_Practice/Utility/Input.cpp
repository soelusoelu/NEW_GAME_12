#include "Input.h"

BOOL CALLBACK enumJoysticksCallback(const DIDEVICEINSTANCE*, VOID*);
BOOL CALLBACK enumObjectsCallback(const DIDEVICEOBJECTINSTANCE*, VOID*);

HRESULT Input::init(HWND hWnd) {
    // �uDirectInput�v�I�u�W�F�N�g�̍쐬
    if (FAILED(DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&mDinput, NULL))) {
        return E_FAIL;
    }

    // �uDirectInput�f�o�C�X�v�I�u�W�F�N�g�̍쐬
    if (FAILED(mDinput->CreateDevice(GUID_SysKeyboard, &mKeyDevice, NULL))) {
        return E_FAIL;
    }
    // �f�o�C�X���L�[�{�[�h�ɐݒ�
    if (FAILED(mKeyDevice->SetDataFormat(&c_dfDIKeyboard))) {
        return E_FAIL;
    }
    // �������x���̐ݒ�
    if (FAILED(mKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND))) {
        return E_FAIL;
    }
    // �f�o�C�X���u�擾�v����
    mKeyDevice->Acquire();

    //���p�\�ȃQ�[���R���g���[���[�̗񋓊֐������s
    if (FAILED(mDinput->EnumDevices(DI8DEVCLASS_GAMECTRL, enumJoysticksCallback, NULL, DIEDFL_ATTACHEDONLY))) {
        return E_FAIL;
    }
    if (!mPadDevice) { //�p�b�h�̐ڑ��͂����ɏI��
        return S_OK;
    }
    // �f�o�C�X���W���C�X�e�B�b�N�ɐݒ�
    if (FAILED(mPadDevice->SetDataFormat(&c_dfDIJoystick2))) {
        return E_FAIL;
    }
    // �������x���̐ݒ�
    if (FAILED(mPadDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND))) {
        return E_FAIL;
    }
    //�A�v���P�[�V�����Ŏg�p����R���g���[���[�̃v���p�e�B��񋓂��Đݒ肷��
    if (FAILED(mPadDevice->EnumObjects(enumObjectsCallback, NULL, DIDFT_ALL))) {
        return E_FAIL;
    }
    // �f�o�C�X���u�擾�v����
    mPadDevice->Acquire();

    return S_OK;
}

BOOL CALLBACK enumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance, VOID* pContext) {
    //�����񋓂����ꍇ�A���[�U�[�ɑI���E�m�F������
    WCHAR szConfirm[MAX_PATH];
    //���Ŏg�p�\�p�b�h��񋓂��邪�A���͍ŏ��̈�ŏ�����
    //wsprintf(szConfirm, L"���̕����f�o�C�X�Ńf�o�C�X�I�u�W�F�N�g���쐬���܂����H\n���i��%s\n�C���X�^���X��%s", pdidInstance->tszProductName, pdidInstance->tszInstanceName);
    //if (MessageBox(0, szConfirm, L"�m�F", MB_YESNO) == IDNO) {
    //    return DIENUM_CONTINUE;
    //}
    // �uDirectInput�f�o�C�X�v�I�u�W�F�N�g�̍쐬
    if (FAILED(Input::mDinput->CreateDevice(pdidInstance->guidInstance, &Input::mPadDevice, NULL))) {
        return DIENUM_CONTINUE;
    }
    return DIENUM_STOP;
}

BOOL CALLBACK enumObjectsCallback(const DIDEVICEOBJECTINSTANCE* pdidoi, VOID* pContext) {
    if (pdidoi->dwType & DIDFT_AXIS) {
        DIPROPRANGE diprg;
        diprg.diph.dwSize = sizeof(DIPROPRANGE);
        diprg.diph.dwHeaderSize = sizeof(DIPROPHEADER);
        diprg.diph.dwHow = DIPH_BYID;
        diprg.diph.dwObj = pdidoi->dwType;
        diprg.lMin = -1000;
        diprg.lMax = 1000;

        if (FAILED(Input::mPadDevice->SetProperty(DIPROP_RANGE, &diprg.diph))) {
            return DIENUM_STOP;
        }
    }
    return DIENUM_CONTINUE;
}

void Input::end() {
    SAFE_RELEASE(mDinput);
    SAFE_RELEASE(mKeyDevice);
    SAFE_RELEASE(mPadDevice);
}

void Input::update() {
    for (int i = 0; i < 256; i++) {
        mPreviousKeys[i] = mCurrentKeys[i];
    }
    mPreviousJoyState = mCurrentJoyState;

    HRESULT hr = mKeyDevice->Acquire();
    if ((hr == DI_OK) || (hr == S_FALSE)) {
        mKeyDevice->GetDeviceState(sizeof(mCurrentKeys), &mCurrentKeys);
    }
    if (mPadDevice) {
        hr = mPadDevice->Acquire();
        if ((hr == DI_OK) || (hr == S_FALSE)) {
            mPadDevice->GetDeviceState(sizeof(DIJOYSTATE2), &mCurrentJoyState);
        }
    }
}

bool Input::getKeyDown(KeyCode key) {
    return (mCurrentKeys[static_cast<BYTE>(key)] & 0x80 && !(mPreviousKeys[static_cast<BYTE>(key)] & 0x80));
}

bool Input::getJoyStickDown(JoyCode joy) {
    return (mCurrentJoyState.rgbButtons[static_cast<int>(joy)] & 0x80 && !(mPreviousJoyState.rgbButtons[static_cast<int>(joy)] & 0x80));
}

bool Input::getKey(KeyCode key) {
    return mCurrentKeys[static_cast<BYTE>(key)] & 0x80;
}

bool Input::getJoy(JoyCode joy) {
    return mCurrentJoyState.rgbButtons[static_cast<int>(joy)] & 0x80;
}

bool Input::getKeyUp(KeyCode key) {
    return (!(mCurrentKeys[static_cast<BYTE>(key)] & 0x80) && mPreviousKeys[static_cast<BYTE>(key)] & 0x80);
}

bool Input::getJoyUp(JoyCode joy) {
    return (!(mCurrentJoyState.rgbButtons[static_cast<int>(joy)] & 0x80) && mPreviousJoyState.rgbButtons[static_cast<int>(joy)] & 0x80);
}

int Input::horizontal() {
    if (getKey(KeyCode::A) || getKey(KeyCode::LeftArrow)) {
        return -1;
    } else if (getKey(KeyCode::D) || getKey(KeyCode::RightArrow)) {
        return 1;
    } else {
        return 0;
    }
}

int Input::vertical() {
    if (getKey(KeyCode::W) || getKey(KeyCode::UpArrow)) {
        return 1;
    } else if (getKey(KeyCode::S) || getKey(KeyCode::DownArrow)) {
        return -1;
    } else {
        return 0;
    }
}

BYTE Input::mCurrentKeys[256] = { 0 };
BYTE Input::mPreviousKeys[256] = { 0 };
DIJOYSTATE2 Input::mCurrentJoyState;
DIJOYSTATE2 Input::mPreviousJoyState;
LPDIRECTINPUT8 Input::mDinput = nullptr;
LPDIRECTINPUTDEVICE8 Input::mKeyDevice = nullptr;
LPDIRECTINPUTDEVICE8 Input::mPadDevice = nullptr;
