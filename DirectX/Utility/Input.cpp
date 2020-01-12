#include "Input.h"
#include "../System/Game.h"
#include <algorithm>

BOOL CALLBACK enumJoysticksCallback(const DIDEVICEINSTANCE*, VOID*);
BOOL CALLBACK enumObjectsCallback(const DIDEVICEOBJECTINSTANCE*, VOID*);

HRESULT Input::init(HWND hWnd) {
    // 「DirectInput」オブジェクトの作成
    if (FAILED(DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&mDinput, NULL))) {
        return E_FAIL;
    }

    // 「DirectInputデバイス」オブジェクトの作成
    if (FAILED(mDinput->CreateDevice(GUID_SysKeyboard, &mKeyDevice, NULL))) {
        return E_FAIL;
    }
    // デバイスをキーボードに設定
    if (FAILED(mKeyDevice->SetDataFormat(&c_dfDIKeyboard))) {
        return E_FAIL;
    }
    // 協調レベルの設定
    if (FAILED(mKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND))) {
        return E_FAIL;
    }
    // デバイスを「取得」する
    mKeyDevice->Acquire();

    //利用可能なゲームコントローラーの列挙関数を実行
    if (FAILED(mDinput->EnumDevices(DI8DEVCLASS_GAMECTRL, enumJoysticksCallback, NULL, DIEDFL_ATTACHEDONLY))) {
        return E_FAIL;
    }
    if (!mPadDevice) { //パッドの接続はせずに終了
        return S_OK;
    }
    // デバイスをジョイスティックに設定
    if (FAILED(mPadDevice->SetDataFormat(&c_dfDIJoystick2))) {
        return E_FAIL;
    }
    // 協調レベルの設定
    if (FAILED(mPadDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND))) {
        return E_FAIL;
    }
    //アプリケーションで使用するコントローラーのプロパティを列挙して設定する
    if (FAILED(mPadDevice->EnumObjects(enumObjectsCallback, NULL, DIDFT_ALL))) {
        return E_FAIL;
    }
    // デバイスを「取得」する
    mPadDevice->Acquire();

    return S_OK;
}

//追加
// 1つのデバイスごとに呼び出されるコールバック関数
BOOL PASCAL EnumJoyDeviceProc(HWND hWnd, LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef)
{
	//DEBUG("コールバック呼び出し\n");

	// ジョイスティックデバイスの作成
	HRESULT ret = Input::mDinput->CreateDevice(lpddi->guidInstance, &Input::mPadDevice, NULL);
	if (FAILED(ret)) {
		//DEBUG("デバイス作成失敗\n");
		return DIENUM_STOP;
	}

	// 入力データ形式のセット
	ret = Input::mPadDevice->SetDataFormat(&c_dfDIJoystick);
	if (FAILED(ret)) {
		//DEBUG("入力データ形式のセット失敗\n");
		Input::mPadDevice->Release();
		return DIENUM_STOP;
	}

	// 排他制御のセット
	ret = Input::mPadDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	if (FAILED(ret)) {
		//DEBUG("排他制御のセット失敗\n");
		Input::mPadDevice->Release();
		return DIENUM_STOP;
	}

	// 入力範囲のセット
	DIPROPRANGE diprg;
	diprg.diph.dwSize = sizeof(diprg);
	diprg.diph.dwHeaderSize = sizeof(diprg.diph);
	diprg.diph.dwHow = DIPH_BYOFFSET;
	diprg.lMax = 1000;
	diprg.lMin = -1000;

	// X軸
	diprg.diph.dwObj = DIJOFS_X;
	Input::mPadDevice->SetProperty(DIPROP_RANGE, &diprg.diph);

	// Y軸
	diprg.diph.dwObj = DIJOFS_Y;
	Input::mPadDevice->SetProperty(DIPROP_RANGE, &diprg.diph);

	// Z軸
	diprg.diph.dwObj = DIJOFS_Z;
	Input::mPadDevice->SetProperty(DIPROP_RANGE, &diprg.diph);

	// RX軸
	diprg.diph.dwObj = DIJOFS_RX;
	Input::mPadDevice->SetProperty(DIPROP_RANGE, &diprg.diph);

	// RY軸
	diprg.diph.dwObj = DIJOFS_RY;
	Input::mPadDevice->SetProperty(DIPROP_RANGE, &diprg.diph);

	// RZ軸
	diprg.diph.dwObj = DIJOFS_RZ;
	Input::mPadDevice->SetProperty(DIPROP_RANGE, &diprg.diph);

	// 起動準備完了
	Input::mPadDevice->Poll();

	// 構築完了なら
	//DEBUG("インスタンスの登録名 [%s]\n", lpddi->tszInstanceName);
	//DEBUG("製品の登録名         [%s]\n", lpddi->tszProductName);
	//DEBUG("構築完了\n");

	// 最初の1つのみで終わる
	return DIENUM_STOP;         // 次のデバイスを列挙するにはDIENUM_CONTINUEを返す
}
//ここまで

BOOL CALLBACK enumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance, VOID* pContext) {
    //複数列挙される場合、ユーザーに選択・確認させる
    WCHAR szConfirm[MAX_PATH];
    //↓で使用可能パッドを列挙するが、今は最初の一つで初期化
    //wsprintf(szConfirm, L"この物理デバイスでデバイスオブジェクトを作成しますか？\n商品名%s\nインスタンス名%s", pdidInstance->tszProductName, pdidInstance->tszInstanceName);
    //if (MessageBox(0, szConfirm, L"確認", MB_YESNO) == IDNO) {
    //    return DIENUM_CONTINUE;
    //}
    // 「DirectInputデバイス」オブジェクトの作成
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

	//追加
	if (mPadDevice)
	{
		mPadDevice->Release();
		mDinput->Release();
	}
	//ここまで
}

void Input::update() {
    memcpy_s(mPreviousKeys, sizeof(mPreviousKeys), mCurrentKeys, sizeof(mCurrentKeys));
    mPreviousJoyState = mCurrentJoyState;

    HRESULT hr = mKeyDevice->Acquire();
    if ((hr == DI_OK) || (hr == S_FALSE)) {
        mKeyDevice->GetDeviceState(sizeof(mCurrentKeys), &mCurrentKeys);
    }
    if (mPadDevice) {
        hr = mPadDevice->Acquire();
        if ((hr == DI_OK) || (hr == S_FALSE)) {
            //mPadDevice->GetDeviceState(sizeof(DIJOYSTATE2), &mCurrentJoyState);
			//変更
			// ジョイスティックの入力
			DIJOYSTATE joy;
			ZeroMemory(&joy, sizeof(joy));
			HRESULT ret = mPadDevice->GetDeviceState(sizeof(joy), &joy);
			if (FAILED(ret)) {
				// 失敗なら再び動作開始を行う
				mPadDevice->Acquire();
			}
        }
    }

	//追加
	//mPadDevice->Acquire();
	// データ取得前にPollが必要なら
	//if (dc.dwFlags&DIDC_POLLEDDATAFORMAT) {
	//	lpJoystick->Poll();
	//}

	// ジョイスティックの入力
	//DIJOYSTATE joy;
	//ZeroMemory(&joy, sizeof(joy));
	//HRESULT ret = mPadDevice->GetDeviceState(sizeof(joy), &joy);
	//if (FAILED(ret)) {
	//	// 失敗なら再び動作開始を行う
	//	mPadDevice->Acquire();
	//}
	//ここまで
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

bool Input::getJoya(JoyCode joy)
{
	DIPROPRANGE diprg;
	diprg.diph.dwSize = sizeof(diprg);
	diprg.diph.dwHeaderSize = sizeof(diprg.diph);
	diprg.diph.dwHow = DIPH_BYOFFSET;
	diprg.lMax = 1000;
	diprg.lMin = -1000;
	return mPadDevice->SetProperty(DIPROP_RANGE, &diprg.diph);
}

bool Input::getKeyUp(KeyCode key) {
    return (!(mCurrentKeys[static_cast<BYTE>(key)] & 0x80) && mPreviousKeys[static_cast<BYTE>(key)] & 0x80);
}

bool Input::getJoyUp(JoyCode joy) {
    return (!(mCurrentJoyState.rgbButtons[static_cast<int>(joy)] & 0x80) && mPreviousJoyState.rgbButtons[static_cast<int>(joy)] & 0x80);
}

int Input::horizontal() {
    if (getKey(KeyCode::A) || getKey(KeyCode::LeftArrow)/*||getJoya(JoyCode::B) */){
        return -1;
    } else if (getKey(KeyCode::D) || getKey(KeyCode::RightArrow) || getJoy(JoyCode::A)) {
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
